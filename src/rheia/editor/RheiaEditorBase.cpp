/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaEditorBase.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaEditorBase.h"

namespace
{
    int idSplit = wxNewId();
}

BEGIN_EVENT_TABLE(RheiaEditorBase,RheiaBookPage)
    EVT_CONTEXT_MENU(RheiaEditorBase::OnRequestContextMenu)
END_EVENT_TABLE()

RheiaEditorBase::RheiaEditorBase( RheiaManagedFrame* toplevel, wxWindow* parent , RheiaEditorFile* container , RheiaEditorLayout* context ):
    RheiaBookPage(parent),
    m_container(container),
    m_parent(toplevel),
    m_context(context)
{
    wxPanel::Create(parent,wxID_ANY);
	
	m_lastFindPos = -1;
	
    idCloseMe               = wxNewId();
    idCloseAll              = wxNewId();
    idCloseAllOthers        = wxNewId();
    idSaveMe                = wxNewId();
    idSaveAs                = wxNewId();
    idSaveAll               = wxNewId();
    idSplitHoriz            = wxNewId();
    idSplitVertical         = wxNewId();
    idUnsplit               = wxNewId();
    idUndo                  = wxNewId();
    idRedo                  = wxNewId();
    idCut                   = wxNewId();
    idCopy                  = wxNewId();
    idPaste                 = wxNewId();
    idDelete                = wxNewId();
    idClearHistory          = wxNewId();
    idSelectAll             = wxNewId();
    idSelectLine            = wxNewId();
    idFind                  = wxNewId();
    idFindNext              = wxNewId();
    idReplace               = wxNewId();
    idReplaceNext           = wxNewId();
    idToggleBookMark        = wxNewId();
    idNextBookmark          = wxNewId();
    idPreviousBookMark      = wxNewId();
    idAutoFormatSel         = wxNewId();
    idAutoFormatAll         = wxNewId();
    idConfigure             = wxNewId();
    idProperties            = wxNewId();
    idFoldAll               = wxNewId();
    idUnfoldAll             = wxNewId();
    idToggleAllFolds        = wxNewId();
    idFoldCurrentBlock      = wxNewId();
    idUnfoldCurrentBlock    = wxNewId();
    idToggleCurrentBlockFold= wxNewId();
    idCommentSel            = wxNewId();
    idUncommentSel          = wxNewId();

    Registerevents();
    RegisterSTCEvents();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    m_control = new wxStyledTextCtrl( this, m_ID, wxPoint(10,10), wxSize(200,200), 0, wxEmptyString );
    Reload();
    sizer->Add( m_control, 1, wxEXPAND | wxALL, 5 );
    this->SetSizer( sizer );
    this->Layout();
}

RheiaEditorBase::~RheiaEditorBase()
{
	delete m_context;
}

void RheiaEditorBase::SetContext(RheiaEditorLayout* context)
{
	delete m_context;
	m_context = context;
	
	Reload();
}

void RheiaEditorBase::Reload()
{
    m_control->SetLexer(m_context->GetLexer());
    wxArrayString kw = m_context->GetKeywords();

    for( unsigned int i = 0; i < kw.GetCount() ; ++i )
        m_control->SetKeyWords(i,kw[i]);

    m_control->SetViewEOL( m_context->ViewEOL() );
    m_control->SetViewWhiteSpace( m_context->ViewWhiteSpace() );
    m_control->SetMarginWidth( 2, 0 );

    m_control->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
    m_control->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
    m_control->SetMarginWidth( 1, 16);
    m_control->SetMarginSensitive( 1, true );

    wxStcPropertyMap props = m_context->GetPropertyMap();
    wxStcPropertyMap::iterator it = props.begin();
    for(; it != props.end() ; ++it )
        m_control->SetProperty( it->first, it->second );

    m_control->SetModEventMask ( m_context->GetModEventMask() );
    m_control->SetXCaretPolicy( m_context->GetXCaretPolicy() , m_context->GetXCaretZone() );
    m_control->SetYCaretPolicy( m_context->GetYCaretPolicy() , m_context->GetYCaretZone() );
    m_control->SetFoldFlags( m_context->GetFoldFlags() );

    m_control->SetMarginType(SYMBOLS_MARGIN_ID, wxSTC_MARGIN_SYMBOL);
    m_control->SetMarginType(NUMBER_MARGIN_ID, wxSTC_MARGIN_NUMBER);
    m_control->SetMarginType(EDIT_TRACKER_MARGIN_ID, 4); // Styled Text margin
    m_control->SetMarginWidth(EDIT_TRACKER_MARGIN_ID, 3 );
    m_control->SetMarginMask(EDIT_TRACKER_MARGIN_ID, 0);

    // Separators
    m_control->SetMarginType(SYMBOLS_MARGIN_SEP_ID, wxSTC_MARGIN_FORE);
    m_control->SetMarginMask(SYMBOLS_MARGIN_SEP_ID, 0);

    // Fold margin - allow only folder symbols to display
    m_control->SetMarginMask(FOLD_MARGIN_ID, wxSTC_MASK_FOLDERS);
    // Set margins' width
    m_control->SetMarginWidth(SYMBOLS_MARGIN_ID, 16);	// Symbol margin

    // If the symbols margin is hidden, hide its related separator margin
    // as well
    m_control->SetMarginWidth(SYMBOLS_MARGIN_SEP_ID, 1);	// Symbol margin which acts as separator

    // allow everything except for the folding symbols
    m_control->SetMarginMask(SYMBOLS_MARGIN_ID, ~(wxSTC_MASK_FOLDERS));

    // Line number margin
#ifdef __WXMSW__
    int pixelWidth = 4 + 5*m_control->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("9"));
#else
    int pixelWidth = 4 + 5*8;
#endif

    // Show number margin according to settings.
    m_control->SetMarginWidth(NUMBER_MARGIN_ID, pixelWidth);

    // Show the fold margin
    m_control->SetMarginWidth(FOLD_MARGIN_ID, 12);	// Fold margin

    // Mark fold margin & symbols margins as sensetive
    m_control->SetMarginSensitive(FOLD_MARGIN_ID, true);
    m_control->SetMarginSensitive(SYMBOLS_MARGIN_ID, true);

    m_control->SetEdgeMode(m_context->GetEdgeMode());
    m_control->SetEdgeColour(m_context->GetEdgeColour());
    m_control->SetEdgeColumn(m_context->GetEdgeColumn() );
    wxString foldstyle = m_context->GetFoldStyle();

    //---------------------------------------------------
    // Fold settings
    //---------------------------------------------------
    // Define the folding style to be square
    if ( foldstyle == wxT("Flatten Tree Square Headers") )
    {
        DefineMarker(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_VLINE, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_LCORNER, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUSCONNECTED, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUSCONNECTED, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));

    }
    else if ( foldstyle == wxT("Flatten Tree Circular Headers") )
    {
        DefineMarker(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_CIRCLEMINUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_CIRCLEPLUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_VLINE, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_LCORNERCURVE, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_CIRCLEPLUSCONNECTED, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_CIRCLEMINUSCONNECTED, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));

    }
    else if ( foldstyle == wxT("Simple") )
    {
        DefineMarker(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_MINUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_PLUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_BACKGROUND, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_BACKGROUND, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_PLUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_MINUS, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_BACKGROUND, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));

    }
    else if ( foldstyle == wxT("Arrows with Background Colour") )
    {

        wxColour bgcol = wxColor(0x80, 0x80, 0x80);

        DefineMarker(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_FULLRECT, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_FULLRECT, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_ARROW, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_FULLRECT, wxColor(0xff, 0xff, 0xff), bgcol);
    }
    else if ( foldstyle == wxT("Simple with Background Colour") )
    {

        wxColour bgcol = wxColor(0x80, 0x80, 0x80);

        DefineMarker(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_MINUS, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_PLUS, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_FULLRECT, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_FULLRECT, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_PLUS, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_MINUS, wxColor(0xff, 0xff, 0xff), bgcol);
        DefineMarker(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_FULLRECT, wxColor(0xff, 0xff, 0xff), bgcol);

    }
    else if ( foldstyle == wxT("Arrows") )
    {
        DefineMarker(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_BACKGROUND, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_BACKGROUND, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_ARROW, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));
        DefineMarker(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_BACKGROUND, wxColor(0xff, 0xff, 0xff), wxColor(0x80, 0x80, 0x80));

    }

    m_control->MarkerDefine(BOOKMARK_MARKER, BOOKMARK_STYLE);

#if defined(__WXMAC__)
    // turning off these two greatly improves performance
    // on Mac
    m_control->SetTwoPhaseDraw(false);
    m_control->SetBufferedDraw(false);

#elif defined(__WXGTK__)
    m_control->SetTwoPhaseDraw(true);
    m_control->SetBufferedDraw(false);

#else // MSW
    m_control->SetTwoPhaseDraw(true);
    m_control->SetBufferedDraw(true);
#endif
    //m_control->SetInidicatorValue(MATCH_INDICATOR,    1);
    //m_control->SetInidicatorValue(DEBUGGER_INDICATOR, 1);
    m_control->SendMsg(2510,1,1);
    m_control->SendMsg(2510,2,1);
    m_control->SendMsg(2510,MATCH_INDICATOR,1);
    m_control->SendMsg(2510,DEBUGGER_INDICATOR,1);
    m_control->SendMsg(2510,HYPERLINK_INDICATOR,1);

    m_control->SendMsg(2502,MATCH_INDICATOR,1);
    m_control->SendMsg(2502,DEBUGGER_INDICATOR,1);

    wxColour col(*wxLIGHT_GREY);
    m_control->IndicatorSetForeground(1, col);
    m_control->IndicatorSetForeground(2, col);
    m_control->IndicatorSetStyle     (HYPERLINK_INDICATOR, wxSTC_INDIC_PLAIN);
    m_control->IndicatorSetStyle     (MATCH_INDICATOR, wxSTC_INDIC_BOX);
    m_control->IndicatorSetForeground(MATCH_INDICATOR, wxT("GREY"));
    m_control->IndicatorSetStyle     (DEBUGGER_INDICATOR, wxSTC_INDIC_BOX);
    m_control->IndicatorSetForeground(DEBUGGER_INDICATOR, wxT("GREY"));

    m_control->IndicatorSetForeground(USER_INDICATOR, wxT("RED"));
    m_control->IndicatorSetStyle(USER_INDICATOR, wxSTC_INDIC_SQUIGGLE);
    m_control->SendMsg(2510,USER_INDICATOR,1);

    //indentation settings
    m_control->SetTabIndents(m_context->TabIndents());
    m_control->SetBackSpaceUnIndents (m_context->BackspaceUnIndents());
    m_control->SetUseTabs(m_context->UseTabs());
    m_control->SetTabWidth(m_context->TabWidth());
    m_control->SetIndent(m_context->GetIndents());
    m_control->SetIndentationGuides( m_context->GetIndentationGuides() );
    m_control->SetLayoutCache(m_context->GetLayoutCache());

    m_control->StyleClearAll();
    m_context->SetStyles( m_control );
    m_control->UsePopUp(false);
}

void RheiaEditorBase::Registerevents()
{
    Connect(idCloseMe,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnCloseMe));
    Connect(idCloseAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnCloseAll));
    Connect(idCloseAllOthers,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnCloseAllButMe));
    Connect(idSaveMe,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnSameMe));
    Connect(idSaveAs,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnSaveMeAs));
    Connect(idSaveAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnSaveAll));

    Connect(idSplitHoriz,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idSplitVertical,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idUnsplit,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idUndo,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idRedo,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idCut,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idCopy,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idPaste,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idDelete,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idClearHistory,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idSelectAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idSelectLine,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idFind,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idFindNext,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idReplace,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idReplaceNext,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idToggleBookMark,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idNextBookmark,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idPreviousBookMark,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idAutoFormatSel,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idAutoFormatAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idFoldAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idUnfoldAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idToggleAllFolds,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idFoldCurrentBlock,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idUnfoldCurrentBlock,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idToggleCurrentBlockFold,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idCommentSel,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));
    Connect(idUncommentSel,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnContextMenu));

    Connect(idConfigure,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnConfigureEditor));
    Connect(idProperties,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorBase::OnFileProperties));
}

void RheiaEditorBase::OnRequestContextMenu( wxContextMenuEvent& event )
{
    wxMenu* m_menu = BuilContextMenu();

    int mx = wxGetMousePosition().x - this->GetScreenPosition().x;
    int my = wxGetMousePosition().y - this->GetScreenPosition().y;

    wxPoint pos(mx,my);

    PopupMenu( m_menu , pos );
}

void RheiaEditorBase::DefineMarker(int marker, int markerType, wxColor fore, wxColor back)
{
    m_control->MarkerDefine(marker, markerType);
    m_control->MarkerSetForeground(marker, fore);
    m_control->MarkerSetBackground(marker, back);
}

bool RheiaEditorBase::GetModified()
{
    return m_control->GetModify();
}

bool RheiaEditorBase::Save( const wxString& filename )
{
    return m_control->SaveFile(filename);
}

bool RheiaEditorBase::Load( const wxString& filename )
{
    return m_control->LoadFile(filename);
}

wxMenu* RheiaEditorBase::BuilContextMenu()
{
    wxMenu* m_menu = new wxMenu();;
    m_menu->Append( idCloseMe , wxT("&Close...") , wxT("Close me ..."));
    m_menu->Append( idCloseAll , wxT("C&lose all...") , wxT("Close all ..."));
    m_menu->Append( idCloseAllOthers , wxT("Close &all Others...") , wxT("Close all others..."));
    m_menu->AppendSeparator();
    m_menu->Append( idSaveMe , wxT("&Save...") , wxT("Save me ..."));
    m_menu->Append( idSaveAs , wxT("Save as...") , wxT("Save me in a new file..."));
    m_menu->Append( idSaveAll , wxT("Sa&ve all...") , wxT("Save all ..."));

    wxMenu* mnSplit = new wxMenu();
    mnSplit->Append( idSplitHoriz , wxT("Split horizontally") );
    mnSplit->Append( idSplitVertical , wxT("Split horizontally") );
    mnSplit->AppendSeparator( );
    mnSplit->Append( idUnsplit , wxT("Unsplit") );

    mnSplit->Enable(idSplitHoriz,!IsSplitted());
    mnSplit->Enable(idSplitVertical,!IsSplitted());
    mnSplit->Enable(idUnsplit,IsSplitted());

    m_menu->AppendSeparator();
    m_menu->Append(idSplit,wxT("Split view"),mnSplit);
    m_menu->Enable(idSplit,CanSplit());

    /*** Build the edit part for the menu */
    wxMenu* mnEdit = new wxMenu();

    mnEdit->Append(idUndo,wxT("Undo"));
    mnEdit->Append(idRedo,wxT("Redo"));
    mnEdit->Append(idClearHistory,wxT("Clear history"));
    mnEdit->AppendSeparator();
    mnEdit->Append(idCut,wxT("Cut"));
    mnEdit->Append(idCopy,wxT("Copy"));
    mnEdit->Append(idPaste,wxT("Paste"));
    mnEdit->Append(idDelete,wxT("Delete"));
    mnEdit->AppendSeparator();
    mnEdit->Append(idSelectAll,wxT("Select all"));
    mnEdit->Append(idSelectLine,wxT("Select line"));

    mnEdit->Enable(idUndo,CanUndo());
    mnEdit->Enable(idRedo,CanRedo());
    mnEdit->Enable(idClearHistory,CanClearHistory());
    mnEdit->Enable(idCut,CanCut());
    mnEdit->Enable(idCopy,CanCopy());
    mnEdit->Enable(idPaste,CanPaste());
    mnEdit->Enable(idDelete,CanDelete());
    mnEdit->Enable(idSelectAll,CanSelectAll());
    mnEdit->Enable(idSelectLine,CanSelectLine());

    m_menu->AppendSeparator();
    m_menu->Append(wxID_ANY,wxT("Edit"),mnEdit);

    /*** Build the find and replace part for the menu */
    wxMenu* mnFind = new wxMenu();

    mnFind->Append(idFind,wxT("Find"));
    mnFind->Append(idFindNext,wxT("Find Next"));
    mnFind->Append(idFind,wxT("Replace"));
    mnFind->Append(idFind,wxT("Replace Next"));

    m_menu->Append(wxID_ANY,wxT("Find"),mnFind);

    /*** Build the bookmark part for the menu */
    wxMenu* mnBookmarks = new wxMenu();

    mnBookmarks->Append(idToggleBookMark,wxT("Toggle bookmark"));
    mnBookmarks->Append(idNextBookmark,wxT("Next bookmark"));
    mnBookmarks->Append(idPreviousBookMark,wxT("Previous bookmark"));

    m_menu->Append(wxID_ANY,wxT("Bookmarks"),mnBookmarks);

    /*** Build autoformating part for the menu */
    wxMenu* mnAutoformat = new wxMenu();

    mnAutoformat->Append(idAutoFormatSel,wxT("Format selection"));
    mnAutoformat->Append(idAutoFormatAll,wxT("Format all"));

    m_menu->Append(wxID_ANY,wxT("Autoformat"),mnAutoformat);

    /*** Build the folding part for the menu */
    wxMenu* mnFold = new wxMenu();

    mnFold->Append(idFoldAll,wxT("Fold all"));
    mnFold->Append(idUnfoldAll,wxT("Unfold all"));
    mnFold->Append(idToggleAllFolds,wxT("Toggle all folds"));
    mnFold->AppendSeparator();
    mnFold->Append(idFoldCurrentBlock,wxT("Fold current block"));
    mnFold->Append(idUnfoldCurrentBlock,wxT("Unfold current block"));
    mnFold->Append(idToggleCurrentBlockFold,wxT("Toggle current block fold"));

    m_menu->Append(wxID_ANY,wxT("Folding"),mnFold);

    /*** Build configuration part for the menu */
    m_menu->AppendSeparator();
    m_menu->Append(idConfigure,wxT("Configure"));
    m_menu->Append(idProperties,wxT("Properties"));
    m_menu->AppendSeparator();
    m_menu->Append(idCommentSel,wxT("Comment Selection"));
    m_menu->Append(idUncommentSel,wxT("Uncomment Selection"));

    return m_menu;
}

void RheiaEditorBase::OnCloseMe( wxCommandEvent& event )
{

}

void RheiaEditorBase::OnCloseAll( wxCommandEvent& event )
{

}

void RheiaEditorBase::OnCloseAllButMe( wxCommandEvent& event )
{

}

void RheiaEditorBase::OnSameMe( wxCommandEvent& event )
{

}

void RheiaEditorBase::OnSaveAll( wxCommandEvent& event )
{

}

void RheiaEditorBase::OnSaveMeAs( wxCommandEvent& event )
{

}

void RheiaEditorBase::OnContextMenu(wxCommandEvent& event)
{
    int id = event.GetId();

    if( id == idSplitHoriz && CanSplit() && !IsSplitted() )
        Split( splitHoriz );
    else if( id == idSplitVertical && CanSplit() && !IsSplitted() )
        Split( splitVertical );
    else if( id == idUnsplit && CanSplit() && IsSplitted() )
        Unsplit( );
    else if( id == idUndo && CanUndo() )
        DoUndo();
    else if( id == idRedo && CanRedo() )
        DoRedo();
    else if( id == idCut && CanCut() )
        DoCut();
    else if( id == idCopy && CanCopy() )
        DoCopy();
    else if( id == idPaste && CanPaste() )
        DoPaste();
    else if( id == idDelete && CanDelete() )
        DoDelete();
    else if( id == idClearHistory && CanClearHistory() )
        DoClearHistory();
    else if( id == idSelectAll && CanSelectAll() )
        DoSelectAll();
    else if( id == idSelectLine && CanSelectLine() )
        DoSelectLine();
    else if( id == idFind )
        {}
    else if( id == idFindNext )
        {}
    else if( id == idReplace )
        {}
    else if( id == idReplaceNext )
        {}
    else if( id == idToggleBookMark )
        ToggleBookmark();
    else if( id == idNextBookmark )
        GotoNextBookmark();
    else if( id == idPreviousBookMark )
        GotoPreviousBookmark();
    else if( id == idAutoFormatAll && CanFormat() )
        DoFormat();
    else if( id == idAutoFormatSel && CanFormatSelection() )
        DoFormatSelection();
    else if( id == idFoldAll && CanFold() )
        DoFoldAll();
    else if( id == idUnfoldAll && CanFold() )
        DoUnfoldAll();
    else if( id == idToggleAllFolds && CanFold() )
        DoToggleAllFolds();
    else if( id == idFoldCurrentBlock && CanFold() )
        DoFoldCurrentBlock();
    else if( id == idUnfoldCurrentBlock && CanFold() )
        DoUnFoldCurrentBlock();
    else if( id == idToggleCurrentBlockFold && CanFold() )
        DoToggleCurrentBlockFold();
    else if( id == idCommentSel && CanComment() )
        DoComment();
    else if( id == idUncommentSel && CanComment() )
        DoUncomment();
}

void RheiaEditorBase::OnConfigureEditor(wxCommandEvent& event)
{

}

void RheiaEditorBase::OnFileProperties( wxCommandEvent& event )
{

}

void RheiaEditorBase::RegisterSTCEvents()
{
    // dynamic events
    Connect( m_ID,  -1, wxEVT_STC_MARGINCLICK,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnMarginClick );
    Connect( m_ID,  -1, wxEVT_STC_UPDATEUI,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnUpdateUI );
    Connect( m_ID,  -1, wxEVT_STC_CHANGE,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnChange );
    Connect( m_ID,  -1, wxEVT_STC_CHARADDED,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnCharAdded );
    Connect( m_ID,  -1, wxEVT_STC_DWELLSTART,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnDwellStart );
    Connect( m_ID,  -1, wxEVT_STC_DWELLEND,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnDwellEnd );
    Connect( m_ID,  -1, wxEVT_STC_MODIFIED,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaEditorBase::OnModified );

    // Now bind all *other* scintilla events to a common function so that editor hooks
    // can be informed for them too.
    // If you implement one of these events using a different function, do the following:
    //  * comment it out here,
    //  * "connect" it in the above block
    //  * and make sure you call OnScintillaEvent() from your new handler function
    // This will make sure that all editor hooks will be called when needed.
    int scintilla_events[] =
    {
        wxEVT_STC_STYLENEEDED,
        wxEVT_STC_SAVEPOINTREACHED,
        wxEVT_STC_SAVEPOINTLEFT,
        wxEVT_STC_ROMODIFYATTEMPT,
        wxEVT_STC_KEY,
        wxEVT_STC_DOUBLECLICK,
        wxEVT_STC_MACRORECORD,
        wxEVT_STC_NEEDSHOWN,
        wxEVT_STC_PAINTED,
        wxEVT_STC_USERLISTSELECTION,
        wxEVT_STC_URIDROPPED,
        wxEVT_STC_START_DRAG,
        wxEVT_STC_DRAG_OVER,
        wxEVT_STC_DO_DROP,
        wxEVT_STC_ZOOM,
        wxEVT_STC_HOTSPOT_CLICK,
        wxEVT_STC_HOTSPOT_DCLICK,
        wxEVT_STC_CALLTIP_CLICK,
        -1 // to help enumeration of this array
    };
    int i = 0;
    while (scintilla_events[i] != -1)
    {
        Connect( m_ID,  -1, scintilla_events[i],
                 (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
                 &RheiaEditorBase::OnStcEvent );
        ++i;
    }
}

void RheiaEditorBase::OnCharAdded (wxStyledTextEvent &event)
{
    char chr = (char)event.GetKey();
    int currentLine = m_control->GetCurrentLine();
    // Change this if support for mac files with \r is needed
    if (chr == '\n')
    {
        int lineInd = 0;
        if (currentLine > 0)
        {
            lineInd = m_control->GetLineIndentation(currentLine - 1);
        }
        if (lineInd == 0) return;
        m_control->SetLineIndentation (currentLine, lineInd);
        m_control->GotoPos(m_control->PositionFromLine (currentLine) + lineInd);
    }
}

//! misc
void RheiaEditorBase::OnMarginClick (wxStyledTextEvent &event)
{
    if (event.GetMargin() == FOLD_MARGIN_ID)
    {
        int lineClick = m_control->LineFromPosition (event.GetPosition());
        int levelClick = m_control->GetFoldLevel (lineClick);
        if ((levelClick & wxSTC_FOLDLEVELHEADERFLAG) > 0)
        {
            m_control->ToggleFold (lineClick);
        }
    }
}

void RheiaEditorBase::OnUpdateUI(wxStyledTextEvent& event)
{

}

void RheiaEditorBase::OnChange(wxStyledTextEvent& event)
{

}

void RheiaEditorBase::OnDwellStart(wxStyledTextEvent& event)
{

}

void RheiaEditorBase::OnDwellEnd(wxStyledTextEvent& event)
{

}

void RheiaEditorBase::OnModified(wxStyledTextEvent& event)
{

}

void RheiaEditorBase::OnZoom(wxStyledTextEvent& event)
{

}

void RheiaEditorBase::OnStcEvent(wxStyledTextEvent& event)
{
    if( event.GetEventType() == wxEVT_STC_DOUBLECLICK )
    {
        wxString word = m_control->GetSelectedText();
        HighlightOccurrences(word, wxSTC_FIND_MATCHCASE | wxSTC_FIND_WORDSTART );
    }
}

void RheiaEditorBase::DoSelectLine()
{
    int lineStart = m_control->PositionFromLine (m_control->GetCurrentLine());
    int lineEnd = m_control->PositionFromLine (m_control->GetCurrentLine() + 1);
    m_control->SetSelection (lineStart, lineEnd);
}

void RheiaEditorBase::HighlightOccurrences( const wxString& expr , int flag )
{
    const int theIndicator = MATCH_INDICATOR;
    m_control->SendMsg( 2500 , theIndicator , 0 );

    wxString selectedText = expr;
    int eof = m_control->GetLength();
    m_control->SendMsg( 2505 , 0 , eof );

    if( selectedText.Len() > 2        // if there is no text selected (a == b), it stops here and does not hog the cpu further
            && selectedText.Find(_T(' ')) == wxNOT_FOUND
            && selectedText.Find(_T('\t')) == wxNOT_FOUND
            && selectedText.Find(_T('\n')) == wxNOT_FOUND )
    {

        // search for every occurence
        for ( int pos = m_control->FindText(0, eof, selectedText, flag );
                pos != wxSTC_INVALID_POSITION ;
                pos = m_control->FindText(pos+=selectedText.Len(), eof, selectedText, flag) )
        {
            m_control->SendMsg( 2504 , pos , selectedText.Len() );
        }
    }
}

void RheiaEditorBase::DoFoldAll()
{
    int count = m_control->GetLineCount();
    for (int i = 0; i <= count; ++i)
        DoFoldLine(i, 1);
}

void RheiaEditorBase::DoUnfoldAll()
{
    int count = m_control->GetLineCount();
    for (int i = 0; i <= count; ++i)
        DoFoldLine(i, 0);
}

void RheiaEditorBase::DoToggleAllFolds()
{
    int count = m_control->GetLineCount();
    for (int i = 0; i <= count; ++i)
        DoFoldLine(i, 2);
}

void RheiaEditorBase::DoFoldLine( int line , int fold )
{
    int level = m_control->GetFoldLevel(line);

    // The fold parameter is the type of folding action requested
    // 0 = Unfold; 1 = Fold; 2 = Toggle folding.

    // Check if the line is a header (fold point).
    if (level & wxSTC_FOLDLEVELHEADERFLAG)
    {
        bool IsExpanded = m_control->GetFoldExpanded(line);

        // If a fold/unfold request is issued when the block is already
        // folded/unfolded, ignore the request.
        if (fold == 0 && IsExpanded) return;
        if (fold == 1 && !IsExpanded) return;

        m_control->ToggleFold(line);
        return;
    }
    return;
}

void RheiaEditorBase::FoldBlockFromLine(int line)
{
    if (line == -1)
        line = m_control->GetCurrentLine();
    DoFoldBlockFromLine(line, 1);
}

void RheiaEditorBase::UnfoldBlockFromLine(int line)
{
    if (line == -1)
        line = m_control->GetCurrentLine();
    DoFoldBlockFromLine(line, 0);
}

void RheiaEditorBase::ToggleFoldBlockFromLine(int line)
{
    if (line == -1)
        line = m_control->GetCurrentLine();
    DoFoldBlockFromLine(line, 2);
}

void RheiaEditorBase::DoFoldCurrentBlock()
{
    FoldBlockFromLine();
};

void RheiaEditorBase::DoUnFoldCurrentBlock()
{
    UnfoldBlockFromLine();
};

void RheiaEditorBase::DoToggleCurrentBlockFold()
{
    ToggleFoldBlockFromLine();
};

void RheiaEditorBase::DoFoldBlockFromLine(int line, int fold)
{
    m_control->Colourise(0, -1); // the *most* important part!
    int i, parent, maxLine, level, UnfoldUpto = line;
    bool FoldedInside = false;

    parent = m_control->GetFoldParent(line);
    level = m_control->GetFoldLevel(parent);
    /* The following code will check if the child is hidden
    *  under parent before unfolding it
    */
    if (fold == 0)
    {
        do
        {
            if (!m_control->GetFoldExpanded(parent))
            {
                FoldedInside = true;
                UnfoldUpto = parent;
            }
            if (wxSTC_FOLDLEVELBASE == (level & wxSTC_FOLDLEVELNUMBERMASK))
                break;
            parent = m_control->GetFoldParent(parent);
            level = m_control->GetFoldLevel(parent);
        }
        while (parent != -1);
    }

    maxLine =m_control->GetLastChild(line, -1);

    for (i = UnfoldUpto; i <= maxLine; ++i)
        DoFoldLine(i, fold);
}

bool RheiaEditorBase::LineHasMarker(int marker, int line)
{
    if (line == -1)
        line = m_control->GetCurrentLine();

    return m_control->MarkerGet(line) & (1 << marker);
}

void RheiaEditorBase::ToggleBookmark(int line)
{
    MarkerToggle(BOOKMARK_MARKER,line);
}

void RheiaEditorBase::MarkerToggle( int marker, int line )
{
    if (line == -1)
        line = m_control->GetCurrentLine();
    if (LineHasMarker(marker, line))
        m_control->MarkerDelete(line, marker);
    else
        m_control->MarkerAdd(line, marker);
}

void RheiaEditorBase::MarkerNext(int marker)
{
    int line = m_control->GetCurrentLine() + 1;
    int newLine = m_control->MarkerNext(line, 1 << marker);
    if (newLine != -1)
        m_control->GotoLine(newLine);
}

void RheiaEditorBase::MarkerPrevious(int marker)
{
    int line = m_control->GetCurrentLine() - 1;
    int newLine = m_control->MarkerPrevious(line, 1 << marker);
    if (newLine != -1)
        m_control->GotoLine(newLine);
}

void RheiaEditorBase::GotoNextBookmark()
{
    MarkerNext(BOOKMARK_MARKER);
}

void RheiaEditorBase::GotoPreviousBookmark()
{
    MarkerPrevious(BOOKMARK_MARKER);
}

void RheiaEditorBase::DoApplyRegex( const wxRegEx& expression , const wxString& repStr , bool selOnly , bool confirm )
{
    wxString text;

    if( selOnly )
        text = m_control->GetSelectedText();
    else
        text = m_control->GetText();

    int count = expression.ReplaceAll(&text,repStr);

    if( selOnly )
        m_control->ReplaceSelection(text);
    else
        m_control->SetText(text);
}

int RheiaEditorBase::Find( const wxString& expr , int flag )
{
    const int theIndicator = MATCH_INDICATOR;
    m_control->SendMsg( 2500 , theIndicator , 0 );
	int ret = -1;
    wxString selectedText = expr;
	bool findFirst = false;
	
    int eof = m_control->GetLength();
    m_control->SendMsg( 2505 , 0 , eof );

    if( selectedText.Len() > 2        // if there is no text selected (a == b), it stops here and does not hog the cpu further
            && selectedText.Find(_T(' ')) == wxNOT_FOUND
            && selectedText.Find(_T('\t')) == wxNOT_FOUND
            && selectedText.Find(_T('\n')) == wxNOT_FOUND )
    {

        // search for every occurence
        for ( int pos = m_control->FindText(0, eof, selectedText, flag );
                pos != wxSTC_INVALID_POSITION ;
                pos = m_control->FindText(pos+=selectedText.Len(), eof, selectedText, flag) )
        {
			if( !findFirst )
			{
				m_control->SetSelectionStart(pos);
				m_control->SetSelectionEnd(pos+=selectedText.Len());
				ret = pos;
				m_lastFindPos = ret;
			}
            m_control->SendMsg( 2504 , pos , selectedText.Len() );
        }
    }
	
	return ret;
}

int RheiaEditorBase::FindNext( const wxString& expr , int flag )
{
	return 0;
}

void RheiaEditorBase::Goto( int line )
{
  #if wxCHECK_VERSION(2,9,0)
    int no_lines = m_control->GetNumberOfLines()-1;
#else
	int no_lines = m_control->GetLineCount()-1;
#endif

    if( no_lines < line )
        line = no_lines;

	m_control->GotoLine(line);
    m_control->SetFocus();
}
