/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */


#include "PyFindFilesDialog.h"


PyFindFilesDialog::PyFindFilesDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Text to search for :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer21->Add( m_staticText11, 0, wxALL, 5 );

	cbFindText = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer21->Add( cbFindText, 1, wxALL|wxEXPAND, 0 );

	bSizer20->Add( bSizer21, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 2, 8, 8 );
	fgSizer6->AddGrowableCol( 0 );
	fgSizer6->AddGrowableCol( 1 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxVERTICAL );

	chkWholeWord = new wxCheckBox( this, wxID_ANY, wxT("Whole word"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( chkWholeWord, 0, wxALL, 5 );

	chkStartWord = new wxCheckBox( this, wxID_ANY, wxT("Start Word"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer13->Add( chkStartWord, 0, wxALL, 5 );

	chkMatchCase = new wxCheckBox( this, wxID_ANY, wxT("Match case"), wxDefaultPosition, wxDefaultSize, 0 );
	chkMatchCase->SetValue(true);
	sbSizer13->Add( chkMatchCase, 0, wxALL, 5 );

	chkWrapAtEof = new wxCheckBox( this, wxID_ANY, wxT("Delete old search results"), wxDefaultPosition, wxDefaultSize, 0 );
	chkWrapAtEof->SetValue(true);
	sbSizer13->Add( chkWrapAtEof, 0, wxALL, 5 );

	fgSizer6->Add( sbSizer13, 1, wxALL|wxEXPAND, 5 );

	wxString rbScopeChoices[] = { wxT("Open files"), wxT("Search path") };
	int rbScopeNChoices = sizeof( rbScopeChoices ) / sizeof( wxString );
	rbScope = new wxRadioBox( this, wxID_ANY, wxT("Scope"), wxDefaultPosition, wxDefaultSize, rbScopeNChoices, rbScopeChoices, 1, wxRA_SPECIFY_COLS );
	rbScope->SetSelection( 0 );
	fgSizer6->Add( rbScope, 1, wxALL|wxEXPAND, 5 );

	bSizer20->Add( fgSizer6, 0, wxALL|wxEXPAND, 0 );

	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Search path") ), wxVERTICAL );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Path :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer26->Add( m_staticText14, 0, wxALL, 5 );

	txtPath = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtPath->Enable( false );

	bSizer26->Add( txtPath, 1, wxALL|wxEXPAND, 0 );

	btnSelPath = new wxButton( this, wxID_ANY, wxT("..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( btnSelPath, 0, wxALL, 0 );

	sbSizer16->Add( bSizer26, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Mask :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer27->Add( m_staticText15, 0, wxALL, 5 );

	txtMask = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtMask->Enable( false );

	bSizer27->Add( txtMask, 1, wxALL|wxEXPAND, 0 );

	sbSizer16->Add( bSizer27, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );


	bSizer28->Add( 50, 0, 0, wxEXPAND, 0 );

	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Example mask: *.py;*.html"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer28->Add( m_staticText17, 0, wxALL, 5 );

	sbSizer16->Add( bSizer28, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );

	chkRecursive = new wxCheckBox( this, wxID_ANY, wxT("Recurse subdirectories"), wxDefaultPosition, wxDefaultSize, 0 );
	chkRecursive->Enable( false );

	bSizer29->Add( chkRecursive, 1, wxALL|wxEXPAND, 5 );

	chkHiddenFiles = new wxCheckBox( this, wxID_ANY, wxT("Hidden files"), wxDefaultPosition, wxDefaultSize, 0 );
	chkHiddenFiles->Enable( false );

	bSizer29->Add( chkHiddenFiles, 0, wxALL, 5 );

	sbSizer16->Add( bSizer29, 0, wxEXPAND, 5 );

	bSizer20->Add( sbSizer16, 0, wxALL|wxEXPAND, 5 );

	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer20->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );

	m_sdbSizer5 = new wxStdDialogButtonSizer();
	m_sdbSizer5OK = new wxButton( this, wxID_OK , wxT("Find") );
	m_sdbSizer5->AddButton( m_sdbSizer5OK );
	m_sdbSizer5Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer5->AddButton( m_sdbSizer5Cancel );
	m_sdbSizer5->Realize();
	bSizer20->Add( m_sdbSizer5, 1, wxALL|wxEXPAND, 5 );

	this->SetSizer( bSizer20 );
	this->Layout();

	this->Centre( wxBOTH );
}

PyFindFilesDialog::~PyFindFilesDialog()
{
}

