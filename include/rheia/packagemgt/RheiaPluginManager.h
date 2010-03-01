/**
*   @file RheiaPluginManager.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 25-November-2009
*       Changes : Commentaries and addaptation accordingly to the RheiaPackageManager
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaPluginManager_h_
#define RheiaPluginManager_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <RheiaManager.h>

#include <vector>

#include <wx/event.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/string.h>
#include <wx/dynlib.h>

/* lib xml2 imports */
typedef struct _xmlDoc xmlDoc;

/* Rheia imports */
class RheiaPlugin;
class RheiaEvent;
class RheiaConfigurationPanel;
class RheiaPluginManifest;
struct RheiaDynamicLibrary;

/* wxWidgets imports */
class wxMenu;
class wxMenuBar;

/*! A plugin is a dynamic library, that must provide the application with 3
* functions for getting the version, creating the thred and deleting the thread
* This is used to manage plugins by the PluginManager
*/
typedef RheiaPlugin*(*CreatePluginProcess)();

/*! A plugin is a dynamic library, that must provide the application with 3
* functions for getting the version, creating the thred and deleting the thread
* This is used to manage plugins by the PluginManager
*/
typedef void(*FreePluginProcess)(RheiaPlugin*);

/*! @brief Plugin Registration structure */
struct RheiaPluginRegistration
{
	RheiaPluginRegistration() : createProcess(0), freeProcess(0), info(NULL), plugin(NULL), dylib(NULL) {}
	RheiaPluginRegistration(const RheiaPluginRegistration& rhs)
		: name(rhs.name),
		createProcess(rhs.createProcess),
		freeProcess(rhs.freeProcess),
		info(rhs.info),
		plugin( rhs.plugin ),
		dylib(rhs.dylib)
	{}
	wxString name;
	CreatePluginProcess createProcess;
	FreePluginProcess freeProcess;
	RheiaPluginManifest* info;
	RheiaPlugin* plugin;
	RheiaDynamicLibrary* dylib;
};

/*! define the RheiaPluginRegistrationTable */
typedef std::vector< RheiaPluginRegistration > RheiaPluginRegistrationTable;

/** define a plugin array using wxWidgets macros */
WX_DEFINE_ARRAY(RheiaPlugin*, RheiaPluginsArray);

/**
*	@class RheiaPluginManager
*
*	@brief The RheiaPluginManager class manages plugins that can be added to the application
*	during run time and during the initialisation time.
*
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
**/

class PMGT_DLLEXPORT RheiaPluginManager : public wxEvtHandler, public Mgr<RheiaPluginManager>
{
	/** Give Mgr access to our private members */
	friend class Mgr<RheiaPluginManager>;

	/** Give RheiaManager access to our private memebers */
	friend class RheiaManager;

public :

	/********************************************************************************************
	*	METHODS
	********************************************************************************************/
	/**
	*   This will create the plugins menu, in order to manage plugins configurations and informations
	*	@param menuBar The menubar in which to create the Plugins Menu;
	*/
	void CreateMenu(wxMenuBar* menuBar);

	/**
	*   This will destroy the plugins menu and remove it from the given menu bar
	*	@param menuBar the menubar in which to remove the plugins menu
	*/
    void ReleaseMenu(wxMenuBar* menuBar);

	/**
	*   Loads a specific plugin by its name
	*	@param pluginName The plugin's name to load
	*	@param pluginInfo The plugin's loading information to load
	*/
	bool LoadPlugin(const wxString& pluginName );

	/**
	*   Loads a specific plugin by its name
	*	@param pluginName The plugin's name to load
	*	@param pluginInfo The plugin's loading information to load
	*/
	bool LoadLibrary(const wxString& fileName );

	/*! This will load all the available plugins */
	void LoadAllPlugins();

	/*! This will unload all the available plugins */
	void UnloadAllPlugins();

	/*! This will unload a specific plugin acordingly to its name */
	void UnloadPlugin(RheiaPluginRegistration* plugin);

	/*! Attach the given plugin to the plugin manager
	*	@param plugin the plugin to attach
	*/
	bool AttachPlugin(RheiaPlugin* plugin);

	/*! Detach the given plugin to the plugin manager
	*	@param plugin the plugin to detach
	*/
	bool DetachPlugin(RheiaPlugin* plugin);

	/*! Register a new plugin
	*	@param pluginInfo RheiaPluginLoadingInfo of the plugin
	*	@param createProc CreatePluginProcess function for the plugin (i.e : to instanciate the plugin)
	*	@param freeProc FreePluginProcess function for the plugin (i.e : to free the plugin)
	*	@param versionProc PluginSDKVersionProcess function for the plugin (i.e : to get the plugin version)
	*
	*/
	bool RegisterPlugin( const wxString& name,
                            CreatePluginProcess createProc,
                            FreePluginProcess freeProc );

	/*! Exports a specific plugin in a specific file name
	*	@param plugin The plugin to exports
	*	@param filename The file name in which to export the plugin
	*/
	bool ExportPlugin(RheiaPlugin* plugin, const wxString& filename);

	/**
    *   @return True if the plugin should be loaded, false if not.
    */
	RheiaPluginManifest* ReadManifestFile(
        const wxString& pluginFilename
		);

	/*! Gets the RheiaPluginInfo structure for a plugin by its pointer
	*	@param plugin The plugin's pointer to get the info
	*/
	RheiaPluginRegistration* FindElement(RheiaPlugin* plugin);

	/*! Get a plugin element by its name
	*	@param pluginName Plugin's name to get the elements
	*/
	RheiaPluginRegistration* FindElement(const wxString& pluginName);

	/*! Find a plugin by its name
	*	@param pluginName Plugin's name to find
	*/
	RheiaPlugin* FindPlugin(const wxString& pluginName);

	void NotifyPlugins(RheiaEvent& event);

	/*!	Get the array of plugin elements available in the plugin manager for a specific configuration group */
	RheiaPluginRegistrationTable& GetPlugins(int ConfigGroup);

	/**
	*   Get offered plugins for the given configuration group
	*/
	RheiaPluginsArray GetOffersFor( RheiaPluginType type );

private :
	/****************************************************************************************************
	*	CONSTRUCTOR
	****************************************************************************************************/
	/*! Default constructor */
	RheiaPluginManager();

	/*! Destructor */
    ~RheiaPluginManager();

	/****************************************************************************************************
	*	PRIVATE VARIABLES
	****************************************************************************************************/
	RheiaPluginRegistrationTable RegisteredPlugins;						/*!< vector of registrered plugins */

	DECLARE_EVENT_TABLE()
};

/** @brief Plugin registration object.
*
* Use this class to register your new plugin with Rehia
* All you have to do is instantiate a RheiaPluginRegistrant object.
* @par
* Example code to use in one of your plugin's source files (supposedly called "MyPlugin"):
* @code
* namespace
* {
*     RheiaPluginRegistrant<MyPlugin> registration("MyPlugin");
* }
* @endcode
*/
template<class T> class RheiaPluginRegistrant
{
public:
	/*! Base constructor
	*	@param name The plugin's name.
	*/
	RheiaPluginRegistrant(const wxString& name)
	{
		RheiaPluginManager::Get()->RegisterPlugin(name,
			&CreatePlugin,
			&FreePlugin );
	}

	/*! Function for creating the plugin */
	static RheiaPlugin* CreatePlugin()
	{
		return new T;
	}

	/*! Function for freeing the plugin
	*	@param plugin the plugin to free
	*/
	static void FreePlugin(RheiaPlugin* plugin)
	{
		delete plugin;
	}

};

#endif
