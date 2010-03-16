/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#ifndef RheiaProjectItem_h_
#define RheiaProjectItem_h_

#include <RheiaGlobals.h>
#include <RheiaWMgtSettings.h>
#include <RheiaTreeItem.h>

#include <wx/event.h>
#include <wx/string.h>
#include <wx/treectrl.h>

/* Rheia imports */
class RheiaWorkspace;
class RheiaProject;
class RheiaProjectLoader;
class RheiaPlugin;
class RheiaWorkspaceManager;
class RheiaConfigurationPanel;

/* wxWidgets imports */
class wxTreeCtrl;
class wxTreeItemId;
class wxMenu;
class wxMenuBar;
class wxWindow;

/* libxml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaProjectItem
*
*   @brief Basic class for adding elements/items into a project
*
*   A project Item is an abstract notion for handling and organizing items in a project. An item
*   can be related files, data, groups, folders, or virtual folders too.
*   RheiaProject handles items automatically and Items can also contain other items... This is the pupose
*   of RheiaProjectItemGroup which is also a project item... Hence it will be easy to have multiple items
*   in the tree and to display them has a project item.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 07-Dec-2008
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectItem : public wxEvtHandler
{
    /** give private access to Rheia's workspaces */
    friend class RheiaWorkspace;
    /** give private access to Rheia's projects */
    friend class RheiaProject;
    /** give private access to Rheia's workspace manager */
    friend class RheiaWorkspaceManager;
    /** give private access to RheiaProjectLoader */
    friend class RheiaProjectLoader;

public :
    /**********************************************************************************
    *   CONSTRUCTORS
    **********************************************************************************/
    /**
    *   basic constructor, for building an elements attached to the given project
    *   @param owner Owner project for the element
    */
    RheiaProjectItem(
        RheiaProject *owner,
        const wxString& name = wxEmptyString );

    virtual ~RheiaProjectItem();

    /**********************************************************************************
    *   METODS
    **********************************************************************************/
	/** This function is used when the main frame ask the project to build its context menu
	*	@param menu menu in which we want to create the context menu for the project
	*/
	virtual void BuildContextMenu( wxMenu *menu ){};

    /** Check if this item can be configured */
    virtual bool CanConfigure() {return false;}

    /** This function is used for building the element's page in the main workspace book
    *   The page build here is used in the attached project's main page.
    *   @param parent parent's window reference
    */
    virtual RheiaConfigurationPanel* Configure( wxWindow *parent ) {return 0L;};

    /** Get the bitmap accordingly to the given size */
    virtual const wxBitmap& GetBitmap( int size ) = 0;

    /**********************************************************************************
    *   NON Overloadable methods
    **********************************************************************************/

    /** Set the element type */
    void SetType( const wxString& type ){m_type=type;};

    /** Get type */
    wxString GetType(){return m_type;}

    /** Returns the element's name */
	wxString GetName( void ) const { return m_name; };

	/** Renames the element
	*	@param name new name for the element
	*	@param confirm specifies if the user should be asked for a confirmation dialog about the element's name
	*
	*	@return Returns true if the name has been modified, false any else
	*
	*	@note This function changes the name of the element, and displays the new name where it has to be.
	*	untill the element is not saved, the modifications will not be taken into account. Hence this just
	*	renames the element in run - time.
	*/
	void Rename( const wxString& name ) {m_name = name;};

protected :
    /**********************************************************************************
    *   LOAD AND SAVE METODS
    **********************************************************************************/

    /**
    *   When an element shall be load from a file, RheiaProjectManager is loading the
    *   file and the element common informations.
    *   When the element has been created from the RheiaProjectItemPlugin, the element
    *   options shall be loaded from an xmlNode.
    *   Here is the place to do this, anay element that you use shall provide the application
    *   with the way to load its specific options.
    *
    *   @param parent the parent node from which the options have to be loaded
    *
    *   @return true if the options have been loaded properly.
    */
    virtual bool DoLoadElementOptions( xmlNode* parent ) {return true;};

    /**
    *   Similarly as DoLoadElementOptions, any element shall provide the application
    *   with a way to save its options to a file. RheiaProjectManager load the file and manage
    *   its common information.
    *   Here is the place to achieve such a task.
    *
    *   @param parent the parent node to which the options have to be saved
    *
    *   @return true if the options have been saved properly
    */
    virtual bool DoSaveElementOptions( xmlNode* parent ) {return true;};

protected :

    /**********************************************************************************
    *   PRIVATE VARIBALES
    **********************************************************************************/
    RheiaProject *Owner;                                   	/*!< Owner project for the element */

    bool m_modified;									    /*!< Specifies if the workspace has been modified in any way */
	wxString m_name;										/*!< Name of the workspace in GRAYMAT BOX choosen by the user */
	wxString m_type;
};

#endif
