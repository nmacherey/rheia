/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef PYEDITOR_BASE_H
#define PYEDITOR_BASE_H

#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaPageContainer.h>
#include <RheiaBookPage.h>
#include <RheiaException.h>

#include "PyEditorContext.h"

#include <wx/event.h>
#include <wx/menu.h>
#include <wx/treectrl.h>
#include <wx/string.h>
#include <wx/regex.h>
#include <wx/stc/stc.h>
#include <map>

/* imports */
class PyFile;

//const int matchStart          = wxSTC_FIND_WORDSTART;
const int matchCase           = wxSTC_FIND_MATCHCASE;
const int matchWholeWord      = wxSTC_FIND_WHOLEWORD;
const int matchAll            = 0;

const int NUMBER_MARGIN_ID = 0;
const int EDIT_TRACKER_MARGIN_ID = 1;
const int SYMBOLS_MARGIN_ID = 2;
const int SYMBOLS_MARGIN_SEP_ID = 3;
const int FOLD_MARGIN_ID = 4;

#define DEBUGGER_INDICATOR          11
#define MATCH_INDICATOR             10
#define USER_INDICATOR              3
#define HYPERLINK_INDICATOR         4

#define BOOKMARK_MARKER       2
#define BOOKMARK_STYLE        wxSTC_MARK_ARROW

enum SplitWindow
{
    splitNone = 0,
    splitHoriz,
    splitVertical
};

/**
*   @class PyEditorBase
*   @brief This class is a basic wrapper for defining an editor in the python editor
*
*   This class shall be derived from a RheiaBookPage, this is for enabling displaying
*   editors in a book in the rheia framework.
*
*   What we need....
*   1- All editors must be associated to a file
*   2- All editors shall be able to :
*       + Undo
*       + Redo
*       + Copy
*       + Paste
*       + Cut
*       + Clear
*       + Select All
*       + Select a line
*       + Select all occurrences of a word
*       + Find a word
*       + Find/Select next occurence of a word
*       + Replace a word
*       + Replace all occurences of a word
+       + Apply a regular expression
*       + Goto a given line
*       + Save
*       + Notify for modifications
*       + Split (either horizontally or vertically... )
*       + Check if the file opened is Read Only or not
*
*   Accordingly to the last requirements we will wrote methods of the type :
*       bool CanFoo();
*       bool DoFoo();
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class PyEditorBase : public RheiaBookPage
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
    PyEditorBase( RheiaManagedFrame* toplevel , wxWindow* parent , PyFile* container , PyEditorContext* context );

    /** Default dtor (do not forgot to make it virtual...) */
    virtual ~PyEditorBase();

    /** Get the context */
    PyEditorContext* GetContext() {return m_context;};

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** Get the editor associated container */
    PyFile* GetContainer( ) {return m_container;};

    /** Set the editor associated container
    *   @param container new container for this editor
    */
    void SetContainer( PyFile* container );

    /** Reloads the container contents */
    virtual void Reload();

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
    /** Check if the method can undo */
    virtual bool CanUndo() {return true;}

    /** Undo last action */
    virtual void DoUndo(){m_control->Undo();};

    /** Check if the method can Redo */
    virtual bool CanRedo() {return true;}

    /** Redo last action */
    virtual void DoRedo(){m_control->Redo();};

    /** Check if the method can delete */
    virtual bool CanDelete() {return true;}

    /** Delete selected text */
    virtual void DoDelete(){m_control->ReplaceSelection(wxEmptyString);};

    /** Check if the method can Cut */
    virtual bool CanCut() {return true;}

    /** Cut selected text */
    virtual void DoCut(){m_control->Cut();};

    /** Check if the method can Copy */
    virtual bool CanCopy() {return true;}

    /** Copy selected text */
    virtual void DoCopy(){m_control->Copy();};

    /** Check if the method can Paste */
    virtual bool CanPaste() {return true;}

    /** Paste clipboard content */
    virtual void DoPaste(){m_control->Paste();};

    /** Check if the method can Clear */
    virtual bool CanClear() {return true;}

    /** Clear the page */
    virtual void DoClear(){m_control->SelectAll();m_control->ReplaceSelection(wxEmptyString);};

    /** Check if the method can select all the contents */
    virtual bool CanSelectAll() {return true;}

    /** Select All */
    virtual void DoSelectAll(){m_control->SelectAll();};

    /** Check if the method can Select line */
    virtual bool CanSelectLine() {return true;}

    /** Select line */
    virtual void DoSelectLine();

    /** Has selection in the file */
    virtual bool HasSelection() {return false;}

    /** Check if the file is read only or not */
    virtual bool IsReadOnly() {return false;};

    /** Apply the given regular expression */
    virtual void DoApplyRegex( const wxRegEx& expression , const wxString& repStr , bool selOnly = false , bool confirm = true );

    /** Higlight all occurences of the given expression */
    virtual void HighlightRegexMatch( const wxRegEx& expression ){};

    /** Higlight all occurences of the given expression */
    virtual void HighlightOccurrences( const wxString& expr , int flag = matchAll );

    /** Find all occurences of the given expression
    *   @return the number of matches for the given expression
    */
    virtual int Find( const wxString& expr , int flag = matchAll ){};

    /** Find next occurence of the given expression */
    virtual int FindNext( const wxString& expr , int flag = matchAll ){};

    /** Find all occurences of the given expression */
    virtual void Replace( const wxString& expr , int flag = matchAll ){};

    /** Find next occurence of the given expression */
    virtual void ReplaceNext( const wxString& expr , int flag = matchAll ){};

    /** Goto the given line */
    virtual void Goto( int line ) {};

    /** Clear undo redo history */
    virtual bool CanClearHistory() {return true;};

    /** Clear undo redo history */
    virtual void DoClearHistory() {m_control->EmptyUndoBuffer();};

    /** Check if the method can save */
    virtual bool CanSave() {return false;}

    /** Save file */
    virtual void DoSave(){};

    /** Check if the method can save as */
    virtual bool CanSaveAs() {return false;}

    /** Save the file in a new file */
    virtual void DoSaveAs(){};

    /** Toggle bookmark at specified line.
    * @param line The line to toggle the bookmark on. If @c line is -1,
    *             use current line.
    */
    virtual void ToggleBookmark(int line = -1);

    /** Does @c line has bookmark?
    * @param line The line to check for bookmark existence.
    * @return True if there is a bookmark on this line, false if not.
    */
    virtual bool HasBookmark(int line) const { return false; };

    /** Go to next bookmark. */
    virtual void GotoNextBookmark();

    /** Go to previous bookmark. */
    virtual void GotoPreviousBookmark();

    /** check if the window can be splitted */
    virtual bool CanSplit(){return false;};

    /** Split the window */
    virtual void Split( SplitWindow type ) {};

    /** Check if the window is already splitted */
    virtual bool IsSplitted() {return false;};

    /** Get the currently splitted type */
    virtual SplitWindow GetCurrentSplit() {return splitNone;};

    /** check if the window can be unsplitted */
    virtual bool CanUnsplit(){return false;};

    /** Unsplit the current window */
    virtual void Unsplit() {};

    /** Get the title for this page */
    virtual wxString GetTitle() {return wxEmptyString;};

    /** Check if the editor cna fold */
    virtual bool CanFold() {return true;};

    /** Fold all folding possibilities */
    virtual void DoFoldAll();

    /** UnFold all folding possibilities */
    virtual void DoUnfoldAll();

    /** Toggle all folds */
    virtual void DoToggleAllFolds();

    /** Fold current */
    virtual void DoFoldCurrentBlock();

    /** Unfold Current */
    virtual void DoUnFoldCurrentBlock();

    /** Toggle Current fold */
    virtual void DoToggleCurrentBlockFold();

    /** check if the selection can be autoformated */
    virtual bool CanFormatSelection() {return false;}

    /** format the selection */
    virtual void DoFormatSelection() {};

    /** check if can autoformat the entire file */
    virtual bool CanFormat() {return false;}

    /** format the entire file */
    virtual void DoFormat() {};

    /** check if the editor can comment */
    virtual bool CanComment() {return false;}

    /** comment selection */
    virtual void DoComment() {};

    /** uncomment selection */
    virtual void DoUncomment() {};

    /** Add the context menu in the given context menu stuff
    *   @param menu the menu in which you should append your editor's specific options
    */
    virtual void AddContextMenuStuff( wxMenu* menu ) {};

    virtual bool GetModified();

protected :
    /**************************************************************************************
    *   ATTRIBUTES
    **************************************************************************************/
    /** container for this editor */
    PyFile* m_container;
    RheiaManagedFrame* m_parent;
    PyEditorContext* m_context;
    wxStyledTextCtrl* m_control;
    int m_ID;

    /**************************************************************************************
    *   EVENT IDS
    **************************************************************************************/
    int idCloseMe;
    int idCloseAll;
    int idCloseAllOthers;
    int idSaveMe;
    int idSaveAs;
    int idSaveAll;
    int idSplitHoriz;
    int idSplitVertical;
    int idUnsplit;
    int idUndo;
    int idRedo;
    int idCut;
    int idCopy;
    int idPaste;
    int idDelete;
    int idClearHistory;
    int idSelectAll;
    int idSelectLine;
    int idFind;
    int idFindNext;
    int idReplace;
    int idReplaceNext;
    int idToggleBookMark;
    int idNextBookmark;
    int idPreviousBookMark;
    int idAutoFormatSel;
    int idAutoFormatAll;
    int idConfigure;
    int idProperties;
    int idFoldAll;
    int idUnfoldAll;
    int idToggleAllFolds;
    int idFoldCurrentBlock;
    int idUnfoldCurrentBlock;
    int idToggleCurrentBlockFold;
    int idCommentSel;
    int idUncommentSel;

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
    /** calback used when the user wants to close the current document */
    void OnCloseMe( wxCommandEvent& event );

    /** calback used when the user wants to close all opened documents */
    void OnCloseAll( wxCommandEvent& event );

    /** calback used when the user wants to close all opened documents except me */
    void OnCloseAllButMe( wxCommandEvent& event );

    /** calback used when the user wants to save the current document */
    void OnSameMe( wxCommandEvent& event );

    /** calback used when the user wants to save all opened documents */
    void OnSaveAll( wxCommandEvent& event );

    /** calback used when the user wants to save the current document in a new file */
    void OnSaveMeAs( wxCommandEvent& event );

    /** callback used for CanFoo DoFoo related methods */
    void OnContextMenu(wxCommandEvent& event);

    /** calback used when the user wants to configure the editor */
    void OnConfigureEditor(wxCommandEvent& event);

    /** callback used when the user wants to change properties */
    void OnFileProperties( wxCommandEvent& event );

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

    /** Register events */
    void RegisterSTCEvents();

    /** define a marker */
    void DefineMarker(int marker, int markerType, wxColor fore, wxColor back);

    /** Do fold the given line */
    void DoFoldLine( int line , int fold );

    /** Do fold the given line */
    void FoldBlockFromLine(int line = -1);
    /** Do fold the given line */
    void UnfoldBlockFromLine(int line = -1);
    /** Do fold the given line */
    void ToggleFoldBlockFromLine(int line = -1);
    /** Do fold the given line */
    void DoFoldBlockFromLine(int line, int fold);

    /** Line has marker */
    bool LineHasMarker(int marker, int line = -1);

    /** Toggle marker */
    void MarkerToggle( int marker, int line = -1 );

    /** Goto the next marker of the given type */
    void MarkerNext(int marker);

    /** Goto previous marker */
    void MarkerPrevious( int marker );

    DECLARE_EVENT_TABLE()
};

#endif

