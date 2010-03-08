%module(package="rheia",directors="1") packagemgt
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

#include "RheiaPMgtSettings.h"
#include "RheiaPlugin.h"
#include "RheiaLibLoader.h"
#include "RheiaPackageControl.h"
#include "RheiaPackageVersion.h"
#include "RheiaPackageDBManager.h"
#include "RheiaPackageDependency.h"
#include "RheiaPackageDescription.h"
#include "RheiaPackageDependencies.h"
#include "RheiaPackageFile.h"
#include "RheiaPackageFiles.h"

#include "RheiaPackageInfo.h"
#include "RheiaPackageLib.h"
#include "RheiaPackageLibs.h"
#include "RheiaPackageMaintainer.h"
#include "RheiaPackageManagedFile.h"
#include "RheiaPackageManagedFiles.h"
#include "RheiaPackageManagementDialog.h"
#include "RheiaPackageManager.h"

#include "RheiaPluginManager.h"
#include "RheiaPluginManifest.h"
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
%import loggers.i
%import base.i
%import rh_event.i


%pythoncode { 
%#// A little trick to make 'wx' be a reference to this module so wx.Names can
%#// be used here.
import sys as _sys
rheia = _sys.modules[__name__]
}

%import "RheiaPMgtSettings.h"

%include packagemgt_api.i
%include "RheiaPlugin.h"

%include pluginevent.i

typedef Mgr<RheiaLibLoader> MgrRheiaLibLoader;
%rename(MgrRheiaLibLoader) Mgr<RheiaLibLoader>;
%template(MgrRheiaLibLoader) Mgr<RheiaLibLoader>;

%include "RheiaLibLoader.h"

%include "RheiaPackageControl.h"

typedef Mgr<RheiaPackageDBManager> MgrRheiaPackageDBManager;
%rename(MgrRheiaPackageDBManager) Mgr<RheiaPackageDBManager>;
%template(MgrRheiaPackageDBManager) Mgr<RheiaPackageDBManager>;

%include "RheiaPackageDBManager.h"
%include "RheiaPackageVersion.h"
%include "RheiaPackageDependency.h"
%include "RheiaPackageDependencies.h"
%include "RheiaPackageDescription.h"
%include "RheiaPackageFile.h"
%include "RheiaPackageFiles.h"

%include "RheiaPackageInfo.h"
%include "RheiaPackageLib.h"
%include "RheiaPackageLibs.h"
%include "RheiaPackageMaintainer.h"
%include "RheiaPackageManagedFile.h"
%include "RheiaPackageManagedFiles.h"

%feature("pythonprepend") RheiaPackageManagementDialog::RheiaPackageManagementDialog(wxWindow* parent) %{
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);
%}

%include "RheiaPackageManagementDialog.h"

typedef Mgr<RheiaPackageManager> MgrRheiaPackageManager;
%rename(MgrRheiaPackageManager) Mgr<RheiaPackageManager>;
%template(MgrRheiaPackageManager) Mgr<RheiaPackageManager>;

%include "RheiaPackageManager.h"

typedef Mgr<RheiaPluginManager> MgrRheiaPluginManager;
%rename(MgrRheiaPluginManager) Mgr<RheiaPluginManager>;
%template(MgrRheiaPluginManager) Mgr<RheiaPluginManager>;

%include "RheiaPluginManager.h"
%include "RheiaPluginManifest.h"


