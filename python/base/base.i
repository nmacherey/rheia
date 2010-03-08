%module(package="rheia",directors="1") base
%include "std_map.i"
%{

#include <wx/wxPython/wxPython.h>
#include <wx/wxPython/wxPython_int.h>
#include <wx/wxPython/pyclasses.h>
#include "wx/wxPython/printfw.h"
#include <wx/treectrl.h>
#include <wx/wx.h>
#include <wx/wizard.h>

#include "wx/wxPython/pytree.h"

#include "RheiaAppGlobals.h"
#include "RheiaGlobals.h"
#include "RheiaInfoWindow.h"
#include "RheiaPlatform.h"
#include "RheiaStandardPaths.h"

#include "RheiaAppBase.h"
#include "RheiaApplicationConfigurationDialog.h"
#include "RheiaConfigurationPanel.h"
#include "RheiaApplicationGeneralPanel.h"
#include "RheiaBookConfigurationPanel.h"
#include "RheiaBookManager.h"
#include "RheiaBookPage.h"
#include "RheiaCenterMgrSettingsPanel.h"
#include "RheiaCenterPaneManager.h"
#include "RheiaManager.h"
#include "RheiaConfigurationDialog.h"

#include "RheiaXmlManager.h"
#include "RheiaConfigurationManager.h"
#include "RheiaConfigurationPathsDialog.h"

#include "RheiaDebug.h"
#include "RheiaDockSystSettingsPanel.h"
#include "RheiaEnvironementManager.h"

#include "RheiaEnvVarsConfigurationDialog.h"
#include "RheiaEventsManager.h"

#include "RheiaInfoMgrSettingsPanel.h"
#include "RheiaInfoPage.h"

#include "RheiaInfoPaneManager.h"
#include "RheiaLeftMgrSettingsPanel.h"

#include "RheiaLeftPaneManager.h"
#include "RheiaManagedFrame.h"

#include "RheiaMenuManager.h"

#include "RheiaPageContainer.h"
#include "RheiaPersonalityManager.h"

#include "RheiaProfileManager.h"
#include "RheiaSplashScreen.h"
#include "RheiaStartPageContainer.h"

#include "RheiaStatusBarManager.h"
#include "RheiaToolBarManager.h"
#include "RheiaTreeItem.h"
#include "RheiaTreeItemData.h"
#include "RheiaXulManager.h"

#include "RheiaPython.h"

%}

// Globally turn on the autodoc feature
%feature("autodoc", "1");  // 0 == no param types, 1 == show param types

// Turn on kwargs by default
%feature("kwargs", "1");

// Don't generate separate wrappers for each default args combination
%feature("compactdefaultargs");

#if SWIG_VERSION < 0x010328
// Don't generate default ctors or dtors if the C++ doesn't have them
%feature("nodefault");
#else
// This is the SWIG 1.3.28 way to do the above...
%feature("nodefaultctor");
%feature("nodefaultdtor");
#endif

%import core.i
%import windows.i
%import utils.i
%import _defs.i
%import _treectrl.i

%pythoncode { 
import sys as _sys
rheia = _sys.modules[__name__]
}

typedef wxPyTreeItemData wxTreeItemData;

%import "RheiaBaseSettings.h"

%include base_api.i
%include "RheiaConfigurationPanel.h"

%include base_panels.i

%include "RheiaBookManager.h"
%include "RheiaBookPage.h"
%include "RheiaManager.h"

typedef RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager> RheiaMgrRheiaCenterPaneManager;
%rename(RheiaMgrRheiaCenterPaneManager) RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>;
%template(RheiaMgrRheiaCenterPaneManager) RheiaMgr<RheiaManagedFrame,RheiaCenterPaneManager>;

%include "RheiaCenterPaneManager.h"
%include dialogs.i
%include "RheiaConfigurationManager.h"

%include "RheiaDebug.h"

typedef Mgr<RheiaEnvironementManager> MgrRheiaEnvironementManager;
%rename(MgrRheiaEnvironementManager) Mgr<RheiaEnvironementManager>;
%template(MgrRheiaEnvironementManager) Mgr<RheiaEnvironementManager>;
%include "RheiaEnvironementManager.h"

%include rh_event.i

typedef Mgr<RheiaEventsManager> MgrRheiaEventsManager;
%rename(MgrRheiaEventsManager) Mgr<RheiaEventsManager>;
%template(MgrRheiaEventsManager) Mgr<RheiaEventsManager>;
%include "RheiaEventsManager.h"

typedef RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager> RheiaMgrRheiaInfoPaneManager;
%rename(RheiaMgrRheiaInfoPaneManager) RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>;
%template(RheiaMgrRheiaInfoPaneManager) RheiaMgr<RheiaManagedFrame,RheiaInfoPaneManager>;

%include "RheiaInfoPaneManager.h"

typedef RheiaMgr<RheiaManagedFrame,RheiaLeftPaneManager> RheiaMgrRheiaLeftPaneManager;
%rename(RheiaMgrRheiaLeftPaneManager) RheiaMgr<RheiaManagedFrame,RheiaLeftPaneManager>;
%template(RheiaMgrRheiaLeftPaneManager) RheiaMgr<RheiaManagedFrame,RheiaLeftPaneManager>;

%include "RheiaLeftPaneManager.h"

%feature("pythonprepend") RheiaManagedFrame::RheiaManagedFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER) %{
	if len(args) == 6:
		wx.Frame.__init__(self,args[0],args[1],args[2],args[3],args[4],args[5]);
	elif len(args) == 5:
		wx.Frame.__init__(self,args[0],args[1],args[2],args[3],args[4],wx.DEFAULT_FRAME_STYLE | wx.SUNKEN_BORDER);
	elif len(args) == 4:
		wx.Frame.__init__(self,args[0],args[1],args[2],args[3],wx.DefaultSize,wx.DEFAULT_FRAME_STYLE | wx.SUNKEN_BORDER);
	else:
		wx.Frame.__init__(self,args[0],args[1],args[2],wx.DefaultPosition,wx.DefaultSize,wx.DEFAULT_FRAME_STYLE | wx.SUNKEN_BORDER);
%}

%include "RheiaManagedFrame.h"

typedef RheiaMgr<RheiaManagedFrame,RheiaMenuManager> RheiaMgrRheiaMenuManager;
%rename(RheiaMgrRheiaMenuManager) RheiaMgr<RheiaManagedFrame,RheiaMenuManager>;
%template(RheiaMgrRheiaMenuManager) RheiaMgr<RheiaManagedFrame,RheiaMenuManager>;

%include "RheiaMenuManager.h"

%include "RheiaPageContainer.h"

typedef Mgr<RheiaPersonalityManager> MgrRheiaPersonalityManager;
%rename(MgrRheiaPersonalityManager) Mgr<RheiaPersonalityManager>;
%template(MgrRheiaPersonalityManager) Mgr<RheiaPersonalityManager>;

%include "RheiaPersonalityManager.h"

typedef Mgr<RheiaProfileManager> MgrRheiaProfileManager;
%rename(MgrRheiaProfileManager) Mgr<RheiaProfileManager>;
%template(MgrRheiaProfileManager) Mgr<RheiaProfileManager>;

%include "RheiaProfileManager.h"

%include "RheiaSplashScreen.h"
%include "RheiaStartPageContainer.h"

typedef RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager> RheiaMgrRheiaStatusBarManager;
%rename(RheiaMgrRheiaStatusBarManager) RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>;
%template(RheiaMgrRheiaStatusBarManager) RheiaMgr<RheiaManagedFrame,RheiaStatusBarManager>;

%include "RheiaStatusBarManager.h"

typedef RheiaMgr<RheiaManagedFrame,RheiaToolBarManager> RheiaMgrRheiaToolBarManager;
%rename(RheiaMgrRheiaToolBarManager) RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>;
%template(RheiaMgrRheiaToolBarManager) RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>;

%include "RheiaToolBarManager.h"

%include "RheiaTreeItem.h"
%include "RheiaTreeItemData.h"

typedef Mgr<RheiaXulManager> MgrRheiaXulManager;
%rename(MgrRheiaXulManager) Mgr<RheiaXulManager>;
%template(MgrRheiaXulManager) Mgr<RheiaXulManager>;

%include "RheiaXulManager.h"
