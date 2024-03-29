/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPythonUtils.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	27-January-2010
*	@version 0.0.2
*/
#include <wx/xrc/xmlres.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/msgdlg.h>
#include <wx/aui/aui.h>

#include <RheiaManager.h>
#include <RheiaEvents.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaMenuManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaProfileManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEnvironementManager.h>
#include <RheiaPersonalityManager.h>
#include <RheiaProfileManager.h>
#include <RheiaXmlManager.h>
#include <RheiaEventsManager.h>

#include <RheiaPythonUtils.h>

#include <Python.h>
#include <node.h>
#include <errcode.h>
#include <grammar.h>
#include <parsetok.h>
#include <compile.h>
#include <object.h>
#include <compile.h>
#include <eval.h>

#include <Python.h>
#include <wx/wxPython/wxPython.h>

#include "RheiaPython.h"

extern grammar _PyParser_Grammar; /* From graminit.c */

/*! declare global instance for the RheiaPythonUtils */
template<> RheiaPythonUtils* Singleton<RheiaPythonUtils>::instance = 0;
/*! declare global isShutdown for the RheiaPythonUtils */
template<> bool  Singleton<RheiaPythonUtils>::isShutdown = false;

namespace
{
    const wxString keywords0 = _("class def elif else for from if import help print "
                "while __import__ __dict__ __class__ __bases__ __name__ =");
}

RheiaPythonUtils::RheiaPythonUtils()
{
    m_mainModule = NULL;
    m_mainDict = NULL;
    hasPythonSupport = false;
}

RheiaPythonUtils::~RheiaPythonUtils()
{
    if( hasPythonSupport )
        PythonExit();
}

void RheiaPythonUtils::PythonInit()
{
    // initialize python
    Py_Initialize();
    PyEval_InitThreads();

    // Save the current Python thread state and release the
    // Global Interpreter Lock.
    //m_mainTState = Py_NewInterpreter();

    hasPythonSupport = true;

    m_mainModule = PyImport_AddModule( "__main__" );
    assert(m_mainModule);
    Py_INCREF(m_mainModule);

    m_mainDict = PyModule_GetDict( m_mainModule );
    assert(m_mainDict);
    Py_INCREF(m_mainDict);

    PyDict_SetItemString(m_mainDict, "__builtins__", PyEval_GetBuiltins());

    //m_mainTState = wxPyBeginAllowThreads();


    wxString command = wxT("sys.path = [\"");
    command += wxT("\", \"") ;

    LoadPaths();
    LoadDefaultPaths();

    for( unsigned int i = 0; i < m_defaultPaths.GetCount(); ++i )
    {
        if( i < m_defaultPaths.GetCount() -1 )
            command += m_defaultPaths[i] + wxT("\", \"");
        else
            command += m_defaultPaths[i];
    }

    if( m_paths.GetCount() != 0 )
        command += wxT("\", \"");

    for( unsigned int i = 0; i < m_paths.GetCount(); ++i )
    {
        if( i < m_paths.GetCount() -1 )
            command += m_paths[i] + wxT("\", \"");
        else
            command += m_paths[i];
    }

    command += wxT("\"] + sys.path");

    PythonExecuteCommand( wxT("import sys") ); // import sys module (for display / exception hooks)
    PythonExecuteCommand( wxT("import traceback") ); // for formatting stack traces
    PythonExecuteCommand( wxT("import __main__") ); // to access explicitly global variables
    PythonExecuteCommand( command );
	
	//ImportWxPythonAPI();
	//if( !ImportRheiaPythonAPI() )
	//	wxMessageBox(wxT("damn") );
	//
	//PythonExecuteCommand( wxT("import rheia") ); // import sys module (for display / exception hooks)
	//PythonExecuteCommand( wxT("pluginmgr = rheia.pyPluginMgr.RheiaPythonPluginManager()") ); // import sys module (for display / exception hooks)
	//PythonExecuteCommand( wxT("rheia.pyPluginMgr.s_plugins['toto'] = 'maman'") );
	//
 //   PythonExecuteCommand(
 //       _("def rheia_exception_msg(type, value, tb, msg):\n"
 //           "  lst = traceback.format_exception(type, value, tb)\n"
 //           "  if msg == None: msg = 'An error has occured while executing Python code'\n"
 //           "  txt = ''\n"
 //           "  for s in lst:\n"
 //           "    txt += s\n"
 //           "  txt += 'Python version: ' + sys.version + '\\n\\n' \n"
 //           "  txt += 'Python path: ' + str(sys.path) + '\\n\\n' \n"
 //           "  \n"
 //           "  wx.MessageBox( txt , 'ERROR' )" ) );
 //   PythonExecuteCommand(
 //       _("def rheia_exception(type, value, tb):\n"
 //           "  rheia_exception_msg(type, value, tb, None)\n" ) );

 //   // hook for python console so all output will be redirected
 //   // and then shown in console
 //   command =  wxT("def console_display_hook(obj):\n");
 //   command += wxT("   __main__.__result = obj\n");

 //   PythonExecuteCommand( command );
}

void RheiaPythonUtils::PythonExit()
{
    // Restore the thread state and tell Python to cleanup after itself.
    // wxPython will do its own cleanup as part of that process.  This is done
    // in OnExit instead of ~MyApp because OnExit is only called if OnInit is
    // successful.
    //wxPyEndAllowThreads(m_mainTState);
    Py_Finalize();
    m_mainModule = NULL;
    m_mainDict = NULL;
    hasPythonSupport = false;
}

void RheiaPythonUtils::SetException()
{
    //PythonExecuteCommand( wxT("sys.excepthook = rheia_exception") );
}

void RheiaPythonUtils::UnsetException()
{
    //PythonExecuteCommand( wxT("sys.excepthook = sys.__excepthook__") );
}

bool RheiaPythonUtils::PythonExecuteCommandSafe( const wxString& command , bool file )
{
    // First, whenever you do anything with Python objects or code, you
    // *MUST* aquire the Global Interpreter Lock and block other
    // Python threads from running.
    //wxPyBlock_t blocked = wxPyBeginBlockThreads();

    //PyEval_AcquireThread(m_mainTState);
    PyRun_String( command.ToUTF8().data() , file ? Py_file_input : Py_single_input, m_mainDict, m_mainDict );

    // Finally, release the GIL and let other Python threads run.
    //wxPyEndBlockThreads(blocked);
    return ( PyErr_Occurred() == 0 );
}

bool RheiaPythonUtils::PythonExecuteCommand( const wxString& command , bool file , wxString errorMsg )
{
    if( PythonExecuteCommandSafe( command , file ) )
        return true;

    if( errorMsg.IsEmpty() )
        errorMsg = wxT( "An error occured during execution of following code:\n") + command;

    wxString traceback = PythonGetTraceback();
    wxString path,version;

    // As always, first grab the GIL
    //wxPyBlock_t blocked = wxPyBeginBlockThreads();

    PythonEvalString( wxT("str(sys.path)"), path , Py_single_input );
    PythonEvalString( wxT("sys.version"), version , Py_single_input );

    wxString msg = errorMsg;
    msg += wxT("\n\n\t Traceback : \n\n");
    msg += traceback;
    msg += wxT("\n\n\t Python version : \n\n");
    msg += version;
    msg += wxT("\n\n\t Python path : \n\n");
    msg += path;

    wxMessageBox( msg , wxT("Error in RheiaPythonUtils...") );

    // Finally, after all Python stuff is done, release the GIL
    //wxPyEndBlockThreads(blocked);
    return false;
	
	
}

wxString RheiaPythonUtils::PythonGetTraceback()
{
    // As always, first grab the GIL
    //wxPyBlock_t blocked = wxPyBeginBlockThreads();

    wxString result;

    PyObject *moduleStringIO = NULL;
    PyObject *moduleTraceback = NULL;
    PyObject *objectStringIO = NULL;
    PyObject *objectResult = NULL;

    PyObject *type, *value, *traceback;

    PyErr_Fetch( &type, &value, &traceback );
    PyErr_NormalizeException( &type, &value, &traceback );

    moduleStringIO = PyImport_ImportModule( "cStringIO" );
    if ( moduleStringIO == NULL )
    {
        result = wxT("Can't import cStringIO...");
        Py_XDECREF( moduleStringIO );
        Py_XDECREF( moduleTraceback );
        Py_XDECREF( objectStringIO );
        Py_XDECREF( objectResult );
        Py_XDECREF( value );
        Py_XDECREF( traceback );
        Py_XDECREF( type );
         // Finally, after all Python stuff is done, release the GIL
        //wxPyEndBlockThreads(blocked);
        return result;
    }

    objectStringIO = PyObject_CallMethod( moduleStringIO, ( char* ) "StringIO", NULL );

    /* Construct a cStringIO object */
    if ( objectStringIO == NULL )
    {
        result = wxT("cStringIO.StringIO() failed..." );
        Py_XDECREF( moduleStringIO );
        Py_XDECREF( moduleTraceback );
        Py_XDECREF( objectStringIO );
        Py_XDECREF( objectResult );
        Py_XDECREF( value );
        Py_XDECREF( traceback );
        Py_XDECREF( type );
         // Finally, after all Python stuff is done, release the GIL
        //wxPyEndBlockThreads(blocked);
        return result;
    }


    moduleTraceback = PyImport_ImportModule( "traceback" );
    if ( moduleTraceback == NULL )
    {
        result = wxT("Can't import traceback..." );
        Py_XDECREF( moduleStringIO );
        Py_XDECREF( moduleTraceback );
        Py_XDECREF( objectStringIO );
        Py_XDECREF( objectResult );
        Py_XDECREF( value );
        Py_XDECREF( traceback );
        Py_XDECREF( type );
         // Finally, after all Python stuff is done, release the GIL
        //wxPyEndBlockThreads(blocked);
        return result;
    }


    objectResult = PyObject_CallMethod( moduleTraceback, ( char* ) "print_exception",
                                        ( char* ) "OOOOO",
                                        type, value ? value : Py_None,
                                        traceback ? traceback : Py_None,
                                        Py_None,
                                        objectStringIO );

    if ( objectResult == NULL )
    {
        result = wxT("Call to traceback.print_exception() failed..." );
        Py_XDECREF( moduleStringIO );
        Py_XDECREF( moduleTraceback );
        Py_XDECREF( objectStringIO );
        Py_XDECREF( objectResult );
        Py_XDECREF( value );
        Py_XDECREF( traceback );
        Py_XDECREF( type );
         // Finally, after all Python stuff is done, release the GIL
        //wxPyEndBlockThreads(blocked);
        return result;
    }

    Py_DECREF( objectResult );

    objectResult = PyObject_CallMethod( objectStringIO, ( char* ) "getvalue", NULL );

    if ( objectResult == NULL )
    {
        result = wxT("Call to getvalue() failed..." );
        Py_XDECREF( moduleStringIO );
        Py_XDECREF( moduleTraceback );
        Py_XDECREF( objectStringIO );
        Py_XDECREF( objectResult );
        Py_XDECREF( value );
        Py_XDECREF( traceback );
        Py_XDECREF( type );
         // Finally, after all Python stuff is done, release the GIL
        //wxPyEndBlockThreads(blocked);
        return result;
    }


    /* And it should be a string all ready to go - duplicate it. */
    if ( !PyString_Check( objectResult ) )
    {
        result = wxT("getvalue() did not return a string" );
        Py_XDECREF( moduleStringIO );
        Py_XDECREF( moduleTraceback );
        Py_XDECREF( objectStringIO );
        Py_XDECREF( objectResult );
        Py_XDECREF( value );
        Py_XDECREF( traceback );
        Py_XDECREF( type );
         // Finally, after all Python stuff is done, release the GIL
        //wxPyEndBlockThreads(blocked);
        return result;
    }

    result = PyObjectToWxString( objectResult );

    Py_XDECREF( moduleStringIO );
    Py_XDECREF( moduleTraceback );
    Py_XDECREF( objectStringIO );
    Py_XDECREF( objectResult );
    Py_XDECREF( value );
    Py_XDECREF( traceback );
    Py_XDECREF( type );

     // Finally, after all Python stuff is done, release the GIL
    //wxPyEndBlockThreads(blocked);
    return result;
}


wxString RheiaPythonUtils::PyObjectToWxString( PyObject* object )
{
    wxString result;

    // is it None?
    if ( object == Py_None )
    {
        return wxEmptyString;
    }

    // check whether the object is already a unicode string
    if ( PyUnicode_Check( object ) )
    {
        PyObject* utf8 = PyUnicode_AsUTF8String( object );
        if ( utf8 )
            result = wxString::FromUTF8( PyString_AS_STRING( utf8 ) );
        else
            result = wxT("(rheia error)");

        Py_XDECREF( utf8 );
        return result;
    }

    // check whether the object is a classical (8-bit) string
    if ( PyString_Check( object ) )
    {
        return wxString::FromUTF8( PyString_AS_STRING( object ) );
    }

    // it's some other type of object:
    // convert object to unicode string (equivalent to calling unicode(object) )

    PyObject* obj_uni = PyObject_Unicode( object ); // obj_uni is new reference
    if ( obj_uni )
    {
        // get utf-8 representation of unicode string (new reference)
        PyObject* obj_utf8 = PyUnicode_AsUTF8String( obj_uni );
        // convert from utf-8 to QString
        if ( obj_utf8 )
            result = wxString::FromUTF8( PyString_AsString( obj_utf8 ) );
        else
            result = wxT("(rheia error)");

        Py_XDECREF( obj_utf8 );
        Py_XDECREF( obj_uni );
        return result;
    }

    // if conversion to unicode failed, try to convert it to classic string, i.e. str(object)
    PyObject* obj_str = PyObject_Str( object ); // new reference
    if ( obj_str )
    {
        result = wxString::FromUTF8( PyString_AS_STRING( obj_str ) );
        Py_XDECREF( obj_str );
        return result;
    }

    return wxT("(rheia error)");
}

int RheiaPythonUtils::PythonGetFlagFromString( const wxString& command )
{
    if( m_keywords.GetCount() == 0 )
    {
        wxString comm = keywords0;

        while(comm.Contains(wxT(" ")))
        {
            wxString temp = comm.BeforeFirst(wxT(' '));

            if( !temp.IsEmpty() )
                m_keywords.Add(temp);

            comm = comm.AfterFirst(wxT(' '));
        }

        if( !comm.IsEmpty() )
            m_keywords.Add(comm);
    }

    bool haskeys = false;

    for(unsigned int i = 0; i < m_keywords.GetCount() ; ++i )
    {
        if( command.Contains( m_keywords[i] ) && !m_keywords[i].IsEmpty() )
        {
            haskeys = true;
            break;
        }
    }

    int flag ;

    if( haskeys )
        flag = Py_file_input;
    else
        flag = Py_eval_input;

    return flag;
}

int RheiaPythonUtils::ShallExecuteCommand( const wxString& command , wxString& error , int nolines )
{	
	PyObject *src;
	PyObject *exc, *val, *trb, obj;
	char *msg = NULL;
	
	src = Py_CompileString (rcU2C(command), "<stdin>", Py_single_input);
	if (NULL != src)
	{
		int ret = 1;
		if( command[command.Len() -2] != wxT('\n') && nolines > 1 )
			ret = 0;
			
		Py_XDECREF (src);
		return ret;
	}
	else if (PyErr_ExceptionMatches (PyExc_SyntaxError))
	{
		PyErr_Fetch (&exc, &val, &trb);
		if (PyArg_ParseTuple (val, "sO", &msg, &obj) &&
		!strcmp (msg, "unexpected EOF while parsing")) /* E_EOF */
		{
			Py_XDECREF (exc);
			Py_XDECREF (val);
			Py_XDECREF (trb);
			return 0;
		}
		else
		{
			PyErr_Restore (exc, val, trb);
			error += PythonGetTraceback();
			return -1;
		}
	}
	else
	{
		error += PythonGetTraceback();
		return -1;
	}
}


bool RheiaPythonUtils::PythonEvalString( const wxString& command, wxString& result , int flag )
{	
	char buf[BUFSIZ];
	
	fflush(stdout);
	FILE* stream;
	stream = freopen( "console" , "w+" , stdout);
	
	PyObject *src;
	PyObject *dum;
	src = Py_CompileString (rcU2C(command), "<stdin>", Py_single_input);
	
	if (NULL != src)
	/* compiled just fine - */
	{

		/* so execute it */
		dum = PyEval_EvalCode ((PyCodeObject *)src, m_mainDict, m_mainDict);
		fseek( stream , 0 , SEEK_SET );
		char c;
		int i = 0;
		while ( (c = fgetc(stream)) != EOF )
		{
			buf[i++]=c;
			if( i >= BUFSIZ )
			{
				buf[i-1] = '\0';
				result += RheiaC2U( buf );
				i = 0;
			}	
		}
		if( i != 0 )
		{
			buf[i-1] = '\0';
			result += RheiaC2U( buf );
		}
		
		fclose(stream);
		
		Py_XDECREF (dum);
		Py_XDECREF (src);

		if (PyErr_Occurred ())
		{
			wxString traceback = PythonGetTraceback();
			result.Clear();
			result += traceback;
			return false;
		}
		
		//PyErr_Print ();
		return true;
	}
	else
	{
		fclose(stream);
		wxString traceback = PythonGetTraceback();
		result.Clear();
		result += traceback;
		return false;
	}
	
	fclose(stream);
	return false;
}

bool RheiaPythonUtils::PythonGetError( wxString& className , wxString& errorText )
{
    if ( !PyErr_Occurred() )
        return false;

    PyObject* err_type;
    PyObject* err_value;
    PyObject* err_tb;

    // get the exception information and clear error
    PyErr_Fetch( &err_type, &err_value, &err_tb );

    // get exception's class name
    className = PythonGetType( err_type );

    // get exception's text
    if ( err_value != NULL && err_value != Py_None )
    {
        errorText = PyObjectToWxString( err_value );
    }
    else
        errorText.Clear();

    // cleanup
    Py_XDECREF( err_type );
    Py_XDECREF( err_value );
    Py_XDECREF( err_tb );

    return true;
}

wxString RheiaPythonUtils::PythonGetType( PyObject* obj )
{
    if ( obj == NULL )
        return wxEmptyString;

    if ( PyClass_Check( obj ) )
    {
        return wxString::FromAscii( PyString_AsString((( PyClassObject* )obj )->cl_name ) );
    }
    else if ( PyType_Check( obj ) )
    {
        return wxString::FromAscii((( PyTypeObject* )obj )->tp_name );
    }
    else
    {
        return PyObjectToWxString( obj );
    }
}

wxString RheiaPythonUtils::PythonGetVariable( const wxString& name )
{
    PyObject* obj;
    wxString output;

    // get the result
    obj = PyDict_GetItemString( m_mainDict, rcU2C(name) ); // obj is borrowed reference

    if ( obj != NULL && obj != Py_None )
    {
        output = PyObjectToWxString( obj );
    }

    // erase result
    PyDict_SetItemString( m_mainDict, rcU2C(name), Py_None );

    return output;
}

wxArrayString RheiaPythonUtils::LoadDefaultPaths()
{
    m_defaultPaths.Clear();
    m_defaultPaths.Add( RheiaStandardPaths::PluginDirectoryUser() );
    m_defaultPaths.Add( RheiaStandardPaths::PluginDirectoryGlobal() );

    return m_defaultPaths;
}

wxArrayString RheiaPythonUtils::LoadPaths()
{
    m_paths = RheiaManager::Get()->GetConfigurationManager( wxT("RheiaPythonUtils") )->ReadArrayString( wxT("/user_defined_paths") );
    return m_paths;
}

void RheiaPythonUtils::SavePaths()
{
    RheiaManager::Get()->GetConfigurationManager( wxT("RheiaPythonUtils") )->Write( wxT("/user_defined_paths") , m_paths );
}

void RheiaPythonUtils::AddPath( const wxString& path )
{
    int idx = m_paths.Index( path );
    if( idx != wxNOT_FOUND )
        return;

    m_paths.Add( path );
}

void RheiaPythonUtils::RemovePath( const wxString& path )
{
    int idx = m_paths.Index( path );
    if( idx == wxNOT_FOUND )
        return;

    m_paths.RemoveAt( idx );
}

void RheiaPythonUtils::RemovePathByIndex( int index )
{
    if( index >= (int) m_paths.GetCount() )
        return;

    m_paths.RemoveAt( index );
}

bool RheiaPythonUtils::ImportWxPythonAPI()
{
	 // Save the current Python thread state and release the
    // Global Interpreter Lock.
    // Load the wxPython core API.  Imports the wx._core_ module and sets a
    // local pointer to a function table located there.  The pointer is used
    // internally by the rest of the API functions.
    if ( ! wxPyCoreAPI_IMPORT() ) {
        PyErr_Print();
        return false;
    }
	
	return true;
}
	
bool RheiaPythonUtils::ImportRheiaPythonAPI()
{
	if( !RheiaPythonCoreAPI_IMPORT() )
	{
		PyErr_Print();
        return false;
    }
	
	return true;
}

int RheiaPythonUtils::GetPluginsCount()
{
	PyObject* pmgr = PyDict_GetItemString(m_mainDict, "pluginmgr");
	PyObject* meth = PyString_FromString("GetPluginsCount");
    PyObject* res = PyObject_CallMethodObjArgs(pmgr, meth );
	
	int ret = -1;
	if(res)
	{
		ret = PyLong_AsLong(res);
	};
	
	return ret;
}

wxArrayString RheiaPythonUtils::GetPluginsNames()
{
	int count = GetPluginsCount();
	wxArrayString ret;
	
	if( count <= 0 )
		return ret;
	
	PyObject* pmgr = PyDict_GetItemString(m_mainDict, "pluginmgr");
	PyObject* meth = PyString_FromString("GetPluginNameAt");
	
	for( unsigned int i = 0; i < (unsigned int) count ; ++i )
	{
		PyObject* arg = PyLong_FromLong( (long) i );
		PyObject* res = PyObject_CallMethodObjArgs(pmgr, meth , arg ,NULL);
		if(res)
		{
			char* str = PyString_AsString(res);
			wxString result = RheiaC2U(str);
			ret.Add( result );
			Py_DECREF(res);
		}
		Py_DECREF(arg);
	}
	return ret;
}
	