/**
*   @file RheiaProject.h
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
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaProject_h_
#define RheiaProject_h_

#include <RheiaWMgtSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaPageContainer.h>
#include <RheiaTreeItem.h>

#include <wx/event.h>
#include <wx/treectrl.h>
#include <wx/string.h>
#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;

/* wx Imports */
class wxTreeCtrl;
class wxMenu;
class wxTreeItemId;

/* Rheia imports */
class RheiaEnvironmentPlugin;
class RheiaWorkspace;
class RheiaWorkspaceManager;
class RheiaProjectManager;
class RheiaProjectLoader;
class RheiaBookPage;

/**
*	@class RheiaProject
*
*	@brief The RheiaProject class is the base class for defining a project.
*
*	RheiaProject is one of the basic classes when you want to enable project management
*   schemes in your application. You have to derive from this class and use the project factory
*   in order to register your projects and make them available.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 08-Nov-2008
*	@version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProject : public RheiaTreeItem, public RheiaPageContainer
{
    DECLARE_ABSTRACT_CLASS(RheiaProject)
	/*! Give our private member access to RheiRheiaTreeItemaEnvironmentPlugin */
	friend class RheiaEnvironmentPlugin;
	/*! Give our private member access to RheiaWorkspace */
	friend class RheiaWorkspace;
	/*! Give our private member access to RheiaWorkspaceManager */
	friend class RheiaWorkspaceManager;
    /*! Give our private member access to RheiaProjectManager */
	friend class RheiaProjectManager;
	/*! Give our private member access to RheiaProjectLoader */
	friend class RheiaProjectLoader;

public :
	/*************************************************************************************************
	*	CONSTRUCTORS
	*************************************************************************************************/
	/**
	* Base constructor, the file name is optional, and can be change during run-time.
	*   @param parent parented frame in which the project will be created
	*	@param workspace attached workspace
	*	@param filename The filename in which to save the project configuration (optional)
	*	@param name name of the project
	*/
	RheiaProject(
        RheiaManagedFrame* parent,
        RheiaWorkspace *workspace,
        const wxString& filename = wxEmptyString ,
		const wxString& name = wxEmptyString );

	/** Destructor */
	virtual ~RheiaProject();

	/** Copy constructor
	*	@param Prj reference object from which to copy info
	*/
	RheiaProject( RheiaProject& Prj );

	/**
	* Virtual clone method for copying project derived from this class
	* If you want to create a new project type, you have to overload this method in
	* order to allow the application management to make a copy of your project
	* starting from this base class.
	*/
	virtual RheiaProject* Clone() = 0;

	/*************************************************************************************************
	*	METHODS
	*************************************************************************************************/

	/** Returns the project's name */
	wxString GetName( void ) const { return m_name; };

	/** Sets the project's name */
	void SetName( const wxString& name ) { m_name = name; };

	/**
	* Renames the project
	*	@param name new name for the project
	*	@param confirm specifies if the user should be asked for a confirmation dialog about the project name
	*
	*	@return Returns true if the name has been modified, false any else
	*
	*	@note This function changes the name of the project, and displays the new name where it has to be.
	*	untill the project is not saved, the modifications will not be taken into account. Hence this just
	*	renames the project in run - time.
	*/
	virtual bool Rename( const wxString& name , bool confirm = false );

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

	/*! Get the project's owner workspace */
	RheiaWorkspace *GetWorkspace( ) {return m_workspace;};

	/** Get the project file */
	wxString GetFileName(){return m_filename;};

	/** Set the project file */
	void SetFileName( const wxString& file ) {m_filename = file;};

	/** Get the project type */
	wxString GetType(){return m_type;};

	/** Set the project type */
	void SetType( const wxString& type ) {m_type = type;}

protected :

	/*************************************************************************************************
	*	PRIVATE VARIABLES
	*************************************************************************************************/
	wxString m_filename;																/*!< File name of the workspace */
	bool m_loaded;																	/*!< Specifies if the workspace has been fully loaded or not */
	wxString m_name;																	/*!< Name of the workspace in GRAYMAT BOX choosen by the user */
	RheiaWorkspace* m_workspace;														/*!< Owner workspace for the project */
	wxString m_type;                                                                /*!< project type */
	RheiaManagedFrame* m_parent;

protected :

    /**
    *   Any Project shall be able to load its options from an xml node given by
    *   RheiaProjectLoader. Hence any kind of additionnal informations that are not
    *   saved by default and which are not RheiaProjectElements or other data manage
    *   separatly you have to overload this method in order to enable loading of your info.
    *
    *   However any options loaded here must be registered in the project by your own.
    *
    *   @param parent the parent node from which to load the options.
    */
    virtual bool DoLoadProjectOptions( xmlNode* parent ) = 0;

    /**
    *   Any project shall be able to save it specific option in a given xmlNode. The file and common
    *   information are saved by RheiaProjectLoader. But as any project can have its own info, this
    *   method has to be overwrittent to achieve such a task !
    *
    *   @param parent the node in which to save
    *
    *   @return true if the options have been saved properly
    */
    virtual bool DoSaveProjectOptions( xmlNode* parent ) = 0;
};


/**
*   @class RheiaProjectLayout
*
*   @brief this is the basic template for defining the project layout information
*
*   Project's layout informations are used by RheiaProjectCreationDlg to display
*   project's information such as bitmaps and others.
*
*   Any project must derive from this class. If you forget, compiler shall tell you
*   that there are some missing informations because those informations are requested
*   by RheiaProjectRegistrant in order to register the wright info for a new project.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 25-April-2009
*   @version 0.0.1
*/
template< class T > class RheiaProjectLayout
{
public :

    /** The project description consists in a string that will be displayed
    * when a project is selected in RheiaProjectCreationDlg */
    static wxString description;

    /** The project description consists in a string that will be displayed
    * when a project is selected in RheiaProjectCreationDlg */
    static wxString title;

    /**
    *   The bitmap base name is very important because the project's bitmap
    *   will be loaded by RheiaProjectCreationDlg in order to display the project
    *   option in the dialog
    */
    static wxString bitmapBaseName;
};

#endif
