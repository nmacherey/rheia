/**
*	@file RheiaEventProject.h
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaProjectEvents_h_
#define RheiaProjectEvents_h_

#include <RheiaWMgtSettings.h>
#include <RheiaEvents.h>
#include <wx/intl.h>
#include <wx/event.h>

class RheiaProject;

/**
*	@class RheiaProjectEvent
*
*	@brief This is the basic event data container for Rheia projects.
*
*	This event can handle a plugin when a plugin is generating the event, in other case the pointer
*	will be null.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectEvent : public RheiaEvent 
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
	*	@param plugin Pointer to RheiaPlugin that handle the event
	*	@param workspace Pointer to RheiaWorkspace that own the event
	*/
	RheiaProjectEvent(wxEventType commandType = wxEVT_NULL,
            int id = 0,
            RheiaProject* project = 0L,
            const wxString& name = wxEmptyString )
		: RheiaEvent(commandType, id ),
        m_project(project),
        m_name( name )
		{}

	/*! Copy Constructor
	*	@param event RheiaEvent from which to copy
	*/
	RheiaProjectEvent(const RheiaProjectEvent& event)
		: RheiaEvent(event),
		m_project( event.m_project ),
		m_name(event.m_name)
		{}

	/*******************************************************************************************************
	*	METHODS
	*******************************************************************************************************/
	/*! This method overloads the clone virtual method for creating a new event from this one */
	virtual wxEvent *Clone() const { return new RheiaProjectEvent(*this); }

	/*! This method returns the project concerned by the event */
	RheiaProject* GetProject() const { return m_project; }

	/** Set the project */
	void SetProject( RheiaProject* project ){m_project = project;};

	/** Get the project's name */
	wxString GetProjectName(){return m_name;};

	/** Set the project's name */
	void SetProjectName( const wxString& name ) {m_name = name;};

protected:
	/*******************************************************************************************************
	*	PRIVATE VRIABLES
	*******************************************************************************************************/
	RheiaProject* m_project;									/*! Concerned plugin by the event */
	wxString m_name;

private:
	DECLARE_DYNAMIC_CLASS(RheiaProjectEvent)
};

typedef void (wxEvtHandler::*RheiaProjectEventFunction)(RheiaProjectEvent&);

#define RheiaProjectEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(RheiaProjectEventFunction, &func)

/**************************************************************************
*   PROJECT EVENTS
**************************************************************************/
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_CREATED;
#define EVT_PROJECT_CREATED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_CREATED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_OPENED;
#define EVT_PROJECT_OPENED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_OPENED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_CLOSING;
#define EVT_PROJECT_CLOSING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_CLOSING, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_CLOSED;
#define EVT_PROJECT_CLOSED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_CLOSED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_ACTIVATED;
#define EVT_PROJECT_ACTIVATED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_ACTIVATED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_SELECTED;
#define EVT_PROJECT_SELECTED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_SELECTED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_RENAMED;
#define EVT_PROJECT_RENAMED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_RENAMED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_SAVING;
#define EVT_PROJECT_SAVING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_SAVING, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_SAVED;
#define EVT_PROJECT_SAVED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_SAVED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS;
#define EVT_PROJECT_BEGIN_ADD_ELEMENTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_END_ADD_ELEMENTS;
#define EVT_PROJECT_END_ADD_ELEMENTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_END_ADD_ELEMENTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_BEGIN_REMOVE_ELEMENTS;
#define EVT_PROJECT_BEGIN_REMOVE_ELEMENTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),
extern WMGT_DLLEXPORT const wxEventType RheiaEVT_PROJECT_END_REMOVE_ELEMENTS;
#define EVT_PROJECT_END_REMOVE_ELEMENTS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROJECT_END_REMOVE_ELEMENTS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaProjectEventFunction)&fn, (wxObject *) NULL ),


#endif

