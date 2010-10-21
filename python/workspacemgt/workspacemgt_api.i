/////////////////////////////////////////////////////////////////////////////
// Name:        Workspace_api.i
// Purpose:
//
// Author:      Nicolas Macherey from the work of Robin Dunn 
// Remarks : 	This file has just been adapted in order to be specific to the base rheia python wrapper
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// Not a %module


//---------------------------------------------------------------------------
%{
// Helper functions for dealing with SWIG objects and such.  These are
// located here so they know about the SWIG types and functions declared
// in the wrapper code.
#include "RheiaPython.h"
#include <wx/hashmap.h>
WX_DECLARE_STRING_HASH_MAP( swig_type_info*, RheiaPythonWorkspaceTypeInfoHashMap );


// Maintains a hashmap of className to swig_type_info pointers.  Given the
// name of a class either looks up the type info in the cache, or scans the
// SWIG tables for it.
PyObject* RheiaPythonWorkspacePtrTypeMap = PyDict_New();
 
static
swig_type_info* RheiaPythonWorkspaceFindSwigType(const wxString& className) {

    static RheiaPythonWorkspaceTypeInfoHashMap* typeInfoCache = NULL;

    if (typeInfoCache == NULL)
        typeInfoCache = new RheiaPythonWorkspaceTypeInfoHashMap;

    wxString name(className);
    swig_type_info* swigType = (*typeInfoCache)[name];

    if (! swigType) {
        // it wasn't in the cache, so look it up from SWIG
        name.Append(wxT(" *"));
        swigType = SWIG_TypeQuery(name.mb_str());
        
        // if it still wasn't found, try looking for a mapped name
        if (!swigType) {
            PyObject* item;
            name = className;
            
            if ((item = PyDict_GetItemString(RheiaPythonWorkspacePtrTypeMap,
                               (char*)(const char*)name.mbc_str())) != NULL) {
                name = wxString(PyString_AsString(item), *wxConvCurrent);
                name.Append(wxT(" *"));
                swigType = SWIG_TypeQuery(name.mb_str());
            }
        }
        if (swigType) {
            // and add it to the map if found
            (*typeInfoCache)[className] = swigType;
        }
    }
    return swigType;    
}


// Check if a class name is a type known to SWIG
bool RheiaPythonWorkspaceCheckSwigType(const wxString& className) {

    swig_type_info* swigType = RheiaPythonWorkspaceFindSwigType(className);
    return swigType != NULL;
}
 
    
// Given a pointer to a C++ object and a class name, construct a Python proxy
// object for it.    
PyObject* RheiaPythonWorkspaceConstructObject(void* ptr,
                              const wxString& className,
                              int setThisOwn) {

    swig_type_info* swigType = RheiaPythonWorkspaceFindSwigType(className);
    wxCHECK_MSG(swigType != NULL, NULL, wxT("Unknown type in RheiaPythonWorkspaceConstructObject"));

    return SWIG_Python_NewPointerObj(ptr, swigType, setThisOwn);
}


// Extract a pointer to the wrapped C++ object from a Python proxy object.
// Ensures that the proxy object is of the specified (or derived) type.  If
// not able to perform the conversion then a Python exception is set and the
// error should be handled properly in the caller.  Returns True on success.
bool RheiaPythonWorkspaceConvertSwigPtr(PyObject* obj, void **ptr,
                        const wxString& className) {

    swig_type_info* swigType = RheiaPythonWorkspaceFindSwigType(className);
    wxCHECK_MSG(swigType != NULL, false, wxT("Unknown type in RheiaPythonWorkspaceConvertSwigPtr"));

    return SWIG_Python_ConvertPtr(obj, ptr, swigType, SWIG_POINTER_EXCEPTION) != -1;
}

%}


#if SWIG_VERSION < 0x010328
%{
// Make a SWIGified pointer object suitable for a .this attribute
PyObject* RheiaPythonWorkspaceMakeSwigPtr(void* ptr, const wxString& className) {
    
    PyObject* robj = NULL;

    swig_type_info* swigType = RheiaPythonWorkspaceFindSwigType(className);
    wxCHECK_MSG(swigType != NULL, NULL, wxT("Unknown type in RheiaPythonWorkspaceMakeSwigPtr"));

#ifdef SWIG_COBJECT_TYPES
    robj = PySwigObject_FromVoidPtrAndDesc((void *) ptr, (char *)swigType->name);
#else
    {
        char result[1024];
        robj = SWIG_PackVoidPtr(result, ptr, swigType->name, sizeof(result)) ?
            PyString_FromString(result) : 0;
    }
#endif
    return robj;
}
%}

#else // SWIG_VERSION >= 1.3.28
%{
// Make a SWIGified pointer object suitable for a .this attribute
PyObject* RheiaPythonWorkspaceMakeSwigPtr(void* ptr, const wxString& className) {
    
    PyObject* robj = NULL;

    swig_type_info* swigType = RheiaPythonWorkspaceFindSwigType(className);
    wxCHECK_MSG(swigType != NULL, NULL, wxT("Unknown type in RheiaPythonWorkspaceMakeSwigPtr"));

    robj = PySwigObject_New(ptr, swigType, 0);
    return robj;
}
%}
#endif



%{    
// Python's PyInstance_Check does not return True for instances of new-style
// classes.  This should get close enough for both new and old classes but I
// should re-evaluate the need for doing instance checks...
bool RheiaPythonWorkspaceInstance_Check(PyObject* obj) {
    return PyObject_HasAttrString(obj, "__class__") != 0;
}


// This one checks if the object is an instance of a SWIG proxy class (it has
// a .this attribute, and the .this attribute is a PySwigObject.)
bool RheiaPythonWorkspaceSwigInstance_Check(PyObject* obj) {
    static PyObject* this_str = NULL;
    if (this_str == NULL)
        this_str = PyString_FromString("this");
    
    PyObject* this_attr = PyObject_GetAttr(obj, this_str);
    if (this_attr) {
        bool retval = (PySwigObject_Check(this_attr) != 0);
        Py_DECREF(this_attr);
        return retval;
    }

    PyErr_Clear();
    return false;
}


// Export a C API in a struct.  Other modules will be able to load this from
// the wx._core_ module and will then have safe access to these functions,
// even if they are located in another shared library.
static RheiaPythonCoreAPI API = {

    RheiaPythonWorkspaceCheckSwigType,
    RheiaPythonWorkspaceConstructObject,
    RheiaPythonWorkspaceConvertSwigPtr,
    RheiaPythonWorkspaceMakeSwigPtr
};

%}




%init %{
    // Make our API structure a CObject so other modules can import it
    // from this module.
    PyObject* cobj = PyCObject_FromVoidPtr(&API, NULL);
    PyDict_SetItemString(d,"_RheiaPythonWorkspaceAPI", cobj);
    Py_XDECREF(cobj);
%}

//---------------------------------------------------------------------------

