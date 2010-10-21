/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
	m_parent = parent;
	FileName = filename;
	isLoaded = false;
	Name = name;
    /* register the workspace as a Main frames event handler */
    m_parent->PushEventHandler(this);
}

/* Destructor */
RheiaWorkspace::~RheiaWorkspace()
{
    m_parent->RemoveEventHandler(this);
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

///* Returns the workspace's path */
wxString RheiaWorkspace::GetPath( void )
{
    if ( FileName.IsEmpty() )
        return RheiaStandardPaths::DataDirectoryUser();

    wxFileName file( FileName );
    return file.GetPath();
}

const wxBitmap& RheiaWorkspace::GetBitmap( const int& size )
{
    wxString fPath = RheiaStandardPaths::DataDirectoryGlobal() + wxString::Format( wxT("/resource.zip#zip:workspace_%d.png") , size );
    m_bmp = RheiaLoadBitmap( fPath );

    return m_bmp;
}
