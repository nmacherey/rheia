/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef PYCONSOLE_H
#define PYCONSOLE_H

#include <iostream>
#include <RheiaPythonUtils.h>
#include "RheiaPythonLayout.h"
#include "RheiaBookPage.h"

#include <pythonrun.h>

#include <wx/thread.h>

class wxSStyledTextCtrl : public wxStyledTextCtrl, public std::streambuf
{
public :
	wxSStyledTextCtrl( wxWindow *parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0 ) : wxStyledTextCtrl( parent , id , pos, size , style ){};

protected :
	int overflow(int i){
		AppendText((wxChar)i);
		// return something different from EOF
		return 0;
	};
};

/*********************************************************************************************************//**
*	@class wxStreamToTextRedirector
*
*	@brief The wxStreamToTextRedirector class is made for enabling the redirection of a stream to a textctrl
*
*	This class has been taken from as well as the original wxWidgets one
*************************************************************************************************************/
class wxSStreamToTextRedirector
{
private:
    void Init(wxSStyledTextCtrl *text)
    {
        m_sbufOld = m_ostr.rdbuf();
        m_ostr.rdbuf(text);
    }

public:
    wxSStreamToTextRedirector(wxSStyledTextCtrl *text , wxSTD ostream& _m_ostr )
        : m_ostr(_m_ostr)
    {
        Init(text);
    }

    wxSStreamToTextRedirector(wxSStyledTextCtrl *text, wxSTD ostream *ostr)
        : m_ostr(*ostr)
    {
        Init(text);
    }

    ~wxSStreamToTextRedirector()
    {
        m_ostr.rdbuf(m_sbufOld);
    }

private:
    // the stream we're redirecting
    wxSTD ostream&   m_ostr;

    // the old streambuf (before we changed it)
    wxSTD streambuf *m_sbufOld;
};

class RheiaPythonConsole : public RheiaBookPage
{
public :

    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /**
    *   Base ctor,
    *   @param parent the parent window in which the editor shall be created
    *   @param container the PyFile which handles the data displayed in the container
    */
    RheiaPythonConsole( RheiaManagedFrame* toplevel , wxWindow* parent );

    /** Default dtor (do not forgot to make it virtual...) */
    virtual ~RheiaPythonConsole();

    /** Reloads the container contents */
    virtual void Reload();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** save the content in the given filename */
    bool Save( const wxString& filename );

    /** load the content from the given filename */
    bool Load( const wxString& filename );

    /**
    *   Callback method used when the page is changing in the main book.
    *   you must overload this method if you want to do specific stuff
    *   when the user is changing the current selected page
    *
    *   @return true if the application allow for page changing false else
    */
    virtual bool OnPageChanging(){return true;};

    /**
    *   Callback method used when the page is changed in the main book.
    *   you must overload this method if you want to do specific stuff
    *   when the user is changing the current selected page
    */
    virtual bool OnPageChanged(){return true;};

    /**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual void OnPageClosed(){};

    /**
    *   Callback used when the information has benn modified outside
    *   the application.
    *   You must overload this method in order to refresh information about
    *   the page content when its requested
    */
    virtual void OnPageUpdate() {};

    /**
    *   Callback used on OnDelete()
    */
    virtual void OnDelete() {};

    /**
    *   Callback used when creating the panel
    */
    virtual void OnCreate(){};

    /**************************************************************************************
    *   EDITION
    **************************************************************************************/

    /** Delete selected text */
    virtual void DoDelete();

    /** Cut selected text */
    virtual void DoCut();

    /** Copy selected text */
    virtual void DoCopy();

    /** Paste clipboard content */
    virtual void DoPaste();

    /** Check if the method can Clear */
    virtual bool CanClear() {return true;}

    /** Clear the page */
    virtual void DoClear(){m_control->SelectAll();m_control->ReplaceSelection(wxEmptyString);m_control->SetText(wxT(">>>"));};

    /** Select All */
    virtual void DoSelectAll(){m_control->SelectAll();};

    /** Clear undo redo history */
    virtual void DoClearHistory() {m_control->EmptyUndoBuffer();};

    /** Get the title for this page */
    virtual wxString GetTitle() {return wxEmptyString;};

protected :
    /**************************************************************************************
    *   ATTRIBUTES
    **************************************************************************************/
    /** container for this editor */
    RheiaManagedFrame* m_parent;
    RheiaPythonLayout* m_context;
    wxSStyledTextCtrl* m_control;
    wxSStreamToTextRedirector *m_stdoutred;
    wxSStreamToTextRedirector *m_stderrred;
    wxString m_commandBuffer;
    int m_nolines;
    int m_ID;

    wxArrayString m_history;
    int m_currentHistoryPos;
    /**************************************************************************************
    *   EVENT IDS
    **************************************************************************************/
    int idSaveMe;
    int idSaveAs;
    int idCut;
    int idCopy;
    int idPaste;
    int idDelete;
    int idClearHistory;
    int idSelectAll;
    int idSelectLine;

    /**************************************************************************************
    *   METHODS
    **************************************************************************************/
    /** this method is used to build the context menu in the editor
    * it will call PyEditorBase::AddContextMenuStuff() in order to allow any
    * editor to add specific menu options to the displayed context menu */
    wxMenu* BuilContextMenu();

    /** On request context menu */
    void OnRequestContextMenu( wxContextMenuEvent& event );

    /** this method is used to connect events */
    void Registerevents();

    /**************************************************************************************
    *   CONTEXT MENU CALLBACKS
    **************************************************************************************/
    /** calback used when the user wants to save the current document */
    void OnSaveMe( wxCommandEvent& event );

    /** calback used when the user wants to save the current document in a new file */
    void OnSaveMeAs( wxCommandEvent& event );

    /** callback used for CanFoo DoFoo related methods */
    void OnContextMenu(wxCommandEvent& event);

    /**************************************************************************************
    *   CALLBACKS FOR SCINTILLA EVENTS
    **************************************************************************************/
    /** Used when the user clicks on the margin */
    void OnMarginClick(wxStyledTextEvent& event);

    /** Used when the something change in the user interface */
    void OnUpdateUI(wxStyledTextEvent& event);

    /** Used when something change in the control */
    void OnChange(wxStyledTextEvent& event);

    /** Used when a new char is added when editing in the control */
    void OnCharAdded(wxStyledTextEvent& event);

    /** Used for tool tips */
    void OnDwellStart(wxStyledTextEvent& event);

    /** Used for tool tips */
    void OnDwellEnd(wxStyledTextEvent& event);

    /** Used when the file has been modified */
    void OnModified(wxStyledTextEvent& event);

    /** Used when the user uses the zoom in the editor */
    void OnZoom(wxStyledTextEvent& event);

    /** General method to follow events from scintilla not managed basically by the editor */
    void OnStcEvent(wxStyledTextEvent& event);

    /** called when the user press a key */
    //void OnStcKey(wxStyledTextEvent& event);

    /** called when the user press a key */
    void OnStcKey(wxKeyEvent& event);

    /** Register events */
    void RegisterSTCEvents();

    /** define a marker */
    void DefineMarker(int marker, int markerType, wxColor fore, wxColor back);

    /** Line has marker */
    bool LineHasMarker(int marker, int line = -1);



    DECLARE_EVENT_TABLE()
};


#endif
