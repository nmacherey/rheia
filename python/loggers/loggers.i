%module(package="rheia",directors="1") loggers
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

#include "RheiaLogger.h"
#include "RheiaFileLogger.h"
#include "RheiaHtmlLogger.h"
#include "RheiaStdLogger.h"

#include "RheiaLoggerManager.h"
#include "RheiaLogMgrSettingsPanel.h"

#include "RheiaTextLogger.h"
#include "RheiaTextLoggerConfigurationPanel.h"
#include "RheiaTextLoggerPage.h"

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
%import base.i

%pythoncode { 
%#// A little trick to make 'wx' be a reference to this module so wx.Names can
%#// be used here.
import sys as _sys
rheia = _sys.modules[__name__]
}

%import "RheiaLoggersSettings.h"

%include loggers_api.i
%include "RheiaLogger.h"
%include "RheiaFileLogger.h"
%include "RheiaHtmlLogger.h"

typedef Mgr<RheiaLoggerFactory> MgrRheiaLoggerFactory;
%rename(MgrRheiaLoggerFactory) Mgr<RheiaLoggerFactory>;
%template(MgrRheiaLoggerFactory) Mgr<RheiaLoggerFactory>;

typedef RheiaMgr<RheiaManagedFrame,RheiaLoggerManager> RheiaMgrRheiaLoggerManager;
%rename(RheiaMgrRheiaLoggerManager) RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>;
%template(RheiaMgrRheiaLoggerManager) RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>;

%include "RheiaLoggerManager.h"
%include "RheiaLogMgrSettingsPanel.h"

%include "RheiaStdLogger.h"
%include "RheiaTextLogger.h"

%include "RheiaTextLoggerConfigurationPanel.h"
%include "RheiaTextLoggerPage.h"

