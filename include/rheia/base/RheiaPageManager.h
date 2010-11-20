/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPageManager.h
*
*   Revision : 31-October-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : New file
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	31-October-2010
*	@version 10.10
*/

#ifndef RHEIA_PAGE_MANAGER_H
#define RHEIA_PAGE_MANAGER_H

#include <map>

#include <wx/event.h>
#include <wx/panel.h>
#include <wx/sizer.h>

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <RheiaBookManager.h>

/* rheia imports */
class RheiaPageContainer;
class RheiaBookPage;
class RheiaConfigurationManager;


/**
*	@class RheiaPageManager
*
*	@brief RheiaPageManager is the manager class for Rheia Container's pages displayed in
*       Rheia's center pane.
*
*	RheiaPageManager manages the layout and the different windows viewed in the center pane.
*	The center pane is a basic graphical element of Rheia's main frame. This manager provide developpers
*   with all informations about containers page displayed (or not) in the center pane's panel.
*
*	Rheia's center pane manager is built with a wxAuiNotebook, this is mainly an ergonomy choice, because
*   wxAuiNoteBook is a specific wxWidgets control which allow the user to split pages either horizontally
*   or vertically simply by dragging them to the side they want to split.
*
*   This class as many other managers in Rheia cannot be built directly, you have to get the pointer to
*   the global instance of this manager by using RheiaPageManager::Get(). It is the same for destroying
*   the class, you have to call RheiaPageManager::Free(). However you may not do this by your own except
*   if you are an advertise developper because freeing the global instance of this manager will destroy all
*   informations contained in and will result in a Rheia crash.
*   RheiaManager shall only be the class allowed to free the RheiaPageManager global instance. This
*   is achieve when the application is closing.
*
*	@todo define here how the center pane is managed
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	02-Dec-2008
*	@version 0.0.2
*/
class BASE_DLLEXPORT RheiaPageManager : public wxEvtHandler
{
	/** Give our private member access to RheiaManager */
	friend class RheiaManager;

public :

	/**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaPageManager::Get() to get the global instance of this class.
	*/
	RheiaPageManager(RheiaManagedFrame* parent);

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaPageManager::Free() to do this. However you may NEVER
	*   call RheiaPageManager::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	virtual ~RheiaPageManager();
	
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
	wxWindow* GetWindow(){return m_window;};

	/** Create window */
	wxWindow* CreateWindow( wxWindow* parent );

	/** you can overload this if you want to do somthing when the window is recreated */
	virtual void OnCreateWindow(){};

	/** Callback used when the parent is closing */
	virtual void OnCloseParent( RheiaFrameEvent& event );

	/** Reload the book configuration using the given manager in argument */
	void ReloadConfiguration( RheiaConfigurationManager* cfg ){};

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
	*   Find a page given its page pointer
	*   @param page the page's pointer to find the name for
	*   @return a wxEmptyString if the page has not been found
	*/
	wxString FindPageNameByObject( RheiaBookPage* page );

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

protected :

    /** Send an event */
    void SendEvent( const wxEventType& type );

	/**********************************************************************************************************
	*	PRIVATE VARIABLES
	**********************************************************************************************************/
	wxPanel* m_window;
	wxSizer* m_sizer;
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
