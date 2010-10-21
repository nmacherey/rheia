/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#ifndef RheiaPageContainer_h_
#define RheiaPageContainer_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>

#include <wx/event.h>
#include <wx/treectrl.h>
#include <wx/string.h>
#include <map>

class RheiaBookPage;

class BASE_DLLEXPORT RheiaPageContainer : public virtual RheiaObjectWithBitmap
{
public :

    /**
	*   Any project will have a window in the center pane, which will be called
	*   the project's main envrionment.
	*
	*   For this purpose, any projects must provide the application with a MainWindow
	*   which will be displayed and managed by RheiaCenterPaneManager.
	*
	*   We consider that a project cannot be provided without any MainWindow.
	*
	*   @param parent the parent window in which the project's main window shall be created
	*/
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent ) = 0;

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed() {return true;};
	
	/**
	 * Method that you shall overload if you want to destroy the container 
	 * when the book manager is shutting down
	 */
	virtual bool DestroyOnClose() {return false;};
};

#endif
