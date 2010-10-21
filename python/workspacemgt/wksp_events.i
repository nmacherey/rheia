%{
#include "RheiaEvents.h"
#include "RheiaEventProject.h"
#include "RheiaEventWorkspace.h"
%}

%constant wxEventType RheiaEVT_PROJECT_CREATED;
%constant wxEventType RheiaEVT_PROJECT_OPENED;
%constant wxEventType RheiaEVT_PROJECT_CLOSING;
%constant wxEventType RheiaEVT_PROJECT_CLOSED;
%constant wxEventType RheiaEVT_PROJECT_ACTIVATED;
%constant wxEventType RheiaEVT_PROJECT_SELECTED;
%constant wxEventType RheiaEVT_PROJECT_RENAMED;
%constant wxEventType RheiaEVT_PROJECT_SAVING;
%constant wxEventType RheiaEVT_PROJECT_SAVED;
%constant wxEventType RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS;
%constant wxEventType RheiaEVT_PROJECT_END_ADD_ELEMENTS;
%constant wxEventType RheiaEVT_PROJECT_BEGIN_REMOVE_ELEMENTS;
%constant wxEventType RheiaEVT_PROJECT_END_REMOVE_ELEMENTS;

%constant wxEventType RheiaEVT_WORKSPACE_OPENING;
%constant wxEventType RheiaEVT_WORKSPACE_OPENED;
%constant wxEventType RheiaEVT_WORKSPACE_SAVED;
%constant wxEventType RheiaEVT_WORKSPACE_SAVING;
%constant wxEventType RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS;
%constant wxEventType RheiaEVT_WORKSPACE_END_ADD_PROJECTS;
%constant wxEventType RheiaEVT_WORKSPACE_CLOSING;
%constant wxEventType RheiaEVT_WORKSPACE_CLOSED;
%constant wxEventType RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS;
%constant wxEventType RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS;

%pythoncode {
%#
%# Create some event binders
EVT_PROJECT_CREATED = wx.PyEventBinder( RheiaEVT_PROJECT_CREATED )
EVT_PROJECT_OPENED = wx.PyEventBinder( RheiaEVT_PROJECT_OPENED )
EVT_PROJECT_CLOSING = wx.PyEventBinder( RheiaEVT_PROJECT_CLOSING )
EVT_PROJECT_CLOSED = wx.PyEventBinder( RheiaEVT_PROJECT_CLOSED )
EVT_PROJECT_ACTIVATED = wx.PyEventBinder( RheiaEVT_PROJECT_ACTIVATED )
EVT_PROJECT_SELECTED = wx.PyEventBinder( RheiaEVT_PROJECT_SELECTED )
EVT_PROJECT_RENAMED = wx.PyEventBinder( RheiaEVT_PROJECT_RENAMED )
EVT_PROJECT_SAVING = wx.PyEventBinder( RheiaEVT_PROJECT_SAVING )
EVT_PROJECT_SAVED = wx.PyEventBinder( RheiaEVT_PROJECT_SAVED )
EVT_PROJECT_BEGIN_ADD_ELEMENTS = wx.PyEventBinder( RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS )
EVT_PROJECT_END_ADD_ELEMENTS = wx.PyEventBinder( RheiaEVT_PROJECT_END_ADD_ELEMENTS )
EVT_PROJECT_END_REMOVE_ELEMENTS = wx.PyEventBinder( RheiaEVT_PROJECT_END_REMOVE_ELEMENTS )
EVT_PROJECT_BEGIN_REMOVE_ELEMENTS = wx.PyEventBinder( RheiaEVT_PROJECT_BEGIN_REMOVE_ELEMENTS )

EVT_WORKSPACE_OPENING = wx.PyEventBinder( RheiaEVT_WORKSPACE_OPENING )
EVT_WORKSPACE_OPENED = wx.PyEventBinder( RheiaEVT_WORKSPACE_OPENED )
EVT_WORKSPACE_SAVED = wx.PyEventBinder( RheiaEVT_WORKSPACE_SAVED )
EVT_WORKSPACE_SAVING = wx.PyEventBinder( RheiaEVT_WORKSPACE_SAVING )
EVT_WORKSPACE_BEGIN_ADD_PROJECTS = wx.PyEventBinder( RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS )
EVT_WORKSPACE_END_ADD_PROJECTS = wx.PyEventBinder( RheiaEVT_WORKSPACE_END_ADD_PROJECTS )
EVT_WORKSPACE_CLOSING = wx.PyEventBinder( RheiaEVT_WORKSPACE_CLOSING )
EVT_WORKSPACE_CLOSED = wx.PyEventBinder( RheiaEVT_WORKSPACE_CLOSED )
EVT_WORKSPACE_BEGIN_REMOVE_PROJECTS = wx.PyEventBinder( RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS )
EVT_WORKSPACE_END_REMOVE_PROJECTS = wx.PyEventBinder( RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS )
}


class WMGT_DLLEXPORT RheiaProjectEvent : public RheiaEvent
{
public:
	RheiaProjectEvent(wxEventType commandType = wxEVT_NULL,
            int id = 0,
            RheiaProject* project = 0L,
            const wxString& name = wxEmptyString );

	%rename(RheiaProjectEventCopy) RheiaProjectEvent(const RheiaProjectEvent& event);
	RheiaProjectEvent(const RheiaProjectEvent& event);

	virtual wxEvent *Clone() const;
	RheiaProject* GetProject() const;
	void SetProject( RheiaProject* project );
	wxString GetProjectName();
	void SetProjectName( const wxString& name );
};

class WMGT_DLLEXPORT RheiaWorkspaceEvent : public RheiaEvent
{
public:
	RheiaWorkspaceEvent(wxEventType commandType = wxEVT_NULL, int id = 0, RheiaWorkspace* workspace = 0L);

	%rename(RheiaWorkspaceEventCopy) RheiaWorkspaceEvent(const RheiaWorkspaceEvent& event);
	RheiaWorkspaceEvent(const RheiaWorkspaceEvent& event);

	virtual wxEvent *Clone() const;
	RheiaWorkspace* GetWorkspace() const;

};

