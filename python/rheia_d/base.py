# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

import _base
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
    __swig_destroy__ = _base.delete_PySwigIterator
    __del__ = lambda self : None;
    def value(*args): return _base.PySwigIterator_value(*args)
    def incr(*args): return _base.PySwigIterator_incr(*args)
    def decr(*args): return _base.PySwigIterator_decr(*args)
    def distance(*args): return _base.PySwigIterator_distance(*args)
    def equal(*args): return _base.PySwigIterator_equal(*args)
    def copy(*args): return _base.PySwigIterator_copy(*args)
    def next(*args): return _base.PySwigIterator_next(*args)
    def previous(*args): return _base.PySwigIterator_previous(*args)
    def advance(*args): return _base.PySwigIterator_advance(*args)
    def __eq__(*args): return _base.PySwigIterator___eq__(*args)
    def __ne__(*args): return _base.PySwigIterator___ne__(*args)
    def __iadd__(*args): return _base.PySwigIterator___iadd__(*args)
    def __isub__(*args): return _base.PySwigIterator___isub__(*args)
    def __add__(*args): return _base.PySwigIterator___add__(*args)
    def __sub__(*args): return _base.PySwigIterator___sub__(*args)
    def __iter__(self): return self
_base.PySwigIterator_swigregister(PySwigIterator)

import wx._core
import wx._windows
import utils
import sys as _sys
rheia = _sys.modules[__name__]

class RheiaConfigurationPanel(wx._windows.Panel):
    """Proxy of C++ RheiaConfigurationPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _base.delete_RheiaConfigurationPanel
    __del__ = lambda self : None;
    def GetTitle(*args, **kwargs):
        """GetTitle(self) -> String"""
        return _base.RheiaConfigurationPanel_GetTitle(*args, **kwargs)

    def GetBitmapBaseName(*args, **kwargs):
        """GetBitmapBaseName(self) -> String"""
        return _base.RheiaConfigurationPanel_GetBitmapBaseName(*args, **kwargs)

    def OnApply(*args, **kwargs):
        """OnApply(self) -> bool"""
        return _base.RheiaConfigurationPanel_OnApply(*args, **kwargs)

    def OnCancel(*args, **kwargs):
        """OnCancel(self) -> bool"""
        return _base.RheiaConfigurationPanel_OnCancel(*args, **kwargs)

_base.RheiaConfigurationPanel_swigregister(RheiaConfigurationPanel)

class RheiaApplicationGeneralPanel(RheiaConfigurationPanel):
    """Proxy of C++ RheiaApplicationGeneralPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaApplicationGeneralPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _base.RheiaApplicationGeneralPanel_swiginit(self,_base.new_RheiaApplicationGeneralPanel(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaApplicationGeneralPanel
    __del__ = lambda self : None;
_base.RheiaApplicationGeneralPanel_swigregister(RheiaApplicationGeneralPanel)

class RheiaBookConfigurationPanel(RheiaConfigurationPanel):
    """Proxy of C++ RheiaBookConfigurationPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent, RheiaConfigurationManager cfg) -> RheiaBookConfigurationPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _base.RheiaBookConfigurationPanel_swiginit(self,_base.new_RheiaBookConfigurationPanel(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaBookConfigurationPanel
    __del__ = lambda self : None;
_base.RheiaBookConfigurationPanel_swigregister(RheiaBookConfigurationPanel)

class RheiaCenterMgrSettingsPanel(RheiaConfigurationPanel):
    """Proxy of C++ RheiaCenterMgrSettingsPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaCenterMgrSettingsPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _base.RheiaCenterMgrSettingsPanel_swiginit(self,_base.new_RheiaCenterMgrSettingsPanel(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaCenterMgrSettingsPanel
    __del__ = lambda self : None;
_base.RheiaCenterMgrSettingsPanel_swigregister(RheiaCenterMgrSettingsPanel)

class RheiaDockSystSettingsPanel(RheiaConfigurationPanel):
    """Proxy of C++ RheiaDockSystSettingsPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaDockSystSettingsPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _base.RheiaDockSystSettingsPanel_swiginit(self,_base.new_RheiaDockSystSettingsPanel(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaDockSystSettingsPanel
    __del__ = lambda self : None;
_base.RheiaDockSystSettingsPanel_swigregister(RheiaDockSystSettingsPanel)

class RheiaInfoMgrSettingsPanel(RheiaConfigurationPanel):
    """Proxy of C++ RheiaInfoMgrSettingsPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaInfoMgrSettingsPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _base.RheiaInfoMgrSettingsPanel_swiginit(self,_base.new_RheiaInfoMgrSettingsPanel(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaInfoMgrSettingsPanel
    __del__ = lambda self : None;
_base.RheiaInfoMgrSettingsPanel_swigregister(RheiaInfoMgrSettingsPanel)

class RheiaInfoPage(wx._windows.Panel):
    """Proxy of C++ RheiaInfoPage class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _base.delete_RheiaInfoPage
    __del__ = lambda self : None;
    def OnPageChanging(*args, **kwargs):
        """OnPageChanging(self) -> bool"""
        return _base.RheiaInfoPage_OnPageChanging(*args, **kwargs)

    def OnPageChanged(*args, **kwargs):
        """OnPageChanged(self) -> bool"""
        return _base.RheiaInfoPage_OnPageChanged(*args, **kwargs)

    def OnPageClosed(*args, **kwargs):
        """OnPageClosed(self)"""
        return _base.RheiaInfoPage_OnPageClosed(*args, **kwargs)

    def OnPageUpdate(*args, **kwargs):
        """OnPageUpdate(self)"""
        return _base.RheiaInfoPage_OnPageUpdate(*args, **kwargs)

    def OnDelete(*args, **kwargs):
        """OnDelete(self)"""
        return _base.RheiaInfoPage_OnDelete(*args, **kwargs)

    def OnCreate(*args, **kwargs):
        """OnCreate(self)"""
        return _base.RheiaInfoPage_OnCreate(*args, **kwargs)

    def GetBitmap(*args, **kwargs):
        """GetBitmap(self, int size) -> Bitmap"""
        return _base.RheiaInfoPage_GetBitmap(*args, **kwargs)

_base.RheiaInfoPage_swigregister(RheiaInfoPage)

class RheiaLeftMgrSettingsPanel(RheiaConfigurationPanel):
    """Proxy of C++ RheiaLeftMgrSettingsPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaLeftMgrSettingsPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _base.RheiaLeftMgrSettingsPanel_swiginit(self,_base.new_RheiaLeftMgrSettingsPanel(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaLeftMgrSettingsPanel
    __del__ = lambda self : None;
_base.RheiaLeftMgrSettingsPanel_swigregister(RheiaLeftMgrSettingsPanel)

class RheiaPageInfo(object):
    """Proxy of C++ RheiaPageInfo class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaPageInfo"""
        _base.RheiaPageInfo_swiginit(self,_base.new_RheiaPageInfo(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaPageInfo
    __del__ = lambda self : None;
    name = property(_base.RheiaPageInfo_name_get, _base.RheiaPageInfo_name_set)
    bmp = property(_base.RheiaPageInfo_bmp_get, _base.RheiaPageInfo_bmp_set)
    container = property(_base.RheiaPageInfo_container_get, _base.RheiaPageInfo_container_set)
    page = property(_base.RheiaPageInfo_page_get, _base.RheiaPageInfo_page_set)
_base.RheiaPageInfo_swigregister(RheiaPageInfo)

def RheiaPageInfoCopy(*args, **kwargs):
    """RheiaPageInfoCopy(RheiaPageInfo rhs) -> RheiaPageInfo"""
    val = _base.new_RheiaPageInfoCopy(*args, **kwargs)
    return val

class RheiaBookManager(wx._core.EvtHandler):
    """Proxy of C++ RheiaBookManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, MenuBar ?)"""
        return _base.RheiaBookManager_BuildMenu(*args, **kwargs)

    def ReleaseMenu(*args, **kwargs):
        """ReleaseMenu(self, MenuBar ?)"""
        return _base.RheiaBookManager_ReleaseMenu(*args, **kwargs)

    def GetNoteBook(*args, **kwargs):
        """GetNoteBook(self) -> AuiNotebook"""
        return _base.RheiaBookManager_GetNoteBook(*args, **kwargs)

    def CreateWindow(*args, **kwargs):
        """CreateWindow(self, Window parent) -> AuiNotebook"""
        return _base.RheiaBookManager_CreateWindow(*args, **kwargs)

    def OnCreateWindow(*args, **kwargs):
        """OnCreateWindow(self)"""
        return _base.RheiaBookManager_OnCreateWindow(*args, **kwargs)

    def OnCloseParent(*args, **kwargs):
        """OnCloseParent(self, RheiaFrameEvent event)"""
        return _base.RheiaBookManager_OnCloseParent(*args, **kwargs)

    def ReloadBookConfiguration(*args, **kwargs):
        """ReloadBookConfiguration(self, RheiaConfigurationManager cfg)"""
        return _base.RheiaBookManager_ReloadBookConfiguration(*args, **kwargs)

    def AddPage(*args, **kwargs):
        """AddPage(self, String name, RheiaPageContainer container) -> bool"""
        return _base.RheiaBookManager_AddPage(*args, **kwargs)

    def DeletePage(*args, **kwargs):
        """DeletePage(self, String name) -> bool"""
        return _base.RheiaBookManager_DeletePage(*args, **kwargs)

    def RemovePage(*args, **kwargs):
        """RemovePage(self, String name) -> bool"""
        return _base.RheiaBookManager_RemovePage(*args, **kwargs)

    def RenamePage(*args, **kwargs):
        """RenamePage(self, String oldName, String newName)"""
        return _base.RheiaBookManager_RenamePage(*args, **kwargs)

    def ClosePage(*args, **kwargs):
        """ClosePage(self, String name) -> bool"""
        return _base.RheiaBookManager_ClosePage(*args, **kwargs)

    def PageIsOpened(*args, **kwargs):
        """PageIsOpened(self, String name) -> bool"""
        return _base.RheiaBookManager_PageIsOpened(*args, **kwargs)

    def PageExists(*args, **kwargs):
        """PageExists(self, String name) -> bool"""
        return _base.RheiaBookManager_PageExists(*args, **kwargs)

    def ActivatePage(*args, **kwargs):
        """ActivatePage(self, String name) -> bool"""
        return _base.RheiaBookManager_ActivatePage(*args, **kwargs)

    def GetActivePageName(*args, **kwargs):
        """GetActivePageName(self) -> String"""
        return _base.RheiaBookManager_GetActivePageName(*args, **kwargs)

    def GetActivePage(*args, **kwargs):
        """GetActivePage(self) -> RheiaBookPage"""
        return _base.RheiaBookManager_GetActivePage(*args, **kwargs)

    def FindPageByName(*args, **kwargs):
        """FindPageByName(self, String name) -> RheiaBookPage"""
        return _base.RheiaBookManager_FindPageByName(*args, **kwargs)

    def FindPageIndexByName(*args, **kwargs):
        """FindPageIndexByName(self, String name) -> int"""
        return _base.RheiaBookManager_FindPageIndexByName(*args, **kwargs)

    def FindPageNameByObject(*args, **kwargs):
        """FindPageNameByObject(self, RheiaBookPage page) -> String"""
        return _base.RheiaBookManager_FindPageNameByObject(*args, **kwargs)

    def FindPageIndexByObject(*args, **kwargs):
        """FindPageIndexByObject(self, RheiaBookPage page) -> int"""
        return _base.RheiaBookManager_FindPageIndexByObject(*args, **kwargs)

    def FindPageNameByContainer(*args, **kwargs):
        """FindPageNameByContainer(self, RheiaPageContainer container) -> String"""
        return _base.RheiaBookManager_FindPageNameByContainer(*args, **kwargs)

    def FindPageByContainer(*args, **kwargs):
        """FindPageByContainer(self, RheiaPageContainer container) -> RheiaBookPage"""
        return _base.RheiaBookManager_FindPageByContainer(*args, **kwargs)

    def FindPageIndexByContainer(*args, **kwargs):
        """FindPageIndexByContainer(self, RheiaPageContainer container) -> int"""
        return _base.RheiaBookManager_FindPageIndexByContainer(*args, **kwargs)

_base.RheiaBookManager_swigregister(RheiaBookManager)

class RheiaBookPage(wx._windows.Panel):
    """Proxy of C++ RheiaBookPage class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaBookPage"""
        _base.RheiaBookPage_swiginit(self,_base.new_RheiaBookPage(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaBookPage
    __del__ = lambda self : None;
    def OnPageChanging(*args, **kwargs):
        """OnPageChanging(self) -> bool"""
        return _base.RheiaBookPage_OnPageChanging(*args, **kwargs)

    def OnPageChanged(*args, **kwargs):
        """OnPageChanged(self) -> bool"""
        return _base.RheiaBookPage_OnPageChanged(*args, **kwargs)

    def OnPageClosed(*args, **kwargs):
        """OnPageClosed(self)"""
        return _base.RheiaBookPage_OnPageClosed(*args, **kwargs)

    def OnTabRightClicked(*args, **kwargs):
        """OnTabRightClicked(self)"""
        return _base.RheiaBookPage_OnTabRightClicked(*args, **kwargs)

    def OnPageUpdate(*args, **kwargs):
        """OnPageUpdate(self)"""
        return _base.RheiaBookPage_OnPageUpdate(*args, **kwargs)

    def OnDelete(*args, **kwargs):
        """OnDelete(self)"""
        return _base.RheiaBookPage_OnDelete(*args, **kwargs)

    def OnCreate(*args, **kwargs):
        """OnCreate(self)"""
        return _base.RheiaBookPage_OnCreate(*args, **kwargs)

_base.RheiaBookPage_swigregister(RheiaBookPage)

class RheiaManager(object):
    """Proxy of C++ RheiaManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaManager"""
        _base.RheiaManager_swiginit(self,_base.new_RheiaManager(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaManager
    __del__ = lambda self : None;
    def Get(*args, **kwargs):
        """Get() -> RheiaManager"""
        return _base.RheiaManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
    def Close(*args, **kwargs):
        """Close(self)"""
        return _base.RheiaManager_Close(*args, **kwargs)

    def LoadResource(*args, **kwargs):
        """LoadResource(String file) -> bool"""
        return _base.RheiaManager_LoadResource(*args, **kwargs)

    LoadResource = staticmethod(LoadResource)
    def GetCenterPaneManager(*args, **kwargs):
        """GetCenterPaneManager(self, RheiaManagedFrame parent) -> RheiaCenterPaneManager"""
        return _base.RheiaManager_GetCenterPaneManager(*args, **kwargs)

    def GetMenuManager(*args, **kwargs):
        """GetMenuManager(self, RheiaManagedFrame parent) -> RheiaMenuManager"""
        return _base.RheiaManager_GetMenuManager(*args, **kwargs)

    def GetToolBarManager(*args, **kwargs):
        """GetToolBarManager(self, RheiaManagedFrame parent) -> RheiaToolBarManager"""
        return _base.RheiaManager_GetToolBarManager(*args, **kwargs)

    def GetStatusBarManager(*args, **kwargs):
        """GetStatusBarManager(self, RheiaManagedFrame parent) -> RheiaStatusBarManager"""
        return _base.RheiaManager_GetStatusBarManager(*args, **kwargs)

    def GetProfileManager(*args, **kwargs):
        """GetProfileManager(self) -> RheiaProfileManager"""
        return _base.RheiaManager_GetProfileManager(*args, **kwargs)

    def GetConfigurationManager(*args, **kwargs):
        """GetConfigurationManager(self, String name_space) -> RheiaConfigurationManager"""
        return _base.RheiaManager_GetConfigurationManager(*args, **kwargs)

    def IsAppShuttingDown(*args, **kwargs):
        """IsAppShuttingDown() -> bool"""
        return _base.RheiaManager_IsAppShuttingDown(*args, **kwargs)

    IsAppShuttingDown = staticmethod(IsAppShuttingDown)
    def isappShuttingDown(*args, **kwargs):
        """isappShuttingDown() -> bool"""
        return _base.RheiaManager_isappShuttingDown(*args, **kwargs)

    isappShuttingDown = staticmethod(isappShuttingDown)
    def AddonToolBar(*args, **kwargs):
        """AddonToolBar(ToolBar toolBar, String resid)"""
        return _base.RheiaManager_AddonToolBar(*args, **kwargs)

    AddonToolBar = staticmethod(AddonToolBar)
_base.RheiaManager_swigregister(RheiaManager)

def RheiaManager_Get(*args):
  """RheiaManager_Get() -> RheiaManager"""
  return _base.RheiaManager_Get(*args)

def RheiaManager_Free(*args):
  """RheiaManager_Free()"""
  return _base.RheiaManager_Free(*args)

def RheiaManager_LoadResource(*args, **kwargs):
  """RheiaManager_LoadResource(String file) -> bool"""
  return _base.RheiaManager_LoadResource(*args, **kwargs)

def RheiaManager_IsAppShuttingDown(*args):
  """RheiaManager_IsAppShuttingDown() -> bool"""
  return _base.RheiaManager_IsAppShuttingDown(*args)

def RheiaManager_isappShuttingDown(*args):
  """RheiaManager_isappShuttingDown() -> bool"""
  return _base.RheiaManager_isappShuttingDown(*args)

def RheiaManager_AddonToolBar(*args, **kwargs):
  """RheiaManager_AddonToolBar(ToolBar toolBar, String resid)"""
  return _base.RheiaManager_AddonToolBar(*args, **kwargs)

class RheiaMgrRheiaCenterPaneManager(object):
    """Proxy of C++ RheiaMgrRheiaCenterPaneManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaCenterPaneManager"""
        return _base.RheiaMgrRheiaCenterPaneManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _base.RheiaMgrRheiaCenterPaneManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _base.RheiaMgrRheiaCenterPaneManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaMgrRheiaCenterPaneManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaMgrRheiaCenterPaneManager_swigregister(RheiaMgrRheiaCenterPaneManager)

def RheiaMgrRheiaCenterPaneManager_Get(*args, **kwargs):
  """RheiaMgrRheiaCenterPaneManager_Get(RheiaManagedFrame in) -> RheiaCenterPaneManager"""
  return _base.RheiaMgrRheiaCenterPaneManager_Get(*args, **kwargs)

def RheiaMgrRheiaCenterPaneManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaCenterPaneManager_Exists(RheiaManagedFrame in) -> bool"""
  return _base.RheiaMgrRheiaCenterPaneManager_Exists(*args, **kwargs)

def RheiaMgrRheiaCenterPaneManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaCenterPaneManager_FreeByInstance(RheiaManagedFrame in)"""
  return _base.RheiaMgrRheiaCenterPaneManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaCenterPaneManager_Free(*args):
  """RheiaMgrRheiaCenterPaneManager_Free()"""
  return _base.RheiaMgrRheiaCenterPaneManager_Free(*args)

class RheiaCenterPaneManager(RheiaBookManager,RheiaMgrRheiaCenterPaneManager):
    """Proxy of C++ RheiaCenterPaneManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def OnConfigure(*args, **kwargs):
        """OnConfigure(self, CommandEvent event)"""
        return _base.RheiaCenterPaneManager_OnConfigure(*args, **kwargs)

    def ReloadConfiguration(*args, **kwargs):
        """ReloadConfiguration(self)"""
        return _base.RheiaCenterPaneManager_ReloadConfiguration(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _base.RheiaCenterPaneManager_RegisterEvents(*args, **kwargs)

    def OnConfigChanged(*args, **kwargs):
        """OnConfigChanged(self, CommandEvent event)"""
        return _base.RheiaCenterPaneManager_OnConfigChanged(*args, **kwargs)

_base.RheiaCenterPaneManager_swigregister(RheiaCenterPaneManager)

class RheiaConfigurationDialog(wx._windows.Dialog):
    """Proxy of C++ RheiaConfigurationDialog class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaConfigurationDialog"""
        _base.RheiaConfigurationDialog_swiginit(self,_base.new_RheiaConfigurationDialog(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaConfigurationDialog
    __del__ = lambda self : None;
    def SetConfigurationTool(*args, **kwargs):
        """SetConfigurationTool(self, RheiaConfigurationPanel panel)"""
        return _base.RheiaConfigurationDialog_SetConfigurationTool(*args, **kwargs)

    def Display(*args, **kwargs):
        """Display(self, bool show=True) -> int"""
        return _base.RheiaConfigurationDialog_Display(*args, **kwargs)

    def DisplayModal(*args, **kwargs):
        """DisplayModal(self) -> int"""
        return _base.RheiaConfigurationDialog_DisplayModal(*args, **kwargs)

_base.RheiaConfigurationDialog_swigregister(RheiaConfigurationDialog)

class RheiaConfigurationPageInfo(object):
    """Proxy of C++ RheiaConfigurationPageInfo class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaConfigurationPageInfo"""
        _base.RheiaConfigurationPageInfo_swiginit(self,_base.new_RheiaConfigurationPageInfo(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaConfigurationPageInfo
    __del__ = lambda self : None;
    page = property(_base.RheiaConfigurationPageInfo_page_get, _base.RheiaConfigurationPageInfo_page_set)
    idxOn = property(_base.RheiaConfigurationPageInfo_idxOn_get, _base.RheiaConfigurationPageInfo_idxOn_set)
    idxOff = property(_base.RheiaConfigurationPageInfo_idxOff_get, _base.RheiaConfigurationPageInfo_idxOff_set)
    title = property(_base.RheiaConfigurationPageInfo_title_get, _base.RheiaConfigurationPageInfo_title_set)
_base.RheiaConfigurationPageInfo_swigregister(RheiaConfigurationPageInfo)

def RheiaConfigurationPageInfoCopy(*args, **kwargs):
    """RheiaConfigurationPageInfoCopy(RheiaConfigurationPageInfo rhs) -> RheiaConfigurationPageInfo"""
    val = _base.new_RheiaConfigurationPageInfoCopy(*args, **kwargs)
    return val

class RheiaApplicationConfigurationDialog(wx._windows.Dialog):
    """Proxy of C++ RheiaApplicationConfigurationDialog class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaApplicationConfigurationDialog"""
        _base.RheiaApplicationConfigurationDialog_swiginit(self,_base.new_RheiaApplicationConfigurationDialog(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaApplicationConfigurationDialog
    __del__ = lambda self : None;
    def SetPageSelection(*args, **kwargs):
        """SetPageSelection(self, String page_name)"""
        return _base.RheiaApplicationConfigurationDialog_SetPageSelection(*args, **kwargs)

    def Display(*args, **kwargs):
        """Display(self, bool show=True) -> int"""
        return _base.RheiaApplicationConfigurationDialog_Display(*args, **kwargs)

    def DisplayModal(*args, **kwargs):
        """DisplayModal(self) -> int"""
        return _base.RheiaApplicationConfigurationDialog_DisplayModal(*args, **kwargs)

_base.RheiaApplicationConfigurationDialog_swigregister(RheiaApplicationConfigurationDialog)

class RheiaConfigurationPathsDialog(wx._windows.Dialog):
    """Proxy of C++ RheiaConfigurationPathsDialog class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaConfigurationPathsDialog"""
        _base.RheiaConfigurationPathsDialog_swiginit(self,_base.new_RheiaConfigurationPathsDialog(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaConfigurationPathsDialog
    __del__ = lambda self : None;
    def Display(*args, **kwargs):
        """Display(self, bool show=True) -> int"""
        return _base.RheiaConfigurationPathsDialog_Display(*args, **kwargs)

    def DisplayModal(*args, **kwargs):
        """DisplayModal(self) -> int"""
        return _base.RheiaConfigurationPathsDialog_DisplayModal(*args, **kwargs)

_base.RheiaConfigurationPathsDialog_swigregister(RheiaConfigurationPathsDialog)

class RheiaConfigurationManager(object):
    """Proxy of C++ RheiaConfigurationManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _base.RheiaConfigurationManager_Clear(*args, **kwargs)

    def Delete(*args, **kwargs):
        """Delete(self)"""
        return _base.RheiaConfigurationManager_Delete(*args, **kwargs)

    def DeletePath(*args, **kwargs):
        """DeletePath(self, String path)"""
        return _base.RheiaConfigurationManager_DeletePath(*args, **kwargs)

    def WriteString(*args, **kwargs):
        """WriteString(self, String path, String value, bool ignoreEmpty=False)"""
        return _base.RheiaConfigurationManager_WriteString(*args, **kwargs)

    def ReadString(*args, **kwargs):
        """ReadString(self, String path, String defaultVal=wxEmptyString) -> String"""
        return _base.RheiaConfigurationManager_ReadString(*args, **kwargs)

    def DoReadString(*args, **kwargs):
        """DoReadString(self, String path, String str) -> bool"""
        return _base.RheiaConfigurationManager_DoReadString(*args, **kwargs)

    def WriteChars(*args, **kwargs):
        """WriteChars(self, String path, char str)"""
        return _base.RheiaConfigurationManager_WriteChars(*args, **kwargs)

    def WriteInt(*args, **kwargs):
        """WriteInt(self, String path, int value)"""
        return _base.RheiaConfigurationManager_WriteInt(*args, **kwargs)

    def DoReadInt(*args, **kwargs):
        """DoReadInt(self, String path, int value) -> bool"""
        return _base.RheiaConfigurationManager_DoReadInt(*args, **kwargs)

    def ReadInt(*args, **kwargs):
        """ReadInt(self, String path, int defaultVal=0) -> int"""
        return _base.RheiaConfigurationManager_ReadInt(*args, **kwargs)

    def WriteBool(*args, **kwargs):
        """WriteBool(self, String path, bool value)"""
        return _base.RheiaConfigurationManager_WriteBool(*args, **kwargs)

    def DoReadBool(*args, **kwargs):
        """DoReadBool(self, String path, bool value) -> bool"""
        return _base.RheiaConfigurationManager_DoReadBool(*args, **kwargs)

    def ReadBool(*args, **kwargs):
        """ReadBool(self, String path, bool defaultVal=False) -> bool"""
        return _base.RheiaConfigurationManager_ReadBool(*args, **kwargs)

    def Write(*args, **kwargs):
        """Write(self, String path, double value)"""
        return _base.RheiaConfigurationManager_Write(*args, **kwargs)

    def DoReadDouble(*args, **kwargs):
        """DoReadDouble(self, String path, double value) -> bool"""
        return _base.RheiaConfigurationManager_DoReadDouble(*args, **kwargs)

    def ReadDouble(*args, **kwargs):
        """ReadDouble(self, String path, double defaultVal=0.0f) -> double"""
        return _base.RheiaConfigurationManager_ReadDouble(*args, **kwargs)

    def WriteArrayString(*args, **kwargs):
        """WriteArrayString(self, String path, wxArrayString as)"""
        return _base.RheiaConfigurationManager_WriteArrayString(*args, **kwargs)

    def DoReadArrayString(*args, **kwargs):
        """DoReadArrayString(self, String path, wxArrayString as)"""
        return _base.RheiaConfigurationManager_DoReadArrayString(*args, **kwargs)

    def ReadArrayString(*args, **kwargs):
        """ReadArrayString(self, String path) -> wxArrayString"""
        return _base.RheiaConfigurationManager_ReadArrayString(*args, **kwargs)

    def WriteStringStringMap(*args, **kwargs):
        """WriteStringStringMap(self, String path, RheiaStringStringMap as)"""
        return _base.RheiaConfigurationManager_WriteStringStringMap(*args, **kwargs)

    def DoReadStringStringMap(*args, **kwargs):
        """DoReadStringStringMap(self, String path, RheiaStringStringMap as)"""
        return _base.RheiaConfigurationManager_DoReadStringStringMap(*args, **kwargs)

    def ReadStringStringMap(*args, **kwargs):
        """ReadStringStringMap(self, String path) -> RheiaStringStringMap"""
        return _base.RheiaConfigurationManager_ReadStringStringMap(*args, **kwargs)

    def WriteArrayInt(*args, **kwargs):
        """WriteArrayInt(self, String path, wxArrayInt arrayInt)"""
        return _base.RheiaConfigurationManager_WriteArrayInt(*args, **kwargs)

    def DoReadArrayInt(*args, **kwargs):
        """DoReadArrayInt(self, String path, wxArrayInt arrayInt)"""
        return _base.RheiaConfigurationManager_DoReadArrayInt(*args, **kwargs)

    def ReadArrayInt(*args, **kwargs):
        """ReadArrayInt(self, String path) -> wxArrayInt"""
        return _base.RheiaConfigurationManager_ReadArrayInt(*args, **kwargs)

    def WriteArrayDouble(*args, **kwargs):
        """WriteArrayDouble(self, String path, wxArrayDouble arrayDouble)"""
        return _base.RheiaConfigurationManager_WriteArrayDouble(*args, **kwargs)

    def DoReadArrayDouble(*args, **kwargs):
        """DoReadArrayDouble(self, String path, wxArrayDouble arrayDouble)"""
        return _base.RheiaConfigurationManager_DoReadArrayDouble(*args, **kwargs)

    def ReadArrayDouble(*args, **kwargs):
        """ReadArrayDouble(self, String path) -> wxArrayDouble"""
        return _base.RheiaConfigurationManager_ReadArrayDouble(*args, **kwargs)

    def WriteArrayBool(*args, **kwargs):
        """WriteArrayBool(self, String path, ArrayBool arrayBool)"""
        return _base.RheiaConfigurationManager_WriteArrayBool(*args, **kwargs)

    def DoReadArrayBool(*args, **kwargs):
        """DoReadArrayBool(self, String path, ArrayBool arrayBool)"""
        return _base.RheiaConfigurationManager_DoReadArrayBool(*args, **kwargs)

    def ReadArrayBool(*args, **kwargs):
        """ReadArrayBool(self, String path) -> ArrayBool"""
        return _base.RheiaConfigurationManager_ReadArrayBool(*args, **kwargs)

    def WriteStdArrayString(*args, **kwargs):
        """WriteStdArrayString(self, String path, std::vector<(std::string)> arrayString)"""
        return _base.RheiaConfigurationManager_WriteStdArrayString(*args, **kwargs)

    def DoReadStdArrayString(*args, **kwargs):
        """DoReadStdArrayString(self, String path, std::vector<(std::string)> arrayString)"""
        return _base.RheiaConfigurationManager_DoReadStdArrayString(*args, **kwargs)

    def ReadStdArrayString(*args, **kwargs):
        """ReadStdArrayString(self, String path) -> std::vector<(std::string)>"""
        return _base.RheiaConfigurationManager_ReadStdArrayString(*args, **kwargs)

    def WriteStdArrayInt(*args, **kwargs):
        """WriteStdArrayInt(self, String path, std::vector<(int)> arrayInt)"""
        return _base.RheiaConfigurationManager_WriteStdArrayInt(*args, **kwargs)

    def DoReadStdArrayInt(*args, **kwargs):
        """DoReadStdArrayInt(self, String path, std::vector<(int)> arrayInt)"""
        return _base.RheiaConfigurationManager_DoReadStdArrayInt(*args, **kwargs)

    def ReadStdArrayInt(*args, **kwargs):
        """ReadStdArrayInt(self, String path) -> std::vector<(int)>"""
        return _base.RheiaConfigurationManager_ReadStdArrayInt(*args, **kwargs)

    def WriteStdArrayDouble(*args, **kwargs):
        """WriteStdArrayDouble(self, String path, std::vector<(double)> arrayDouble)"""
        return _base.RheiaConfigurationManager_WriteStdArrayDouble(*args, **kwargs)

    def DoReadStdArrayDouble(*args, **kwargs):
        """DoReadStdArrayDouble(self, String path, std::vector<(double)> arrayDouble)"""
        return _base.RheiaConfigurationManager_DoReadStdArrayDouble(*args, **kwargs)

    def ReadStdArrayDouble(*args, **kwargs):
        """ReadStdArrayDouble(self, String path) -> std::vector<(double)>"""
        return _base.RheiaConfigurationManager_ReadStdArrayDouble(*args, **kwargs)

    def WriteStdArrayBool(*args, **kwargs):
        """WriteStdArrayBool(self, String path, std::vector<(bool)> arrayBool)"""
        return _base.RheiaConfigurationManager_WriteStdArrayBool(*args, **kwargs)

    def DoReadStdArrayBool(*args, **kwargs):
        """DoReadStdArrayBool(self, String path, std::vector<(bool)> arrayBool)"""
        return _base.RheiaConfigurationManager_DoReadStdArrayBool(*args, **kwargs)

    def ReadStdArrayBool(*args, **kwargs):
        """ReadStdArrayBool(self, String path) -> std::vector<(bool)>"""
        return _base.RheiaConfigurationManager_ReadStdArrayBool(*args, **kwargs)

    def WriteColour(*args, **kwargs):
        """WriteColour(self, String path, Colour c)"""
        return _base.RheiaConfigurationManager_WriteColour(*args, **kwargs)

    def DoReadColour(*args, **kwargs):
        """DoReadColour(self, String path, Colour value) -> bool"""
        return _base.RheiaConfigurationManager_DoReadColour(*args, **kwargs)

    def ReadColour(*args, **kwargs):
        """ReadColour(self, String path, Colour defaultVal=*wxBLACK) -> Colour"""
        return _base.RheiaConfigurationManager_ReadColour(*args, **kwargs)

    def WriteFont(*args, **kwargs):
        """WriteFont(self, String name, Font font)"""
        return _base.RheiaConfigurationManager_WriteFont(*args, **kwargs)

    def DoReadFond(*args, **kwargs):
        """DoReadFond(self, String name, Font font) -> bool"""
        return _base.RheiaConfigurationManager_DoReadFond(*args, **kwargs)

    def ReadFont(*args, **kwargs):
        """ReadFont(self, String name) -> Font"""
        return _base.RheiaConfigurationManager_ReadFont(*args, **kwargs)

    def WriteTextAttr(*args, **kwargs):
        """WriteTextAttr(self, String name, wxTextAttr attr)"""
        return _base.RheiaConfigurationManager_WriteTextAttr(*args, **kwargs)

    def DoReadTextAttr(*args, **kwargs):
        """DoReadTextAttr(self, String name, wxTextAttr attr) -> bool"""
        return _base.RheiaConfigurationManager_DoReadTextAttr(*args, **kwargs)

    def ReadTextAttr(*args, **kwargs):
        """ReadTextAttr(self, String name) -> wxTextAttr"""
        return _base.RheiaConfigurationManager_ReadTextAttr(*args, **kwargs)

    def WriteSashSize(*args, **kwargs):
        """WriteSashSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteSashSize(*args, **kwargs)

    def WriteCaptionSize(*args, **kwargs):
        """WriteCaptionSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteCaptionSize(*args, **kwargs)

    def WriteGripperSize(*args, **kwargs):
        """WriteGripperSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteGripperSize(*args, **kwargs)

    def WritePaneBorderSize(*args, **kwargs):
        """WritePaneBorderSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WritePaneBorderSize(*args, **kwargs)

    def WritePaneButtonSize(*args, **kwargs):
        """WritePaneButtonSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WritePaneButtonSize(*args, **kwargs)

    def WriteActiveCaptionColor(*args, **kwargs):
        """WriteActiveCaptionColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteActiveCaptionColor(*args, **kwargs)

    def WriteActiveCaptionGradientColor(*args, **kwargs):
        """WriteActiveCaptionGradientColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteActiveCaptionGradientColor(*args, **kwargs)

    def WriteActiveCaptionTextColor(*args, **kwargs):
        """WriteActiveCaptionTextColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteActiveCaptionTextColor(*args, **kwargs)

    def WriteInactiveCaptionColor(*args, **kwargs):
        """WriteInactiveCaptionColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteInactiveCaptionColor(*args, **kwargs)

    def WriteInactiveCaptionGradientColor(*args, **kwargs):
        """WriteInactiveCaptionGradientColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteInactiveCaptionGradientColor(*args, **kwargs)

    def WriteInactiveCaptionTextColor(*args, **kwargs):
        """WriteInactiveCaptionTextColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteInactiveCaptionTextColor(*args, **kwargs)

    def WriteGripperColor(*args, **kwargs):
        """WriteGripperColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteGripperColor(*args, **kwargs)

    def ReadSashSize(*args, **kwargs):
        """ReadSashSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadSashSize(*args, **kwargs)

    def ReadCaptionSize(*args, **kwargs):
        """ReadCaptionSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadCaptionSize(*args, **kwargs)

    def ReadGripperSize(*args, **kwargs):
        """ReadGripperSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadGripperSize(*args, **kwargs)

    def ReadPaneBorderSize(*args, **kwargs):
        """ReadPaneBorderSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadPaneBorderSize(*args, **kwargs)

    def ReadPaneButtonSize(*args, **kwargs):
        """ReadPaneButtonSize(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadPaneButtonSize(*args, **kwargs)

    def ReadActiveCaptionColor(*args, **kwargs):
        """ReadActiveCaptionColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadActiveCaptionColor(*args, **kwargs)

    def ReadActiveCaptionGradientColor(*args, **kwargs):
        """ReadActiveCaptionGradientColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadActiveCaptionGradientColor(*args, **kwargs)

    def ReadActiveCaptionTextColor(*args, **kwargs):
        """ReadActiveCaptionTextColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadActiveCaptionTextColor(*args, **kwargs)

    def ReadInactiveCaptionColor(*args, **kwargs):
        """ReadInactiveCaptionColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadInactiveCaptionColor(*args, **kwargs)

    def ReadInactiveCaptionGradientColor(*args, **kwargs):
        """ReadInactiveCaptionGradientColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadInactiveCaptionGradientColor(*args, **kwargs)

    def ReadInactiveCaptionTextColor(*args, **kwargs):
        """ReadInactiveCaptionTextColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadInactiveCaptionTextColor(*args, **kwargs)

    def ReadGripperColor(*args, **kwargs):
        """ReadGripperColor(self, String path, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_ReadGripperColor(*args, **kwargs)

    def WritePerspective(*args, **kwargs):
        """
        WritePerspective(self, String path, AuiManager LayoutManager, String pName, 
            bool overwrite_existing)
        """
        return _base.RheiaConfigurationManager_WritePerspective(*args, **kwargs)

    def WritePerspectiveString(*args, **kwargs):
        """WritePerspectiveString(self, String path, String pName, String pValue, bool overwrite_existing)"""
        return _base.RheiaConfigurationManager_WritePerspectiveString(*args, **kwargs)

    def ReadPerspective(*args, **kwargs):
        """ReadPerspective(self, String path, AuiManager LayoutManager, String pName)"""
        return _base.RheiaConfigurationManager_ReadPerspective(*args, **kwargs)

    def WriteLayout(*args, **kwargs):
        """
        WriteLayout(self, String path, AuiManager LayoutManager, wxArrayString LayoutNames, 
            wxArrayString LayoutValues, bool overwrite_existing=True)
        """
        return _base.RheiaConfigurationManager_WriteLayout(*args, **kwargs)

    def ReadLayout(*args, **kwargs):
        """ReadLayout(self, String path, AuiManager LayoutManager, String pName)"""
        return _base.RheiaConfigurationManager_ReadLayout(*args, **kwargs)

    def WriteFrameStatusBar(*args, **kwargs):
        """WriteFrameStatusBar(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_WriteFrameStatusBar(*args, **kwargs)

    def ReadFrameStatusBar(*args, **kwargs):
        """ReadFrameStatusBar(self, String path, bool defaultval=True) -> bool"""
        return _base.RheiaConfigurationManager_ReadFrameStatusBar(*args, **kwargs)

    def WriteFrameFullScreen(*args, **kwargs):
        """WriteFrameFullScreen(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_WriteFrameFullScreen(*args, **kwargs)

    def ReadFrameFullScreen(*args, **kwargs):
        """ReadFrameFullScreen(self, String path, bool defaultval=False) -> bool"""
        return _base.RheiaConfigurationManager_ReadFrameFullScreen(*args, **kwargs)

    def WriteFrameMaximized(*args, **kwargs):
        """WriteFrameMaximized(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_WriteFrameMaximized(*args, **kwargs)

    def ReadFrameMaximized(*args, **kwargs):
        """ReadFrameMaximized(self, String path, bool defaultval=True) -> bool"""
        return _base.RheiaConfigurationManager_ReadFrameMaximized(*args, **kwargs)

    def WriteFramePosition(*args, **kwargs):
        """WriteFramePosition(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_WriteFramePosition(*args, **kwargs)

    def ReadFramePosition(*args, **kwargs):
        """ReadFramePosition(self, String path, Point defaultval=DefaultPosition) -> Point"""
        return _base.RheiaConfigurationManager_ReadFramePosition(*args, **kwargs)

    def ReadFramePositionAndSet(*args, **kwargs):
        """ReadFramePositionAndSet(self, String path, Frame frame, Point defaultval=DefaultPosition)"""
        return _base.RheiaConfigurationManager_ReadFramePositionAndSet(*args, **kwargs)

    def WriteFrameSize(*args, **kwargs):
        """WriteFrameSize(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_WriteFrameSize(*args, **kwargs)

    def ReadFrameSize(*args, **kwargs):
        """ReadFrameSize(self, String path, Size defaultval=DefaultSize) -> Size"""
        return _base.RheiaConfigurationManager_ReadFrameSize(*args, **kwargs)

    def ReadFrameSizeAndSet(*args, **kwargs):
        """ReadFrameSizeAndSet(self, String path, Frame frame, Size defaultval=DefaultSize)"""
        return _base.RheiaConfigurationManager_ReadFrameSizeAndSet(*args, **kwargs)

    def WriteFrameInfo(*args, **kwargs):
        """WriteFrameInfo(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_WriteFrameInfo(*args, **kwargs)

    def ReadFrameInfo(*args, **kwargs):
        """ReadFrameInfo(self, String path, Frame frame)"""
        return _base.RheiaConfigurationManager_ReadFrameInfo(*args, **kwargs)

    def WriteBasicConfiguration(*args, **kwargs):
        """WriteBasicConfiguration(self, Frame main_frame, AuiManager LayoutManager)"""
        return _base.RheiaConfigurationManager_WriteBasicConfiguration(*args, **kwargs)

    def ListRootChildrens(*args, **kwargs):
        """ListRootChildrens(self) -> wxArrayString"""
        return _base.RheiaConfigurationManager_ListRootChildrens(*args, **kwargs)

_base.RheiaConfigurationManager_swigregister(RheiaConfigurationManager)

class RheiaDebug(object):
    """Proxy of C++ RheiaDebug class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Log(*args, **kwargs):
        """Log(String str)"""
        return _base.RheiaDebug_Log(*args, **kwargs)

    Log = staticmethod(Log)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaDebug_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaDebug_swigregister(RheiaDebug)

def RheiaDebug_Log(*args, **kwargs):
  """RheiaDebug_Log(String str)"""
  return _base.RheiaDebug_Log(*args, **kwargs)

def RheiaDebug_Free(*args):
  """RheiaDebug_Free()"""
  return _base.RheiaDebug_Free(*args)

class MgrRheiaEnvironementManager(object):
    """Proxy of C++ MgrRheiaEnvironementManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _base.MgrRheiaEnvironementManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaEnvironementManager"""
        return _base.MgrRheiaEnvironementManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.MgrRheiaEnvironementManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.MgrRheiaEnvironementManager_swigregister(MgrRheiaEnvironementManager)

def MgrRheiaEnvironementManager_Valid(*args):
  """MgrRheiaEnvironementManager_Valid() -> bool"""
  return _base.MgrRheiaEnvironementManager_Valid(*args)

def MgrRheiaEnvironementManager_Get(*args):
  """MgrRheiaEnvironementManager_Get() -> RheiaEnvironementManager"""
  return _base.MgrRheiaEnvironementManager_Get(*args)

def MgrRheiaEnvironementManager_Free(*args):
  """MgrRheiaEnvironementManager_Free()"""
  return _base.MgrRheiaEnvironementManager_Free(*args)

class RheiaEnvironementManager(wx._core.EvtHandler,MgrRheiaEnvironementManager):
    """Proxy of C++ RheiaEnvironementManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, RheiaManagedFrame parent, MenuBar menuBar)"""
        return _base.RheiaEnvironementManager_BuildMenu(*args, **kwargs)

    def ReleaseMenu(*args, **kwargs):
        """ReleaseMenu(self, RheiaManagedFrame parent, MenuBar menuBar)"""
        return _base.RheiaEnvironementManager_ReleaseMenu(*args, **kwargs)

    def OnManageEnvironmentVariables(*args, **kwargs):
        """OnManageEnvironmentVariables(self, CommandEvent event)"""
        return _base.RheiaEnvironementManager_OnManageEnvironmentVariables(*args, **kwargs)

    def Add(*args, **kwargs):
        """Add(self, String name, String value) -> bool"""
        return _base.RheiaEnvironementManager_Add(*args, **kwargs)

    def Change(*args, **kwargs):
        """Change(self, String name, String value) -> bool"""
        return _base.RheiaEnvironementManager_Change(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self, String name) -> bool"""
        return _base.RheiaEnvironementManager_Remove(*args, **kwargs)

    def FindVariableByName(*args, **kwargs):
        """FindVariableByName(self, String name) -> String"""
        return _base.RheiaEnvironementManager_FindVariableByName(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _base.RheiaEnvironementManager_Exists(*args, **kwargs)

    def GetVariables(*args, **kwargs):
        """GetVariables(self) -> RheiaStringStringMap"""
        return _base.RheiaEnvironementManager_GetVariables(*args, **kwargs)

    def Clear(*args, **kwargs):
        """Clear(self)"""
        return _base.RheiaEnvironementManager_Clear(*args, **kwargs)

    def AddPath(*args, **kwargs):
        """AddPath(self, String path) -> bool"""
        return _base.RheiaEnvironementManager_AddPath(*args, **kwargs)

    def RemovePath(*args, **kwargs):
        """RemovePath(self, String path) -> bool"""
        return _base.RheiaEnvironementManager_RemovePath(*args, **kwargs)

    def PathExists(*args, **kwargs):
        """PathExists(self, String path) -> bool"""
        return _base.RheiaEnvironementManager_PathExists(*args, **kwargs)

    def ClearPaths(*args, **kwargs):
        """ClearPaths(self)"""
        return _base.RheiaEnvironementManager_ClearPaths(*args, **kwargs)

    def GetPathsList(*args, **kwargs):
        """GetPathsList(self) -> wxArrayString"""
        return _base.RheiaEnvironementManager_GetPathsList(*args, **kwargs)

    def OnCloseFrame(*args, **kwargs):
        """OnCloseFrame(self, RheiaFrameEvent event)"""
        return _base.RheiaEnvironementManager_OnCloseFrame(*args, **kwargs)

_base.RheiaEnvironementManager_swigregister(RheiaEnvironementManager)

RheiaEVT_APP_STARTUP_DONE = _base.RheiaEVT_APP_STARTUP_DONE
RheiaEVT_APP_START_SHUTDOWN = _base.RheiaEVT_APP_START_SHUTDOWN
RheiaEVT_PACKAGE_INSTALLED = _base.RheiaEVT_PACKAGE_INSTALLED
RheiaEVT_PACKAGE_REMOVED = _base.RheiaEVT_PACKAGE_REMOVED
RheiaEVT_PROFILE_CHANGED = _base.RheiaEVT_PROFILE_CHANGED
RheiaEVT_MENU_CALLBACK_ADDED = _base.RheiaEVT_MENU_CALLBACK_ADDED
RheiaEVT_MENU_CALLBACK_REMOVED = _base.RheiaEVT_MENU_CALLBACK_REMOVED
RheiaEVT_MENU_REBUILT = _base.RheiaEVT_MENU_REBUILT
RheiaEVT_CENTER_PAGE_CHANGED = _base.RheiaEVT_CENTER_PAGE_CHANGED
RheiaEVT_CENTER_PAGE_CHANGING = _base.RheiaEVT_CENTER_PAGE_CHANGING
RheiaEVT_CENTER_PAGE_CLOSED = _base.RheiaEVT_CENTER_PAGE_CLOSED
RheiaEVT_CENTER_PAGE_OPENED = _base.RheiaEVT_CENTER_PAGE_OPENED
RheiaEVT_CENTER_PAGE_DELETED = _base.RheiaEVT_CENTER_PAGE_DELETED
RheiaEVT_CENTER_PAGE_ACTIVATED = _base.RheiaEVT_CENTER_PAGE_ACTIVATED
RheiaEVT_INFOMGR_SETTINGS_CHANGED = _base.RheiaEVT_INFOMGR_SETTINGS_CHANGED
RheiaEVT_LEFTMGR_SETTINGS_CHANGED = _base.RheiaEVT_LEFTMGR_SETTINGS_CHANGED
RheiaEVT_CENTERMGR_SETTINGS_CHANGED = _base.RheiaEVT_CENTERMGR_SETTINGS_CHANGED
RheiaEVT_WKSPMGR_SETTINGS_CHANGED = _base.RheiaEVT_WKSPMGR_SETTINGS_CHANGED
RheiaEVT_LAYOUT_SETTINGS_CHANGED = _base.RheiaEVT_LAYOUT_SETTINGS_CHANGED
RheiaEVT_LOGGER_REMOVED = _base.RheiaEVT_LOGGER_REMOVED
RheiaEVT_LOGGER_SETTINGS = _base.RheiaEVT_LOGGER_SETTINGS
RheiaEVT_TXT_LOGGER_SETTINGS = _base.RheiaEVT_TXT_LOGGER_SETTINGS
RheiaEVT_HTML_LOGGER_SETTINGS = _base.RheiaEVT_HTML_LOGGER_SETTINGS
RheiaEVT_LIST_LOGGER_SETTINGS = _base.RheiaEVT_LIST_LOGGER_SETTINGS
RheiaEVT_FILE_LOGGER_SETTINGS = _base.RheiaEVT_FILE_LOGGER_SETTINGS
RheiaEVT_FRAME_CREATED = _base.RheiaEVT_FRAME_CREATED
RheiaEVT_FRAME_CLOSING = _base.RheiaEVT_FRAME_CLOSING
#
# Create some event binders
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


class RheiaEvent(wx._core.CommandEvent):
    """Proxy of C++ RheiaEvent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, EventType commandType=wxEVT_NULL, int id=0) -> RheiaEvent"""
        _base.RheiaEvent_swiginit(self,_base.new_RheiaEvent(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaEvent
    __del__ = lambda self : None;
    def GetX(*args, **kwargs):
        """GetX(self) -> int"""
        return _base.RheiaEvent_GetX(*args, **kwargs)

    def SetX(*args, **kwargs):
        """SetX(self, int x)"""
        return _base.RheiaEvent_SetX(*args, **kwargs)

    def GetY(*args, **kwargs):
        """GetY(self) -> int"""
        return _base.RheiaEvent_GetY(*args, **kwargs)

    def SetY(*args, **kwargs):
        """SetY(self, int y)"""
        return _base.RheiaEvent_SetY(*args, **kwargs)

_base.RheiaEvent_swigregister(RheiaEvent)

def RheiaEventCopy(*args, **kwargs):
    """RheiaEventCopy(RheiaEvent event) -> RheiaEvent"""
    val = _base.new_RheiaEventCopy(*args, **kwargs)
    return val

class RheiaFrameEvent(RheiaEvent):
    """Proxy of C++ RheiaFrameEvent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, EventType commandType=wxEVT_NULL, int id=0, RheiaManagedFrame frame=0L, 
            String name=wxEmptyString) -> RheiaFrameEvent
        """
        _base.RheiaFrameEvent_swiginit(self,_base.new_RheiaFrameEvent(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaFrameEvent
    __del__ = lambda self : None;
    def GetFrame(*args, **kwargs):
        """GetFrame(self) -> RheiaManagedFrame"""
        return _base.RheiaFrameEvent_GetFrame(*args, **kwargs)

    def SetFrame(*args, **kwargs):
        """SetFrame(self, RheiaManagedFrame frame)"""
        return _base.RheiaFrameEvent_SetFrame(*args, **kwargs)

    def GetFrameName(*args, **kwargs):
        """GetFrameName(self) -> String"""
        return _base.RheiaFrameEvent_GetFrameName(*args, **kwargs)

    def SetFrameName(*args, **kwargs):
        """SetFrameName(self, String name)"""
        return _base.RheiaFrameEvent_SetFrameName(*args, **kwargs)

_base.RheiaFrameEvent_swigregister(RheiaFrameEvent)

def RheiaFrameEventCopy(*args, **kwargs):
    """RheiaFrameEventCopy(RheiaFrameEvent event) -> RheiaFrameEvent"""
    val = _base.new_RheiaFrameEventCopy(*args, **kwargs)
    return val

class MgrRheiaEventsManager(object):
    """Proxy of C++ MgrRheiaEventsManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _base.MgrRheiaEventsManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaEventsManager"""
        return _base.MgrRheiaEventsManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.MgrRheiaEventsManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.MgrRheiaEventsManager_swigregister(MgrRheiaEventsManager)

def MgrRheiaEventsManager_Valid(*args):
  """MgrRheiaEventsManager_Valid() -> bool"""
  return _base.MgrRheiaEventsManager_Valid(*args)

def MgrRheiaEventsManager_Get(*args):
  """MgrRheiaEventsManager_Get() -> RheiaEventsManager"""
  return _base.MgrRheiaEventsManager_Get(*args)

def MgrRheiaEventsManager_Free(*args):
  """MgrRheiaEventsManager_Free()"""
  return _base.MgrRheiaEventsManager_Free(*args)

class RheiaEventsManager(MgrRheiaEventsManager):
    """Proxy of C++ RheiaEventsManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def ProcessEvent(*args, **kwargs):
        """ProcessEvent(self, Event event) -> bool"""
        return _base.RheiaEventsManager_ProcessEvent(*args, **kwargs)

    def RegisterEventMethod(*args, **kwargs):
        """RegisterEventMethod(self, EventType eventType, RheiaEventFunctorBase functor)"""
        return _base.RheiaEventsManager_RegisterEventMethod(*args, **kwargs)

    def RemoveAllEventMethodsFor(*args, **kwargs):
        """RemoveAllEventMethodsFor(self, void owner)"""
        return _base.RheiaEventsManager_RemoveAllEventMethodsFor(*args, **kwargs)

    def RemoveAllEventMethods(*args, **kwargs):
        """RemoveAllEventMethods(self)"""
        return _base.RheiaEventsManager_RemoveAllEventMethods(*args, **kwargs)

_base.RheiaEventsManager_swigregister(RheiaEventsManager)

class RheiaMgrRheiaInfoPaneManager(object):
    """Proxy of C++ RheiaMgrRheiaInfoPaneManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaInfoPaneManager"""
        return _base.RheiaMgrRheiaInfoPaneManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _base.RheiaMgrRheiaInfoPaneManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _base.RheiaMgrRheiaInfoPaneManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaMgrRheiaInfoPaneManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaMgrRheiaInfoPaneManager_swigregister(RheiaMgrRheiaInfoPaneManager)

def RheiaMgrRheiaInfoPaneManager_Get(*args, **kwargs):
  """RheiaMgrRheiaInfoPaneManager_Get(RheiaManagedFrame in) -> RheiaInfoPaneManager"""
  return _base.RheiaMgrRheiaInfoPaneManager_Get(*args, **kwargs)

def RheiaMgrRheiaInfoPaneManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaInfoPaneManager_Exists(RheiaManagedFrame in) -> bool"""
  return _base.RheiaMgrRheiaInfoPaneManager_Exists(*args, **kwargs)

def RheiaMgrRheiaInfoPaneManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaInfoPaneManager_FreeByInstance(RheiaManagedFrame in)"""
  return _base.RheiaMgrRheiaInfoPaneManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaInfoPaneManager_Free(*args):
  """RheiaMgrRheiaInfoPaneManager_Free()"""
  return _base.RheiaMgrRheiaInfoPaneManager_Free(*args)

class RheiaInfoPaneManager(RheiaBookManager,RheiaMgrRheiaInfoPaneManager):
    """Proxy of C++ RheiaInfoPaneManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def ReloadConfiguration(*args, **kwargs):
        """ReloadConfiguration(self)"""
        return _base.RheiaInfoPaneManager_ReloadConfiguration(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _base.RheiaInfoPaneManager_RegisterEvents(*args, **kwargs)

    def OnConfigChanged(*args, **kwargs):
        """OnConfigChanged(self, CommandEvent event)"""
        return _base.RheiaInfoPaneManager_OnConfigChanged(*args, **kwargs)

    def OnConfigureInfoWindow(*args, **kwargs):
        """OnConfigureInfoWindow(self, CommandEvent event)"""
        return _base.RheiaInfoPaneManager_OnConfigureInfoWindow(*args, **kwargs)

    def DoPageClose(*args, **kwargs):
        """DoPageClose(self, String name)"""
        return _base.RheiaInfoPaneManager_DoPageClose(*args, **kwargs)

    def ActivatePage(*args, **kwargs):
        """ActivatePage(self, String name) -> bool"""
        return _base.RheiaInfoPaneManager_ActivatePage(*args, **kwargs)

_base.RheiaInfoPaneManager_swigregister(RheiaInfoPaneManager)

class RheiaMgrRheiaLeftPaneManager(object):
    """Proxy of C++ RheiaMgrRheiaLeftPaneManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaLeftPaneManager"""
        return _base.RheiaMgrRheiaLeftPaneManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _base.RheiaMgrRheiaLeftPaneManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _base.RheiaMgrRheiaLeftPaneManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaMgrRheiaLeftPaneManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaMgrRheiaLeftPaneManager_swigregister(RheiaMgrRheiaLeftPaneManager)

def RheiaMgrRheiaLeftPaneManager_Get(*args, **kwargs):
  """RheiaMgrRheiaLeftPaneManager_Get(RheiaManagedFrame in) -> RheiaLeftPaneManager"""
  return _base.RheiaMgrRheiaLeftPaneManager_Get(*args, **kwargs)

def RheiaMgrRheiaLeftPaneManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaLeftPaneManager_Exists(RheiaManagedFrame in) -> bool"""
  return _base.RheiaMgrRheiaLeftPaneManager_Exists(*args, **kwargs)

def RheiaMgrRheiaLeftPaneManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaLeftPaneManager_FreeByInstance(RheiaManagedFrame in)"""
  return _base.RheiaMgrRheiaLeftPaneManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaLeftPaneManager_Free(*args):
  """RheiaMgrRheiaLeftPaneManager_Free()"""
  return _base.RheiaMgrRheiaLeftPaneManager_Free(*args)

class RheiaLeftPaneManager(RheiaBookManager,RheiaMgrRheiaLeftPaneManager):
    """Proxy of C++ RheiaLeftPaneManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def OnConfigure(*args, **kwargs):
        """OnConfigure(self, CommandEvent event)"""
        return _base.RheiaLeftPaneManager_OnConfigure(*args, **kwargs)

    def ReloadConfiguration(*args, **kwargs):
        """ReloadConfiguration(self)"""
        return _base.RheiaLeftPaneManager_ReloadConfiguration(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _base.RheiaLeftPaneManager_RegisterEvents(*args, **kwargs)

    def OnConfigChanged(*args, **kwargs):
        """OnConfigChanged(self, CommandEvent event)"""
        return _base.RheiaLeftPaneManager_OnConfigChanged(*args, **kwargs)

    def DoPageClose(*args, **kwargs):
        """DoPageClose(self, String name)"""
        return _base.RheiaLeftPaneManager_DoPageClose(*args, **kwargs)

    def ActivatePage(*args, **kwargs):
        """ActivatePage(self, String name) -> bool"""
        return _base.RheiaLeftPaneManager_ActivatePage(*args, **kwargs)

_base.RheiaLeftPaneManager_swigregister(RheiaLeftPaneManager)

class RheiaManagedFrame(wx._windows.Frame):
    """Proxy of C++ RheiaManagedFrame class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, Window parent, int id, String title, Point pos=DefaultPosition, 
            Size size=DefaultSize, long style=wxDEFAULT_FRAME_STYLE|wxSUNKEN_BORDER) -> RheiaManagedFrame
        """
        
	if len(args) == 6:
		wx.Frame.__init__(self,args[0],args[1],args[2],args[3],args[4],args[5]);
	elif len(args) == 5:
		wx.Frame.__init__(self,args[0],args[1],args[2],args[3],args[4],wx.DEFAULT_FRAME_STYLE | wx.SUNKEN_BORDER);
	elif len(args) == 4:
		wx.Frame.__init__(self,args[0],args[1],args[2],args[3],wx.DefaultSize,wx.DEFAULT_FRAME_STYLE | wx.SUNKEN_BORDER);
	else:
		wx.Frame.__init__(self,args[0],args[1],args[2],wx.DefaultPosition,wx.DefaultSize,wx.DEFAULT_FRAME_STYLE | wx.SUNKEN_BORDER);

        _base.RheiaManagedFrame_swiginit(self,_base.new_RheiaManagedFrame(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaManagedFrame
    __del__ = lambda self : None;
    def BuildStatusBar(*args, **kwargs):
        """BuildStatusBar(self)"""
        return _base.RheiaManagedFrame_BuildStatusBar(*args, **kwargs)

    def BuildMenu(*args, **kwargs):
        """BuildMenu(self)"""
        return _base.RheiaManagedFrame_BuildMenu(*args, **kwargs)

    def BuildAui(*args, **kwargs):
        """BuildAui(self)"""
        return _base.RheiaManagedFrame_BuildAui(*args, **kwargs)

    def GetLayoutManager(*args, **kwargs):
        """GetLayoutManager(self) -> AuiManager"""
        return _base.RheiaManagedFrame_GetLayoutManager(*args, **kwargs)

    def IsFrameClosing(*args, **kwargs):
        """IsFrameClosing(self) -> bool"""
        return _base.RheiaManagedFrame_IsFrameClosing(*args, **kwargs)

    def OnExitApp(*args, **kwargs):
        """OnExitApp(self, CloseEvent event)"""
        return _base.RheiaManagedFrame_OnExitApp(*args, **kwargs)

    def OnFileExit(*args, **kwargs):
        """OnFileExit(self, CommandEvent event)"""
        return _base.RheiaManagedFrame_OnFileExit(*args, **kwargs)

    def OnFileClose(*args, **kwargs):
        """OnFileClose(self, CommandEvent event)"""
        return _base.RheiaManagedFrame_OnFileClose(*args, **kwargs)

    def OnAboutRheia(*args, **kwargs):
        """OnAboutRheia(self, CommandEvent event)"""
        return _base.RheiaManagedFrame_OnAboutRheia(*args, **kwargs)

    def OnBuildAui(*args, **kwargs):
        """OnBuildAui(self)"""
        return _base.RheiaManagedFrame_OnBuildAui(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _base.RheiaManagedFrame_RegisterEvents(*args, **kwargs)

    def LoadLayout(*args, **kwargs):
        """LoadLayout(self)"""
        return _base.RheiaManagedFrame_LoadLayout(*args, **kwargs)

    def GetMenuBar(*args, **kwargs):
        """GetMenuBar(self) -> MenuBar"""
        return _base.RheiaManagedFrame_GetMenuBar(*args, **kwargs)

    def CanClose(*args, **kwargs):
        """CanClose(self) -> bool"""
        return _base.RheiaManagedFrame_CanClose(*args, **kwargs)

    def SetCanClose(*args, **kwargs):
        """SetCanClose(self, bool value=False)"""
        return _base.RheiaManagedFrame_SetCanClose(*args, **kwargs)

    def OnToggleStatusBar(*args, **kwargs):
        """OnToggleStatusBar(self, CommandEvent event)"""
        return _base.RheiaManagedFrame_OnToggleStatusBar(*args, **kwargs)

    def OnToggleFullScreen(*args, **kwargs):
        """OnToggleFullScreen(self, CommandEvent event)"""
        return _base.RheiaManagedFrame_OnToggleFullScreen(*args, **kwargs)

    def OnViewMenuUpdateUI(*args, **kwargs):
        """OnViewMenuUpdateUI(self, UpdateUIEvent event)"""
        return _base.RheiaManagedFrame_OnViewMenuUpdateUI(*args, **kwargs)

_base.RheiaManagedFrame_swigregister(RheiaManagedFrame)

def PreRheiaManagedFrame(*args, **kwargs):
    """PreRheiaManagedFrame() -> RheiaManagedFrame"""
    val = _base.new_PreRheiaManagedFrame(*args, **kwargs)
    return val

class RheiaMgrRheiaMenuManager(object):
    """Proxy of C++ RheiaMgrRheiaMenuManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaMenuManager"""
        return _base.RheiaMgrRheiaMenuManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _base.RheiaMgrRheiaMenuManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _base.RheiaMgrRheiaMenuManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaMgrRheiaMenuManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaMgrRheiaMenuManager_swigregister(RheiaMgrRheiaMenuManager)

def RheiaMgrRheiaMenuManager_Get(*args, **kwargs):
  """RheiaMgrRheiaMenuManager_Get(RheiaManagedFrame in) -> RheiaMenuManager"""
  return _base.RheiaMgrRheiaMenuManager_Get(*args, **kwargs)

def RheiaMgrRheiaMenuManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaMenuManager_Exists(RheiaManagedFrame in) -> bool"""
  return _base.RheiaMgrRheiaMenuManager_Exists(*args, **kwargs)

def RheiaMgrRheiaMenuManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaMenuManager_FreeByInstance(RheiaManagedFrame in)"""
  return _base.RheiaMgrRheiaMenuManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaMenuManager_Free(*args):
  """RheiaMgrRheiaMenuManager_Free()"""
  return _base.RheiaMgrRheiaMenuManager_Free(*args)

class RheiaMenuManager(wx._core.EvtHandler,RheiaMgrRheiaMenuManager):
    """Proxy of C++ RheiaMenuManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetMainMenuBar(*args, **kwargs):
        """GetMainMenuBar(self) -> MenuBar"""
        return _base.RheiaMenuManager_GetMainMenuBar(*args, **kwargs)

_base.RheiaMenuManager_swigregister(RheiaMenuManager)

class RheiaPageContainer(utils.RheiaObjectWithBitmap):
    """Proxy of C++ RheiaPageContainer class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def BuildMainWindow(*args, **kwargs):
        """BuildMainWindow(self, Window parent) -> RheiaBookPage"""
        return _base.RheiaPageContainer_BuildMainWindow(*args, **kwargs)

    def OnPageClosed(*args, **kwargs):
        """OnPageClosed(self) -> bool"""
        return _base.RheiaPageContainer_OnPageClosed(*args, **kwargs)

_base.RheiaPageContainer_swigregister(RheiaPageContainer)

class MgrRheiaPersonalityManager(object):
    """Proxy of C++ MgrRheiaPersonalityManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _base.MgrRheiaPersonalityManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaPersonalityManager"""
        return _base.MgrRheiaPersonalityManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.MgrRheiaPersonalityManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.MgrRheiaPersonalityManager_swigregister(MgrRheiaPersonalityManager)

def MgrRheiaPersonalityManager_Valid(*args):
  """MgrRheiaPersonalityManager_Valid() -> bool"""
  return _base.MgrRheiaPersonalityManager_Valid(*args)

def MgrRheiaPersonalityManager_Get(*args):
  """MgrRheiaPersonalityManager_Get() -> RheiaPersonalityManager"""
  return _base.MgrRheiaPersonalityManager_Get(*args)

def MgrRheiaPersonalityManager_Free(*args):
  """MgrRheiaPersonalityManager_Free()"""
  return _base.MgrRheiaPersonalityManager_Free(*args)

class RheiaPersonalityManager(MgrRheiaPersonalityManager):
    """Proxy of C++ RheiaPersonalityManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def SetPersonality(*args, **kwargs):
        """SetPersonality(self, String personality, bool createIfNotExist=False)"""
        return _base.RheiaPersonalityManager_SetPersonality(*args, **kwargs)

    def GetPersonality(*args, **kwargs):
        """GetPersonality(self) -> String"""
        return _base.RheiaPersonalityManager_GetPersonality(*args, **kwargs)

    def GetPersonalitiesList(*args, **kwargs):
        """GetPersonalitiesList(self) -> wxArrayString"""
        return _base.RheiaPersonalityManager_GetPersonalitiesList(*args, **kwargs)

_base.RheiaPersonalityManager_swigregister(RheiaPersonalityManager)

class MgrRheiaProfileManager(object):
    """Proxy of C++ MgrRheiaProfileManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _base.MgrRheiaProfileManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaProfileManager"""
        return _base.MgrRheiaProfileManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.MgrRheiaProfileManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.MgrRheiaProfileManager_swigregister(MgrRheiaProfileManager)

def MgrRheiaProfileManager_Valid(*args):
  """MgrRheiaProfileManager_Valid() -> bool"""
  return _base.MgrRheiaProfileManager_Valid(*args)

def MgrRheiaProfileManager_Get(*args):
  """MgrRheiaProfileManager_Get() -> RheiaProfileManager"""
  return _base.MgrRheiaProfileManager_Get(*args)

def MgrRheiaProfileManager_Free(*args):
  """MgrRheiaProfileManager_Free()"""
  return _base.MgrRheiaProfileManager_Free(*args)

class RheiaProfileManager(wx._core.EvtHandler,MgrRheiaProfileManager):
    """Proxy of C++ RheiaProfileManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetActiveProfile(*args, **kwargs):
        """GetActiveProfile(self) -> String"""
        return _base.RheiaProfileManager_GetActiveProfile(*args, **kwargs)

    def GetActiveProfileManager(*args, **kwargs):
        """GetActiveProfileManager(self) -> RheiaConfigurationManager"""
        return _base.RheiaProfileManager_GetActiveProfileManager(*args, **kwargs)

    def GetProfileManager(*args, **kwargs):
        """GetProfileManager(self, String profile) -> RheiaConfigurationManager"""
        return _base.RheiaProfileManager_GetProfileManager(*args, **kwargs)

    def ChangeActiveProfile(*args, **kwargs):
        """ChangeActiveProfile(self, String profile)"""
        return _base.RheiaProfileManager_ChangeActiveProfile(*args, **kwargs)

    def GetAvailableProfiles(*args, **kwargs):
        """GetAvailableProfiles(self) -> wxArrayString"""
        return _base.RheiaProfileManager_GetAvailableProfiles(*args, **kwargs)

_base.RheiaProfileManager_swigregister(RheiaProfileManager)

class RheiaSplashScreen(wx._windows.SplashScreen):
    """Proxy of C++ RheiaSplashScreen class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, Bitmap label, long flags=wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, 
            long time_out=6000, Window parent=None, 
            int id=ID_ANY, Point pos=DefaultPosition, 
            Size size=DefaultSize, long style=wxSIMPLE_BORDER|wxSTAY_ON_TOP) -> RheiaSplashScreen
        """
        _base.RheiaSplashScreen_swiginit(self,_base.new_RheiaSplashScreen(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaSplashScreen
    __del__ = lambda self : None;
_base.RheiaSplashScreen_swigregister(RheiaSplashScreen)

class RheiaStartPageContainer(wx._core.EvtHandler,RheiaPageContainer):
    """Proxy of C++ RheiaStartPageContainer class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaManagedFrame parent, String file=wxEmptyString) -> RheiaStartPageContainer"""
        _base.RheiaStartPageContainer_swiginit(self,_base.new_RheiaStartPageContainer(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaStartPageContainer
    __del__ = lambda self : None;
    def GetHtmlFile(*args, **kwargs):
        """GetHtmlFile(self) -> String"""
        return _base.RheiaStartPageContainer_GetHtmlFile(*args, **kwargs)

    def SetHtmlFile(*args, **kwargs):
        """SetHtmlFile(self, String file)"""
        return _base.RheiaStartPageContainer_SetHtmlFile(*args, **kwargs)

    def OnCloseParent(*args, **kwargs):
        """OnCloseParent(self, RheiaFrameEvent event)"""
        return _base.RheiaStartPageContainer_OnCloseParent(*args, **kwargs)

_base.RheiaStartPageContainer_swigregister(RheiaStartPageContainer)

class RheiaStartPage(RheiaBookPage):
    """Proxy of C++ RheiaStartPage class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent, String file) -> RheiaStartPage"""
        _base.RheiaStartPage_swiginit(self,_base.new_RheiaStartPage(*args, **kwargs))
    def DoBuildStartPage(*args, **kwargs):
        """DoBuildStartPage(self)"""
        return _base.RheiaStartPage_DoBuildStartPage(*args, **kwargs)

    def OnOpenURI(*args, **kwargs):
        """OnOpenURI(self, WebEvent event)"""
        return _base.RheiaStartPage_OnOpenURI(*args, **kwargs)

_base.RheiaStartPage_swigregister(RheiaStartPage)

class RheiaMgrRheiaStatusBarManager(object):
    """Proxy of C++ RheiaMgrRheiaStatusBarManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaStatusBarManager"""
        return _base.RheiaMgrRheiaStatusBarManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _base.RheiaMgrRheiaStatusBarManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _base.RheiaMgrRheiaStatusBarManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaMgrRheiaStatusBarManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaMgrRheiaStatusBarManager_swigregister(RheiaMgrRheiaStatusBarManager)

def RheiaMgrRheiaStatusBarManager_Get(*args, **kwargs):
  """RheiaMgrRheiaStatusBarManager_Get(RheiaManagedFrame in) -> RheiaStatusBarManager"""
  return _base.RheiaMgrRheiaStatusBarManager_Get(*args, **kwargs)

def RheiaMgrRheiaStatusBarManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaStatusBarManager_Exists(RheiaManagedFrame in) -> bool"""
  return _base.RheiaMgrRheiaStatusBarManager_Exists(*args, **kwargs)

def RheiaMgrRheiaStatusBarManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaStatusBarManager_FreeByInstance(RheiaManagedFrame in)"""
  return _base.RheiaMgrRheiaStatusBarManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaStatusBarManager_Free(*args):
  """RheiaMgrRheiaStatusBarManager_Free()"""
  return _base.RheiaMgrRheiaStatusBarManager_Free(*args)

class RheiaStatusBarManager(wx._core.EvtHandler,RheiaMgrRheiaStatusBarManager):
    """Proxy of C++ RheiaStatusBarManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaManagedFrame parent) -> RheiaStatusBarManager"""
        _base.RheiaStatusBarManager_swiginit(self,_base.new_RheiaStatusBarManager(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaStatusBarManager
    __del__ = lambda self : None;
    def SetWorkspace(*args, **kwargs):
        """SetWorkspace(self, String workspace)"""
        return _base.RheiaStatusBarManager_SetWorkspace(*args, **kwargs)

    def SetProject(*args, **kwargs):
        """SetProject(self, String project)"""
        return _base.RheiaStatusBarManager_SetProject(*args, **kwargs)

    def Update(*args, **kwargs):
        """Update(self)"""
        return _base.RheiaStatusBarManager_Update(*args, **kwargs)

    def GetProject(*args, **kwargs):
        """GetProject(self) -> String"""
        return _base.RheiaStatusBarManager_GetProject(*args, **kwargs)

_base.RheiaStatusBarManager_swigregister(RheiaStatusBarManager)

class RheiaMgrRheiaToolBarManager(object):
    """Proxy of C++ RheiaMgrRheiaToolBarManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaToolBarManager"""
        return _base.RheiaMgrRheiaToolBarManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _base.RheiaMgrRheiaToolBarManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _base.RheiaMgrRheiaToolBarManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.RheiaMgrRheiaToolBarManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.RheiaMgrRheiaToolBarManager_swigregister(RheiaMgrRheiaToolBarManager)

def RheiaMgrRheiaToolBarManager_Get(*args, **kwargs):
  """RheiaMgrRheiaToolBarManager_Get(RheiaManagedFrame in) -> RheiaToolBarManager"""
  return _base.RheiaMgrRheiaToolBarManager_Get(*args, **kwargs)

def RheiaMgrRheiaToolBarManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaToolBarManager_Exists(RheiaManagedFrame in) -> bool"""
  return _base.RheiaMgrRheiaToolBarManager_Exists(*args, **kwargs)

def RheiaMgrRheiaToolBarManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaToolBarManager_FreeByInstance(RheiaManagedFrame in)"""
  return _base.RheiaMgrRheiaToolBarManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaToolBarManager_Free(*args):
  """RheiaMgrRheiaToolBarManager_Free()"""
  return _base.RheiaMgrRheiaToolBarManager_Free(*args)

class RheiaToolBarManager(wx._core.EvtHandler,RheiaMgrRheiaToolBarManager):
    """Proxy of C++ RheiaToolBarManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaManagedFrame parent) -> RheiaToolBarManager"""
        _base.RheiaToolBarManager_swiginit(self,_base.new_RheiaToolBarManager(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaToolBarManager
    __del__ = lambda self : None;
    def GetToolBar(*args, **kwargs):
        """GetToolBar(self) -> ToolBar"""
        return _base.RheiaToolBarManager_GetToolBar(*args, **kwargs)

    def AddToolBar(*args, **kwargs):
        """AddToolBar(self, String name, ToolBar toolbar)"""
        return _base.RheiaToolBarManager_AddToolBar(*args, **kwargs)

    def RemoveToolBar(*args, **kwargs):
        """RemoveToolBar(self, String name)"""
        return _base.RheiaToolBarManager_RemoveToolBar(*args, **kwargs)

    def GetToolBars(*args, **kwargs):
        """GetToolBars(self) -> ToolBarArray"""
        return _base.RheiaToolBarManager_GetToolBars(*args, **kwargs)

    def OnCloseParent(*args, **kwargs):
        """OnCloseParent(self, RheiaFrameEvent event)"""
        return _base.RheiaToolBarManager_OnCloseParent(*args, **kwargs)

_base.RheiaToolBarManager_swigregister(RheiaToolBarManager)

class RheiaTreeItem(wx._core.EvtHandler,utils.RheiaObjectWithBitmap):
    """Proxy of C++ RheiaTreeItem class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _base.delete_RheiaTreeItem
    __del__ = lambda self : None;
    def Clone(*args, **kwargs):
        """Clone(self) -> RheiaTreeItem"""
        return _base.RheiaTreeItem_Clone(*args, **kwargs)

    def GetRoot(*args, **kwargs):
        """GetRoot(self) -> TreeItemId"""
        return _base.RheiaTreeItem_GetRoot(*args, **kwargs)

    def CopyTo(*args, **kwargs):
        """CopyTo(self, TreeCtrl tree, TreeItemId root, int bmpSize, bool moveTo=True) -> bool"""
        return _base.RheiaTreeItem_CopyTo(*args, **kwargs)

    def RemoveAll(*args, **kwargs):
        """RemoveAll(self)"""
        return _base.RheiaTreeItem_RemoveAll(*args, **kwargs)

    def CreateTree(*args, **kwargs):
        """CreateTree(self, TreeCtrl tree, TreeItemId root, int bmpSize)"""
        return _base.RheiaTreeItem_CreateTree(*args, **kwargs)

    def UpdateTree(*args, **kwargs):
        """UpdateTree(self, TreeCtrl tree, int bmpSize)"""
        return _base.RheiaTreeItem_UpdateTree(*args, **kwargs)

    def SetFlags(*args, **kwargs):
        """SetFlags(self, int flags)"""
        return _base.RheiaTreeItem_SetFlags(*args, **kwargs)

    def OnItemSelected(*args, **kwargs):
        """OnItemSelected(self)"""
        return _base.RheiaTreeItem_OnItemSelected(*args, **kwargs)

    def OnItemActivated(*args, **kwargs):
        """OnItemActivated(self)"""
        return _base.RheiaTreeItem_OnItemActivated(*args, **kwargs)

    def OnItemRightClick(*args, **kwargs):
        """OnItemRightClick(self)"""
        return _base.RheiaTreeItem_OnItemRightClick(*args, **kwargs)

    def OnRequestContextMenu(*args, **kwargs):
        """OnRequestContextMenu(self, Menu ?)"""
        return _base.RheiaTreeItem_OnRequestContextMenu(*args, **kwargs)

    def OnPreDelete(*args, **kwargs):
        """OnPreDelete(self)"""
        return _base.RheiaTreeItem_OnPreDelete(*args, **kwargs)

    def OnBeginDrag(*args, **kwargs):
        """OnBeginDrag(self) -> bool"""
        return _base.RheiaTreeItem_OnBeginDrag(*args, **kwargs)

    def OnEndDrag(*args, **kwargs):
        """OnEndDrag(self) -> bool"""
        return _base.RheiaTreeItem_OnEndDrag(*args, **kwargs)

    def GetModified(*args, **kwargs):
        """GetModified(self) -> bool"""
        return _base.RheiaTreeItem_GetModified(*args, **kwargs)

    def SetModified(*args, **kwargs):
        """SetModified(self, bool value=True, bool recursive=False)"""
        return _base.RheiaTreeItem_SetModified(*args, **kwargs)

    def Add(*args, **kwargs):
        """Add(self, String name, RheiaTreeItem item) -> bool"""
        return _base.RheiaTreeItem_Add(*args, **kwargs)

    def Remove(*args, **kwargs):
        """Remove(self, String name) -> bool"""
        return _base.RheiaTreeItem_Remove(*args, **kwargs)

    def RemoveItem(*args, **kwargs):
        """RemoveItem(self, RheiaTreeItem item) -> bool"""
        return _base.RheiaTreeItem_RemoveItem(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _base.RheiaTreeItem_Exists(*args, **kwargs)

    def ItemExists(*args, **kwargs):
        """ItemExists(self, RheiaTreeItem item) -> bool"""
        return _base.RheiaTreeItem_ItemExists(*args, **kwargs)

    def Find(*args, **kwargs):
        """Find(self, String name, bool recursive=True) -> RheiaTreeItem"""
        return _base.RheiaTreeItem_Find(*args, **kwargs)

    def GetItemName(*args, **kwargs):
        """GetItemName(self, RheiaTreeItem item, bool recursive=True) -> String"""
        return _base.RheiaTreeItem_GetItemName(*args, **kwargs)

    def GetItems(*args, **kwargs):
        """GetItems(self) -> RheiaTreeItemMap"""
        return _base.RheiaTreeItem_GetItems(*args, **kwargs)

_base.RheiaTreeItem_swigregister(RheiaTreeItem)
cvar = _base.cvar
rhTREE_DELETE_ON_DESTROY = cvar.rhTREE_DELETE_ON_DESTROY
rhTREE_CLEAR_ON_DESTROY = cvar.rhTREE_CLEAR_ON_DESTROY
rhTREE_DEFAULT = cvar.rhTREE_DEFAULT

class RheiaTreeItemData(wx._core.Object):
    """Proxy of C++ RheiaTreeItemData class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaTreeItem item=0L) -> RheiaTreeItemData"""
        _base.RheiaTreeItemData_swiginit(self,_base.new_RheiaTreeItemData(*args, **kwargs))
    __swig_destroy__ = _base.delete_RheiaTreeItemData
    __del__ = lambda self : None;
    def GetOwner(*args, **kwargs):
        """GetOwner(self) -> RheiaTreeItem"""
        return _base.RheiaTreeItemData_GetOwner(*args, **kwargs)

    def SetOwner(*args, **kwargs):
        """SetOwner(self, RheiaTreeItem owner)"""
        return _base.RheiaTreeItemData_SetOwner(*args, **kwargs)

_base.RheiaTreeItemData_swigregister(RheiaTreeItemData)

class MgrRheiaXulManager(object):
    """Proxy of C++ MgrRheiaXulManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _base.MgrRheiaXulManager_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaXulManager"""
        return _base.MgrRheiaXulManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _base.MgrRheiaXulManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_base.MgrRheiaXulManager_swigregister(MgrRheiaXulManager)

def MgrRheiaXulManager_Valid(*args):
  """MgrRheiaXulManager_Valid() -> bool"""
  return _base.MgrRheiaXulManager_Valid(*args)

def MgrRheiaXulManager_Get(*args):
  """MgrRheiaXulManager_Get() -> RheiaXulManager"""
  return _base.MgrRheiaXulManager_Get(*args)

def MgrRheiaXulManager_Free(*args):
  """MgrRheiaXulManager_Free()"""
  return _base.MgrRheiaXulManager_Free(*args)

class RheiaXulManager(MgrRheiaXulManager):
    """Proxy of C++ RheiaXulManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Init(*args, **kwargs):
        """Init(self, String path)"""
        return _base.RheiaXulManager_Init(*args, **kwargs)

    def AddPluginPath(*args, **kwargs):
        """AddPluginPath(self, String path)"""
        return _base.RheiaXulManager_AddPluginPath(*args, **kwargs)

    def FindXulRunner(*args, **kwargs):
        """FindXulRunner(self, String xulrunner_dirname) -> String"""
        return _base.RheiaXulManager_FindXulRunner(*args, **kwargs)

    def IsRunning(*args, **kwargs):
        """IsRunning(self) -> bool"""
        return _base.RheiaXulManager_IsRunning(*args, **kwargs)

_base.RheiaXulManager_swigregister(RheiaXulManager)



