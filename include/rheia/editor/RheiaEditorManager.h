/**
*   @file RheiaEditorManager.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef RheiaEditor_MANAGER_H
#define RheiaEditor_MANAGER_H

#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaPageContainer.h>
#include <RheiaBookPage.h>
#include <RheiaException.h>

#include <wx/stc/stc.h>

#include "RheiaEditorSettings.h"

#include <map>

class RheiaEditorFile;
class RheiaEditorLayout;
class RheiaEditorBase;
class wxMenuBar;
class wxToolbar;
class wxStaticText;
class wxTextCtrl;

const int matchStart          = wxSTC_FIND_WORDSTART;
const int matchCase           = wxSTC_FIND_MATCHCASE;
const int matchWholeWord      = wxSTC_FIND_WHOLEWORD;
const int matchAll            = 0;

/**
*   @class RheiaEditorHandler
*   @brief simple class for handling new file types
*
*   Any file that can be loaded in our editor shall be derived from this one
*   any handler will provide info about file loading in RheiaEditorFile
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class RheiaEditorHandler
{
public :
    /** default constructor for handling a file */
    RheiaEditorHandler(){};

    /** copy ctor */
    RheiaEditorHandler(const RheiaEditorHandler& /*rhs*/) {};

    /** Clone method that you have to overload */
    virtual RheiaEditorHandler* Clone() = 0;

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( const wxString& file ) = 0;

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( RheiaEditorLayout* context ) = 0;

    /** Get global extensions */
    virtual wxArrayString GetExtensions() = 0;

    /** Create a new file */
    virtual RheiaEditorLayout* CreateContext( ) = 0;

    /** Get the file names list */
    virtual wxArrayString GetLanguages() = 0;
};

WX_DEFINE_ARRAY( RheiaEditorHandler* , RheiaEditorHandlerArray );
WX_DEFINE_ARRAY( RheiaEditorFile* , RheiaEditorArray );

typedef std::map<wxString,RheiaEditorFile*> RheiaEditorMap;

/**
*   @class RheiaEditorManager
*   @brief This is the basic class for managing files in an editor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaEditorManager : public wxEvtHandler, public RheiaMgr<RheiaManagedFrame,RheiaEditorManager>
{
    friend class RheiaMgr<RheiaManagedFrame,RheiaEditorManager>;
public :

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
    bool NotifyClose(RheiaEditorFile* file);

private :
    /** ctor */
    RheiaEditorManager( RheiaManagedFrame* parent );

    /** dtor */
    virtual ~RheiaEditorManager();

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
    bool AddFile( const wxString& filename , RheiaEditorFile* file );

    /** Save file */
    bool SaveFile( RheiaEditorFile* file , bool force_file = false );

    /** Close file */
    bool CloseFile( RheiaEditorFile* file , bool askfor = true );

    /** Get current editor */
    RheiaEditorBase* GetCurrentEditor();
	
	/**************************************************************************************
    *   FIND / REPLACE METHODS
    **************************************************************************************/
	/** Find the given expression int the given editor
	 * @param editor Editor in which the expression shall be found
	 * @param expr Expression to find
	 * @param flag one of the wxSCI_FIND_WHOLEWORD, wxSCI_FIND_WORDSTART, wxSCI_FIND_MATCHCASE flags
	 * @param selOnly specify if the find shall be done in the selected teext only ot not
	 * @return the current position for the first expression found in the editor or 
	 * -1 if the expression does not exists
	 */
	int FindIn( RheiaEditorBase* editor , const wxString& expr , int flag , bool selOnly );
	
private :
    /** parented managed window */
    RheiaManagedFrame* m_parent;

    /** open files array */
    RheiaEditorMap m_files;
	RheiaEditorFile* m_currentFile;
    RheiaEditorBase* m_currentEditor;
    wxString m_lastFind;
	
	wxToolBar* m_tbEdition;
	wxToolBar* m_tbPythonTools;
	
	wxStaticText* m_txtGoto;
	wxTextCtrl* m_txtGotoLine;
	wxStaticText* m_stFind;
	wxTextCtrl* m_txtFind;

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
	int idFindPrevious;
    int idReplace;
    int idReplaceInFiles;
    int idReplaceNext;
    int idApplyRegEx;

    /*** In the Settings menu */
    int idConfigure;
	
	/** @struct InternalFindData
	 * @brief basic class fo storing find info internally
	 */
	struct InternalFindData
	{
		wxString expr;
		int start;
		int end;
		bool selOnly;
		int pos;
		int flag;
	};
	
	InternalFindData m_findData;
};

/**
*   @class RheiaEditorFactory
*   @brief This is the basic class for managing files in an editor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaEditorFactory : public Singleton<RheiaEditorFactory>
{
    friend class Singleton<RheiaEditorFactory>;
public :
    /**************************************************************************************
    *   STATIC METHODS FOR GENERAL STUFF
    **************************************************************************************/
    /** Static method for adding handlers in this manager */
    void PushHandler( RheiaEditorHandler* handler );
	
	/** Static method for removing handlers in this manager */
    void RemoveHandler( RheiaEditorHandler* handler );

    /** static method for freeing memory */
    void RemoveAll();
	
	/** static objects class for handling handlers */
    RheiaEditorHandlerArray m_handlers;
	
private :
	RheiaEditorFactory() {};
	~RheiaEditorFactory();
};


/**
 * @class RheiaEditorHandlerRegistrant
 * @brief base template class for registering file handlers in the RheiaEditorManager
 * @author Nicolas Macherey (nm@graymat.fr)
 * @date 14-February-2009
 * @version 0.1.0
 */
template<class T> class RheiaEditorHandlerRegistrant
{
public:
	/**
	*   Base constructor
	*   When building this object we regiter the template class T given in the
	*   template cast and the build and destroy method.
	*	@param name The configuration tool's name, commonly it is the object name.
	*/
	RheiaEditorHandlerRegistrant( )
	{
		m_instance = new T();
		RheiaEditorFactory::Get()->PushHandler( m_instance );
	}

	/** default destructor */
	~RheiaEditorHandlerRegistrant()
	{
	    RheiaEditorFactory::Get()->RemoveHandler( m_instance );
	}
	
private :
    T* m_instance;
};

#define REGISTER_EDITOR_HANDLER(object) \
    namespace { \
        RheiaEditorHandlerRegistrant<object> object##Registrant; \
    }

#endif
