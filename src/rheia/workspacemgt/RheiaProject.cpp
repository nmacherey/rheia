/**
*   @file RheiaProject.cpp
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added modifications of RheiaProject to be
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaProject.h>

#include <RheiaManager.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaWorkspace.h>
#include <RheiaToolBarManager.h>
#include <RheiaTreeItemData.h>
#include <RheiaEvents.h>
#include <RheiaEventProject.h>
#include <RheiaEventsManager.h>
#include <RheiaEnvironmentPlugin.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#include <wx/frame.h>
#include <wx/imaglist.h>

IMPLEMENT_ABSTRACT_CLASS(RheiaProject,RheiaTreeItem)

/* Constructor */
RheiaProject::RheiaProject(
    RheiaManagedFrame* parent,
    RheiaWorkspace* workspace ,
    const wxString& filename ,
    const wxString& name ):
    RheiaTreeItem(),
    m_parent( parent ),
    m_filename( filename ),
    m_loaded( false ),
    m_name( name ),
    m_workspace( workspace )
{
	if(m_parent)
        m_parent->PushEventHandler(this);

}

/* Destructor */
RheiaProject::~RheiaProject(){

    if(m_parent)
        m_parent->RemoveEventHandler(this);
}

/* Copy constructor
*	@param Prj Reference object from which to copy info
*/
RheiaProject::RheiaProject( RheiaProject& Prj ) :
    RheiaTreeItem( Prj ),
    m_parent( Prj.m_parent ),
    m_filename( Prj.m_filename ),
    m_loaded( Prj.m_loaded ),
    m_name( Prj.m_name ),
    m_workspace( Prj.m_workspace )
{
	if(m_parent)
        m_parent->PushEventHandler(this);
}

///* Specifies if the project has been modified in any way.
//*
//*	@return True if the project is modified in any way. */
//bool RheiaProject::HasBeenModified() {
//	return m_modified;
//};
//
///* Mark the project as modified or not.
//*	This function shall be derived by any project in order to manage specific info
//*	when marking the project has modified.
//*
//* @param modified If true, the project is marked as modified. If false, as not-modified.
//*/
//void RheiaProject::SetHasBeenModified(bool modified)
//{
//	/*! @todo here the project is set as has been modified, when we are setting this variable
//	*	the project has to specify to all its content that it has been modified.
//	*/
//	m_modified = modified;
//}

//void RheiaProject::CreateManagementTree( wxTreeCtrl *Tree , const wxTreeItemId& root )
//{
//    RheiaProjectTreeItemData *TreeItemData = new RheiaProjectTreeItemData(m_workspace, this);
//    TreeItemData->SetOwner( this );
//
//    wxImageList *TreeImages = Tree->GetImageList();
//
//    int IndexSelected;
//    wxBitmap m_bmp = GetBitmap(16);
//    IndexSelected = TreeImages->Add( m_bmp );
//
//    m_treeroot = Tree->AppendItem( root , m_name , IndexSelected , IndexSelected , TreeItemData );
//    OnCreateManagementTree( Tree , m_treeroot );
//}

bool RheiaProject::Rename( const wxString& name , bool confirm )
{
    if( confirm )
    {
        int ret = wxMessageBox( wxT("Are you sure you want to rename this project ?") , wxT("Warning") , wxYES_NO | wxICON_QUESTION );
        if( ret == wxNO )
            return true;
    }

    RheiaWorkspaceManager::Get(m_parent)->GetManagementTree()->SetItemText( m_root , name );
    m_name = name;
    return true;
}
