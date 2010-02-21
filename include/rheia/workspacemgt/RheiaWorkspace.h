/**
*   @file RheiaWorkspace.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added modifications of RheiaProject to be
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 08-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaWorkspace_h_
#define RheiaWorkspace_h_

#include <RheiaWMgtSettings.h>
#include <RheiaTreeItem.h>

#include <wx/event.h>
#include <wx/treectrl.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* wx imports */
class wxString;
class wxTreeCtrl;
class wxMenu;
class wxMenuBar;
class wxFrame;
class wxAuiManager;
class RheiaManagedFrame;

/* Rheia imports */
class RheiaProject;
class RheiaWorkspaceManager;

///*! associate a wxString to a RheiaProject object pointer */
//typedef std::map< wxString , RheiaProject* > RheiaProjectTable;

/**
*	@class RheiaWorkspace
*
*	@brief The RheiaWorkspace class is the base class for adding a workspace.
*
*	A RheiaWorskpace is defined by a plugin.
*	A workspace when created must handle events and add its different information in the different
*	Rehia layout elements, menu and tool bars.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 08-Nov-2008
*/
class WMGT_DLLEXPORT RheiaWorkspace : public RheiaTreeItem
{

    DECLARE_DYNAMIC_CLASS(RheiaWorkspace)

	/** Give our private member access to RheiaWorkspaceManager */
	friend class RheiaWorkspaceManager;

	/** Give our private member access to RheiaWorkspaceLoader */
	friend class RheiaWorkspaceLoader;
public :
	/*************************************************************************************************
											CONSTRUCTORS
	*************************************************************************************************/
	/** Base constructor, the file name is optional, and can be change during run-time.
	*	@param owner The owner plugin for the workspace
	*	@param filename The filename in which to save the project configuration (optional)
	*	@param name name of the workspace displayed in the box
	*/
	RheiaWorkspace( RheiaManagedFrame* parent,
        const wxString& filename = wxEmptyString ,
		const wxString& name = wxEmptyString );

    /** Default ctor */
	RheiaWorkspace(  );

    /*************************************************************************************************
											CONSTRUCTORS
	*************************************************************************************************/
	/** Base constructor, the file name is optional, and can be change during run-time.
	*	@param owner The owner plugin for the workspace
	*	@param filename The filename in which to save the project configuration (optional)
	*	@param name name of the workspace displayed in the box
	*/
	void Create( RheiaManagedFrame* parent,
        const wxString& filename = wxEmptyString ,
		const wxString& name = wxEmptyString );

	/** Destructor */
	virtual ~RheiaWorkspace();

	/** Clone method */
    virtual RheiaTreeItem* Clone();

	/** Copy constructor
	*	@param Wksp Reference object from which to copy info
	*/
	RheiaWorkspace( RheiaWorkspace& Wksp );

	virtual const wxBitmap& GetBitmap( const int& size );

	/*************************************************************************************************
	*	METHODS
	*************************************************************************************************/
//	/** Create workspace items in the Configuration Tree.
//	*	This method is called when attaching the workspace to the main frame. This method
//	*	is virtual pure, you has to derive it for any type of workspace.
//	*
//	*	@param Tree The wxTreeCtrl in which we want to create the configuration Tree
//	*	@param root	The node of the @c Tree treat as root node for creating tree items of
//	*				the workspace
//	*/
//	virtual void CreateManagementTree( wxTreeCtrl *Tree , const wxTreeItemId& root );
//
//	/*! Create workspace items in the Configuration Tree.
//	*	This method is called when attaching the workspace to the main frame. This method
//	*	is virtual pure, you has to derive it for any type of workspace.
//	*
//	*	@param Tree The wxTreeCtrl in which we want to create the configuration Tree
//	*	@param root	The node of the @c Tree treat as root node for creating tree items of
//	*				the workspace
//	*/
//	virtual void UpdateManagementTree( wxTreeCtrl *Tree , const wxTreeItemId& root );


//	/*! Specifies if the workspace has been modified in any way.
//	*
//	*	@return True if the workspace is modified in any way. */
//	virtual bool HasBeenModified();
//
//	/*! Mark the workspace as modified or not.
//	*	This function shall be derived by any workspace in order to manage specific info
//	*	when marking the workspace has modified.
//	*
//	* @param modified If true, the workspace is marked as modified. If false, as not-modified.
//	*/
//	virtual void SetHasBeenModified(bool modified = true);

	/*! Returns the workspace's name */
	virtual wxString GetName( void ) const { return Name; };

	/*! Returns the workspace's File Name */
	virtual wxString GetFileName( void ) const { return FileName; };

	/*! Returns the workspace's path */
	virtual wxString GetPath( void );

	/*! Renames the workspace
	*	@param name new name for the workspace
	*	@param confirm specifies if the user should be asked for a confirmation dialog about the workspace name
	*
	*	@return Returns true if the name has been modified, false any else
	*
	*	@note This function changes the name of the workspace, and displays the new name where it has to be.
	*	untill the workspace is not saved, the modifications will not be taken into account. Hence this just
	*	renames the workspace in run - time.
	*/
	virtual bool Rename( const wxString& name , bool confirm = false ) {return true;};

	/**********************************************************************************
    *   EVENT RELATED METHODS
    **********************************************************************************/
    /** this method is called when the user will act on the tree by simply selecting the item */
    virtual void OnItemSelected() {};

    /** this method is called when the user double cliks on the item tree */
    virtual void OnItemActivated() {};

    /** this method is used to build specific menu information about the item when the user
    *   request it
    */
    virtual void OnRequestContextMenu( wxMenu* menu ) {};

    /** this method is used whent the item is about to be deleted */
    virtual void OnPreDelete() {};

    /** this method is used whent the item is about to be dragged */
    virtual bool OnBeginDrag() {return false;};

    /** this method is used whent the item is about to be dragged */
    virtual bool OnEndDrag() {return false;};

//	/*! This is used to get the whole project table for the workspace */
//	RheiaProjectTable &GetProjectTable(void){ return ProjectTable;};
//
//	/*! This function is used to add a project to the workspace's projects table
//	*
//	*	@param name name of the project to add
//	*	@param project pointer to the RheiaProject to add in the workspace
//	*/
//	virtual bool AddProject( wxString name, RheiaProject* project );
//
//	/*! Finds a Specific project in the workspace map by its name
//	*	@param name Name of the project to get
//	*/
//	RheiaProject *FindProjectByName( const wxString name );
//
//	/*! Removes a project in the workspace map by its name
//	*	@param name Name of the project to remove
//	*	@param confirm specifies if the workspace shall ask for a confirmation for the removal
//	*/
//	virtual bool RemoveProject( const wxString name , bool confirm = true );
//
//	/*! Removes a project in the workspace map by its RheiaProject Ptr
//	*	@param project RheiaProject pointer of the project to remove
//	*	@param confirm specifies if the workspace shall ask for a confirmation for the removal
//	*/
//	virtual bool RemoveProject( RheiaProject* project , bool confirm = true );
//
//	/*! This method returns the management tree root item */
//	wxTreeItemId& GetManagementTreeRoot( void )	{return WorkspaceManagementRoot;};
//
//	/*! Specifies if a project exists in the project table or not */
//	bool ProjectExists( wxString name );

//	/*! Returns the array of project names */
//	wxArrayString& GetProjectNames();

//    /** Get the workspace currently selected project */
//    wxString& GetCurrentProject() {return CurrentProject;};
//
//    /** Sets the workspace currently selected project */
//    void SetCurrentProject( wxString name ) {CurrentProject = name;};

    /** Changes the workspace name */
    void SetName( const wxString& name ) {Name = name;};

    /** Changes the workspace name */
    void SetFileName( const wxString& file ) {FileName = file;};

protected :
	/*************************************************************************************************
	*	PRIVATE VARIABLES
	*************************************************************************************************/
	wxString FileName;											/*!< File name of the workspace */
	bool isLoaded;												/*!< Specifies if the workspace has been fully loaded or not */
	wxString Name;												/*!< Name of the workspace in GRAYMAT BOX choosen by the user */
	//RheiaProjectTable ProjectTable;								/*!< All projects available in the workspace */
	//wxArrayString ProjectsNames;								/*!< Names of projects in the workspace */
	//wxString CurrentProject;
	RheiaManagedFrame* m_parent;
	wxBitmap m_bmp;

protected :

};

#endif
