#include <RheiaWorkspace.h>

#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaProject.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaMenuManager.h>
#include <RheiaPlatform.h>
#include <RheiaTreeItemData.h>

#include <wx/frame.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/aui/aui.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaWorkspace, RheiaTreeItem)


RheiaWorkspace::RheiaWorkspace( RheiaManagedFrame* parent,
                            const wxString& filename ,
                            const wxString& name ):
                            RheiaTreeItem(),
                            FileName( filename ),
                            isLoaded( false ),
                            Name( name ),
                            m_parent(parent)
{
    /* register the workspace as a Main frames event handler */
    m_parent->PushEventHandler(this);
}

RheiaWorkspace::RheiaWorkspace(  ):
    RheiaTreeItem(),
    FileName( wxEmptyString ),
    isLoaded( false ),
    Name( wxEmptyString ),
    m_parent(NULL)
{

}

void RheiaWorkspace::Create( RheiaManagedFrame* parent,
        const wxString& filename,
		const wxString& name )
{
    /* register the workspace as a Main frames event handler */
    m_parent->PushEventHandler(this);
}

/* Destructor */
RheiaWorkspace::~RheiaWorkspace()
{
    m_parent->RemoveEventHandler(this);

//    RheiaProjectTable::iterator pit = ProjectTable.begin();
//    for( ; pit != ProjectTable.end() ; ++pit )
//    {
//        RheiaCenterPaneManager::Get(m_parent)->DeletePage( pit->first );
//        delete pit->second;
//    }
}

/* Copy constructor
*	@param Wksp Reference object from which to copy info
*/
RheiaWorkspace::RheiaWorkspace( RheiaWorkspace& Wksp ) :
    RheiaTreeItem(Wksp),
    FileName( Wksp.FileName ),
    isLoaded( Wksp.isLoaded ),
    Name( Wksp.Name ),
    m_parent(Wksp.m_parent)
{
    /* register the workspace as a Main frames event handler */
    m_parent->PushEventHandler(this);
}

RheiaTreeItem* RheiaWorkspace::Clone()
{
    return new RheiaWorkspace(*this);
}

//wxArrayString& RheiaWorkspace::GetProjectNames()
//{
//    RheiaProjectTable::iterator iter = ProjectTable.begin();
//    ProjectsNames.Clear();
//    if ( ProjectTable.size() > 0 )
//    {
//        for ( iter ; iter != ProjectTable.end() ; iter++ )
//        {
//            ProjectsNames.Add( iter->first );
//        }
//    }
//    return ProjectsNames;
//}

//bool RheiaWorkspace::ProjectExists( wxString name )
//{
//    RheiaProjectTable::iterator iter = ProjectTable.find( name );
//    if ( iter != ProjectTable.end() )
//        return true;
//    return false;
//}
//
//RheiaProject *RheiaWorkspace::FindProjectByName( const wxString name )
//{
//    RheiaProjectTable::iterator iter = ProjectTable.find( name );
//    if ( iter != ProjectTable.end() )
//        return iter->second;
//    return NULL;
//}
//
//bool RheiaWorkspace::AddProject( wxString name, RheiaProject* project )
//{
//    if ( ProjectExists(name) )
//        return false;
//
//    ProjectTable[name] = project;
//    SetCurrentProject( name );
//
//    /* mark the workspace as modified */
//    SetHasBeenModified(true);
//
//    RheiaCenterPaneManager::Get(m_parent)->AddPage( name , project );
//
//    return true;
//}
//
//bool RheiaWorkspace::RemoveProject( const wxString name , bool confirm )
//{
//    if( confirm )
//    {
//        int retcode = wxMessageBox( wxT("Are you sure you want to close this project : ") + name + wxT("?"),
//                        wxT("Alert") , wxOK | wxCANCEL );
//
//        if( retcode == wxCANCEL )
//            return false;
//    }
//
//    RheiaProjectTable::iterator pit = ProjectTable.find(name);
//
//    if( pit == ProjectTable.end() )
//        return false;
//
//    RheiaCenterPaneManager::Get(m_parent)->DeletePage( pit->first );
//
//    delete pit->second;
//    ProjectTable.erase( pit );
//
//    return true;
//}

//bool RheiaWorkspace::RemoveProject( RheiaProject* project , bool confirm )
//{
//    wxString name;
//
//    RheiaProjectTable::iterator pit = ProjectTable.begin();
//
//    for( ; pit != ProjectTable.end() ; ++pit )
//        if( pit->second == project )
//        {
//            name = pit->first;
//            break;
//        }
//
//    if( name.IsEmpty() )
//        return false;
//
//    if( confirm )
//    {
//        int retcode = wxMessageBox( wxT("Are you sure you want to close this project : ") + name + wxT("?"),
//                        wxT("Alert") , wxOK | wxCANCEL );
//
//        if( retcode == wxCANCEL )
//            return false;
//    }
//
//    RheiaCenterPaneManager::Get(m_parent)->DeletePage( pit->first );
//
//    delete pit->second;
//    ProjectTable.erase( pit );
//
//    return true;
//}

///* Returns the workspace's path */
wxString RheiaWorkspace::GetPath( void )
{
    if ( FileName.IsEmpty() )
        return RheiaStandardPaths::DataDirectoryUser();

    wxFileName file( FileName );
    return file.GetPath();
}
//
///* Specifies if the workspace has been modified in any way.
//*
//*	@return True if the workspace is modified in any way. */
//bool RheiaWorkspace::HasBeenModified()
//{
//
//    RheiaProjectTable::iterator iter = ProjectTable.begin();
//    for ( iter ; iter != ProjectTable.end() ; iter++ )
//        if ( iter->second->HasBeenModified( ) )
//            hasBeenModified = true;
//
//    return hasBeenModified;
//}

///* Mark the workspace as modified or not.
//*	This function shall be derived by any workspace in order to manage specific info
//*	when marking the workspace has modified.
//*
//* @param modified If true, the workspace is marked as modified. If false, as not-modified.
//*/
//void RheiaWorkspace::SetHasBeenModified(bool modified)
//{
//    RheiaProjectTable::iterator iter = ProjectTable.begin();
//    for ( iter ; iter != ProjectTable.end() ; iter++ )
//    {
//        iter->second->SetHasBeenModified( modified );
//    }
//    hasBeenModified=modified;
//}

//void RheiaWorkspace::CreateManagementTree( wxTreeCtrl *Tree , const wxTreeItemId& root )
//{
//    RheiaTreeItemData *TreeItemData = new RheiaTreeItemData(this);
//    TreeItemData->SetOwner( this );
//    wxImageList *TreeImages = Tree->GetImageList();
//    int IndexSelected;
//    int IndexUSelected;
//
//    wxString fPath = RheiaStandardPaths::DataDirectoryGlobal() + wxT("/resource.zip#zip:workspace_16.png");
//
//    wxBitmap BmpSelected = RheiaLoadBitmap( fPath );
//    wxBitmap BmpUSelected = RheiaLoadBitmap( fPath );
//
//    IndexSelected = TreeImages->Add( BmpSelected );
//    IndexUSelected = TreeImages->Add( BmpUSelected );
//
//    WorkspaceManagementRoot = Tree->AppendItem( root , Name , IndexUSelected , IndexSelected , TreeItemData );
//
//    /*******************************************************************************************************
//    * Now add the projects management trees
//    *******************************************************************************************************/
//    RheiaProjectTable::iterator it = ProjectTable.begin();
//
//    for( ; it != ProjectTable.end() ; it++ )
//        if( it->second != NULL )
//            it->second->CreateManagementTree( Tree , WorkspaceManagementRoot );
//}

const wxBitmap& RheiaWorkspace::GetBitmap( const int& size )
{
    wxString fPath = RheiaStandardPaths::DataDirectoryGlobal() + wxString::Format( wxT("/resource.zip#zip:workspace_%d.png") , size );
    m_bmp = RheiaLoadBitmap( fPath );

    return m_bmp;
}

//void RheiaWorkspace::UpdateManagementTree( wxTreeCtrl *Tree , const wxTreeItemId& root )
//{
//    Tree->DeleteChildren( WorkspaceManagementRoot );
//    /*******************************************************************************************************
//    * Now add the projects management trees
//    *******************************************************************************************************/
//    RheiaProjectTable::iterator it = ProjectTable.begin();
//
//    for( ; it != ProjectTable.end() ; it++ )
//        if( it->second != NULL )
//            it->second->CreateManagementTree( Tree , WorkspaceManagementRoot );
//}
