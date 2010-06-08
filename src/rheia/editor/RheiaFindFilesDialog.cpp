/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaFindFilesDialog.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaFindFilesDialog.h"
#include "RheiaManager.h"
#include "RheiaConfigurationManager.h"
#include "RheiaStandardPaths.h"

#include <wx/dirdlg.h>

RheiaFindFilesDialog::RheiaFindFilesDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	m_wholeWord = false;
	m_startWord = false;
	m_matchCase = false;
	m_wrapAtEOF = false;
	m_scope = 0;

	m_recursive = false;
	m_hiddenFiles = false;
	
	idRbScope = wxNewId();
	idSelectpath = wxNewId();
	
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

	wxString rbScopeChoices[] = { wxT("Current file") , wxT("Open files"), wxT("Search path") , wxT("Selection Only") };
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
	bSizer29->Add( chkRecursive, 1, wxALL|wxEXPAND, 5 );

	chkHiddenFiles = new wxCheckBox( this, wxID_ANY, wxT("Hidden files"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	//bSizer20->SetSizeHints(this);
	this->SetSize(wxSize(600,450));
	this->Centre( wxBOTH );
	
	rbScope->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED,wxCommandEventHandler(RheiaFindFilesDialog::OnScopeChange),NULL,this);
	btnSelPath->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(RheiaFindFilesDialog::OnBtnSearchPath),NULL,this);
	
	EnableSearchPaths( rbScope->GetSelection() == 2 );
	
	RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("FindFilesDialog"));
	m_history = cfg->ReadArrayString( wxT("/history") );
	
	cbFindText->Append(m_history);
}

RheiaFindFilesDialog::~RheiaFindFilesDialog()
{
}

void RheiaFindFilesDialog::EndModal( int retCode )
{
	if (retCode == wxID_OK)
    {
		m_expr = cbFindText->GetValue();
		
		if( m_expr.IsEmpty() )
		{
			wxMessageBox( wxT("Cannot leave empty find expression !") , wxT("warning") , wxICON_ERROR , this );
			return;
		}
		
		m_wholeWord = chkWholeWord->IsChecked();
		m_startWord = chkStartWord->IsChecked();
		m_matchCase = chkMatchCase->IsChecked();
		m_wrapAtEOF = chkWrapAtEof->IsChecked();
		m_scope = rbScope->GetSelection();
		
		m_path = txtPath->GetValue();
		m_masks = txtMask->GetValue();
		m_recursive = chkRecursive->IsChecked();
		m_hiddenFiles = chkHiddenFiles->IsChecked();
		
		if( m_history.Index(m_expr) != wxNOT_FOUND )
            m_history.RemoveAt(m_history.Index(m_expr));

        m_history.Insert(m_expr,0);

        if( m_history.GetCount() > MAX_FIND_HIST )
            m_history.RemoveAt(MAX_FIND_HIST);

        RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("FindFilesDialog"));
        cfg->Write( wxT("/history") , m_history );
	}
	wxDialog::EndModal(retCode);
}

void RheiaFindFilesDialog::OnScopeChange(wxCommandEvent& WXUNUSED(event))
{
	EnableSearchPaths( rbScope->GetSelection() == 2 );
}

void RheiaFindFilesDialog::OnBtnSearchPath(wxCommandEvent& WXUNUSED(event))
{
	wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("search_paths") )->Read( wxT("/last_path") , RheiaStandardPaths::HomeDirectory() );

	wxDirDialog dialog( m_parent,
						 wxT("Select the search path"),
						 LastOpenPath,
						 wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST );

	if ( dialog.ShowModal() == wxID_OK )
	{
		wxString path = dialog.GetPath();
		RheiaManager::Get()->GetConfigurationManager( wxT("search_paths") )->Write( wxT("/last_path") , path );
		txtPath->SetValue( path );
	}
	else
	{
		return;
	}
}

void RheiaFindFilesDialog::EnableSearchPaths(bool value)
{
	m_staticText14->Enable(value);
    txtPath->Enable(value);
    btnSelPath->Enable(value);
    m_staticText15->Enable(value);
    txtMask->Enable(value);

    m_staticText17->Enable(value);
    chkRecursive->Enable(value);
    chkHiddenFiles->Enable(value);
}