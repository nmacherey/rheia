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

///******************************************************************************************
//*	File Menu related id's
//******************************************************************************************/
///*! id comming from the main menu bar ressource for creating a new project*/
//int idFileWorkspaceNew = XRCID("idFileWorkspaceNew");
///*! id comming from the main menu bar ressource for opening an existing workspace */
//int idFileWorkspaceOpen = XRCID("idFileWorkspaceOpen");
///*! id comming from the main menu bar ressource for opening an existing workspace */
//int idFileWorkspaceSave = XRCID("idFileWorkspaceSave");
///*! id comming from the main menu bar ressource for opening an existing workspace */
//int idFileSaveAllWorkspaces = XRCID("idFileSaveAllWorkspaces");
///*! id for closing the current workspace from the menu */
//int idFileWorkspaceClose = XRCID("idFileWorkspaceClose");
//
///*! id for creating a new project from the menu */
//int idFileNewProject = XRCID("idFileNewProject");
///*! id for opening project from the menu */
//int idFileOpenProject = XRCID("idFileOpenProject");
///*! id for saving a project from the menu */
//int idFileProjectSave = XRCID("idFileProjectSave");
///*! id for saving a project in a new name from the menu */
//int idFileProjectSaveAs = XRCID("idFileProjectSaveAs");
///*! id for closing project from the menu */
//int idFileProjectClose = XRCID("idFileProjectClose");
//
///*! id for saving all opened files from the menu */
//int idFileSaveAll = XRCID("idFileSaveAll");
//
///*! id comming from the main menu bar ressource for exiting the application*/
//int idFileExit = XRCID("idFileExit");
//
///******************************************************************************************
//*	View Menu related id's
//******************************************************************************************/
///*! id comming from the main menu bar ressource for viewing the main tool bar */
//int idViewToolMain = XRCID("idViewToolMain");
///*! id comming from the main menu bar ressource for viewing the management window*/
//int idViewManagementWindow = XRCID("idViewManagementWindow");
///*! id comming from the main menu bar ressource for viewing the information window*/
//int idViewInformationWindow = XRCID("idViewInformationWindow");
///*! id comming from the main menu bar ressource for viewing the status bar*/
//int idViewStatusbar = XRCID("idViewStatusbar");
///*! id comming from the main menu bar ressource for viewing in full screen */
//int idViewFullScreen = XRCID("idViewFullScreen");
//
///******************************************************************************************
//*	Workspace Menu related id's
//******************************************************************************************/
//int idWorkspaceNewProject = XRCID("idWorkspaceNewProject");
//int idWorkspaceExistingProject = XRCID("idWorkspaceExistingProject");
//int idWorkspaceRename = XRCID("idWorkspaceRename");
//
///******************************************************************************************
//*	Settings Menu related id's
//******************************************************************************************/
//int idSettingsEnvConfig = XRCID("idSettingsEnvConfig");;
//int idSettingsLogMgrConfig = XRCID("idSettingsLogMgrConfig");
//int idSettingsWksMgrConfig = XRCID("idSettingsWksMgrConfig");
//int idSettingsMainWinConfig = XRCID("idSettingsMainWinConfig");
//int idSettingsManagePlugin = XRCID("idSettingsManagePlugin");
//int idSettingsEnvVarsnConfig = XRCID("idSettingsEnvVarsnConfig");
//int idSettingsConfigPaths = XRCID("idSettingsConfigPaths");
//
//BEGIN_EVENT_TABLE(RheiaMainFrame, wxFrame)
//    /* UI UPDATES RETATED EVENTS */
//    EVT_UPDATE_UI(idViewToolMain, RheiaMainFrame::OnViewMenuUpdateUI)
//    EVT_UPDATE_UI(idViewManagementWindow, RheiaMainFrame::OnViewMenuUpdateUI)
//    EVT_UPDATE_UI(idViewInformationWindow, RheiaMainFrame::OnViewMenuUpdateUI)
//    EVT_UPDATE_UI(idViewStatusbar, RheiaMainFrame::OnViewMenuUpdateUI)
//    EVT_UPDATE_UI(idViewFullScreen, RheiaMainFrame::OnViewMenuUpdateUI)
//
//    /* MAIN MENU RELATED EVENTS */
//    EVT_MENU( idFileWorkspaceNew, RheiaMainFrame::OnFileWorkspaceNew )
//    EVT_MENU( idFileWorkspaceOpen, RheiaMainFrame::OnFileWorkspaceOpen )
//    EVT_MENU( idFileWorkspaceSave, RheiaMainFrame::OnFileWorkspaceSave )
//    EVT_MENU( idFileSaveAllWorkspaces, RheiaMainFrame::OnFileWorkspaceSaveAll )
//    EVT_MENU( idFileWorkspaceClose, RheiaMainFrame::OnFileWorkspaceClose )
//
//    EVT_MENU( idFileNewProject , RheiaMainFrame::OnFileProjectNew )
//    EVT_MENU( idFileOpenProject, RheiaMainFrame::OnFileProjectOpen )
//    EVT_MENU( idFileProjectSave, RheiaMainFrame::OnFileProjectSave )
//    EVT_MENU( idFileProjectSaveAs, RheiaMainFrame::OnFileProjectSaveAs )
//    EVT_MENU( idFileProjectClose, RheiaMainFrame::OnFileProjectClose )
//
//    EVT_MENU( idFileExit, RheiaMainFrame::OnFileExit )
//
//    EVT_MENU( idViewToolMain, RheiaMainFrame::OnToggleLayoutManagerWindow )
//    EVT_MENU( idViewManagementWindow, RheiaMainFrame::OnToggleLayoutManagerWindow )
//    EVT_MENU( idViewInformationWindow, RheiaMainFrame::OnToggleLayoutManagerWindow )
//    EVT_MENU( idViewStatusbar, RheiaMainFrame::OnToggleStatusBar )
//    EVT_MENU( idViewFullScreen, RheiaMainFrame::OnToggleFullScreen )
//
//    EVT_MENU( idWorkspaceNewProject, RheiaMainFrame::OnWorkspaceNewProject )
//
//    EVT_MENU( idSettingsManagePlugin , RheiaMainFrame::OnPlugConfig )
//    EVT_MENU( idSettingsEnvConfig , RheiaMainFrame::OnAppConfig )
//    EVT_MENU( idSettingsWksMgrConfig , RheiaMainFrame::OnAppConfigWksMgr )
//    EVT_MENU( idSettingsLogMgrConfig , RheiaMainFrame::OnAppConfigLogMgr )
//    EVT_MENU( idSettingsMainWinConfig , RheiaMainFrame::OnAppConfigDocSyst )
//    EVT_MENU( idSettingsEnvVarsnConfig , RheiaMainFrame::OnManageEnvironementVariables )
//    EVT_MENU( idSettingsConfigPaths , RheiaMainFrame::OnManageConfigurationPaths )
//
//    EVT_MENU( wxID_ABOUT , RheiaMainFrame::OnAboutRheia )
//
//    /* EVENT CLOSING THE FRAME AND THE APPLICATION */
//    EVT_CLOSE( RheiaMainFrame::OnExitApp )
//END_EVENT_TABLE()
//
//RheiaMainFrame::RheiaMainFrame(wxWindow* parent,
//                               wxWindowID id,
//                               const wxString& title,
//                               const wxPoint& pos,
//                               const wxSize& size,
//                               long style): wxFrame(parent, id, title, pos, size, style),
//        LayoutManager(0)
//{
//    /* First build the aui components */
//    BuildAui();
//
//    RheiaLogger* log = RheiaLoggerManager::Get()->GetRheiaDebugLogger();
//    log->Log( wxT("RheiaMainFrame::Registering Rheia Events..."), RheiaLogging::info );
//
//    RegisterEvents();
//
////    wxBitmap bmp = RheiaLoadBitmap(RheiaStandardPaths::DataDirectoryGlobal() + (_T("/share/rheia/images/rheia_24.jpg")) , wxBITMAP_TYPE_JPEG );
////    wxIcon icon;
////    icon.CopyFromBitmap( bmp );
////    SetIcon( icon );
//
//    //SetIcon(wxICON(NumengoIcon));
//
//    /* First build the status bar */
//    log->Log( wxT("RheiaMainFrame::Building Rheia status bar..."), RheiaLogging::info);
//    BuildStatusBar();
//
//    /* Displays a welcome message in the status bar */
//#if wxUSE_STATUSBAR
//    SetStatusText(_("Welcome to Rheia !"));
//#endif // wxUSE_STATUSBAR
//    RheiaManager::Get()->GetMenuManager();
//
//    log->Log( wxT("RheiaMainFrame::Loading user profile..."), RheiaLogging::info);
//    RheiaConfigurationManager* CfgMgr = RheiaProfileManager::Get()->GetActiveProfileManager();
//    wxString LayoutName = wxT("default");
//    CfgMgr->ReadLayout( wxT("/MainFrame/LayoutManager") , LayoutManager , LayoutName );
//
//    LayoutManager->Update();
//
//    /*** init environement variables */
//    log->Log( wxT("RheiaMainFrame::Initializing environment variables..."), RheiaLogging::info);
//    RheiaEnvironementManager::Get();
//
//    log->Log( wxT("RheiaMainFrame::Initializing package data base..."), RheiaLogging::info);
//    RheiaPackageDBManager::Get();
//    log->Log( wxT("RheiaMainFrame::Checking for pending packages..."), RheiaLogging::info);
//    RheiaPackageManager::Get()->InstallPendingPackages( true );
//    log->Log( wxT("RheiaMainFrame::Loading installed plugins..."), RheiaLogging::info);
//    RheiaPluginManager::Get()->LoadAllPlugins();
//
//    CreateWorkspacePluginMenus();
//
//    log->Log( wxT("RheiaMainFrame::Finalizing initialization..."), RheiaLogging::info);
//    /* Now loading the workspace info on start-up */
//    bool blankWksp = CfgMgr->ReadBool( wxT("/environment/blank_workspace") , true );
//    if ( blankWksp )
//    {
//        RheiaWorkspace *newWksp = new RheiaWorkspace( wxEmptyString , wxT("workspace") );
//        RheiaWorkspaceManager::Get()->AddWorkspace( newWksp , wxT("workspace") );
//        RheiaStatusBarManager::Get()->SetWorkspace( wxT("workspace") );
//    }
//    else
//    {
//        RheiaWorkspaceManager::Get()->LoadLast();
//    }
//
//    log->Log( wxT("RheiaMainFrame::Recreating menus..."), RheiaLogging::info);
//    RheiaWorkspaceManager::Get()->RecreateLastMenu();
//}
//RheiaMainFrame::~RheiaMainFrame()
//{
//    //LayoutManager.UnInit();
//}
//
//void RheiaMainFrame::RegisterEvents()
//{
//    /* Register events for plugin installation and uninstallation */
//    RheiaEventsManager* pm = RheiaEventsManager::Get();
//
//    pm->RegisterEventMethod(RheiaEVT_PLUGIN_ATTACHED, new RheiaEventFunctor<RheiaMainFrame, RheiaEvent>(this, &RheiaMainFrame::OnPluginAttached));
//    pm->RegisterEventMethod(RheiaEVT_PLUGIN_RELEASED, new RheiaEventFunctor<RheiaMainFrame, RheiaEvent>(this, &RheiaMainFrame::OnPluginReleased));
//}
//
//void RheiaMainFrame::OnPluginAttached( RheiaEvent& event )
//{
//    /* Toolbar */
//    RheiaPlugin* plugin = event.GetPlugin();
//    wxString plugName = RheiaPluginManager::Get()->FindElement( plugin )->name;
//
//    //RheiaNameSpaceViewManager::Get()->AssociatePlugin( plugin->GetNamespaceView() , plugName, plugin );
//}
//void RheiaMainFrame::OnPluginReleased( RheiaEvent& event )
//{
//    /* Toolbar */
//    RheiaPlugin* plugin = event.GetPlugin();
//    wxString plugName = RheiaPluginManager::Get()->FindElement( plugin )->name;
//
//    //RheiaNameSpaceViewManager::Get()->RemovePlugin( plugin->GetNamespaceView() , plugName );
//}
//
//void RheiaMainFrame::RecreateMenuBar()
//{
////    Freeze();
////    RheiaMenuManager::Get()->RecreateMenuBar();
////    Thaw();
//}
///**********************************************************************************************************
//											METHODS
//**********************************************************************************************************/
///* Creates the main frame's status bar */
//void RheiaMainFrame::BuildStatusBar()
//{
//#if wxUSE_STATUSBAR
//    wxCoord width[16]; // 16 max
//
//    wxClientDC dc(this);
//    wxFont font = dc.GetFont();
//    int h;
//    int num = 0;
//
//    width[num++] = -1; // main field
//    dc.GetTextExtent(_(" WORKSPACE-1234567812345678 "), &width[num++], &h);
//    dc.GetTextExtent(_(" PROJECT-1234567812345678 "), &width[num++], &h);
//    dc.GetTextExtent(_(" EXPERIMENT-1234567812345678 "),  &width[num++], &h);
//
//    CreateStatusBar(num);
//    SetStatusWidths(num, width);
//
//    RheiaStatusBarManager::Get()->Update();
//
//#endif // wxUSE_STATUSBAR
//}
///* Updates the status bar */
//void RheiaMainFrame::updateStatusBar()
//{
//#if wxUSE_STATUSBAR
//    if (!GetStatusBar())
//        return;
//
//    int panel = 0;
//    SetStatusText(_("Welcome to Rheia !"), panel++);
//    SetStatusText(wxEmptyString, panel++);
//    SetStatusText(wxEmptyString, panel++);
//    SetStatusText(wxEmptyString, panel++);
//
//    RheiaStatusBarManager::Get()->Update();
//
//#endif // wxUSE_STATUSBAR
//}
//
///**********************************************************************************************************
//									PRIVATE METHODS ABOUT THE FRAME INIT
//**********************************************************************************************************/
///* Creates the default frame controls and initialise the different managers info and books */
//void RheiaMainFrame::BuildAui(void)
//{
//    wxSize clientsize = GetClientSize();
//
//    RheiaManager::Get(this);
//
//    LayoutManager = RheiaManager::Get()->GetLayoutManager();
//
//    LayoutManager->AddPane( RheiaManager::Get()->GetWorkspaceManager()->GetNoteBook() , wxAuiPaneInfo().
//                            Name(wxT("ManagementPane")).Caption(_("Management")).
//                            BestSize(wxSize(200, clientsize.GetHeight())).//MinSize(wxSize(100,100)).
//                            Left().Layer(1));
//
//    LayoutManager->AddPane( RheiaManager::Get()->GetCenterPaneManager()->GetNoteBook() , wxAuiPaneInfo().
//                            Name(wxT("MainPane")).Caption(_("MainBook")).
//                            BestSize(wxSize(200, clientsize.GetHeight())).//MinSize(wxSize(100,100)).
//                            CenterPane());
//
//    RheiaInfoPaneManager::Get();
//    RheiaLoggerManager::Get()->InitializeEnvironment();
//
//    LayoutManager->AddPane( RheiaInfoPaneManager::Get()->GetNoteBook() , wxAuiPaneInfo().
//                            Name(wxT("InfoPane")).Caption(_("Information")).
//                            BestSize(200,200).MinSize(wxSize(100,100)).//PinButton(true).Floatable(false).
//                            Bottom().Layer(0));
//
//    CreateToolBars();
//    SetToolBar(0);
//
//    LayoutManager->SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_DRAG);
//
//    DoUpdateManagerColours();
//    LayoutManager->Update();
//}
//
///**********************************************************************************************************
//									MENU CALLBACKS
//**********************************************************************************************************/
///* Used when we want to set the fullscreen mode */
//void RheiaMainFrame::OnToggleFullScreen( wxCommandEvent &event )
//{
//    ShowFullScreen( !IsFullScreen(), wxFULLSCREEN_NOTOOLBAR// | wxFULLSCREEN_NOSTATUSBAR
//                    | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION );
//}
//
///* Used when we want to view/hide the status bar */
//void RheiaMainFrame::OnToggleStatusBar( wxCommandEvent &event )
//{
//    wxStatusBar* sb = GetStatusBar();
//    if (sb)
//    {
//        sb->Hide();
//        SetStatusBar(0);
//        sb->Destroy();
//    }
//    else
//        BuildStatusBar();
//
//    updateStatusBar();
//}
//
///* Used when we want to view/hide the management window */
//void RheiaMainFrame::OnToggleLayoutManagerWindow( wxCommandEvent &event )
//{
//    wxWindow* win = 0;
//    if (event.GetId() == idViewManagementWindow)
//        win = RheiaManager::Get()->GetWorkspaceManager()->GetNoteBook();
//    else if (event.GetId() == idViewInformationWindow)
//        win = RheiaInfoPaneManager::Get()->GetNoteBook();
//    else if (event.GetId() == idViewToolMain)
//        win = ToolBar;
//    /*else
//    {
//        wxString pluginName = m_PluginIDsMap[event.GetId()];
//        if (!pluginName.IsEmpty())
//        {
//            cbPlugin* plugin = Manager::Get()->GetPluginManager()->FindPluginByName(pluginName);
//            if (plugin)
//                win = m_PluginsTools[plugin];
//        }
//    }*/
//
//    if (win)
//    {
//        LayoutManager->GetPane(win).Show(event.IsChecked());
//        LayoutManager->Update();
//    }
//}
//
///* Used when we act on the view menu */
//void RheiaMainFrame::OnViewMenuUpdateUI( wxUpdateUIEvent& event )
//{
//    if (RheiaManager::isappShuttingDown())
//    {
//        event.Skip();
//        return;
//    }
//
//    wxMenuBar* mbar = GetMenuBar();
//
//    mbar->Check(idViewManagementWindow, LayoutManager->GetPane(RheiaManager::Get()->GetWorkspaceManager()->GetNoteBook()).IsShown() );
//    mbar->Check(idViewInformationWindow, LayoutManager->GetPane(RheiaInfoPaneManager::Get()->GetNoteBook()).IsShown() );
//    mbar->Check(idViewStatusbar, GetStatusBar() && GetStatusBar()->IsShown());
//    mbar->Check(idViewFullScreen, IsFullScreen());
//
//    // toolbars
//    mbar->Check(idViewToolMain, LayoutManager->GetPane(ToolBar).IsShown());
//
//    /* Now Checking plugin items */
//
//
//    event.Skip();
//}
//
///* Used when we act on the file menu new workspace item */
//void RheiaMainFrame::OnFileWorkspaceNew( wxCommandEvent &event )
//{
//    wxString path = wxEmptyString;
//    wxString name = wxGetTextFromUser( wxT("Enter the name of your new workspace : ") , wxT("New workspace name") , wxT("workspace") );
//
//    if ( name.IsEmpty() )
//        return;
//
//    while ( RheiaWorkspaceManager::Get()->Exists( name ) )
//    {
//        name = wxGetTextFromUser( wxT("Workspace exists please select a different name for your new workspace : ") , wxT("New workspace name") , name );
//        if ( name.IsEmpty() )
//            return;
//    }
//
//    int retId = wxMessageBox( wxT("Would you like to save your workspace first ?") , wxT("Request for workspace file...") , wxYES_NO );
//
//    if ( retId == wxYES )
//    {
//        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_workspace_path") , RheiaStandardPaths::HomeDirectory() );
//
//        wxFileDialog dialog( this,
//                             wxT("Select the workspace files you want to load..."),
//                             LastOpenPath,
//                             name + FileExt::WKSP_EXT,
//                             FileExt::WKSP_EXT_FILE,
//                             wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
//
//        if ( dialog.ShowModal() == wxID_OK )
//        {
//            path = dialog.GetPath();
//            wxFileName lastPath( path );
//            RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_workspace_path") , lastPath.GetPath() );
//        }
//    }
//
//    RheiaWorkspace *newWksp = new RheiaWorkspace( path , name );
//
//    RheiaWorkspaceManager::Get()->AddWorkspace( newWksp , name );
//
//    if ( !path.IsEmpty() )
//    {
//        RheiaWorkspaceManager::Get()->SaveWorkspace( newWksp );
//        RheiaWorkspaceManager::Get()->SetLast( path );
//        RheiaWorkspaceManager::Get()->AddLast( path );
//    }
//
//    RheiaStatusBarManager::Get()->SetWorkspace( name );
//}
//
///* Used when we act on the file menu new workspace item */
//void RheiaMainFrame::OnFileWorkspaceOpen( wxCommandEvent &event )
//{
//
//    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_workspace_path") , RheiaStandardPaths::HomeDirectory() );
//
//    wxFileDialog dialog( this,
//                         wxT("Select the workspace files you want to load..."),
//                         LastOpenPath,
//                         wxEmptyString,
//                         FileExt::WKSP_EXT_FILE,
//                         wxFD_OPEN | wxFD_MULTIPLE );
//
//    if ( dialog.ShowModal() != wxID_OK )
//    {
//        return;
//    }
//
//    wxArrayString filepaths;
//    dialog.GetPaths(filepaths);
//
//    wxFileName lastPath( filepaths[0] );
//    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_workspace_path") , lastPath.GetPath() );
//
//    for ( unsigned int i = 0; i < filepaths.size() ; i++ )
//    {
//        RheiaWorkspace* LoadedWorkspace = 0L;
//        /* Now just realese the last selected workspace menu */
//        bool load = true;
//        RheiaWorkspaceTable WorkspaceTable = RheiaWorkspaceManager::Get()->GetWorkspaceTable();
//        if ( WorkspaceTable.size() > 0 )
//        {
//            RheiaWorkspaceTable::iterator iter = WorkspaceTable.begin();
//            for ( iter ; iter != WorkspaceTable.end() ; iter++ )
//            {
//                wxFileName tested( iter->second->GetFileName() );
//                wxFileName local( filepaths[i] );
//
//                wxString dum1 = tested.GetPath() + wxT("/") + tested.GetFullName();
//                wxString dum2 = local.GetPath() + wxT("/") + local.GetFullName();
//
//                if ( dum1.IsSameAs( dum2 ) )
//                {
//                    load = false;
//                    break;
//                }
//            }
//        }
//
//        if ( load )
//        {
//            LoadedWorkspace = RheiaWorkspaceManager::Get()->LoadWorkspace( filepaths[i] );
//            if ( LoadedWorkspace == NULL )
//            {
//                wxMessageBox(wxT("Cannot Load the workspace : \n") + filepaths[i] , wxT("Alert") );
//                return;
//            }
//        }
//    }
//}
//
///* Used when we act on the file menu new workspace item */
//void RheiaMainFrame::OnAppConfig( wxCommandEvent &event )
//{
//    RheiaApplicationConfigurationDialog dlg(this );
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        DoUpdateManagerColours();
//    }
//}
//
///* Used when we act on the file menu new workspace item */
//void RheiaMainFrame::OnAppConfigLangAndFunc( wxCommandEvent &event )
//{
//    RheiaApplicationConfigurationDialog dlg(this );
//    dlg.SetPageSelection( wxT("Languages & Functionalities") );
//
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        DoUpdateManagerColours();
//    }
//}
//
///* Used when we act on the file menu new workspace item */
//void RheiaMainFrame::OnPlugConfig( wxCommandEvent &event )
//{
//    RheiaPackageManagementDialog dlg(this );
//    if (dlg.ShowModal() == wxID_OK)
//    {
//
//    }
//}
//
//void RheiaMainFrame::OnAppConfigMsgMgr( wxCommandEvent &event )
//{
//    RheiaApplicationConfigurationDialog dlg(this );
//    dlg.SetPageSelection( wxT("Message Manager Appearance") );
//
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        DoUpdateManagerColours();
//    }
//}
//
//void RheiaMainFrame::OnAppConfigLogMgr( wxCommandEvent &event )
//{
//    RheiaApplicationConfigurationDialog dlg(this);
//    dlg.SetPageSelection( wxT("Information Window Appearance") );
//
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        DoUpdateManagerColours();
//    }
//}
//
//void RheiaMainFrame::OnAppConfigWksMgr( wxCommandEvent &event )
//{
//    RheiaApplicationConfigurationDialog dlg(this);
//    dlg.SetPageSelection( wxT("Workspace Manager Appearance") );
//
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        DoUpdateManagerColours();
//    }
//}
//
//void RheiaMainFrame::OnAppConfigDocSyst( wxCommandEvent &event )
//{
//    RheiaApplicationConfigurationDialog dlg(this );
//    dlg.SetPageSelection( wxT("Docking system") );
//
//    if (dlg.ShowModal() == wxID_OK)
//    {
//        DoUpdateManagerColours();
//    }
//}
//
//void RheiaMainFrame::OnManageEnvironementVariables( wxCommandEvent &event )
//{
//    RheiaEnvVarsConfigurationDialog dialog( this );
//    dialog.ShowModal();
//}
//
//void RheiaMainFrame::OnManageConfigurationPaths( wxCommandEvent &event )
//{
//    RheiaConfigurationPathsDialog dialog( this );
//    dialog.ShowModal();
//}
//
///* Used when we act on the file menu new workspace item */
//void RheiaMainFrame::OnFileWorkspaceSave( wxCommandEvent &event )
//{
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//    if ( !workspace )
//        return;
//
//    if ( workspace->HasBeenModified() )
//    {
//        RheiaWorkspaceManager::Get()->SaveWorkspace( workspace );
//        SetStatusText( wxT("Workspace : ") + workspace->GetName() + wxT(" saved !") );
//    }
//    else
//        SetStatusText( wxT("Workspace : ") + workspace->GetName() + wxT(" already saved !") );
//}
//
///* Used when we act on the file menu save all workspace item */
//void RheiaMainFrame::OnFileWorkspaceSaveAll( wxCommandEvent &event )
//{
//    RheiaWorkspaceTable table = RheiaWorkspaceManager::Get()->GetWorkspaceTable();
//    RheiaWorkspaceTable::iterator iter = table.begin();
//    wxString SavedWksp;
//
//    if ( table.size() > 0 )
//    {
//        for ( iter ; iter != table.end() ; iter++ )
//        {
//            if ( iter->second->HasBeenModified() )
//            {
//                RheiaWorkspaceManager::Get()->SaveWorkspace( iter->second );
//                SavedWksp = SavedWksp + iter->second->GetName() + wxT(",");
//                iter->second->SetHasBeenModified(false);
//            }
//        }
//        if ( SavedWksp.IsEmpty() )
//            SetStatusText( wxT("All workspaces already saved !") );
//        else
//            SetStatusText( wxT("Workspaces : ") + SavedWksp + wxT(" saved !") );
//    }
//}
//
//void RheiaMainFrame::OnFileWorkspaceClose( wxCommandEvent &event )
//{
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//    if ( !workspace )
//        return;
//
//    this->Freeze();
//
//    if ( workspace->HasBeenModified() )
//    {
//        int retId = wxMessageBox( wxT("The workspace has changed do you want to save it ?") , wxT("Alert") , wxYES | wxNO | wxCANCEL | wxCENTER );
//
//        if ( retId == wxYES )
//        {
//            RheiaWorkspaceManager::Get()->SaveWorkspace( workspace );
//            workspace->SetHasBeenModified(false);
//        }
//        else if ( retId == wxCANCEL )
//        {
//            this->Thaw();
//            return;
//        }
//    }
//
//    RheiaWorkspaceManager::Get()->RemoveWorkspace( workspace->GetName() );
//    this->Thaw();
//}
//
///* Callback called when requesting the exit of the application, generates an EVT_CLOSE in order to centralize with
//other close controls */
//void RheiaMainFrame::OnFileExit( wxCommandEvent& event )
//{
//    Close(true);
//}
//
///* Used when we close the frame */
//void RheiaMainFrame::OnExitApp( wxCloseEvent &event )
//{
//    RheiaEvent evt(RheiaEVT_APP_START_SHUTDOWN);
//    RheiaEventsManager::Get()->ProcessEvent( evt );
//
//    RheiaConfigurationManager* CfgMgr = RheiaProfileManager::Get()->GetActiveProfileManager();
//
//    try
//    {
//        CfgMgr->WriteFrameInfo( wxT("/MainFrame") , this );
//    }
//    catch( RheiaException& err )
//    {
//        err.ShowErrorMessage();
//    }
//
//    wxAuiManager* LayoutMgr = RheiaManager::Get()->GetLayoutManager();
//
//    wxArrayString LayoutVal;
//    LayoutVal.Add( LayoutMgr->SavePerspective() );
//
//    wxArrayString LayoutName;
//    LayoutName.Add( wxT("default" ) );
//
//    CfgMgr->WriteLayout( wxT("/MainFrame/LayoutManager") , LayoutMgr,  LayoutName , LayoutVal );
//
//    /* Check for unsaved workspaces */
//    RheiaWorkspaceTable table = RheiaWorkspaceManager::Get()->GetWorkspaceTable();
//    RheiaWorkspaceTable::iterator iter = table.begin();
//
//    if ( table.size() > 0 )
//    {
//        for ( iter ; iter != table.end() ; iter++ )
//        {
//            if ( iter->second->HasBeenModified() )
//            {
//                wxMessageDialog dialog( this, wxT("Workspace : ") + iter->first + wxT(" not saved would you like to save it ?"),
//                                        wxT("Save ") + iter->first + wxT("?") , wxYES | wxNO | wxCANCEL | wxCENTRE );
//
//                int ret = dialog.ShowModal();
//                if ( ret == wxID_YES )
//                    RheiaWorkspaceManager::Get()->SaveWorkspace( iter->second );
//                else if( ret == wxID_CANCEL )
//                {
//                    event.Veto();
//                    return;
//                }
//            }
//        }
//    }
//    RheiaManager::Get()->Close();
//    Destroy();
//}
//
///* This function is used for creating the main tool bar and the different plugin's toolbars */
//void RheiaMainFrame::CreateToolBars(void)
//{
//    if (ToolBar)
//    {
//        SetToolBar(0L);
//        ToolBar = 0L;
//    }
//
//    ToolBar = RheiaManager::Get()->GetToolBarManager()->GetToolBar();
//
////    // add toolbars in docking system
//    LayoutManager->AddPane(ToolBar, wxAuiPaneInfo().
//                           Name(wxT("MainToolbar")).
//                           ToolbarPane().Top().Layer(1));
//
//    LayoutManager->Update();
//}
//
//void RheiaMainFrame::OnWorkspaceNewProject( wxCommandEvent &event )
//{
//    /* First Find the currently selected workspace */
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//
//    if ( !workspace )
//    {
//        wxMessageBox( wxT("Please Create a workspace first") , wxT("Rheia : Alert") );
//        return;
//    }
////
////    RheiaEnvironmentPlugin *owner = workspace->GetOwner();
////    owner->RunProjectWizard( workspace );
//}
//
//void RheiaMainFrame::CreateWorkspacePluginMenus()
//{
////    RheiaPluginRegistrationTable WkspPlugs = RheiaPluginManager::Get()->GetPlugins( RhEnvironment );
////    for ( unsigned int i = 0 ; i < WkspPlugs.size() ; i++ )
////    {
////        WkspPlugs[i]->plugin->BuildMenu( RheiaMenuManager::Get()->GetMainMenuBar() );
////    }
//}
//
//void RheiaMainFrame::OnFileProjectNew( wxCommandEvent &event )
//{
//    /* First Find the currently selected workspace */
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//
//    if ( !workspace )
//    {
//        wxMessageBox( wxT("Please Create a workspace first") , wxT("Rheia : Alert") );
//        return;
//    }
//
//    RheiaWizardManager::Get()->DoCreateNewProject( workspace );
//}
//
//void RheiaMainFrame::OnFileProjectOpen( wxCommandEvent &event )
//{
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//
//    if ( !workspace )
//    {
//        wxMessageBox( wxT("Please Create a workspace first") , wxT("Rheia : Alert") );
//        return;
//    }
//
//    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );
//
//    wxFileDialog dialog( this,
//                         wxT("Select the workspace files you want to load..."),
//                         LastOpenPath,
//                         wxEmptyString,
//                         FileExt::PRJ_EXT_FILE,
//                         wxFD_OPEN | wxFD_MULTIPLE );
//
//    if ( dialog.ShowModal() != wxID_OK )
//    {
//        return;
//    }
//
//    wxArrayString filepaths;
//    dialog.GetPaths(filepaths);
//
//    wxFileName lastPath( filepaths[0] );
//    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
//
//    for ( unsigned int i = 0; i < filepaths.size() ; i++ )
//    {
//        RheiaProject* loadedProject = NULL;
//        RheiaProjectLoader loader;
//
//        if ( !loader.Open( filepaths[i] , workspace ) )
//        {
//            InfoWindow::Display( wxT("WARNING") , wxT("Cannot load the document : ") + filepaths[i] );
//        }
//        else
//        {
//            loadedProject = loader.GetProject();
//            workspace->AddProject( loadedProject->GetName() , loadedProject );
//
//            RheiaProjectEvent evt(RheiaEVT_PROJECT_OPENED,
//                    0,
//                    loadedProject->GetEnvironement(),
//                    workspace,
//                    loadedProject,
//                    loadedProject->GetName()
//                    );
//
//            RheiaEventsManager::Get()->ProcessEvent(evt);
//        }
//    }
//
//    workspace->UpdateManagementTree( RheiaWorkspaceManager::Get()->GetManagementTree() ,
//                                     RheiaWorkspaceManager::Get()->GetManagementTreeRoot() );
//}
//
//void RheiaMainFrame::OnFileProjectSave( wxCommandEvent &event )
//{
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//
//    if ( !workspace )
//        return;
//
//    wxString prjname = workspace->GetCurrentProject();
//    RheiaProject* project = workspace->FindProjectByName( prjname );
//
//    if ( project == NULL )
//        return;
//
//    if ( !project->HasBeenModified() )
//        return;
//
//    wxString prjpath = project->GetFileName();
//
//    if( prjpath.IsEmpty() )
//    {
//        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );
//
//        wxFileDialog dialog( this,
//                         wxT("Select project path files you want to save..."),
//                         LastOpenPath,
//                         wxEmptyString,
//                         FileExt::PRJ_EXT_FILE,
//                         wxFD_SAVE );
//
//        if ( dialog.ShowModal() != wxID_OK )
//        {
//            return;
//        }
//
//        prjpath = dialog.GetPath();
//        wxFileName lastPath( prjpath );
//        RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
//
//        project->SetFileName( prjpath );
//    }
//
//    RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//    RheiaEventsManager::Get()->ProcessEvent(evt);
//
//    RheiaProjectLoader loader( project );
//    if( !loader.Save( prjpath ) )
//        return;
//
//    RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//    RheiaEventsManager::Get()->ProcessEvent(evt2);
//
//}
//
//void RheiaMainFrame::OnFileProjectSaveAs( wxCommandEvent &event )
//{
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//
//    if ( !workspace )
//        return;
//
//    wxString prjname = workspace->GetCurrentProject();
//    RheiaProject* project = workspace->FindProjectByName( prjname );
//
//    if ( project == NULL )
//        return;
//
//    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );
//
//    wxFileDialog dialog( this,
//                     wxT("Select project path files you want to save..."),
//                     LastOpenPath,
//                     wxEmptyString,
//                     FileExt::PRJ_EXT_FILE,
//                     wxFD_SAVE );
//
//    if ( dialog.ShowModal() != wxID_OK )
//    {
//        return;
//    }
//
//    wxString prjpath = dialog.GetPath();
//    wxFileName lastPath( prjpath );
//    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
//
//    project->SetFileName( prjpath );
//
//    RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//    RheiaEventsManager::Get()->ProcessEvent(evt);
//
//    RheiaProjectLoader loader( project );
//    if( !loader.Save( prjpath ) )
//        return;
//
//    RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//    RheiaEventsManager::Get()->ProcessEvent(evt2);
//}
//
//void RheiaMainFrame::OnFileProjectClose( wxCommandEvent &event )
//{
//    RheiaWorkspace *workspace = RheiaWorkspaceManager::Get()->FindWorkspace( RheiaWorkspaceManager::Get()->GetCurrentSelectedWorkspace() );
//
//    if ( !workspace )
//        return;
//
//    wxString prjname = workspace->GetCurrentProject();
//    RheiaProject* project = workspace->FindProjectByName( prjname );
//
//    if ( project == NULL )
//        return;
//
//    RheiaProjectEvent evt(RheiaEVT_PROJECT_CLOSING,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//    RheiaEventsManager::Get()->ProcessEvent(evt);
//    RheiaEnvironmentPlugin *env = project->GetEnvironement();
//
//    if ( project->HasBeenModified() )
//    {
//        int retcode = wxMessageBox( wxT("The project : ") + prjname + wxT(" has not been saved, would you like to save it?") ,
//            wxT("Alert") , wxYES | wxNO |wxCANCEL | wxCENTER );
//
//        if( retcode == wxCANCEL )
//            return;
//        else if( retcode == wxYES )
//        {
//            wxString prjpath = project->GetFileName();
//
//            if( prjpath.IsEmpty() )
//            {
//                wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );
//
//                wxFileDialog dialog( this,
//                                 wxT("Select project path files you want to save..."),
//                                 LastOpenPath,
//                                 wxEmptyString,
//                                 FileExt::PRJ_EXT_FILE,
//                                 wxFD_SAVE );
//
//                if ( dialog.ShowModal() != wxID_OK )
//                {
//                    return;
//                }
//
//                prjpath = dialog.GetPath();
//                wxFileName lastPath( prjpath );
//                RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
//            }
//            RheiaProjectLoader loader( project );
//
//            RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//            RheiaEventsManager::Get()->ProcessEvent(evt);
//
//            loader.Save( prjpath );
//
//            RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
//                    0,
//                    project->GetEnvironement(),
//                    workspace,
//                    project,
//                    project->GetName()
//                    );
//
//            RheiaEventsManager::Get()->ProcessEvent(evt2);
//        }
//    }
//
//    workspace->RemoveProject( prjname );
//    workspace->UpdateManagementTree( RheiaWorkspaceManager::Get()->GetManagementTree() ,
//                                     RheiaWorkspaceManager::Get()->GetManagementTreeRoot() );
//    workspace->SetHasBeenModified( true );
//
//    RheiaProjectEvent evt2(RheiaEVT_PROJECT_CLOSED,
//                    0,
//                    env,
//                    workspace,
//                    NULL,
//                    prjname
//                    );
//
//    RheiaEventsManager::Get()->ProcessEvent(evt2);
//}
//
//void RheiaMainFrame::DoUpdateManagerColours()
//{
//    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();
//    wxAuiDockArt* art = LayoutManager->GetArtProvider();
//
//    LayoutManager->SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_DRAG);
//    art->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE,   cfg->ReadInt(_T("/environment/aui/border_size"), art->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE)));
//    art->SetMetric(wxAUI_DOCKART_SASH_SIZE,          cfg->ReadInt(_T("/environment/aui/sash_size"), art->GetMetric(wxAUI_DOCKART_SASH_SIZE)));
//    art->SetMetric(wxAUI_DOCKART_CAPTION_SIZE,       cfg->ReadInt(_T("/environment/aui/caption_size"), art->GetMetric(wxAUI_DOCKART_CAPTION_SIZE)));
//    art->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR,              cfg->ReadColour(_T("/environment/aui/active_caption_colour"), art->GetColour(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR)));
//    art->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR,     cfg->ReadColour(_T("/environment/aui/active_caption_gradient_colour"), art->GetColour(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR)));
//    art->SetColour(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR,         cfg->ReadColour(_T("/environment/aui/active_caption_text_colour"), art->GetColour(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR)));
//    art->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR,            cfg->ReadColour(_T("/environment/aui/inactive_caption_colour"), art->GetColour(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR)));
//    art->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR,   cfg->ReadColour(_T("/environment/aui/inactive_caption_gradient_colour"), art->GetColour(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR)));
//    art->SetColour(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR,       cfg->ReadColour(_T("/environment/aui/inactive_caption_text_colour"), art->GetColour(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR)));
//
//    LayoutManager->Update();
//}
//
//void RheiaMainFrame::OnAboutRheia( wxCommandEvent& event )
//{
//    RheiaAboutDialog dialog( this );
//    dialog.ShowModal();
//}


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

    //SetIcon(wxICON(NumengoIcon));

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


}

RheiaMainFrame::~RheiaMainFrame()
{

}
