# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

import _loggers
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
    __swig_destroy__ = _loggers.delete_PySwigIterator
    __del__ = lambda self : None;
    def value(*args): return _loggers.PySwigIterator_value(*args)
    def incr(*args): return _loggers.PySwigIterator_incr(*args)
    def decr(*args): return _loggers.PySwigIterator_decr(*args)
    def distance(*args): return _loggers.PySwigIterator_distance(*args)
    def equal(*args): return _loggers.PySwigIterator_equal(*args)
    def copy(*args): return _loggers.PySwigIterator_copy(*args)
    def next(*args): return _loggers.PySwigIterator_next(*args)
    def previous(*args): return _loggers.PySwigIterator_previous(*args)
    def advance(*args): return _loggers.PySwigIterator_advance(*args)
    def __eq__(*args): return _loggers.PySwigIterator___eq__(*args)
    def __ne__(*args): return _loggers.PySwigIterator___ne__(*args)
    def __iadd__(*args): return _loggers.PySwigIterator___iadd__(*args)
    def __isub__(*args): return _loggers.PySwigIterator___isub__(*args)
    def __add__(*args): return _loggers.PySwigIterator___add__(*args)
    def __sub__(*args): return _loggers.PySwigIterator___sub__(*args)
    def __iter__(self): return self
_loggers.PySwigIterator_swigregister(PySwigIterator)

import wx._core
import wx._windows
import utils
import base
#// A little trick to make 'wx' be a reference to this module so wx.Names can
#// be used here.
import sys as _sys
rheia = _sys.modules[__name__]

message = _loggers.message
warning = _loggers.warning
success = _loggers.success
error = _loggers.error
fatalerror = _loggers.fatalerror
info = _loggers.info
status = _loggers.status
syserror = _loggers.syserror
debug = _loggers.debug
trace = _loggers.trace
class RheiaLogger(wx._core.EvtHandler,base.RheiaPageContainer):
    """Proxy of C++ RheiaLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _loggers.delete_RheiaLogger
    __del__ = lambda self : None;
    def GetType(*args, **kwargs):
        """GetType(self) -> String"""
        return _loggers.RheiaLogger_GetType(*args, **kwargs)

    def SetType(*args, **kwargs):
        """SetType(self, String type)"""
        return _loggers.RheiaLogger_SetType(*args, **kwargs)

    def Log(*args, **kwargs):
        """Log(self, String msg, int level=message)"""
        return _loggers.RheiaLogger_Log(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _loggers.RheiaLogger_Clear(*args, **kwargs)

    def CopyAll(*args, **kwargs):
        """CopyAll(self)"""
        return _loggers.RheiaLogger_CopyAll(*args, **kwargs)

    def CopySelection(*args, **kwargs):
        """CopySelection(self)"""
        return _loggers.RheiaLogger_CopySelection(*args, **kwargs)

    def HelpOnSelection(*args, **kwargs):
        """HelpOnSelection(self)"""
        return _loggers.RheiaLogger_HelpOnSelection(*args, **kwargs)

    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, Menu menu)"""
        return _loggers.RheiaLogger_BuildMenu(*args, **kwargs)

    def UpdateSettings(*args, **kwargs):
        """UpdateSettings(self)"""
        return _loggers.RheiaLogger_UpdateSettings(*args, **kwargs)

_loggers.RheiaLogger_swigregister(RheiaLogger)
cvar = _loggers.cvar
RheiaLogLevelNumber = cvar.RheiaLogLevelNumber

class RheiaNullLogger(RheiaLogger):
    """Proxy of C++ RheiaNullLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
_loggers.RheiaNullLogger_swigregister(RheiaNullLogger)

class RheiaFileLogger(RheiaLogger):
    """Proxy of C++ RheiaFileLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaFileLogger"""
        _loggers.RheiaFileLogger_swiginit(self,_loggers.new_RheiaFileLogger(*args, **kwargs))
    __swig_destroy__ = _loggers.delete_RheiaFileLogger
    __del__ = lambda self : None;
    def SetFile(*args, **kwargs):
        """SetFile(self, String filename) -> bool"""
        return _loggers.RheiaFileLogger_SetFile(*args, **kwargs)

    def Open(*args, **kwargs):
        """Open(self, String filename) -> bool"""
        return _loggers.RheiaFileLogger_Open(*args, **kwargs)

    def Close(*args, **kwargs):
        """Close(self)"""
        return _loggers.RheiaFileLogger_Close(*args, **kwargs)

    def GetConfigurationTool(*args, **kwargs):
        """GetConfigurationTool(self, Window parent) -> RheiaConfigurationPanel"""
        return _loggers.RheiaFileLogger_GetConfigurationTool(*args, **kwargs)

_loggers.RheiaFileLogger_swigregister(RheiaFileLogger)

def RheiaFileLoggerCopy(*args, **kwargs):
    """RheiaFileLoggerCopy(String filename) -> RheiaFileLogger"""
    val = _loggers.new_RheiaFileLoggerCopy(*args, **kwargs)
    return val

class RheiaTimeStampableFileLogger(RheiaFileLogger):
    """Proxy of C++ RheiaTimeStampableFileLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaTimeStampableFileLogger"""
        _loggers.RheiaTimeStampableFileLogger_swiginit(self,_loggers.new_RheiaTimeStampableFileLogger(*args, **kwargs))
_loggers.RheiaTimeStampableFileLogger_swigregister(RheiaTimeStampableFileLogger)

def RheiaTimeStampableFileLoggerCopy(*args, **kwargs):
    """RheiaTimeStampableFileLoggerCopy(String filename) -> RheiaTimeStampableFileLogger"""
    val = _loggers.new_RheiaTimeStampableFileLoggerCopy(*args, **kwargs)
    return val

class RheiaHtmlHeader(object):
    """Proxy of C++ RheiaHtmlHeader class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    message = property(_loggers.RheiaHtmlHeader_message_get, _loggers.RheiaHtmlHeader_message_set)
    warning = property(_loggers.RheiaHtmlHeader_warning_get, _loggers.RheiaHtmlHeader_warning_set)
    success = property(_loggers.RheiaHtmlHeader_success_get, _loggers.RheiaHtmlHeader_success_set)
    error = property(_loggers.RheiaHtmlHeader_error_get, _loggers.RheiaHtmlHeader_error_set)
    fatalerror = property(_loggers.RheiaHtmlHeader_fatalerror_get, _loggers.RheiaHtmlHeader_fatalerror_set)
    info = property(_loggers.RheiaHtmlHeader_info_get, _loggers.RheiaHtmlHeader_info_set)
    status = property(_loggers.RheiaHtmlHeader_status_get, _loggers.RheiaHtmlHeader_status_set)
    syserror = property(_loggers.RheiaHtmlHeader_syserror_get, _loggers.RheiaHtmlHeader_syserror_set)
    debug = property(_loggers.RheiaHtmlHeader_debug_get, _loggers.RheiaHtmlHeader_debug_set)
    trace = property(_loggers.RheiaHtmlHeader_trace_get, _loggers.RheiaHtmlHeader_trace_set)
    h1 = property(_loggers.RheiaHtmlHeader_h1_get, _loggers.RheiaHtmlHeader_h1_set)
    h2 = property(_loggers.RheiaHtmlHeader_h2_get, _loggers.RheiaHtmlHeader_h2_set)
    timestamp = property(_loggers.RheiaHtmlHeader_timestamp_get, _loggers.RheiaHtmlHeader_timestamp_set)
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaHtmlHeader"""
        _loggers.RheiaHtmlHeader_swiginit(self,_loggers.new_RheiaHtmlHeader(*args, **kwargs))
_loggers.RheiaHtmlHeader_swigregister(RheiaHtmlHeader)

def RheiaHtmlHeaderCopy(*args, **kwargs):
    """RheiaHtmlHeaderCopy(RheiaHtmlHeader rhs) -> RheiaHtmlHeader"""
    val = _loggers.new_RheiaHtmlHeaderCopy(*args, **kwargs)
    return val

class RheiaHtmlLogger(RheiaFileLogger):
    """Proxy of C++ RheiaHtmlLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaHtmlLogger"""
        _loggers.RheiaHtmlLogger_swiginit(self,_loggers.new_RheiaHtmlLogger(*args, **kwargs))
    __swig_destroy__ = _loggers.delete_RheiaHtmlLogger
    __del__ = lambda self : None;
    def SetHeader(*args, **kwargs):
        """SetHeader(self, RheiaHtmlHeader header)"""
        return _loggers.RheiaHtmlLogger_SetHeader(*args, **kwargs)

_loggers.RheiaHtmlLogger_swigregister(RheiaHtmlLogger)

def RheiaHtmlLoggerCopy(*args, **kwargs):
    """RheiaHtmlLoggerCopy(String filename) -> RheiaHtmlLogger"""
    val = _loggers.new_RheiaHtmlLoggerCopy(*args, **kwargs)
    return val

class RheiaTimeStampableHtmlLogger(RheiaHtmlLogger):
    """Proxy of C++ RheiaTimeStampableHtmlLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaTimeStampableHtmlLogger"""
        _loggers.RheiaTimeStampableHtmlLogger_swiginit(self,_loggers.new_RheiaTimeStampableHtmlLogger(*args, **kwargs))
_loggers.RheiaTimeStampableHtmlLogger_swigregister(RheiaTimeStampableHtmlLogger)

def RheiaTimeStampableHtmlLoggerCopy(*args, **kwargs):
    """RheiaTimeStampableHtmlLoggerCopy(String filename) -> RheiaTimeStampableHtmlLogger"""
    val = _loggers.new_RheiaTimeStampableHtmlLoggerCopy(*args, **kwargs)
    return val

class MgrRheiaLoggerFactory(object):
    """Proxy of C++ MgrRheiaLoggerFactory class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _loggers.MgrRheiaLoggerFactory_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaLoggerFactory"""
        return _loggers.MgrRheiaLoggerFactory_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _loggers.MgrRheiaLoggerFactory_Free(*args, **kwargs)

    Free = staticmethod(Free)
_loggers.MgrRheiaLoggerFactory_swigregister(MgrRheiaLoggerFactory)

def MgrRheiaLoggerFactory_Valid(*args):
  """MgrRheiaLoggerFactory_Valid() -> bool"""
  return _loggers.MgrRheiaLoggerFactory_Valid(*args)

def MgrRheiaLoggerFactory_Get(*args):
  """MgrRheiaLoggerFactory_Get() -> RheiaLoggerFactory"""
  return _loggers.MgrRheiaLoggerFactory_Get(*args)

def MgrRheiaLoggerFactory_Free(*args):
  """MgrRheiaLoggerFactory_Free()"""
  return _loggers.MgrRheiaLoggerFactory_Free(*args)

class RheiaMgrRheiaLoggerManager(object):
    """Proxy of C++ RheiaMgrRheiaLoggerManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaLoggerManager"""
        return _loggers.RheiaMgrRheiaLoggerManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _loggers.RheiaMgrRheiaLoggerManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _loggers.RheiaMgrRheiaLoggerManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _loggers.RheiaMgrRheiaLoggerManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_loggers.RheiaMgrRheiaLoggerManager_swigregister(RheiaMgrRheiaLoggerManager)

def RheiaMgrRheiaLoggerManager_Get(*args, **kwargs):
  """RheiaMgrRheiaLoggerManager_Get(RheiaManagedFrame in) -> RheiaLoggerManager"""
  return _loggers.RheiaMgrRheiaLoggerManager_Get(*args, **kwargs)

def RheiaMgrRheiaLoggerManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaLoggerManager_Exists(RheiaManagedFrame in) -> bool"""
  return _loggers.RheiaMgrRheiaLoggerManager_Exists(*args, **kwargs)

def RheiaMgrRheiaLoggerManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaLoggerManager_FreeByInstance(RheiaManagedFrame in)"""
  return _loggers.RheiaMgrRheiaLoggerManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaLoggerManager_Free(*args):
  """RheiaMgrRheiaLoggerManager_Free()"""
  return _loggers.RheiaMgrRheiaLoggerManager_Free(*args)

class RheiaLoggerFactory(MgrRheiaLoggerFactory):
    """Proxy of C++ RheiaLoggerFactory class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def BuildLogger(*args, **kwargs):
        """BuildLogger(self, String type, String name) -> RheiaLogger"""
        return _loggers.RheiaLoggerFactory_BuildLogger(*args, **kwargs)

_loggers.RheiaLoggerFactory_swigregister(RheiaLoggerFactory)

class RheiaLoggerManager(wx._core.EvtHandler,RheiaMgrRheiaLoggerManager):
    """Proxy of C++ RheiaLoggerManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def InitializeEnvironment(*args, **kwargs):
        """InitializeEnvironment(self)"""
        return _loggers.RheiaLoggerManager_InitializeEnvironment(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _loggers.RheiaLoggerManager_RegisterEvents(*args, **kwargs)

    def OnUnregisterLogger(*args, **kwargs):
        """OnUnregisterLogger(self, CommandEvent event)"""
        return _loggers.RheiaLoggerManager_OnUnregisterLogger(*args, **kwargs)

    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, MenuBar menuBar)"""
        return _loggers.RheiaLoggerManager_BuildMenu(*args, **kwargs)

    def ReleaseMenu(*args, **kwargs):
        """ReleaseMenu(self, MenuBar menuBar)"""
        return _loggers.RheiaLoggerManager_ReleaseMenu(*args, **kwargs)

    def OnConfigure(*args, **kwargs):
        """OnConfigure(self, CommandEvent event)"""
        return _loggers.RheiaLoggerManager_OnConfigure(*args, **kwargs)

    def OnCloseFrame(*args, **kwargs):
        """OnCloseFrame(self, RheiaFrameEvent event)"""
        return _loggers.RheiaLoggerManager_OnCloseFrame(*args, **kwargs)

    def SetActiveLoggerByName(*args, **kwargs):
        """SetActiveLoggerByName(self, String name) -> bool"""
        return _loggers.RheiaLoggerManager_SetActiveLoggerByName(*args, **kwargs)

    def SetActiveLogger(*args, **kwargs):
        """SetActiveLogger(self, RheiaLogger logger) -> bool"""
        return _loggers.RheiaLoggerManager_SetActiveLogger(*args, **kwargs)

    def SetActiveLoggerByNameAndObject(*args, **kwargs):
        """SetActiveLoggerByNameAndObject(self, String name, RheiaLogger logger) -> bool"""
        return _loggers.RheiaLoggerManager_SetActiveLoggerByNameAndObject(*args, **kwargs)

    def GetActiveLogger(*args, **kwargs):
        """GetActiveLogger(self) -> RheiaLogger"""
        return _loggers.RheiaLoggerManager_GetActiveLogger(*args, **kwargs)

    def GetLogger(*args, **kwargs):
        """GetLogger(self, String name) -> RheiaLogger"""
        return _loggers.RheiaLoggerManager_GetLogger(*args, **kwargs)

    def GetRheiaLogger(*args, **kwargs):
        """GetRheiaLogger(self) -> RheiaLogger"""
        return _loggers.RheiaLoggerManager_GetRheiaLogger(*args, **kwargs)

    def GetRheiaDebugLogger(*args, **kwargs):
        """GetRheiaDebugLogger(self) -> RheiaLogger"""
        return _loggers.RheiaLoggerManager_GetRheiaDebugLogger(*args, **kwargs)

    def GetFirstLoggerOf(*args, **kwargs):
        """GetFirstLoggerOf(self, String type) -> RheiaLogger"""
        return _loggers.RheiaLoggerManager_GetFirstLoggerOf(*args, **kwargs)

    def GetLoggerName(*args, **kwargs):
        """GetLoggerName(self, RheiaLogger logger) -> String"""
        return _loggers.RheiaLoggerManager_GetLoggerName(*args, **kwargs)

    def sLog(*args, **kwargs):
        """sLog(String msg, int level=message)"""
        return _loggers.RheiaLoggerManager_sLog(*args, **kwargs)

    sLog = staticmethod(sLog)
    def sLogMessage(*args, **kwargs):
        """sLogMessage(String msg)"""
        return _loggers.RheiaLoggerManager_sLogMessage(*args, **kwargs)

    sLogMessage = staticmethod(sLogMessage)
    def sLogWarning(*args, **kwargs):
        """sLogWarning(String msg)"""
        return _loggers.RheiaLoggerManager_sLogWarning(*args, **kwargs)

    sLogWarning = staticmethod(sLogWarning)
    def sLogSuccess(*args, **kwargs):
        """sLogSuccess(String msg)"""
        return _loggers.RheiaLoggerManager_sLogSuccess(*args, **kwargs)

    sLogSuccess = staticmethod(sLogSuccess)
    def sLogError(*args, **kwargs):
        """sLogError(String msg)"""
        return _loggers.RheiaLoggerManager_sLogError(*args, **kwargs)

    sLogError = staticmethod(sLogError)
    def sLogFataError(*args, **kwargs):
        """sLogFataError(String msg)"""
        return _loggers.RheiaLoggerManager_sLogFataError(*args, **kwargs)

    sLogFataError = staticmethod(sLogFataError)
    def sLogInfo(*args, **kwargs):
        """sLogInfo(String msg)"""
        return _loggers.RheiaLoggerManager_sLogInfo(*args, **kwargs)

    sLogInfo = staticmethod(sLogInfo)
    def sLogStatus(*args, **kwargs):
        """sLogStatus(String msg)"""
        return _loggers.RheiaLoggerManager_sLogStatus(*args, **kwargs)

    sLogStatus = staticmethod(sLogStatus)
    def sLogSystemError(*args, **kwargs):
        """sLogSystemError(String msg)"""
        return _loggers.RheiaLoggerManager_sLogSystemError(*args, **kwargs)

    sLogSystemError = staticmethod(sLogSystemError)
    def sLogDebug(*args, **kwargs):
        """sLogDebug(String msg)"""
        return _loggers.RheiaLoggerManager_sLogDebug(*args, **kwargs)

    sLogDebug = staticmethod(sLogDebug)
    def sLogTrace(*args, **kwargs):
        """sLogTrace(String msg)"""
        return _loggers.RheiaLoggerManager_sLogTrace(*args, **kwargs)

    sLogTrace = staticmethod(sLogTrace)
    def sdLog(*args, **kwargs):
        """sdLog(String msg, int level=message)"""
        return _loggers.RheiaLoggerManager_sdLog(*args, **kwargs)

    sdLog = staticmethod(sdLog)
    def sdLogMessage(*args, **kwargs):
        """sdLogMessage(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogMessage(*args, **kwargs)

    sdLogMessage = staticmethod(sdLogMessage)
    def sdLogWarning(*args, **kwargs):
        """sdLogWarning(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogWarning(*args, **kwargs)

    sdLogWarning = staticmethod(sdLogWarning)
    def sdLogSuccess(*args, **kwargs):
        """sdLogSuccess(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogSuccess(*args, **kwargs)

    sdLogSuccess = staticmethod(sdLogSuccess)
    def sdLogError(*args, **kwargs):
        """sdLogError(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogError(*args, **kwargs)

    sdLogError = staticmethod(sdLogError)
    def sdLogFataError(*args, **kwargs):
        """sdLogFataError(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogFataError(*args, **kwargs)

    sdLogFataError = staticmethod(sdLogFataError)
    def sdLogInfo(*args, **kwargs):
        """sdLogInfo(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogInfo(*args, **kwargs)

    sdLogInfo = staticmethod(sdLogInfo)
    def sdLogStatus(*args, **kwargs):
        """sdLogStatus(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogStatus(*args, **kwargs)

    sdLogStatus = staticmethod(sdLogStatus)
    def sdLogSystemError(*args, **kwargs):
        """sdLogSystemError(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogSystemError(*args, **kwargs)

    sdLogSystemError = staticmethod(sdLogSystemError)
    def sdLogDebug(*args, **kwargs):
        """sdLogDebug(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogDebug(*args, **kwargs)

    sdLogDebug = staticmethod(sdLogDebug)
    def sdLogTrace(*args, **kwargs):
        """sdLogTrace(String msg)"""
        return _loggers.RheiaLoggerManager_sdLogTrace(*args, **kwargs)

    sdLogTrace = staticmethod(sdLogTrace)
    def Log(*args, **kwargs):
        """Log(self, String msg, int level=message)"""
        return _loggers.RheiaLoggerManager_Log(*args, **kwargs)

    def LogMessage(*args, **kwargs):
        """LogMessage(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogMessage(*args, **kwargs)

    def LogWarning(*args, **kwargs):
        """LogWarning(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogWarning(*args, **kwargs)

    def LogSuccess(*args, **kwargs):
        """LogSuccess(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogSuccess(*args, **kwargs)

    def LogError(*args, **kwargs):
        """LogError(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogError(*args, **kwargs)

    def LogFataError(*args, **kwargs):
        """LogFataError(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogFataError(*args, **kwargs)

    def LogInfo(*args, **kwargs):
        """LogInfo(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogInfo(*args, **kwargs)

    def LogStatus(*args, **kwargs):
        """LogStatus(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogStatus(*args, **kwargs)

    def LogSystemError(*args, **kwargs):
        """LogSystemError(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogSystemError(*args, **kwargs)

    def LogDebug(*args, **kwargs):
        """LogDebug(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogDebug(*args, **kwargs)

    def LogTrace(*args, **kwargs):
        """LogTrace(self, String msg)"""
        return _loggers.RheiaLoggerManager_LogTrace(*args, **kwargs)

    def ClearLog(*args, **kwargs):
        """ClearLog(self)"""
        return _loggers.RheiaLoggerManager_ClearLog(*args, **kwargs)

    def CleaLogByName(*args, **kwargs):
        """CleaLogByName(self, String name)"""
        return _loggers.RheiaLoggerManager_CleaLogByName(*args, **kwargs)

    def ListLoggers(*args, **kwargs):
        """ListLoggers(self) -> wxArrayString"""
        return _loggers.RheiaLoggerManager_ListLoggers(*args, **kwargs)

    def AddLogger(*args, **kwargs):
        """AddLogger(self, RheiaLogger logger, String name) -> bool"""
        return _loggers.RheiaLoggerManager_AddLogger(*args, **kwargs)

    def DeleteLogger(*args, **kwargs):
        """DeleteLogger(self, RheiaLogger logger) -> bool"""
        return _loggers.RheiaLoggerManager_DeleteLogger(*args, **kwargs)

    def DeleteLoggerByName(*args, **kwargs):
        """DeleteLoggerByName(self, String name) -> bool"""
        return _loggers.RheiaLoggerManager_DeleteLoggerByName(*args, **kwargs)

    def NotifyUpdate(*args, **kwargs):
        """NotifyUpdate(self)"""
        return _loggers.RheiaLoggerManager_NotifyUpdate(*args, **kwargs)

    def ShowLoggerByName(*args, **kwargs):
        """ShowLoggerByName(self, String name)"""
        return _loggers.RheiaLoggerManager_ShowLoggerByName(*args, **kwargs)

    def Show(*args, **kwargs):
        """Show(self, RheiaLogger logger)"""
        return _loggers.RheiaLoggerManager_Show(*args, **kwargs)

    def GetLogPageIndexByName(*args, **kwargs):
        """GetLogPageIndexByName(self, String name) -> int"""
        return _loggers.RheiaLoggerManager_GetLogPageIndexByName(*args, **kwargs)

    def GetLogPageIndex(*args, **kwargs):
        """GetLogPageIndex(self, RheiaLogger logger) -> int"""
        return _loggers.RheiaLoggerManager_GetLogPageIndex(*args, **kwargs)

    def GetConfigurationGroupFor(*args, **kwargs):
        """GetConfigurationGroupFor(self, RheiaLogger logger) -> RheiaConfigurationManager"""
        return _loggers.RheiaLoggerManager_GetConfigurationGroupFor(*args, **kwargs)

    def GetConfigurationGroupByNameFor(*args, **kwargs):
        """GetConfigurationGroupByNameFor(self, String name) -> RheiaConfigurationManager"""
        return _loggers.RheiaLoggerManager_GetConfigurationGroupByNameFor(*args, **kwargs)

_loggers.RheiaLoggerManager_swigregister(RheiaLoggerManager)

def RheiaLoggerManager_sLog(*args, **kwargs):
  """RheiaLoggerManager_sLog(String msg, int level=message)"""
  return _loggers.RheiaLoggerManager_sLog(*args, **kwargs)

def RheiaLoggerManager_sLogMessage(*args, **kwargs):
  """RheiaLoggerManager_sLogMessage(String msg)"""
  return _loggers.RheiaLoggerManager_sLogMessage(*args, **kwargs)

def RheiaLoggerManager_sLogWarning(*args, **kwargs):
  """RheiaLoggerManager_sLogWarning(String msg)"""
  return _loggers.RheiaLoggerManager_sLogWarning(*args, **kwargs)

def RheiaLoggerManager_sLogSuccess(*args, **kwargs):
  """RheiaLoggerManager_sLogSuccess(String msg)"""
  return _loggers.RheiaLoggerManager_sLogSuccess(*args, **kwargs)

def RheiaLoggerManager_sLogError(*args, **kwargs):
  """RheiaLoggerManager_sLogError(String msg)"""
  return _loggers.RheiaLoggerManager_sLogError(*args, **kwargs)

def RheiaLoggerManager_sLogFataError(*args, **kwargs):
  """RheiaLoggerManager_sLogFataError(String msg)"""
  return _loggers.RheiaLoggerManager_sLogFataError(*args, **kwargs)

def RheiaLoggerManager_sLogInfo(*args, **kwargs):
  """RheiaLoggerManager_sLogInfo(String msg)"""
  return _loggers.RheiaLoggerManager_sLogInfo(*args, **kwargs)

def RheiaLoggerManager_sLogStatus(*args, **kwargs):
  """RheiaLoggerManager_sLogStatus(String msg)"""
  return _loggers.RheiaLoggerManager_sLogStatus(*args, **kwargs)

def RheiaLoggerManager_sLogSystemError(*args, **kwargs):
  """RheiaLoggerManager_sLogSystemError(String msg)"""
  return _loggers.RheiaLoggerManager_sLogSystemError(*args, **kwargs)

def RheiaLoggerManager_sLogDebug(*args, **kwargs):
  """RheiaLoggerManager_sLogDebug(String msg)"""
  return _loggers.RheiaLoggerManager_sLogDebug(*args, **kwargs)

def RheiaLoggerManager_sLogTrace(*args, **kwargs):
  """RheiaLoggerManager_sLogTrace(String msg)"""
  return _loggers.RheiaLoggerManager_sLogTrace(*args, **kwargs)

def RheiaLoggerManager_sdLog(*args, **kwargs):
  """RheiaLoggerManager_sdLog(String msg, int level=message)"""
  return _loggers.RheiaLoggerManager_sdLog(*args, **kwargs)

def RheiaLoggerManager_sdLogMessage(*args, **kwargs):
  """RheiaLoggerManager_sdLogMessage(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogMessage(*args, **kwargs)

def RheiaLoggerManager_sdLogWarning(*args, **kwargs):
  """RheiaLoggerManager_sdLogWarning(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogWarning(*args, **kwargs)

def RheiaLoggerManager_sdLogSuccess(*args, **kwargs):
  """RheiaLoggerManager_sdLogSuccess(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogSuccess(*args, **kwargs)

def RheiaLoggerManager_sdLogError(*args, **kwargs):
  """RheiaLoggerManager_sdLogError(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogError(*args, **kwargs)

def RheiaLoggerManager_sdLogFataError(*args, **kwargs):
  """RheiaLoggerManager_sdLogFataError(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogFataError(*args, **kwargs)

def RheiaLoggerManager_sdLogInfo(*args, **kwargs):
  """RheiaLoggerManager_sdLogInfo(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogInfo(*args, **kwargs)

def RheiaLoggerManager_sdLogStatus(*args, **kwargs):
  """RheiaLoggerManager_sdLogStatus(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogStatus(*args, **kwargs)

def RheiaLoggerManager_sdLogSystemError(*args, **kwargs):
  """RheiaLoggerManager_sdLogSystemError(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogSystemError(*args, **kwargs)

def RheiaLoggerManager_sdLogDebug(*args, **kwargs):
  """RheiaLoggerManager_sdLogDebug(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogDebug(*args, **kwargs)

def RheiaLoggerManager_sdLogTrace(*args, **kwargs):
  """RheiaLoggerManager_sdLogTrace(String msg)"""
  return _loggers.RheiaLoggerManager_sdLogTrace(*args, **kwargs)

class RheiaLoggerPageInfo(object):
    """Proxy of C++ RheiaLoggerPageInfo class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaLoggerPageInfo"""
        _loggers.RheiaLoggerPageInfo_swiginit(self,_loggers.new_RheiaLoggerPageInfo(*args, **kwargs))
    __swig_destroy__ = _loggers.delete_RheiaLoggerPageInfo
    __del__ = lambda self : None;
    name = property(_loggers.RheiaLoggerPageInfo_name_get, _loggers.RheiaLoggerPageInfo_name_set)
    page = property(_loggers.RheiaLoggerPageInfo_page_get, _loggers.RheiaLoggerPageInfo_page_set)
_loggers.RheiaLoggerPageInfo_swigregister(RheiaLoggerPageInfo)

def RheiaLoggerPageInfoCopy(*args, **kwargs):
    """RheiaLoggerPageInfoCopy(RheiaLoggerPageInfo rhs) -> RheiaLoggerPageInfo"""
    val = _loggers.new_RheiaLoggerPageInfoCopy(*args, **kwargs)
    return val

class RheiaLogMgrSettingsPanel(base.RheiaConfigurationPanel):
    """Proxy of C++ RheiaLogMgrSettingsPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaLogMgrSettingsPanel"""
        _loggers.RheiaLogMgrSettingsPanel_swiginit(self,_loggers.new_RheiaLogMgrSettingsPanel(*args, **kwargs))
_loggers.RheiaLogMgrSettingsPanel_swigregister(RheiaLogMgrSettingsPanel)

class RheiaStdLogger(RheiaLogger):
    """Proxy of C++ RheiaStdLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
_loggers.RheiaStdLogger_swigregister(RheiaStdLogger)

class RheiaTimeStampableStdLogger(RheiaLogger):
    """Proxy of C++ RheiaTimeStampableStdLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
_loggers.RheiaTimeStampableStdLogger_swigregister(RheiaTimeStampableStdLogger)

class RheiaTextLogger(RheiaLogger):
    """Proxy of C++ RheiaTextLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaTextLogger"""
        _loggers.RheiaTextLogger_swiginit(self,_loggers.new_RheiaTextLogger(*args, **kwargs))
    __swig_destroy__ = _loggers.delete_RheiaTextLogger
    __del__ = lambda self : None;
    def OnTextLoggerSettings(*args, **kwargs):
        """OnTextLoggerSettings(self, CommandEvent event)"""
        return _loggers.RheiaTextLogger_OnTextLoggerSettings(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _loggers.RheiaTextLogger_RegisterEvents(*args, **kwargs)

    def GetTextAttributes(*args, **kwargs):
        """GetTextAttributes(self) -> wxTextAttrEx"""
        return _loggers.RheiaTextLogger_GetTextAttributes(*args, **kwargs)

_loggers.RheiaTextLogger_swigregister(RheiaTextLogger)

class RheiaTimeStampableTextLogger(RheiaTextLogger):
    """Proxy of C++ RheiaTimeStampableTextLogger class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaTimeStampableTextLogger"""
        _loggers.RheiaTimeStampableTextLogger_swiginit(self,_loggers.new_RheiaTimeStampableTextLogger(*args, **kwargs))
_loggers.RheiaTimeStampableTextLogger_swigregister(RheiaTimeStampableTextLogger)

class RheiaTextLoggerConfigurationPanel(base.RheiaConfigurationPanel):
    """Proxy of C++ RheiaTextLoggerConfigurationPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaTextLoggerConfigurationPanel"""
        _loggers.RheiaTextLoggerConfigurationPanel_swiginit(self,_loggers.new_RheiaTextLoggerConfigurationPanel(*args, **kwargs))
    def DoInitEnvironment(*args, **kwargs):
        """DoInitEnvironment(self)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_DoInitEnvironment(*args, **kwargs)

    def UpdateInfoFor(*args, **kwargs):
        """UpdateInfoFor(self, int selection)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateInfoFor(*args, **kwargs)

    def UpdateSample(*args, **kwargs):
        """UpdateSample(self)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateSample(*args, **kwargs)

    def UpdateFontFor(*args, **kwargs):
        """UpdateFontFor(self, int selection, Font font)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateFontFor(*args, **kwargs)

    def UpdateBackgroundColorFor(*args, **kwargs):
        """UpdateBackgroundColorFor(self, int selection, Colour colour)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateBackgroundColorFor(*args, **kwargs)

    def UpdateForegroundColorFor(*args, **kwargs):
        """UpdateForegroundColorFor(self, int selection, Colour colour)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateForegroundColorFor(*args, **kwargs)

    def UpdateUnderlinedFor(*args, **kwargs):
        """UpdateUnderlinedFor(self, int selection, bool underlined)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateUnderlinedFor(*args, **kwargs)

    def UpdateAlignmentFor(*args, **kwargs):
        """UpdateAlignmentFor(self, int selection, wxTextAttrAlignment align)"""
        return _loggers.RheiaTextLoggerConfigurationPanel_UpdateAlignmentFor(*args, **kwargs)

_loggers.RheiaTextLoggerConfigurationPanel_swigregister(RheiaTextLoggerConfigurationPanel)

class RheiaTextLoggerPage(base.RheiaBookPage):
    """Proxy of C++ RheiaTextLoggerPage class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent, RheiaTextLogger logger) -> RheiaTextLoggerPage"""
        _loggers.RheiaTextLoggerPage_swiginit(self,_loggers.new_RheiaTextLoggerPage(*args, **kwargs))
    __swig_destroy__ = _loggers.delete_RheiaTextLoggerPage
    __del__ = lambda self : None;
    def GetTextCtrl(*args, **kwargs):
        """GetTextCtrl(self) -> RichTextCtrl"""
        return _loggers.RheiaTextLoggerPage_GetTextCtrl(*args, **kwargs)

    def GetContent(*args, **kwargs):
        """GetContent(self, RichTextBuffer content)"""
        return _loggers.RheiaTextLoggerPage_GetContent(*args, **kwargs)

    def SetContent(*args, **kwargs):
        """SetContent(self, RichTextBuffer content)"""
        return _loggers.RheiaTextLoggerPage_SetContent(*args, **kwargs)

_loggers.RheiaTextLoggerPage_swigregister(RheiaTextLoggerPage)



