/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaPluginEvents.cpp
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/

#include <RheiaEventPlugin.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaPluginEvent, RheiaEvent)

/**************************************************************************
*   PLUGIN EVENTS EVENTS
**************************************************************************/
/* Defines the events types for the plugin management */
const wxEventType RheiaEVT_PLUGIN_ATTACHED = wxNewEventType();
const wxEventType RheiaEVT_PLUGIN_RELEASED = wxNewEventType();
const wxEventType RheiaEVT_ENVPLUGIN_REQUEST_DETACH = wxNewEventType();


