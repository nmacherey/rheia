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

/************************************************
This is the Source File for RheiaApp

 * Author: Nicolas Macherey
 * Date: 2008.11.6
 ************************************************/

IMPLEMENT_APP(RheiaApp)

BEGIN_EVENT_TABLE(RheiaApp, wxApp)
	EVT_ACTIVATE_APP( RheiaApp::OnAppActivate )
END_EVENT_TABLE()

bool RheiaApp::OnInit(){
	
	/** Call basic initializations */
	DoBasicInitializations();

	if( !CheckForSingleInstance() )
		return false;
	
	RheiaConfigurationManager* cmgr = RheiaProfileManager::Get()->GetActiveProfileManager();
	bool showSplash = cmgr->ReadBool( wxT("show_splash") , true ) && m_noSplash;
	
	if( showSplash )
		ShowSplashScreen(RheiaStandardPaths::DataDirectoryGlobal() + wxT("/resource.zip#zip:splash_screen.png") );

	if(!LoadConfig())
		return false;

	/* Initialize resource */
	if(!InitXRCStuff())
	{
		wxMessageBox(wxT("Resources cannot be loaded properly the application will terminate immediately"),wxT("Rheia : ERROR") );
		return false;
	}

	/* Initialize the Main Frame of the application */
	MainFrame = InitMainFrame();

	/* Setting the window and showing the frame */
	SetTopWindow(MainFrame);
    MainFrame->Show();

    try
    {
        cmgr->ReadFrameInfo( wxT("/MainFrame") , MainFrame );
    }
    catch(RheiaException& err)
    {

    }
    HideSplashScreen();
	
    StartUpFinalStep();
    return true;
}

/* Membership function for initializing the main frame */
RheiaMainFrame *RheiaApp::InitMainFrame(void)
{
	RheiaMainFrame *frame = new RheiaMainFrame(NULL,
		wxID_ANY,
		wxT("Rheia"),wxDefaultPosition,wxSize(1200,600));
		
	return frame;
}

/* Parsing the command line */
bool RheiaApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    return wxApp::OnCmdLineParsed(parser);
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
    { wxCMD_LINE_SWITCH, CMD_ENTRY("ns"), CMD_ENTRY("no-splash-screen"),      CMD_ENTRY("don't display a splash screen while loading"),
      wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_NONE }
 };

int RheiaApp::ParseCmdLine(RheiaMainFrame* handlerFrame)
{
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
                }
                else
                {
                    wxString val;
                    m_noSplash = parser.Found(_T("no-splash-screen"));
                }
            }
            break;

        default:
            return 1; // syntax error / unknown option
    }
	
    return 0;
}

bool RheiaApp::LoadConfig()
{
    if (ParseCmdLine(0L) == -1) // only abort if '--help' was passed in the command line
        return false;

    return true;
}
