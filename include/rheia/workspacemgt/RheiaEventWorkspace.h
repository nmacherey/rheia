/**
*	@file RheiaEventWorkspace.h
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaWorkspaceEvents_h_
#define RheiaWorkspaceEvents_h_

#include <RheiaWMgtSettings.h>
#include <RheiaEvents.h>
#include <wx/intl.h>
#include <wx/event.h>

class RheiaWorkspace;

/**
*	@class RheiaWorkspaceEvent
*
*	@brief This is the basic CommandEvent for Rheia.
*
*	This event can handle a plugin when a plugin is generating the event, in other case the pointer
*	will be null.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class WMGT_DLLEXPORT RheiaWorkspaceEvent : public RheiaEvent
{
public:
	/*******************************************************************************************************
	*	CONSTRCUTORS
	*******************************************************************************************************/
	/**
	*   The constructor builds the event with the given wxEventType, the given Id and the given RheiaPlugin
	*
	*	@param commandType wxEventType handled by the object
	*	@param id Id of the generator
	*	@param workspace Pointer to RheiaWorkspace that own the event
	*/
	RheiaWorkspaceEvent(wxEventType commandType = wxEVT_NULL, int id = 0, RheiaWorkspace* workspace = 0L)
		: RheiaEvent(commandType, id),
		Workspace(workspace){}

	/*! Copy Constructor
	*	@param event RheiaWorkspaceEvent from which to copy
	*/
	RheiaWorkspaceEvent(const RheiaWorkspaceEvent& event)
		: RheiaEvent(event),
		Workspace(event.Workspace){}

	/*******************************************************************************************************
	*	METHODS
	*******************************************************************************************************/
	/*! This method overloads the clone virtual method for creating a new event from this one */
	virtual wxEvent *Clone() const { return new RheiaWorkspaceEvent(*this); }

	/*! This method returns the plugin concerned by the event */
	RheiaWorkspace* GetWorkspace() const { return Workspace; }

protected:
	/*******************************************************************************************************
	*	PRIVATE VRIABLES
	*******************************************************************************************************/
	RheiaWorkspace* Workspace;								/*! Concerned workspace by the event */

private:
	DECLARE_DYNAMIC_CLASS(RheiaWorkspaceEvent)
};

/** define a function pointer for functions handling RheiaWorkspaceEvents */
typedef void (wxEvtHandler::*RheiaWorkspaceEventFunction)(RheiaWorkspaceEvent&);

#define RheiaWorkspaceEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(RheiaWorkspaceEventFunction, &func)

/**************************************************************************
*   WORKSPACE EVENTS
**************************************************************************/
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_OPENING;
#define EVT_WORKSPACE_OPENING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_OPENING, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_OPENED;
#define EVT_WORKSPACE_OPENED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_OPENED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_SAVED;
#define EVT_WORKSPACE_SAVED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_SAVED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_SAVING;
#define EVT_WORKSPACE_SAVING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_SAVING, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS;
#define EVT_WORKSPACE_BEGIN_ADD_PROJECTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_END_ADD_PROJECTS;
#define EVT_WORKSPACE_END_ADD_PROJECTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_END_ADD_PROJECTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_CLOSING;
#define EVT_WORKSPACE_CLOSING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_CLOSING, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_CLOSED;
#define EVT_WORKSPACE_CLOSED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_CLOSED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS;
#define EVT_WORKSPACE_BEGIN_REMOVE_PROJECTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS;
#define EVT_WORKSPACE_END_REMOVE_PROJECTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaWorkspaceEventFunction)&fn, (wxObject *) NULL ),

#endif
