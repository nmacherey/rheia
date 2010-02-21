/**
*   @file RheiaInfoPaneManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaInfoPaneManager_h_
#define RheiaInfoPaneManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaBookManager.h>
#include <wx/event.h>
#include <map>

class wxAuiNotebook;
class wxTreeCtrl;
class wxMenuBar;

/* rheia imports */
class RheiaInfoPage;
class wxAuiNotebookEvent;

typedef std::map<wxString,int> RheiaPageMenuIdMap;

/**
*	@class RheiaInfoPaneManager
*
*	@brief RheiaInfoPaneManager is the manager class for Rheia Project's pages displayed in
*       Rheia's center book.
*
*	RheiaInfoPaneManager manages the layout and the different windows viewed in the center pane.
*	The center pane is a basic graphical element of Rheia's main frame. This manager provide developpers
*   with all informations about projects page displayed (or not) in the center pane's book.
*
*	Rheia's center pane manager is built with a wxAuiNotebook, this is mainly an ergonomy choice, because
*   wxAuiNoteBook is a specific wxWidgets control which allow the user to split pages either horizontally
*   or vertically simply by dragging them to the side they want to split.
*
*   This class as many other managers in Rheia cannot be built directly, you have to get the pointer to
*   the global instance of this manager by using RheiaInfoPaneManager::Get(). It is the same for destroying
*   the class, you have to call RheiaInfoPaneManager::Free(). However you may not do this by your own except
*   if you are an advertise developper because freeing the global instance of this manager will destroy all
*   informations contained in and will result in a Rheia crash.
*   RheiaManager shall only be the class allowed to free the RheiaInfoPaneManager global instance. This
*   is achieve when the application is closing.
*
*	@todo define here how the center pane is managed
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	02-Dec-2008
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaInfoPaneManager : public RheiaBookManager, public RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>
{
    /** Give our private member access to RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager> */
	friend class RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>;

	/** Give our private member access to RheiaManager */
	friend class RheiaManager;

public :
	/**********************************************************************************************************
	*	METHODS
	**********************************************************************************************************/
	/** Reload configuration */
	void ReloadConfiguration();

	/** Register events */
	void RegisterEvents();

	/** Event callback used when a logger is unregistered */
	void OnConfigChanged(wxCommandEvent& event);

	/** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( wxMenuBar* menuBar );

	/** Callback used when the user want to manage environment variables */
	void OnConfigureInfoWindow(wxCommandEvent& event);

	/** you can overload this if you want to do somthing when the window is recreated */
	virtual void OnCreateWindow();

	/**
	*   Add container page to the center book
	*
	*   Any page in the book must be associated to a RheiaPageContainer, by calling this
	*   method you can add a page in the center pane's book. If the container
	*   page is already registered this will return false.
	*
	*   This method will build by its own the container page in the book, by
	*   calling RheiaPageContainer::BuildMainWindow, so you shall never do it by
	*   your own.
	*
	*   After adding the page in the center book this method will call,
	*   RheiaPageContainerPage::OnCreate() method. So you can overload it if
	*   you want to do a specific stuff once the page is shown in the
	*   center book.
	*
	*   @param name containers name (registering key)
	*   @param container page associated container
	*
	*   @return false if the page already exists
	*/
	virtual bool AddPage( wxString name, RheiaPageContainer* container );

	/**
	*   Remove a page from the notebook and delete its corresponding
	*   info.
	*
	*   If you use this method the page will be destroyed from the book
	*   and its corresponding RheiaPageInfo will be removed from the map.
	*   Hence, the page information will no longer be available in this
	*   manager. If you just want to close the page but keep the relative
	*   RheiaPageInfo for the given page please use :
    *   RheiaBookManager::ClosePage.
	*
	*   @param name container's name or page's name to delete
	*   @return false if the page cannot be removed
	*/
	virtual bool DeletePage( const wxString& name );

	/**
	*   Remove a page from the notebook but do not delete its corresponding
	*   info.
	*
	*   If you use this method the page will be destroyed from the book
	*   and its corresponding RheiaPageInfo will be kept in the map.
	*   Hence, the page information will still be available in this
	*   manager and a call to  RheiaBookManager::ActivatePage will
	*   rebuild the page and show it again in the center book.
	*   If you want to delete the page and all its relative information
	*   please use : RheiaBookManager::ClosePage.
	*
	*   @param name container's name or page's name to close
	*   @return false if the page cannot be closed
	*/
	virtual bool ClosePage( const wxString& name );


	virtual void DoPageClose( const wxString& name );

	/**
	*   Activate a page in the center pane book
	*
	*   If the RheiaPageInfo is not available in the manager
	*   this method will return false. However, if the page has been
	*   closed or if it has not been created yet, this method will reopen
	*   the page in the center book by calling RheiaPageContainer::BuildMainWindow.
	*
	*   After adding the page in the center book this method will call,
	*   RheiaPageContainerPage::OnCreate() method. So you can overload it if
	*   you want to do a specific stuff once the page is shown in the
	*   center book.
	*
	*   @param name container's name or page's name to activate
	*   @return false if the page has not been added properly
	*/
	bool ActivatePage( const wxString& name );

private :
    /**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaInfoPaneManager::Get() to get the global instance of this class.
	*/
	RheiaInfoPaneManager(RheiaManagedFrame* parent);

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaInfoPaneManager::Free() to do this. However you may NEVER
	*   call RheiaInfoPaneManager::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	virtual ~RheiaInfoPaneManager();

    /** toggle the page at the given index */
    void Toggle(size_t index);

    /** Hide the page at the given index */
    void Hide(size_t i);

    /** Callback method used when requesting a context menu */
    void OnMenu(wxCommandEvent& event);

    /** Callback method when the menu item copy is clicked */
    void OnCopy(wxCommandEvent& event);

    /** Callback method for clearing the log content */
    void OnClear(wxCommandEvent& event);

    /** Callback method when requesting a context menu */
    void ContextMenu(wxContextMenuEvent& event);

    /** Callback used when the user selects a page in the menu */
	void OnSelectPageMenu(wxCommandEvent& event);

	/** Callback used when the user selects a page in the menu */
	void OnToggleMgtBook(wxCommandEvent& event);

	/*! Used when we act on the view menu */
	void OnToolsUpdateUI( wxUpdateUIEvent& event );

	/**********************************************************************************************************
	*	PRIVATE VARIABLES
	**********************************************************************************************************/
	wxMenu* m_menu;
	wxMenuItem* m_item;
	RheiaPageMenuIdMap m_pageIds;

    /**********************************************************************************************************
	*	EVENT TABLE
	**********************************************************************************************************/
	DECLARE_EVENT_TABLE()
};

#endif

