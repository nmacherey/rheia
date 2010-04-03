/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
#include <RheiaManagedFrame.h>
#include <RheiaPluginManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaPMgtSettings.h>

/* Define basic groups for plugins' identification. */
static const int RhCore									= 0x0001; /*!< Core plugins ( inside the box ) ! */
static const int RhContrib							    = 0x0002; /*!< Contrib Plugins */
static const int RhUnknown						        = 0x0004; /*!< Unknown */

/* imports */
class RheiaConfigurationPanel;

/**
*	@class RheiaPlugin
*	@brief RheiaPlugin is the model of plug-ins class that can be attached to Rheia
*
*	A plugin is an object that can be attached to Rheia. Hence it as to define a set of
*	method to enable its management in Rheia.
*
*	Any plugin is first built as object instance but this will not necessarily give access to it.
*	A plugin must be attached. When a plugin is attached the Plug() method calls the OnPlug()
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
	RheiaPlugin(RheiaManagedFrame* parent);

	/*! Default destructor. */
	virtual ~RheiaPlugin();

	/*******************************************************************************************
	*	METHODS
	*******************************************************************************************/
	/*! Returns the plugin's type  */
	virtual RheiaPluginType GetType() const { return Type; };

	/** Return the configuration group for this plugin. Default is RhUnknown.
	* If you want to use Rheia plugin management system in your applications
	* and you need to develop new plugins, you can add your specific group identifier
	* to obtain more flexibility if you want to manage special options for
	* your plugins.
	*/
	virtual int GetGroupIdentifier() const { return RhUnknown; }

	/**
	* 	Return plugin's configuration panel.
	*	@param parent The parent window.
	*	@return A pointer to the plugin's RheiaConfigurationPanel. It is deleted by the caller.
	*/
	virtual RheiaConfigurationPanel* GetConfigurationPanel(wxWindow*){ return 0; }

	/** 
	* See whether this plugin is plugged or not. You might never perform plugin task 
	* in the constructor of the plugin.
	* @note This function is *not* virtual.
	* @return Returns true if it attached, false if not.
	*/
	bool IsPlugged() const { return m_plugged; }

	/**
	* See whether this plugin can be unplugged or not.
	* For example if your plugin handles information not usaually managed 
	* by the application you might want to disable the user to unplug the
	* plugin.
	* This method is only called when the user wants to disable the plugin 
	* from the Installed Softwares Dialog.
	*/
	virtual bool CanUnplug() const { return true; }

	/** 
	* This method is called by Rheia in order to build the plugin's toolbar 
	* in the application.
	* @param parent the parent in which the toolbar shall be created
	* @return the toolbar if the plugin is creating a toolbar else
	* return nothing.
	*/
	virtual void BuildToolBar(RheiaManagedFrame*) {};

	/** 
	* Create the plugin menu in the menubar... This shall be called by your
	* mainframe when you receive the EVT_PLUGIN_ATTACHED. 
	* @note This function may be called more than one time. This can happen,
	* for example, when the menu is recreated from the wxMenuManager
	* @param menuBar the wxMenuBar to create items in
	*/
	virtual void BuildMenu(RheiaManagedFrame*,wxMenuBar*){};

protected:
	/**
	* If you want to write a plugin all your building and construction tasks shall be done
	* in this method. It is called by the RheiaPlugin::Plug() method in RheiaPluginManager
	* and allow you to perform you initalization tasks. Then the plugin shall be usable and
	* all it's informations too. In the application.
	* Here do what you need simply overload the method... 
	*/
	virtual void OnPlug(){};

	/*! Any descendent plugin should override this virtual method and
	* perform any necessary de-initialization. This method is called by
	* Rheia (RheiaPluginManager actually) when the plugin has been
	* loaded, attached and should de-attach from Rheia.\n
	* Think of this method as the actual destructor...
	* @param appShutDown If true, the application is shutting down. In this
	*         case *don't* use RheiaManager::Get()->Get...() functions or the
	*         behaviour is undefined...
	*/
	virtual void OnUnplug(bool){}

	/*! Holds the plugin's type. Set in the default constructor. */
	RheiaPluginType Type;

	/** Holds the "attached" state. */
	bool m_plugged;

private:
	friend class RheiaPluginManager; // only the plugin manager has access here

	/** 
	* You might never have to deal with this function unless you are a Rheia core 
	* developper. What you have to know is that you shall never execute plugin
	* task in your application untill this method and as weel the OnPlug one 
	* have been called.
	*/
	void Plug();

	/** 
	* Unplug the plugin from the application nothing provided by the plugin
	* shall be somwhere in the application after a call to this methos.
	*/
	void Unplug(bool appShutDown);
	
	/** attribute to the plugin's parent */
	RheiaManagedFrame* m_parent;
};

#endif
