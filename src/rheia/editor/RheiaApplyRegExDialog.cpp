/**
*   @file RheiaApplyRegExDialog.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/

#include "RheiaApplyRegExDialog.h"
#include "RheiaManager.h"
#include "RheiaConfigurationManager.h"

RheiaApplyRegExDialog::RheiaApplyRegExDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) :
    wxDialog( parent, id, title, pos, size, style ),
    m_currentFile(false),
    m_selOnly(false),
    m_allFiles(false)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	cbRegEx = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_SIMPLE|wxTE_PROCESS_ENTER );
	bSizer18->Add( cbRegEx, 0, wxALL|wxEXPAND, 5 );

	cbReplacement = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
	bSizer18->Add( cbReplacement, 0, wxALL|wxEXPAND, 5 );

	wxString rbReApplyChoices[] = { wxT("Current file only"), wxT("All open files"), wxT("Selection") };
	int rbReApplyNChoices = sizeof( rbReApplyChoices ) / sizeof( wxString );
	rbReApply = new wxRadioBox( this, wxID_ANY, wxT("Apply to"), wxDefaultPosition, wxDefaultSize, rbReApplyNChoices, rbReApplyChoices, 1, wxRA_SPECIFY_COLS );
	rbReApply->SetSelection( 0 );
	bSizer18->Add( rbReApply, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Options") ), wxVERTICAL );

	chkReExtended = new wxCheckBox( this, wxID_ANY, wxT("Use extended regex syntax"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( chkReExtended, 0, wxALL, 5 );

	chkReAdvanced = new wxCheckBox( this, wxID_ANY, wxT("Use advanced regex syntax"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( chkReAdvanced, 0, wxALL, 5 );

	chkReBasic = new wxCheckBox( this, wxID_ANY, wxT("Use basic regex syntax"), wxDefaultPosition, wxDefaultSize, 0 );
	chkReBasic->SetValue(true);
	sbSizer11->Add( chkReBasic, 0, wxALL, 5 );

	chkReIgnore = new wxCheckBox( this, wxID_ANY, wxT("Ingore case in match"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( chkReIgnore, 0, wxALL, 5 );

	chkReNosub = new wxCheckBox( this, wxID_ANY, wxT("Only check match, don't set back references"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( chkReNosub, 0, wxALL, 5 );

	chkReNewline = new wxCheckBox( this, wxID_ANY, wxT("If not set, treat ':"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( chkReNewline, 0, wxALL, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("' as an ordinary character, otherwise it i special it is not match by '."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer19->Add( m_staticText9, 0, wxALIGN_LEFT|wxLEFT, 40 );


	bSizer19->Add( 0, 8, 1, wxEXPAND, 5 );

	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("' and '^' and '$' always match after/before it regardless of setting of start-end line options"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer19->Add( m_staticText10, 0, wxEXPAND|wxLEFT, 40 );


	bSizer19->Add( 0, 8, 1, wxEXPAND, 5 );

	sbSizer11->Add( bSizer19, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("start-end line options") ), wxVERTICAL );

	chkReStartLine = new wxCheckBox( this, wxID_ANY, wxT("'^' doesn't match at the start of line"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( chkReStartLine, 0, wxALL, 5 );

	chkReEnd = new wxCheckBox( this, wxID_ANY, wxT("'$' doesn't match at the end of line"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer12->Add( chkReEnd, 0, wxALL, 5 );

	sbSizer11->Add( sbSizer12, 1, wxEXPAND|wxLEFT, 40 );

	bSizer18->Add( sbSizer11, 0, wxALL|wxEXPAND, 5 );

	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer18->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	bSizer18->Add( m_sdbSizer2, 1, wxALL|wxEXPAND, 5 );

	RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("PyRegExDialog"));
	m_history = cfg->ReadArrayString( wxT("/regex/history") );
	m_rephistory = cfg->ReadArrayString( wxT("/regex/replacement_history") );

	cbRegEx->Append(m_history);
	cbReplacement->Append(m_rephistory);

#ifndef wxHAS_REGEX_ADVANCED
    chkReAdvanced->Enable(false);
#endif

	this->SetSizer( bSizer18 );
	this->Layout();
	
	bSizer18->SetSizeHints(this);
	this->Centre( wxBOTH );
}

RheiaApplyRegExDialog::~RheiaApplyRegExDialog()
{
}

void RheiaApplyRegExDialog::EndModal(int retCode)
{
    if( retCode == wxID_OK )
    {
        wxString value = cbRegEx->GetValue();
        if( value.IsEmpty() )
        {
            wxMessageBox( wxT("Cannot leave empty the regular expression...") , wxT("WARNING") , wxICON_ERROR , GetParent() );
            return;
        }

        m_replace = cbReplacement->GetValue();
        if( m_replace.IsEmpty() )
        {
            wxMessageBox( wxT("Cannot leave empty the replacement string...") , wxT("WARNING") , wxICON_ERROR , GetParent() );
            return;
        }

        int flag = 0;

        if( chkReExtended->IsChecked() )
            flag |=  wxRE_EXTENDED;

#ifdef wxHAS_REGEX_ADVANCED
        if( chkReAdvanced->IsChecked() )
            flag |= wxRE_ADVANCED;
#endif

        if( chkReBasic->IsChecked() )
            flag |=  wxRE_BASIC;

        if( chkReIgnore->IsChecked() )
            flag |=  wxRE_ICASE;

        if( chkReNosub->IsChecked() )
            flag |=  wxRE_NOSUB;

        if( chkReStartLine->IsChecked() )
            flag |=  wxRE_NOTBOL;

        if( chkReEnd->IsChecked() )
            flag |=  wxRE_NOTEOL;

        if( !m_regex.Compile(value,flag) )
        {
            wxMessageBox( wxT("Invalid regular expression please check...") , wxT("WARNING") , wxICON_ERROR , GetParent() );
            return;
        }

        if( rbReApply->GetSelection() == 0 )
            m_currentFile = true;
        else if( rbReApply->GetSelection() == 1 )
            m_allFiles = true;
        else if( rbReApply->GetSelection() == 2 )
            m_selOnly = true;

        m_flags = flag;
        m_expr = value;

        if( m_history.Index(m_expr) != wxNOT_FOUND )
            m_history.RemoveAt(m_history.Index(m_expr));

        m_history.Insert(m_expr,0);

        if( m_history.GetCount() > MAX_REGEX_HIST )
            m_history.RemoveAt(MAX_REGEX_HIST);

        if( m_rephistory.Index(m_replace) != wxNOT_FOUND )
            m_rephistory.RemoveAt(m_rephistory.Index(m_replace));

        m_rephistory.Insert(m_replace,0);

        if( m_rephistory.GetCount() > MAX_REGEX_HIST )
            m_rephistory.RemoveAt(MAX_REGEX_HIST);

        RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("PyRegExDialog"));
        cfg->Write( wxT("/regex/history") , m_history );
        cfg->Write( wxT("/regex/replacement_history") , m_rephistory );
    }

    wxDialog::EndModal(retCode);
}
