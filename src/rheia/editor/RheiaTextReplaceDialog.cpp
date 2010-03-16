/**
*   @file RheiaTextReplaceDialog.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 13-March-2010
*/

#include "RheiaTextReplaceDialog.h"

RheiaTextReplaceDialog::RheiaTextReplaceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : 
	wxDialog( parent, id, title, pos, size, style ),
	m_applyAll(false),
	m_all(false)
{
	idAll = wxNewId();
	
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Would you like to replace this occurence ?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("(You can choose all if you want to replace all occurrencies of the word)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer1->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );
	
	m_chkAllDocuments = new wxCheckBox( this, wxID_ANY, wxT("Apply to all documents"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_chkAllDocuments, 0, wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnYes = new wxButton( this, wxID_YES, wxT("Yes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_btnYes, 0, wxALL, 0 );
	
	m_btnNo = new wxButton( this, wxID_NO, wxT("No"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_btnNo, 0, wxALL, 0 );
	
	m_btnCancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_btnCancel, 0, wxALL, 0 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnAll = new wxButton( this, idAll, wxT("All"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_btnAll, 0, wxALL, 0 );
	
	bSizer1->Add( bSizer2, 0, wxALL|wxEXPAND, 5 );
	
	// Connect Events
	m_btnAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RheiaTextReplaceDialog::OnApplyAll ), NULL, this );
	m_btnYes->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RheiaTextReplaceDialog::OnBtnClick ), NULL, this );
	m_btnNo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RheiaTextReplaceDialog::OnBtnNo ), NULL, this );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	bSizer1->SetSizeHints(this);
	this->Centre( wxBOTH );
}

RheiaTextReplaceDialog::~RheiaTextReplaceDialog()
{
}

void RheiaTextReplaceDialog::OnApplyAll( wxCommandEvent& WXUNUSED(event) )
{
	m_all = true;
	wxDialog::EndModal(wxYES);
}

void RheiaTextReplaceDialog::EndModal( int retCode )
{
	m_applyAll = m_chkAllDocuments->IsChecked();
	wxDialog::EndModal(retCode);
}

void RheiaTextReplaceDialog::OnBtnClick( wxCommandEvent& event )
{
	EndModal( wxYES );
}

void RheiaTextReplaceDialog::OnBtnNo( wxCommandEvent& event )
{
	EndModal( wxNO );
}
