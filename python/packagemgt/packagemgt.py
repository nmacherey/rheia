# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

import _packagemgt
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


def _swig_setattr_nondynamic_method(set):
    def set_attr(self,name,value):
        if (name == "thisown"): return self.this.own(value)
        if hasattr(self,name) or (name == "this"):
            set(self,name,value)
        else:
            raise AttributeError("You cannot add attributes to %s" % self)
    return set_attr


try:
    import weakref
    weakref_proxy = weakref.proxy
except:
    weakref_proxy = lambda x: x


class PySwigIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _packagemgt.delete_PySwigIterator
    __del__ = lambda self : None;
    def value(*args): return _packagemgt.PySwigIterator_value(*args)
    def incr(*args): return _packagemgt.PySwigIterator_incr(*args)
    def decr(*args): return _packagemgt.PySwigIterator_decr(*args)
    def distance(*args): return _packagemgt.PySwigIterator_distance(*args)
    def equal(*args): return _packagemgt.PySwigIterator_equal(*args)
    def copy(*args): return _packagemgt.PySwigIterator_copy(*args)
    def next(*args): return _packagemgt.PySwigIterator_next(*args)
    def previous(*args): return _packagemgt.PySwigIterator_previous(*args)
    def advance(*args): return _packagemgt.PySwigIterator_advance(*args)
    def __eq__(*args): return _packagemgt.PySwigIterator___eq__(*args)
    def __ne__(*args): return _packagemgt.PySwigIterator___ne__(*args)
    def __iadd__(*args): return _packagemgt.PySwigIterator___iadd__(*args)
    def __isub__(*args): return _packagemgt.PySwigIterator___isub__(*args)
    def __add__(*args): return _packagemgt.PySwigIterator___add__(*args)
    def __sub__(*args): return _packagemgt.PySwigIterator___sub__(*args)
    def __iter__(self): return self
_packagemgt.PySwigIterator_swigregister(PySwigIterator)

import wx._core
import wx._windows
import utils
import loggers
import base
#// A little trick to make 'wx' be a reference to this module so wx.Names can
#// be used here.
import sys as _sys
rheia = _sys.modules[__name__]

class RheiaPlugin(wx._core.EvtHandler):
    """Proxy of C++ RheiaPlugin class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPlugin"""
        _packagemgt.RheiaPlugin_swiginit(self,_packagemgt.new_RheiaPlugin(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPlugin
    __del__ = lambda self : None;
    def GetType(*args, **kwargs):
        """GetType(self) -> int"""
        return _packagemgt.RheiaPlugin_GetType(*args, **kwargs)

    def GetGroupIdentifier(*args, **kwargs):
        """GetGroupIdentifier(self) -> int"""
        return _packagemgt.RheiaPlugin_GetGroupIdentifier(*args, **kwargs)

    def GetConfigurationPanel(*args, **kwargs):
        """GetConfigurationPanel(self, Window ?) -> RheiaConfigurationPanel"""
        return _packagemgt.RheiaPlugin_GetConfigurationPanel(*args, **kwargs)

    def IsPlugged(*args, **kwargs):
        """IsPlugged(self) -> bool"""
        return _packagemgt.RheiaPlugin_IsPlugged(*args, **kwargs)

    def CanUnplug(*args, **kwargs):
        """CanUnplug(self) -> bool"""
        return _packagemgt.RheiaPlugin_CanUnplug(*args, **kwargs)

    def BuildToolBar(*args, **kwargs):
        """BuildToolBar(self, RheiaManagedFrame ?)"""
        return _packagemgt.RheiaPlugin_BuildToolBar(*args, **kwargs)

    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, RheiaManagedFrame ?, MenuBar ?)"""
        return _packagemgt.RheiaPlugin_BuildMenu(*args, **kwargs)

_packagemgt.RheiaPlugin_swigregister(RheiaPlugin)
cvar = _packagemgt.cvar
RhCore = cvar.RhCore
RhContrib = cvar.RhContrib
RhUnknown = cvar.RhUnknown

class RheiaPyPlugin(RheiaPlugin):
    """Proxy of C++ RheiaPyPlugin class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def OnPyPlug(*args, **kwargs):
        """OnPyPlug(self)"""
        return _packagemgt.RheiaPyPlugin_OnPyPlug(*args, **kwargs)

    def OnPyUnplug(*args, **kwargs):
        """OnPyUnplug(self, bool ?)"""
        return _packagemgt.RheiaPyPlugin_OnPyUnplug(*args, **kwargs)

_packagemgt.RheiaPyPlugin_swigregister(RheiaPyPlugin)

RheiaEVT_PLUGIN_ATTACHED = _packagemgt.RheiaEVT_PLUGIN_ATTACHED
RheiaEVT_PLUGIN_RELEASED = _packagemgt.RheiaEVT_PLUGIN_RELEASED
RheiaEVT_ENVPLUGIN_REQUEST_DETACH = _packagemgt.RheiaEVT_ENVPLUGIN_REQUEST_DETACH
#
# Create some event binders
EVT_PLUGIN_ATTACHED = wx.PyEventBinder( RheiaEVT_PLUGIN_ATTACHED )
EVT_PLUGIN_RELEASED = wx.PyEventBinder( RheiaEVT_PLUGIN_RELEASED )

EVT_ENVPLUGIN_REQUEST_DETACH = wx.PyEventBinder( RheiaEVT_ENVPLUGIN_REQUEST_DETACH )


class RheiaPluginEvent(base.RheiaEvent):
    """Proxy of C++ RheiaPluginEvent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, EventType commandType=wxEVT_NULL, int id=0, RheiaPlugin plugin=0L, 
            String name=wxEmptyString) -> RheiaPluginEvent
        """
        _packagemgt.RheiaPluginEvent_swiginit(self,_packagemgt.new_RheiaPluginEvent(*args, **kwargs))
    def GetPlugin(*args, **kwargs):
        """GetPlugin(self) -> RheiaPlugin"""
        return _packagemgt.RheiaPluginEvent_GetPlugin(*args, **kwargs)

    def SetPlugin(*args, **kwargs):
        """SetPlugin(self, RheiaPlugin plugin)"""
        return _packagemgt.RheiaPluginEvent_SetPlugin(*args, **kwargs)

    def GetPluginName(*args, **kwargs):
        """GetPluginName(self) -> String"""
        return _packagemgt.RheiaPluginEvent_GetPluginName(*args, **kwargs)

    def SetPluginName(*args, **kwargs):
        """SetPluginName(self, String name)"""
        return _packagemgt.RheiaPluginEvent_SetPluginName(*args, **kwargs)

_packagemgt.RheiaPluginEvent_swigregister(RheiaPluginEvent)

def RheiaPluginEventCopy(*args, **kwargs):
    """RheiaPluginEventCopy(RheiaPluginEvent event) -> RheiaPluginEvent"""
    val = _packagemgt.new_RheiaPluginEventCopy(*args, **kwargs)
    return val

class MgrRheiaLibLoader(object):
    """Proxy of C++ MgrRheiaLibLoader class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _packagemgt.MgrRheiaLibLoader_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaLibLoader"""
        return _packagemgt.MgrRheiaLibLoader_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _packagemgt.MgrRheiaLibLoader_Free(*args, **kwargs)

    Free = staticmethod(Free)
_packagemgt.MgrRheiaLibLoader_swigregister(MgrRheiaLibLoader)

def MgrRheiaLibLoader_Valid(*args):
  """MgrRheiaLibLoader_Valid() -> bool"""
  return _packagemgt.MgrRheiaLibLoader_Valid(*args)

def MgrRheiaLibLoader_Get(*args):
  """MgrRheiaLibLoader_Get() -> RheiaLibLoader"""
  return _packagemgt.MgrRheiaLibLoader_Get(*args)

def MgrRheiaLibLoader_Free(*args):
  """MgrRheiaLibLoader_Free()"""
  return _packagemgt.MgrRheiaLibLoader_Free(*args)

class RheiaDynamicLibrary(object):
    """Proxy of C++ RheiaDynamicLibrary class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaDynamicLibrary"""
        _packagemgt.RheiaDynamicLibrary_swiginit(self,_packagemgt.new_RheiaDynamicLibrary(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaDynamicLibrary
    __del__ = lambda self : None;
    path = property(_packagemgt.RheiaDynamicLibrary_path_get, _packagemgt.RheiaDynamicLibrary_path_set)
    name = property(_packagemgt.RheiaDynamicLibrary_name_get, _packagemgt.RheiaDynamicLibrary_name_set)
    lib = property(_packagemgt.RheiaDynamicLibrary_lib_get, _packagemgt.RheiaDynamicLibrary_lib_set)
_packagemgt.RheiaDynamicLibrary_swigregister(RheiaDynamicLibrary)

def RheiaDynamicLibraryCopy(*args, **kwargs):
    """RheiaDynamicLibraryCopy(RheiaDynamicLibrary rhs) -> RheiaDynamicLibrary"""
    val = _packagemgt.new_RheiaDynamicLibraryCopy(*args, **kwargs)
    return val

class RheiaLibLoader(MgrRheiaLibLoader):
    """Proxy of C++ RheiaLibLoader class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def LoadLibrary(*args, **kwargs):
        """LoadLibrary(self, String filename) -> RheiaDynamicLibrary"""
        return _packagemgt.RheiaLibLoader_LoadLibrary(*args, **kwargs)

    def RemoveLibrary(*args, **kwargs):
        """RemoveLibrary(self, wxDynamicLibrary lib) -> bool"""
        return _packagemgt.RheiaLibLoader_RemoveLibrary(*args, **kwargs)

    def RemoveLibraryByObject(*args, **kwargs):
        """RemoveLibraryByObject(self, RheiaDynamicLibrary lib) -> bool"""
        return _packagemgt.RheiaLibLoader_RemoveLibraryByObject(*args, **kwargs)

    def RemoveLibraryByName(*args, **kwargs):
        """RemoveLibraryByName(self, String name) -> bool"""
        return _packagemgt.RheiaLibLoader_RemoveLibraryByName(*args, **kwargs)

    def LibraryExists(*args, **kwargs):
        """LibraryExists(self, wxDynamicLibrary lib) -> bool"""
        return _packagemgt.RheiaLibLoader_LibraryExists(*args, **kwargs)

    def LibraryExistsByObject(*args, **kwargs):
        """LibraryExistsByObject(self, RheiaDynamicLibrary lib) -> bool"""
        return _packagemgt.RheiaLibLoader_LibraryExistsByObject(*args, **kwargs)

    def LibraryExistsByName(*args, **kwargs):
        """LibraryExistsByName(self, String name) -> bool"""
        return _packagemgt.RheiaLibLoader_LibraryExistsByName(*args, **kwargs)

    def FindLibraryByName(*args, **kwargs):
        """FindLibraryByName(self, String name) -> RheiaDynamicLibrary"""
        return _packagemgt.RheiaLibLoader_FindLibraryByName(*args, **kwargs)

    def FindLibrary(*args, **kwargs):
        """FindLibrary(self, wxDynamicLibrary lib) -> RheiaDynamicLibrary"""
        return _packagemgt.RheiaLibLoader_FindLibrary(*args, **kwargs)

    def Cleanup(*args, **kwargs):
        """Cleanup(self)"""
        return _packagemgt.RheiaLibLoader_Cleanup(*args, **kwargs)

_packagemgt.RheiaLibLoader_swigregister(RheiaLibLoader)

class RheiaPackageControl(object):
    """Proxy of C++ RheiaPackageControl class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageControl"""
        _packagemgt.RheiaPackageControl_swiginit(self,_packagemgt.new_RheiaPackageControl(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageControl
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageControl"""
        return _packagemgt.RheiaPackageControl_Clone(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _packagemgt.RheiaPackageControl_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _packagemgt.RheiaPackageControl_SetName(*args, **kwargs)

    def GetTitle(*args, **kwargs):
        """GetTitle(self) -> String"""
        return _packagemgt.RheiaPackageControl_GetTitle(*args, **kwargs)

    def SetTitle(*args, **kwargs):
        """SetTitle(self, String title)"""
        return _packagemgt.RheiaPackageControl_SetTitle(*args, **kwargs)

    def GetArchitecture(*args, **kwargs):
        """GetArchitecture(self) -> String"""
        return _packagemgt.RheiaPackageControl_GetArchitecture(*args, **kwargs)

    def SetArchitecture(*args, **kwargs):
        """SetArchitecture(self, String archi)"""
        return _packagemgt.RheiaPackageControl_SetArchitecture(*args, **kwargs)

    def GetOperatingSystem(*args, **kwargs):
        """GetOperatingSystem(self) -> String"""
        return _packagemgt.RheiaPackageControl_GetOperatingSystem(*args, **kwargs)

    def SetOperatingSystem(*args, **kwargs):
        """SetOperatingSystem(self, String os)"""
        return _packagemgt.RheiaPackageControl_SetOperatingSystem(*args, **kwargs)

    def GetCategory(*args, **kwargs):
        """GetCategory(self) -> String"""
        return _packagemgt.RheiaPackageControl_GetCategory(*args, **kwargs)

    def SetCategory(*args, **kwargs):
        """SetCategory(self, String category)"""
        return _packagemgt.RheiaPackageControl_SetCategory(*args, **kwargs)

    def GetMaintainer(*args, **kwargs):
        """GetMaintainer(self) -> RheiaPackageMaintainer"""
        return _packagemgt.RheiaPackageControl_GetMaintainer(*args, **kwargs)

    def SetMaintainer(*args, **kwargs):
        """SetMaintainer(self, RheiaPackageMaintainer maintainer)"""
        return _packagemgt.RheiaPackageControl_SetMaintainer(*args, **kwargs)

    def GetVersion(*args, **kwargs):
        """GetVersion(self) -> RheiaPackageVersion"""
        return _packagemgt.RheiaPackageControl_GetVersion(*args, **kwargs)

    def SetVersion(*args, **kwargs):
        """SetVersion(self, RheiaPackageVersion version)"""
        return _packagemgt.RheiaPackageControl_SetVersion(*args, **kwargs)

    def GetSDKVersion(*args, **kwargs):
        """GetSDKVersion(self) -> RheiaPackageVersion"""
        return _packagemgt.RheiaPackageControl_GetSDKVersion(*args, **kwargs)

    def SetSDKVersion(*args, **kwargs):
        """SetSDKVersion(self, RheiaPackageVersion sdkversion)"""
        return _packagemgt.RheiaPackageControl_SetSDKVersion(*args, **kwargs)

    def GetDependencies(*args, **kwargs):
        """GetDependencies(self) -> RheiaPackageDependencies"""
        return _packagemgt.RheiaPackageControl_GetDependencies(*args, **kwargs)

    def SetDependencies(*args, **kwargs):
        """SetDependencies(self, RheiaPackageDependencies dependencies)"""
        return _packagemgt.RheiaPackageControl_SetDependencies(*args, **kwargs)

    def GetDescription(*args, **kwargs):
        """GetDescription(self) -> RheiaPackageDescription"""
        return _packagemgt.RheiaPackageControl_GetDescription(*args, **kwargs)

    def SetDescription(*args, **kwargs):
        """SetDescription(self, RheiaPackageDescription description)"""
        return _packagemgt.RheiaPackageControl_SetDescription(*args, **kwargs)

    def GetSharedLibraries(*args, **kwargs):
        """GetSharedLibraries(self) -> wxArrayString"""
        return _packagemgt.RheiaPackageControl_GetSharedLibraries(*args, **kwargs)

    def SetSharedLibraries(*args, **kwargs):
        """SetSharedLibraries(self, wxArrayString shlibs)"""
        return _packagemgt.RheiaPackageControl_SetSharedLibraries(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageControl_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageControl_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageControl_swigregister(RheiaPackageControl)

def RheiaPackageControlCopy(*args, **kwargs):
    """RheiaPackageControlCopy(RheiaPackageControl rhs) -> RheiaPackageControl"""
    val = _packagemgt.new_RheiaPackageControlCopy(*args, **kwargs)
    return val

class MgrRheiaPackageDBManager(object):
    """Proxy of C++ MgrRheiaPackageDBManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _packagemgt.MgrRheiaPackageDBManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaPackageDBManager"""
        return _packagemgt.MgrRheiaPackageDBManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _packagemgt.MgrRheiaPackageDBManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_packagemgt.MgrRheiaPackageDBManager_swigregister(MgrRheiaPackageDBManager)

def MgrRheiaPackageDBManager_Valid(*args):
  """MgrRheiaPackageDBManager_Valid() -> bool"""
  return _packagemgt.MgrRheiaPackageDBManager_Valid(*args)

def MgrRheiaPackageDBManager_Get(*args):
  """MgrRheiaPackageDBManager_Get() -> RheiaPackageDBManager"""
  return _packagemgt.MgrRheiaPackageDBManager_Get(*args)

def MgrRheiaPackageDBManager_Free(*args):
  """MgrRheiaPackageDBManager_Free()"""
  return _packagemgt.MgrRheiaPackageDBManager_Free(*args)

class RheiaPackageDBManager(MgrRheiaPackageDBManager):
    """Proxy of C++ RheiaPackageDBManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def FindPackageByName(*args, **kwargs):
        """FindPackageByName(self, String name) -> RheiaPackageInfo"""
        return _packagemgt.RheiaPackageDBManager_FindPackageByName(*args, **kwargs)

    def FindPackageByTitle(*args, **kwargs):
        """FindPackageByTitle(self, String title) -> RheiaPackageInfo"""
        return _packagemgt.RheiaPackageDBManager_FindPackageByTitle(*args, **kwargs)

    def ExistsByName(*args, **kwargs):
        """ExistsByName(self, String name) -> bool"""
        return _packagemgt.RheiaPackageDBManager_ExistsByName(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, RheiaPackageInfo info) -> bool"""
        return _packagemgt.RheiaPackageDBManager_Exists(*args, **kwargs)

    def ExistsByTitle(*args, **kwargs):
        """ExistsByTitle(self, String title) -> bool"""
        return _packagemgt.RheiaPackageDBManager_ExistsByTitle(*args, **kwargs)

    def RegisterPackage(*args, **kwargs):
        """RegisterPackage(self, RheiaPackageInfo info) -> bool"""
        return _packagemgt.RheiaPackageDBManager_RegisterPackage(*args, **kwargs)

    def UnregisterPackage(*args, **kwargs):
        """UnregisterPackage(self, RheiaPackageInfo info) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterPackage(*args, **kwargs)

    def UnregisterPackageByName(*args, **kwargs):
        """UnregisterPackageByName(self, String name) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterPackageByName(*args, **kwargs)

    def IsPackageNode(*args, **kwargs):
        """IsPackageNode(self, xmlNode parent, String name) -> bool"""
        return _packagemgt.RheiaPackageDBManager_IsPackageNode(*args, **kwargs)

    def UnregisterPackageByTitle(*args, **kwargs):
        """UnregisterPackageByTitle(self, String title) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterPackageByTitle(*args, **kwargs)

    def RegisterFileForPackage(*args, **kwargs):
        """RegisterFileForPackage(self, String name, RheiaPackageManagedFile file) -> bool"""
        return _packagemgt.RheiaPackageDBManager_RegisterFileForPackage(*args, **kwargs)

    def RegisterFilesForPackage(*args, **kwargs):
        """RegisterFilesForPackage(self, String name, RheiaPackageManagedFiles files) -> bool"""
        return _packagemgt.RheiaPackageDBManager_RegisterFilesForPackage(*args, **kwargs)

    def UnregisterFileForPackage(*args, **kwargs):
        """UnregisterFileForPackage(self, String name, String file) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterFileForPackage(*args, **kwargs)

    def FileIsInNode(*args, **kwargs):
        """FileIsInNode(self, xmlNode parent, String name) -> bool"""
        return _packagemgt.RheiaPackageDBManager_FileIsInNode(*args, **kwargs)

    def GetFileNode(*args, **kwargs):
        """GetFileNode(self, xmlNode parent, String name) -> xmlNode"""
        return _packagemgt.RheiaPackageDBManager_GetFileNode(*args, **kwargs)

    def UnregisterFilesForPackage(*args, **kwargs):
        """UnregisterFilesForPackage(self, String name, wxArrayString files) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterFilesForPackage(*args, **kwargs)

    def RegisterDependecyForPackage(*args, **kwargs):
        """RegisterDependecyForPackage(self, String name, RheiaPackageDependency dependency) -> bool"""
        return _packagemgt.RheiaPackageDBManager_RegisterDependecyForPackage(*args, **kwargs)

    def RegisterDependeciesForPackage(*args, **kwargs):
        """RegisterDependeciesForPackage(self, String name, RheiaPackageDependencies dependencies) -> bool"""
        return _packagemgt.RheiaPackageDBManager_RegisterDependeciesForPackage(*args, **kwargs)

    def UnregisterDependencyForPackage(*args, **kwargs):
        """UnregisterDependencyForPackage(self, String name, String dependency) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterDependencyForPackage(*args, **kwargs)

    def UnregisterDependenciesForPackage(*args, **kwargs):
        """UnregisterDependenciesForPackage(self, String name, wxArrayString dependencies) -> bool"""
        return _packagemgt.RheiaPackageDBManager_UnregisterDependenciesForPackage(*args, **kwargs)

    def GetPackageList(*args, **kwargs):
        """GetPackageList(self) -> wxArrayString"""
        return _packagemgt.RheiaPackageDBManager_GetPackageList(*args, **kwargs)

    def GetPackageListByTitle(*args, **kwargs):
        """GetPackageListByTitle(self) -> wxArrayString"""
        return _packagemgt.RheiaPackageDBManager_GetPackageListByTitle(*args, **kwargs)

    def ListDependentPackagesFor(*args, **kwargs):
        """ListDependentPackagesFor(self, String name) -> wxArrayString"""
        return _packagemgt.RheiaPackageDBManager_ListDependentPackagesFor(*args, **kwargs)

    def GetLibsLoadingList(*args, **kwargs):
        """GetLibsLoadingList(self) -> RheiaPackageMangedFileArray"""
        return _packagemgt.RheiaPackageDBManager_GetLibsLoadingList(*args, **kwargs)

    def GetPluginsLoadingList(*args, **kwargs):
        """GetPluginsLoadingList(self) -> RheiaPackageMangedFileArray"""
        return _packagemgt.RheiaPackageDBManager_GetPluginsLoadingList(*args, **kwargs)

    def GetLoadingList(*args, **kwargs):
        """GetLoadingList(self) -> RheiaPackageMangedFileArray"""
        return _packagemgt.RheiaPackageDBManager_GetLoadingList(*args, **kwargs)

    def GetPackages(*args, **kwargs):
        """GetPackages(self) -> RheiaPackageInfoMap"""
        return _packagemgt.RheiaPackageDBManager_GetPackages(*args, **kwargs)

    def Reload(*args, **kwargs):
        """Reload(self) -> bool"""
        return _packagemgt.RheiaPackageDBManager_Reload(*args, **kwargs)

    def Save(*args, **kwargs):
        """Save(self) -> bool"""
        return _packagemgt.RheiaPackageDBManager_Save(*args, **kwargs)

_packagemgt.RheiaPackageDBManager_swigregister(RheiaPackageDBManager)

class RheiaPackageVersion(object):
    """Proxy of C++ RheiaPackageVersion class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageVersion"""
        _packagemgt.RheiaPackageVersion_swiginit(self,_packagemgt.new_RheiaPackageVersion(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageVersion
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageVersion"""
        return _packagemgt.RheiaPackageVersion_Clone(*args, **kwargs)

    def GetMajor(*args, **kwargs):
        """GetMajor(self) -> long"""
        return _packagemgt.RheiaPackageVersion_GetMajor(*args, **kwargs)

    def SetMajor(*args, **kwargs):
        """SetMajor(self, long major)"""
        return _packagemgt.RheiaPackageVersion_SetMajor(*args, **kwargs)

    def GetMinor(*args, **kwargs):
        """GetMinor(self) -> long"""
        return _packagemgt.RheiaPackageVersion_GetMinor(*args, **kwargs)

    def SetMinor(*args, **kwargs):
        """SetMinor(self, long minor)"""
        return _packagemgt.RheiaPackageVersion_SetMinor(*args, **kwargs)

    def GetBuild(*args, **kwargs):
        """GetBuild(self) -> long"""
        return _packagemgt.RheiaPackageVersion_GetBuild(*args, **kwargs)

    def SetBuild(*args, **kwargs):
        """SetBuild(self, long build)"""
        return _packagemgt.RheiaPackageVersion_SetBuild(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageVersion_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageVersion_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageVersion_swigregister(RheiaPackageVersion)

def RheiaPackageVersionCopy(*args, **kwargs):
    """RheiaPackageVersionCopy(RheiaPackageVersion rhs) -> RheiaPackageVersion"""
    val = _packagemgt.new_RheiaPackageVersionCopy(*args, **kwargs)
    return val

class RheiaPackageDependency(RheiaPackageVersion):
    """Proxy of C++ RheiaPackageDependency class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageDependency"""
        _packagemgt.RheiaPackageDependency_swiginit(self,_packagemgt.new_RheiaPackageDependency(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageDependency
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageDependency"""
        return _packagemgt.RheiaPackageDependency_Clone(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _packagemgt.RheiaPackageDependency_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _packagemgt.RheiaPackageDependency_SetName(*args, **kwargs)

_packagemgt.RheiaPackageDependency_swigregister(RheiaPackageDependency)

def RheiaPackageDependencyCopy(*args, **kwargs):
    """RheiaPackageDependencyCopy(RheiaPackageDependency rhs) -> RheiaPackageDependency"""
    val = _packagemgt.new_RheiaPackageDependencyCopy(*args, **kwargs)
    return val

class RheiaPackageDependencies(object):
    """Proxy of C++ RheiaPackageDependencies class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageDependencies"""
        _packagemgt.RheiaPackageDependencies_swiginit(self,_packagemgt.new_RheiaPackageDependencies(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageDependencies
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageDependencies"""
        return _packagemgt.RheiaPackageDependencies_Clone(*args, **kwargs)

    def GetDependencies(*args, **kwargs):
        """GetDependencies(self) -> RheiaPackageDependencyMap"""
        return _packagemgt.RheiaPackageDependencies_GetDependencies(*args, **kwargs)

    def SetDependencies(*args, **kwargs):
        """SetDependencies(self, RheiaPackageDependencyMap dependencies)"""
        return _packagemgt.RheiaPackageDependencies_SetDependencies(*args, **kwargs)

    def FindDependency(*args, **kwargs):
        """FindDependency(self, String name) -> RheiaPackageDependency"""
        return _packagemgt.RheiaPackageDependencies_FindDependency(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _packagemgt.RheiaPackageDependencies_Exists(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self, String name) -> bool"""
        return _packagemgt.RheiaPackageDependencies_Remove(*args, **kwargs)

    def Add(*args, **kwargs):
        """Add(self, String name, RheiaPackageDependency dep) -> bool"""
        return _packagemgt.RheiaPackageDependencies_Add(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _packagemgt.RheiaPackageDependencies_Clear(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageDependencies_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageDependencies_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageDependencies_swigregister(RheiaPackageDependencies)

def RheiaPackageDependenciesCopy(*args, **kwargs):
    """RheiaPackageDependenciesCopy(RheiaPackageDependencies rhs) -> RheiaPackageDependencies"""
    val = _packagemgt.new_RheiaPackageDependenciesCopy(*args, **kwargs)
    return val

class RheiaPackageDescription(object):
    """Proxy of C++ RheiaPackageDescription class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageDescription"""
        _packagemgt.RheiaPackageDescription_swiginit(self,_packagemgt.new_RheiaPackageDescription(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageDescription
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageDescription"""
        return _packagemgt.RheiaPackageDescription_Clone(*args, **kwargs)

    def GetShort(*args, **kwargs):
        """GetShort(self) -> String"""
        return _packagemgt.RheiaPackageDescription_GetShort(*args, **kwargs)

    def SetShort(*args, **kwargs):
        """SetShort(self, String short_d)"""
        return _packagemgt.RheiaPackageDescription_SetShort(*args, **kwargs)

    def GetFull(*args, **kwargs):
        """GetFull(self) -> String"""
        return _packagemgt.RheiaPackageDescription_GetFull(*args, **kwargs)

    def SetFull(*args, **kwargs):
        """SetFull(self, String full)"""
        return _packagemgt.RheiaPackageDescription_SetFull(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageDescription_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageDescription_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageDescription_swigregister(RheiaPackageDescription)

def RheiaPackageDescriptionCopy(*args, **kwargs):
    """RheiaPackageDescriptionCopy(RheiaPackageDescription rhs) -> RheiaPackageDescription"""
    val = _packagemgt.new_RheiaPackageDescriptionCopy(*args, **kwargs)
    return val

class RheiaPackageFile(object):
    """Proxy of C++ RheiaPackageFile class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageFile"""
        _packagemgt.RheiaPackageFile_swiginit(self,_packagemgt.new_RheiaPackageFile(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageFile
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageFile"""
        return _packagemgt.RheiaPackageFile_Clone(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _packagemgt.RheiaPackageFile_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _packagemgt.RheiaPackageFile_SetName(*args, **kwargs)

    def GetType(*args, **kwargs):
        """GetType(self) -> String"""
        return _packagemgt.RheiaPackageFile_GetType(*args, **kwargs)

    def SetType(*args, **kwargs):
        """SetType(self, String type)"""
        return _packagemgt.RheiaPackageFile_SetType(*args, **kwargs)

    def GetPath(*args, **kwargs):
        """GetPath(self) -> String"""
        return _packagemgt.RheiaPackageFile_GetPath(*args, **kwargs)

    def SetPath(*args, **kwargs):
        """SetPath(self, String path)"""
        return _packagemgt.RheiaPackageFile_SetPath(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self) -> bool"""
        return _packagemgt.RheiaPackageFile_Remove(*args, **kwargs)

    def SetRemove(*args, **kwargs):
        """SetRemove(self, bool value)"""
        return _packagemgt.RheiaPackageFile_SetRemove(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageFile_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageFile_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageFile_swigregister(RheiaPackageFile)

def RheiaPackageFileCopy(*args, **kwargs):
    """RheiaPackageFileCopy(RheiaPackageFile rhs) -> RheiaPackageFile"""
    val = _packagemgt.new_RheiaPackageFileCopy(*args, **kwargs)
    return val

class RheiaPackageFiles(object):
    """Proxy of C++ RheiaPackageFiles class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageFiles"""
        _packagemgt.RheiaPackageFiles_swiginit(self,_packagemgt.new_RheiaPackageFiles(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageFiles
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageFiles"""
        return _packagemgt.RheiaPackageFiles_Clone(*args, **kwargs)

    def GetFiles(*args, **kwargs):
        """GetFiles(self) -> RheiaPackageFileMap"""
        return _packagemgt.RheiaPackageFiles_GetFiles(*args, **kwargs)

    def SetFiles(*args, **kwargs):
        """SetFiles(self, RheiaPackageFileMap files)"""
        return _packagemgt.RheiaPackageFiles_SetFiles(*args, **kwargs)

    def FindFile(*args, **kwargs):
        """FindFile(self, String name) -> RheiaPackageFile"""
        return _packagemgt.RheiaPackageFiles_FindFile(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _packagemgt.RheiaPackageFiles_Exists(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self, String name) -> bool"""
        return _packagemgt.RheiaPackageFiles_Remove(*args, **kwargs)

    def Add(*args, **kwargs):
        """Add(self, String name, RheiaPackageFile dep) -> bool"""
        return _packagemgt.RheiaPackageFiles_Add(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _packagemgt.RheiaPackageFiles_Clear(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageFiles_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageFiles_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageFiles_swigregister(RheiaPackageFiles)

def RheiaPackageFilesCopy(*args, **kwargs):
    """RheiaPackageFilesCopy(RheiaPackageFiles rhs) -> RheiaPackageFiles"""
    val = _packagemgt.new_RheiaPackageFilesCopy(*args, **kwargs)
    return val

class RheiaPackageInfo(object):
    """Proxy of C++ RheiaPackageInfo class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageInfo"""
        _packagemgt.RheiaPackageInfo_swiginit(self,_packagemgt.new_RheiaPackageInfo(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageInfo
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageInfo"""
        return _packagemgt.RheiaPackageInfo_Clone(*args, **kwargs)

    def GetControl(*args, **kwargs):
        """GetControl(self) -> RheiaPackageControl"""
        return _packagemgt.RheiaPackageInfo_GetControl(*args, **kwargs)

    def SetControl(*args, **kwargs):
        """SetControl(self, RheiaPackageControl control)"""
        return _packagemgt.RheiaPackageInfo_SetControl(*args, **kwargs)

    def GetManagedFiles(*args, **kwargs):
        """GetManagedFiles(self) -> RheiaPackageManagedFiles"""
        return _packagemgt.RheiaPackageInfo_GetManagedFiles(*args, **kwargs)

    def SetManagedFiles(*args, **kwargs):
        """SetManagedFiles(self, RheiaPackageManagedFiles files)"""
        return _packagemgt.RheiaPackageInfo_SetManagedFiles(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageInfo_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageInfo_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageInfo_swigregister(RheiaPackageInfo)

def RheiaPackageInfoCopy(*args, **kwargs):
    """RheiaPackageInfoCopy(RheiaPackageInfo rhs) -> RheiaPackageInfo"""
    val = _packagemgt.new_RheiaPackageInfoCopy(*args, **kwargs)
    return val

class RheiaPackageLib(object):
    """Proxy of C++ RheiaPackageLib class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageLib"""
        _packagemgt.RheiaPackageLib_swiginit(self,_packagemgt.new_RheiaPackageLib(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageLib
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageLib"""
        return _packagemgt.RheiaPackageLib_Clone(*args, **kwargs)

    def GetVersion(*args, **kwargs):
        """GetVersion(self) -> RheiaPackageVersion"""
        return _packagemgt.RheiaPackageLib_GetVersion(*args, **kwargs)

    def SetVersion(*args, **kwargs):
        """SetVersion(self, RheiaPackageVersion version)"""
        return _packagemgt.RheiaPackageLib_SetVersion(*args, **kwargs)

    def GetDependencies(*args, **kwargs):
        """GetDependencies(self) -> RheiaPackageDependencies"""
        return _packagemgt.RheiaPackageLib_GetDependencies(*args, **kwargs)

    def SetDependencies(*args, **kwargs):
        """SetDependencies(self, RheiaPackageDependencies dependencies)"""
        return _packagemgt.RheiaPackageLib_SetDependencies(*args, **kwargs)

    def GetFile(*args, **kwargs):
        """GetFile(self) -> RheiaPackageFile"""
        return _packagemgt.RheiaPackageLib_GetFile(*args, **kwargs)

    def SetFile(*args, **kwargs):
        """SetFile(self, RheiaPackageFile file)"""
        return _packagemgt.RheiaPackageLib_SetFile(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageLib_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageLib_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageLib_swigregister(RheiaPackageLib)

def RheiaPackageLibCopy(*args, **kwargs):
    """RheiaPackageLibCopy(RheiaPackageLib rhs) -> RheiaPackageLib"""
    val = _packagemgt.new_RheiaPackageLibCopy(*args, **kwargs)
    return val

class RheiaPackageLibs(object):
    """Proxy of C++ RheiaPackageLibs class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageLibs"""
        _packagemgt.RheiaPackageLibs_swiginit(self,_packagemgt.new_RheiaPackageLibs(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageLibs
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageLibs"""
        return _packagemgt.RheiaPackageLibs_Clone(*args, **kwargs)

    def GetLibs(*args, **kwargs):
        """GetLibs(self) -> RheiaPackageLibMap"""
        return _packagemgt.RheiaPackageLibs_GetLibs(*args, **kwargs)

    def SetLibs(*args, **kwargs):
        """SetLibs(self, RheiaPackageLibMap libs)"""
        return _packagemgt.RheiaPackageLibs_SetLibs(*args, **kwargs)

    def FindLib(*args, **kwargs):
        """FindLib(self, String name) -> RheiaPackageLib"""
        return _packagemgt.RheiaPackageLibs_FindLib(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _packagemgt.RheiaPackageLibs_Exists(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self, String name) -> bool"""
        return _packagemgt.RheiaPackageLibs_Remove(*args, **kwargs)

    def Add(*args, **kwargs):
        """Add(self, String name, RheiaPackageLib dep) -> bool"""
        return _packagemgt.RheiaPackageLibs_Add(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _packagemgt.RheiaPackageLibs_Clear(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageLibs_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageLibs_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageLibs_swigregister(RheiaPackageLibs)

def RheiaPackageLibsCopy(*args, **kwargs):
    """RheiaPackageLibsCopy(RheiaPackageLibs rhs) -> RheiaPackageLibs"""
    val = _packagemgt.new_RheiaPackageLibsCopy(*args, **kwargs)
    return val

class RheiaPackageMaintainer(object):
    """Proxy of C++ RheiaPackageMaintainer class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageMaintainer"""
        _packagemgt.RheiaPackageMaintainer_swiginit(self,_packagemgt.new_RheiaPackageMaintainer(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageMaintainer
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageMaintainer"""
        return _packagemgt.RheiaPackageMaintainer_Clone(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _packagemgt.RheiaPackageMaintainer_SetName(*args, **kwargs)

    def GetAddress(*args, **kwargs):
        """GetAddress(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetAddress(*args, **kwargs)

    def SetAddress(*args, **kwargs):
        """SetAddress(self, String address)"""
        return _packagemgt.RheiaPackageMaintainer_SetAddress(*args, **kwargs)

    def GetZipCode(*args, **kwargs):
        """GetZipCode(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetZipCode(*args, **kwargs)

    def SetZipCode(*args, **kwargs):
        """SetZipCode(self, String zipcode)"""
        return _packagemgt.RheiaPackageMaintainer_SetZipCode(*args, **kwargs)

    def GetTown(*args, **kwargs):
        """GetTown(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetTown(*args, **kwargs)

    def SetTown(*args, **kwargs):
        """SetTown(self, String town)"""
        return _packagemgt.RheiaPackageMaintainer_SetTown(*args, **kwargs)

    def GetCountry(*args, **kwargs):
        """GetCountry(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetCountry(*args, **kwargs)

    def SetCountry(*args, **kwargs):
        """SetCountry(self, String country)"""
        return _packagemgt.RheiaPackageMaintainer_SetCountry(*args, **kwargs)

    def GetPhone(*args, **kwargs):
        """GetPhone(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetPhone(*args, **kwargs)

    def SetPhone(*args, **kwargs):
        """SetPhone(self, String phone)"""
        return _packagemgt.RheiaPackageMaintainer_SetPhone(*args, **kwargs)

    def GetFax(*args, **kwargs):
        """GetFax(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetFax(*args, **kwargs)

    def SetFax(*args, **kwargs):
        """SetFax(self, String fax)"""
        return _packagemgt.RheiaPackageMaintainer_SetFax(*args, **kwargs)

    def GetEmail(*args, **kwargs):
        """GetEmail(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetEmail(*args, **kwargs)

    def SetEmail(*args, **kwargs):
        """SetEmail(self, String email)"""
        return _packagemgt.RheiaPackageMaintainer_SetEmail(*args, **kwargs)

    def GetWebSite(*args, **kwargs):
        """GetWebSite(self) -> String"""
        return _packagemgt.RheiaPackageMaintainer_GetWebSite(*args, **kwargs)

    def SetWebSite(*args, **kwargs):
        """SetWebSite(self, String website)"""
        return _packagemgt.RheiaPackageMaintainer_SetWebSite(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageMaintainer_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageMaintainer_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageMaintainer_swigregister(RheiaPackageMaintainer)

def RheiaPackageMaintainerCopy(*args, **kwargs):
    """RheiaPackageMaintainerCopy(RheiaPackageMaintainer rhs) -> RheiaPackageMaintainer"""
    val = _packagemgt.new_RheiaPackageMaintainerCopy(*args, **kwargs)
    return val

class RheiaPackageManagedFile(object):
    """Proxy of C++ RheiaPackageManagedFile class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageManagedFile"""
        _packagemgt.RheiaPackageManagedFile_swiginit(self,_packagemgt.new_RheiaPackageManagedFile(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageManagedFile
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageManagedFile"""
        return _packagemgt.RheiaPackageManagedFile_Clone(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _packagemgt.RheiaPackageManagedFile_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _packagemgt.RheiaPackageManagedFile_SetName(*args, **kwargs)

    def GetType(*args, **kwargs):
        """GetType(self) -> String"""
        return _packagemgt.RheiaPackageManagedFile_GetType(*args, **kwargs)

    def SetType(*args, **kwargs):
        """SetType(self, String type)"""
        return _packagemgt.RheiaPackageManagedFile_SetType(*args, **kwargs)

    def GetPath(*args, **kwargs):
        """GetPath(self) -> String"""
        return _packagemgt.RheiaPackageManagedFile_GetPath(*args, **kwargs)

    def SetPath(*args, **kwargs):
        """SetPath(self, String path)"""
        return _packagemgt.RheiaPackageManagedFile_SetPath(*args, **kwargs)

    def GetRemove(*args, **kwargs):
        """GetRemove(self) -> bool"""
        return _packagemgt.RheiaPackageManagedFile_GetRemove(*args, **kwargs)

    def SetRemove(*args, **kwargs):
        """SetRemove(self, bool remove)"""
        return _packagemgt.RheiaPackageManagedFile_SetRemove(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageManagedFile_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageManagedFile_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageManagedFile_swigregister(RheiaPackageManagedFile)

def RheiaPackageManagedFileCopy(*args, **kwargs):
    """RheiaPackageManagedFileCopy(RheiaPackageManagedFile rhs) -> RheiaPackageManagedFile"""
    val = _packagemgt.new_RheiaPackageManagedFileCopy(*args, **kwargs)
    return val

class RheiaPackageManagedFiles(object):
    """Proxy of C++ RheiaPackageManagedFiles class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageManagedFiles"""
        _packagemgt.RheiaPackageManagedFiles_swiginit(self,_packagemgt.new_RheiaPackageManagedFiles(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageManagedFiles
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPackageManagedFiles"""
        return _packagemgt.RheiaPackageManagedFiles_Clone(*args, **kwargs)

    def GetManagedFiles(*args, **kwargs):
        """GetManagedFiles(self) -> RheiaPackageManagedFileMap"""
        return _packagemgt.RheiaPackageManagedFiles_GetManagedFiles(*args, **kwargs)

    def SetManagedFiles(*args, **kwargs):
        """SetManagedFiles(self, RheiaPackageManagedFileMap files)"""
        return _packagemgt.RheiaPackageManagedFiles_SetManagedFiles(*args, **kwargs)

    def FindManagedFile(*args, **kwargs):
        """FindManagedFile(self, String name) -> RheiaPackageManagedFile"""
        return _packagemgt.RheiaPackageManagedFiles_FindManagedFile(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _packagemgt.RheiaPackageManagedFiles_Exists(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self, String name) -> bool"""
        return _packagemgt.RheiaPackageManagedFiles_Remove(*args, **kwargs)

    def Add(*args, **kwargs):
        """Add(self, String name, RheiaPackageManagedFile dep) -> bool"""
        return _packagemgt.RheiaPackageManagedFiles_Add(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _packagemgt.RheiaPackageManagedFiles_Clear(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageManagedFiles_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPackageManagedFiles_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPackageManagedFiles_swigregister(RheiaPackageManagedFiles)

def RheiaPackageManagedFilesCopy(*args, **kwargs):
    """RheiaPackageManagedFilesCopy(RheiaPackageManagedFiles rhs) -> RheiaPackageManagedFiles"""
    val = _packagemgt.new_RheiaPackageManagedFilesCopy(*args, **kwargs)
    return val

class RheiaPackageManagementDialog(wx._windows.Dialog):
    """Proxy of C++ RheiaPackageManagementDialog class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaPackageManagementDialog"""
        
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);

        _packagemgt.RheiaPackageManagementDialog_swiginit(self,_packagemgt.new_RheiaPackageManagementDialog(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageManagementDialog
    __del__ = lambda self : None;
_packagemgt.RheiaPackageManagementDialog_swigregister(RheiaPackageManagementDialog)

class RheiaPackageTreeItemData(object):
    """Proxy of C++ RheiaPackageTreeItemData class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaPackageInfo pkgInfo=0L) -> RheiaPackageTreeItemData"""
        _packagemgt.RheiaPackageTreeItemData_swiginit(self,_packagemgt.new_RheiaPackageTreeItemData(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageTreeItemData
    __del__ = lambda self : None;
    def GetInfo(*args, **kwargs):
        """GetInfo(self) -> RheiaPackageInfo"""
        return _packagemgt.RheiaPackageTreeItemData_GetInfo(*args, **kwargs)

    def SetInfo(*args, **kwargs):
        """SetInfo(self, RheiaPackageInfo pkgInfo)"""
        return _packagemgt.RheiaPackageTreeItemData_SetInfo(*args, **kwargs)

_packagemgt.RheiaPackageTreeItemData_swigregister(RheiaPackageTreeItemData)

class MgrRheiaPackageManager(object):
    """Proxy of C++ MgrRheiaPackageManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _packagemgt.MgrRheiaPackageManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaPackageManager"""
        return _packagemgt.MgrRheiaPackageManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _packagemgt.MgrRheiaPackageManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_packagemgt.MgrRheiaPackageManager_swigregister(MgrRheiaPackageManager)

def MgrRheiaPackageManager_Valid(*args):
  """MgrRheiaPackageManager_Valid() -> bool"""
  return _packagemgt.MgrRheiaPackageManager_Valid(*args)

def MgrRheiaPackageManager_Get(*args):
  """MgrRheiaPackageManager_Get() -> RheiaPackageManager"""
  return _packagemgt.MgrRheiaPackageManager_Get(*args)

def MgrRheiaPackageManager_Free(*args):
  """MgrRheiaPackageManager_Free()"""
  return _packagemgt.MgrRheiaPackageManager_Free(*args)

class RheiaPackageScanInfo(object):
    """Proxy of C++ RheiaPackageScanInfo class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPackageScanInfo"""
        _packagemgt.RheiaPackageScanInfo_swiginit(self,_packagemgt.new_RheiaPackageScanInfo(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPackageScanInfo
    __del__ = lambda self : None;
    name = property(_packagemgt.RheiaPackageScanInfo_name_get, _packagemgt.RheiaPackageScanInfo_name_set)
    fullname = property(_packagemgt.RheiaPackageScanInfo_fullname_get, _packagemgt.RheiaPackageScanInfo_fullname_set)
    path = property(_packagemgt.RheiaPackageScanInfo_path_get, _packagemgt.RheiaPackageScanInfo_path_set)
    control = property(_packagemgt.RheiaPackageScanInfo_control_get, _packagemgt.RheiaPackageScanInfo_control_set)
_packagemgt.RheiaPackageScanInfo_swigregister(RheiaPackageScanInfo)

def RheiaPackageScanInfoCopy(*args, **kwargs):
    """RheiaPackageScanInfoCopy(RheiaPackageScanInfo rhs) -> RheiaPackageScanInfo"""
    val = _packagemgt.new_RheiaPackageScanInfoCopy(*args, **kwargs)
    return val

class RheiaPackageManager(wx._core.EvtHandler,MgrRheiaPackageManager):
    """Proxy of C++ RheiaPackageManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def ScanForPackages(*args, **kwargs):
        """ScanForPackages(self, String path) -> int"""
        return _packagemgt.RheiaPackageManager_ScanForPackages(*args, **kwargs)

    def AddPackageToList(*args, **kwargs):
        """AddPackageToList(self, String filename) -> bool"""
        return _packagemgt.RheiaPackageManager_AddPackageToList(*args, **kwargs)

    def InstallPendingPackages(*args, **kwargs):
        """InstallPendingPackages(self, bool askfor=True)"""
        return _packagemgt.RheiaPackageManager_InstallPendingPackages(*args, **kwargs)

    def InstallPackages(*args, **kwargs):
        """
        InstallPackages(self, bool askfor=True, bool globaly=False, bool silent=True, 
            bool confirm=False) -> bool
        """
        return _packagemgt.RheiaPackageManager_InstallPackages(*args, **kwargs)

    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, RheiaManagedFrame parent, MenuBar menuBar)"""
        return _packagemgt.RheiaPackageManager_BuildMenu(*args, **kwargs)

    def ReleaseMenu(*args, **kwargs):
        """ReleaseMenu(self, RheiaManagedFrame parent, MenuBar menuBar)"""
        return _packagemgt.RheiaPackageManager_ReleaseMenu(*args, **kwargs)

    def OnManagePackages(*args, **kwargs):
        """OnManagePackages(self, CommandEvent event)"""
        return _packagemgt.RheiaPackageManager_OnManagePackages(*args, **kwargs)

    def OnCloseFrame(*args, **kwargs):
        """OnCloseFrame(self, RheiaFrameEvent event)"""
        return _packagemgt.RheiaPackageManager_OnCloseFrame(*args, **kwargs)

    def ExtractFile(*args, **kwargs):
        """ExtractFile(self, String package, String source, String destination) -> bool"""
        return _packagemgt.RheiaPackageManager_ExtractFile(*args, **kwargs)

    def ExtractFiles(*args, **kwargs):
        """
        ExtractFiles(self, String package, String dir, String ext, String destination, 
            String error, wxArrayString installed, 
            RheiaPackageManagedFiles files, String type) -> bool
        """
        return _packagemgt.RheiaPackageManager_ExtractFiles(*args, **kwargs)

    def ReadControlFileFor(*args, **kwargs):
        """ReadControlFileFor(self, String file) -> RheiaPackageControl"""
        return _packagemgt.RheiaPackageManager_ReadControlFileFor(*args, **kwargs)

    def InstallPackage(*args, **kwargs):
        """
        InstallPackage(self, String name, String fullname, String path, bool globaly=False, 
            bool silent=False, bool confirm=True) -> bool
        """
        return _packagemgt.RheiaPackageManager_InstallPackage(*args, **kwargs)

    def PurgePackage(*args, **kwargs):
        """
        PurgePackage(self, String name, bool silent=False, bool confirm=True, 
            bool recursive=True) -> bool
        """
        return _packagemgt.RheiaPackageManager_PurgePackage(*args, **kwargs)

    def OrderScanByDependencies(*args, **kwargs):
        """OrderScanByDependencies(self) -> wxArrayString"""
        return _packagemgt.RheiaPackageManager_OrderScanByDependencies(*args, **kwargs)

    def CheckScanDependencies(*args, **kwargs):
        """CheckScanDependencies(self, wxArrayString packages) -> String"""
        return _packagemgt.RheiaPackageManager_CheckScanDependencies(*args, **kwargs)

    def CheckDependenciesFor(*args, **kwargs):
        """CheckDependenciesFor(self, RheiaPackageControl ctrl, wxArrayString packages, String error) -> bool"""
        return _packagemgt.RheiaPackageManager_CheckDependenciesFor(*args, **kwargs)

    def CheckSdkVersionFor(*args, **kwargs):
        """CheckSdkVersionFor(self, RheiaPackageControl ctrl, String error) -> bool"""
        return _packagemgt.RheiaPackageManager_CheckSdkVersionFor(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _packagemgt.RheiaPackageManager_Clear(*args, **kwargs)

_packagemgt.RheiaPackageManager_swigregister(RheiaPackageManager)

class MgrRheiaPluginManager(object):
    """Proxy of C++ MgrRheiaPluginManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _packagemgt.MgrRheiaPluginManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaPluginManager"""
        return _packagemgt.MgrRheiaPluginManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _packagemgt.MgrRheiaPluginManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_packagemgt.MgrRheiaPluginManager_swigregister(MgrRheiaPluginManager)

def MgrRheiaPluginManager_Valid(*args):
  """MgrRheiaPluginManager_Valid() -> bool"""
  return _packagemgt.MgrRheiaPluginManager_Valid(*args)

def MgrRheiaPluginManager_Get(*args):
  """MgrRheiaPluginManager_Get() -> RheiaPluginManager"""
  return _packagemgt.MgrRheiaPluginManager_Get(*args)

def MgrRheiaPluginManager_Free(*args):
  """MgrRheiaPluginManager_Free()"""
  return _packagemgt.MgrRheiaPluginManager_Free(*args)

class RheiaPluginManager(wx._core.EvtHandler,MgrRheiaPluginManager):
    """Proxy of C++ RheiaPluginManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def CreateMenu(*args, **kwargs):
        """CreateMenu(self, MenuBar menuBar)"""
        return _packagemgt.RheiaPluginManager_CreateMenu(*args, **kwargs)

    def ReleaseMenu(*args, **kwargs):
        """ReleaseMenu(self, MenuBar menuBar)"""
        return _packagemgt.RheiaPluginManager_ReleaseMenu(*args, **kwargs)

    def LoadPlugin(*args, **kwargs):
        """LoadPlugin(self, String pluginName) -> bool"""
        return _packagemgt.RheiaPluginManager_LoadPlugin(*args, **kwargs)

    def LoadLibrary(*args, **kwargs):
        """LoadLibrary(self, String fileName) -> bool"""
        return _packagemgt.RheiaPluginManager_LoadLibrary(*args, **kwargs)

    def LoadAllPlugins(*args, **kwargs):
        """LoadAllPlugins(self)"""
        return _packagemgt.RheiaPluginManager_LoadAllPlugins(*args, **kwargs)

    def UnloadAllPlugins(*args, **kwargs):
        """UnloadAllPlugins(self)"""
        return _packagemgt.RheiaPluginManager_UnloadAllPlugins(*args, **kwargs)

    def UnloadPlugin(*args, **kwargs):
        """UnloadPlugin(self, RheiaPluginRegistration plugin)"""
        return _packagemgt.RheiaPluginManager_UnloadPlugin(*args, **kwargs)

    def AttachPlugin(*args, **kwargs):
        """AttachPlugin(self, RheiaPlugin plugin) -> bool"""
        return _packagemgt.RheiaPluginManager_AttachPlugin(*args, **kwargs)

    def DetachPlugin(*args, **kwargs):
        """DetachPlugin(self, RheiaPlugin plugin) -> bool"""
        return _packagemgt.RheiaPluginManager_DetachPlugin(*args, **kwargs)

    def RegisterPlugin(*args, **kwargs):
        """RegisterPlugin(self, String name, CreatePluginProcess createProc, FreePluginProcess freeProc) -> bool"""
        return _packagemgt.RheiaPluginManager_RegisterPlugin(*args, **kwargs)

    def ReadManifestFile(*args, **kwargs):
        """ReadManifestFile(self, String pluginFilename) -> RheiaPluginManifest"""
        return _packagemgt.RheiaPluginManager_ReadManifestFile(*args, **kwargs)

    def FindElement(*args, **kwargs):
        """FindElement(self, RheiaPlugin plugin) -> RheiaPluginRegistration"""
        return _packagemgt.RheiaPluginManager_FindElement(*args, **kwargs)

    def FindElementByName(*args, **kwargs):
        """FindElementByName(self, String pluginName) -> RheiaPluginRegistration"""
        return _packagemgt.RheiaPluginManager_FindElementByName(*args, **kwargs)

    def FindPlugin(*args, **kwargs):
        """FindPlugin(self, String pluginName) -> RheiaPlugin"""
        return _packagemgt.RheiaPluginManager_FindPlugin(*args, **kwargs)

    def NotifyPlugins(*args, **kwargs):
        """NotifyPlugins(self, RheiaEvent event)"""
        return _packagemgt.RheiaPluginManager_NotifyPlugins(*args, **kwargs)

    def GetOffersFor(*args, **kwargs):
        """GetOffersFor(self, int type) -> RheiaPluginsArray"""
        return _packagemgt.RheiaPluginManager_GetOffersFor(*args, **kwargs)

_packagemgt.RheiaPluginManager_swigregister(RheiaPluginManager)

class RheiaPluginManifest(object):
    """Proxy of C++ RheiaPluginManifest class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPluginManifest"""
        _packagemgt.RheiaPluginManifest_swiginit(self,_packagemgt.new_RheiaPluginManifest(*args, **kwargs))
    __swig_destroy__ = _packagemgt.delete_RheiaPluginManifest
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaPluginManifest"""
        return _packagemgt.RheiaPluginManifest_Clone(*args, **kwargs)

    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _packagemgt.RheiaPluginManifest_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _packagemgt.RheiaPluginManifest_SetName(*args, **kwargs)

    def GetTitle(*args, **kwargs):
        """GetTitle(self) -> String"""
        return _packagemgt.RheiaPluginManifest_GetTitle(*args, **kwargs)

    def SetTitle(*args, **kwargs):
        """SetTitle(self, String title)"""
        return _packagemgt.RheiaPluginManifest_SetTitle(*args, **kwargs)

    def GetThanksTo(*args, **kwargs):
        """GetThanksTo(self) -> String"""
        return _packagemgt.RheiaPluginManifest_GetThanksTo(*args, **kwargs)

    def SetThanksTo(*args, **kwargs):
        """SetThanksTo(self, String thanks)"""
        return _packagemgt.RheiaPluginManifest_SetThanksTo(*args, **kwargs)

    def GetClass(*args, **kwargs):
        """GetClass(self) -> String"""
        return _packagemgt.RheiaPluginManifest_GetClass(*args, **kwargs)

    def SetClass(*args, **kwargs):
        """SetClass(self, String classt)"""
        return _packagemgt.RheiaPluginManifest_SetClass(*args, **kwargs)

    def GetDescription(*args, **kwargs):
        """GetDescription(self) -> RheiaPackageDescription"""
        return _packagemgt.RheiaPluginManifest_GetDescription(*args, **kwargs)

    def SetDescription(*args, **kwargs):
        """SetDescription(self, RheiaPackageDescription description)"""
        return _packagemgt.RheiaPluginManifest_SetDescription(*args, **kwargs)

    def GetVersion(*args, **kwargs):
        """GetVersion(self) -> RheiaPackageVersion"""
        return _packagemgt.RheiaPluginManifest_GetVersion(*args, **kwargs)

    def SetVersion(*args, **kwargs):
        """SetVersion(self, RheiaPackageVersion version)"""
        return _packagemgt.RheiaPluginManifest_SetVersion(*args, **kwargs)

    def GetSDKVersion(*args, **kwargs):
        """GetSDKVersion(self) -> RheiaPackageVersion"""
        return _packagemgt.RheiaPluginManifest_GetSDKVersion(*args, **kwargs)

    def SetSDKVersion(*args, **kwargs):
        """SetSDKVersion(self, RheiaPackageVersion version)"""
        return _packagemgt.RheiaPluginManifest_SetSDKVersion(*args, **kwargs)

    def GetAuthor(*args, **kwargs):
        """GetAuthor(self) -> RheiaPackageMaintainer"""
        return _packagemgt.RheiaPluginManifest_GetAuthor(*args, **kwargs)

    def SetAuthor(*args, **kwargs):
        """SetAuthor(self, RheiaPackageMaintainer author)"""
        return _packagemgt.RheiaPluginManifest_SetAuthor(*args, **kwargs)

    def DoReadFromNode(*args, **kwargs):
        """DoReadFromNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPluginManifest_DoReadFromNode(*args, **kwargs)

    def DoWriteToNode(*args, **kwargs):
        """DoWriteToNode(self, xmlNode parent) -> bool"""
        return _packagemgt.RheiaPluginManifest_DoWriteToNode(*args, **kwargs)

_packagemgt.RheiaPluginManifest_swigregister(RheiaPluginManifest)

def RheiaPluginManifestCopy(*args, **kwargs):
    """RheiaPluginManifestCopy(RheiaPluginManifest rhs) -> RheiaPluginManifest"""
    val = _packagemgt.new_RheiaPluginManifestCopy(*args, **kwargs)
    return val



