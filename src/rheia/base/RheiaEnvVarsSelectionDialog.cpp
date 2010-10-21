/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaEnvVarsSelectionDialog.cpp
*
*   Dialog for environement variables configuration
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#include <RheiaEnvVarsSelectionDialog.h>
#include <RheiaEnvironementManager.h>

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
#include <wx/dirdlg.h>
#include <wx/imaglist.h>
#include <wx/settings.h>
#include <wx/stattext.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>

namespace
{
    int btnVarSelectDir = XRCID("btnVarSelectDir");
}

BEGIN_EVENT_TABLE(RheiaEnvVarsSelectionDialog,wxDialog)
    EVT_BUTTON( btnVarSelectDir , RheiaEnvVarsSelectionDialog::OnBrowse )
    EVT_UPDATE_UI(wxID_ANY , RheiaEnvVarsSelectionDialog::OnUpdateUI )
END_EVENT_TABLE()

RheiaEnvVarsSelectionDialog::RheiaEnvVarsSelectionDialog(wxWindow* parent):wxDialog()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgEnvVarsSel");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:envar_sel_dialog.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, xrcDialogName);

    wxButton *m_btnok = XRCCTRL(*this,"wxID_OK",wxButton);
    m_btnok->Enable(false);

    SetMinSize(wxSize(300,100));
    GetSizer()->SetSizeHints(this);
    CenterOnParent();
}

void RheiaEnvVarsSelectionDialog::OnUpdateUI(wxUpdateUIEvent& WXUNUSED(event))
{
    wxTextCtrl *m_txtkey = XRCCTRL(*this,"txtVarName",wxTextCtrl);
    wxTextCtrl *m_txtvalue = XRCCTRL(*this,"txtVarValue",wxTextCtrl);

    bool enable = (!m_txtkey->GetValue().IsEmpty()) && (!m_txtvalue->GetValue().IsEmpty());
    wxButton *m_btnok = XRCCTRL(*this,"wxID_OK",wxButton);
    m_btnok->Enable(enable);
}

void RheiaEnvVarsSelectionDialog::OnBrowse( wxCommandEvent& WXUNUSED(event) )
{
    wxDirDialog dialog(this, wxT("Choose a directory"));

    if( dialog.ShowModal() == wxID_CANCEL )
        return;

    wxString path = dialog.GetPath();

    wxTextCtrl *m_txtvalue = XRCCTRL(*this,"txtVarValue",wxTextCtrl);
    m_txtvalue->SetValue( path );
}

void RheiaEnvVarsSelectionDialog::EndModal(int retCode)
{
    wxTextCtrl *m_txtkey = XRCCTRL(*this,"txtVarName",wxTextCtrl);
    wxTextCtrl *m_txtvalue = XRCCTRL(*this,"txtVarValue",wxTextCtrl);

    m_key = m_txtkey->GetValue();
    m_value = m_txtvalue->GetValue();

    wxDialog::EndModal( retCode );
}

void RheiaEnvVarsSelectionDialog::SetKey( const wxString& name )
{
    wxTextCtrl *m_txtkey = XRCCTRL(*this,"txtVarName",wxTextCtrl);
    m_txtkey->SetValue( name );
}

void RheiaEnvVarsSelectionDialog::SetValue( const wxString& value )
{
    wxTextCtrl *m_txtvalue = XRCCTRL(*this,"txtVarValue",wxTextCtrl);
    m_txtvalue->SetValue( value );
}
