/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#include <RheiaStatusBarManager.h>
#include <RheiaManager.h>

#include <wx/msgdlg.h>
#include <wx/frame.h>
#include <wx/string.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaStatusBarManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>::m_ns = locmap;

RheiaStatusBarManager::RheiaStatusBarManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_parent(parent)
{

}

RheiaStatusBarManager::~RheiaStatusBarManager()
{

}

/* Changes StatusBar m_workspace name */
void RheiaStatusBarManager::SetWorkspace( wxString workspace ){
	m_parent->SetStatusText(wxT("WORKSPACE : ") + workspace, 1);
	m_workspace = workspace;
}

/* Changes StatusBar m_workspace name */
void RheiaStatusBarManager::SetProject( wxString project ){
	m_parent->SetStatusText(wxT("PROJECT : ") + project, 2);
	m_project = project;
}

/* Changes StatusBar m_workspace name */
void RheiaStatusBarManager::Update(  ){
	m_parent->SetStatusText(wxT("Welcome to Rheia"), 0);
	m_parent->SetStatusText(wxT("WORKSPACE : ") + m_workspace, 1);
	m_parent->SetStatusText(wxT("PROJECT : ") + m_project, 2);
}
