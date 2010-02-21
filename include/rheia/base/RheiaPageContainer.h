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
    virtual bool OnPageClosed() = 0;
};

#endif
