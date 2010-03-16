/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaInfoMgrSettingsPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaInfoMgrSettingsPanel.h"

#include <wx/button.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>
#include <wx/colordlg.h>
#include <wx/msgdlg.h>
#include <wx/imaglist.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaProfileManager.h>
#include <RheiaInfoPaneManager.h>
#include <RheiaConfigurationToolsManager.h>
#include <RheiaBookConfigurationPanel.h>

REGISTER_CONFIGURATION_TOOL( RheiaInfoMgrSettingsPanel )

namespace
{

};

BEGIN_EVENT_TABLE(RheiaInfoMgrSettingsPanel,RheiaConfigurationPanel)
    //EVT_CHECKBOX(chkAutoHideLogs, RheiaInfoMgrSettingsPanel::OnAutoHideLogs)
END_EVENT_TABLE()

RheiaInfoMgrSettingsPanel::RheiaInfoMgrSettingsPanel( wxWindow* parent ):
    RheiaConfigurationPanel()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("panelInfoMgrSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:infomgrconf_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);
    DoInitEnvironment();

    GetSizer()->SetSizeHints(this);
}

void RheiaInfoMgrSettingsPanel::DoInitEnvironment()
{
    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("info_manager"));

    wxPanel* panel = XRCCTRL(*this,"pnlInfoMgrBook",wxPanel);
    m_panel = new RheiaBookConfigurationPanel(panel,icfg);
    panel->GetSizer()->Add( m_panel , 0 , wxALL | wxEXPAND );
    panel->GetSizer()->Layout();
}

void RheiaInfoMgrSettingsPanel::DoSaveEnvironment()
{
    m_panel->OnApply();
    wxCommandEvent event( RheiaEVT_INFOMGR_SETTINGS_CHANGED );
    RheiaEventsManager::Get()->ProcessEvent( event );
}

wxString RheiaInfoMgrSettingsPanel::GetBitmapBaseName() const
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    return path + wxT("#zip:infomgr_settings");
}

bool RheiaInfoMgrSettingsPanel::OnApply()
{
    DoSaveEnvironment();
    return true;
}

bool RheiaInfoMgrSettingsPanel::OnCancel()
{
    return true;
}


