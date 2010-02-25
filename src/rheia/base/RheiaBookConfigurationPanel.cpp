/**
*   @file RheiaBookConfigurationPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaBookConfigurationPanel.h"
#include "RheiaStandardPaths.h"
#include "RheiaConfigurationManager.h"

#include <wx/sizer.h>
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

RheiaBookConfigurationPanel::RheiaBookConfigurationPanel(wxWindow *parent,RheiaConfigurationManager* cfg):
    RheiaConfigurationPanel(),
    m_cfg(cfg)
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    wxString xrcName = _T("panelBookSettings");

    wxXmlResource *myres = wxXmlResource::Get();
    myres->LoadPanel(this, parent, xrcName);

    // Workspace manager
    XRCCTRL(*this, "cmbBookEditorTabs", wxComboBox)->SetStringSelection(m_cfg->Read(_T("/notebook/tabs_style"), _T("Default")));
    XRCCTRL(*this, "chkBookTabSplit", wxCheckBox)->SetValue( m_cfg->ReadBool(_T("/notebook/allow_tab_split"), true) );
    XRCCTRL(*this, "chkBookTabMove", wxCheckBox)->SetValue( m_cfg->ReadBool(_T("/notebook/allow_tab_move"), true) );
    XRCCTRL(*this, "chkBookTabExternalMove", wxCheckBox)->SetValue( m_cfg->ReadBool(_T("/notebook/allow_tab_external_move"), true) );
    XRCCTRL(*this, "chkBookBookScrollBtn", wxCheckBox)->SetValue( m_cfg->ReadBool(_T("/notebook/tab_has_scroll"), true) );
    XRCCTRL(*this, "chkBookBookWindowListBtn", wxCheckBox)->SetValue( m_cfg->ReadBool(_T("/notebook/tab_has_window_list"), true) );

    XRCCTRL(*this, "rbBookCloseButtons", wxRadioBox)->SetStringSelection( m_cfg->Read(_T("/notebook/close_buttons")) );
    XRCCTRL(*this, "rbBookTabsView", wxRadioBox)->SetSelection(m_cfg->ReadBool(_T("/notebook/tabs_on_top"), true) ? 1 : 0);
}

bool RheiaBookConfigurationPanel::OnApply()
{
    // Workspace manager page
    m_cfg->Write(_T("/notebook/tabs_style"),                        	          XRCCTRL(*this, "cmbBookEditorTabs", wxComboBox)->GetStringSelection() );
    m_cfg->Write(_T("/notebook/allow_tab_split"),                        	(bool) XRCCTRL(*this, "chkBookTabSplit", wxCheckBox)->GetValue());
    m_cfg->Write(_T("/notebook/allow_tab_move"),                      	(bool) XRCCTRL(*this, "chkBookTabMove", wxCheckBox)->GetValue());
    m_cfg->Write(_T("/notebook/allow_tab_external_move"),     	(bool) XRCCTRL(*this, "chkBookTabExternalMove", wxCheckBox)->GetValue());
    m_cfg->Write(_T("/notebook/tab_has_scroll"),                        		(bool) XRCCTRL(*this, "chkBookBookScrollBtn", wxCheckBox)->GetValue());
    m_cfg->Write(_T("/notebook/tab_has_window_list"),             	(bool) XRCCTRL(*this, "chkBookBookWindowListBtn", wxCheckBox)->GetValue());

    m_cfg->Write(_T("/notebook/tabs_on_top"),             ((bool) XRCCTRL(*this, "rbBookTabsView", wxRadioBox)->GetSelection()) ? true : false);
    m_cfg->Write(_T("/notebook/close_buttons"),             XRCCTRL(*this, "rbBookCloseButtons", wxRadioBox)->GetStringSelection() );

    return true;
}

bool RheiaBookConfigurationPanel::OnCancel()
{
    return true;
}
