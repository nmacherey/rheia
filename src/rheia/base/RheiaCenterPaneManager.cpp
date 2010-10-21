/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaCenterPaneManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaCenterPaneManager.h>
#include <RheiaBookPage.h>
#include <RheiaPageContainer.h>
#include <RheiaException.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>
#include <RheiaCenterMgrSettingsPanel.h>
#include <RheiaConfigurationDialog.h>
#include <wx/aui/aui.h>
#include <wx/menu.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>::MgrNsMap locmap;

    int menuId = wxNewId();
}

/*! Global instance for the RheiaCenterPaneManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>::m_ns = locmap;

BEGIN_EVENT_TABLE( RheiaCenterPaneManager , RheiaBookManager )
    EVT_MENU( menuId , RheiaCenterPaneManager::OnConfigure )
END_EVENT_TABLE()

RheiaCenterPaneManager::RheiaCenterPaneManager(RheiaManagedFrame* parent):
    RheiaBookManager(parent)
{
    RegisterEvents();
}

RheiaCenterPaneManager::~RheiaCenterPaneManager()
{
}

void RheiaCenterPaneManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_CENTERMGR_SETTINGS_CHANGED, new RheiaEventFunctor<RheiaCenterPaneManager>(this, wxCommandEventHandler(RheiaCenterPaneManager::OnConfigChanged)));
}

void RheiaCenterPaneManager::OnConfigChanged(wxCommandEvent& WXUNUSED(event))
{
    if( m_book )
        ReloadConfiguration();
}

void RheiaCenterPaneManager::OnCreateWindow()
{
    ReloadConfiguration();
}

void RheiaCenterPaneManager::ReloadConfiguration()
{
    if( !m_book )
        RheiaThrow( wxT("RheiaCenterPaneManager::Error::ReloadConfiguration trying use the book but not created") );

    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("center_manager"));
    ReloadBookConfiguration(icfg);
}

void RheiaCenterPaneManager::BuildMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Append( menuId , wxT("&Center Window Settings") , wxT("Configure the center pane manager") );
    }
}

void RheiaCenterPaneManager::ReleaseMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnSettings = menuBar->GetMenu( idx );
        mnSettings->Delete( menuId );
    }
}

void RheiaCenterPaneManager::OnConfigure(wxCommandEvent& WXUNUSED(event))
{
    RheiaConfigurationDialog dialog( m_parent );
    RheiaCenterMgrSettingsPanel* m_panel = new RheiaCenterMgrSettingsPanel(&dialog);
    dialog.SetConfigurationTool( m_panel );
    dialog.ShowModal();
}
