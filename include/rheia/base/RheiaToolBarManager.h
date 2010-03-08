#ifndef RheiaToolBarManager_h_
#define RheiaToolBarManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <wx/event.h>
#include <wx/dynarray.h>

class wxToolBar;

typedef std::map<wxString,wxToolBar*> wxToolBarArray;
typedef std::map<wxToolBar*,int> RheiaToolMenuIdMap;

/**
*	@class RheiaToolBarManager
*	@brief RheiaToolBarManager is the manager class available for managing the content of the toolbar
*
*	Rheia's tool bar manager enable any plugin to add remove or manage information from the main tool bar.
*	Unless the classical tools for opening saving workspaces the main tool bar has 3 choices boxes.
*	It mainly works as RheiaStatusBarManager. One list is for workspaces, the second is for the available
*	projects in the workspace and the third one for expriments.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaToolBarManager : public wxEvtHandler, public RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>
{
	friend class RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>;				/*!< Give our private member access to Mgr */
	friend class RheiaManager;							                        /*!< Give our private member access to RheiaManager */
public :
	/**********************************************************************************************************
	* CONSTRUCTORS
	**********************************************************************************************************/
	/*! Default constructor */
	RheiaToolBarManager(RheiaManagedFrame* parent);

	/*! Default destructor */
	~RheiaToolBarManager();

	/**********************************************************************************************************
	* METHODS
	**********************************************************************************************************/
	/*! Get the leftPane Manager Book */
	wxToolBar *GetToolBar(){return m_toolbar;};

	/** Add Tool Bar */
	void AddToolBar( const wxString& name , wxToolBar* toolbar );

	/** Remove ToolBar */
	void RemoveToolBar( const wxString& name );

	/** Get the toolbars */
	wxToolBarArray& GetToolBars() {return m_toolbars;}

	/** on close parent event */
	void OnCloseParent(RheiaFrameEvent& event);

private :

    /** Callback used when the user selects a page in the menu */
	void OnSelectToolbarMenu(wxCommandEvent& event);

	/*! Used when we act on the view menu */
	void OnToolsUpdateUI( wxUpdateUIEvent& event );

	/**********************************************************************************************************
												PRIVATE VARIABLES
	**********************************************************************************************************/
	wxToolBar *m_toolbar;						/*!< pointer to the main tool bar */
	RheiaManagedFrame* m_parent;
	wxToolBarArray m_toolbars;
	RheiaToolMenuIdMap m_toolIds;
	int m_index;
#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};

#endif
