/**
*   @file RheiaPythonUtils.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	27-January-2010
*	@version 0.0.2
*/
#ifndef RheiaPythonUtils_h_
#define RheiaPythonUtils_h_

#include <RheiaPythonSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <wx/event.h>
#include <map>

#include <Python.h>

class PYTHON_DLLEXPORT RheiaPythonUtils : public wxEvtHandler, public Mgr<RheiaPythonUtils>
{
    /** Give our private member access to Mgr */
	friend class Mgr<RheiaPythonUtils>;

	/** Give our private member access to RheiaManager */
	friend class RheiaManager;

public :
    /**********************************************************************************************************
	*	METHODS
	**********************************************************************************************************/

	/**
	*   This method is used once in order to initialize the python interface usgin python tools
	*   It will push in the python runtime the different instance of managers and RheiaCreated objects.
	*   Objects available there will be RheiaManager, RheiaPluginManager, RheiaCenterPaneManager, RheiaWorkspaceManager
	*   RheiaInfoPaneManager, RheiaToolBarManager, RheiaMenuManager, RheiaProjectManager, RheiaLoggerManager...
	*   You can use this instances in yout python code in order to interact with the application...
	*   Have fun !
	*/
	void PythonInit();

	/** Stop the python support in rheia */
	void PythonExit();

	/**
	*   Execute a python string in the python interface
	*/
	bool PythonExecuteCommand( const wxString& command , bool file = false , wxString errorMsg = wxEmptyString );

	/**
	*   Execute a python string in the python interface
	*/
	bool PythonExecuteCommandSafe( const wxString& command , bool file = false );

	/**
	*   Evaluate the given string and retrun the result as string in the
	*   given argument
	*/
	bool PythonEvalString( const wxString& command, wxString& result , int flag );

	/** Get the flag from the given command */
	int PythonGetFlagFromString( const wxString& command );

	/** check if the given string shall be executed */
	bool ShallExecuteCommand( const wxString& command , int nolines );

	/**
	*   Get the python traceback module output
	*/
	wxString PythonGetTraceback();

	/** Get the error from python */
	bool PythonGetError( wxString& className , wxString& errorText );

	/** Get the type of the given object */
	wxString PythonGetType( PyObject* obj );

	/** return the object as string */
	wxString PyObjectToWxString( PyObject* object );

	/** Get a variable from the python main */
	wxString PythonGetVariable( const wxString& name );

	/** Specify if the engine is running or not */
	bool HasPythonSupport() {return hasPythonSupport;};

	/** Set the exception object */
	void SetException();

	/** Unset the exception object */
	void UnsetException();

	/** get default paths as a wxArrayString */
	wxArrayString GetDefaultPaths() {return m_defaultPaths; };

	/** get the user defined paths */
	wxArrayString GetUserDefinedPaths() {return m_paths; }

	/** load the default paths */
	wxArrayString LoadDefaultPaths();

	/** load the user defined paths */
	wxArrayString LoadPaths();

	/** save the user defined paths */
	void SavePaths();

	/** Add a path in the path list */
	void AddPath( const wxString& path );

	/** Remove a path from the path list */
	void RemovePath( const wxString& path );

	/** Remove a path from the path list by index */
	void RemovePathByIndex( int index );

private :
    /**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaPythonUtils::Get() to get the global instance of this class.
	*/
	RheiaPythonUtils();

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaPythonUtils::Free() to do this. However you may NEVER
	*   call RheiaPythonUtils::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	~RheiaPythonUtils();

private :
    /**********************************************************************************************************
	*	PRIVATE MEMBERS
	**********************************************************************************************************/
	PyObject* m_mainModule;
	PyObject* m_mainDict;
	PyThreadState* m_mainTState;
	wxArrayString m_keywords;

	bool hasPythonSupport;
	wxArrayString m_defaultPaths;
	wxArrayString m_paths;
};

#endif
