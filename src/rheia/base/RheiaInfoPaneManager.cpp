/**
*   @file RheiaInfoPaneManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaInfoPaneManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaConfigurationDialog.h>
#include <RheiaInfoMgrSettingsPanel.h>
#include <RheiaInfoPage.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>
#include <wx/aui/aui.h>
#include <wx/menu.h>
#include <RheiaException.h>

namespace
{
    int idClear = wxNewId();
	int idCopySelectedToClipboard = wxNewId();
	int idCopyAllToClipboard = wxNewId();

	int menuId = wxNewId();
	int viewInfoBook = wxNewId();

	RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>::MgrNsMap locmap;
};

/*! Global instance for the RheiaInfoPaneManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>::m_ns = locmap;

BEGIN_EVENT_TABLE( RheiaInfoPaneManager , wxEvtHandler )
    EVT_MENU( menuId , RheiaInfoPaneManager::OnConfigureInfoWindow )

    EVT_UPDATE_UI(viewInfoBook, RheiaInfoPaneManager::OnToolsUpdateUI)
    EVT_MENU(viewInfoBook, RheiaInfoPaneManager::OnToggleMgtBook)
END_EVENT_TABLE()

RheiaInfoPaneManager::RheiaInfoPaneManager(RheiaManagedFrame* parent):
    RheiaBookManager(parent)
{
    RegisterEvents();
}

void RheiaInfoPaneManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_INFOMGR_SETTINGS_CHANGED, new RheiaEventFunctor<RheiaInfoPaneManager>(this, wxCommandEventHandler(RheiaInfoPaneManager::OnConfigChanged)));
}

void RheiaInfoPaneManager::OnConfigChanged(wxCommandEvent& event)
{
    if( m_book )
        ReloadConfiguration();
}

void RheiaInfoPaneManager::OnCreateWindow()
{
    ReloadConfiguration();
}

void RheiaInfoPaneManager::ReloadConfiguration()
{
    if( !m_book )
        RheiaThrow( wxT("RheiaInfoPaneManager::Error::ReloadConfiguration trying use the book but not created") );

    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("info_manager"));
    ReloadBookConfiguration(icfg);
}

void RheiaInfoPaneManager::BuildMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Append( menuId , wxT("&Information Window Settings") , wxT("Configure the information pane manager") );
    }

    idx = menuBar->FindMenu(wxT("View"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        mnEdit->AppendSeparator();
        m_menu = new wxMenu();
        mnEdit->AppendCheckItem(viewInfoBook,wxT("View Information Book\tF2"));
        m_item = mnEdit->AppendSubMenu( m_menu , wxT("&Information Book") );
    }
}

void RheiaInfoPaneManager::ReleaseMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Delete( menuId );
    }

    idx = menuBar->FindMenu(wxT("View"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        mnEdit->Delete( m_item );

        m_menu = NULL;
        m_item = NULL;

        m_pageIds.clear();
    }
}

void RheiaInfoPaneManager::OnConfigureInfoWindow(wxCommandEvent& event)
{
    RheiaConfigurationDialog dialog( m_parent );
    RheiaInfoMgrSettingsPanel* m_panel = new RheiaInfoMgrSettingsPanel(&dialog);
    dialog.SetConfigurationTool( m_panel );

    dialog.ShowModal();
}

RheiaInfoPaneManager::~RheiaInfoPaneManager()
{

}

bool RheiaInfoPaneManager::ActivatePage( const wxString& name )
{
    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    if( !m_layout->GetPane(m_book).IsShown() )
    {
        m_layout->GetPane(m_book).Show(true);
        m_layout->Update();
    }

    if( !RheiaBookManager::ActivatePage(name) )
        return false;

    return true;
}

bool RheiaInfoPaneManager::AddPage( wxString name, RheiaPageContainer* container )
{
    if( !RheiaBookManager::AddPage(name,container) )
        return false;

    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    if( !m_layout->GetPane(m_book).IsShown() )
    {
        m_layout->GetPane(m_book).Show(true);
        m_layout->Update();
    }

    if( m_menu == NULL )
        return true;

    m_pageIds[name] = wxNewId();
    m_menu->AppendCheckItem(m_pageIds[name],name,wxT("Display the page ") + name )->Check(true);
    Connect( m_pageIds[name] , wxEVT_COMMAND_MENU_SELECTED , wxCommandEventHandler(RheiaInfoPaneManager::OnSelectPageMenu) );
    Connect( m_pageIds[name] , wxEVT_UPDATE_UI , wxUpdateUIEventHandler(RheiaInfoPaneManager::OnToolsUpdateUI) );

    return true;
}

bool RheiaInfoPaneManager::DeletePage( const wxString& name )
{
    RheiaPageMenuIdMap::iterator it= m_pageIds.find(name);
    if( it != m_pageIds.end() )
    {
        m_menu->Delete(it->second);
        m_pageIds.erase(it);
    }

    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    if( m_book->GetPageCount() ==  1 )
    {
        m_layout->GetPane(m_book).Show(false);
        m_layout->Update();
    }

    return RheiaBookManager::DeletePage(name);
}

bool RheiaInfoPaneManager::ClosePage( const wxString& name )
{
    if( m_menu != NULL )
    {
        RheiaPageMenuIdMap::iterator it= m_pageIds.find(name);
        if( it != m_pageIds.end() )
            m_menu->FindItem(it->second)->Check(false);
    }

    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    if( m_book->GetPageCount() ==  1 )
    {
        m_layout->GetPane(m_book).Show(false);
        m_layout->Update();
    }

    return RheiaBookManager::ClosePage(name);
}

void RheiaInfoPaneManager::DoPageClose( const wxString& name )
{
    if( m_menu == NULL )
        return;

    RheiaPageMenuIdMap::iterator it= m_pageIds.find(name);
    if( it != m_pageIds.end() )
        m_menu->FindItem(it->second)->Check(false);

    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    if( m_book->GetPageCount() ==  1 )
    {
        m_layout->GetPane(m_book).Show(false);
        m_layout->Update();
    }
}

void RheiaInfoPaneManager::OnSelectPageMenu(wxCommandEvent& event)
{
    if( m_menu == NULL )
        return;

    RheiaPageMenuIdMap::iterator it= m_pageIds.begin();

    for( ; it != m_pageIds.end() ; ++it )
        if( it->second == event.GetId() )
        {
            if( !m_menu->FindItem(it->second)->IsChecked() )
            {
                ClosePage( it->first );
            }else
            {
                ActivatePage( it->first );
            }

            event.Skip();
            return;
        }

    event.Skip();
}

void RheiaInfoPaneManager::OnToolsUpdateUI( wxUpdateUIEvent& event )
{
    wxMenuBar* mbar = m_parent->GetMenuBar();
    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    mbar->Check(viewInfoBook, m_layout->GetPane(m_book).IsShown() );
    RheiaPageMenuIdMap::iterator tit = m_pageIds.begin();
    for( ; tit != m_pageIds.end() ; ++tit )
        mbar->Check(tit->second, PageIsOpened(tit->first) );
}

void RheiaInfoPaneManager::OnToggleMgtBook(wxCommandEvent& event)
{
    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    m_layout->GetPane(m_book).Show(!m_layout->GetPane(m_book).IsShown());

    m_layout->Update();
}
