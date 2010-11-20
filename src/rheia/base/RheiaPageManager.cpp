/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPageManager.cpp
*
*   Revision : 31-October-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : New file
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	31-October-2010
*	@version 10.10
*/
#include <wx/aui/aui.h>

#include <RheiaPageManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaBookPage.h>
#include <RheiaPageContainer.h>
#include <RheiaException.h>
#include <RheiaEvents.h>
#include <RheiaEventFrame.h>
#include <RheiaEventsManager.h>
#include <RheiaDebug.h>

BEGIN_EVENT_TABLE( RheiaPageManager , wxEvtHandler )
    //EVT_FRAME_CLOSING( RheiaPageManager::OnCloseParent )
END_EVENT_TABLE()

RheiaPageManager::RheiaPageManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_window(NULL),
	m_sizer(NULL),
    m_parent(parent),
    cbookId(wxNewId())
{
    if (m_parent)
    {
        // push ourself in the application's event handling chain...
        m_parent->PushEventHandler(this);
    }
	
	RheiaFrameEventsManager::Get(m_parent)->RegisterEventMethod(RheiaEVT_FRAME_CLOSING,new RheiaEventFunctor<RheiaPageManager>(this, RheiaFrameEventHandler(RheiaPageManager::OnCloseParent)));
}

RheiaPageManager::~RheiaPageManager() 
{	
	if( m_window != NULL )
		RheiaThrow( wxT("Error it seams that your are trying to delete a Book Manager without having destroyed its book first !") );
}

wxWindow* RheiaPageManager::CreateWindow( wxWindow* parent )
{
    m_window = new wxPanel(parent, cbookId);
	m_sizer = new wxBoxSizer(wxVERTICAL);
	
	m_window->SetSizer(m_sizer);
	m_sizer->SetSizeHints(m_window);

    OnCreateWindow();
    return m_window;
}

void RheiaPageManager::OnCloseParent( RheiaFrameEvent& event )
{
    ///@todo here implement the check for closing all pages
    m_parent->RemoveEventHandler(this);
	
	RheiaPageInfoMap::iterator it = m_pages.begin();
	for( ; it != m_pages.end() ; ++it )
		if( it->second.container->DestroyOnClose() )
			delete it->second.container;
			
    event.Skip();
	m_window = NULL;
}

bool RheiaPageManager::AddPage( wxString name, RheiaPageContainer* container )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::AddPage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it != m_pages.end() )
        return false;

    if( container == NULL )
        return false;
	
	m_parent->Freeze();
    RheiaBookPage* page = container->BuildMainWindow( m_window );

    if( page == NULL ) {
		m_parent->Thaw();
        return false;
	}

    RheiaPageInfo info;

    info.name = name;
    info.container = container;
    info.page = page;
    info.bmp = container->GetBitmap( 16 );
	
    m_pages[name] = info;
	m_sizer->Add( page , 1 , wxALL | wxEXPAND , 0 );
	m_sizer->Hide(page,true);
    page->OnCreate();
	
	m_parent->Thaw();
    SendEvent(RheiaEVT_CENTER_PAGE_OPENED);
    return true;
}

bool RheiaPageManager::ActivatePage( const wxString& name )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::ActivatePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;
	
	
	m_parent->Freeze();
	RheiaPageInfo &info = it->second;
	
	RheiaPageInfoMap::iterator it2 = m_pages.begin();
	for( ; it2 != m_pages.end() ; ++it2 )
		m_sizer->Hide(it2->second.page,true);
		
	m_sizer->Show(info.page,true,true);
	
	m_parent->Thaw();
    SendEvent(RheiaEVT_CENTER_PAGE_ACTIVATED);
    return true;
}

bool RheiaPageManager::DeletePage( const wxString& name )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::DeletePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    if( !it->second.container->OnPageClosed() )
        return false;
	
	if( it->second.container->DestroyOnClose() )
		delete it->second.container;
		
    m_sizer->Remove( it->second.page );
	m_window->RemoveChild(it->second.page);
    m_pages.erase( it );

    return true;
}

bool RheiaPageManager::RemovePage( const wxString& name )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::DeletePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    if( !it->second.container->OnPageClosed() )
        return false;
	
	if( it->second.container->DestroyOnClose() )
		delete it->second.container;
		
    m_pages.erase( it );

    return true;
}

void RheiaPageManager::RenamePage( const wxString& oldName , const wxString& newName )
{
	if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::DeletePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( oldName );
    if( it == m_pages.end() )
        return;
		
	RheiaPageInfoMap::iterator it2 = m_pages.find( newName );
	if( it2 != m_pages.end() )
		return;

	RheiaPageInfo info = it->second;
    m_pages.erase( it );
	
	info.name = newName;
	m_pages[newName] = info;
    return;
}

bool RheiaPageManager::ClosePage( const wxString& name )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::ClosePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    if( !it->second.container->OnPageClosed() )
        return false;

    m_sizer->Hide(it->second.page,true);
    return true;
}

bool RheiaPageManager::PageExists( const wxString& name )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::PageExists call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    return true;
}

RheiaBookPage* RheiaPageManager::FindPageByName( const wxString& name )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::FindPageByName call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );

    if( it != m_pages.end() )
        return it->second.page;

    return NULL;
}

wxString RheiaPageManager::FindPageNameByObject( RheiaBookPage* page )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::FindPageNameByObject call Create Window with the proper window first") );

    if( page == NULL )
        return wxEmptyString;

    RheiaPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; it++ )
    {
        if( it->second.page == page )
            return it->first;
    }

    return wxEmptyString;
}

wxString RheiaPageManager::FindPageNameByContainer( RheiaPageContainer* container )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::FindPageNameByContainer call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; it++ )
    {
        if( it->second.container == container )
            return it->first;
    }

    return wxEmptyString;
}

RheiaBookPage* RheiaPageManager::FindPageByContainer( RheiaPageContainer* container )
{
    if( !m_window )
        RheiaThrow( wxT("RheiaPageManager::Error::FindPageByContainer call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; it++ )
    {
        if( it->second.container == container )
            return it->second.page;
    }

    return NULL;
}

void RheiaPageManager::SendEvent( const wxEventType& type )
{
    RheiaEvent event( type );
    m_parent->GetEventHandler()->ProcessEvent( event );
}
