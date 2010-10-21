/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaBookPage.h
*
*   @brief This is the main header file for defining the main environement page for a project in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*/

#ifndef RheiaBookPage_h_
#define RheiaBookPage_h_

#include "RheiaGlobals.h"
#include "RheiaBaseSettings.h"

/**
*   @class RheiaBookPage
*
*   @brief this is the main panel that any project shall create in order to view
*   the page in the center pane when the project is created
*
*   This page is derived from a wxPanel an can be created more than once by the application.
*   Any project derived from RheiaProject shall build it's on derived RheiaBookPage
*   in order to manage specific stuff in the Rheia's center pane.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*
*/

class BASE_DLLEXPORT RheiaBookPage : public wxPanel
{
public :

    /**
    *   Basic constructor
    *
    *   @param parent the parent window in which the panel shall be created
    */
    RheiaBookPage( wxWindow* parent );

    /** Default destructor */
    virtual ~RheiaBookPage();

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
    virtual void OnPageClosed() {};
	
	/**
	 * this method is called when the user right clicks on the book tab
	 * the book tab is where the page's title is displayed
	 */
	virtual void OnTabRightClicked() {};

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
};

#endif
