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
#include <RheiaCenterPaneManager.h>

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
    m_filename( filename ),
    m_loaded( false ),
    m_name( name ),
    m_workspace( workspace ),
	m_parent( parent )
{
	if(m_parent)
        m_parent->PushEventHandler(this);

}

/* Destructor */
RheiaProject::~RheiaProject(){
    RheiaCenterPaneManager *cpm = RheiaCenterPaneManager::Get(m_parent);
    cpm->DeletePage(m_name);
	
	RheiaWorkspaceManager* wmgr = RheiaWorkspaceManager::Get(m_parent);
	if( !m_filename.IsEmpty() )
		wmgr->AddLastProject(m_filename);
	
    if(m_parent)
        m_parent->RemoveEventHandler(this);
}

/* Copy constructor
*	@param Prj Reference object from which to copy info
*/
RheiaProject::RheiaProject( RheiaProject& Prj ) :
    RheiaTreeItem( Prj ),
    m_filename( Prj.m_filename ),
    m_loaded( Prj.m_loaded ),
    m_name( Prj.m_name ),
    m_workspace( Prj.m_workspace ),
	m_parent( Prj.m_parent )
{
	if(m_parent)
        m_parent->PushEventHandler(this);
}

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
