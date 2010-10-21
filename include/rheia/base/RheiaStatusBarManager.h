/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#ifndef RheiaStatusBarManager_h_
#define RheiaStatusBarManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>

#include <wx/event.h>

/* wxWidgets imports */
class wxFrame;

/**
*	@class RheiaStatusBarManager
*	@brief RheiaStatusBarManager is the manager class available for managing the content of the
*	statusbar
*
*	Rheia's status bar manager, manages the main frame's status bar content. The status bar has 3 fields
*	WORKSPACE, PROJECT, EXPERIMENT in which the name of the different selected items are displayed.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaStatusBarManager : public wxEvtHandler, public RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>
{
	friend class RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>;				/*!< Give our private member access to Singleton */
	friend class RheiaManager;								                    /*!< Give our private member access to RheiaManager */
public :
	/**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/*! Default constructor */
	RheiaStatusBarManager(RheiaManagedFrame* parent);

	/*! Default destructor */
	~RheiaStatusBarManager();

	/**********************************************************************************************************
	*	METHODS
	**********************************************************************************************************/
	/*! Change the workspace name
	*	@param workspace name of the workspace to be displayed
	*/
	void SetWorkspace( wxString workspace );

	/*! Change the project name
	*	@param project name of the project to be displayed
	*/
	void SetProject( wxString project );

	/*! Update the status bar */
	void Update( void );

	/*! Get the active project name */
	wxString GetProject(){return m_project;};

private :
	/**********************************************************************************************************
	*	PRIVATE VARIABLES
	**********************************************************************************************************/
	RheiaManagedFrame *m_parent;					/*!< pointer to the main frame */
	wxString m_workspace;					        /*!< last workspace name */
	wxString m_project;					            /*!< last project name */
};

#endif
