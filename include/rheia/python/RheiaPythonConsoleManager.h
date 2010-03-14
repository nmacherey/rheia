/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef RheiaPythonConsole_MANAGER_H
#define RheiaPythonConsole_MANAGER_H

#include <RheiaPythonUtils.h>
#include <RheiaPageContainer.h>

#include <wx/menu.h>

 /**
*   @class RheiaPythonConsoleManager
*   @brief this is the basic class for handling styled text control informations
*/
class RheiaPythonConsoleManager : public wxEvtHandler, public RheiaPageContainer , public RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>
{
    friend class RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>;

public :
	/** Register events */
	void RegisterEvents();

	/** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( wxMenuBar* menuBar );

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
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );

	/**
	*   Get the project bitmap to the given size,
	*   size could be 16x16, 32x32, 48x48, 80x80 or 128x128
	*/
	virtual const wxBitmap& GetBitmap( const int& size ){return m_bmp;};

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed(){return true;};

private :

    /**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaPythonConsoleManager::Get(Frame) to get the global instance of this class.
	*/
    RheiaPythonConsoleManager(RheiaManagedFrame* parent);

    /**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaPythonConsoleManager::Free(Frame) to do this. However you may NEVER
	*   call RheiaPythonConsoleManager::Free(Frame) this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
    virtual ~RheiaPythonConsoleManager();

    /** parented managed frame */
    RheiaManagedFrame* m_parent;
    wxBitmap m_bmp;
};

 #endif
