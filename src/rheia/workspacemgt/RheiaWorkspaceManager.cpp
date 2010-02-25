#include <RheiaWorkspaceManager.h>
#include <RheiaWorkspaceLoader.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaMenuManager.h>
#include <RheiaWorkspace.h>
#include <RheiaWizardManager.h>
#include <RheiaProject.h>
#include <RheiaAppGlobals.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaTreeItemData.h>
#include <RheiaInfoWindow.h>
#include <RheiaProject.h>
#include <RheiaStatusBarManager.h>
#include <RheiaPlatform.h>
#include <RheiaProjectConfigurationDlg.h>
#include <RheiaProjectLoader.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaEventFrame.h>
#include <RheiaException.h>
#include <RheiaEventProject.h>
#include <RheiaEventWorkspace.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaConfigurationDialog.h>
#include <RheiaWkspMgrSettingsPanel.h>

#include <wx/aui/aui.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/choice.h>
#include <wx/xrc/xmlres.h>
#include <wx/toolbar.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <wx/menu.h>
#include <wx/log.h>
#include <wx/toolbar.h>

#include <iostream>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaWorkspaceManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaWorkspaceManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaWorkspaceManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaWorkspaceManager>::m_ns = locmap;

/*! Id of the management tree */
int m_treeId = wxNewId();

int DefaultHistoryLength = 10;

int idLastWksp[] = {
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId()
    };

int idLastPrj[] = {
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId(),
    wxNewId()
    };

namespace
{
    /*! id comming from the main menu bar ressource for creating a new project*/
    int idFileWorkspaceNew = XRCID("idFileWorkspaceNew");
    /*! id comming from the main menu bar ressource for opening an existing workspace */
    int idFileWorkspaceOpen = XRCID("idFileWorkspaceOpen");
    /*! id comming from the main menu bar ressource for opening an existing workspace */
    int idFileWorkspaceSave = XRCID("idFileWorkspaceSave");
    int idFileWorkspaceSaveAs = wxNewId();
    /*! id comming from the main menu bar ressource for opening an existing workspace */
    int idFileSaveAllWorkspaces = XRCID("idFileSaveAllWorkspaces");
    /*! id for closing the current workspace from the menu */
    int idFileWorkspaceClose = wxNewId();

    /*! id for creating a new project from the menu */
    int idFileNewProject = XRCID("idFileNewProject");
    /*! id for opening project from the menu */
    int idFileOpenProject = XRCID("idFileOpenProject");
    /*! id for saving a project from the menu */
    int idFileProjectSave = XRCID("idFileProjectSave");
    /*! id for saving a project in a new name from the menu */
    int idFileProjectSaveAs = wxNewId();
    /*! id for closing project from the menu */
    int idFileProjectClose = wxNewId();

    /*! id for saving all opened files from the menu */
    int idFileSaveAll = wxNewId();

    /*! id for configuring the workspace manager */
    int menuId = wxNewId();
}

BEGIN_EVENT_TABLE(RheiaWorkspaceManager,wxEvtHandler)
    EVT_TREE_SEL_CHANGED( m_treeId , RheiaWorkspaceManager::OnManagementTreeSelection )
    EVT_TREE_ITEM_ACTIVATED( m_treeId , RheiaWorkspaceManager::OnManagementTreeDClick )

    EVT_MENU( idLastWksp[0] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[1] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[2] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[3] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[4] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[5] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[6] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[7] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[8] , RheiaWorkspaceManager::OnRecentOpen )
    EVT_MENU( idLastWksp[9] , RheiaWorkspaceManager::OnRecentOpen )

    /* MAIN MENU RELATED EVENTS */
    EVT_MENU( idFileWorkspaceNew, RheiaWorkspaceManager::OnFileWorkspaceNew )
    EVT_MENU( idFileWorkspaceOpen, RheiaWorkspaceManager::OnFileWorkspaceOpen )
    EVT_MENU( idFileWorkspaceSave, RheiaWorkspaceManager::OnFileWorkspaceSave )
    EVT_MENU( idFileSaveAllWorkspaces, RheiaWorkspaceManager::OnFileWorkspaceSaveAll )
    EVT_MENU( idFileWorkspaceClose, RheiaWorkspaceManager::OnFileWorkspaceClose )

    EVT_MENU( idFileNewProject , RheiaWorkspaceManager::OnFileProjectNew )
    EVT_MENU( idFileOpenProject, RheiaWorkspaceManager::OnFileProjectOpen )
    EVT_MENU( idFileProjectSave, RheiaWorkspaceManager::OnFileProjectSave )
    EVT_MENU( idFileProjectSaveAs, RheiaWorkspaceManager::OnFileProjectSaveAs )
    EVT_MENU( idFileProjectClose, RheiaWorkspaceManager::OnFileProjectClose )

    EVT_MENU( menuId, RheiaWorkspaceManager::OnConfigure )

    //EVT_FRAME_CLOSING( RheiaWorkspaceManager::OnCloseParent )
END_EVENT_TABLE()

/**********************************************************************************************************
*	CONSTRUCTORS
**********************************************************************************************************/
RheiaWorkspaceManager::RheiaWorkspaceManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_tree(NULL),
    m_parent(parent)
{
    m_parent->PushEventHandler(this);
	m_parent->Connect( RheiaEVT_FRAME_CLOSING , RheiaFrameEventHandler(RheiaWorkspaceManager::OnCloseParent) , NULL , this );
    RegisterEvents();
}

RheiaBookPage* RheiaWorkspaceManager::BuildMainWindow( wxWindow* parent )
{
    RheiaWorkspaceBookPage* page = new RheiaWorkspaceBookPage(parent,this);

    m_tree = new wxTreeCtrl( page , m_treeId,
                                     wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTR_HAS_BUTTONS | wxTR_HIDE_ROOT | wxTR_SINGLE | wxTR_LINES_AT_ROOT );

    page->m_sizer->Add( m_tree , 1 , wxALL | wxEXPAND );
    page->SetSizer(page->m_sizer);

    m_treeRoot = m_tree->AddRoot( wxT("Home") );
    m_treeImages = new wxImageList( 16 , 16 , true );
    m_tree->SetImageList( m_treeImages );

    ReloadConfig();
    ReloadWorkspaceTree();

    return page;
}

void RheiaWorkspaceManager::ReloadConfig()
{
    if( !m_tree )
        RheiaThrow( wxT("RheiaWorkspaceManager::Error::ReloadConfig call Create Window with the proper window first") );

    // Set user profile book configuration
    RheiaConfigurationManager *wcfg = RheiaManager::Get()->GetConfigurationManager(_T("workspace_manager"));
    // Set user profile tree configuration

    long treeStyle = wxNO_BORDER | wxTR_EDIT_LABELS | wxTR_HIDE_ROOT |  wxTR_SINGLE;

    treeStyle = treeStyle |  ( (wcfg->ReadBool(_T("/tree_ctrl/has_buttons"), true) ) ? wxTR_HAS_BUTTONS : wxTR_NO_BUTTONS ) ;
    treeStyle = treeStyle |  ( (wcfg->ReadBool(_T("/tree_ctrl/has_lines"), true) ) ? 0 : wxTR_NO_LINES ) ;
    treeStyle = treeStyle |  ( (wcfg->ReadBool(_T("/tree_ctrl/has_lines_at_root"), true) ) ? wxTR_LINES_AT_ROOT : 0 ) ;
    treeStyle = treeStyle |  ( (wcfg->ReadBool(_T("/tree_ctrl/has_row_lines"), false) ) ? wxTR_ROW_LINES : 0 ) ;

    m_tree->SetWindowStyle( treeStyle );

    /* */
    m_LastFiles = wcfg->ReadArrayString( wxT("/recent_workspaces" ) );
    m_Last = wcfg->Read( wxT("/last_workspace") );
    m_HistoryLength = DefaultHistoryLength;
}

void RheiaWorkspaceManager::ReloadWorkspaceTree()
{

}

const wxBitmap& RheiaWorkspaceManager::GetBitmap( const int& size )
{
    wxString fPath = RheiaStandardPaths::DataDirectoryGlobal() + wxString::Format( wxT("/resource.zip#zip:workspace_%d.png") , size );
    m_bmp = RheiaLoadBitmap( fPath );

    return m_bmp;
}

void RheiaWorkspaceManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_WKSPMGR_SETTINGS_CHANGED, new RheiaEventFunctor<RheiaWorkspaceManager>(this, wxCommandEventHandler(RheiaWorkspaceManager::OnSettingsChanged)));
    pm->RegisterEventMethod(RheiaEVT_ENVPLUGIN_REQUEST_DETACH, new RheiaEventFunctor<RheiaWorkspaceManager>(this, RheiaPluginEventHandler(RheiaWorkspaceManager::OnEnvironmentPluginDetach)));
    //pm->RegisterEventMethod(RheiaEVT_FRAME_CLOSING, new RheiaEventFunctor<RheiaWorkspaceManager, RheiaFrameEvent>(this, &RheiaWorkspaceManager::OnCloseParent));
}

void RheiaWorkspaceManager::OnSettingsChanged( wxCommandEvent& event )
{
    ReloadConfig();
}

void RheiaWorkspaceManager::OnEnvironmentPluginDetach( RheiaPluginEvent& event )
{
    RemoveProjectsFor( (RheiaEnvironmentPlugin*) event.GetPlugin() , true );
}

RheiaWorkspaceManager::~RheiaWorkspaceManager()
{
    m_parent->RemoveEventHandler(this);

    RheiaWorkspaceTable::iterator it = m_workspaces.begin();
    for( ; it != m_workspaces.end() ; ++it )
        delete it->second;
}

/**********************************************************************************************************
*	METHODS
**********************************************************************************************************/
void RheiaWorkspaceManager::OnManagementTreeSelection(wxTreeEvent& event)
{
    wxTreeItemId SelectedItem = event.GetItem();

    if (!SelectedItem.IsOk())
        return;

    RheiaTreeItemData *ItemData = (RheiaTreeItemData *) m_tree->GetItemData( SelectedItem );

    if ( !ItemData )
        return;

//    ItemWksp = ItemData->GetWorkspace();
//
//    if ( !ItemWksp )
//        return;

    RheiaTreeItem* item = ItemData->GetOwner();
    item->OnItemSelected();

//    long type = ItemData->GetType();
//
//    RheiaWorkspace *LastWksp = FindWorkspace( m_currentWorkspace );
//    /* First managing the workspace part which is not optional */
//    m_currentWorkspace = ItemWksp->GetName();
//
//    /* Once the workspace */
//    if ( type == ItemData->tdkProject )
//    {
//        RheiaProjectTreeItemData* ItemData2 = (RheiaProjectTreeItemData*) ItemData;
//        RheiaProject *SelectedProject = ItemData2->GetProject();
//        if ( SelectedProject )
//        {
//            ItemWksp->SetCurrentProject( SelectedProject->GetName() );
//            //RheiaNameSpaceViewManager::Get()->Activate( SelectedProject->GetProjectNameSpace() );
//            RheiaCenterPaneManager::Get(m_parent)->ActivatePage( SelectedProject->GetName() );
//
//            RheiaProjectEvent evt(RheiaEVT_PROJECT_SELECTED,
//                            0,
//                            SelectedProject,
//                            SelectedProject->GetName()
//                            );
//
//            m_parent->GetEventHandler()->ProcessEvent(evt);
//        }
//    }
//    else if ( type == ItemData->tdkProjectElement )
//    {
//        RheiaProjectElementTreeItemData* ItemData3 = (RheiaProjectElementTreeItemData*) ItemData;
//        RheiaProject *SelectedProject = ItemData3->GetProject();
//        if ( SelectedProject )
//        {
//            ItemWksp->SetCurrentProject( SelectedProject->GetName() );
//            //RheiaNameSpaceViewManager::Get()->Activate( SelectedProject->GetProjectNameSpace() );
//            RheiaCenterPaneManager::Get(m_parent)->ActivatePage( SelectedProject->GetName() );
//            RheiaProjectElement *Element = ItemData3->GetProjectElement();
//        }
//    }
}

void RheiaWorkspaceManager::OnManagementTreeDClick(wxTreeEvent& event)
{
    wxTreeItemId SelectedItem = event.GetItem();

    if (!SelectedItem.IsOk())
        return;

    RheiaTreeItemData *ItemData = (RheiaTreeItemData *) m_tree->GetItemData( SelectedItem );

    if ( !ItemData )
        return;

//    ItemWksp = ItemData->GetWorkspace();
//
//    if ( !ItemWksp )
//        return;

    RheiaTreeItem* item = ItemData->GetOwner();
    item->OnItemSelected();

//    long type = ItemData->GetType();
//
//    RheiaWorkspace *LastWksp = FindWorkspace( m_currentWorkspace );
//    /* First managing the workspace part which is not optional */
//    m_currentWorkspace = ItemWksp->GetName();
//
//    /* Once the workspace */
//    if ( type == ItemData->tdkProject )
//    {
//        RheiaProjectTreeItemData* ItemData2 = (RheiaProjectTreeItemData*) ItemData;
//        RheiaProject *SelectedProject = ItemData2->GetProject();
//        if ( !SelectedProject )
//        {
//            return;
//        }
//        else
//        {
//            RheiaProjectConfigurationDlg dlg( m_parent , SelectedProject );
//            dlg.ShowModal();
//
//
//            RheiaProjectEvent evt(RheiaEVT_PROJECT_ACTIVATED,
//                            0,
//                            SelectedProject,
//                            SelectedProject->GetName()
//                            );
//
//            m_parent->GetEventHandler()->ProcessEvent(evt);
//        }
//    }
}

/* Add a new RheiaWorkspace to the workspace table */
bool RheiaWorkspaceManager::AddWorkspace( RheiaWorkspace *workspace, wxString name )
{
    RheiaWorkspaceTable::iterator it = m_workspaces.find( name );
    if( it != m_workspaces.end() )
    {
        return false;
    }

    if( workspace == NULL )
    {
        return false;
    }

    /* Inserting the new workspace in the table */
    std::pair< wxString , RheiaWorkspace* > TempPair( name , workspace );
    m_workspaces.insert( TempPair );

    if( m_tree )
    {
        wxBitmap bmp = workspace->GetBitmap(16 );

        int idx = m_treeImages->Add( bmp );
        RheiaTreeItemData* item = new RheiaTreeItemData( workspace );

        wxTreeItemId wkspId = m_tree->AppendItem( m_treeRoot , name , idx , idx , item );
        /* @todo, here we have to manage the creation of the workspace in the
        *	main frame. CreateMenu, CreateTreeConfig and result...
        *	We might have to do this in different functions.
        */
        workspace->CreateTree( m_tree ,
                            wkspId , 16 );

        GetManagementTree()->SelectItem( workspace->GetRoot() );
    }

    /* Setting the currently selected workspace */
    m_currentWorkspace = name;

    return true;
}

/* Specifies if the workspace already exists or not */
bool RheiaWorkspaceManager::Exists( wxString name )
{
    RheiaWorkspaceTable::iterator iter;

    iter = m_workspaces.find( name );
    if ( iter == m_workspaces.end() )
    {
        return false;
    }

    return true;
}

/* Find a workspace in the table by its name */
RheiaWorkspace* RheiaWorkspaceManager::FindWorkspace( const wxString name )
{
    RheiaWorkspaceTable::iterator iter;

    iter = m_workspaces.find( name );
    if ( iter != m_workspaces.end() )
    {
        return iter->second;
    }

    return NULL;
}

/* This method is used when we need to save a workspace
*	@param workspace RheiaWorkspace to save
*/
bool RheiaWorkspaceManager::SaveWorkspace( RheiaWorkspace *workspace )
{
    if( workspace == NULL )
        return false;

    RheiaWorkspaceEvent evt(RheiaEVT_WORKSPACE_SAVING,0,workspace);
    m_parent->GetEventHandler()->ProcessEvent(evt);

    if ( workspace->FileName.IsEmpty() )
    {
        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_workspace_path") , RheiaStandardPaths::HomeDirectory() );

        wxFileDialog dialog( m_parent ,
                             wxT("Select the workspace file in which you want to save..."),
                             RheiaStandardPaths::HomeDirectory(),
                             wxEmptyString,
                             wxT("*.wksp" ),
                             wxFD_SAVE |  wxFD_OVERWRITE_PROMPT );

        if ( dialog.ShowModal() != wxID_OK )
        {
            InfoWindow::Display( wxT("WARNING"), wxT("You have canceled the save of your workspace\n"
                                 "If the application is closing all information will be destroy !") );
            return false;
        }

        workspace->FileName = dialog.GetPath();

        wxFileName lastPath( workspace->FileName );
        RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
    }

    if( workspace->Name.IsEmpty() )
    {
        wxString WkspName = wxGetTextFromUser( wxT("Please enter your workspace name : ") , wxT("Saving workspace with no name ...") , wxT("workspace") );

        if( WkspName.IsEmpty() )
            return false;

        workspace->Name = WkspName;
    }

    RheiaWorkspaceLoader loader( workspace );
    loader.Save( workspace->FileName );

    workspace->SetModified( false );

    AddLast( workspace->FileName );
    SetLast( workspace->FileName );

    RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_SAVED,0,workspace);
    m_parent->GetEventHandler()->ProcessEvent(evt);

    return true;
}

/* This method is used when we want to load a workspace via its workspace plugin
*	@param filename File's name for loading the workspace
*/
RheiaWorkspace* RheiaWorkspaceManager::LoadWorkspace( wxString filename )
{
    RheiaWorkspace* workspace = NULL;
    workspace = new RheiaWorkspace(m_parent);

    RheiaWorkspaceEvent evt(RheiaEVT_WORKSPACE_OPENING,0,workspace);
    m_parent->GetEventHandler()->ProcessEvent(evt);

    RheiaWorkspaceLoader loader( workspace );

    if( !loader.Open( filename ) )
    {
        delete workspace;
        return NULL;
    }

    SelectWorkspace( workspace->GetName() );

    RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_OPENED,0,workspace);
    m_parent->GetEventHandler()->ProcessEvent(evt2);

    return workspace;
}

/* Add a workspace to the last workspace list */
bool RheiaWorkspaceManager::AddLast( const wxString& path )
{
    RheiaConfigurationManager* wcfg = RheiaManager::Get()->GetConfigurationManager( wxT("workspace_manager") );
    size_t len = m_LastFiles.size();

    int index = m_LastFiles.Index( path );

    if( index != wxNOT_FOUND )
    {
            m_LastFiles.RemoveAt( index );
            m_LastFiles.Insert( path , 0 );
    }else{
            if( len > m_HistoryLength )
                    m_LastFiles.Remove( m_LastFiles.Last() );
            m_LastFiles.Insert( path , 0 );
    }

    RecreateLastMenu();

    /* Now save the list in the configuration manager */
    wcfg->Write( wxT("/recent_workspaces") , m_LastFiles );

    return true;
}

void RheiaWorkspaceManager::RecreateLastMenu()
{
    wxMenuBar* mainMenuBar = RheiaMenuManager::Get(m_parent)->GetMainMenuBar();
    int index = mainMenuBar->FindMenuItem( wxT("File"), wxT("Recent workspaces") );

    wxMenuItem* item = mainMenuBar->FindItem( index );
    wxMenu* m_menu = item->GetSubMenu();

    wxMenuItemList items = m_menu->GetMenuItems();
    for( size_t i = 0; i < items.size(); i++ )
    {
            m_menu->Delete( items[i] );
    }

    for( size_t i = 0; i < m_LastFiles.size(); i++ )
    {
            wxString itemPath = m_LastFiles[i];
            wxMenuItem *item = m_menu->Append( idLastWksp[i] , itemPath );
    }
}

/* History lenght set function */
bool RheiaWorkspaceManager::SetHistoryLenght( size_t length )
{
    RheiaConfigurationManager* wcfg = RheiaManager::Get()->GetConfigurationManager( wxT("workspace_manager") );
    m_HistoryLength = DefaultHistoryLength;
    wcfg->Write( wxT("/history_length") , (int) m_HistoryLength );

    if( m_LastFiles.size() > length )
    {
            m_LastFiles.RemoveAt( m_HistoryLength , m_LastFiles.GetCount() - m_HistoryLength );
            wcfg->Write( wxT("/recent_workspaces") , m_LastFiles );
            RecreateLastMenu();
    }

    return true;
}

/* Sets the last workspace and write it in the configuration file */
bool RheiaWorkspaceManager::SetLast( const wxString& path )
{
    RheiaConfigurationManager* wcfg = RheiaManager::Get()->GetConfigurationManager( wxT("workspace_manager") );
    m_Last = path;
    wcfg->Write( wxT("/last_workspace") , m_Last );

    return true;
}

bool RheiaWorkspaceManager::LoadLast()
{
    RheiaWorkspace* workspace = LoadWorkspace( m_Last );
    if( workspace == NULL )
            return false;

    workspace->UpdateTree( m_tree , workspace->GetRoot() );

    return true;
}

void RheiaWorkspaceManager::OnRecentOpen( wxCommandEvent& event )
{
    wxString path;
    int Id = event.GetId();

    path = m_LastFiles[ Id - idLastWksp[0] ];

    if( path.IsEmpty() )
        return;

    RheiaWorkspace* workspace = LoadWorkspace( path );
}

bool RheiaWorkspaceManager::RemoveWorkspace( const wxString& name )
{
    RheiaWorkspaceTable::iterator it = m_workspaces.find( name );

    if( it == m_workspaces.end() )
        return false;

    RheiaWorkspaceEvent evt(RheiaEVT_WORKSPACE_CLOSING,0,it->second);
    m_parent->GetEventHandler()->ProcessEvent(evt);

    if( m_tree )
    {
        wxTreeItemId workspaceRoot = it->second->GetRoot();
        m_tree->Delete( workspaceRoot );
    }

    delete it->second;
    m_workspaces.erase( it );

    if ( name.IsSameAs( m_currentWorkspace ) )
    {
        m_currentWorkspace = wxEmptyString;
        if ( m_workspaces.size() > 0 )
        {
            it = m_workspaces.begin();
            SelectWorkspace( it->first );
        }
    }

    RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_CLOSED,0,it->second);
    m_parent->GetEventHandler()->ProcessEvent(evt2);

    return true;
}

void RheiaWorkspaceManager::SelectWorkspace( wxString name )
{
    m_currentWorkspace = name;
    /* now select the workspace int the tree */
    RheiaWorkspace* workspace = FindWorkspace( name );

    if( m_tree )
    {
        wxTreeItemId wroot = workspace->GetRoot();
        m_tree->SelectItem( wroot , true );
    }
}

void RheiaWorkspaceManager::SelectProject( wxString name )
{
    if( !m_tree )
        return;

    RheiaWorkspaceTable::iterator it = m_workspaces.begin();

    for( ; it != m_workspaces.end() ; ++it )
    {
        wxTreeItemId wroot = it->second->GetRoot();

        wxTreeItemIdValue m_cookie;
        wxTreeItemId child = m_tree->GetFirstChild( wroot , m_cookie );

        while( child.IsOk() )
        {
            wxString cname = m_tree->GetItemText( child );
            if( cname.IsSameAs( name ) )
            {
                m_tree->SelectItem( child );

                RheiaProject* project = (RheiaProject*) it->second->Find( cname );
                if( project )
                {
                    RheiaProjectEvent evt(RheiaEVT_PROJECT_SELECTED,
                                    0,
                                    project,
                                    project->GetName()
                                    );

                   m_parent->GetEventHandler()->ProcessEvent(evt);
                }

                return;
            }
            child = m_tree->GetNextChild( wroot , m_cookie );
        }
    }
}

bool RheiaWorkspaceManager::RemoveProjectsFor( RheiaEnvironmentPlugin* plugin , bool confirmation )
{
    RheiaWorkspaceTable::iterator it = m_workspaces.begin();

    for( ; it != m_workspaces.end() ; ++it )
    {
        RheiaTreeItemMap m_projects = it->second->GetItems();
        RheiaTreeItemMap::iterator pit = m_projects.begin();

        RheiaWorkspaceEvent evt(RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS,0,it->second);
        m_parent->GetEventHandler()->ProcessEvent(evt);

        for( ; pit != m_projects.end() ; pit++ )
        {
            if( pit->second->IsKindOf(CLASSINFO(RheiaProject) ) && plugin->CanHandleProject( ((RheiaProject*) pit->second)->GetType()) )
            {
                RheiaProject* project = (RheiaProject*) pit->second;
                wxString prjname = pit->first;

                if( confirmation )
                {
                    if ( project->GetModified() )
                    {
                        int retcode = wxMessageBox( wxT("The project : ") + prjname + wxT(" has not been saved, would you like to save it?") ,
                            wxT("Alert") , wxYES | wxNO |wxCANCEL | wxCENTER );

                        if( retcode == wxCANCEL )
                        {
                            RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS,0,it->second);
                            m_parent->GetEventHandler()->ProcessEvent(evt2);
                            return false;
                        }
                        else if( retcode == wxYES )
                        {
                            wxString prjpath = project->GetFileName();

                            if( prjpath.IsEmpty() )
                            {
                                wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );

                                wxFileDialog dialog( m_parent,
                                                 wxT("Select project path files you want to save..."),
                                                 LastOpenPath,
                                                 wxEmptyString,
                                                 FileExt::PRJ_EXT_FILE,
                                                 wxFD_SAVE );

                                if ( dialog.ShowModal() != wxID_OK )
                                {
                                    RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS,0,it->second);
                                    m_parent->GetEventHandler()->ProcessEvent(evt2);
                                    return false;
                                }

                                prjpath = dialog.GetPath();
                                wxFileName lastPath( prjpath );
                                RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
                            }

                            RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
                                            0,
                                            project,
                                            project->GetName()
                                            );

                            m_parent->GetEventHandler()->ProcessEvent(evt);

                            RheiaProjectLoader loader( project );
                            loader.Save( prjpath );

                            RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
                                            0,
                                            project,
                                            project->GetName()
                                            );

                            m_parent->GetEventHandler()->ProcessEvent(evt2);
                        }
                    }
                }
                project->SetModified( false );
                it->second->Remove( pit->first );

                if( m_tree )
                    it->second->UpdateTree( GetManagementTree() ,
                                     it->second->GetRoot() );

                it->second->SetModified( true );
            }

        }

        RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS,0,it->second);
        m_parent->GetEventHandler()->ProcessEvent(evt2);

    }

    return true;
}

/* Used when we act on the file menu new workspace item */
void RheiaWorkspaceManager::OnFileWorkspaceNew( wxCommandEvent &event )
{
    wxString path = wxEmptyString;
    wxString name = wxGetTextFromUser( wxT("Enter the name of your new workspace : ") , wxT("New workspace name") , wxT("workspace") , m_parent );

    if ( name.IsEmpty() )
        return;

    while ( Exists( name ) )
    {
        name = wxGetTextFromUser( wxT("Workspace exists please select a different name for your new workspace : ") , wxT("New workspace name") , name , m_parent );
        if ( name.IsEmpty() )
            return;
    }

    int retId = wxMessageBox( wxT("Would you like to save your workspace first ?") , wxT("Request for workspace file...") , wxYES_NO );

    if ( retId == wxYES )
    {
        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_workspace_path") , RheiaStandardPaths::HomeDirectory() );

        wxFileDialog dialog( m_parent,
                             wxT("Select the workspace files you want to load..."),
                             LastOpenPath,
                             name + FileExt::WKSP_EXT,
                             FileExt::WKSP_EXT_FILE,
                             wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

        if ( dialog.ShowModal() == wxID_OK )
        {
            path = dialog.GetPath();
            wxFileName lastPath( path );
            RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_workspace_path") , lastPath.GetPath() );
        }
    }

    RheiaWorkspace *newWksp = new RheiaWorkspace( m_parent , path , name );
    AddWorkspace( newWksp , name );

    if ( !path.IsEmpty() )
    {
        SaveWorkspace( newWksp );
        SetLast( path );
        AddLast( path );
    }

    RheiaStatusBarManager::Get(m_parent)->SetWorkspace( name );
}

/* Used when we act on the file menu new workspace item */
void RheiaWorkspaceManager::OnFileWorkspaceOpen( wxCommandEvent &event )
{

    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_workspace_path") , RheiaStandardPaths::HomeDirectory() );

    wxFileDialog dialog( m_parent,
                         wxT("Select the workspace files you want to load..."),
                         LastOpenPath,
                         wxEmptyString,
                         FileExt::WKSP_EXT_FILE,
                         wxFD_OPEN | wxFD_MULTIPLE );

    if ( dialog.ShowModal() != wxID_OK )
    {
        return;
    }

    wxArrayString filepaths;
    dialog.GetPaths(filepaths);

    wxFileName lastPath( filepaths[0] );
    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_workspace_path") , lastPath.GetPath() );

    for ( unsigned int i = 0; i < filepaths.size() ; i++ )
    {
        RheiaWorkspace* LoadedWorkspace = 0L;
        /* Now just realese the last selected workspace menu */
        bool load = true;
        RheiaWorkspaceTable m_workspaces = GetWorkspaceTable();
        if ( m_workspaces.size() > 0 )
        {
            RheiaWorkspaceTable::iterator iter = m_workspaces.begin();
            for ( iter ; iter != m_workspaces.end() ; iter++ )
            {
                wxFileName tested( iter->second->GetFileName() );
                wxFileName local( filepaths[i] );

                wxString dum1 = tested.GetPath() + wxT("/") + tested.GetFullName();
                wxString dum2 = local.GetPath() + wxT("/") + local.GetFullName();

                if ( dum1.IsSameAs( dum2 ) )
                {
                    load = false;
                    break;
                }
            }
        }

        if ( load )
        {
            LoadedWorkspace = LoadWorkspace( filepaths[i] );
            if ( LoadedWorkspace == NULL )
            {
                wxMessageBox(wxT("Cannot Load the workspace : \n") + filepaths[i] , wxT("Alert") , wxICON_INFORMATION , m_parent );
                return;
            }
        }
    }
}

/* Used when we act on the file menu new workspace item */
void RheiaWorkspaceManager::OnFileWorkspaceSave( wxCommandEvent &event )
{
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );
    if ( !workspace )
        return;

    if ( workspace->GetModified() )
    {
        SaveWorkspace( workspace );
        m_parent->SetStatusText( wxT("Workspace : ") + workspace->GetName() + wxT(" saved !") );
    }
    else
        m_parent->SetStatusText( wxT("Workspace : ") + workspace->GetName() + wxT(" already saved !") );
}

/* Used when we act on the file menu save all workspace item */
void RheiaWorkspaceManager::OnFileWorkspaceSaveAll( wxCommandEvent &event )
{
    RheiaWorkspaceTable table = GetWorkspaceTable();
    RheiaWorkspaceTable::iterator iter = table.begin();
    wxString SavedWksp;

    if ( table.size() > 0 )
    {
        for ( iter ; iter != table.end() ; iter++ )
        {
            if ( iter->second->GetModified() )
            {
                SaveWorkspace( iter->second );
                SavedWksp = SavedWksp + iter->second->GetName() + wxT(",");
                iter->second->SetModified(false);
            }
        }
        if ( SavedWksp.IsEmpty() )
            m_parent->SetStatusText( wxT("All workspaces already saved !") );
        else
            m_parent->SetStatusText( wxT("Workspaces : ") + SavedWksp + wxT(" saved !") );
    }
}

void RheiaWorkspaceManager::OnFileWorkspaceClose( wxCommandEvent &event )
{
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );
    if ( !workspace )
        return;

    m_parent->Freeze();

    if ( workspace->GetModified() )
    {
        int retId = wxMessageBox( wxT("The workspace has changed do you want to save it ?") , wxT("Alert") , wxYES | wxNO | wxCANCEL | wxCENTER , m_parent );

        if ( retId == wxYES )
        {
            SaveWorkspace( workspace );
            workspace->SetModified(false);
        }
        else if ( retId == wxCANCEL )
        {
            m_parent->Thaw();
            return;
        }
    }

    RemoveWorkspace( workspace->GetName() );
    m_parent->Thaw();
}

void RheiaWorkspaceManager::OnFileProjectNew( wxCommandEvent &event )
{
    /* First Find the currently selected workspace */
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );

    if ( !workspace )
    {
        wxMessageBox( wxT("Please Create a workspace first") , wxT("Rheia : Alert") );
        return;
    }

    RheiaWizardManager::Get(m_parent)->DoCreateNewProject( workspace );
}

void RheiaWorkspaceManager::OnFileProjectOpen( wxCommandEvent &event )
{
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );

    if ( !workspace )
    {
        wxMessageBox( wxT("Please Create a workspace first") , wxT("Rheia : Alert") );
        return;
    }

    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );

    wxFileDialog dialog( m_parent,
                         wxT("Select the workspace files you want to load..."),
                         LastOpenPath,
                         wxEmptyString,
                         FileExt::PRJ_EXT_FILE,
                         wxFD_OPEN | wxFD_MULTIPLE );

    if ( dialog.ShowModal() != wxID_OK )
    {
        return;
    }

    wxArrayString filepaths;
    dialog.GetPaths(filepaths);

    wxFileName lastPath( filepaths[0] );
    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );

    for ( unsigned int i = 0; i < filepaths.size() ; i++ )
    {
        RheiaProject* loadedProject = NULL;
        RheiaProjectLoader loader;

        if ( !loader.Open( filepaths[i] , m_parent, workspace ) )
        {
            InfoWindow::Display( wxT("WARNING") , wxT("Cannot load the document : ") + filepaths[i] );
        }
        else
        {
            loadedProject = loader.GetProject();
            workspace->Add( loadedProject->GetName() , loadedProject );

            RheiaProjectEvent evt(RheiaEVT_PROJECT_OPENED,
                    0,
                    loadedProject,
                    loadedProject->GetName()
                    );

            m_parent->GetEventHandler()->ProcessEvent(evt);
        }
    }

    if( m_tree )
        workspace->UpdateTree( GetManagementTree() ,
                               workspace->GetRoot() );
}

void RheiaWorkspaceManager::OnFileProjectSave( wxCommandEvent &event )
{
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );

    if ( !workspace )
        return;

    wxTreeItemId selItem = m_tree->GetSelection();
    if( !selItem.IsOk() )
        return;

    wxString itemText = m_tree->GetItemText(selItem);
    RheiaTreeItem* item = workspace->Find( itemText );

    if( item == NULL || !item->IsKindOf(CLASSINFO(RheiaProject) ) )
        return;

    RheiaProject* project = dynamic_cast<RheiaProject*>(item);

    if ( !project->GetModified() )
        return;

    wxString prjpath = project->GetFileName();

    if( prjpath.IsEmpty() )
    {
        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );

        wxFileDialog dialog( m_parent,
                         wxT("Select project path files you want to save..."),
                         LastOpenPath,
                         wxEmptyString,
                         FileExt::PRJ_EXT_FILE,
                         wxFD_SAVE );

        if ( dialog.ShowModal() != wxID_OK )
        {
            return;
        }

        prjpath = dialog.GetPath();
        wxFileName lastPath( prjpath );
        RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );

        project->SetFileName( prjpath );
    }

    RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
                    0,
                    project,
                    project->GetName()
                    );

    m_parent->GetEventHandler()->ProcessEvent(evt);

    RheiaProjectLoader loader( project );
    if( !loader.Save( prjpath ) )
        return;

    project->SetModified(false);

    RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
                    0,
                    project,
                    project->GetName()
                    );

    m_parent->GetEventHandler()->ProcessEvent(evt2);
}

void RheiaWorkspaceManager::OnFileProjectSaveAs( wxCommandEvent &event )
{
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );

    if ( !workspace )
        return;

    wxTreeItemId selItem = m_tree->GetSelection();
    if( !selItem.IsOk() )
        return;

    wxString itemText = m_tree->GetItemText(selItem);
    RheiaTreeItem* item = workspace->Find( itemText );

    if( item == NULL || !item->IsKindOf(CLASSINFO(RheiaProject) ) )
        return;

    RheiaProject* project = dynamic_cast<RheiaProject*>(item);

    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );

    wxFileDialog dialog( m_parent,
                     wxT("Select project path files you want to save..."),
                     LastOpenPath,
                     wxEmptyString,
                     FileExt::PRJ_EXT_FILE,
                     wxFD_SAVE );

    if ( dialog.ShowModal() != wxID_OK )
    {
        return;
    }

    wxString prjpath = dialog.GetPath();
    wxFileName lastPath( prjpath );
    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );

    project->SetFileName( prjpath );

    RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
                    0,
                    project,
                    project->GetName()
                    );

    m_parent->GetEventHandler()->ProcessEvent(evt);

    RheiaProjectLoader loader( project );
    if( !loader.Save( prjpath ) )
        return;

    project->SetModified(false);

    RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
                    0,
                    project,
                    project->GetName()
                    );

    m_parent->GetEventHandler()->ProcessEvent(evt2);
}

void RheiaWorkspaceManager::OnFileProjectClose( wxCommandEvent &event )
{
    RheiaWorkspace *workspace = FindWorkspace( GetCurrentSelectedWorkspace() );

    if ( !workspace )
        return;

    wxTreeItemId selItem = m_tree->GetSelection();
    if( !selItem.IsOk() )
        return;

    wxString itemText = m_tree->GetItemText(selItem);
    RheiaTreeItem* item = workspace->Find( itemText );

    if( item == NULL || !item->IsKindOf(CLASSINFO(RheiaProject) ) )
        return;

    RheiaProject* project = dynamic_cast<RheiaProject*>(item);

    RheiaProjectEvent evt(RheiaEVT_PROJECT_CLOSING,
                    0,
                    project,
                    project->GetName()
                    );

    m_parent->GetEventHandler()->ProcessEvent(evt);

    if ( project->GetModified() )
    {
        int retcode = wxMessageBox( wxT("The project : ") + project->GetName() + wxT(" has not been saved, would you like to save it?") ,
            wxT("Alert") , wxYES | wxNO |wxCANCEL | wxCENTER , m_parent );

        if( retcode == wxCANCEL )
            return;
        else if( retcode == wxYES )
        {
            wxString prjpath = project->GetFileName();

            if( prjpath.IsEmpty() )
            {
                wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );

                wxFileDialog dialog( m_parent,
                                 wxT("Select project path files you want to save..."),
                                 LastOpenPath,
                                 wxEmptyString,
                                 FileExt::PRJ_EXT_FILE,
                                 wxFD_SAVE );

                if ( dialog.ShowModal() != wxID_OK )
                {
                    return;
                }

                prjpath = dialog.GetPath();
                wxFileName lastPath( prjpath );
                RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
            }
            RheiaProjectLoader loader( project );

            RheiaProjectEvent evt(RheiaEVT_PROJECT_SAVING,
                    0,
                    project,
                    project->GetName()
                    );

            m_parent->GetEventHandler()->ProcessEvent(evt);

            loader.Save( prjpath );
            project->SetModified(false);

            RheiaProjectEvent evt2(RheiaEVT_PROJECT_SAVED,
                    0,
                   project,
                    project->GetName()
                    );

            m_parent->GetEventHandler()->ProcessEvent(evt2);
        }
    }

    wxString prjname = project->GetName();

    workspace->Remove( prjname );

    if( m_tree )
        workspace->UpdateTree( GetManagementTree() ,
                                workspace->GetRoot() );

    workspace->SetModified( true );

    RheiaProjectEvent evt2(RheiaEVT_PROJECT_CLOSED,
                    0,
                    NULL,
                    prjname
                    );

    m_parent->GetEventHandler()->ProcessEvent(evt2);
}

void RheiaWorkspaceManager::BuildMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Append( menuId , wxT("&Workspace Manager Settings") , wxT("Configure the workspace manager") );
    }

    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal | rspfDataUser );

    idx = menuBar->FindMenu(wxT("File"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnFile = menuBar->GetMenu( idx );

        wxMenuItem* m_item = new wxMenuItem( mnFile , idFileWorkspaceNew , wxT("&New Workspace\tCTRL-N") , wxT("Creates a new worspace") );
        wxBitmap bmp = RheiaLoadBitmap( path+wxT("#zip:workspace_new_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 0 , m_item );

        m_item = new wxMenuItem( mnFile , idFileWorkspaceOpen , wxT("&Open Workspace\tCTRL-O") , wxT("Open a worspace") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:workspace_open_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 1 , m_item );

        m_item = new wxMenuItem( mnFile , idFileWorkspaceSave , wxT("&Save Workspace\tCTRL-S") , wxT("Save the current workspace and all its contents") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:workspace_save_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 2 , m_item );

        m_item = new wxMenuItem( mnFile , idFileWorkspaceSaveAs , wxT("Save Workspace &As...") , wxT("Save the current workspace and all its contens in a new file") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:workspace_save_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 3 , m_item );

        m_item = new wxMenuItem( mnFile , idFileWorkspaceClose , wxT("&Close Workspace...") , wxT("Close the current workspace and all its contents") );
        mnFile->Insert( 4 , m_item );

        m_item = new wxMenuItem( mnFile , wxID_SEPARATOR , wxEmptyString , wxEmptyString , wxITEM_SEPARATOR );
        mnFile->Insert( 5 , m_item );

        m_item = new wxMenuItem( mnFile , idFileNewProject , wxT("New P&roject\tCTRL-ALT-N") , wxT("Creates a new project in the current workspace (wizard)") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:project_new_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 6 , m_item );

        m_item = new wxMenuItem( mnFile , idFileNewProject , wxT("O&pen Project\tCTRL-ALT-O") , wxT("Adds an existing project in the current workspace") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:project_open_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 7 , m_item );

        m_item = new wxMenuItem( mnFile , idFileNewProject , wxT("Sa&ve Project\tCTRL-ALT-S") , wxT("Save the current project and all its contents") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:project_save_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 8 , m_item );

        m_item = new wxMenuItem( mnFile , idFileNewProject , wxT("Save Projec&t As...\tCTRL-ALT-S") , wxT("Save the current workspace and all its contents in a new file") );
        mnFile->Insert( 9 , m_item );

        m_item = new wxMenuItem( mnFile , idFileNewProject , wxT("C&lose Project\tCTRL-ALT-K") , wxT("Close the current from the current workspace") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:project_close_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 10 , m_item );

        m_item = new wxMenuItem( mnFile , wxID_SEPARATOR , wxEmptyString , wxEmptyString , wxITEM_SEPARATOR );
        mnFile->Insert( 11 , m_item );

        m_item = new wxMenuItem( mnFile , idFileSaveAll , wxT("&Save All\tCTRL-ALT-A") , wxT("Save all opened workspaces, projects and files") );
        bmp = RheiaLoadBitmap( path+wxT("#zip:save_all_24.png") );
        m_item->SetBitmap(bmp);
        mnFile->Insert( 12 , m_item );
    }
}

void RheiaWorkspaceManager::ReleaseMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Delete( menuId );
    }

    idx = menuBar->FindMenu(wxT("File"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnFile = menuBar->GetMenu( idx );
        mnFile->Delete( idFileWorkspaceNew );
        mnFile->Delete( idFileWorkspaceOpen );
        mnFile->Delete( idFileWorkspaceSave );
        mnFile->Delete( idFileSaveAllWorkspaces );
        mnFile->Delete( idFileWorkspaceClose );
        mnFile->Delete( idFileNewProject );
        mnFile->Delete( idFileOpenProject );
        mnFile->Delete( idFileProjectSave );
        mnFile->Delete( idFileProjectSaveAs );
        mnFile->Delete( idFileProjectClose );
        mnFile->Delete( idFileSaveAll );
    }
}

void RheiaWorkspaceManager::OnConfigure(wxCommandEvent& event)
{
    RheiaConfigurationDialog dialog( m_parent );
    RheiaWkspMgrSettingsPanel* m_panel = new RheiaWkspMgrSettingsPanel(&dialog);
    dialog.SetConfigurationTool( m_panel );
    dialog.ShowModal();
}

void RheiaWorkspaceManager::FinalizeStartUp()
{
    RheiaConfigurationManager* CfgMgr = RheiaProfileManager::Get()->GetActiveProfileManager();
    bool blankWksp = CfgMgr->ReadBool( wxT("/environment/blank_workspace") , true );
    if ( blankWksp )
    {
        RheiaWorkspace *newWksp = new RheiaWorkspace( m_parent , wxEmptyString , wxT("workspace") );
        AddWorkspace( newWksp , wxT("workspace") );
        RheiaStatusBarManager::Get(m_parent)->SetWorkspace( wxT("workspace") );
    }
    else
    {
        LoadLast();
    }
}

bool RheiaWorkspaceManager::SaveAll()
{
    /* Check for unsaved workspaces */
    RheiaWorkspaceTable table = GetWorkspaceTable();
    RheiaWorkspaceTable::iterator iter = table.begin();

    if ( table.size() > 0 )
    {
        for ( iter ; iter != table.end() ; iter++ )
        {
            if ( iter->second->GetModified() )
            {
                wxMessageDialog dialog( m_parent, wxT("Workspace : ") + iter->first + wxT(" not saved would you like to save it ?"),
                                        wxT("Save ") + iter->first + wxT("?") , wxYES | wxNO | wxCANCEL | wxCENTRE );

                int ret = dialog.ShowModal();
                if ( ret == wxID_YES )
                    SaveWorkspace( iter->second );
                else if( ret == wxID_CANCEL )
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void RheiaWorkspaceManager::OnCloseParent( RheiaFrameEvent& event )
{
    if( !SaveAll() )
        m_parent->SetCanClose();

    event.Skip();
}

wxToolBar* RheiaWorkspaceManager::BuildToolBar(wxWindow* parent)
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    wxString resname = wxT("wksp_toolbar");

    wxXmlResource *myres = wxXmlResource::Get();
    if( !myres->Load(path + _T("#zip:wksp_toolbar.xrc")) )
        wxMessageBox(_("Error loadding ressource") + path + _T("#zip:prj_toolbar.xrc") , _("Error") );

    wxSize size = wxSize( 24 , 24 );
    wxToolBar* tbworkspace = new wxToolBar(parent, -1, wxDefaultPosition, size, wxTB_FLAT | wxTB_NODIVIDER);
    tbworkspace->SetToolBitmapSize(size);
    RheiaManager::Get()->AddonToolBar(tbworkspace,resname);

    tbworkspace->Realize();
    tbworkspace->SetInitialSize();

    return tbworkspace;
}

wxToolBar* RheiaWorkspaceManager::BuildProjectsToolBar(wxWindow* parent)
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    wxString resname = wxT("prj_toolbar");

    wxXmlResource *myres = wxXmlResource::Get();
    if( !myres->Load(path + _T("#zip:prj_toolbar.xrc")) )
        wxMessageBox(_("Error loadding ressource") + path + _T("#zip:prj_toolbar.xrc") , _("Error") );

    wxSize size = wxSize( 24 , 24 );
    wxToolBar* tbproject = new wxToolBar(parent, -1, wxDefaultPosition, size, wxTB_FLAT | wxTB_NODIVIDER);
    tbproject->SetToolBitmapSize(size);
    RheiaManager::Get()->AddonToolBar(tbproject,resname);

    tbproject->Realize();
    tbproject->SetInitialSize();

    return tbproject;
}
