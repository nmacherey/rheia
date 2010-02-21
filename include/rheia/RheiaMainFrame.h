#ifndef RheiaMainFrame_h_
#define RheiaMainFrame_h_

#include <RheiaManagedFrame.h>
#include <wx/frame.h>
#include <wx/string.h>
#include <wx/toolbar.h>
#include <wx/aui/aui.h>
#include <wx/wizard.h>
#include <wx/listctrl.h>

#include <map>

//class RheiaPlugin;
//class RheiaWorkspace;
//class RheiaEvent;
//
//WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, RheiaPluginIdsMap);
//WX_DECLARE_HASH_MAP(RheiaPlugin*, wxToolBar*, wxPointerHash, wxPointerEqual, RheiaPluginToolbarsMap);
//WX_DECLARE_STRING_HASH_MAP(wxString, RheiaLayoutMap);
//
//class RheiaMainFrame : public wxFrame
//{
//	/*! Enumerate the control ids managed by the frame */
//	enum{
//		idPluginInstalled = wxID_HIGHEST + 1,
//		idPluginUninstalled,
//		idPluginAttached,
//		idPluginDettached
//	};
//public :
//
//	/**********************************************************************************************************
//													CONSTRUCTORS
//	**********************************************************************************************************/
//	/*! Base constructor for building the main frame
//	*
//	*	@param parent Parent Pointer in which to Create the main frame
//	*	@param id Frame's id for eventual frame events
//	*	@param title Frame's title displayed on the window bar
//	*	@param pos Default frame's position when creating
//	*	@param size Default frame's size when creating
//	*	@param style Frame's style see wxWidgets window styles for info
//	*/
//	RheiaMainFrame(wxWindow* parent,
//            wxWindowID id,
//            const wxString& title,
//            const wxPoint& pos = wxDefaultPosition,
//            const wxSize& size = wxDefaultSize,
//            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);
//
//	/*! Destructor */
//	~RheiaMainFrame();
//
//	/**********************************************************************************************************
//													METHODS
//	**********************************************************************************************************/
//	/*! Creates the main frame's status bar */
//	void BuildStatusBar();
//
//	/*! Updates the status bar */
//	void updateStatusBar();
//
//	/*! Creates the different tool bars */
//	void CreateToolBars(void);
//
//	void CreateWorkspacePluginMenus();
//
//	/**********************************************************************************************************
//												MENU CALLBACKS
//	**********************************************************************************************************/
//	/*! Used when we act on the file menu new workspace item */
//	void OnFileWorkspaceNew( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu open workspace item */
//	void OnFileWorkspaceOpen( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu save workspace item */
//	void OnFileWorkspaceSave( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu save all workspace s item */
//	void OnFileWorkspaceSaveAll( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu close workspace item */
//	void OnFileWorkspaceClose( wxCommandEvent &event );
//
//    /*! Used when we act on the file menu new project's item */
//	void OnFileProjectNew( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu open project's item */
//	void OnFileProjectOpen( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu save project's item */
//	void OnFileProjectSave( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu save as project's item */
//	void OnFileProjectSaveAs( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu close project's item */
//	void OnFileProjectClose( wxCommandEvent &event );
//
//	/*! Used when we act on the file menu exit item */
//	void OnFileExit( wxCommandEvent &event );
//
//	/*! Used when we act on the setting app config item */
//	void OnAppConfig( wxCommandEvent &event );
//
//	/*! Used when we act on the setting app config item */
//	void OnPlugConfig( wxCommandEvent &event );
//
//	/*! Used when we act on the setting lang config item */
//	void OnAppConfigLangAndFunc( wxCommandEvent &event );
//
//	/*! Used when we act on the setting lang config item */
//	void OnAppConfigMsgMgr( wxCommandEvent &event );
//
//	/*! Used when we act on the setting lang config item */
//	void OnAppConfigWksMgr( wxCommandEvent &event );
//
//	/*! Used when we act on the setting lang config item */
//	void OnAppConfigLogMgr( wxCommandEvent &event );
//
//	/*! Used when we act on the setting lang config item */
//	void OnAppConfigDocSyst( wxCommandEvent &event );
//
//	/*! Used when we want to set environement variables */
//	void OnManageEnvironementVariables( wxCommandEvent &event );
//
//	/*! Used when we want to view configuration paths */
//	void OnManageConfigurationPaths( wxCommandEvent &event );
//
//	/*! Used when we close the frame */
//	void OnExitApp( wxCloseEvent &event );
//
//	/*! Used when we want to set the fullscreen mode */
//	void OnToggleFullScreen( wxCommandEvent &event );
//
//	/*! Used when we want to view/hide the status bar */
//	void OnToggleStatusBar( wxCommandEvent &event );
//
//	/*! Used when we want to view/hide the management window */
//	void OnToggleLayoutManagerWindow( wxCommandEvent &event );
//
//	/*! Used when we act on the view menu */
//	void OnViewMenuUpdateUI( wxUpdateUIEvent& event );
//
//    /** Create a new project in the workspace */
//	void OnWorkspaceNewProject( wxCommandEvent &event );
//
//	/** Callback used when the user wants to show the Rheia About Dialog */
//	void OnAboutRheia( wxCommandEvent& event );
//
//private :
//	/**********************************************************************************************************
//												LAYOUT MANAGER
//	**********************************************************************************************************/
//	wxAuiManager *LayoutManager;						/*!< Main frame's layout manager */
//	RheiaLayoutMap LayoutPerspectives;					/*!< Array of layout manager's perspectives */
//
//	wxToolBar *ToolBar;									/*!< Main Tool Bar */
//
//	/**********************************************************************************************************
//										PRIVATE METHODS ABOUT THE FRAME INIT
//	**********************************************************************************************************/
//	/*! Creates the default frame controls and initialise the different managers info and books */
//	void BuildAui(void);
//
//	void RegisterEvents();
//
//	void OnPluginAttached( RheiaEvent& event );
//	void OnPluginReleased( RheiaEvent& event );
//
//	void RecreateMenuBar();
//	void CreateMenuBar();
//
//	void DoUpdateManagerColours();
//
//private :
//	DECLARE_EVENT_TABLE()
//};

/**
*   @class RheiaMainFrame
*
*   @brief RheiaMainFrame is the basic frame for applications based on the RheiaFrameWork
*
*   It is mainly composed of an aui manager which allow different panes to be drawn in the window.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	29-January-2010
*	@version 0.0.2
*/
class RheiaMainFrame : public RheiaManagedFrame
{
public :

	/**********************************************************************************************************
													CONSTRUCTORS
	**********************************************************************************************************/
	/*! Base constructor for building the main frame
	*
	*	@param parent Parent Pointer in which to Create the main frame
	*	@param id Frame's id for eventual frame events
	*	@param title Frame's title displayed on the window bar
	*	@param pos Default frame's position when creating
	*	@param size Default frame's size when creating
	*	@param style Frame's style see wxWidgets window styles for info
	*/
	RheiaMainFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

	/*! Destructor */
	~RheiaMainFrame();

};


#endif
