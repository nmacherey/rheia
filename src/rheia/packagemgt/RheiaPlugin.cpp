#include <RheiaPlugin.h>
#include <RheiaEvents.h>
#include <RheiaEventPlugin.h>
#include <RheiaEventsManager.h>

#include <wx/frame.h>

RheiaPlugin::RheiaPlugin()
    : Type(ptNone),
    isAttached(false)
{
	SetEvtHandlerEnabled(false);
}

RheiaPlugin::~RheiaPlugin()
{
}

void RheiaPlugin::Attach()
{
    isAttached = true;
	OnAttach();
	SetEvtHandlerEnabled(true);

	RheiaPluginEvent event(RheiaEVT_PLUGIN_ATTACHED);
	event.SetPlugin(this);
	// post event in the host's event queue
	RheiaEventsManager::Get()->ProcessEvent(event);
}

void RheiaPlugin::Release(bool appShutDown)
{
	if (!isAttached)
		return;
	isAttached = false;
	SetEvtHandlerEnabled(false);
	OnRelease(appShutDown);
	RheiaPluginEvent event(RheiaEVT_PLUGIN_RELEASED);
	event.SetPlugin(this);
	// ask the host to process this event immediately
	// it must be done this way, because if the host references
	// us (through event.GetEventObject()), we might not be valid at that time
	// (while, now, we are...)
	RheiaEventsManager::Get()->ProcessEvent(event);

//	if (appShutDown)
//        return; // nothing more to do, if the app is shutting down
}
