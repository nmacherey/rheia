/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "PyConsole.h"
#include "PyContext.h"
#include "PyConsoleManager.h"
#include "PyUtils.h"

#include <RheiaPythonUtils.h>
#include <RheiaConfigurationManager.h>
#include <RheiaManager.h>

namespace
{
    const wxString& defText = wxT("Rheia Python Console version 0.1.1 \n"
                                  "This program is free software under LGPL... Have Fun !\n");
}


BEGIN_EVENT_TABLE(PyConsole,RheiaBookPage)
    EVT_CONTEXT_MENU(PyConsole::OnRequestContextMenu)
    //EVT_STC_KEY_PROCESS(wxID_ANY , PyConsole::OnStcKey)
END_EVENT_TABLE()

PyConsole::PyConsole( RheiaManagedFrame* toplevel , wxWindow* parent ):
    RheiaBookPage(parent),
    m_parent(toplevel),
    m_context(NULL)
{
    RheiaPythonUtils::Get()->PythonInit();
    m_context = new PyContext;
    wxPanel::Create(parent,wxID_ANY);
    m_ID = wxNewId();

    m_nolines = 0;
    m_currentHistoryPos = 0;

    idSaveMe                = wxNewId();
    idSaveAs                = wxNewId();
    idCut                   = wxNewId();
    idCopy                  = wxNewId();
    idPaste                 = wxNewId();
    idDelete                = wxNewId();
    idSelectAll             = wxNewId();
    idSelectLine            = wxNewId();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    m_control = new wxSStyledTextCtrl( this, m_ID, wxPoint(10,10), wxSize(200,200), 0 );
    m_stdoutred = new wxSStreamToTextRedirector(m_control,std::cout );
    m_stderrred = new wxSStreamToTextRedirector(m_control,std::cerr );

    m_control->SetText(defText);
    int eof = m_control->GetLength();
    m_control->GotoPos(eof);
    m_control->AddText(wxT(">>> ")); 

    Reload();

    Registerevents();
    RegisterSTCEvents();

    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("pyconsole"));
    m_history = cfg->ReadArrayString(wxT("/history"));

    sizer->Add( m_control, 1, wxEXPAND | wxALL, 5 );
    this->SetSizer( sizer );
    this->Layout();
}

PyConsole::~PyConsole()
{
    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("pyconsole"));
    cfg->Write(wxT("/history"),m_history);
}

void PyConsole::Reload()
{
    m_control->SetLexer(m_context->GetLexer());
    wxArrayString kw = m_context->GetKeywords();

    for( unsigned int i = 0; i < kw.GetCount() ; ++i )
        m_control->SetKeyWords(i,kw[i]);

    m_control->SetViewEOL( m_context->ViewEOL() );
    m_control->SetViewWhiteSpace( m_context->ViewWhiteSpace() );
    m_control->SetMarginWidth( 2, 0 );

    m_control->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
    //m_control->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
    m_control->SetMarginWidth( 1, 16);
    m_control->SetMarginSensitive( 1, true );

    wxStcPropertyMap props = m_context->GetPropertyMap();
    wxStcPropertyMap::iterator it = props.begin();
    for(; it != props.end() ; ++it )
        m_control->SetProperty( it->first, it->second );

    m_control->SetModEventMask ( m_context->GetModEventMask() );
    m_control->SetXCaretPolicy( m_context->GetXCaretPolicy() , m_context->GetXCaretZone() );
    m_control->SetYCaretPolicy( m_context->GetYCaretPolicy() , m_context->GetYCaretZone() );

    m_control->SetMarginType(SYMBOLS_MARGIN_ID, wxSTC_MARGIN_SYMBOL);
    m_control->SetMarginType(NUMBER_MARGIN_ID, wxSTC_MARGIN_NUMBER);
    m_control->SetMarginType(EDIT_TRACKER_MARGIN_ID, 4); // Styled Text margin
    m_control->SetMarginWidth(EDIT_TRACKER_MARGIN_ID, 3 );
    m_control->SetMarginMask(EDIT_TRACKER_MARGIN_ID, 0);

    // Separators
    m_control->SetMarginType(SYMBOLS_MARGIN_SEP_ID, wxSTC_MARGIN_FORE);
    m_control->SetMarginMask(SYMBOLS_MARGIN_SEP_ID, 0);

    // Fold margin - allow only folder symbols to display
    m_control->SetMarginMask(FOLD_MARGIN_ID, ~(wxSTC_MASK_FOLDERS));
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

    wxColour col(wxT("LIGHT BLUE"));
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
    m_control->SetTabIndents(true);
    m_control->SetBackSpaceUnIndents (true);
    m_control->SetUseTabs(true);
    m_control->SetTabWidth(4);
    m_control->SetIndent(4);
    m_control->SetIndentationGuides( 3 );
    m_control->SetLayoutCache(m_context->GetLayoutCache());

    m_control->StyleClearAll();
    m_context->SetStyles( m_control );
    m_control->UsePopUp(false);
}

void PyConsole::Registerevents()
{
    Connect(idSaveMe,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnSaveMe));
    Connect(idSaveAs,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnSaveMeAs));
    Connect(idCut,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnContextMenu));
    Connect(idCopy,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnContextMenu));
    Connect(idPaste,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnContextMenu));
    Connect(idDelete,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnContextMenu));
    Connect(idSelectAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(PyConsole::OnContextMenu));
    m_control->Connect(m_ID,wxEVT_KEY_DOWN,wxKeyEventHandler(PyConsole::OnStcKey),NULL,this);
}

void PyConsole::OnRequestContextMenu( wxContextMenuEvent& event )
{
    wxMenu* m_menu = BuilContextMenu();

    int mx = wxGetMousePosition().x - this->GetScreenPosition().x;
    int my = wxGetMousePosition().y - this->GetScreenPosition().y;

    wxPoint pos(mx,my);

    PopupMenu( m_menu , pos );
}

void PyConsole::DefineMarker(int marker, int markerType, wxColor fore, wxColor back)
{
    m_control->MarkerDefine(marker, markerType);
    m_control->MarkerSetForeground(marker, fore);
    m_control->MarkerSetBackground(marker, back);
}

bool PyConsole::Save( const wxString& filename )
{
    return m_control->SaveFile(filename);
}

bool PyConsole::Load( const wxString& filename )
{
    return m_control->LoadFile(filename);
}

wxMenu* PyConsole::BuilContextMenu()
{
    wxMenu* m_menu = new wxMenu();;
    m_menu->Append( idSaveMe , wxT("&Save...") , wxT("Save me ..."));
    m_menu->Append( idSaveAs , wxT("Save as...") , wxT("Save me in a new file..."));
    m_menu->AppendSeparator();
    m_menu->Append(idCut,wxT("Cut"));
    m_menu->Append(idCopy,wxT("Copy"));
    m_menu->Append(idPaste,wxT("Paste"));
    m_menu->Append(idDelete,wxT("Delete"));
    m_menu->AppendSeparator();
    m_menu->Append(idSelectAll,wxT("Select all"));

    return m_menu;
}

void PyConsole::OnSaveMe( wxCommandEvent& event )
{

}

void PyConsole::OnSaveMeAs( wxCommandEvent& event )
{

}

void PyConsole::OnContextMenu(wxCommandEvent& event)
{
    int id = event.GetId();

    if( id == idCut )
        DoCut();
    else if( id == idCopy )
        DoCopy();
    else if( id == idPaste )
        DoPaste();
    else if( id == idDelete )
        DoDelete();
    else if( id == idSelectAll )
        DoSelectAll();
}

void PyConsole::RegisterSTCEvents()
{
    // dynamic events
    Connect( m_ID, wxEVT_STC_MARGINCLICK,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnMarginClick );
    Connect( m_ID, wxEVT_STC_UPDATEUI,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnUpdateUI );
    Connect( m_ID, wxEVT_STC_CHANGE,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnChange );
    Connect( m_ID, wxEVT_STC_CHARADDED,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnCharAdded );
    Connect( m_ID, wxEVT_STC_DWELLSTART,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnDwellStart );
    Connect( m_ID, wxEVT_STC_DWELLEND,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnDwellEnd );
    Connect( m_ID, wxEVT_STC_MODIFIED,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnModified );
    Connect( m_ID, wxEVT_STC_KEY,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &PyConsole::OnStcKey );


    int scintilla_events[] =
    {
        wxEVT_STC_STYLENEEDED,
        wxEVT_STC_SAVEPOINTREACHED,
        wxEVT_STC_SAVEPOINTLEFT,
        wxEVT_STC_ROMODIFYATTEMPT,
        //wxEVT_STC_KEY,
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
        Connect( m_ID, scintilla_events[i],
                 (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
                 &PyConsole::OnStcEvent );
        ++i;
    }
}

void PyConsole::OnCharAdded (wxStyledTextEvent &event)
{
    char chr = (char)event.GetKey();
    int currentLine = m_control->GetCurrentLine();
#if wxCHECK_VERSION(2,9,0)
    int no_lines = m_control->GetNumberOfLines();
#else
	int no_lines = m_control->GetLineCount();
#endif

    if (chr == '\n' || chr == '\r')
    {
        int lineInd = 0;

        if (currentLine > 0 )
        {
            wxString command = m_control->GetLine(currentLine-1);
            wxString prompt;

            if( command.Contains(wxT(">>> ")) || command.Contains(wxT("... ")) )
            {
                wxString res;
                command.Replace(wxT(">>> "),wxT(""),true);
                command.Replace(wxT("... "),wxT(""),true);

                if( m_nolines == 0 && (command.IsEmpty() || command == wxT("\n") ) )
                {
                    int eof = m_control->GetLength();
                    m_control->GotoPos(eof);
                    m_control->AddText(wxT(">>> "));

                    return;
                }

                wxString temp = command;
                temp.RemoveLast();
                if( !temp.IsEmpty() )
                {
                    m_history.Insert(temp,0);

                    if( m_history.GetCount() >= 300 )
                        m_history.RemoveAt( m_history.GetCount()-1 );
                }

                m_currentHistoryPos = 0;

                m_commandBuffer += command;
                m_nolines++;

                bool shalExec = RheiaPythonUtils::Get()->ShallExecuteCommand( m_commandBuffer , m_nolines );

                /** @todo add the command to the history there */
                if(shalExec)
                {
                    int flag = RheiaPythonUtils::Get()->PythonGetFlagFromString( m_commandBuffer );
                    if( !RheiaPythonUtils::Get()->PythonEvalString(m_commandBuffer,res,flag) )
                        m_control->AppendText(res + wxT("\n"));
                    else if( !res.IsEmpty() )
                    {
                        //res = wxT("Command returned : \n") + res;
                        m_control->AppendText(res + wxT("\n"));
                    }


                    m_commandBuffer.Clear();
                    m_nolines = 0;
                    int eof = m_control->GetLength();
                    m_control->GotoPos(eof);
                    m_control->AddText(wxT(">>> "));
                }
                else
                {
                    int eof = m_control->GetLength();
                    m_control->GotoPos(eof);
                    m_control->AddText(wxT("... "));
                }
            }
			else
			{
				int eof = m_control->GetLength();
				m_control->GotoPos(eof);
				m_control->AddText(wxT(">>> "));
			}
		}
    }
}

//! misc
void PyConsole::OnMarginClick (wxStyledTextEvent &event)
{

}

void PyConsole::OnUpdateUI(wxStyledTextEvent& event)
{

}

void PyConsole::OnChange(wxStyledTextEvent& event)
{

}

void PyConsole::OnDwellStart(wxStyledTextEvent& event)
{

}

void PyConsole::OnDwellEnd(wxStyledTextEvent& event)
{

}

void PyConsole::OnModified(wxStyledTextEvent& event)
{

}

void PyConsole::OnZoom(wxStyledTextEvent& event)
{

}

void PyConsole::OnStcKey(wxKeyEvent& event)
{
    //int key = event.GetKeyCode();
    int key = event.GetKeyCode();
    int eof = m_control->GetLength();
    int pos = m_control->GetCurrentPos();

    int posAtLine;
    int line = m_control->GetCurrentLine();
    wxString lineContent = m_control->GetCurLine(&posAtLine);
#if wxCHECK_VERSION(2,9,0)
    int no_lines = m_control->GetNumberOfLines()-1;
#else
	int no_lines = m_control->GetLineCount()-1;
#endif

    if( key == WXK_RETURN )
    {
        if( pos != eof )
            m_control->GotoPos(eof);

        if( line != no_lines )
            return;
    }
    else if( key == WXK_UP )
    {
        /** shall add here stuff for history browsing */
        m_control->GotoPos(eof);

        if(m_history.GetCount() == 0 || m_currentHistoryPos >= m_history.GetCount() )
            return;

        if( posAtLine > 4 )
        {
            m_control->GotoLine(line);
            int pfl = m_control->GetCurrentPos();
#if wxCHECK_VERSION(2,9,0)
            m_control->Remove(pfl+4,eof);
#else
			m_control->SetSelection(pfl+4,eof);
			m_control->ReplaceSelection(wxT(""));
#endif
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
        }


        m_control->AppendText( m_history[m_currentHistoryPos] );
        m_currentHistoryPos++;
        eof = m_control->GetLength();
        m_control->GotoPos(eof);

        return;
    }
    else if( key == WXK_DOWN )
    {
        /** shall add here stuff for history browsing */
        m_control->GotoPos(eof);

        if(m_history.GetCount() == 0 || m_currentHistoryPos <= 0 )
            return;

        if( posAtLine > 4 )
        {
            m_control->GotoLine(line);
            int pfl = m_control->GetCurrentPos();
#if wxCHECK_VERSION(2,9,0)
            m_control->Remove(pfl+4,eof);
#else
			m_control->SetSelection(pfl+4,eof);
			m_control->ReplaceSelection(wxT(""));
#endif
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
        }

        m_currentHistoryPos--;
        m_control->AppendText( m_history[m_currentHistoryPos] );
        eof = m_control->GetLength();
        m_control->GotoPos(eof);

        return;
    }
    else if( key == WXK_DELETE || key == WXK_BACK )
    {

        if( line != no_lines )
        {
            m_control->GotoPos(eof);
            return;
        }

        if( posAtLine <= 4 )
            return;
    }


    event.Skip();
}

void PyConsole::OnStcEvent(wxStyledTextEvent& event)
{
    if( event.GetEventType() == wxEVT_STC_DOUBLECLICK )
    {
        wxString word = m_control->GetSelectedText();
        HighlightOccurrences(word, wxSTC_FIND_MATCHCASE | wxSTC_FIND_WORDSTART );
        event.Skip();
    }
}

void PyConsole::HighlightOccurrences( const wxString& expr , int flag )
{
    static int old_a;
    static int old_b;

    int a,b;

    const int theIndicator = MATCH_INDICATOR;

    m_control->GetSelection(&a,&b);
    m_control->SendMsg( 2500 , theIndicator , 0 );

    if(old_a == a && old_b == b) // whatever the current state is, we've already done it once
        return;

    old_a = a;
    old_b = b;

    wxString selectedText(m_control->GetTextRange(a, b));
    int eof = m_control->GetLength();
    m_control->SendMsg( 2505 , 0 , eof );

    if( selectedText.Len() > 2        // if there is no text selected (a == b), it stops here and does not hog the cpu further
            && selectedText.Find(_T(' ')) == wxNOT_FOUND
            && selectedText.Find(_T('\t')) == wxNOT_FOUND
            && selectedText.Find(_T('\n')) == wxNOT_FOUND )
    {

        // search for every occurence
        int lengthFound = 0; // we need this to work properly with multibyte characters
        for ( int pos = m_control->FindText(0, eof, selectedText, flag );
                pos != wxSTC_INVALID_POSITION ;
                pos = m_control->FindText(pos+=selectedText.Len(), eof, selectedText, flag) )
        {
            // does not make sense anymore: check that the found occurrence is not the same as the selected,
            // since it is not selected in the second view -> so highlight it
            m_control->SendMsg( 2504 , pos , selectedText.Len() );
        }
    }
}

bool PyConsole::LineHasMarker(int marker, int line)
{
    if (line == -1)
        line = m_control->GetCurrentLine();

    return m_control->MarkerGet(line) & (1 << marker);
}
