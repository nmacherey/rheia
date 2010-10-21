
%module(package="rheia",directors="1") utils
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
#include "wxirrlicht.h"

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
%import _treectrl.i

%pythoncode { 
%#// A little trick to make 'wx' be a reference to this module so wx.Names can
%#// be used here.
import sys as _sys
rheia = _sys.modules[__name__]
}

%import "RheiaUtilsSettings.h"
%include utils_api.i

%include "RheiaAppGlobals.h"
%include "RheiaGlobals.h"
%include "RheiaInfoWindow.h"
%include "RheiaStandardPaths.h"
%include "wxirrlicht.h"

