/**
*	@file RheiaEnvironementManager.h
*
*   Revision : 20-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries and MacOSX version
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#ifndef RheiaEnvironementManager_h_
#define RheiaEnvironementManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaManager.h>
#include <RheiaEventFrame.h>

#include <wx/event.h>
#include <map>

/* wxWidgets imports */
class wxFrame;
class wxMenuBar;

/** define a map of strings */
typedef std::map< wxString , wxString > RheiaStringStringMap;

/**
*	@class RheiaEnvironementManager
*
*   RheiaEnvironement Manager is the singleton class that can be used to register/unregister, add/remove
*   application's local Environement Variables.
*
*   Environment variables in Rheia are setted at the early start up of the application in order to allow
*   any plugin and any libraries to have them defined. You can either define your own environment
*   variable for example if you want to specify specific locations for your own license file or
*   any data folders that can be used by your plugin. Or you can specify some data path added to
*   the global environment path variables PATH under Windows, LD_LIBRARY_PATH under Linux like
*   systems and DYLD_LIBRARY_PATH under MacOS X.
*
*   Unfortunatly, these variables are not relly setted as we need to set it before application starts.
*   However they will be availble for any child processes luacnhed by the application.
*   You can register at any time new environment variable and remember that they are saved between
*   two applications run so you do not have to do it at any time you attach or load a plugin.s
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaEnvironementManager : public wxEvtHandler , public Singleton<RheiaEnvironementManager>
{
    /** give RheiaManager our private memebers access */
    friend class RheiaManager;

    /** give Singleton our private members access */
    friend class Singleton<RheiaEnvironementManager>;

public :
    /******************************************************************************************************
    *   MENU METHODS
    ******************************************************************************************************/
    /** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( RheiaManagedFrame* parent, wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( RheiaManagedFrame* parent , wxMenuBar* menuBar );

	/** Callback used when the user want to manage environment variables */
	void OnManageEnvironmentVariables(wxCommandEvent& event);

    /******************************************************************************************************
    *   ACCESSORS FOR ENVIRONEMENT VARIABLES
    ******************************************************************************************************/
    /**
    *   Add the given environement variable and call wxSetEnv
    *   @param name variable name (i.e : Environement shorcut ex : HOME for the home variable)
    *   @param value variable value (i.e : path pointed by the variable, ex : /home/nicolas for my $HOME)
    *   @return true if the variable has been added in the manager
    */
    bool Add( const wxString& name , const wxString& value );

    /**
    *   Change the given environement variable and call wxSetEnv
    *   @param name variable name (i.e : Environement shorcut ex : HOME for the home variable)
    *   @param value variable value (i.e : path pointed by the variable, ex : /home/nicolas for my $HOME)
    *   @return true if the variable has been added in the manager
    */
    bool Change( const wxString& name , const wxString& value );

    /**
    *   Removes the given environement variable by its name
    *   @param name variable name (i.e : Environement shorcut ex : HOME for the home variable)
    *   @return true if the variable has been removed from the manager
    */
    bool Remove( const wxString& name );

    /**
    *   Find a variable by its name
    *   @param name variable name (i.e : Environement shorcut ex : HOME for the home variable)
    *   @return variable value (i.e : path pointed by the variable, ex : /home/nicolas for my $HOME) or
    *   empty string if the variable has not been found
    *
    *   @note this function will first look in the manager for registering environement variables and
    *   if not found will get wxGetEnv in order to check for a globally existing environement variable.
    */
    wxString FindVariableByName( const wxString& name );

    /**
    *   Check if the given environement variable exists in this manager
    *   @param name variable name (i.e : Environement shorcut ex : HOME for the home variable)
    *   @return true if the variable exists
    */
    bool Exists( const wxString& name );

    /** Get the variables map */
    const RheiaStringStringMap& GetVariables() {return m_envars;};

    /** Clear the variables list */
    void Clear() {m_envars.clear();};

    /******************************************************************************************************
    *   ACCESSORS FOR ENVIRONEMENT LIBRARY PATHS
    ******************************************************************************************************/
    /**
    *   Add the given library path and set the new library path
    *   with set env
    *   @param path path to add to the global library path
    *   @return true if the path has been added properly
    */
    bool AddPath( const wxString& path );

    /**
    *   Remove the given library path
    *   @param path path to remove from the global library path
    *   @return true if the path has been removed properly
    */
    bool RemovePath( const wxString& path );

    /**
    *   Check if the given environement variable exists in this manager
    *   @param name variable name (i.e : Environement shorcut ex : HOME for the home variable)
    *   @return true if the variable exists
    */
    bool PathExists( const wxString& path );

    /** Clear the variables list */
    void ClearPaths() {m_libpaths.Clear();};

    /** Get the paths list */
    wxArrayString& GetPathsList() {return m_libpaths;};

    /** Callback used when the user want to manage environment variables */
	void OnCloseFrame(RheiaFrameEvent& event);

private :
    /******************************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ******************************************************************************************************/
    /** default constructor */
    RheiaEnvironementManager();

    /** default desstructor */
    ~RheiaEnvironementManager();

private :

    RheiaStringStringMap m_envars;
    wxArrayString m_libpaths;
    RheiaManagedFrameIdMap m_frameIds;

#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};
#endif
