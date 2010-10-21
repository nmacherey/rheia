/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
#include <RheiaEventFrame.h>
#include <RheiaEventsManager.h>

#include <vector>
#include <map>

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
typedef RheiaPlugin*(*CreatePluginProcess)(RheiaManagedFrame*);

/*! A plugin is a dynamic library, that must provide the application with 3
* functions for getting the version, creating the thred and deleting the thread
* This is used to manage plugins by the PluginManager
*/
typedef void(*FreePluginProcess)(RheiaPlugin*);

#ifndef SWIG
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
#endif
/** define a plugin array using wxWidgets macros */
WX_DEFINE_ARRAY(RheiaPlugin*, RheiaPluginsArray);

/** define a map of plugins that will be used in a frame */
typedef std::map < wxString , RheiaPlugin* > RheiaPluginMap;

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

class PMGT_DLLEXPORT RheiaPluginManager : public wxEvtHandler, public Singleton<RheiaPluginManager>
{
	/** Give Singleton access to our private members */
	friend class Singleton<RheiaPluginManager>;

	/** Give RheiaManager access to our private memebers */
	friend class RheiaManager;
	
	/** Give RheiaFramePluginManager access to our private members */
	friend class RheiaFramePluginManager;

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

	/**
    *   @return True if the plugin should be loaded, false if not.
    */
	RheiaPluginManifest* ReadManifestFile(
        const wxString& pluginFilename
		);
	
	/*! Gets the RheiaPluginInfo structure for a plugin by its pointer
	*	@param plugin The plugin's pointer to get the info
	*/
	RheiaPluginRegistration* FindElement(const wxString& name);
	
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

#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};

/**
 * @class RheiaFramePluginManager
 * @brief Main class for handling plugins in a Rheia Managed Frame
 * This class is the one that must be used in order to associate plugins 
 * in a Rheia Managed Frame
 */
class PMGT_DLLEXPORT RheiaFramePluginManager : public wxEvtHandler , public RheiaMgr< RheiaManagedFrame , RheiaFramePluginManager >
{
	/** give RheiaMgr< RheiaManagedFrame , RheiaFramePluginManager > our private member access */
	friend class RheiaMgr< RheiaManagedFrame , RheiaFramePluginManager >;
	
	/** give RheiaPluginManager our private members access */
	friend class RheiaPluginManager;

public :

	/** 
	 * This will load all the available plugins 
	 * Plugins must have been previously registered in RheiaPluginManager
	 * This method is a helper method to help you in associating registered
	 * plugins to a RheiaManagedFrame.
	 */
	void LoadAllPlugins();

	/** 
	 * This will unload all the available plugins 
	 * This will simply free all plugin instances registered in
	 * this manager instance and return.
	 */
	void UnloadAllPlugins();
	
	/**
	 * Load a specific plugin accordingly to it's name 
	 * @param name plugin name to load
	 * @return false if the plugin was not loaded properly
	 */
	bool LoadPlugin(const wxString& name);
	
	/**
	 * Unload a the given plugin
	 * @param name plugin to unload
	 * @return false if the was not unloaded properly
	 */
	bool UnloadPlugin( const wxString& name );
	
#ifndef SWIG
	/*!	Get the array of plugin elements available in the plugin manager for a specific configuration group */
	RheiaPluginsArray& GetPlugins(int ConfigGroup);
#endif

	/**
	*   Get offered plugins for the given configuration group
	*/
	RheiaPluginsArray GetOffersFor( RheiaPluginType type );
	
	/*! Find a plugin by its name
	*	@param pluginName Plugin's name to find
	*/
	RheiaPlugin* FindPlugin(const wxString& pluginName);

	/** Process the given event in the parented frame */
	void NotifyPlugins(RheiaEvent& event);
	
	/*! Gets the RheiaPluginInfo structure for a plugin by its pointer
	*	@param plugin The plugin's pointer to get the info
	*/
	RheiaPluginRegistration* FindElement(RheiaPlugin* plugin);

#ifdef SWIG
	%rename(FindElementByName) FindElement(const wxString& pluginName);
#endif
	/*! Get a plugin element by its name
	*	@param pluginName Plugin's name to get the elements
	*/
	RheiaPluginRegistration* FindElement(const wxString& pluginName);

private:

    /****************************************************************************************************
	*	EVENTS CALLBACKS
	****************************************************************************************************/
    
    /** The next event is used when the parented frame of this manager is 
    * going to be closed, we need to detach all plugins... 
    */
    void OnCloseParent( RheiaFrameEvent& event );

	/****************************************************************************************************
	*	CONSTRUCTOR
	****************************************************************************************************/
	/** Default constructor,
	 * As many other managers in Rheia, you cannot build directly this
	 * manager you have to use the RheiaFramePluginManager::Get(frame) passing
	 * your RheiaManagedFrame instance to get the global instance of this manager
	 * associated to the frame instance you need to interact with.
	 */
	RheiaFramePluginManager(RheiaManagedFrame* parent);

	/** Destructor 
	 * You cannot directly destroy an instance of this class,
	 * you have to use RheiaFramePluginManager::Free(frame) passing
	 * your RheiaManagedFrame instance to destroy the global instance of this manager
	 * associated to the frame instance you want. After a call to RheiaFramePluginmanager::Free
	 * all plugins associated to the frame will removed from the frame.
	 * usually unless you are a Rheia core developer you might never have 
	 * to deal with the RheiaFramePluginManager::Free() method.
	 */
    ~RheiaFramePluginManager();

	/** attribute that store all plugins associated to the frame */
	RheiaPluginMap m_plugins;
	
	/** managed parent associated to this instance */
	RheiaManagedFrame* m_parent;
};

#ifndef SWIG
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
	static RheiaPlugin* CreatePlugin(RheiaManagedFrame* parent)
	{
		return new T(parent);
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

#endif
