


#ifndef RheiaPython_h_
#define RheiaPython_h_

#include <Python.h>
#include <wx/wx.h>


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


#endif
