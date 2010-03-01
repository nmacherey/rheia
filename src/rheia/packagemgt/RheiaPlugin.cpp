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
