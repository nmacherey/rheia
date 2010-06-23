/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#include <RheiaEvents.h>

/* Implementing dynamic class for our events */
IMPLEMENT_DYNAMIC_CLASS(RheiaEvent, wxCommandEvent)

/**************************************************************************
*   STARTUP EVENTS
**************************************************************************/
/* Defines the events type for application start up and shut down */
const wxEventType RheiaEVT_APP_STARTUP_DONE = wxNewEventType();
const wxEventType RheiaEVT_APP_START_SHUTDOWN = wxNewEventType();

/**************************************************************************
*   PROFILE EVENTS
**************************************************************************/
const wxEventType RheiaEVT_PROFILE_CHANGED = wxNewEventType();

/**************************************************************************
*   PACKAGES EVENTS
**************************************************************************/
const wxEventType RheiaEVT_PACKAGE_INSTALLED = wxNewEventType();
const wxEventType RheiaEVT_PACKAGE_REMOVED = wxNewEventType();

/**************************************************************************
*   MENU EVENTS
**************************************************************************/
const wxEventType RheiaEVT_MENU_CALLBACK_ADDED = wxNewEventType();
const wxEventType RheiaEVT_MENU_CALLBACK_REMOVED = wxNewEventType();
const wxEventType RheiaEVT_MENU_REBUILT = wxNewEventType();

/**************************************************************************
*   CENTERPANE EVENTS
**************************************************************************/
const wxEventType RheiaEVT_CENTER_PAGE_CHANGED = wxNewEventType();
const wxEventType RheiaEVT_CENTER_PAGE_CHANGING = wxNewEventType();
const wxEventType RheiaEVT_CENTER_PAGE_OPENED = wxNewEventType();
const wxEventType RheiaEVT_CENTER_PAGE_CLOSED = wxNewEventType();
const wxEventType RheiaEVT_CENTER_PAGE_ACTIVATED = wxNewEventType();
const wxEventType RheiaEVT_CENTER_PAGE_DELETED = wxNewEventType();

/**************************************************************************
*   SETTINGS EVENTS
**************************************************************************/
const wxEventType RheiaEVT_INFOMGR_SETTINGS_CHANGED = wxNewEventType();
const wxEventType RheiaEVT_LEFTMGR_SETTINGS_CHANGED = wxNewEventType();
const wxEventType RheiaEVT_CENTERMGR_SETTINGS_CHANGED = wxNewEventType();
const wxEventType RheiaEVT_WKSPMGR_SETTINGS_CHANGED = wxNewEventType();
const wxEventType RheiaEVT_LAYOUT_SETTINGS_CHANGED = wxNewEventType();

/**************************************************************************
*   LOGGER EVENTS
**************************************************************************/
const wxEventType RheiaEVT_LOGGER_REMOVED = wxNewEventType();
const wxEventType RheiaEVT_LOGGER_SETTINGS = wxNewEventType();
const wxEventType RheiaEVT_TXT_LOGGER_SETTINGS = wxNewEventType();
const wxEventType RheiaEVT_HTML_LOGGER_SETTINGS = wxNewEventType();
const wxEventType RheiaEVT_LIST_LOGGER_SETTINGS = wxNewEventType();
const wxEventType RheiaEVT_FILE_LOGGER_SETTINGS = wxNewEventType();
