/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaWorkspaceEvents.cpp
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/

#include <RheiaEventWorkspace.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaWorkspaceEvent, RheiaEvent)

/**************************************************************************
*   WORKSPACE EVENTS
**************************************************************************/
const wxEventType RheiaEVT_WORKSPACE_OPENING = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_OPENED = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_SAVED = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_SAVING = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_END_ADD_PROJECTS = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_CLOSING = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_CLOSED = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS = wxNewEventType();
const wxEventType RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS = wxNewEventType();
