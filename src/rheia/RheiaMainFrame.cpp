#include <RheiaMainFrame.h>
#include <wx/xrc/xmlres.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/dcclient.h>
#include <wx/statusbr.h>
#include <wx/msgdlg.h>
#include <wx/bmpbuttn.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <wx/dirdlg.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/imaglist.h>

#include <iostream>

#include <RheiaManager.h>
#include <RheiaAppGlobals.h>
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaPluginManager.h>
#include <RheiaMenuManager.h>
#include <RheiaEnvironementManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaApplicationConfigurationDialog.h>
#include <RheiaEnvVarsConfigurationDialog.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaWorkspaceLoader.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaLeftPaneManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaLogger.h>
#include <RheiaInfoPaneManager.h>
#include <RheiaProfileManager.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaWorkspace.h>
#include <RheiaProject.h>
#include <RheiaProjectLoader.h>
#include <RheiaProjectCreationDlg.h>
#include <RheiaProjectCreationWizard.h>
#include <RheiaGlobals.h>
#include <RheiaAppGlobals.h>
#include <RheiaInfoWindow.h>
#include <RheiaEvents.h>
#include <RheiaWizardPageBase.h>
#include <RheiaWizardManager.h>
#include <RheiaConfigurationPathsDialog.h>
#include <RheiaAboutDialog.h>
#include <RheiaException.h>
#include <RheiaPackageDBManager.h>
#include <RheiaPackageManager.h>
#include <RheiaEventsManager.h>
#include <RheiaPackageManagementDialog.h>
#include <RheiaStartPageContainer.h>

RheiaMainFrame::RheiaMainFrame(wxWindow* parent,
       wxWindowID id,
       const wxString& title,
       const wxPoint& pos,
       const wxSize& size,
       long style):
       RheiaManagedFrame(parent, id, title, pos, size, style)
{
    BuildMenu();

    /* First build the aui components */
    BuildAui();


    /* now create the info window */
    wxAuiNotebook* book = RheiaInfoPaneManager::Get(this)->CreateWindow(this);
    RheiaInfoPaneManager::Get(this)->BuildMenu( m_menuBar );

    m_layout->AddPane( book , wxAuiPaneInfo().
                            Name(wxT("InfoPane")).Caption(_("Information")).
                            BestSize(600,300).MinSize(wxSize(100,100)).//PinButton(true).Floatable(false).
                            Bottom().Layer(0));

    /* now create the info window */
    book = RheiaLeftPaneManager::Get(this)->CreateWindow(this);
    RheiaLeftPaneManager::Get(this)->BuildMenu( m_menuBar );

    m_layout->AddPane( book , wxAuiPaneInfo().
                            Name(wxT("ManagementPane")).Caption(_("Management")).
                            BestSize(300,600).MinSize(wxSize(100,100)).//PinButton(true).Floatable(false).
                            Left().Layer(1));

    /*** Now add the workspace manager to the left pane's manager */
    RheiaLeftPaneManager::Get(this)->AddPage( wxT("Workspaces") , RheiaWorkspaceManager::Get(this) );
    RheiaWorkspaceManager::Get(this)->BuildMenu( m_menuBar );

    wxToolBar* wksptb = RheiaWorkspaceManager::Get(this)->BuildToolBar(this);
    RheiaToolBarManager::Get(this)->AddToolBar(wxT("Workspaces"),wksptb);

    wxToolBar* prjtb = RheiaWorkspaceManager::Get(this)->BuildProjectsToolBar(this);
    RheiaToolBarManager::Get(this)->AddToolBar(wxT("Projects"),prjtb);

    RheiaLoggerManager::Get(this)->InitializeEnvironment();
    RheiaLoggerManager::Get(this)->BuildMenu(m_menuBar);
    RheiaLogger* log = RheiaLoggerManager::Get(this)->GetRheiaDebugLogger();
    log->Log( wxT("RheiaMainFrame::Registering Rheia Events..."), RheiaLogging::info );

    m_layout->Update();
//
    RegisterEvents();  

//    wxBitmap bmp = RheiaLoadBitmap(RheiaStandardPaths::DataDirectoryGlobal() + (_T("/share/rheia/images/rheia_24.jpg")) , wxBITMAP_TYPE_JPEG );
//    wxIcon icon;
//    icon.CopyFromBitmap( bmp );
//    SetIcon( icon );

    /* First build the status bar */
    log->Log( wxT("RheiaMainFrame::Building Rheia status bar..."), RheiaLogging::info);
    BuildStatusBar();

    /* Displays a welcome message in the status bar */
#if wxUSE_STATUSBAR
    SetStatusText(_("Welcome to Rheia !"));
#endif // wxUSE_STATUSBAR

    log->Log( wxT("RheiaMainFrame::Loading user profile..."), RheiaLogging::info);
    LoadLayout();

    log->Log( wxT("RheiaMainFrame::Initializing package data base..."), RheiaLogging::info);
    RheiaPackageDBManager::Get();
    log->Log( wxT("RheiaMainFrame::Checking for pending packages..."), RheiaLogging::info);
    RheiaPackageManager::Get()->InstallPendingPackages( true );
    log->Log( wxT("RheiaMainFrame::Loading installed plugins..."), RheiaLogging::info);
    RheiaPluginManager::Get()->LoadAllPlugins();

    RheiaPackageManager::Get()->BuildMenu( this , m_menuBar );
    log->Log( wxT("RheiaMainFrame::Initializing package data base..."), RheiaLogging::info);
    RheiaPackageDBManager::Get();
    log->Log( wxT("RheiaMainFrame::Checking for pending packages..."), RheiaLogging::info);
    RheiaPackageManager::Get()->InstallPendingPackages( true );
    log->Log( wxT("RheiaMainFrame::Loading installed plugins..."), RheiaLogging::info);
    RheiaPluginManager::Get()->LoadAllPlugins();

	RheiaStartPageContainer* m_startpage = new RheiaStartPageContainer( this, wxT("nm_test_page.html") );
	RheiaCenterPaneManager::Get(this)->AddPage( wxT("Start here") , m_startpage );
}

RheiaMainFrame::~RheiaMainFrame()
{

}
