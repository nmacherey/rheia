/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaProjectEvents.cpp
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/

#include <RheiaEventProject.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaProjectEvent, RheiaEvent)

/**************************************************************************
*   PROJECT EVENTS
**************************************************************************/
const wxEventType RheiaEVT_PROJECT_CREATED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_OPENED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_CLOSED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_CLOSING = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_ACTIVATED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_SELECTED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_RENAMED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_SAVED = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_SAVING = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_END_ADD_ELEMENTS = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_BEGIN_REMOVE_ELEMENTS = wxNewEventType();
const wxEventType RheiaEVT_PROJECT_END_REMOVE_ELEMENTS = wxNewEventType();

