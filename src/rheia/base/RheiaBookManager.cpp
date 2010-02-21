/**
*   @file RheiaBookManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaBookManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaBookPage.h>
#include <RheiaPageContainer.h>
#include <RheiaException.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>
#include <wx/aui/aui.h>

BEGIN_EVENT_TABLE( RheiaBookManager , wxEvtHandler )
    EVT_FRAME_CLOSING( RheiaBookManager::OnCloseParent )
END_EVENT_TABLE()

RheiaBookManager::RheiaBookManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_book(NULL),
    m_parent(parent),
    cbookId(wxNewId())
{
    if (m_parent)
    {
        // push ourself in the application's event handling chain...
        m_parent->PushEventHandler(this);
    }

    Connect( cbookId , wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE , wxAuiNotebookEventHandler(RheiaBookManager::OnPageClose) );
    Connect( cbookId , wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED , wxAuiNotebookEventHandler(RheiaBookManager::OnPageChanged) );
    Connect( cbookId , wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING , wxAuiNotebookEventHandler(RheiaBookManager::OnPageChanging) );
}

RheiaBookManager::~RheiaBookManager()
{
//    if (m_parent)
//    {
//		// remove ourself from the application's event handling chain...
//		m_parent->RemoveEventHandler(this);
//    }
}

wxAuiNotebook* RheiaBookManager::CreateWindow( wxWindow* parent )
{
    m_book = new wxAuiNotebook(parent, cbookId,
    wxDefaultPosition, wxDefaultSize,
    wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS );

    OnCreateWindow();

    return m_book;
}

void RheiaBookManager::ReloadBookConfiguration( RheiaConfigurationManager* cfg )
{
    long style = 0;
    style = style | ((cfg->ReadBool(_T("/notebook/tabs_on_top"), true) ) ? wxAUI_NB_BOTTOM : wxAUI_NB_TOP );
    style = style | ( cfg->ReadBool(_T("/notebook/allow_tab_split"), true) ? wxAUI_NB_TAB_SPLIT : 0);
    style = style | ( cfg->ReadBool(_T("/notebook/allow_tab_move"), true) ? wxAUI_NB_TAB_MOVE : 0);
    style = style | ( cfg->ReadBool(_T("/notebook/allow_tab_external_move"), true) ? wxAUI_NB_TAB_EXTERNAL_MOVE : 0);
    style = style | ( cfg->ReadBool(_T("/notebook/tab_has_scroll"), true) ? wxAUI_NB_SCROLL_BUTTONS : 0);
    style = style | ( cfg->ReadBool(_T("/notebook/tab_has_window_list"), true) ? wxAUI_NB_WINDOWLIST_BUTTON : 0);

    wxString closeBtn = cfg->Read(_T("/notebook/close_buttons") ) ;
    if ( closeBtn.IsSameAs(wxT("Place only on active tab") ) )
        style = style |  wxAUI_NB_CLOSE_ON_ACTIVE_TAB;
    else  if ( closeBtn.IsSameAs(wxT("Place on all tabs") ) )
        style = style |  wxAUI_NB_CLOSE_ON_ALL_TABS;
    else  if ( closeBtn.IsSameAs(wxT("Place on tabs caption") ) )
        style = style |  wxAUI_NB_CLOSE_BUTTON;

    wxAuiTabArt *tabArt;
    wxString TabArtName = cfg->Read(_T("/notebook/tabs_style"), _T("Default"));

    if ( TabArtName.IsSameAs( wxT("Default") ) )
    {
        tabArt = new wxAuiDefaultTabArt();
        m_book->SetArtProvider( tabArt );
    }
    else if ( TabArtName.IsSameAs( wxT("Smart") ) )
    {
        tabArt = new wxAuiSimpleTabArt();
        m_book->SetArtProvider( tabArt );
    }

    m_book->SetWindowStyleFlag( style );
}

void RheiaBookManager::OnCloseParent( RheiaFrameEvent& event )
{
    ///@todo here implement the check for closing all pages
    m_parent->RemoveEventHandler(this);

    Disconnect( cbookId , wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE , wxAuiNotebookEventHandler(RheiaBookManager::OnPageClose) );
    Disconnect( cbookId , wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED , wxAuiNotebookEventHandler(RheiaBookManager::OnPageChanged) );
    Disconnect( cbookId , wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING , wxAuiNotebookEventHandler(RheiaBookManager::OnPageChanging) );

    event.Skip();
}

bool RheiaBookManager::AddPage( wxString name, RheiaPageContainer* container )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::AddPage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it != m_pages.end() )
        return false;

    if( container == NULL )
        return false;

    RheiaBookPage* page = container->BuildMainWindow( m_book );

    if( page == NULL )
        return false;

    RheiaPageInfo info;

    info.name = name;
    info.container = container;
    info.page = page;
    info.bmp = container->GetBitmap( 16 );

    m_pages[name] = info;
    bool value = m_book->AddPage( page , name , true , info.bmp );

    page->OnCreate();
    SendEvent(RheiaEVT_CENTER_PAGE_OPENED);
    return value;
}

bool RheiaBookManager::ActivatePage( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::ActivatePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    int idx = m_book->GetPageIndex( it->second.page );

    if( idx == wxNOT_FOUND )
    {
        RheiaPageInfo &info = it->second;

        info.page = info.container->BuildMainWindow( m_book );
        info.bmp = info.container->GetBitmap( 16 );
        bool value = m_book->AddPage( info.page , info.name , true , info.bmp );
        info.page->OnCreate();
        SendEvent(RheiaEVT_CENTER_PAGE_OPENED);
    }

    idx = m_book->GetPageIndex( it->second.page );
    m_book->SetSelection( idx );
    SendEvent(RheiaEVT_CENTER_PAGE_ACTIVATED);
    return true;
}

bool RheiaBookManager::DeletePage( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::DeletePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    int idx = FindPageIndexByName( name );
    if( idx == wxNOT_FOUND )
        return false;

    if( !it->second.container->OnPageClosed() )
        return false;

    m_book->DeletePage( idx );
    m_pages.erase( it );

    return true;
}

bool RheiaBookManager::RemovePage( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::DeletePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    m_pages.erase( it );

    return true;
}

bool RheiaBookManager::ClosePage( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::ClosePage call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    int idx = FindPageIndexByName( name );
    if( idx == wxNOT_FOUND )
        return false;

    if( !it->second.container->OnPageClosed() )
        return false;

    m_book->DeletePage( idx );

    it->second.page = NULL;

    return true;
}

bool RheiaBookManager::PageIsOpened( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::PageIsOpened call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    int idx = FindPageIndexByName( name );
    if( idx == wxNOT_FOUND )
        return false;

    return true;
}

bool RheiaBookManager::PageExists( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::PageExists call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );
    if( it == m_pages.end() )
        return false;

    return true;
}

RheiaBookPage* RheiaBookManager::FindPageByName( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageByName call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );

    if( it != m_pages.end() )
        return it->second.page;

    return NULL;
}

int RheiaBookManager::FindPageIndexByName( const wxString& name )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageIndexByName call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.find( name );

    if( it == m_pages.end() || it->second.page == NULL )
        return wxNOT_FOUND;

    return m_book->GetPageIndex( it->second.page );
}

wxString RheiaBookManager::FindPageNameByObject( RheiaBookPage* page )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageNameByObject call Create Window with the proper window first") );

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

int RheiaBookManager::FindPageIndexByObject( RheiaBookPage* page )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageIndexByObject call Create Window with the proper window first") );

    if( page == NULL )
        return wxNOT_FOUND;

    return m_book->GetPageIndex( page );
}

wxString RheiaBookManager::FindPageNameByContainer( RheiaPageContainer* container )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageNameByContainer call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; it++ )
    {
        if( it->second.container == container )
            return it->first;
    }

    return wxEmptyString;
}

RheiaBookPage* RheiaBookManager::FindPageByContainer( RheiaPageContainer* container )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageByContainer call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; it++ )
    {
        if( it->second.container == container )
            return it->second.page;
    }

    return NULL;
}

int RheiaBookManager::FindPageIndexByContainer( RheiaPageContainer* container )
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::FindPageIndexByContainer call Create Window with the proper window first") );

    RheiaPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; it++ )
    {
        if( it->second.container == container )
            return m_book->GetPageIndex( it->second.page );
    }

    return NULL;
}

void RheiaBookManager::OnPageClose( wxAuiNotebookEvent& event )
{
    SendEvent(RheiaEVT_CENTER_PAGE_CLOSED);

    int index = event.GetSelection();
    RheiaBookPage* page = (RheiaBookPage*) m_book->GetPage( index );

    if( page == NULL )
        return;

    wxString name = FindPageNameByObject( page );

    DoPageClose(name);

    RheiaPageInfoMap::iterator it = m_pages.find( name );

    if( it != m_pages.end() )
    {
        if( !it->second.container->OnPageClosed() )
        {
            event.Veto();
            return;
        }
        it->second.page = NULL;
    }

    page->OnPageClosed();
}

void RheiaBookManager::OnPageChanging( wxAuiNotebookEvent& event )
{
}

wxString RheiaBookManager::GetActivePageName()
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::GetActivePageName call Create Window with the proper window first") );

    return m_book->GetPageText( m_book->GetSelection() );
}

RheiaBookPage* RheiaBookManager::GetActivePage()
{
    if( !m_book )
        RheiaThrow( wxT("RheiaBookManager::Error::GetActivePage call Create Window with the proper window first") );

    return (RheiaBookPage*) m_book->GetPage( m_book->GetSelection() );
}

void RheiaBookManager::OnPageChanged( wxAuiNotebookEvent& event )
{
    int index = event.GetOldSelection();
    RheiaBookPage* page = (RheiaBookPage*) m_book->GetPage( index );

    if( page != NULL && !page->OnPageChanging() )
    {
        event.Veto();
        return;
    }

    index = event.GetSelection();
    page = (RheiaBookPage*) m_book->GetPage( index );

    SendEvent(RheiaEVT_CENTER_PAGE_CHANGED);

    if( page != NULL )
        page->OnPageChanged();
}

void RheiaBookManager::SendEvent( const wxEventType& type )
{
    RheiaEvent event( type );
    m_parent->GetEventHandler()->ProcessEvent( event );
}

