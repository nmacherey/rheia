/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */
#include <Python.h>
#include <wx/wxPython/wxPython.h>

#include "RheiaPythonConsole.h"
#include "RheiaPythonLayout.h"
#include "RheiaPythonConsoleManager.h"
#include "RheiaEditorBase.h"

#include <RheiaPythonUtils.h>
#include <RheiaPython.h>
#include <RheiaConfigurationManager.h>
#include <RheiaManager.h>

namespace
{
    const wxString& defText = _("Rheia Python Console version 0.1.1 \n"
                                  "This program is based on python 2.6 and wxStyledTextCtrl !\n");
}


BEGIN_EVENT_TABLE(RheiaPythonConsole,RheiaBookPage)
    EVT_CONTEXT_MENU(RheiaPythonConsole::OnRequestContextMenu)
    //EVT_STC_KEY_PROCESS(wxID_ANY , RheiaPythonConsole::OnStcKey)
END_EVENT_TABLE()

RheiaPythonConsole::RheiaPythonConsole( RheiaManagedFrame* toplevel , wxWindow* parent ):
    RheiaBookPage(parent),
    m_parent(toplevel),
    m_context(NULL)
{
    RheiaPythonUtils::Get()->PythonInit();
    m_context = new RheiaPythonLayout;
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

    m_stdoutred = new wxSStreamToTextRedirector(m_control,wxSTD cout );
    m_stderrred = new wxSStreamToTextRedirector(m_control,wxSTD cerr );

    m_control->SetText(defText);
    int eof = m_control->GetLength();
    m_control->GotoPos(eof);
    m_control->AddText(wxT(">>> ")); 

    Reload();

    Registerevents();
    RegisterSTCEvents();

    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("RheiaPythonConsole"));
    m_history = cfg->ReadArrayString(wxT("/history"));
	wxString res;

    sizer->Add( m_control, 1, wxEXPAND | wxALL, 5 );
    this->SetSizer( sizer );
    this->Layout();
	
	if( RheiaPythonGetBaseAPIPtr() )
	{
		PyObject* arg = rheiaPythonBaseConstructObject((void*) m_parent, wxT("RheiaManagedFrame") , true);
		PyModule_AddObject(RheiaPythonUtils::Get()->GetMainModule(), "rhFrame", arg);
	}
	
	RheiaPythonUtils::Get()->GetPluginsCount();
	RheiaPythonUtils::Get()->GetPluginsNames();
}

RheiaPythonConsole::~RheiaPythonConsole()
{
	//RheiaPythonUtils::Get()->PythonExit();
    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager(wxT("RheiaPythonConsole"));
    cfg->Write(wxT("/history"),m_history);
}

void RheiaPythonConsole::Reload()
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
    m_control->SetBackSpaceUnIndents (false);
    m_control->SetUseTabs(false);
    m_control->SetTabWidth(4);
    m_control->SetIndent(0);
    m_control->SetLayoutCache(m_context->GetLayoutCache());

    m_control->StyleClearAll();
    m_context->SetStyles( m_control );
    m_control->UsePopUp(false);
}

void RheiaPythonConsole::Registerevents()
{
    Connect(idSaveMe,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnSaveMe));
    Connect(idSaveAs,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnSaveMeAs));
    Connect(idCut,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnContextMenu));
    Connect(idCopy,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnContextMenu));
    Connect(idPaste,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnContextMenu));
    Connect(idDelete,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnContextMenu));
    Connect(idSelectAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsole::OnContextMenu));
    m_control->Connect(m_ID,wxEVT_KEY_DOWN,wxKeyEventHandler(RheiaPythonConsole::OnStcKey),NULL,this);
    m_control->Connect(m_ID,wxEVT_CHAR,wxKeyEventHandler(RheiaPythonConsole::OnStcChar),NULL,this);
}

void RheiaPythonConsole::OnRequestContextMenu( wxContextMenuEvent& event )
{
    wxMenu* m_menu = BuilContextMenu();

    int mx = wxGetMousePosition().x - this->GetScreenPosition().x;
    int my = wxGetMousePosition().y - this->GetScreenPosition().y;

    wxPoint pos(mx,my);

    PopupMenu( m_menu , pos );
}

void RheiaPythonConsole::DefineMarker(int marker, int markerType, wxColor fore, wxColor back)
{
    m_control->MarkerDefine(marker, markerType);
    m_control->MarkerSetForeground(marker, fore);
    m_control->MarkerSetBackground(marker, back);
}

bool RheiaPythonConsole::Save( const wxString& filename )
{
    return m_control->SaveFile(filename);
}

bool RheiaPythonConsole::Load( const wxString& filename )
{
    return m_control->LoadFile(filename);
}

wxMenu* RheiaPythonConsole::BuilContextMenu()
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

void RheiaPythonConsole::OnSaveMe( wxCommandEvent& event )
{

}

void RheiaPythonConsole::OnSaveMeAs( wxCommandEvent& event )
{

}

void RheiaPythonConsole::OnContextMenu(wxCommandEvent& event)
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

void RheiaPythonConsole::DoCut()
{
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
	
	if( line != no_lines )
	{
		m_control->Copy();
		return;
	}
	
	int start = m_control->GetLineSelStartPosition(line);
	int end = m_control->GetLineSelEndPosition(line);
	
	int lstart = m_control->GetLineEndPosition(line-1)+1;
	
	int diffstart = 4 - (start - lstart);
	int diffend = 4 - (end - lstart);
	
	if( diffstart > 0 )
		m_control->SetSelectionStart(start+diffstart);

	if( diffend > 0 )
		m_control->SetSelectionEnd(start+diffend);
	
	m_control->Cut();
}

void RheiaPythonConsole::DoPaste()
{
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
	
	if( line != no_lines )
	{
		eof = m_control->GetLength();
        m_control->GotoPos(eof);
		m_control->Paste();
		return;
	}
	
	if( posAtLine < 4 )
		return;
		
	m_control->Paste();
}

void RheiaPythonConsole::DoDelete()
{
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
	
	if( line != no_lines )
	{
		return;
	}
	
	if( posAtLine < 4 )
		return;
		
	m_control->ReplaceSelection(wxEmptyString);
};

void RheiaPythonConsole::DoCopy()
{
	m_control->Copy();
}

void RheiaPythonConsole::RegisterSTCEvents()
{
    // dynamic events
    Connect( m_ID, wxEVT_STC_MARGINCLICK,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnMarginClick );
    Connect( m_ID, wxEVT_STC_UPDATEUI,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnUpdateUI );
    Connect( m_ID, wxEVT_STC_CHANGE,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnChange );
    /*Connect( m_ID, wxEVT_STC_CHARADDED,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnCharAdded );*/
    Connect( m_ID, wxEVT_STC_DWELLSTART,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnDwellStart );
    Connect( m_ID, wxEVT_STC_DWELLEND,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnDwellEnd );
    Connect( m_ID, wxEVT_STC_MODIFIED,
             (wxObjectEventFunction) (wxEventFunction) (wxStyledTextEventFunction)
             &RheiaPythonConsole::OnModified );


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
                 &RheiaPythonConsole::OnStcEvent );
        ++i;
    }
}

void RheiaPythonConsole::OnStcChar(wxKeyEvent& event)
{
    //int key = event.GetKeyCode();
    int key = event.GetKeyCode();
    int eof = m_control->GetLength();
    int pos = m_control->GetCurrentPos();

    int posAtLine;
    int line = m_control->GetCurrentLine();
    wxString lineContent = m_control->GetCurLine(&posAtLine);

    if( key == WXK_RETURN || key == WXK_NUMPAD_ENTER )
        return;
    else
        event.Skip();
}

void RheiaPythonConsole::OnCharAdded (wxStyledTextEvent &event)
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
                command.Remove(0,4);
#ifdef WIN32
                command.RemoveLast();
#endif
                if( command.IsEmpty() || command.IsSameAs(wxT("\n")) || command.IsSameAs(wxT("\r")) )
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
				
				wxString err;
                std::cout << RheiaU2C(command) << std::endl;
				
                int shalExec = RheiaPythonUtils::Get()->ShallExecuteCommand( m_commandBuffer , err , m_nolines );

                /** @todo add the command to the history there */
                if(shalExec == 1)
                {
                    int flag = RheiaPythonUtils::Get()->PythonGetFlagFromString( m_commandBuffer );
                    if( !RheiaPythonUtils::Get()->PythonEvalString(m_commandBuffer,res,flag) )
                        m_control->AppendText(res + wxT("\n"));
                    else if( !res.IsEmpty() )
                    {
                        m_control->AppendText(res + wxT("\n"));
                    }


                    m_commandBuffer.Clear();
                    m_nolines = 0;
                    int eof = m_control->GetLength();
                    m_control->GotoPos(eof);
                    m_control->AddText(wxT(">>> "));
                }
                else if(shalExec == 0)
                {
                    int eof = m_control->GetLength();
                    m_control->GotoPos(eof);
                    m_control->AddText(wxT("... "));
                }
				else
				{	
					m_commandBuffer.Clear();
                    m_nolines = 0;
					m_control->AppendText(err + wxT("\n"));
					int eof = m_control->GetLength();
                    m_control->GotoPos(eof);
                    m_control->AddText(wxT(">>> "));
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
void RheiaPythonConsole::OnMarginClick (wxStyledTextEvent &event)
{

}

void RheiaPythonConsole::OnUpdateUI(wxStyledTextEvent& event)
{

}

void RheiaPythonConsole::OnChange(wxStyledTextEvent& event)
{

}

void RheiaPythonConsole::OnDwellStart(wxStyledTextEvent& event)
{

}

void RheiaPythonConsole::OnDwellEnd(wxStyledTextEvent& event)
{

}

void RheiaPythonConsole::OnModified(wxStyledTextEvent& event)
{

}

void RheiaPythonConsole::OnZoom(wxStyledTextEvent& event)
{

}

void RheiaPythonConsole::DoClearLastLine()
{
    int eof = m_control->GetLength();

#if wxCHECK_VERSION(2,9,0)
    int no_lines = m_control->GetNumberOfLines()-1;
#else
	int no_lines = m_control->GetLineCount()-1;
#endif

    /** shall add here stuff for history browsing */
    m_control->GotoPos(eof);
    m_control->GotoLine(no_lines);
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

void RheiaPythonConsole::DoProcessLine()
{
    int eof = m_control->GetLength();
    int pos = m_control->GetCurrentPos();
    bool selecting = m_control->GetSelectionStart() != m_control->GetSelectionEnd();

    int posAtLine;
    int line = m_control->GetCurrentLine();
    int currentLine = m_control->GetCurrentLine();
    wxString lineContent = m_control->GetCurLine(&posAtLine);

#if wxCHECK_VERSION(2,9,0)
    int no_lines = m_control->GetNumberOfLines()-1;
#else
	int no_lines = m_control->GetLineCount()-1;
#endif

    wxString command = m_control->GetLine(currentLine);
    wxString prompt;

    if( command.Contains(wxT(">>> ")) || command.Contains(wxT("... ")) )
    {
        wxString res;
        command.Remove(0,4);

        if( m_nolines == 0 && (command.IsEmpty() || command.IsSameAs(wxT("\n")) || command.IsSameAs(wxT("\r"))) )
        {
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
            m_control->AppendText(wxT("\n>>> "));
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
            return;
        }

        wxString temp = command;
        if( !temp.IsEmpty() )
        {
            m_history.Insert(temp,0);

            if( m_history.GetCount() >= 300 )
                m_history.RemoveAt( m_history.GetCount()-1 );
        }

        m_currentHistoryPos = 0;

        m_commandBuffer += command + wxT("\n");
        m_nolines++;
			
		wxString err;
        int shalExec = RheiaPythonUtils::Get()->ShallExecuteCommand( m_commandBuffer , err , m_nolines );

        if(shalExec == 1)
        {
            int flag = RheiaPythonUtils::Get()->PythonGetFlagFromString( m_commandBuffer );
            if( !RheiaPythonUtils::Get()->PythonEvalString(m_commandBuffer,res,flag) )
                m_control->AppendText(wxT("\n") + res);
            else if( !res.IsEmpty() )
            {
                m_control->AppendText(wxT("\n") + res);
            }


            m_commandBuffer.Clear();
            m_nolines = 0;
            int eof = m_control->GetLength();
            m_control->GotoPos(eof);
            m_control->AppendText(wxT("\n>>> "));
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
        }
        else if(shalExec == 0)
        {
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
            m_control->AppendText(wxT("\n... "));
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
        }
		else
		{	
			m_commandBuffer.Clear();
            m_nolines = 0;
			m_control->AppendText(wxT("\n") + err );
			eof = m_control->GetLength();
            m_control->GotoPos(eof);
            m_control->AppendText(wxT("\n>>> "));
            eof = m_control->GetLength();
            m_control->GotoPos(eof);
		}
    }
	else
	{
		eof = m_control->GetLength();
		m_control->GotoPos(eof);
		m_control->AppendText(wxT("\n>>> "));
        eof = m_control->GetLength();
        m_control->GotoPos(eof);
	}
}

void RheiaPythonConsole::OnStcKey(wxKeyEvent& event)
{
    //int key = event.GetKeyCode();
    int key = event.GetKeyCode();
    bool controlDown = event.ControlDown();
    bool altDown = event.AltDown();
    bool shiftDown = event.ShiftDown();

    int eof = m_control->GetLength();
    int pos = m_control->GetCurrentPos();
    bool selecting = m_control->GetSelectionStart() != m_control->GetSelectionEnd();

    int posAtLine;
    int line = m_control->GetCurrentLine();
    int currentLine = m_control->GetCurrentLine();
    wxString lineContent = m_control->GetCurLine(&posAtLine);

#if wxCHECK_VERSION(2,9,0)
    int no_lines = m_control->GetNumberOfLines()-1;
#else
	int no_lines = m_control->GetLineCount()-1;
#endif

    if( (!controlDown && !shiftDown && !altDown) && (key == WXK_RETURN || key == WXK_NUMPAD_ENTER) )
    {
        if( pos != eof )
        {
            m_control->GotoPos(eof);
            return;
        }

        if( line != no_lines )
            return;

        DoProcessLine();

        return;
    }
    else if( key == WXK_UP )
    {
        /** shall add here stuff for history browsing */
        m_control->GotoPos(eof);

        if(m_history.GetCount() == 0 || m_currentHistoryPos >= (int) m_history.GetCount() )
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
		{
			DoClearLastLine();
            return;
		}

        if( posAtLine > 4 )
        {
            DoClearLastLine();
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
            return;

        if( (posAtLine <= 4 && m_control->GetSelectedText().IsEmpty()) )
            return;
			
		if( posAtLine < 4 )
			return;
		
    }
    else if( key == WXK_HOME || key == WXK_NUMPAD_HOME )
	{
		if( line != no_lines )
            return;
		
		m_control->GotoLine(line);
		int pfl = m_control->GetCurrentPos();
		
		m_control->GotoPos(pfl+4);
		return;
	}
    else if( controlDown && altDown )
    {
        event.Skip();
        return;
    }
    else if( key == WXK_ESCAPE )
	{
        DoClearLastLine();
    }
    else if( key == WXK_BACK && controlDown && shiftDown )
	{
        DoClearLastLine();
    }
    else if( key == WXK_LEFT && shiftDown && controlDown )
	{
        if( line != no_lines )
            return;
        
        if( posAtLine <= 4 )
			return;
    }
    else if( key == WXK_LEFT )
	{
        if( line != no_lines )
            return;
        
        if( posAtLine <= 4 )
			return;
    }
    else if( key == WXK_RIGHT )
	{
        if( line != no_lines )
            return;
        
        if( posAtLine < 4 )
			return;
    }
    else
    {
		if( line != no_lines )
            return;
		
		if( posAtLine < 4 )
			return;
	}

    event.Skip();
}

void RheiaPythonConsole::OnStcEvent(wxStyledTextEvent& event)
{

}

bool RheiaPythonConsole::LineHasMarker(int marker, int line)
{
    if (line == -1)
        line = m_control->GetCurrentLine();

    return m_control->MarkerGet(line) & (1 << marker);
}
