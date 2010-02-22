/**
*	@file RheiaEvents.h
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaEvents_h_
#define RheiaEvents_h_

#include <RheiaBaseSettings.h>
#include <wx/intl.h>
#include <wx/event.h>

/**
*	@class RheiaEvent
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
class BASE_DLLEXPORT RheiaEvent : public wxNotifyEvent
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
	RheiaEvent(wxEventType commandType = wxEVT_NULL, int id = 0)
		: wxNotifyEvent(commandType, id),
		X(0),
		Y(0) { }

	/** Copy Constructor
	*	@param event RheiaEvent from which to copy
	*/
	RheiaEvent(const RheiaEvent& event)
		: wxNotifyEvent(event),
		X(event.X),
		Y(event.Y) {}
		
	/** destrcutor */
	virtual ~RheiaEvent() {};

	/*******************************************************************************************************
	*	METHODS
	*******************************************************************************************************/
	/*! This method overloads the clone virtual method for creating a new event from this one */
	virtual wxEvent *Clone() const { return new RheiaEvent(*this); }

	/*! Returns the x coordinate of the mouse position */
	int GetX() const { return X; }
	/*! Sets the x coordinate of the mouse position
	*	@param x the x coordinate of mouse position
	*/
	void SetX(int x){ X = x; }

	/*! Gets the y coordinate of the mouse position */
	int GetY() const { return Y; }
	/*! Sets the y coordinate of the mouse position
	*	@param y the y coordinate of mouse position
	*/
	void SetY(int y){ Y = y; }

protected:
	/*******************************************************************************************************
	*	PRIVATE VRIABLES
	*******************************************************************************************************/
	int X;													/*! mouse x coordinate */
	int Y;													/*! mouse y coordinate */

private:
	DECLARE_DYNAMIC_CLASS(RheiaEvent)
};

/*! defines the event function for further defines of Rheia events */
typedef void (wxEvtHandler::*CommandEventFunction)(wxCommandEvent&);
typedef void (wxEvtHandler::*RheiaEventFunction)(RheiaEvent&);

#define RheiaEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent(RheiaEventFunction, &func)

/**************************************************************************
*   STARTUP EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_APP_STARTUP_DONE;
#define EVT_APP_STARTUP_DONE(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_APP_STARTUP_DONE, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_APP_START_SHUTDOWN;
#define EVT_APP_START_SHUTDOWN(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_APP_START_SHUTDOWN, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),

/**************************************************************************
*   PACKAGE EVENTS EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_PACKAGE_INSTALLED;
#define EVT_PACKAGE_INSTALLED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PACKAGE_INSTALLED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_PACKAGE_REMOVED;
#define EVT_PACKAGE_REMOVED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PACKAGE_REMOVED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),

/**************************************************************************
*   PROFILE EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_PROFILE_CHANGED;
#define EVT_PROFILE_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PROFILE_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),

/**************************************************************************
*   MENU EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_MENU_CALLBACK_ADDED;
#define EVT_MENU_CALLBACK_ADDED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_MENU_CALLBACK_ADDED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_MENU_CALLBACK_REMOVED;
#define EVT_MENU_CALLBACK_REMOVED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_MENU_CALLBACK_REMOVED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_MENU_REBUILT;
#define EVT_MENU_REBUILT(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_MENU_REBUILT, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),

/**************************************************************************
*   CENTERPANE EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTER_PAGE_CHANGED;
#define EVT_CENTER_PAGE_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTER_PAGE_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTER_PAGE_CHANGING;
#define EVT_CENTER_PAGE_CHANGING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTER_PAGE_CHANGING, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTER_PAGE_OPENED;
#define EVT_CENTER_PAGE_OPENED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTER_PAGE_OPENED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTER_PAGE_CLOSED;
#define EVT_CENTER_PAGE_CLOSED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTER_PAGE_CLOSED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTER_PAGE_DELETED;
#define EVT_CENTER_PAGE_DELETED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTER_PAGE_DELETED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTER_PAGE_ACTIVATED;
#define EVT_CENTER_PAGE_ACTIVATED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTER_PAGE_ACTIVATED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),

/**************************************************************************
*   SETTINGS EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_INFOMGR_SETTINGS_CHANGED;
#define EVT_INFOMGR_SETTINGS_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_INFOMGR_SETTINGS_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_LEFTMGR_SETTINGS_CHANGED;
#define EVT_LEFTMGR_SETTINGS_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_LEFTMGR_SETTINGS_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_CENTERMGR_SETTINGS_CHANGED;
#define EVT_CENTERMGR_SETTINGS_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_CENTERMGR_SETTINGS_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_WKSPMGR_SETTINGS_CHANGED;
#define EVT_WKSPMGR_SETTINGS_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_WKSPMGR_SETTINGS_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_LAYOUT_SETTINGS_CHANGED;
#define EVT_LAYOUT_SETTINGS_CHANGED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_LAYOUT_SETTINGS_CHANGED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),

/**************************************************************************
*   LOGGER EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_LOGGER_REMOVED;
#define EVT_LOGGER_REMOVED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_LOGGER_REMOVED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_LOGGER_SETTINGS;
#define EVT_LOGGER_SETTINGS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_LOGGER_SETTINGS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_TXT_LOGGER_SETTINGS;
#define EVT_TXT_LOGGER_SETTINGS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_TXT_LOGGER_SETTINGS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_HTML_LOGGER_SETTINGS;
#define EVT_HTML_LOGGER_SETTINGS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_HTML_LOGGER_SETTINGS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_LIST_LOGGER_SETTINGS;
#define EVT_LIST_LOGGER_SETTINGS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_LIST_LOGGER_SETTINGS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_FILE_LOGGER_SETTINGS;
#define EVT_FILE_LOGGER_SETTINGS(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_FILE_LOGGER_SETTINGS, -1, -1, (wxObjectEventFunction)(wxEventFunction)(CommandEventFunction)&fn, (wxObject *) NULL ),

#endif
