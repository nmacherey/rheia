/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaCenterPageManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added modifications of RheiaCenterPageManager to be
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaCenterPageManager_h_
#define RheiaCenterPageManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <RheiaPageManager.h>
#include <wx/event.h>
#include <map>

/**
*	@class RheiaCenterPageManager
*
*	@brief RheiaCenterPageManager is the manager class for Rheia Container's pages displayed in
*       Rheia's center book.
*
*	RheiaCenterPageManager manages the layout and the different windows viewed in the center pane.
*	The center pane is a basic graphical element of Rheia's main frame. This manager provide developpers
*   with all informations about containers page displayed (or not) in the center pane's book.
*
*	Rheia's center pane manager is built with a wxAuiNotebook, this is mainly an ergonomy choice, because
*   wxAuiNoteBook is a specific wxWidgets control which allow the user to split pages either horizontally
*   or vertically simply by dragging them to the side they want to split.
*
*   This class as many other managers in Rheia cannot be built directly, you have to get the pointer to
*   the global instance of this manager by using RheiaCenterPageManager::Get(). It is the same for destroying
*   the class, you have to call RheiaCenterPageManager::Free(). However you may not do this by your own except
*   if you are an advertise developper because freeing the global instance of this manager will destroy all
*   informations contained in and will result in a Rheia crash.
*   RheiaManager shall only be the class allowed to free the RheiaCenterPageManager global instance. This
*   is achieve when the application is closing.
*
*	@todo define here how the center pane is managed
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	02-Dec-2008
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaCenterPageManager : public RheiaPageManager, public RheiaMgr<RheiaManagedFrame,RheiaCenterPageManager>
{
    /** Give our private member access to RheiaMgr<RheiaManagedFrame,RheiaCenterPageManager> */
	friend class RheiaMgr<RheiaManagedFrame,RheiaCenterPageManager>;

	/** Give our private member access to RheiaManager */
	friend class RheiaManager;

public :
    /**********************************************************************************************************
	*	MENU MANAGEMENT METHODS
	**********************************************************************************************************/
	/** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( wxMenuBar* menuBar );

	/** Reload configuration */
	void ReloadConfiguration();

	/** Register events */
	void RegisterEvents();

	/** you can overload this if you want to do somthing when the window is recreated */
	virtual void OnCreateWindow();

private :
    /**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaCenterPageManager::Get() to get the global instance of this class.
	*/
	RheiaCenterPageManager(RheiaManagedFrame* parent);

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaCenterPageManager::Free() to do this. However you may NEVER
	*   call RheiaCenterPageManager::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	virtual ~RheiaCenterPageManager();
	
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#endif
