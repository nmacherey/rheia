%{
#include "RheiaEvents.h"
#include "RheiaEventPlugin.h"
%}

%constant wxEventType RheiaEVT_PLUGIN_ATTACHED;
%constant wxEventType RheiaEVT_PLUGIN_RELEASED;
%constant wxEventType RheiaEVT_ENVPLUGIN_REQUEST_DETACH;

%pythoncode {
%#
%# Create some event binders
EVT_PLUGIN_ATTACHED = wx.PyEventBinder( RheiaEVT_PLUGIN_ATTACHED )
EVT_PLUGIN_RELEASED = wx.PyEventBinder( RheiaEVT_PLUGIN_RELEASED )

EVT_ENVPLUGIN_REQUEST_DETACH = wx.PyEventBinder( RheiaEVT_ENVPLUGIN_REQUEST_DETACH )

}


class PMGT_DLLEXPORT RheiaPluginEvent : public RheiaEvent
{
public:

	RheiaPluginEvent(wxEventType commandType = wxEVT_NULL,
            int id = 0,
            RheiaPlugin* plugin = 0L,
            const wxString& name = wxEmptyString );

	%rename(RheiaPluginEventCopy) RheiaPluginEvent(const RheiaPluginEvent& event);
	RheiaPluginEvent(const RheiaPluginEvent& event);

	virtual wxEvent *Clone() const;
	RheiaPlugin* GetPlugin() const;

	void SetPlugin( RheiaPlugin* plugin );
	wxString GetPluginName();

	void SetPluginName( const wxString& name );
};
