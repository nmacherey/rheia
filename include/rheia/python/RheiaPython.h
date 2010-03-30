/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/



#ifndef RheiaPython_h_
#define RheiaPython_h_

#include <Python.h>
#include <wx/wx.h>

#include <wx/busyinfo.h>
#include <wx/caret.h>
#include <wx/choicebk.h>
#include <wx/clipbrd.h>
#include <wx/colordlg.h>
#include <wx/config.h>
#include <wx/cshelp.h>
#include <wx/dcmirror.h>
#include <wx/dcps.h>
#include <wx/dirctrl.h>
#include <wx/dirdlg.h>
#include <wx/numdlg.h>
#include <wx/dnd.h>
#include <wx/docview.h>
#include <wx/encconv.h>
#include <wx/fdrepdlg.h>
#include <wx/fileconf.h>
#include <wx/filesys.h>
#include <wx/fontdlg.h>
#include <wx/fs_inet.h>
#include <wx/fs_mem.h>
#include <wx/fs_zip.h>
#include <wx/gbsizer.h>
#include <wx/wrapsizer.h>
#include <wx/geometry.h>
#include <wx/htmllbox.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/intl.h>
#include <wx/laywin.h>
#include <wx/listbase.h>
#include <wx/listbook.h>
#include <wx/minifram.h>
#include <wx/notebook.h>
#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/process.h>
#include <wx/progdlg.h>
#include <wx/sashwin.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splash.h>
#include <wx/splitter.h>
#include <wx/statline.h>
#include <wx/stream.h>
#include <wx/sysopt.h>
#include <wx/taskbar.h>
#include <wx/tglbtn.h>
#include <wx/tipwin.h>
#include <wx/toolbook.h>
#include <wx/tooltip.h>
#include <wx/treebook.h>
#include <wx/vlbox.h>
#include <wx/vscroll.h>
#include <wx/dateevt.h>
#include <wx/datectrl.h>
#include <wx/power.h>
#include <wx/hyperlink.h>
#include <wx/pickerbase.h>
#include <wx/clrpicker.h>
#include <wx/filepicker.h>
#include <wx/fontpicker.h>    
#include <wx/collpane.h>
#include <wx/srchctrl.h>
#include <wx/generic/datectrl.h>
#include <wx/filectrl.h>
#include <wx/notifmsg.h>
#include <wx/wizard.h>

// C++ version of Python aware wxTreeCtrl
class wxPyTreeCtrl : public wxTreeCtrl {
    DECLARE_ABSTRACT_CLASS(wxPyTreeCtrl)
public:
    wxPyTreeCtrl() : wxTreeCtrl() {}
    wxPyTreeCtrl(wxWindow *parent, wxWindowID id,
                 const wxPoint& pos,
                 const wxSize& size,
                 long style,
                 const wxValidator& validator,
                 const wxString& name) :
        wxTreeCtrl(parent, id, pos, size, style, validator, name) {}

    bool Create(wxWindow *parent, wxWindowID id,
                const wxPoint& pos,
                const wxSize& size,
                long style,
                const wxValidator& validator,
                const wxString& name) {
        return wxTreeCtrl::Create(parent, id, pos, size, style, validator, name);
    }


    int OnCompareItems(const wxTreeItemId& item1,
                       const wxTreeItemId& item2) {
        int rval = 0;
        bool found;
        wxPyBlock_t blocked = wxPyBeginBlockThreads();
        if ((found = wxPyCBH_findCallback(m_myInst, "OnCompareItems"))) {
            PyObject *o1 = wxPyConstructObject((void*)&item1, wxT("wxTreeItemId"), false);
            PyObject *o2 = wxPyConstructObject((void*)&item2, wxT("wxTreeItemId"), false);
            rval = wxPyCBH_callCallback(m_myInst, Py_BuildValue("(OO)",o1,o2));
            Py_DECREF(o1);
            Py_DECREF(o2);
        }
        wxPyEndBlockThreads(blocked);
        if (! found)
            rval = wxTreeCtrl::OnCompareItems(item1, item2);
        return rval;
    }
    PYPRIVATE;
};

class wxPyWizardPage : public wxWizardPage {
    DECLARE_ABSTRACT_CLASS(wxPyWizardPage)
public:
    wxPyWizardPage() : wxWizardPage() {}
    wxPyWizardPage(wxWizard *parent,
                   const wxBitmap& bitmap = wxNullBitmap)
        : wxWizardPage(parent, bitmap) {}

    DEC_PYCALLBACK_WIZPG__pure(GetPrev);
    DEC_PYCALLBACK_WIZPG__pure(GetNext);
    DEC_PYCALLBACK_BITMAP__pure(GetBitmap);

    DEC_PYCALLBACK_VOID_INT4(DoMoveWindow);
    DEC_PYCALLBACK_VOID_INT5(DoSetSize);
    DEC_PYCALLBACK_VOID_INTINT(DoSetClientSize);
    DEC_PYCALLBACK_VOID_INTINT(DoSetVirtualSize);

    DEC_PYCALLBACK_VOID_INTPINTP_const(DoGetSize);
    DEC_PYCALLBACK_VOID_INTPINTP_const(DoGetClientSize);
    DEC_PYCALLBACK_VOID_INTPINTP_const(DoGetPosition);

    DEC_PYCALLBACK_SIZE_const(DoGetVirtualSize);
    DEC_PYCALLBACK_SIZE_const(DoGetBestSize);

    DEC_PYCALLBACK__(InitDialog);
    DEC_PYCALLBACK_BOOL_(TransferDataFromWindow);
    DEC_PYCALLBACK_BOOL_(TransferDataToWindow);
    DEC_PYCALLBACK_BOOL_(Validate);

    DEC_PYCALLBACK_BOOL_const(AcceptsFocus);
    DEC_PYCALLBACK_BOOL_const(AcceptsFocusFromKeyboard);
    DEC_PYCALLBACK_SIZE_const(GetMaxSize);

    DEC_PYCALLBACK_VOID_WXWINBASE(AddChild);
    DEC_PYCALLBACK_VOID_WXWINBASE(RemoveChild);

    PYPRIVATE;
};


bool RheiaPythonCheckSwigType(const wxString& className);
PyObject* RheiaPythonConstructObject(void* ptr, const wxString& className,  int setThisOwn=0);
bool RheiaPythonConvertSwigPtr(PyObject* obj, void **ptr, const wxString& className);
PyObject* RheiaPythonMakeSwigPtr(void* ptr, const wxString& classname);

bool RheiaPythonUtilsCheckSwigType(const wxString& className);
PyObject* RheiaPythonUtilsConstructObject(void* ptr, const wxString& className,  int setThisOwn=0);
bool RheiaPythonConvertUtilsSwigPtr(PyObject* obj, void **ptr, const wxString& className);
PyObject* RheiaPythonMakeUtilsSwigPtr(void* ptr, const wxString& classname);

bool RheiaPythonLoggersCheckSwigType(const wxString& className);
PyObject* RheiaPythonLoggersConstructObject(void* ptr, const wxString& className,  int setThisOwn=0);
bool RheiaPythonConvertLoggersSwigPtr(PyObject* obj, void **ptr, const wxString& className);
PyObject* RheiaPythonMakeLoggersSwigPtr(void* ptr, const wxString& classname);

bool RheiaPythonPackageCheckSwigType(const wxString& className);
PyObject* RheiaPythonPackageConstructObject(void* ptr, const wxString& className,  int setThisOwn=0);
bool RheiaPythonConvertPackageSwigPtr(PyObject* obj, void **ptr, const wxString& className);
PyObject* RheiaPythonMakePackageSwigPtr(void* ptr, const wxString& classname);

bool RheiaPythonWorkspaceCheckSwigType(const wxString& className);
PyObject* RheiaPythonWorkspaceConstructObject(void* ptr, const wxString& className,  int setThisOwn=0);
bool RheiaPythonConvertWorkspaceSwigPtr(PyObject* obj, void **ptr, const wxString& className);
PyObject* RheiaPythonMakeWorkspaceSwigPtr(void* ptr, const wxString& classname);

struct RheiaPythonCoreAPI {

    bool                (*p_RheiaPythonCheckSwigType)(const wxString& className);
    PyObject*           (*p_RheiaPythonConstructObject)(void* ptr, const wxString& className, int setThisOwn);
    bool                (*p_RheiaPythonConvertSwigPtr)(PyObject* obj, void **ptr, const wxString& className);
    PyObject*           (*p_RheiaPythonMakeSwigPtr)(void* ptr, const wxString& className);
};

static RheiaPythonCoreAPI* RheiaPythonBaseAPI = NULL;
static RheiaPythonCoreAPI* RheiaPythonUtilsAPI = NULL;
static RheiaPythonCoreAPI* RheiaPythonLoggersAPI = NULL;
static RheiaPythonCoreAPI* RheiaPythonPackageAPI = NULL;
static RheiaPythonCoreAPI* RheiaPythonWorkspaceAPI = NULL;


static bool RheiaPythonCoreAPI_IMPORT()
{
    RheiaPythonBaseAPI = (RheiaPythonCoreAPI*)PyCObject_Import("rheia._base", "_RheiaPythonCoreAPI");
	RheiaPythonUtilsAPI = (RheiaPythonCoreAPI*)PyCObject_Import("rheia._utils", "_RheiaPythonUtilsAPI");
	RheiaPythonLoggersAPI = (RheiaPythonCoreAPI*)PyCObject_Import("rheia._loggers", "_RheiaPythonLoggersAPI");
	RheiaPythonPackageAPI = (RheiaPythonCoreAPI*)PyCObject_Import("rheia._packagemgt", "_RheiaPythonPackageAPI");
	RheiaPythonWorkspaceAPI = (RheiaPythonCoreAPI*)PyCObject_Import("rheia._workspacemgt", "_RheiaPythonWorkspaceAPI");
	
    return ( (RheiaPythonBaseAPI != NULL) && (RheiaPythonUtilsAPI != NULL) && (RheiaPythonLoggersAPI != NULL) && (RheiaPythonPackageAPI != NULL) && (RheiaPythonWorkspaceAPI != NULL) );
}

inline RheiaPythonCoreAPI* RheiaPythonGetBaseAPIPtr()
{
    if (RheiaPythonBaseAPI == NULL) RheiaPythonCoreAPI_IMPORT();
    return RheiaPythonBaseAPI;
}

inline RheiaPythonCoreAPI* RheiaPythonGetUtilsAPIPtr()
{
    if (RheiaPythonUtilsAPI == NULL) RheiaPythonCoreAPI_IMPORT();
    return RheiaPythonUtilsAPI;
}

inline RheiaPythonCoreAPI* RheiaPythonGetLoggersAPIPtr()
{
    if (RheiaPythonLoggersAPI == NULL) RheiaPythonCoreAPI_IMPORT();
    return RheiaPythonLoggersAPI;
}

inline RheiaPythonCoreAPI* RheiaPythonGetPackageAPIPtr()
{
    if (RheiaPythonPackageAPI == NULL) RheiaPythonCoreAPI_IMPORT();
    return RheiaPythonPackageAPI;
}

inline RheiaPythonCoreAPI* RheiaPythonGetWorkspaceAPIPtr()
{
    if (RheiaPythonWorkspaceAPI == NULL) RheiaPythonCoreAPI_IMPORT();
    return RheiaPythonWorkspaceAPI;
}

#define rheiaPythonBaseCheckSwigType(a)                    (RheiaPythonGetBaseAPIPtr()->p_RheiaPythonCheckSwigType(a))
#define rheiaPythonBaseConstructObject(a,b,c)              (RheiaPythonGetBaseAPIPtr()->p_RheiaPythonConstructObject(a,b,c))
#define rheiaPythonBaseConvertSwigPtr(a,b,c)               (RheiaPythonGetBaseAPIPtr()->p_RheiaPythonConvertSwigPtr(a,b,c))
#define rheiaPythonBaseMakeSwigPtr(a,b)                    (RheiaPythonGetBaseAPIPtr()->p_RheiaPythonMakeSwigPtr(a,b))

#define rheiaPythonUtilsCheckSwigType(a)                   (RheiaPythonGetUtilsAPIPtr()->p_RheiaPythonCheckSwigType(a))
#define rheiaPythonUtilsConstructObject(a,b,c)             (RheiaPythonGetUtilsAPIPtr()->p_RheiaPythonConstructObject(a,b,c))
#define rheiaPythonUtilsConvertSwigPtr(a,b,c)              (RheiaPythonGetUtilsAPIPtr()->p_RheiaPythonConvertSwigPtr(a,b,c))
#define rheiaPythonUtilsMakeSwigPtr(a,b)                   (RheiaPythonGetUtilsAPIPtr()->p_RheiaPythonMakeSwigPtr(a,b))

#define rheiaPythonLoggersCheckSwigType(a)                 (RheiaPythonGetLoggersAPIPtr()->p_RheiaPythonCheckSwigType(a))
#define rheiaPythonLoggersConstructObject(a,b,c)           (RheiaPythonGetLoggersAPIPtr()->p_RheiaPythonConstructObject(a,b,c))
#define rheiaPythonLoggersConvertSwigPtr(a,b,c)            (RheiaPythonGetLoggersAPIPtr()->p_RheiaPythonConvertSwigPtr(a,b,c))
#define rheiaPythonLoggersMakeSwigPtr(a,b)                 (RheiaPythonGetLoggersAPIPtr()->p_RheiaPythonMakeSwigPtr(a,b))

#define rheiaPythonPackageCheckSwigType(a)                 (RheiaPythonGetPackageAPIPtr()->p_RheiaPythonCheckSwigType(a))
#define rheiaPythonPackageConstructObject(a,b,c)           (RheiaPythonGetPackageAPIPtr()->p_RheiaPythonConstructObject(a,b,c))
#define rheiaPythonPackageConvertSwigPtr(a,b,c)            (RheiaPythonGetPackageAPIPtr()->p_RheiaPythonConvertSwigPtr(a,b,c))
#define rheiaPythonPackageMakeSwigPtr(a,b)                 (RheiaPythonGetPackageAPIPtr()->p_RheiaPythonMakeSwigPtr(a,b))

#define rheiaPythonWorkspaceCheckSwigType(a)               (RheiaPythonGetWorkspaceAPIPtr()->p_RheiaPythonCheckSwigType(a))
#define rheiaPythonWorkspaceConstructObject(a,b,c)         (RheiaPythonGetWorkspaceAPIPtr()->p_RheiaPythonConstructObject(a,b,c))
#define rheiaPythonWorkspaceConvertSwigPtr(a,b,c)          (RheiaPythonGetWorkspaceAPIPtr()->p_RheiaPythonConvertSwigPtr(a,b,c))
#define rheiaPythonWorkspaceMakeSwigPtr(a,b)               (RheiaPythonGetWorkspaceAPIPtr()->p_RheiaPythonMakeSwigPtr(a,b))

#include "RheiaPlugin.h"

class RheiaPyPlugin : public RheiaPlugin
{
public :
	/**
	* If you want to write a plugin all your building and construction tasks shall be done
	* in this method. It is called by the RheiaPlugin::Plug() method in RheiaPluginManager
	* and allow you to perform you initalization tasks. Then the plugin shall be usable and
	* all it's informations too. In the application.
	* Here do what you need simply overload the method... 
	*/
	virtual void OnPyPlug() = 0;

	/*! Any descendent plugin should override this virtual method and
	* perform any necessary de-initialization. This method is called by
	* Rheia (RheiaPluginManager actually) when the plugin has been
	* loaded, attached and should de-attach from Rheia.\n
	* Think of this method as the actual destructor...
	* @param appShutDown If true, the application is shutting down. In this
	*         case *don't* use RheiaManager::Get()->Get...() functions or the
	*         behaviour is undefined...
	*/
	virtual void OnPyUnplug(bool) = 0;
	
protected :
	virtual void OnPlug() {OnPyPlug();};
	virtual void OnUnplug(bool val) {OnPyUnplug(val);};
};

#endif
