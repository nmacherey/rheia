/**
*	@file RheiaPlugin.h
*
*   Revision : 15-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries and data structure
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 03-Dec-2008
*	@version 0.0.1
*/
#ifndef RheiaPlugin_h_
#define RheiaPlugin_h_

#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaPluginManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaPMgtSettings.h>

/* Define basic groups for plugins' configuration. */
static const int RhCore									= 0x01; /*!< Core plugins ( inside the box ) ! */
static const int RhEnvironment					        = 0x02; /*!< Workspace plugins */
static const int RhEnvironmentCore		                = 0x03; /*!< Workspace attachable plugins */
static const int RhContrib							    = 0x04; /*!< Contrib Plugins */
static const int RhUnknown						        = 0x05; /*!< Unknown */

class RheiaConfigurationPanel;
class RheiaPluginAddOn;

class RheiaPluginAddOn{

};

/**
*	@class RheiaPlugin
*	@brief RheiaPlugin is the model of plug-ins class that can be attached to Rheia
*
*	A plugin is an object that can be attached to Rheia. Hence it as to define a set of
*	method to enable its management in Rheia.
*
*	Any plugin is first built as object instance but this will not necessarily give access to it.
*	A plugin must be attached. When a plugin is attached the Attach() method calls the OnAttach()
*	one that you can derive if you want to do specific initialisations in your plugin.
*
*	A plugin can add menu, frames, tool bars and log windows in Rheia. The set of functions enables
*	to plugin to do so.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 03-Dec-2008
*	@version 0.0.1
*/
class PMGT_DLLEXPORT RheiaPlugin : public wxEvtHandler
{
public:
	/*******************************************************************************************
	*	CONSTRUCTORS
	*******************************************************************************************/
	/*! Default constructor */
	RheiaPlugin();

	/*! Default destructor. */
	virtual ~RheiaPlugin();

	/*******************************************************************************************
	*	METHODS
	*******************************************************************************************/
	/*! Returns the plugin's type  */
	virtual RheiaPluginType GetType() const { return Type; };

	/*! If a plugin provides some sort of configuration dialog,
	*	this is the place to invoke it.
	*/
	virtual int Configure(){ return 0; };

	/*! Return the configuration group for this plugin. Default is RheiaUnknown.
	* Notice that you can logically AND more than one configuration groups,
	* so you could set it, for example, as "RheiaWorkspace | RheiaContrib".
	*/
	virtual int GetConfigurationGroup() const { return RhUnknown; }

	/**
	*		Return the namesapce in which the plugin is active
	*		Overload this methods to change this.
	*/
	virtual const wxString GetNamespaceView() const { return wxT("default") ;};

	/*! Return plugin's configuration panel.
	*	@param parent The parent window.
	*	@return A pointer to the plugin's RheiaConfigurationPanel. It is deleted by the caller.
	*/
	virtual RheiaConfigurationPanel* GetConfigurationPanel(wxWindow* parent){ return 0; }

	/*! See whether this plugin is attached or not. A plugin should not perform
	* any of its tasks, if not attached...
	* @note This function is *not* virtual.
	* @return Returns true if it attached, false if not.
	*/
	bool IsAttached() const { return isAttached; }

	/*! See whether this plugin can be detached (unloaded) or not.
	* This function is called usually when the user requests to
	* uninstall or disable a plugin. Before disabling/uninstalling it, Code::Blocks
	* asks the plugin if it can be detached or not. In other words, it checks
	* to see if it can be disabled/uninstalled safely...
	* @par
	* A plugin should return true if it can be detached at this moment, false if not.
	* @return The default implementation returns true.
	*/
	virtual bool CanDetach() const { return true; }

	/*! This method is called by Rehia and is used by the plugin
	* to add any toolbar items it needs on Rehia toolbar.\n
	* It is a pure virtual method that needs to be implemented by all
	* plugins. If the plugin does not need to add items on the toolbar,
	* just do nothing ;)
	* @param toolBar the wxToolBar to create items on
	* @return The plugin should return true if it needed the toolbar, false if not
	*/
	virtual bool BuildToolBar(wxToolBar* toolBar) = 0;

	/*! This method is called by Rheia and is used by the plugin
	* to add any menu items it needs on Rheia's menu bar.\n
	* It is a pure virtual method that needs to be implemented by all
	* plugins. If the plugin does not need to add items on the menu,
	* just do nothing ;)
	*
	* @note This function may be called more than one time. This can happen,
	* for example, when a plugin is installed or uninstalled.
	*
	* @param menuBar the wxMenuBar to create items in
	*/
	virtual void BuildMenu(wxMenuBar* menuBar) = 0;

    /** get the corresponding addon for the plugin */
    virtual RheiaPluginAddOn* GetPluginAddOn() {return 0L;};

protected:
	/*! Any descendent plugin should override this virtual method and
	* perform any necessary initialization. This method is called by
	* Rheia (RheiaPluginManager actually) when the plugin has been
	* loaded and should attach in Rheia. When Rheia
	* starts up, it finds and <em>loads</em> all plugins but <em>does
	* not</em> activate (attaches) them. It then activates all plugins
	* that the user has selected to be activated on start-up.\n
	* This means that a plugin might be loaded but <b>not</b> activated...\n
	* Think of this method as the actual constructor...
	*/
	virtual void OnAttach(){};

	/*! Any descendent plugin should override this virtual method and
	* perform any necessary de-initialization. This method is called by
	* Rheia (RheiaPluginManager actually) when the plugin has been
	* loaded, attached and should de-attach from Rheia.\n
	* Think of this method as the actual destructor...
	* @param appShutDown If true, the application is shutting down. In this
	*         case *don't* use RheiaManager::Get()->Get...() functions or the
	*         behaviour is undefined...
	*/
	virtual void OnRelease(bool appShutDown){}

	/*! Holds the plugin's type. Set in the default constructor. */
	RheiaPluginType Type;

	/** Holds the "attached" state. */
	bool isAttached;

private:
	friend class RheiaPluginManager; // only the plugin manager has access here

	/*! Attach is <b>not</b> a virtual function, so you can't override it.
	*/
	void Attach();

	/** Release is <b>not</b> a virtual function, so you can't override it.
	* The default implementation un-hooks the plugin from GraymatBox's
	* event handling system. Use OnRelease() for any clean-up specific
	* tasks.
	* @param appShutDown If true, the application is shutting down. In this
	*         case *don't* use RheiaManager::Get()->Get...() functions or the
	*         behaviour is undefined...
	* @see OnRelease()
	*/
	void Release(bool appShutDown);
};

#endif
