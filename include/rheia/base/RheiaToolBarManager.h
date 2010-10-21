/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#ifndef RheiaToolBarManager_h_
#define RheiaToolBarManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaEventFrame.h>
#include <wx/event.h>
#include <wx/dynarray.h>

class wxToolBar;
class wxAuiToolBar;

typedef std::map<wxString,wxToolBar*> wxToolBarArray;
typedef std::map<wxString,wxAuiToolBar*> wxAuiToolBarArray;

typedef std::map<wxToolBar*,int> RheiaToolMenuIdMap;
typedef std::map<wxAuiToolBar*,int> RheiaAuiToolMenuIdMap;

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
	friend class RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>;				/*!< Give our private member access to Singleton */
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
	wxAuiToolBar *GetToolBar(){return m_toolbar;};

	/** Add Tool Bar */
	void AddToolBar( const wxString& name , wxToolBar* toolbar );

    /** Add Tool Bar */
#ifdef SWIG
	%rename( AddAuiToolBar ) AddToolBar( const wxString& name , wxAuiToolBar* toolbar );
#endif
	void AddToolBar( const wxString& name , wxAuiToolBar* toolbar );

	/** Remove ToolBar */
	void RemoveToolBar( const wxString& name );

	/** Get the toolbars */
	wxToolBarArray& GetToolBars() {return m_toolbars;}

    /** Get the toolbars */
	wxAuiToolBarArray& GetAuiToolBars() {return m_auiToolbars;}

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
	wxAuiToolBar *m_toolbar;						/*!< pointer to the main tool bar */
	RheiaManagedFrame* m_parent;
	wxToolBarArray m_toolbars;
	RheiaToolMenuIdMap m_toolIds;

    wxAuiToolBarArray m_auiToolbars;
	RheiaAuiToolMenuIdMap m_auiToolIds;

	int m_index;
#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};

#endif
