# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.

import _workspacemgt
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
    __swig_destroy__ = _workspacemgt.delete_PySwigIterator
    __del__ = lambda self : None;
    def value(*args): return _workspacemgt.PySwigIterator_value(*args)
    def incr(*args): return _workspacemgt.PySwigIterator_incr(*args)
    def decr(*args): return _workspacemgt.PySwigIterator_decr(*args)
    def distance(*args): return _workspacemgt.PySwigIterator_distance(*args)
    def equal(*args): return _workspacemgt.PySwigIterator_equal(*args)
    def copy(*args): return _workspacemgt.PySwigIterator_copy(*args)
    def next(*args): return _workspacemgt.PySwigIterator_next(*args)
    def previous(*args): return _workspacemgt.PySwigIterator_previous(*args)
    def advance(*args): return _workspacemgt.PySwigIterator_advance(*args)
    def __eq__(*args): return _workspacemgt.PySwigIterator___eq__(*args)
    def __ne__(*args): return _workspacemgt.PySwigIterator___ne__(*args)
    def __iadd__(*args): return _workspacemgt.PySwigIterator___iadd__(*args)
    def __isub__(*args): return _workspacemgt.PySwigIterator___isub__(*args)
    def __add__(*args): return _workspacemgt.PySwigIterator___add__(*args)
    def __sub__(*args): return _workspacemgt.PySwigIterator___sub__(*args)
    def __iter__(self): return self
_workspacemgt.PySwigIterator_swigregister(PySwigIterator)

import wx._core
import wx._windows
import wx.wizard
import utils
import loggers
import base
import packagemgt
RheiaEVT_PROJECT_CREATED = _workspacemgt.RheiaEVT_PROJECT_CREATED
RheiaEVT_PROJECT_OPENED = _workspacemgt.RheiaEVT_PROJECT_OPENED
RheiaEVT_PROJECT_CLOSING = _workspacemgt.RheiaEVT_PROJECT_CLOSING
RheiaEVT_PROJECT_CLOSED = _workspacemgt.RheiaEVT_PROJECT_CLOSED
RheiaEVT_PROJECT_ACTIVATED = _workspacemgt.RheiaEVT_PROJECT_ACTIVATED
RheiaEVT_PROJECT_SELECTED = _workspacemgt.RheiaEVT_PROJECT_SELECTED
RheiaEVT_PROJECT_RENAMED = _workspacemgt.RheiaEVT_PROJECT_RENAMED
RheiaEVT_PROJECT_SAVING = _workspacemgt.RheiaEVT_PROJECT_SAVING
RheiaEVT_PROJECT_SAVED = _workspacemgt.RheiaEVT_PROJECT_SAVED
RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS = _workspacemgt.RheiaEVT_PROJECT_BEGIN_ADD_ELEMENTS
RheiaEVT_PROJECT_END_ADD_ELEMENTS = _workspacemgt.RheiaEVT_PROJECT_END_ADD_ELEMENTS
RheiaEVT_PROJECT_BEGIN_REMOVE_ELEMENTS = _workspacemgt.RheiaEVT_PROJECT_BEGIN_REMOVE_ELEMENTS
RheiaEVT_PROJECT_END_REMOVE_ELEMENTS = _workspacemgt.RheiaEVT_PROJECT_END_REMOVE_ELEMENTS
RheiaEVT_WORKSPACE_OPENING = _workspacemgt.RheiaEVT_WORKSPACE_OPENING
RheiaEVT_WORKSPACE_OPENED = _workspacemgt.RheiaEVT_WORKSPACE_OPENED
RheiaEVT_WORKSPACE_SAVED = _workspacemgt.RheiaEVT_WORKSPACE_SAVED
RheiaEVT_WORKSPACE_SAVING = _workspacemgt.RheiaEVT_WORKSPACE_SAVING
RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS = _workspacemgt.RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS
RheiaEVT_WORKSPACE_END_ADD_PROJECTS = _workspacemgt.RheiaEVT_WORKSPACE_END_ADD_PROJECTS
RheiaEVT_WORKSPACE_CLOSING = _workspacemgt.RheiaEVT_WORKSPACE_CLOSING
RheiaEVT_WORKSPACE_CLOSED = _workspacemgt.RheiaEVT_WORKSPACE_CLOSED
RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS = _workspacemgt.RheiaEVT_WORKSPACE_BEGIN_REMOVE_PROJECTS
RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS = _workspacemgt.RheiaEVT_WORKSPACE_END_REMOVE_PROJECTS
#
# Create some event binders
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

class RheiaProjectEvent(base.RheiaEvent):
    """Proxy of C++ RheiaProjectEvent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, EventType commandType=wxEVT_NULL, int id=0, RheiaProject project=0L, 
            String name=wxEmptyString) -> RheiaProjectEvent
        """
        _workspacemgt.RheiaProjectEvent_swiginit(self,_workspacemgt.new_RheiaProjectEvent(*args, **kwargs))
    def GetProject(*args, **kwargs):
        """GetProject(self) -> RheiaProject"""
        return _workspacemgt.RheiaProjectEvent_GetProject(*args, **kwargs)

    def SetProject(*args, **kwargs):
        """SetProject(self, RheiaProject project)"""
        return _workspacemgt.RheiaProjectEvent_SetProject(*args, **kwargs)

    def GetProjectName(*args, **kwargs):
        """GetProjectName(self) -> String"""
        return _workspacemgt.RheiaProjectEvent_GetProjectName(*args, **kwargs)

    def SetProjectName(*args, **kwargs):
        """SetProjectName(self, String name)"""
        return _workspacemgt.RheiaProjectEvent_SetProjectName(*args, **kwargs)

_workspacemgt.RheiaProjectEvent_swigregister(RheiaProjectEvent)

def RheiaProjectEventCopy(*args, **kwargs):
    """RheiaProjectEventCopy(RheiaProjectEvent event) -> RheiaProjectEvent"""
    val = _workspacemgt.new_RheiaProjectEventCopy(*args, **kwargs)
    return val

class RheiaWorkspaceEvent(base.RheiaEvent):
    """Proxy of C++ RheiaWorkspaceEvent class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, EventType commandType=wxEVT_NULL, int id=0, RheiaWorkspace workspace=0L) -> RheiaWorkspaceEvent"""
        _workspacemgt.RheiaWorkspaceEvent_swiginit(self,_workspacemgt.new_RheiaWorkspaceEvent(*args, **kwargs))
    def GetWorkspace(*args, **kwargs):
        """GetWorkspace(self) -> RheiaWorkspace"""
        return _workspacemgt.RheiaWorkspaceEvent_GetWorkspace(*args, **kwargs)

_workspacemgt.RheiaWorkspaceEvent_swigregister(RheiaWorkspaceEvent)

def RheiaWorkspaceEventCopy(*args, **kwargs):
    """RheiaWorkspaceEventCopy(RheiaWorkspaceEvent event) -> RheiaWorkspaceEvent"""
    val = _workspacemgt.new_RheiaWorkspaceEventCopy(*args, **kwargs)
    return val

class RheiaProject(base.RheiaTreeItem,base.RheiaPageContainer):
    """Proxy of C++ RheiaProject class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _workspacemgt.delete_RheiaProject
    __del__ = lambda self : None;
    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _workspacemgt.RheiaProject_GetName(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _workspacemgt.RheiaProject_SetName(*args, **kwargs)

    def Rename(*args, **kwargs):
        """Rename(self, String name, bool confirm=False) -> bool"""
        return _workspacemgt.RheiaProject_Rename(*args, **kwargs)

    def GetWorkspace(*args, **kwargs):
        """GetWorkspace(self) -> RheiaWorkspace"""
        return _workspacemgt.RheiaProject_GetWorkspace(*args, **kwargs)

    def GetFileName(*args, **kwargs):
        """GetFileName(self) -> String"""
        return _workspacemgt.RheiaProject_GetFileName(*args, **kwargs)

    def SetFileName(*args, **kwargs):
        """SetFileName(self, String file)"""
        return _workspacemgt.RheiaProject_SetFileName(*args, **kwargs)

    def GetType(*args, **kwargs):
        """GetType(self) -> String"""
        return _workspacemgt.RheiaProject_GetType(*args, **kwargs)

    def SetType(*args, **kwargs):
        """SetType(self, String type)"""
        return _workspacemgt.RheiaProject_SetType(*args, **kwargs)

_workspacemgt.RheiaProject_swigregister(RheiaProject)

class RheiaProjectConfigurationDlg(wx._windows.Dialog):
    """Proxy of C++ RheiaProjectConfigurationDlg class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent, RheiaProject project) -> RheiaProjectConfigurationDlg"""
        
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Project Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);

        _workspacemgt.RheiaProjectConfigurationDlg_swiginit(self,_workspacemgt.new_RheiaProjectConfigurationDlg(*args, **kwargs))
    def SetPageSelection(*args, **kwargs):
        """SetPageSelection(self, String page_name)"""
        return _workspacemgt.RheiaProjectConfigurationDlg_SetPageSelection(*args, **kwargs)

    __swig_destroy__ = _workspacemgt.delete_RheiaProjectConfigurationDlg
    __del__ = lambda self : None;
_workspacemgt.RheiaProjectConfigurationDlg_swigregister(RheiaProjectConfigurationDlg)

class RheiaProjectCreationDlg(wx._windows.Dialog):
    """Proxy of C++ RheiaProjectCreationDlg class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaProjectCreationDlg"""
        
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Project Creation Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);

        _workspacemgt.RheiaProjectCreationDlg_swiginit(self,_workspacemgt.new_RheiaProjectCreationDlg(*args, **kwargs))
    __swig_destroy__ = _workspacemgt.delete_RheiaProjectCreationDlg
    __del__ = lambda self : None;
    def GetSelectedWizard(*args, **kwargs):
        """GetSelectedWizard(self) -> String"""
        return _workspacemgt.RheiaProjectCreationDlg_GetSelectedWizard(*args, **kwargs)

    def CreateInNewWorkspace(*args, **kwargs):
        """CreateInNewWorkspace(self) -> bool"""
        return _workspacemgt.RheiaProjectCreationDlg_CreateInNewWorkspace(*args, **kwargs)

_workspacemgt.RheiaProjectCreationDlg_swigregister(RheiaProjectCreationDlg)

class RheiaProjectCreationWizard(wx._core.EvtHandler):
    """Proxy of C++ RheiaProjectCreationWizard class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _workspacemgt.delete_RheiaProjectCreationWizard
    __del__ = lambda self : None;
    def BuildPages(*args, **kwargs):
        """BuildPages(self)"""
        return _workspacemgt.RheiaProjectCreationWizard_BuildPages(*args, **kwargs)

    def GetBitmap(*args, **kwargs):
        """GetBitmap(self) -> Bitmap"""
        return _workspacemgt.RheiaProjectCreationWizard_GetBitmap(*args, **kwargs)

    def GetTitle(*args, **kwargs):
        """GetTitle(self) -> String"""
        return _workspacemgt.RheiaProjectCreationWizard_GetTitle(*args, **kwargs)

    def GetPages(*args, **kwargs):
        """GetPages(self) -> WizardPagesArray"""
        return _workspacemgt.RheiaProjectCreationWizard_GetPages(*args, **kwargs)

    def GetProject(*args, **kwargs):
        """GetProject(self) -> RheiaProject"""
        return _workspacemgt.RheiaProjectCreationWizard_GetProject(*args, **kwargs)

    def OnWizardCancel(*args, **kwargs):
        """OnWizardCancel(self)"""
        return _workspacemgt.RheiaProjectCreationWizard_OnWizardCancel(*args, **kwargs)

    def OnWizardFinished(*args, **kwargs):
        """OnWizardFinished(self)"""
        return _workspacemgt.RheiaProjectCreationWizard_OnWizardFinished(*args, **kwargs)

_workspacemgt.RheiaProjectCreationWizard_swigregister(RheiaProjectCreationWizard)

class MgrRheiaProjectFactory(object):
    """Proxy of C++ MgrRheiaProjectFactory class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Valid(*args, **kwargs):
        """Valid() -> bool"""
        return _workspacemgt.MgrRheiaProjectFactory_Valid(*args, **kwargs)

    Valid = staticmethod(Valid)
    def Get(*args, **kwargs):
        """Get() -> RheiaProjectFactory"""
        return _workspacemgt.MgrRheiaProjectFactory_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Free(*args, **kwargs):
        """Free()"""
        return _workspacemgt.MgrRheiaProjectFactory_Free(*args, **kwargs)

    Free = staticmethod(Free)
_workspacemgt.MgrRheiaProjectFactory_swigregister(MgrRheiaProjectFactory)

def MgrRheiaProjectFactory_Valid(*args):
  """MgrRheiaProjectFactory_Valid() -> bool"""
  return _workspacemgt.MgrRheiaProjectFactory_Valid(*args)

def MgrRheiaProjectFactory_Get(*args):
  """MgrRheiaProjectFactory_Get() -> RheiaProjectFactory"""
  return _workspacemgt.MgrRheiaProjectFactory_Get(*args)

def MgrRheiaProjectFactory_Free(*args):
  """MgrRheiaProjectFactory_Free()"""
  return _workspacemgt.MgrRheiaProjectFactory_Free(*args)

class RheiaProjectRegistration(object):
    """Proxy of C++ RheiaProjectRegistration class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self) -> RheiaProjectRegistration"""
        _workspacemgt.RheiaProjectRegistration_swiginit(self,_workspacemgt.new_RheiaProjectRegistration(*args, **kwargs))
    name = property(_workspacemgt.RheiaProjectRegistration_name_get, _workspacemgt.RheiaProjectRegistration_name_set)
    description = property(_workspacemgt.RheiaProjectRegistration_description_get, _workspacemgt.RheiaProjectRegistration_description_set)
    title = property(_workspacemgt.RheiaProjectRegistration_title_get, _workspacemgt.RheiaProjectRegistration_title_set)
    bitmapBaseName = property(_workspacemgt.RheiaProjectRegistration_bitmapBaseName_get, _workspacemgt.RheiaProjectRegistration_bitmapBaseName_set)
    ctor = property(_workspacemgt.RheiaProjectRegistration_ctor_get, _workspacemgt.RheiaProjectRegistration_ctor_set)
    dtor = property(_workspacemgt.RheiaProjectRegistration_dtor_get, _workspacemgt.RheiaProjectRegistration_dtor_set)
_workspacemgt.RheiaProjectRegistration_swigregister(RheiaProjectRegistration)

class RheiaProjectFactory(MgrRheiaProjectFactory):
    """Proxy of C++ RheiaProjectFactory class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetProjectList(*args, **kwargs):
        """GetProjectList(self) -> wxArrayString"""
        return _workspacemgt.RheiaProjectFactory_GetProjectList(*args, **kwargs)

    def CreateProject(*args, **kwargs):
        """
        CreateProject(self, String type, RheiaManagedFrame parent, RheiaWorkspace workspace, 
            String name=wxEmptyString, String file=wxEmptyString) -> RheiaProject
        """
        return _workspacemgt.RheiaProjectFactory_CreateProject(*args, **kwargs)

    def RegisterProject(*args, **kwargs):
        """
        RegisterProject(self, String name, String description, String title, String bitmapBaseName, 
            ProjectConstructor ctor, ProjectDestructor dtor) -> bool
        """
        return _workspacemgt.RheiaProjectFactory_RegisterProject(*args, **kwargs)

    def UnregisterProject(*args, **kwargs):
        """UnregisterProject(self, String name) -> bool"""
        return _workspacemgt.RheiaProjectFactory_UnregisterProject(*args, **kwargs)

    def GetRegisteredProjects(*args, **kwargs):
        """GetRegisteredProjects(self) -> RheiaProjectRegistrationMap"""
        return _workspacemgt.RheiaProjectFactory_GetRegisteredProjects(*args, **kwargs)

    def FindProjectRegistration(*args, **kwargs):
        """FindProjectRegistration(self, String name) -> RheiaProjectRegistration"""
        return _workspacemgt.RheiaProjectFactory_FindProjectRegistration(*args, **kwargs)

_workspacemgt.RheiaProjectFactory_swigregister(RheiaProjectFactory)

class RheiaProjectLoader(object):
    """Proxy of C++ RheiaProjectLoader class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaProject project) -> RheiaProjectLoader"""
        _workspacemgt.RheiaProjectLoader_swiginit(self,_workspacemgt.new_RheiaProjectLoader(*args, **kwargs))
    __swig_destroy__ = _workspacemgt.delete_RheiaProjectLoader
    __del__ = lambda self : None;
    def Open(*args, **kwargs):
        """Open(self, String file, RheiaManagedFrame parent, RheiaWorkspace workspace) -> bool"""
        return _workspacemgt.RheiaProjectLoader_Open(*args, **kwargs)

    def Save(*args, **kwargs):
        """Save(self, String file) -> bool"""
        return _workspacemgt.RheiaProjectLoader_Save(*args, **kwargs)

    def SetProject(*args, **kwargs):
        """SetProject(self, RheiaProject project)"""
        return _workspacemgt.RheiaProjectLoader_SetProject(*args, **kwargs)

    def GetProject(*args, **kwargs):
        """GetProject(self) -> RheiaProject"""
        return _workspacemgt.RheiaProjectLoader_GetProject(*args, **kwargs)

_workspacemgt.RheiaProjectLoader_swigregister(RheiaProjectLoader)

def PreRheiaProjectLoader(*args, **kwargs):
    """PreRheiaProjectLoader() -> RheiaProjectLoader"""
    val = _workspacemgt.new_PreRheiaProjectLoader(*args, **kwargs)
    return val

class RheiaMgrRheiaWizardManager(object):
    """Proxy of C++ RheiaMgrRheiaWizardManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaWizardManager"""
        return _workspacemgt.RheiaMgrRheiaWizardManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _workspacemgt.RheiaMgrRheiaWizardManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _workspacemgt.RheiaMgrRheiaWizardManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _workspacemgt.RheiaMgrRheiaWizardManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_workspacemgt.RheiaMgrRheiaWizardManager_swigregister(RheiaMgrRheiaWizardManager)

def RheiaMgrRheiaWizardManager_Get(*args, **kwargs):
  """RheiaMgrRheiaWizardManager_Get(RheiaManagedFrame in) -> RheiaWizardManager"""
  return _workspacemgt.RheiaMgrRheiaWizardManager_Get(*args, **kwargs)

def RheiaMgrRheiaWizardManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaWizardManager_Exists(RheiaManagedFrame in) -> bool"""
  return _workspacemgt.RheiaMgrRheiaWizardManager_Exists(*args, **kwargs)

def RheiaMgrRheiaWizardManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaWizardManager_FreeByInstance(RheiaManagedFrame in)"""
  return _workspacemgt.RheiaMgrRheiaWizardManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaWizardManager_Free(*args):
  """RheiaMgrRheiaWizardManager_Free()"""
  return _workspacemgt.RheiaMgrRheiaWizardManager_Free(*args)

class RheiaWizardManager(wx._core.EvtHandler,RheiaMgrRheiaWizardManager):
    """Proxy of C++ RheiaWizardManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def DoCreateNewProject(*args, **kwargs):
        """DoCreateNewProject(self, RheiaWorkspace workspace) -> bool"""
        return _workspacemgt.RheiaWizardManager_DoCreateNewProject(*args, **kwargs)

    def RegisterProjectWizard(*args, **kwargs):
        """
        RegisterProjectWizard(String name, String category, String resName, String bitmapBasename, 
            WizardConstructor ctor, WizardDestructor dtor) -> bool
        """
        return _workspacemgt.RheiaWizardManager_RegisterProjectWizard(*args, **kwargs)

    RegisterProjectWizard = staticmethod(RegisterProjectWizard)
    def UnregisterProjectWizard(*args, **kwargs):
        """UnregisterProjectWizard(String name) -> bool"""
        return _workspacemgt.RheiaWizardManager_UnregisterProjectWizard(*args, **kwargs)

    UnregisterProjectWizard = staticmethod(UnregisterProjectWizard)
    def GetWizardList(*args, **kwargs):
        """GetWizardList() -> wxArrayString"""
        return _workspacemgt.RheiaWizardManager_GetWizardList(*args, **kwargs)

    GetWizardList = staticmethod(GetWizardList)
    def GetCategoryList(*args, **kwargs):
        """GetCategoryList() -> wxArrayString"""
        return _workspacemgt.RheiaWizardManager_GetCategoryList(*args, **kwargs)

    GetCategoryList = staticmethod(GetCategoryList)
    def GetWizardListFor(*args, **kwargs):
        """GetWizardListFor(String category) -> wxArrayString"""
        return _workspacemgt.RheiaWizardManager_GetWizardListFor(*args, **kwargs)

    GetWizardListFor = staticmethod(GetWizardListFor)
    def CreateWizard(*args, **kwargs):
        """
        CreateWizard(String type, Wizard wizard, RheiaManagedFrame parent, 
            RheiaWorkspace workspace) -> RheiaProjectCreationWizard
        """
        return _workspacemgt.RheiaWizardManager_CreateWizard(*args, **kwargs)

    CreateWizard = staticmethod(CreateWizard)
    def FindProjectWizardByName(*args, **kwargs):
        """FindProjectWizardByName(String name) -> RheiaProjectWizardRegistration"""
        return _workspacemgt.RheiaWizardManager_FindProjectWizardByName(*args, **kwargs)

    FindProjectWizardByName = staticmethod(FindProjectWizardByName)
    def GetRegisteredWizards(*args, **kwargs):
        """GetRegisteredWizards() -> RheiaProjectWizardRegistrationMap"""
        return _workspacemgt.RheiaWizardManager_GetRegisteredWizards(*args, **kwargs)

    GetRegisteredWizards = staticmethod(GetRegisteredWizards)
_workspacemgt.RheiaWizardManager_swigregister(RheiaWizardManager)

def RheiaWizardManager_RegisterProjectWizard(*args, **kwargs):
  """
    RheiaWizardManager_RegisterProjectWizard(String name, String category, String resName, String bitmapBasename, 
        WizardConstructor ctor, WizardDestructor dtor) -> bool
    """
  return _workspacemgt.RheiaWizardManager_RegisterProjectWizard(*args, **kwargs)

def RheiaWizardManager_UnregisterProjectWizard(*args, **kwargs):
  """RheiaWizardManager_UnregisterProjectWizard(String name) -> bool"""
  return _workspacemgt.RheiaWizardManager_UnregisterProjectWizard(*args, **kwargs)

def RheiaWizardManager_GetWizardList(*args):
  """RheiaWizardManager_GetWizardList() -> wxArrayString"""
  return _workspacemgt.RheiaWizardManager_GetWizardList(*args)

def RheiaWizardManager_GetCategoryList(*args):
  """RheiaWizardManager_GetCategoryList() -> wxArrayString"""
  return _workspacemgt.RheiaWizardManager_GetCategoryList(*args)

def RheiaWizardManager_GetWizardListFor(*args, **kwargs):
  """RheiaWizardManager_GetWizardListFor(String category) -> wxArrayString"""
  return _workspacemgt.RheiaWizardManager_GetWizardListFor(*args, **kwargs)

def RheiaWizardManager_CreateWizard(*args, **kwargs):
  """
    RheiaWizardManager_CreateWizard(String type, Wizard wizard, RheiaManagedFrame parent, 
        RheiaWorkspace workspace) -> RheiaProjectCreationWizard
    """
  return _workspacemgt.RheiaWizardManager_CreateWizard(*args, **kwargs)

def RheiaWizardManager_FindProjectWizardByName(*args, **kwargs):
  """RheiaWizardManager_FindProjectWizardByName(String name) -> RheiaProjectWizardRegistration"""
  return _workspacemgt.RheiaWizardManager_FindProjectWizardByName(*args, **kwargs)

def RheiaWizardManager_GetRegisteredWizards(*args):
  """RheiaWizardManager_GetRegisteredWizards() -> RheiaProjectWizardRegistrationMap"""
  return _workspacemgt.RheiaWizardManager_GetRegisteredWizards(*args)

class RheiaWizardPageBase(wx.wizard.WizardPageSimple):
    """Proxy of C++ RheiaWizardPageBase class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _workspacemgt.delete_RheiaWizardPageBase
    __del__ = lambda self : None;
    def GetPageName(*args, **kwargs):
        """GetPageName(self) -> String"""
        return _workspacemgt.RheiaWizardPageBase_GetPageName(*args, **kwargs)

    def OnPageChanged(*args, **kwargs):
        """OnPageChanged(self) -> bool"""
        return _workspacemgt.RheiaWizardPageBase_OnPageChanged(*args, **kwargs)

    def OnPageChanging(*args, **kwargs):
        """OnPageChanging(self) -> bool"""
        return _workspacemgt.RheiaWizardPageBase_OnPageChanging(*args, **kwargs)

_workspacemgt.RheiaWizardPageBase_swigregister(RheiaWizardPageBase)

class RheiaWkspMgrSettingsPanel(base.RheiaConfigurationPanel):
    """Proxy of C++ RheiaWkspMgrSettingsPanel class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent) -> RheiaWkspMgrSettingsPanel"""
        
	wx.Panel.__init__(self,args[0],wx.ID_ANY);

        _workspacemgt.RheiaWkspMgrSettingsPanel_swiginit(self,_workspacemgt.new_RheiaWkspMgrSettingsPanel(*args, **kwargs))
    __swig_destroy__ = _workspacemgt.delete_RheiaWkspMgrSettingsPanel
    __del__ = lambda self : None;
_workspacemgt.RheiaWkspMgrSettingsPanel_swigregister(RheiaWkspMgrSettingsPanel)

class RheiaWorkspace(base.RheiaTreeItem):
    """Proxy of C++ RheiaWorkspace class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """
        __init__(self, RheiaManagedFrame parent, String filename=wxEmptyString, 
            String name=wxEmptyString) -> RheiaWorkspace
        """
        _workspacemgt.RheiaWorkspace_swiginit(self,_workspacemgt.new_RheiaWorkspace(*args, **kwargs))
    def Create(*args, **kwargs):
        """
        Create(self, RheiaManagedFrame parent, String filename=wxEmptyString, 
            String name=wxEmptyString)
        """
        return _workspacemgt.RheiaWorkspace_Create(*args, **kwargs)

    __swig_destroy__ = _workspacemgt.delete_RheiaWorkspace
    __del__ = lambda self : None;
    def GetName(*args, **kwargs):
        """GetName(self) -> String"""
        return _workspacemgt.RheiaWorkspace_GetName(*args, **kwargs)

    def GetFileName(*args, **kwargs):
        """GetFileName(self) -> String"""
        return _workspacemgt.RheiaWorkspace_GetFileName(*args, **kwargs)

    def GetPath(*args, **kwargs):
        """GetPath(self) -> String"""
        return _workspacemgt.RheiaWorkspace_GetPath(*args, **kwargs)

    def Rename(*args, **kwargs):
        """Rename(self, String name, bool confirm=False) -> bool"""
        return _workspacemgt.RheiaWorkspace_Rename(*args, **kwargs)

    def SetName(*args, **kwargs):
        """SetName(self, String name)"""
        return _workspacemgt.RheiaWorkspace_SetName(*args, **kwargs)

    def SetFileName(*args, **kwargs):
        """SetFileName(self, String file)"""
        return _workspacemgt.RheiaWorkspace_SetFileName(*args, **kwargs)

_workspacemgt.RheiaWorkspace_swigregister(RheiaWorkspace)

def PreRheiaWorkspace(*args, **kwargs):
    """PreRheiaWorkspace() -> RheiaWorkspace"""
    val = _workspacemgt.new_PreRheiaWorkspace(*args, **kwargs)
    return val

def RheiaWorkspaceCopy(*args, **kwargs):
    """RheiaWorkspaceCopy(RheiaWorkspace Wksp) -> RheiaWorkspace"""
    val = _workspacemgt.new_RheiaWorkspaceCopy(*args, **kwargs)
    return val

class RheiaWorkspaceLoader(object):
    """Proxy of C++ RheiaWorkspaceLoader class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, RheiaWorkspace workspace) -> RheiaWorkspaceLoader"""
        _workspacemgt.RheiaWorkspaceLoader_swiginit(self,_workspacemgt.new_RheiaWorkspaceLoader(*args, **kwargs))
    __swig_destroy__ = _workspacemgt.delete_RheiaWorkspaceLoader
    __del__ = lambda self : None;
    def Open(*args, **kwargs):
        """Open(self, String file) -> bool"""
        return _workspacemgt.RheiaWorkspaceLoader_Open(*args, **kwargs)

    def Save(*args, **kwargs):
        """Save(self, String file) -> bool"""
        return _workspacemgt.RheiaWorkspaceLoader_Save(*args, **kwargs)

_workspacemgt.RheiaWorkspaceLoader_swigregister(RheiaWorkspaceLoader)

class RheiaMgrRheiaWorkspaceManager(object):
    """Proxy of C++ RheiaMgrRheiaWorkspaceManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def Get(*args, **kwargs):
        """Get(RheiaManagedFrame in) -> RheiaWorkspaceManager"""
        return _workspacemgt.RheiaMgrRheiaWorkspaceManager_Get(*args, **kwargs)

    Get = staticmethod(Get)
    def Exists(*args, **kwargs):
        """Exists(RheiaManagedFrame in) -> bool"""
        return _workspacemgt.RheiaMgrRheiaWorkspaceManager_Exists(*args, **kwargs)

    Exists = staticmethod(Exists)
    def FreeByInstance(*args, **kwargs):
        """FreeByInstance(RheiaManagedFrame in)"""
        return _workspacemgt.RheiaMgrRheiaWorkspaceManager_FreeByInstance(*args, **kwargs)

    FreeByInstance = staticmethod(FreeByInstance)
    def Free(*args, **kwargs):
        """Free()"""
        return _workspacemgt.RheiaMgrRheiaWorkspaceManager_Free(*args, **kwargs)

    Free = staticmethod(Free)
_workspacemgt.RheiaMgrRheiaWorkspaceManager_swigregister(RheiaMgrRheiaWorkspaceManager)

def RheiaMgrRheiaWorkspaceManager_Get(*args, **kwargs):
  """RheiaMgrRheiaWorkspaceManager_Get(RheiaManagedFrame in) -> RheiaWorkspaceManager"""
  return _workspacemgt.RheiaMgrRheiaWorkspaceManager_Get(*args, **kwargs)

def RheiaMgrRheiaWorkspaceManager_Exists(*args, **kwargs):
  """RheiaMgrRheiaWorkspaceManager_Exists(RheiaManagedFrame in) -> bool"""
  return _workspacemgt.RheiaMgrRheiaWorkspaceManager_Exists(*args, **kwargs)

def RheiaMgrRheiaWorkspaceManager_FreeByInstance(*args, **kwargs):
  """RheiaMgrRheiaWorkspaceManager_FreeByInstance(RheiaManagedFrame in)"""
  return _workspacemgt.RheiaMgrRheiaWorkspaceManager_FreeByInstance(*args, **kwargs)

def RheiaMgrRheiaWorkspaceManager_Free(*args):
  """RheiaMgrRheiaWorkspaceManager_Free()"""
  return _workspacemgt.RheiaMgrRheiaWorkspaceManager_Free(*args)

class RheiaWorkspaceManager(wx._core.EvtHandler,base.RheiaPageContainer,RheiaMgrRheiaWorkspaceManager):
    """Proxy of C++ RheiaWorkspaceManager class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def GetManagementTree(*args, **kwargs):
        """GetManagementTree(self) -> TreeCtrl"""
        return _workspacemgt.RheiaWorkspaceManager_GetManagementTree(*args, **kwargs)

    def GetManagementTreeRoot(*args, **kwargs):
        """GetManagementTreeRoot(self) -> TreeItemId"""
        return _workspacemgt.RheiaWorkspaceManager_GetManagementTreeRoot(*args, **kwargs)

    def ReloadWorkspaceTree(*args, **kwargs):
        """ReloadWorkspaceTree(self)"""
        return _workspacemgt.RheiaWorkspaceManager_ReloadWorkspaceTree(*args, **kwargs)

    def ReloadConfig(*args, **kwargs):
        """ReloadConfig(self)"""
        return _workspacemgt.RheiaWorkspaceManager_ReloadConfig(*args, **kwargs)

    def RegisterEvents(*args, **kwargs):
        """RegisterEvents(self)"""
        return _workspacemgt.RheiaWorkspaceManager_RegisterEvents(*args, **kwargs)

    def OnSettingsChanged(*args, **kwargs):
        """OnSettingsChanged(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnSettingsChanged(*args, **kwargs)

    def OnEnvironmentPluginDetach(*args, **kwargs):
        """OnEnvironmentPluginDetach(self, RheiaPluginEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnEnvironmentPluginDetach(*args, **kwargs)

    def AddWorkspace(*args, **kwargs):
        """AddWorkspace(self, RheiaWorkspace workspace, String name) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_AddWorkspace(*args, **kwargs)

    def Exists(*args, **kwargs):
        """Exists(self, String name) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_Exists(*args, **kwargs)

    def FindWorkspace(*args, **kwargs):
        """FindWorkspace(self, String name) -> RheiaWorkspace"""
        return _workspacemgt.RheiaWorkspaceManager_FindWorkspace(*args, **kwargs)

    def GetWorkspaceTable(*args, **kwargs):
        """GetWorkspaceTable(self) -> RheiaWorkspaceTable"""
        return _workspacemgt.RheiaWorkspaceManager_GetWorkspaceTable(*args, **kwargs)

    def GetCurrentSelectedWorkspace(*args, **kwargs):
        """GetCurrentSelectedWorkspace(self) -> String"""
        return _workspacemgt.RheiaWorkspaceManager_GetCurrentSelectedWorkspace(*args, **kwargs)

    def SelectWorkspace(*args, **kwargs):
        """SelectWorkspace(self, String name)"""
        return _workspacemgt.RheiaWorkspaceManager_SelectWorkspace(*args, **kwargs)

    def SelectProject(*args, **kwargs):
        """SelectProject(self, String name)"""
        return _workspacemgt.RheiaWorkspaceManager_SelectProject(*args, **kwargs)

    def LoadWorkspace(*args, **kwargs):
        """LoadWorkspace(self, String filename) -> RheiaWorkspace"""
        return _workspacemgt.RheiaWorkspaceManager_LoadWorkspace(*args, **kwargs)

    def SaveWorkspace(*args, **kwargs):
        """SaveWorkspace(self, RheiaWorkspace workspace) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_SaveWorkspace(*args, **kwargs)

    def RemoveWorkspace(*args, **kwargs):
        """RemoveWorkspace(self, String name) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_RemoveWorkspace(*args, **kwargs)

    def RemoveProjectsFor(*args, **kwargs):
        """RemoveProjectsFor(self, RheiaEnvironmentPlugin plugin, bool confirmation=False) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_RemoveProjectsFor(*args, **kwargs)

    def FinalizeStartUp(*args, **kwargs):
        """FinalizeStartUp(self)"""
        return _workspacemgt.RheiaWorkspaceManager_FinalizeStartUp(*args, **kwargs)

    def BuildMenu(*args, **kwargs):
        """BuildMenu(self, MenuBar menuBar)"""
        return _workspacemgt.RheiaWorkspaceManager_BuildMenu(*args, **kwargs)

    def ReleaseMenu(*args, **kwargs):
        """ReleaseMenu(self, MenuBar menuBar)"""
        return _workspacemgt.RheiaWorkspaceManager_ReleaseMenu(*args, **kwargs)

    def OnConfigure(*args, **kwargs):
        """OnConfigure(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnConfigure(*args, **kwargs)

    def OnFileWorkspaceNew(*args, **kwargs):
        """OnFileWorkspaceNew(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileWorkspaceNew(*args, **kwargs)

    def OnFileWorkspaceOpen(*args, **kwargs):
        """OnFileWorkspaceOpen(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileWorkspaceOpen(*args, **kwargs)

    def OnFileWorkspaceSave(*args, **kwargs):
        """OnFileWorkspaceSave(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileWorkspaceSave(*args, **kwargs)

    def OnFileWorkspaceSaveAll(*args, **kwargs):
        """OnFileWorkspaceSaveAll(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileWorkspaceSaveAll(*args, **kwargs)

    def OnFileWorkspaceClose(*args, **kwargs):
        """OnFileWorkspaceClose(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileWorkspaceClose(*args, **kwargs)

    def OnFileProjectNew(*args, **kwargs):
        """OnFileProjectNew(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileProjectNew(*args, **kwargs)

    def OnFileProjectOpen(*args, **kwargs):
        """OnFileProjectOpen(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileProjectOpen(*args, **kwargs)

    def OnFileProjectSave(*args, **kwargs):
        """OnFileProjectSave(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileProjectSave(*args, **kwargs)

    def OnFileProjectSaveAs(*args, **kwargs):
        """OnFileProjectSaveAs(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileProjectSaveAs(*args, **kwargs)

    def OnFileProjectClose(*args, **kwargs):
        """OnFileProjectClose(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnFileProjectClose(*args, **kwargs)

    def BuildToolBar(*args, **kwargs):
        """BuildToolBar(self, Window parent) -> ToolBar"""
        return _workspacemgt.RheiaWorkspaceManager_BuildToolBar(*args, **kwargs)

    def BuildProjectsToolBar(*args, **kwargs):
        """BuildProjectsToolBar(self, Window parent) -> ToolBar"""
        return _workspacemgt.RheiaWorkspaceManager_BuildProjectsToolBar(*args, **kwargs)

    def SaveAll(*args, **kwargs):
        """SaveAll(self) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_SaveAll(*args, **kwargs)

    def OnCloseParent(*args, **kwargs):
        """OnCloseParent(self, RheiaFrameEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnCloseParent(*args, **kwargs)

    def AddLast(*args, **kwargs):
        """AddLast(self, String path) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_AddLast(*args, **kwargs)

    def SetHistoryLenght(*args, **kwargs):
        """SetHistoryLenght(self, size_t length) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_SetHistoryLenght(*args, **kwargs)

    def SetLast(*args, **kwargs):
        """SetLast(self, String path) -> bool"""
        return _workspacemgt.RheiaWorkspaceManager_SetLast(*args, **kwargs)

    def RecreateLastMenu(*args, **kwargs):
        """RecreateLastMenu(self)"""
        return _workspacemgt.RheiaWorkspaceManager_RecreateLastMenu(*args, **kwargs)

    def OnRecentOpen(*args, **kwargs):
        """OnRecentOpen(self, CommandEvent event)"""
        return _workspacemgt.RheiaWorkspaceManager_OnRecentOpen(*args, **kwargs)

_workspacemgt.RheiaWorkspaceManager_swigregister(RheiaWorkspaceManager)

class RheiaWorkspaceBookPage(base.RheiaBookPage):
    """Proxy of C++ RheiaWorkspaceBookPage class"""
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc='The membership flag')
    __repr__ = _swig_repr
    def __init__(self, *args, **kwargs): 
        """__init__(self, Window parent, RheiaWorkspaceManager wmgr) -> RheiaWorkspaceBookPage"""
        _workspacemgt.RheiaWorkspaceBookPage_swiginit(self,_workspacemgt.new_RheiaWorkspaceBookPage(*args, **kwargs))
    __swig_destroy__ = _workspacemgt.delete_RheiaWorkspaceBookPage
    __del__ = lambda self : None;
_workspacemgt.RheiaWorkspaceBookPage_swigregister(RheiaWorkspaceBookPage)



