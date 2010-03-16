/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS(RheiaWorkspace)
#endif
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

#ifdef SWIG
	%rename(PreRheiaWorkspace) RheiaWorkspace(  );
#endif
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

#ifdef SWIG
	%rename(RheiaWorkspaceCopy) RheiaWorkspace( RheiaWorkspace& Wksp );
#endif
	/** Copy constructor
	*	@param Wksp Reference object from which to copy info
	*/
	RheiaWorkspace( RheiaWorkspace& Wksp );

	virtual const wxBitmap& GetBitmap( const int& size );

	/*************************************************************************************************
	*	METHODS
	*************************************************************************************************/

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
	virtual bool Rename( const wxString& , bool ) {return true;};

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
    virtual void OnRequestContextMenu( wxMenu* ) {};

    /** this method is used whent the item is about to be deleted */
    virtual void OnPreDelete() {};

    /** this method is used whent the item is about to be dragged */
    virtual bool OnBeginDrag() {return false;};

    /** this method is used whent the item is about to be dragged */
    virtual bool OnEndDrag() {return false;};

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
	RheiaManagedFrame* m_parent;
	wxBitmap m_bmp;

protected :

};

#endif
