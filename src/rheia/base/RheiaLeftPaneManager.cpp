/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaLeftPaneManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaLeftPaneManager.h>
#include <RheiaBookPage.h>
#include <RheiaPageContainer.h>
#include <RheiaException.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>
#include <RheiaLeftMgrSettingsPanel.h>
#include <RheiaConfigurationDialog.h>
#include <wx/aui/aui.h>
#include <wx/menu.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaLeftPaneManager>::MgrNsMap locmap;
    int viewMgtBook = wxNewId();
    int menuId = wxNewId();
}

/*! Global instance for the RheiaLeftPaneManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaLeftPaneManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaLeftPaneManager>::m_ns = locmap;


BEGIN_EVENT_TABLE(RheiaLeftPaneManager,RheiaBookManager)
    EVT_UPDATE_UI(viewMgtBook, RheiaLeftPaneManager::OnToolsUpdateUI)
    EVT_MENU(viewMgtBook, RheiaLeftPaneManager::OnToggleMgtBook)

    EVT_MENU( menuId , RheiaLeftPaneManager::OnConfigure )
END_EVENT_TABLE()

RheiaLeftPaneManager::RheiaLeftPaneManager(RheiaManagedFrame* parent):
    RheiaBookManager(parent),
    m_menu(NULL)
{
    RegisterEvents();
}

RheiaLeftPaneManager::~RheiaLeftPaneManager()
{
}

void RheiaLeftPaneManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_LEFTMGR_SETTINGS_CHANGED, new RheiaEventFunctor<RheiaLeftPaneManager>(this, wxCommandEventHandler(RheiaLeftPaneManager::OnConfigChanged)));
}

void RheiaLeftPaneManager::BuildMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("View"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        mnEdit->AppendSeparator();
        m_menu = new wxMenu();
        mnEdit->AppendCheckItem(viewMgtBook,wxT("View Management Book\tShift-F2"));
        m_item = mnEdit->AppendSubMenu( m_menu , wxT("&Management Book") );
    }

    idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Append( menuId , wxT("&Management Window Settings") , wxT("Configure the management window") );
    }
}

void RheiaLeftPaneManager::OnConfigChanged(wxCommandEvent& WXUNUSED(event))
{
    if( m_book )
        ReloadConfiguration();
}

void RheiaLeftPaneManager::OnCreateWindow()
{
    ReloadConfiguration();
}

void RheiaLeftPaneManager::ReloadConfiguration()
{
    if( !m_book )
        RheiaThrow( wxT("RheiaLeftPaneManager::Error::ReloadConfiguration trying use the book but not created") );

    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("left_manager"));
    ReloadBookConfiguration(icfg);
}

void RheiaLeftPaneManager::OnConfigure(wxCommandEvent& WXUNUSED(event))
{
    RheiaConfigurationDialog dialog( m_parent );
    RheiaLeftMgrSettingsPanel* m_panel = new RheiaLeftMgrSettingsPanel(&dialog);
    dialog.SetConfigurationTool( m_panel );

    dialog.ShowModal();
}

void RheiaLeftPaneManager::ReleaseMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("View"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        mnEdit->Delete( m_item );

        m_menu = NULL;
        m_item = NULL;

        m_pageIds.clear();
    }

    idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Delete( menuId );
    }
}

bool RheiaLeftPaneManager::ActivatePage( const wxString& name )
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

bool RheiaLeftPaneManager::AddPage( wxString name, RheiaPageContainer* container )
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
    Connect( m_pageIds[name] , wxEVT_COMMAND_MENU_SELECTED , wxCommandEventHandler(RheiaLeftPaneManager::OnSelectPageMenu) );
    Connect( m_pageIds[name] , wxEVT_UPDATE_UI , wxUpdateUIEventHandler(RheiaLeftPaneManager::OnToolsUpdateUI) );
	
	return true;
}

bool RheiaLeftPaneManager::DeletePage( const wxString& name )
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

bool RheiaLeftPaneManager::ClosePage( const wxString& name )
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

void RheiaLeftPaneManager::DoPageClose( const wxString& name )
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

void RheiaLeftPaneManager::OnSelectPageMenu(wxCommandEvent& event)
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

void RheiaLeftPaneManager::OnToolsUpdateUI( wxUpdateUIEvent& WXUNUSED(event) )
{
    wxMenuBar* mbar = m_parent->GetMenuBar();
    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    mbar->Check(viewMgtBook, m_layout->GetPane(m_book).IsShown() );
    RheiaPageMenuIdMap::iterator tit = m_pageIds.begin();
    for( ; tit != m_pageIds.end() ; ++tit )
        mbar->Check(tit->second, PageIsOpened(tit->first) );
}

void RheiaLeftPaneManager::OnToggleMgtBook(wxCommandEvent& WXUNUSED(event))
{
    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    m_layout->GetPane(m_book).Show(!m_layout->GetPane(m_book).IsShown());

    m_layout->Update();
}
