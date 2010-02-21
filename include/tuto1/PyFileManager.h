/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef PYFILE_MANAGER_H
#define PYFILE_MANAGER_H

#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaPageContainer.h>
#include <RheiaBookPage.h>
#include <RheiaException.h>

#include <map>

class PyFile;
class PyEditorContext;
class PyEditorBase;
class wxMenuBar;

/**
*   @class PyFileHandler
*   @brief simple class for handling new file types
*
*   Any file that can be loaded in our editor shall be derived from this one
*   any handler will provide info about file loading in PyEditor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class PyFileHandler
{
public :
    /** default constructor for handling a file */
    PyFileHandler(){};

    /** copy ctor */
    PyFileHandler(const PyFileHandler& rhs) {};

    /** Clone method that you have to overload */
    virtual PyFileHandler* Clone() = 0;

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( const wxString& file ) = 0;

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( PyEditorContext* context ) = 0;

    /** Get global extensions */
    virtual wxArrayString GetExtensions() = 0;

    /** Create a new file */
    virtual PyEditorContext* CreateContext( ) = 0;

    /** Get the file names list */
    virtual wxArrayString GetLanguages() = 0;
};

WX_DEFINE_ARRAY( PyFileHandler* , PyFileHandlerArray );
WX_DEFINE_ARRAY( PyFile* , PyFileArray );

typedef std::map<wxString,PyFile*> PyFileMap;

/**
*   @class PyFileManager
*   @brief This is the basic class for managing files in an editor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class PyFileManager : public wxEvtHandler, public RheiaMgr<RheiaManagedFrame,PyFileManager>
{
    friend class RheiaMgr<RheiaManagedFrame,PyFileManager>;
public :
    /**************************************************************************************
    *   STATIC METHODS FOR GENERAL STUFF
    **************************************************************************************/
    /** Static method for adding handlers in this manager */
    static void PushHandler( PyFileHandler* handler );

    /** static method for freeing memory */
    static void RemoveAll();

    /**************************************************************************************
    *   METHODS
    **************************************************************************************/
    /** Build the menu in the given menuBar */
    void BuildMenu( wxMenuBar* menuBar );

    /** Release the menu from the given menu bar */
    void ReleaseMenu( wxMenuBar* menuBar );

    /** Build the toolbar */
    void BuildToolBar(wxWindow* parent);

    /** Notify Editor Closed */
    bool NotifyClose(PyFile* file);

private :
    /** ctor */
    PyFileManager( RheiaManagedFrame* parent );

    /** dtor */
    virtual ~PyFileManager();

    /**************************************************************************************
    *   EVENTS
    **************************************************************************************/
    /** Register handled events */
    void RegisterEvents();

    /** Callback used On ui update */
    void OnOpenFileUI( wxUpdateUIEvent& event );

    /** Callback used On ui update */
    void OnSaveFileUI( wxUpdateUIEvent& event );

    /** Callback used On ui update */
    void OnEditUI( wxUpdateUIEvent& event );

    /** Callback used On ui update */
    void OnMenuEdit( wxCommandEvent& event );

    /** Callback used On ui update */
    void OnSearchUI( wxUpdateUIEvent& event );

    /** On file open */
    void OnFileOpen( wxCommandEvent& event );

    /** On file open */
    void OnFileSave( wxCommandEvent& event );

    /** On file open */
    void OnFileSaveAll( wxCommandEvent& event );

    /** On file open */
    void OnFileSaveAs( wxCommandEvent& event );

    /** On file open */
    void OnFileClose( wxCommandEvent& event );

    /** On file open */
    void OnFileCloseAll( wxCommandEvent& event );

    /** On file open */
    void OnFileCloseAllExceptCurrent( wxCommandEvent& event );

    /** OnAplly Regular expression */
    void OnApplyRegEx( wxCommandEvent& event );

    /** OnAplly Regular expression */
    void AskForFindInFiles( );

    /**************************************************************************************
    *   METHODS
    **************************************************************************************/
    /** Open the given file */
    bool Open(const wxString& filename);

    /** Add a page in the list */
    bool AddFile( const wxString& filename , PyFile* file );

    /** Save file */
    bool SaveFile( PyFile* file , bool force_file = false );

    /** Close file */
    bool CloseFile( PyFile* file , bool askfor = true );

    /** Get current editor */
    PyEditorBase* GetCurrentEditor();

private :
    /** parented managed window */
    RheiaManagedFrame* m_parent;

    /** open files array */
    PyFileMap m_files;
    PyEditorBase* m_currentEditor;
    PyFile* m_currentFile;
    wxString m_lastFind;

    /**************************************************************************************
    *   EVENTS IDS
    **************************************************************************************/
    /*** In the file menu */
    int idCloseCurrent;
    int idCloseAll;
    int idCloseAllOthers;
    int idSaveCurrent;
    int idSaveAs;
    int idSaveAll;
    int idOpen;
    int idNew;

    /*** In the Edit menu */
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
    int idFoldAll;
    int idUnfoldAll;
    int idToggleAllFolds;
    int idFoldCurrentBlock;
    int idUnfoldCurrentBlock;
    int idToggleCurrentBlockFold;
    int idToggleBookMark;
    int idNextBookmark;
    int idPreviousBookMark;
    int idAutoFormatSel;
    int idAutoFormatAll;
    int idCommentSel;
    int idUncommentSel;

    /*** In the Search menu */
    int idMenuSearch;
    int idFind;
    int idFindInFiles;
    int idFindNext;
    int idReplace;
    int idReplaceInFiles;
    int idReplaceNext;
    int idApplyRegEx;

    /*** In the Settings menu */
    int idConfigure;

    /**************************************************************************************
    *   STATICS
    **************************************************************************************/
    /** static objects class for handling handlers */
    static PyFileHandlerArray m_handlers;
};

#endif
