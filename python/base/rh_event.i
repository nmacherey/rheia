%{
#include "RheiaEvents.h"
#include "RheiaEventFrame.h"
%}


%constant wxEventType RheiaEVT_APP_STARTUP_DONE;
%constant wxEventType RheiaEVT_APP_START_SHUTDOWN;

%constant wxEventType RheiaEVT_PACKAGE_INSTALLED;
%constant wxEventType RheiaEVT_PACKAGE_REMOVED;

%constant wxEventType RheiaEVT_PROFILE_CHANGED;

%constant wxEventType RheiaEVT_MENU_CALLBACK_ADDED;
%constant wxEventType RheiaEVT_MENU_CALLBACK_REMOVED;
%constant wxEventType RheiaEVT_MENU_REBUILT;

%constant wxEventType RheiaEVT_CENTER_PAGE_CHANGED;
%constant wxEventType RheiaEVT_CENTER_PAGE_CHANGING;
%constant wxEventType RheiaEVT_CENTER_PAGE_CLOSED;
%constant wxEventType RheiaEVT_CENTER_PAGE_OPENED;
%constant wxEventType RheiaEVT_CENTER_PAGE_DELETED;
%constant wxEventType RheiaEVT_CENTER_PAGE_ACTIVATED;

%constant wxEventType RheiaEVT_INFOMGR_SETTINGS_CHANGED;
%constant wxEventType RheiaEVT_LEFTMGR_SETTINGS_CHANGED;
%constant wxEventType RheiaEVT_CENTERMGR_SETTINGS_CHANGED;
%constant wxEventType RheiaEVT_WKSPMGR_SETTINGS_CHANGED;
%constant wxEventType RheiaEVT_LAYOUT_SETTINGS_CHANGED;


%constant wxEventType RheiaEVT_LOGGER_REMOVED;
%constant wxEventType RheiaEVT_LOGGER_SETTINGS;
%constant wxEventType RheiaEVT_TXT_LOGGER_SETTINGS;
%constant wxEventType RheiaEVT_HTML_LOGGER_SETTINGS;
%constant wxEventType RheiaEVT_LIST_LOGGER_SETTINGS;
%constant wxEventType RheiaEVT_FILE_LOGGER_SETTINGS;

%constant wxEventType RheiaEVT_FRAME_CREATED;
%constant wxEventType RheiaEVT_FRAME_CLOSING;

%pythoncode {
%#
%# Create some event binders
EVT_APP_STARTUP_DONE = wx.PyEventBinder( RheiaEVT_APP_STARTUP_DONE )
EVT_APP_START_SHUTDOWN = wx.PyEventBinder( RheiaEVT_APP_START_SHUTDOWN )

EVT_PACKAGE_INSTALLED = wx.PyEventBinder( RheiaEVT_PACKAGE_INSTALLED )
EVT_PACKAGE_REMOVED = wx.PyEventBinder( RheiaEVT_PACKAGE_REMOVED )

EVT_PROFILE_CHANGED = wx.PyEventBinder( RheiaEVT_PROFILE_CHANGED )

EVT_MENU_CALLBACK_ADDED = wx.PyEventBinder( RheiaEVT_MENU_CALLBACK_ADDED )
EVT_MENU_CALLBACK_REMOVED = wx.PyEventBinder( RheiaEVT_MENU_CALLBACK_REMOVED )
EVT_MENU_REBUILT = wx.PyEventBinder( RheiaEVT_MENU_REBUILT )

EVT_CENTER_PAGE_CHANGED = wx.PyEventBinder( RheiaEVT_CENTER_PAGE_CHANGED )
EVT_CENTER_PAGE_CHANGING = wx.PyEventBinder( RheiaEVT_CENTER_PAGE_CHANGING )
EVT_CENTER_PAGE_OPENED = wx.PyEventBinder( RheiaEVT_CENTER_PAGE_OPENED )
EVT_CENTER_PAGE_CLOSED = wx.PyEventBinder( RheiaEVT_CENTER_PAGE_CLOSED )
EVT_CENTER_PAGE_DELETED = wx.PyEventBinder( RheiaEVT_CENTER_PAGE_DELETED )
EVT_CENTER_PAGE_ACTIVATED = wx.PyEventBinder( RheiaEVT_CENTER_PAGE_ACTIVATED )

EVT_INFOMGR_SETTINGS_CHANGED = wx.PyEventBinder( RheiaEVT_INFOMGR_SETTINGS_CHANGED )
EVT_LEFTMGR_SETTINGS_CHANGED = wx.PyEventBinder( RheiaEVT_LEFTMGR_SETTINGS_CHANGED )
EVT_CENTERMGR_SETTINGS_CHANGED = wx.PyEventBinder( RheiaEVT_CENTERMGR_SETTINGS_CHANGED )
EVT_WKSPMGR_SETTINGS_CHANGED = wx.PyEventBinder( RheiaEVT_WKSPMGR_SETTINGS_CHANGED )
EVT_LAYOUT_SETTINGS_CHANGED = wx.PyEventBinder( RheiaEVT_LAYOUT_SETTINGS_CHANGED )

EVT_LOGGER_REMOVED = wx.PyEventBinder( RheiaEVT_LOGGER_REMOVED )
EVT_LOGGER_SETTINGS = wx.PyEventBinder( RheiaEVT_LOGGER_SETTINGS )
EVT_HTML_LOGGER_SETTINGS = wx.PyEventBinder( RheiaEVT_HTML_LOGGER_SETTINGS )
EVT_LIST_LOGGER_SETTINGS = wx.PyEventBinder( RheiaEVT_LIST_LOGGER_SETTINGS )
EVT_FILE_LOGGER_SETTINGS = wx.PyEventBinder( RheiaEVT_FILE_LOGGER_SETTINGS )

EVT_FRAME_CREATED = wx.PyEventBinder( RheiaEVT_FRAME_CREATED )
EVT_FRAME_CLOSING = wx.PyEventBinder( RheiaEVT_FRAME_CLOSING )

}


class RheiaEvent : public wxCommandEvent
{
public:
	RheiaEvent(wxEventType commandType = wxEVT_NULL, int id = 0);
	%rename( RheiaEventCopy ) RheiaEvent(const RheiaEvent& event);
	RheiaEvent(const RheiaEvent& event);

	virtual ~RheiaEvent();
	virtual wxEvent *Clone() const;
	int GetX() const;
	void SetX(int x);
	int GetY() const;
	void SetY(int y);
};


class RheiaFrameEvent : public RheiaEvent
{
public:
	RheiaFrameEvent(wxEventType commandType = wxEVT_NULL,
            int id = 0,
            RheiaManagedFrame* frame = 0L,
            const wxString& name = wxEmptyString );


	%rename( RheiaFrameEventCopy ) RheiaFrameEvent(const RheiaFrameEvent& event);
	RheiaFrameEvent(const RheiaFrameEvent& event);
	
	virtual ~RheiaFrameEvent();

	virtual wxEvent *Clone() const;

	RheiaManagedFrame* GetFrame() const;
	void SetFrame( RheiaManagedFrame* frame );

	wxString GetFrameName();
	void SetFrameName( const wxString& name );
};

