/**
*   @file RheiaTextLoggerConfigurationPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include <RheiaTextLoggerConfigurationPanel.h>
#include <RheiaTextLogger.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>
#include <RheiaTextLoggerPage.h>
#include <RheiaConfigurationToolsManager.h>

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
#include <wx/sizer.h>
#include <wx/fontdlg.h>
#include <wx/choice.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaConfigurationToolsManager.h>
#include <RheiaConfigurationPanel.h>

REGISTER_LOGGER_CONFIGURATION_TOOL(RheiaTextLoggerConfigurationPanel)


namespace
{
    int lstTextLogLevels = XRCID("lstTextLogLevels");
    int btnTextFontChoose = XRCID("btnTextFontChoose");
    int btnTextColorChoose = XRCID("btnTextColorChoose");
    int btnTextBackColorChoose = XRCID("btnTextBackColorChoose");
    int chkTextLogUnderlined = XRCID("chkTextLogUnderlined");
    int cbTextAlignment = XRCID("cbTextAlignment");

    const wxString RheiaLogLevels[] = {
        wxT("message"),
        wxT("warning"),
        wxT("success"),
        wxT("error"),
        wxT("fatalerror"),
        wxT("info"),
        wxT("status"),
        wxT("syserror"),
        wxT("debug"),
        wxT("trace")
    };

    const wxString wxAlignmentOptions [] = {
        wxT("Left"),
        wxT("Right"),
        wxT("Center")
    };

    const wxTextAttrAlignment wxAlignmentFlags [] = {
        wxTEXT_ALIGNMENT_LEFT,
        wxTEXT_ALIGNMENT_RIGHT,
        wxTEXT_ALIGNMENT_CENTRE
    };

    const int noAlignments = sizeof( wxAlignmentOptions ) / sizeof( wxString );
};

BEGIN_EVENT_TABLE( RheiaTextLoggerConfigurationPanel , RheiaConfigurationPanel )
    EVT_LIST_ITEM_SELECTED( lstTextLogLevels , RheiaTextLoggerConfigurationPanel::OnListSelection )
    EVT_LIST_ITEM_ACTIVATED( lstTextLogLevels , RheiaTextLoggerConfigurationPanel::OnListSelection )

    EVT_BUTTON( btnTextFontChoose , RheiaTextLoggerConfigurationPanel::OnChooseFont )
    EVT_BUTTON( btnTextColorChoose , RheiaTextLoggerConfigurationPanel::OnChooseForegroundColor )
    EVT_BUTTON( btnTextBackColorChoose , RheiaTextLoggerConfigurationPanel::OnChooseBackgroundColor )

    EVT_CHOICE( cbTextAlignment , RheiaTextLoggerConfigurationPanel::OnChangeAlignment )
    EVT_CHECKBOX( chkTextLogUnderlined , RheiaTextLoggerConfigurationPanel::OnUnderlinedCheck )
END_EVENT_TABLE()


RheiaTextLoggerConfigurationPanel::RheiaTextLoggerConfigurationPanel( wxWindow* parent ):
    m_loggerpage(NULL)
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal | rspfDataUser );
    wxString xrcDialogName = _T("pnlTextLoggerConfig");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(path + _T("#zip:textlog_configuration_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);

    DoInitEnvironment();
}

void RheiaTextLoggerConfigurationPanel::DoInitEnvironment()
{
    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager( wxT("RheiaTextLogger") );
    bool isFirstTime = true;

    isFirstTime = (bool) cfg->ReadInt( wxT("/first_time") , (int) true );

    if( isFirstTime )
    {
        int size = 10;
        wxFont default_font(size, wxFONTFAMILY_SWISS , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        wxFont bold_font(size, wxFONTFAMILY_SWISS , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        wxFont italic_font(size, wxFONTFAMILY_SWISS , wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);

        bold_font.SetWeight(wxFONTWEIGHT_BOLD);

        wxFont bigger_font(bold_font);
        bigger_font.SetPointSize(size + 2);

        wxFont small_font(default_font);
        small_font.SetPointSize(size - 4);

        for(unsigned int i = 0; i < RheiaLogging::RheiaLogLevelNumber ; ++i)
        {
            m_textattr[i].SetFlags( wxTEXT_ATTR_FONT | wxTEXT_ATTR_ALIGNMENT );
            m_textattr[i].SetFont(default_font);
            m_textattr[i].SetAlignment(wxTEXT_ALIGNMENT_DEFAULT);
            m_textattr[i].SetTextColour(*wxBLACK);
            m_textattr[i].SetBackgroundColour(*wxWHITE);
        }

        m_textattr[RheiaLogging::warning].SetFont(italic_font);
        m_textattr[RheiaLogging::warning].SetTextColour(*wxBLUE);

        m_textattr[RheiaLogging::success].SetAlignment(wxTEXT_ALIGNMENT_CENTRE);
        bigger_font.SetUnderlined(true);
        m_textattr[RheiaLogging::success].SetFont(bigger_font);
        m_textattr[RheiaLogging::success].SetTextColour(*wxBLUE);

        m_textattr[RheiaLogging::error].SetFont(bold_font);
        m_textattr[RheiaLogging::error].SetTextColour(*wxRED);

        m_textattr[RheiaLogging::fatalerror].SetFont(bold_font);
        m_textattr[RheiaLogging::fatalerror].SetTextColour(*wxWHITE);
        m_textattr[RheiaLogging::fatalerror].SetBackgroundColour(*wxRED);

        m_textattr[RheiaLogging::syserror].SetFont(bold_font);
        m_textattr[RheiaLogging::syserror].SetTextColour(*wxWHITE);
        m_textattr[RheiaLogging::syserror].SetBackgroundColour(*wxBLUE);

        m_textattr[RheiaLogging::info].SetFont(italic_font);

        m_textattr[RheiaLogging::status].SetFont(bold_font);
        m_textattr[RheiaLogging::status].SetTextColour(*wxGREEN);

        m_textattr[RheiaLogging::debug].SetFont(italic_font);
        m_textattr[RheiaLogging::debug].SetTextColour(*wxGREEN);

        m_textattr[RheiaLogging::trace].SetFont(italic_font);
        m_textattr[RheiaLogging::trace].SetTextColour(*wxGREEN);


        cfg->Write( wxT("/message") , m_textattr[RheiaLogging::message] );
        cfg->Write( wxT("/warning") , m_textattr[RheiaLogging::warning] );
        cfg->Write( wxT("/success") , m_textattr[RheiaLogging::success] );
        cfg->Write( wxT("/error") , m_textattr[RheiaLogging::error] );
        cfg->Write( wxT("/fatalerror") , m_textattr[RheiaLogging::fatalerror] );
        cfg->Write( wxT("/info") , m_textattr[RheiaLogging::info] );
        cfg->Write( wxT("/status") , m_textattr[RheiaLogging::status] );
        cfg->Write( wxT("/syserror") , m_textattr[RheiaLogging::syserror] );
        cfg->Write( wxT("/debug") , m_textattr[RheiaLogging::debug] );
        cfg->Write( wxT("/trace") , m_textattr[RheiaLogging::trace] );
        cfg->Write( wxT("/first_time") , (int) false );

        return;
    }

    m_textattr[RheiaLogging::message] = cfg->ReadTextAttr( wxT("/message") );
    m_textattr[RheiaLogging::warning] = cfg->ReadTextAttr( wxT("/warning") );
    m_textattr[RheiaLogging::success] = cfg->ReadTextAttr( wxT("/success") );
    m_textattr[RheiaLogging::error] = cfg->ReadTextAttr( wxT("/error") );
    m_textattr[RheiaLogging::fatalerror] = cfg->ReadTextAttr( wxT("/fatalerror") );
    m_textattr[RheiaLogging::info] = cfg->ReadTextAttr( wxT("/info") );
    m_textattr[RheiaLogging::status] = cfg->ReadTextAttr( wxT("/status") );
    m_textattr[RheiaLogging::syserror] = cfg->ReadTextAttr( wxT("/syserror") );
    m_textattr[RheiaLogging::debug] = cfg->ReadTextAttr( wxT("/debug") );
    m_textattr[RheiaLogging::trace] = cfg->ReadTextAttr( wxT("/trace") );

    wxPanel* pnlSample = XRCCTRL( *this , "pnlTextSampleLog" , wxPanel );
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    // initialize the list
    for( int i = 0 ; i < RheiaLogging::RheiaLogLevelNumber ; ++i )
    {
        int idx = lst->InsertItem( i , RheiaLogLevels[i] );
        lst->SetItemData( idx , i );
    }

    int selection = 0;

    // Finally make the selection
    lst->SetItemState( selection , wxLIST_STATE_SELECTED , wxLIST_STATE_SELECTED );
    UpdateInfoFor( selection );

    // Create the sample panel
    m_loggerpage = new wxRichTextCtrl( pnlSample , wxID_ANY , wxEmptyString , wxDefaultPosition , wxDefaultSize , wxRE_READONLY | wxRE_MULTILINE );

    if( m_loggerpage != NULL )
    {
        wxSizer* sizer = pnlSample->GetSizer();
        sizer->Add( m_loggerpage , 1 , wxALL | wxEXPAND );
        sizer->Layout();
        UpdateSample();
    }
}

void RheiaTextLoggerConfigurationPanel::UpdateInfoFor( int selection )
{
    // Now Set the sample text for the given log
    wxStaticText* txtPreview = XRCCTRL(*this,"txtTextLogFontPreview",wxStaticText);
    txtPreview->SetLabel( wxT("This is the sample text !") );

    wxFont font = m_textattr[selection].GetFont();
    txtPreview->SetFont( font );

    // Now update the colors buttons
    wxColour foreground = m_textattr[selection].GetTextColour();
    wxColour background = m_textattr[selection].GetBackgroundColour();

    wxButton* btnForeground = XRCCTRL( *this , "btnTextColorChoose" , wxButton );
    wxButton* btnBackground = XRCCTRL( *this , "btnTextBackColorChoose" , wxButton );

    btnForeground->SetBackgroundColour( foreground );
    btnBackground->SetBackgroundColour( background );

    btnForeground->Refresh();
    btnBackground->Refresh();

    // Create the choice list with default styles
    wxChoice* cbAlignment = XRCCTRL( *this , "cbTextAlignment" , wxChoice );
    cbAlignment->Clear();

    int alignsel = 0;
    for( int i = 0 ; i < noAlignments ; ++i )
    {
        int align = m_textattr[selection].GetAlignment();

        if( align == wxAlignmentFlags[i] )
            alignsel = i;

        cbAlignment->Append( wxAlignmentOptions[i] );
    }

    cbAlignment->SetSelection(alignsel);

    wxCheckBox* chkUnderlined = XRCCTRL( *this , "chkTextLogUnderlined" , wxCheckBox );
    chkUnderlined->SetValue( font.GetUnderlined() );
}

void RheiaTextLoggerConfigurationPanel::UpdateSample()
{
    if( m_loggerpage == NULL )
        return;

    m_loggerpage->Clear();

    // initialize the list
    for( int i = 0 ; i < RheiaLogging::RheiaLogLevelNumber ; ++i )
    {
        wxString msg = wxT("This is the sample text for the level : ") + RheiaLogLevels[i];
        m_loggerpage->BeginStyle(m_textattr[i]);
        m_loggerpage->AppendText(msg);
        m_loggerpage->AppendText(wxT("\n"));
        m_loggerpage->EndStyle();
    }
}

void RheiaTextLoggerConfigurationPanel::UpdateFontFor( int selection , wxFont font )
{
    m_textattr[selection].SetFont( font );

    wxStaticText* txtPreview = XRCCTRL(*this,"txtTextLogFontPreview",wxStaticText);
    txtPreview->SetFont( font );
}

void RheiaTextLoggerConfigurationPanel::UpdateBackgroundColorFor( int selection , wxColour colour )
{
    m_textattr[selection].SetBackgroundColour( colour );
}

void RheiaTextLoggerConfigurationPanel::UpdateForegroundColorFor( int selection , wxColour colour )
{
    m_textattr[selection].SetTextColour( colour );
}

void RheiaTextLoggerConfigurationPanel::UpdateUnderlinedFor( int selection , bool underlined )
{
    wxFont font = m_textattr[selection].GetFont();
    font.SetUnderlined(underlined);
    m_textattr[selection].SetFont( font );
}

void RheiaTextLoggerConfigurationPanel::UpdateAlignmentFor( int selection , wxTextAttrAlignment align )
{
    m_textattr[selection].SetAlignment( align );
}

void RheiaTextLoggerConfigurationPanel::OnChooseFont( wxCommandEvent& event )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    long sel = -1;
    sel = lst->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel == -1)
        return;

    wxFont font = m_textattr[lst->GetItemData(sel)].GetFont();

    wxFontData data;
    data.SetInitialFont( font );

    wxFontDialog dialog( this , data );

    if( dialog.ShowModal() == wxID_OK )
    {
        font = dialog.GetFontData().GetChosenFont();
        UpdateFontFor( lst->GetItemData(sel) , font );
        UpdateSample();
    }
}

void RheiaTextLoggerConfigurationPanel::OnChooseForegroundColor( wxCommandEvent& event )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    long sel = -1;
    sel = lst->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel == -1)
        return;

    wxColourData data;
    wxButton* sender = XRCCTRL( *this , "btnTextColorChoose" , wxButton );
    data.SetColour(sender->GetBackgroundColour());

    wxColourDialog dlg(this, &data);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxColour colour = dlg.GetColourData().GetColour();
        sender->SetBackgroundColour(colour);

        UpdateForegroundColorFor( lst->GetItemData(sel) , colour );
        UpdateSample();
    }
}

void RheiaTextLoggerConfigurationPanel::OnChooseBackgroundColor( wxCommandEvent& event )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    long sel = -1;
    sel = lst->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel == -1)
        return;

    wxColourData data;
    wxButton* sender = XRCCTRL( *this , "btnTextBackColorChoose" , wxButton );
    data.SetColour(sender->GetBackgroundColour());

    wxColourDialog dlg(this, &data);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxColour colour = dlg.GetColourData().GetColour();
        sender->SetBackgroundColour(colour);

        UpdateBackgroundColorFor( lst->GetItemData(sel) , colour );
        UpdateSample();
    }
}

void RheiaTextLoggerConfigurationPanel::OnUnderlinedCheck( wxCommandEvent& event )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    long sel = -1;
    sel = lst->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel == -1)
        return;

    wxCheckBox* chkUnderlined = XRCCTRL( *this , "chkTextLogUnderlined" , wxCheckBox );
    UpdateUnderlinedFor( lst->GetItemData(sel) , chkUnderlined->GetValue() );
    UpdateSample();
}

void RheiaTextLoggerConfigurationPanel::OnChangeAlignment( wxCommandEvent& event )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    long sel = -1;
    sel = lst->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel == -1)
        return;

    wxChoice* cbAlignment = XRCCTRL( *this , "cbTextAlignment" , wxChoice );
    wxString choice = cbAlignment->GetStringSelection();

    for( int i = 0 ; i < noAlignments ; ++i )
    {
        if( wxAlignmentOptions[i].IsSameAs( choice ) )
        {
            UpdateAlignmentFor( lst->GetItemData(sel) , wxAlignmentFlags[i] );
            UpdateSample();
            return;
        }
    }
}

void RheiaTextLoggerConfigurationPanel::OnListSelection( wxListEvent& event )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstTextLogLevels" , wxListCtrl );

    long sel = -1;
    sel = lst->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (sel == -1)
        return;

    UpdateInfoFor( lst->GetItemData(sel) );
}


wxString RheiaTextLoggerConfigurationPanel::GetBitmapBaseName() const
{
    return wxEmptyString;
}

bool RheiaTextLoggerConfigurationPanel::OnApply()
{
    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager( wxT("RheiaTextLogger") );

    cfg->Write( wxT("/message") , m_textattr[RheiaLogging::message] );
    cfg->Write( wxT("/warning") , m_textattr[RheiaLogging::warning] );
    cfg->Write( wxT("/success") , m_textattr[RheiaLogging::success] );
    cfg->Write( wxT("/error") , m_textattr[RheiaLogging::error] );
    cfg->Write( wxT("/fatalerror") , m_textattr[RheiaLogging::fatalerror] );
    cfg->Write( wxT("/info") , m_textattr[RheiaLogging::info] );
    cfg->Write( wxT("/status") , m_textattr[RheiaLogging::status] );
    cfg->Write( wxT("/syserror") , m_textattr[RheiaLogging::syserror] );
    cfg->Write( wxT("/debug") , m_textattr[RheiaLogging::debug] );
    cfg->Write( wxT("/trace") , m_textattr[RheiaLogging::trace] );
    cfg->Write( wxT("/first_time") , (int) false );

    wxCommandEvent event(RheiaEVT_TXT_LOGGER_SETTINGS);
    RheiaEventsManager::Get()->ProcessEvent(event);

    return true;
}

bool RheiaTextLoggerConfigurationPanel::OnCancel()
{
    return true;
}
