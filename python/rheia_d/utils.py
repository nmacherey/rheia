# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

import _utils
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
    __swig_destroy__ = _utils.delete_PySwigIterator
    __del__ = lambda self : None;
    def value(*args): return _utils.PySwigIterator_value(*args)
    def incr(*args): return _utils.PySwigIterator_incr(*args)
    def decr(*args): return _utils.PySwigIterator_decr(*args)
    def distance(*args): return _utils.PySwigIterator_distance(*args)
    def equal(*args): return _utils.PySwigIterator_equal(*args)
    def copy(*args): return _utils.PySwigIterator_copy(*args)
    def next(*args): return _utils.PySwigIterator_next(*args)
    def previous(*args): return _utils.PySwigIterator_previous(*args)
    def advance(*args): return _utils.PySwigIterator_advance(*args)
    def __eq__(*args): return _utils.PySwigIterator___eq__(*args)
    def __ne__(*args): return _utils.PySwigIterator___ne__(*args)
    def __iadd__(*args): return _utils.PySwigIterator___iadd__(*args)
    def __isub__(*args): return _utils.PySwigIterator___isub__(*args)
    def __add__(*args): return _utils.PySwigIterator___add__(*args)
    def __sub__(*args): return _utils.PySwigIterator___sub__(*args)
    def __iter__(self): return self
_utils.PySwigIterator_swigregister(PySwigIterator)

import wx._core
import wx._windows
#// A little trick to make 'wx' be a reference to this module so wx.Names can
#// be used here.
import sys as _sys
rheia = _sys.modules[__name__]

sisLargeIcons = _utils.sisLargeIcons
sisNoIcons = _utils.sisNoIcons

def RheiaLoadBitmap(*args, **kwargs):
  """RheiaLoadBitmap(String filename, int bitmapType=BITMAP_TYPE_PNG) -> Bitmap"""
  return _utils.RheiaLoadBitmap(*args, **kwargs)
ptNone = _utils.ptNone
ptEnvironment = _utils.ptEnvironment
ptOption = _utils.ptOption
ptOther = _utils.ptOther

def RheiaMakeDir(*args, **kwargs):
  """RheiaMakeDir(String full_path, int perms=0775) -> bool"""
  return _utils.RheiaMakeDir(*args, **kwargs)

def RheiaMakeDirRecursively(*args, **kwargs):
  """RheiaMakeDirRecursively(String full_path, int perms=0775) -> bool"""
  return _utils.RheiaMakeDirRecursively(*args, **kwargs)

def DetermineExecutablePath(*args):
  """DetermineExecutablePath() -> String"""
  return _utils.DetermineExecutablePath(*args)

def DetermineResourcesPath(*args):
  """DetermineResourcesPath() -> String"""
  return _utils.DetermineResourcesPath(*args)

def RheiaC2U(*args, **kwargs):
  """RheiaC2U(char str) -> String"""
  return _utils.RheiaC2U(*args, **kwargs)

def RheiaU2C(*args, **kwargs):
  """RheiaU2C(String str) -> std::string"""
  return _utils.RheiaU2C(*args, **kwargs)

def RheiaMessageBox(*args, **kwargs):
  """
    RheiaMessageBox(String message, String caption=wxEmptyString, int style=OK, 
        Window parent=None, int x=-1, int y=-1) -> int
    """
  return _utils.RheiaMessageBox(*args, **kwargs)
dacInvalidDir = _utils.dacInvalidDir
dacReadWrite = _utils.dacReadWrite
dacReadOnly = _utils.dacReadOnly

def RheiaDirAccessCheck(*args, **kwargs):
  """RheiaDirAccessCheck(String dir) -> int"""
  return _utils.RheiaDirAccessCheck(*args, **kwargs)

def CompareVersions(*args, **kwargs):
  """CompareVersions(long major, long minor, long dmajor, long dminor) -> int"""
  return _utils.CompareVersions(*args, **kwargs)
class RheiaObjectWithBitmap(object):
    """Proxy of C++ RheiaObjectWithBitmap class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetBitmap(*args, **kwargs):
        """GetBitmap(self, int size) -> Bitmap"""
        return _utils.RheiaObjectWithBitmap_GetBitmap(*args, **kwargs)

_utils.RheiaObjectWithBitmap_swigregister(RheiaObjectWithBitmap)
cvar = _utils.cvar
DEFAULT_CONSOLE_TERM = cvar.DEFAULT_CONSOLE_TERM
DEFAULT_CONSOLE_SHELL = cvar.DEFAULT_CONSOLE_SHELL
WKSP_EXT = cvar.WKSP_EXT
WKSP_EXT_FILE = cvar.WKSP_EXT_FILE
WKSP_EXT_STANDARD = cvar.WKSP_EXT_STANDARD
PRJ_EXT = cvar.PRJ_EXT
PRJ_EXT_FILE = cvar.PRJ_EXT_FILE
PRJ_EXT_STANDARD = cvar.PRJ_EXT_STANDARD
PACKAGE_EXT = cvar.PACKAGE_EXT
PACKAGE_EXT_FILE = cvar.PACKAGE_EXT_FILE
PACKAGE_EXT_STANDARD = cvar.PACKAGE_EXT_STANDARD
PLUGIN_EXT = cvar.PLUGIN_EXT
PLUGIN_EXT_STANDARD = cvar.PLUGIN_EXT_STANDARD
PLUGIN_EXT_FILE = cvar.PLUGIN_EXT_FILE
DYNAMIC_LIBRARY_FILE_EXT = cvar.DYNAMIC_LIBRARY_FILE_EXT
DYNAMIC_LIBRARY_FILE_EXT_STANDARD = cvar.DYNAMIC_LIBRARY_FILE_EXT_STANDARD
DYNAMIC_LIBRARY_PREFIX = cvar.DYNAMIC_LIBRARY_PREFIX
DEFAULT_PANE_BORDER = cvar.DEFAULT_PANE_BORDER
DEFAULT_SASH_SIZE = cvar.DEFAULT_SASH_SIZE
DEFAULT_CAPTION_SIZE = cvar.DEFAULT_CAPTION_SIZE
DEFAULT_ACTIVE_CAPTION = cvar.DEFAULT_ACTIVE_CAPTION
DEFAULT_ACTIVE_CAPTION_GRADIENT = cvar.DEFAULT_ACTIVE_CAPTION_GRADIENT
DEFAULT_ACTIVE_TEXT_GRADIENT = cvar.DEFAULT_ACTIVE_TEXT_GRADIENT
DEFAULT_INACTIVE_CAPTION = cvar.DEFAULT_INACTIVE_CAPTION
DEFAULT_INACTIVE_CAPTION_GRADIENT = cvar.DEFAULT_INACTIVE_CAPTION_GRADIENT
DEFAULT_INACTIVE_TEXT_GRADIENT = cvar.DEFAULT_INACTIVE_TEXT_GRADIENT

class Stacker(object):
    """Proxy of C++ Stacker class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def StackMe(*args, **kwargs):
        """StackMe(self, int mySize) -> int"""
        return _utils.Stacker_StackMe(*args, **kwargs)

    def ReleaseMe(*args, **kwargs):
        """ReleaseMe(self, int myPos)"""
        return _utils.Stacker_ReleaseMe(*args, **kwargs)

_utils.Stacker_swigregister(Stacker)

class InfoWindow(wx._windows.Dialog):
    """Proxy of C++ InfoWindow class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Display(*args, **kwargs):
        """
        Display(String title, String message, unsigned int delay=5000, 
            unsigned int hysteresis=1)
        """
        return _utils.InfoWindow_Display(*args, **kwargs)

    Display = staticmethod(Display)
_utils.InfoWindow_swigregister(InfoWindow)

def InfoWindow_Display(*args, **kwargs):
  """
    InfoWindow_Display(String title, String message, unsigned int delay=5000, 
        unsigned int hysteresis=1)
    """
  return _utils.InfoWindow_Display(*args, **kwargs)

rspfHome = _utils.rspfHome
rspfInstall = _utils.rspfInstall
rspfTemp = _utils.rspfTemp
rspfPath = _utils.rspfPath
rspfLddir = _utils.rspfLddir
rspfConfig = _utils.rspfConfig
rspfAllBase = _utils.rspfAllBase
rspfPluginsUser = _utils.rspfPluginsUser
rspfDataUser = _utils.rspfDataUser
rspfPackageUser = _utils.rspfPackageUser
rspfCacheUser = _utils.rspfCacheUser
rspfAllUser = _utils.rspfAllUser
rspfPluginsGlobal = _utils.rspfPluginsGlobal
rspfDataGlobal = _utils.rspfDataGlobal
rspfPackageGlobal = _utils.rspfPackageGlobal
rspfCacheGlobal = _utils.rspfCacheGlobal
rspfAllGlobal = _utils.rspfAllGlobal
rspfAllKnown = _utils.rspfAllKnown
class RheiaStandardPaths(object):
    """Proxy of C++ RheiaStandardPaths class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def InitPaths(*args, **kwargs):
        """InitPaths(String appname)"""
        return _utils.RheiaStandardPaths_InitPaths(*args, **kwargs)

    InitPaths = staticmethod(InitPaths)
    def AppDirectory(*args, **kwargs):
        """AppDirectory() -> String"""
        return _utils.RheiaStandardPaths_AppDirectory(*args, **kwargs)

    AppDirectory = staticmethod(AppDirectory)
    def DataDirectoryGlobal(*args, **kwargs):
        """DataDirectoryGlobal() -> String"""
        return _utils.RheiaStandardPaths_DataDirectoryGlobal(*args, **kwargs)

    DataDirectoryGlobal = staticmethod(DataDirectoryGlobal)
    def PluginDirectoryGlobal(*args, **kwargs):
        """PluginDirectoryGlobal() -> String"""
        return _utils.RheiaStandardPaths_PluginDirectoryGlobal(*args, **kwargs)

    PluginDirectoryGlobal = staticmethod(PluginDirectoryGlobal)
    def PluginDirectoryUser(*args, **kwargs):
        """PluginDirectoryUser() -> String"""
        return _utils.RheiaStandardPaths_PluginDirectoryUser(*args, **kwargs)

    PluginDirectoryUser = staticmethod(PluginDirectoryUser)
    def PackageDirectoryGlobal(*args, **kwargs):
        """PackageDirectoryGlobal() -> String"""
        return _utils.RheiaStandardPaths_PackageDirectoryGlobal(*args, **kwargs)

    PackageDirectoryGlobal = staticmethod(PackageDirectoryGlobal)
    def PackageDirectoryUser(*args, **kwargs):
        """PackageDirectoryUser() -> String"""
        return _utils.RheiaStandardPaths_PackageDirectoryUser(*args, **kwargs)

    PackageDirectoryUser = staticmethod(PackageDirectoryUser)
    def CacheDirectoryGlobal(*args, **kwargs):
        """CacheDirectoryGlobal() -> String"""
        return _utils.RheiaStandardPaths_CacheDirectoryGlobal(*args, **kwargs)

    CacheDirectoryGlobal = staticmethod(CacheDirectoryGlobal)
    def CacheDirectoryUser(*args, **kwargs):
        """CacheDirectoryUser() -> String"""
        return _utils.RheiaStandardPaths_CacheDirectoryUser(*args, **kwargs)

    CacheDirectoryUser = staticmethod(CacheDirectoryUser)
    def DataDirectoryUser(*args, **kwargs):
        """DataDirectoryUser() -> String"""
        return _utils.RheiaStandardPaths_DataDirectoryUser(*args, **kwargs)

    DataDirectoryUser = staticmethod(DataDirectoryUser)
    def HomeDirectory(*args, **kwargs):
        """HomeDirectory() -> String"""
        return _utils.RheiaStandardPaths_HomeDirectory(*args, **kwargs)

    HomeDirectory = staticmethod(HomeDirectory)
    def ConfigDirectory(*args, **kwargs):
        """ConfigDirectory() -> String"""
        return _utils.RheiaStandardPaths_ConfigDirectory(*args, **kwargs)

    ConfigDirectory = staticmethod(ConfigDirectory)
    def Directory(*args, **kwargs):
        """Directory(int flag) -> String"""
        return _utils.RheiaStandardPaths_Directory(*args, **kwargs)

    Directory = staticmethod(Directory)
    def PluginsDirectory(*args, **kwargs):
        """PluginsDirectory(bool global=True) -> String"""
        return _utils.RheiaStandardPaths_PluginsDirectory(*args, **kwargs)

    PluginsDirectory = staticmethod(PluginsDirectory)
    def PackageDirectory(*args, **kwargs):
        """PackageDirectory(bool global=True) -> String"""
        return _utils.RheiaStandardPaths_PackageDirectory(*args, **kwargs)

    PackageDirectory = staticmethod(PackageDirectory)
    def CacheDirectory(*args, **kwargs):
        """CacheDirectory(bool global=True) -> String"""
        return _utils.RheiaStandardPaths_CacheDirectory(*args, **kwargs)

    CacheDirectory = staticmethod(CacheDirectory)
    def DataDirectory(*args, **kwargs):
        """DataDirectory(bool global=True) -> String"""
        return _utils.RheiaStandardPaths_DataDirectory(*args, **kwargs)

    DataDirectory = staticmethod(DataDirectory)
    def ExecutableDirectory(*args, **kwargs):
        """ExecutableDirectory() -> String"""
        return _utils.RheiaStandardPaths_ExecutableDirectory(*args, **kwargs)

    ExecutableDirectory = staticmethod(ExecutableDirectory)
    def GetTempDirectory(*args, **kwargs):
        """GetTempDirectory() -> String"""
        return _utils.RheiaStandardPaths_GetTempDirectory(*args, **kwargs)

    GetTempDirectory = staticmethod(GetTempDirectory)
    def TempDirectory(*args, **kwargs):
        """TempDirectory() -> String"""
        return _utils.RheiaStandardPaths_TempDirectory(*args, **kwargs)

    TempDirectory = staticmethod(TempDirectory)
_utils.RheiaStandardPaths_swigregister(RheiaStandardPaths)

def RheiaStandardPaths_InitPaths(*args, **kwargs):
  """RheiaStandardPaths_InitPaths(String appname)"""
  return _utils.RheiaStandardPaths_InitPaths(*args, **kwargs)

def RheiaStandardPaths_AppDirectory(*args):
  """RheiaStandardPaths_AppDirectory() -> String"""
  return _utils.RheiaStandardPaths_AppDirectory(*args)

def RheiaStandardPaths_DataDirectoryGlobal(*args):
  """RheiaStandardPaths_DataDirectoryGlobal() -> String"""
  return _utils.RheiaStandardPaths_DataDirectoryGlobal(*args)

def RheiaStandardPaths_PluginDirectoryGlobal(*args):
  """RheiaStandardPaths_PluginDirectoryGlobal() -> String"""
  return _utils.RheiaStandardPaths_PluginDirectoryGlobal(*args)

def RheiaStandardPaths_PluginDirectoryUser(*args):
  """RheiaStandardPaths_PluginDirectoryUser() -> String"""
  return _utils.RheiaStandardPaths_PluginDirectoryUser(*args)

def RheiaStandardPaths_PackageDirectoryGlobal(*args):
  """RheiaStandardPaths_PackageDirectoryGlobal() -> String"""
  return _utils.RheiaStandardPaths_PackageDirectoryGlobal(*args)

def RheiaStandardPaths_PackageDirectoryUser(*args):
  """RheiaStandardPaths_PackageDirectoryUser() -> String"""
  return _utils.RheiaStandardPaths_PackageDirectoryUser(*args)

def RheiaStandardPaths_CacheDirectoryGlobal(*args):
  """RheiaStandardPaths_CacheDirectoryGlobal() -> String"""
  return _utils.RheiaStandardPaths_CacheDirectoryGlobal(*args)

def RheiaStandardPaths_CacheDirectoryUser(*args):
  """RheiaStandardPaths_CacheDirectoryUser() -> String"""
  return _utils.RheiaStandardPaths_CacheDirectoryUser(*args)

def RheiaStandardPaths_DataDirectoryUser(*args):
  """RheiaStandardPaths_DataDirectoryUser() -> String"""
  return _utils.RheiaStandardPaths_DataDirectoryUser(*args)

def RheiaStandardPaths_HomeDirectory(*args):
  """RheiaStandardPaths_HomeDirectory() -> String"""
  return _utils.RheiaStandardPaths_HomeDirectory(*args)

def RheiaStandardPaths_ConfigDirectory(*args):
  """RheiaStandardPaths_ConfigDirectory() -> String"""
  return _utils.RheiaStandardPaths_ConfigDirectory(*args)

def RheiaStandardPaths_Directory(*args, **kwargs):
  """RheiaStandardPaths_Directory(int flag) -> String"""
  return _utils.RheiaStandardPaths_Directory(*args, **kwargs)

def RheiaStandardPaths_PluginsDirectory(*args, **kwargs):
  """RheiaStandardPaths_PluginsDirectory(bool global=True) -> String"""
  return _utils.RheiaStandardPaths_PluginsDirectory(*args, **kwargs)

def RheiaStandardPaths_PackageDirectory(*args, **kwargs):
  """RheiaStandardPaths_PackageDirectory(bool global=True) -> String"""
  return _utils.RheiaStandardPaths_PackageDirectory(*args, **kwargs)

def RheiaStandardPaths_CacheDirectory(*args, **kwargs):
  """RheiaStandardPaths_CacheDirectory(bool global=True) -> String"""
  return _utils.RheiaStandardPaths_CacheDirectory(*args, **kwargs)

def RheiaStandardPaths_DataDirectory(*args, **kwargs):
  """RheiaStandardPaths_DataDirectory(bool global=True) -> String"""
  return _utils.RheiaStandardPaths_DataDirectory(*args, **kwargs)

def RheiaStandardPaths_ExecutableDirectory(*args):
  """RheiaStandardPaths_ExecutableDirectory() -> String"""
  return _utils.RheiaStandardPaths_ExecutableDirectory(*args)

def RheiaStandardPaths_GetTempDirectory(*args):
  """RheiaStandardPaths_GetTempDirectory() -> String"""
  return _utils.RheiaStandardPaths_GetTempDirectory(*args)

def RheiaStandardPaths_TempDirectory(*args):
  """RheiaStandardPaths_TempDirectory() -> String"""
  return _utils.RheiaStandardPaths_TempDirectory(*args)


def FindFile(*args, **kwargs):
  """FindFile(String filename, int rspf=rspfAllKnown) -> String"""
  return _utils.FindFile(*args, **kwargs)


