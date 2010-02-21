/**
*   @file RheiaApplicationGeneralPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaApplicationGeneralPanel.h"

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

#include <RheiaManager.h>
#include <RheiaAppGlobals.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaConfigurationToolsManager.h>

REGISTER_CONFIGURATION_TOOL( RheiaApplicationGeneralPanel )

RheiaApplicationGeneralPanel::RheiaApplicationGeneralPanel( wxWindow* parent ):
    RheiaConfigurationPanel()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("panelApplicationSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:appconf_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);

    DoInitEnvironment();
}

void RheiaApplicationGeneralPanel::DoInitEnvironment()
{
    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();

    XRCCTRL(*this, "chkShowSplash", wxCheckBox)->SetValue(cfg->ReadBool(_T("/environment/show_splash"), true));
    XRCCTRL(*this, "chkSingleInstance", wxCheckBox)->SetValue(cfg->ReadBool(_T("/environment/single_instance"), false));
    XRCCTRL(*this, "chkShowStartPage", wxCheckBox)->SetValue(cfg->ReadBool(_T("/environment/show_start_here_page"), true));
    XRCCTRL(*this, "chkAssociations", wxCheckBox)->SetValue(cfg->ReadBool(_T("/environment/check_associations"), false));
    XRCCTRL(*this, "rbAppStart", wxRadioBox)->SetSelection(cfg->ReadBool(_T("/environment/blank_workspace"), false) ? 1 : 0);
    XRCCTRL(*this, "rbProjectOpen", wxRadioBox)->SetSelection(cfg->ReadBool(_T("/environment/new_window_workspace"), false) ? 0 :1);

    wxTextCtrl* txt = XRCCTRL(*this, "txtConsoleTerm", wxTextCtrl);
    txt->SetValue(cfg->Read(_T("/console_terminal"), DEFAULT_CONSOLE_TERM));

#ifdef __WXMSW__
    // under win32, this option is not needed, so disable it
    txt->Enable(false);
#endif
    txt = XRCCTRL(*this, "txtConsoleShell", wxTextCtrl);
    txt->SetValue(cfg->Read(_T("/console_shell"), DEFAULT_CONSOLE_SHELL));
#ifdef __WXMSW__
    // under win32, this option is not needed, so disable it
    txt->Enable(false);
#endif

#ifndef __WXMSW__
    XRCCTRL(*this, "chkAssociations", wxCheckBox)->Enable(false);
    XRCCTRL(*this, "btnSetAssocs", wxButton)->Enable(false);
    XRCCTRL(*this, "btnManageAssocs", wxButton)->Enable(false);
#endif
}

void RheiaApplicationGeneralPanel::DoSaveEnvironment()
{
    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();

    cfg->Write(_T("/environment/show_splash"),           ((bool) XRCCTRL(*this, "chkShowSplash", wxCheckBox)->GetValue()));
    cfg->Write(_T("/environment/single_instance"),       ((bool) XRCCTRL(*this, "chkSingleInstance", wxCheckBox)->GetValue()));
    cfg->Write(_T("/environment/check_associations"),    ((bool) XRCCTRL(*this, "chkAssociations", wxCheckBox)->GetValue()));
    cfg->Write(_T("/environment/show_start_here_page"),  ((bool) XRCCTRL(*this, "chkShowStartPage", wxCheckBox)->GetValue()));
    cfg->Write(_T("/environment/blank_workspace"),       ((bool) XRCCTRL(*this, "rbAppStart", wxRadioBox)->GetSelection()) ? true : false);
    cfg->Write(_T("/environment/new_window_workspace"),  ((bool) XRCCTRL(*this, "rbProjectOpen", wxRadioBox)->GetSelection()) ? false : true);
    cfg->Write(_T("/console_shell"),                            XRCCTRL(*this, "txtConsoleShell", wxTextCtrl)->GetValue());
    cfg->Write(_T("/console_terminal"),                         XRCCTRL(*this, "txtConsoleTerm", wxTextCtrl)->GetValue());
}

wxString RheiaApplicationGeneralPanel::GetBitmapBaseName() const
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    return path + wxT("#zip:general_settings");
}

bool RheiaApplicationGeneralPanel::OnApply()
{
    DoSaveEnvironment();
    return true;
}

bool RheiaApplicationGeneralPanel::OnCancel()
{
    return true;
}
