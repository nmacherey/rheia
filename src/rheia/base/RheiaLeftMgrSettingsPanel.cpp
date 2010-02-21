/**
*   @file RheiaLeftMgrSettingsPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaLeftMgrSettingsPanel.h"

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

REGISTER_CONFIGURATION_TOOL( RheiaLeftMgrSettingsPanel )

namespace
{

};

BEGIN_EVENT_TABLE(RheiaLeftMgrSettingsPanel,RheiaConfigurationPanel)
    //EVT_CHECKBOX(chkAutoHideLogs, RheiaLeftMgrSettingsPanel::OnAutoHideLogs)
END_EVENT_TABLE()

RheiaLeftMgrSettingsPanel::RheiaLeftMgrSettingsPanel( wxWindow* parent ):
    RheiaConfigurationPanel()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("panelLeftMgrSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:leftmgrconf_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);
    DoInitEnvironment();

    GetSizer()->SetSizeHints(this);
}

void RheiaLeftMgrSettingsPanel::DoInitEnvironment()
{
    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("left_manager"));

    wxPanel* panel = XRCCTRL(*this,"pnlLeftMgrBook",wxPanel);
    m_panel = new RheiaBookConfigurationPanel(panel,icfg);
    panel->GetSizer()->Add( m_panel , 0 , wxALL | wxEXPAND );
    panel->GetSizer()->Layout();
}

void RheiaLeftMgrSettingsPanel::DoSaveEnvironment()
{
    m_panel->OnApply();
    wxCommandEvent event( RheiaEVT_LEFTMGR_SETTINGS_CHANGED );
    RheiaEventsManager::Get()->ProcessEvent( event );
}

wxString RheiaLeftMgrSettingsPanel::GetBitmapBaseName() const
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    return path + wxT("#zip:leftmgr_settings");
}

bool RheiaLeftMgrSettingsPanel::OnApply()
{
    DoSaveEnvironment();
    return true;
}

bool RheiaLeftMgrSettingsPanel::OnCancel()
{
    return true;
}



