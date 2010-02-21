
/**
*   @file RheiaWkspMgrSettingsPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaWkspMgrSettingsPanel.h"

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
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaPluginManager.h>
#include <RheiaProfileManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaConfigurationToolsManager.h>

REGISTER_CONFIGURATION_TOOL( RheiaWkspMgrSettingsPanel )

RheiaWkspMgrSettingsPanel::RheiaWkspMgrSettingsPanel( wxWindow* parent ):
    RheiaConfigurationPanel()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("panelWkspMgrSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:wkspmgrconf_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);
    DoInitEnvironment();
}

void RheiaWkspMgrSettingsPanel::DoInitEnvironment()
{
    RheiaConfigurationManager *wcfg = RheiaManager::Get()->GetConfigurationManager(_T("workspace_manager"));

    XRCCTRL(*this, "chkWksMgrHasBtn", wxCheckBox)->SetValue( wcfg->ReadBool(_T("/tree_ctrl/has_buttons"), true) );
    XRCCTRL(*this, "chkWksMgrHasLines", wxCheckBox)->SetValue( wcfg->ReadBool(_T("/tree_ctrl/has_lines"), false) );
    XRCCTRL(*this, "chkWksMgrHasLinesRoot", wxCheckBox)->SetValue( wcfg->ReadBool(_T("/tree_ctrl/has_lines_at_root"), true) );
    XRCCTRL(*this, "chkWksMgrRowLines", wxCheckBox)->SetValue( wcfg->ReadBool(_T("/tree_ctrl/has_row_lines"), false) );
}

void RheiaWkspMgrSettingsPanel::DoSaveEnvironment()
{
    RheiaConfigurationManager *wcfg = RheiaManager::Get()->GetConfigurationManager(_T("workspace_manager"));

    wcfg->Write(_T("/tree_ctrl/has_buttons"),                           (bool) XRCCTRL(*this, "chkWksMgrHasBtn", wxCheckBox)->GetValue());
    wcfg->Write(_T("/tree_ctrl/has_lines"),             (bool) XRCCTRL(*this, "chkWksMgrHasLines", wxCheckBox)->GetValue());
    wcfg->Write(_T("/tree_ctrl/has_lines_at_root"),                                     (bool) XRCCTRL(*this, "chkWksMgrHasLinesRoot", wxCheckBox)->GetValue());
    wcfg->Write(_T("/tree_ctrl/has_row_lines"),                 (bool) XRCCTRL(*this, "chkWksMgrRowLines", wxCheckBox)->GetValue());

    wxCommandEvent event( RheiaEVT_WKSPMGR_SETTINGS_CHANGED );
    RheiaEventsManager::Get()->ProcessEvent( event );
}

wxString RheiaWkspMgrSettingsPanel::GetBitmapBaseName() const
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    return path + wxT("#zip:wkspmgr_settings");
}

bool RheiaWkspMgrSettingsPanel::OnApply()
{
    DoSaveEnvironment();
    return true;
}

bool RheiaWkspMgrSettingsPanel::OnCancel()
{
    return true;
}

