/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaBookManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added modifications of RheiaBookManager to be
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaBookManager_h_
#define RheiaBookManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <wx/event.h>
#include <map>

class wxAuiNotebook;
class wxTreeCtrl;

/* rheia imports */
class RheiaPageContainer;
class RheiaBookPage;
class wxAuiNotebookEvent;
class RheiaConfigurationManager;

/**
*   @struct RheiaPageInfo
*
*   @brief This is the main structure for defining a page in the center pane's book
*
*   Any container in Rheia shall provide the application with what is called a container
*   page. A container page is then displayed in the application's center book and can
*   be used by the user. The user can choose to close a container page and to reopen it
*   later. This structure is used to store information about the container page in order
*   to know if it is open, and to store the information requested for properly displaying
*   its page in the book.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	18-May-2009
*	@version 0.0.1
*/
struct RheiaPageInfo
{
    /** default constrcutor */
    RheiaPageInfo() :
        container(NULL),
        page(NULL)
            {};

    /** copy constructor */
#ifdef SWIG
	%rename(RheiaPageInfoCopy) RheiaPageInfo(const RheiaPageInfo& rhs);
#endif
    RheiaPageInfo(const RheiaPageInfo& rhs):
        name(rhs.name),
        bmp(rhs.bmp),
        container(rhs.container),
        page(rhs.page)
            {};

#ifdef SWIG
	~RheiaPageInfo() {};
#endif

    wxString name;
    wxBitmap bmp;
    RheiaPageContainer* container;
    RheiaBookPage* page;
};

/**
*   Associate a wxString (key) to a page for the center book
*   As any page can be registered once, we associate here a key
*   string corresponding to the container's name to the given page
*   This will make easy the page management in the Rheia Center Book.
*/
typedef std::map< wxString , RheiaPageInfo > RheiaPageInfoMap;

/**
*	@class RheiaBookManager
*
*	@brief RheiaBookManager is the manager class for Rheia Container's pages displayed in
*       Rheia's center book.
*
*	RheiaBookManager manages the layout and the different windows viewed in the center pane.
*	The center pane is a basic graphical element of Rheia's main frame. This manager provide developpers
*   with all informations about containers page displayed (or not) in the center pane's book.
*
*	Rheia's center pane manager is built with a wxAuiNotebook, this is mainly an ergonomy choice, because
*   wxAuiNoteBook is a specific wxWidgets control which allow the user to split pages either horizontally
*   or vertically simply by dragging them to the side they want to split.
*
*   This class as many other managers in Rheia cannot be built directly, you have to get the pointer to
*   the global instance of this manager by using RheiaBookManager::Get(). It is the same for destroying
*   the class, you have to call RheiaBookManager::Free(). However you may not do this by your own except
*   if you are an advertise developper because freeing the global instance of this manager will destroy all
*   informations contained in and will result in a Rheia crash.
*   RheiaManager shall only be the class allowed to free the RheiaBookManager global instance. This
*   is achieve when the application is closing.
*
*	@todo define here how the center pane is managed
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	02-Dec-2008
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaBookManager : public wxEvtHandler
{
	/** Give our private member access to RheiaManager */
	friend class RheiaManager;

public :
    /**********************************************************************************************************
	*	MENU MANAGEMENT METHODS
	**********************************************************************************************************/
	/** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	virtual void BuildMenu( wxMenuBar* ){};

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	virtual void ReleaseMenu( wxMenuBar* ){};

	/**********************************************************************************************************
	*	METHODS
	**********************************************************************************************************/
	/** Get the leftPane Manager Book */
	wxAuiNotebook *GetNoteBook(){return m_book;};

	/** Create window */
	wxAuiNotebook* CreateWindow( wxWindow* parent );

	/** you can overload this if you want to do somthing when the window is recreated */
	virtual void OnCreateWindow(){};

	/** Callback used when the parent is closing */
	virtual void OnCloseParent( RheiaFrameEvent& event );

	/** Reload the book configuration using the given manager in argument */
	void ReloadBookConfiguration( RheiaConfigurationManager* cfg );

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
	virtual bool RemovePage( const wxString& name );
	
	/** Rename the given page 
	 * @param odlName actual name
	 * @param newName new page name
	 */
	void RenamePage( const wxString& oldName , const wxString& newName );

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

	/**
	*   Check if the page associated to the given container
	*   name is open in the center book or not. If the page
	*   information do not longer exists this method will also
	*   return false.
	*   If you want to check if the RheiaPageInfo for the container
	*   exists you have to call RheiaBookManager::PageExists.
	*
	*   @param name container's name or page's name
	*   @return false if the page is not opened
	*/
	bool PageIsOpened( const wxString& name );

	/**
	*   Check if a page associated to the given container is registered
	*   int this manager. This method will not check if the page is
	*   opened in the center book. If you want to do so you should rather
	*   call RheiaBookManager::PageIsOpened.
	*
	*   @param name container's name or page's name
	*   @return false if the page does not exists
	*/
	bool PageExists( const wxString& name );

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

	/** Get the active page */
	wxString GetActivePageName();

	/** get the active page */
	RheiaBookPage* GetActivePage();

	/**********************************************************************************************************
	*	PAGE ACESSORS
	**********************************************************************************************************/
	/**
	*   Find a page given its name
	*   Please take care of this method, it will return NULL
	*   in two cases :
	*       + The RheiaPageInfo is not found
	*       + The page has been closed
	*   If you want to check for the existence of the page, you should
	*   rather call RheiaBookManager::PageExists before any call
	*   to this method.
	*
	*   @param name the page's name to find
	*   @return NULL if the page has not been found or is closed.
	*/
	RheiaBookPage* FindPageByName( const wxString& name );

	/**
	*   Find a page index given its name.
	*
	*   This method returns the current page index in the center book.
	*   Please remember that the user can change the page order by dragging
	*   them with the mouse, so you may never consider the return of this method
	*   as fixed.
	*   In the other side if the page does not exist or if the page is closed,
	*   the method will return wxNOT_FOUND. So if you need to check the page existence
	*   before calling this method you shall call :
	*       + RheiaBookManager::PageExists
	*       + RheiaBookManager::PageIsOpened
	*
	*   @param name the page's name to find the index for
	*   @return wxNOT_FOUND if the page is not in the book or not stored in the manager
	*/
	int FindPageIndexByName( const wxString& name );

    /**
	*   Find a page given its page pointer
	*   @param page the page's pointer to find the name for
	*   @return a wxEmptyString if the page has not been found
	*/
	wxString FindPageNameByObject( RheiaBookPage* page );

	/**
	*   Find a page index given its name
	*   @param name the page's name to find the index for
	*   @return wxNOT_FOUND if the page has not been found
	*/
	int FindPageIndexByObject( RheiaBookPage* page );

	/**
	*   Find a page given its container pointer
	*   @param container the page's container to find the name for
	*   @return a wxEmptyString if the page has not been found
	*/
	wxString FindPageNameByContainer( RheiaPageContainer* container );

	/**
	*   Find a page given its container pointer.
	*   @note that this method will return NULL either if the page has been closed
	*   from the center book or if the page has not been found. So you might have
	*   to use the following methods in order to check for the existence of the page
	*   in the center book.
	*   you shall call :
	*       + RheiaBookManager::PageExists
	*       + RheiaBookManager::PageIsOpened
	*
	*   @param container the page's container to find the page for
	*   @return NULL is the page has not been found or if it is not
	*   opened in the center book.
	*/
	RheiaBookPage* FindPageByContainer( RheiaPageContainer* container );

	/**
	*   Find a page index given its container
	*   @note that this method will return wxNOT_FOUND either if the page has been closed
	*   from the center book or if the page has not been found. So you might have
	*   to use the following methods in order to check for the existence of the page
	*   in the center book.
	*   you shall call :
	*       + RheiaBookManager::PageExists
	*       + RheiaBookManager::PageIsOpened
	*
	*   @param container the page's container to find the index for
	*   @return wxNOT_FOUND if the page has not been found
	*/
	int FindPageIndexByContainer( RheiaPageContainer* container );

protected :
    /**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaBookManager::Get() to get the global instance of this class.
	*/
	RheiaBookManager(RheiaManagedFrame* parent);

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaBookManager::Free() to do this. However you may NEVER
	*   call RheiaBookManager::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	virtual ~RheiaBookManager();

    /**********************************************************************************************************
	*	NOTEBOOK RELATED EVENTS
	**********************************************************************************************************/
    /**
    *   Callback used when a page is closed by the user.
    *   This method will call the RheiaPageContainerPage::OnPageClosed method
    *   in order to notify that the user has requested to Close the page.
    *   Simply save what you have to save by overloading this method when
    *   you are writing your container page object.
    *
    *   @param event the related notebook event generated when the user request to close
    *   a page.
    */
    void OnPageClose( wxAuiNotebookEvent& event );

    virtual void DoPageClose( const wxString& ){};

    /**
    *   Callback used when a page is going to be changed by the user
    *   This method is deprecated so it is no longer in use and do
    *   nothing.
    *
    *   @param event the related notebook event generated when the user request to change
    *   the current page.
    */
    void OnPageChanging( wxAuiNotebookEvent& event );

    /**
    *   Callback used when a page is changed by the user
    *   This method will deal with the following methods in the RheiaPageContainerPage :
    *       + Call to RheiaPageContainerPage::OnPageChanging for the last selected page (i.e: the page
    *           which is actually currently selected but which will no longer be after this method returned)
    *       + Call to RheiaPageContainerPage::OnPageChanged for the new selected page.
    *
    *   You shall properly write the two corresponding methods if you want to do some
    *   specific stuff when the user change the currently selected page in the center book.
    *
    *   @param event the related notebook event generated when the user request to change
    *   the current page.
    */
    void OnPageChanged( wxAuiNotebookEvent& event );
	
	/**
	 * Callback used when the user right clicks on a book tab
	 * this method will call the OnTabRightClick method of the RheiaBookPage
	 */
	void OnTabRightClicked( wxAuiNotebookEvent& event );

    /** Send an event */
    void SendEvent( const wxEventType& type );

	/**********************************************************************************************************
	*	PRIVATE VARIABLES
	**********************************************************************************************************/
	wxAuiNotebook *m_book;
	RheiaPageInfoMap m_pages;
	RheiaManagedFrame* m_parent;
	int cbookId;

    /**********************************************************************************************************
	*	EVENT TABLE
	**********************************************************************************************************/
#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};

#endif

