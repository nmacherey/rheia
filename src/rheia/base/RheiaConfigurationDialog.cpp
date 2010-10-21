/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaConfigurationDialog.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 10-February-2010
*	@version 0.0.1
*/
#include <RheiaConfigurationDialog.h>
#include <RheiaConfigurationPanel.h>

#include <wx/sizer.h>
#include <wx/statline.h>

RheiaConfigurationDialog::RheiaConfigurationDialog(wxWindow* parent):
    wxDialog(parent,wxID_ANY,wxT("Configuration Dialog"),wxDefaultPosition,wxDefaultSize,wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX),
    m_panel(NULL)
{
}

void RheiaConfigurationDialog::SetConfigurationTool( RheiaConfigurationPanel* panel )
{
    if( m_panel != NULL )
        return;

    m_panel = panel;

    m_sizer = new wxBoxSizer(wxVERTICAL);
    m_sizer->Add( m_panel , 1 , wxALL | wxEXPAND , 8 );

    wxStdDialogButtonSizer* btnsizer = CreateStdDialogButtonSizer(wxOK|wxCANCEL);
    m_sizer->Add( new wxStaticLine(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLI_HORIZONTAL) , 0 , wxALL|wxEXPAND );
    m_sizer->Add( btnsizer , 0 , wxALL | wxEXPAND );

    SetSizer(m_sizer);
    m_sizer->SetSizeHints(this);

    CenterOnParent();
}

void RheiaConfigurationDialog::EndModal(int retCode)
{
    if( m_panel == NULL )
        wxDialog::EndModal(retCode);

    if( retCode == wxOK || retCode == wxID_OK )
        if(!m_panel->OnApply())
			return;
    else
        if(!m_panel->OnCancel())
			return;

    wxDialog::EndModal(retCode);
}
