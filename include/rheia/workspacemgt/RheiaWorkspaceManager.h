/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#ifndef RheiaWorkspaceManager_h_
#define RheiaWorkspaceManager_h_

#include <RheiaWMgtSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventPlugin.h>
#include <RheiaEventFrame.h>
#include <RheiaBookPage.h>
#include <RheiaPageContainer.h>
#include <RheiaMenuManager.h>

#include <wx/event.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>

#include <map>

class wxAuiNotebook;
class wxAuiToolBar;
class wxTreeCtrl;
class wxTreeItemId;
class wxImageList;
class wxToolBar;

class RheiaWorkspace;
class RheiaEnvironmentPlugin;
class RheiaProject;
class RheiaWorkspaceManager;
class RheiaWorkspaceBookPage;

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;

/*! Associate a wxString to a RheiaWorkspace */
typedef std::map< wxString , RheiaWorkspace* > RheiaWorkspaceTable;

/*! Associate a wxString to a bool for marking workspace as saved or not */
typedef std::map< wxString , bool > RheiaWorkspaceSavingTable;

/**
*	@class RheiaWorkspaceManager
*	@brief RheiaWorkspaceManager is the manager class available for managing workspaces in the
*	main application.
*
*	RheiaWorkspaceManager manages the content of the "left pane" or the management window. Hence
*	it manages all instanciated workspaces and relative event when selecting an item in the wxTreeCtrl.
*	As any other Rheia module you can use RheiaWorkspaceManager::Get() to access to its global instance.
*
*	@note All general workspace management informations must developped in this object
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
class WMGT_DLLEXPORT RheiaWorkspaceManager : public wxEvtHandler , public RheiaPageContainer , public RheiaMgr<RheiaManagedFrame,RheiaWorkspaceManager>
{

	struct WorkspaceInfo{
			xmlNode* root;
			xmlDoc* doc;
	};

	typedef std::map< wxString , WorkspaceInfo > WorkspaceInfoMap;

public :
	friend class RheiaMgr<RheiaManagedFrame,RheiaWorkspaceManager>;				/*!< Give our private member access to Singleton */
	friend class RheiaManager;								/*!< Give our private member access to RheiaManager */
	friend class RheiaWorkspaceBookPage;

	/**********************************************************************************************************
	*	METHODS
	**********************************************************************************************************/
	/*! Returns the Management Tree */
	wxTreeCtrl* GetManagementTree( void ) {return m_tree;};

	/*! Returns the Management Tree Root */
	wxTreeItemId& GetManagementTreeRoot( void ) {return m_treeRoot;};

	/** Create the window */
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );

	/** Reload tree.. */
	void ReloadWorkspaceTree();

	/** Get the bitmap */
	virtual const wxBitmap& GetBitmap( const int& size );

	/** reload Config */
	void ReloadConfig();

	/** Register Events */
	void RegisterEvents();

	/** Callback used when wksp mgr settings are updated */
	void OnSettingsChanged( wxCommandEvent& event );

	/** Callback used when wksp mgr settings are updated */
	void OnEnvironmentPluginDetach( RheiaPluginEvent& event );

	/*! Add a new RheiaWorkspace to the workspace table
	*	@param workspace the workspace to be added
	*	@param name name of the workspace to be added
	*/
	bool AddWorkspace( RheiaWorkspace *workspace, wxString name );

	/*! Specifies if the workspace exists accordingly to its name
	*	@param name Workspace name to find
	*/
	bool Exists( wxString name );

	/*! Find a workspace in the table by its name
	*	@param name Workspace name to find
	*/
	RheiaWorkspace * FindWorkspace( const wxString name );

	/*! Return the m_workspaces (i.e : get all opened workspaces */
	RheiaWorkspaceTable& GetWorkspaceTable(){return m_workspaces;};

	/*! Get the currently selected workspace or active workspace */
	wxString GetCurrentSelectedWorkspace( void ) {return m_currentWorkspace;};

	/*! Set the currently selected workspace */
	void SelectWorkspace( wxString name );

	/*! Select the given project name in the tree */
	void SelectProject( wxString name );

	/*! This method is used when we want to load a workspace via its workspace plugin
	*	@param filename File's name for loading the workspace
	*/
	RheiaWorkspace *LoadWorkspace(wxString filename);

	/*! This method is used when we need to save a workspace
	*	@param workspace RheiaWorkspace to save
	*/
	bool SaveWorkspace( RheiaWorkspace *workspace );

	/**
	*   This function is used when you need to remove/close and existing
	*   workspace.
	*/
	bool RemoveWorkspace( const wxString& name );

	/**
	*   Remove projects from all workspaces for the given environement plugin
	*   This function will search for all workspaces and projects eventually
	*   attached to the given plugin and remove them from their workspaces
	*/
	bool RemoveProjectsFor( RheiaEnvironmentPlugin* plugin , bool confirmation = false );

    /** Finalize start up */
    void FinalizeStartUp();

    /**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed(){m_tree = NULL;return true;};

public :
    /**********************************************************************************************************
    *   EVENTS MANAGEMENT
    **********************************************************************************************************/
    /** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( wxMenuBar* menuBar );

	/** Callback used when the user want to manage environment variables */
	void OnConfigure(wxCommandEvent& event);

    /** Used when we act on the file menu new workspace item */
	void OnFileWorkspaceNew( wxCommandEvent &event );

	/** Used when we act on the file menu open workspace item */
	void OnFileWorkspaceOpen( wxCommandEvent &event );

	/** Used when we act on the file menu save workspace item */
	void OnFileWorkspaceSave( wxCommandEvent &event );

	/** Used when we act on the file menu save all workspace s item */
	void OnFileWorkspaceSaveAll( wxCommandEvent &event );

	/** Used when we act on the file menu close workspace item */
	void OnFileWorkspaceClose( wxCommandEvent &event );

    /** Used when we act on the file menu new project's item */
	void OnFileProjectNew( wxCommandEvent &event );

	/** Used when we act on the file menu open project's item */
	void OnFileProjectOpen( wxCommandEvent &event );

	/** Used when we act on the file menu save project's item */
	void OnFileProjectSave( wxCommandEvent &event );

	/** Used when we act on the file menu save as project's item */
	void OnFileProjectSaveAs( wxCommandEvent &event );

	/** Used when we act on the file menu close project's item */
	void OnFileProjectClose( wxCommandEvent &event );

	/** Build the workspace manager toolbar */
	wxAuiToolBar* BuildToolBar(wxWindow* parent);

	/** Build the projects toolbar */
	wxAuiToolBar* BuildProjectsToolBar(wxWindow* parent);

	/** Close all workspaces method */
	bool SaveAll();

	/** Used when my associated frame is closing */
	void OnCloseParent( RheiaFrameEvent& event );
	
	/** callback used when menus are recreated */
	void OnMenuRecreated( RheiaEvent& event );

private :
	/**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/*! Default constructor */
	RheiaWorkspaceManager(RheiaManagedFrame* parent);

	/*! Default destructor */
	~RheiaWorkspaceManager();

private :
	/**********************************************************************************************************
	*	MANAGEMENT TREE VARIABLES
	**********************************************************************************************************/
	wxTreeCtrl *m_tree;								/*!< Management tree wxTreeCtrl */
	wxTreeItemId m_treeRoot;						/*!< Management tree root item */
	wxImageList *m_treeImages;						/*!< Management tree assigned image list */

	/**********************************************************************************************************
	*	AVAILABLE WORKSPACES VARIABLES
	**********************************************************************************************************/
	RheiaWorkspaceTable m_workspaces;						/*!< Table of opened workspaces */
	WorkspaceInfoMap m_workspaceInfos;
	wxString m_currentWorkspace;						/*!< index of the currently selected workspace in the table */

private :
	/*! Control used when selecting an element in the management tree */
	void OnManagementTreeSelection(wxTreeEvent& event);

	/*! Control used when selecting an element in the management tree */
	void OnManagementTreeDClick(wxTreeEvent& event);

	/** These methods are for managing last workspaces files */
	wxArrayString m_LastFiles;
	wxString m_Last;
	
	wxArrayString m_LastProjectFiles;
	wxString m_LastProject;

	RheiaManagedFrame* m_parent;
	wxBitmap m_bmp;

public :
	/** Add a workspace to the last workspace list */
	bool AddLast( const wxString& path );

	/** Sets the last workspace and write it in the configuration file */
	bool SetLast( const wxString& path );
	
	/** Add a workspace to the last workspace list */
	bool AddLastProject( const wxString& path );

	/** Sets the last workspace and write it in the configuration file */
	bool SetLastProject( const wxString& path );
	
	/** Loads the last workspace */
	bool LoadLast();
	
	/** Loads the last workspace */
	bool LoadLastProject();
	
	/** Loads the last workspace */
	bool LoadProject(const wxString& path);

	/** Recreates the last files menus in the menubar */
	void RecreateLastMenu();
	
	/** Recreates the last files menus in the menubar */
	void RecreateLastProjectsMenu();

	void OnRecentOpen( wxCommandEvent& event );
	void OnRecentProjectOpen( wxCommandEvent& event );

private :
#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};

/**
*   @brief Main page for displaying the workspace manager
*/
class RheiaWorkspaceBookPage : public RheiaBookPage
{
    friend class RheiaWorkspaceManager;

public :

    /**
    *   Basic constructor
    *
    *   @param parent the parent window in which the panel shall be created
    */
    RheiaWorkspaceBookPage( wxWindow* parent , RheiaWorkspaceManager* wmgr ):
		RheiaBookPage(parent),
		m_wmgr(wmgr)
    {
        wxPanel::Create(parent,wxID_ANY);
        m_sizer = new wxBoxSizer( wxVERTICAL );
    }


    /** Default destructor */
    virtual ~RheiaWorkspaceBookPage()
    {

    }

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

protected :
    RheiaWorkspaceManager* m_wmgr;
    wxSizer* m_sizer;
};

#endif
