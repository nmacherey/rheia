/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaCenterPageManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaCenterPageManager.h>
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
    RheiaMgr<RheiaManagedFrame,RheiaCenterPageManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaCenterPageManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaCenterPageManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaCenterPageManager>::m_ns = locmap;

BEGIN_EVENT_TABLE( RheiaCenterPageManager , RheiaPageManager )

END_EVENT_TABLE()

RheiaCenterPageManager::RheiaCenterPageManager(RheiaManagedFrame* parent):
    RheiaPageManager(parent)
{
    RegisterEvents();
}

RheiaCenterPageManager::~RheiaCenterPageManager()
{
}

void RheiaCenterPageManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
}

void RheiaCenterPageManager::OnCreateWindow()
{
}

void RheiaCenterPageManager::ReloadConfiguration()
{
}

void RheiaCenterPageManager::BuildMenu( wxMenuBar* menuBar )
{

}

void RheiaCenterPageManager::ReleaseMenu( wxMenuBar* menuBar )
{

}
