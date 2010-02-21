/**
*   @file RheiaCenterPaneManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added modifications of RheiaCenterPaneManager to be
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaCenterPaneManager_h_
#define RheiaCenterPaneManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <RheiaBookManager.h>
#include <wx/event.h>
#include <map>

/**
*	@class RheiaCenterPaneManager
*
*	@brief RheiaCenterPaneManager is the manager class for Rheia Container's pages displayed in
*       Rheia's center book.
*
*	RheiaCenterPaneManager manages the layout and the different windows viewed in the center pane.
*	The center pane is a basic graphical element of Rheia's main frame. This manager provide developpers
*   with all informations about containers page displayed (or not) in the center pane's book.
*
*	Rheia's center pane manager is built with a wxAuiNotebook, this is mainly an ergonomy choice, because
*   wxAuiNoteBook is a specific wxWidgets control which allow the user to split pages either horizontally
*   or vertically simply by dragging them to the side they want to split.
*
*   This class as many other managers in Rheia cannot be built directly, you have to get the pointer to
*   the global instance of this manager by using RheiaCenterPaneManager::Get(). It is the same for destroying
*   the class, you have to call RheiaCenterPaneManager::Free(). However you may not do this by your own except
*   if you are an advertise developper because freeing the global instance of this manager will destroy all
*   informations contained in and will result in a Rheia crash.
*   RheiaManager shall only be the class allowed to free the RheiaCenterPaneManager global instance. This
*   is achieve when the application is closing.
*
*	@todo define here how the center pane is managed
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	02-Dec-2008
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaCenterPaneManager : public RheiaBookManager, public RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>
{
    /** Give our private member access to RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager> */
	friend class RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>;

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

    /** Callback used when the user want to manage environment variables */
	void OnConfigure(wxCommandEvent& event);

	/** Reload configuration */
	void ReloadConfiguration();

	/** Register events */
	void RegisterEvents();

	/** Event callback used when a logger is unregistered */
	void OnConfigChanged(wxCommandEvent& event);

	/** you can overload this if you want to do somthing when the window is recreated */
	virtual void OnCreateWindow();

private :
    /**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaCenterPaneManager::Get() to get the global instance of this class.
	*/
	RheiaCenterPaneManager(RheiaManagedFrame* parent);

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaCenterPaneManager::Free() to do this. However you may NEVER
	*   call RheiaCenterPaneManager::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	virtual ~RheiaCenterPaneManager();

    DECLARE_EVENT_TABLE()
};

#endif
