#include <RheiaApp.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_wizrd.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/clipbrd.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/cmdline.h>
#include <wx/utils.h>
#include <wx/snglinst.h>

#include <RheiaXtraRes.h>
#include <RheiaException.h>
#include <RheiaGlobals.h>
#include <RheiaSplashScreen.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaEnvironementManager.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaEventFrame.h>

wxCmdLineParser parser;
//RheiaEnvironementManager* env = RheiaEnvironementManager::Get();

/************************************************
This is the Source File for RheiaApp

 * Author: Nicolas Macherey
 * Date: 2008.11.6
 ************************************************/

class Splash
{
public:
	Splash(const bool show) : m_pSplash(0)
	{
		if (show)
		{
			wxBitmap bmp = RheiaLoadBitmap (RheiaStandardPaths::DataDirectoryGlobal() + (_T("/resource.zip#zip:splash_screen.png")) );
			m_pSplash = new RheiaSplashScreen(bmp);
		}
	}
	~Splash() { Hide(); }
	void Hide()
	{
		if (m_pSplash)
		{
			m_pSplash->Destroy();
			m_pSplash = 0;
		}
	}
private:
	RheiaSplashScreen* m_pSplash;
};

IMPLEMENT_APP(RheiaApp)

BEGIN_EVENT_TABLE(RheiaApp, wxApp)
	EVT_ACTIVATE_APP( RheiaApp::OnAppActivate )
END_EVENT_TABLE()

bool RheiaApp::OnInit(){
	/* Enables wxLogging for the application */
#ifndef RHEIA_ENABLE_WXLOGGING
    wxLog::EnableLogging(false);
#endif

#ifdef LINUX
    setlocale(LC_ALL,"C");
#endif

	/* Fushing the clip board */
	wxTheClipboard->Flush();

	/* Initialize File system handler for zip and memory FS */
	wxFileSystem::AddHandler(new wxZipFSHandler);
    wxFileSystem::AddHandler(new wxMemoryFSHandler);
	/* Initialising all image handlers */
    wxInitAllImageHandlers();
	/* Initialising Xml ressource handler */
    wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->AddHandler( new wxToolBarAddOnXmlHandler );

	RheiaManager::Get();
	RheiaStandardPaths::InitPaths();

	m_singleInstanceChecker = 0;

    try
    {
        if(RheiaProfileManager::Get()->GetActiveProfileManager()->ReadBool(_T("/environment/single_instance"), true))
        {
            const wxString name = wxString::Format(_T("Rheia FrameWork-%s"), wxGetUserId().c_str());

            m_singleInstanceChecker = new wxSingleInstanceChecker(name, RheiaStandardPaths::TempDirectory());
            if (m_singleInstanceChecker->IsAnotherRunning())
            {

                /* NOTE: Due to a recent change in logging code, this visual warning got disabled.
                   So the wxLogError() has been changed to a wxMessageBox(). */
                wxMessageBox(_("Another program instance is already running.\nRheia is currently configured to only allow one running instance.\n\nYou can access this Setting under the menu item 'Environment Settings'."),
                            _T("RHEIA"), wxOK | wxICON_ERROR);
                return false;
            }
        }
    }catch(RheiaException& err)
    {
        err.ShowErrorMessage();
    }

	Splash splash(true);

	if(!LoadConfig())
            return false;

	/* Initialize resource */
	if(!InitXRCStuff())
		wxMessageBox(_T("An error append while loading ressource"),_("Rheia : ERROR"));

	/* Initialize the Main Frame of the application */
	MainFrame = InitMainFrame();

	/* Setting the window and showing the frame */
	SetTopWindow(MainFrame);
    MainFrame->Show();

    try
    {
        RheiaConfigurationManager* CfgMgr = RheiaProfileManager::Get()->GetActiveProfileManager();
        CfgMgr->ReadFrameInfo( wxT("/MainFrame") , MainFrame );
    }
    catch(RheiaException& err)
    {

    }
    splash.Hide();
    RheiaEvent event(RheiaEVT_APP_STARTUP_DONE);
    RheiaEventsManager::Get()->ProcessEvent( event );

    return true;
}

int RheiaApp::OnRun()
{
    try
    {
        int retval = wxApp::OnRun();
        return retval;
    }
    catch (...)
    {
        wxSafeShowMessage(_("Exception"), _("Unknown exception was raised. The application will terminate immediately..."));
    }
    // if we reached here, return error
    return -1;
}

/* Membership function for initializing the main frame */
RheiaMainFrame *RheiaApp::InitMainFrame(void)
{
	RheiaMainFrame *frame = new RheiaMainFrame(NULL,
		wxID_ANY,
		_T("Rheia"),wxDefaultPosition,wxSize(1200,600));

//    wxUpdateUIEvent::SetUpdateInterval(100);
//
//    SetTopWindow(0);

	return frame;
}

/* Parsing the command line */
bool RheiaApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    return wxApp::OnCmdLineParsed(parser);
}

/* Callback used for ending the application */
int RheiaApp::OnExit()
{
	/* Flushing the clipboard */
    wxTheClipboard->Flush();
	/* Freeing global manager instance at the totally end of the application */
	RheiaManager::Get()->Close();
    RheiaManager::Free();

    return 0;
}

bool RheiaApp::InitXRCStuff()
{
	if (!RheiaManager::LoadResource(_T("resource.zip")))
    {
        return false;
    }
    return true;
}

/****************************************************************************************************
*Gestion du command line parser
***************************************************************************************************/
#if wxCHECK_VERSION(2, 9, 0)
#define CMD_ENTRY(X) X
#else
#define CMD_ENTRY(X) _T(X)
#endif
const wxCmdLineEntryDesc cmdLineDesc[] =
{
    { wxCMD_LINE_SWITCH, CMD_ENTRY("h"),  CMD_ENTRY("help"),                  CMD_ENTRY("show this help message"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
    { wxCMD_LINE_SWITCH, CMD_ENTRY("?"),  CMD_ENTRY("?"),                     CMD_ENTRY("show this help message (alias for help)"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
#ifdef __WXMSW__
    { wxCMD_LINE_SWITCH, CMD_ENTRY("na"), CMD_ENTRY("no-check-associations"), CMD_ENTRY("don't perform any association checks, file association are used to associate file extensions to Rheia"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },
#endif
    { wxCMD_LINE_SWITCH, CMD_ENTRY("ns"), CMD_ENTRY("no-splash-screen"),      CMD_ENTRY("don't display a splash screen while loading"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_OPTION, CMD_ENTRY(""),   CMD_ENTRY("prefix"),                CMD_ENTRY("the shared data dir prefix, specifies where the application can find the ressources, however if not set the installed application path will be getted"),
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_NEEDS_SEPARATOR },
    { wxCMD_LINE_OPTION, CMD_ENTRY("p"),  CMD_ENTRY("personality"),           CMD_ENTRY("the personality to use: \"ask\" or <personality-name>"),
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_NEEDS_SEPARATOR },
    { wxCMD_LINE_SWITCH, CMD_ENTRY(""),   CMD_ENTRY("no-log"),                CMD_ENTRY("turn off the application log, the log window is used to display different information"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_SWITCH, CMD_ENTRY(""),   CMD_ENTRY("log-to-file"),           CMD_ENTRY("redirect application log to a file"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_OPTION, CMD_ENTRY(""),   CMD_ENTRY("profile"),               CMD_ENTRY("synonym to personality"),
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_NEEDS_SEPARATOR },
    { wxCMD_LINE_OPTION, CMD_ENTRY(""),   CMD_ENTRY("script"),                CMD_ENTRY("execute script file, script files are used to start the application with a specific configuration and workspaces. T"),
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_NEEDS_SEPARATOR },
    { wxCMD_LINE_OPTION, CMD_ENTRY(""),   CMD_ENTRY("file"),                  CMD_ENTRY("open file and optionaly select experiment or project"),
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_NEEDS_SEPARATOR },
    { wxCMD_LINE_PARAM,  CMD_ENTRY(""),   CMD_ENTRY(""),                      CMD_ENTRY("filename(s)"),
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL | wxCMD_LINE_PARAM_MULTIPLE },
    { wxCMD_LINE_NONE }
 };

int RheiaApp::ParseCmdLine(RheiaMainFrame* handlerFrame)
{
    // code shamelessely taken from the console wxWindows sample :)
    bool filesInCmdLine = false;

    parser.SetDesc(cmdLineDesc);
    parser.SetCmdLine(argc, argv);

    switch ( parser.Parse(false) )
    {
        case -1:
            parser.Usage();
            return -1;

			case 0:
            {
                if (handlerFrame)
                {
                    int count = parser.GetParamCount();
                    filesInCmdLine = count != 0;
                    m_HasProject = false;
                    m_HasWorkSpace = false;
                    for ( int param = 0; param < count; ++param )
                    {
                        // is it a project/workspace?
                        //FileType ft = FileTypeOf(parser.GetParam(param));
                    }
                }
                else
                {
                    wxString val;
                    m_NoSplash = parser.Found(_T("no-splash-screen"));
                    m_HasDebugLog = parser.Found(_T("debug-log"));
                    m_NoCrashHandler = parser.Found(_T("no-crash-handler"));
//                    if (parser.Found(_T("personality"), &val) ||
//                        parser.Found(_T("profile"), &val))
//                    {
//                        SetupPersonality(val);
//                    }
                    parser.Found(_T("script"), &m_Script);
                    parser.Found(_T("file"), &m_AutoFile);
						  parser.Found(_T("prefix"), &m_Prefix);

//                    if(parser.Found(_T("no-log")) == false)
//                        Manager::Get()->GetLogManager()->SetLog(new TextCtrlLogger, LogManager::app_log);
//                    if(parser.Found(_T("log-to-file")))
//                        Manager::Get()->GetLogManager()->SetLog(new FileLogger(_T("codeblocks.log")), LogManager::app_log);
//                    if(m_HasDebugLog)
//                        Manager::Get()->GetLogManager()->SetLog(new TextCtrlLogger, LogManager::debug_log);
                }
            }
            break;

        default:
            return 1; // syntax error / unknown option
    }
    return filesInCmdLine ? 1 : 0;
}

bool RheiaApp::LoadConfig()
{
    if (ParseCmdLine(0L) == -1) // only abort if '--help' was passed in the command line
        return false;

    return true;
}
