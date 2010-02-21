/**
*   @file RheiaManagedFrame.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	29-January-2010
*	@version 0.0.2
*/
#ifndef RheiaManagedFrame_h_
#define RheiaManagedFrame_h_

#include <wx/frame.h>
#include <wx/string.h>
#include <wx/toolbar.h>
#include <wx/aui/aui.h>
#include <wx/wizard.h>
#include <wx/listctrl.h>
#include <RheiaEventFrame.h>

#include <map>

/**
*   @class RheiaManagedFrame
*
*   @brief RheiaManagedFrame is the basic frame for applications based on the RheiaFrameWork
*
*   It is mainly composed of an aui manager which allow different panes to be drawn in the window.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	29-January-2010
*	@version 0.0.2
*/
class RheiaManagedFrame : public wxFrame
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
	RheiaManagedFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

	/*! Destructor */
	virtual ~RheiaManagedFrame();

	/**********************************************************************************************************
													METHODS
	**********************************************************************************************************/
	/*! Creates the main frame's status bar */
	void BuildStatusBar( );

	/*! Creates the menu */
	void BuildMenu( );

    /** Create toolbars */
    void BuildToolBar( );

    /** Creates the default frame controls and initialise the different managers info and books */
	void BuildAui(void);

    /** Get the layout manager */
    wxAuiManager* GetLayoutManager() {return m_layout;};

    /** check if the frame is closing or not */
    bool IsFrameClosing() {return m_closing;}

    /*! Used when we close the frame */
	void OnExitApp( wxCloseEvent &event );

	/*! Used when we act on the file menu exit item */
	void OnFileExit( wxCommandEvent &event );

	/*! Used when we act on the file menu exit item */
	void OnFileClose( wxCommandEvent &event );

	/** Callback used when the user wants to show the Rheia About Dialog */
	void OnAboutRheia( wxCommandEvent& event );

	/** Called by build Aui to register the managers and stuff you want to use in the frame */
	virtual void OnBuildAui() {};

	/** register events */
	virtual void RegisterEvents();

	/** Load Layout */
	virtual void LoadLayout();

	/** Get the menuBar */
	wxMenuBar* GetMenuBar() {return m_menuBar;};

	bool CanClose() {return m_canClose;};

	void SetCanClose( bool value = false ) {m_canClose = value;};

	/*! Used when we want to view/hide the status bar */
	void OnToggleStatusBar( wxCommandEvent &event );

	/*! Used when we want to set the fullscreen mode */
	void OnToggleFullScreen( wxCommandEvent &event );

	/*! Used when we act on the view menu */
	void OnViewMenuUpdateUI( wxUpdateUIEvent& event );

protected :
	/**********************************************************************************************************
												LAYOUT MANAGER
	**********************************************************************************************************/
	wxAuiManager *m_layout;					/*!< Main frame's layout manager */
	wxToolBar *ToolBar;						/*!< Main Tool Bar */
	bool m_closing;
	wxMenuBar* m_menuBar;
	bool m_canClose;
	bool m_closeOnly;

	/**********************************************************************************************************
										PRIVATE METHODS ABOUT THE FRAME INIT
	**********************************************************************************************************/

private :
	DECLARE_EVENT_TABLE()
};

#endif

