/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#include <RheiaPlugin.h>
#include <RheiaEvents.h>
#include <RheiaEventPlugin.h>
#include <RheiaEventsManager.h>

#include <wx/frame.h>

RheiaPlugin::RheiaPlugin()
    : Type(ptNone),
    m_plugged(false)
{
	SetEvtHandlerEnabled(false);
}

RheiaPlugin::~RheiaPlugin()
{
}

void RheiaPlugin::Plug()
{
    m_plugged = true;
	OnPlug();
	SetEvtHandlerEnabled(true);

	RheiaPluginEvent event(RheiaEVT_PLUGIN_ATTACHED);
	event.SetPlugin(this);
	// post event in the host's event queue
	RheiaEventsManager::Get()->ProcessEvent(event);
}

void RheiaPlugin::Unplug(bool appShutDown)
{
	if (!m_plugged)
		return;
		
	m_plugged = false;
	SetEvtHandlerEnabled(false);
	OnUnplug(appShutDown);
	RheiaPluginEvent event(RheiaEVT_PLUGIN_RELEASED);
	event.SetPlugin(this);

	RheiaEventsManager::Get()->ProcessEvent(event);
}
