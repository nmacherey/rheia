/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaConfigurationToolsManager.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#ifndef RheiaConfigurationToolsManager_h_
#define RheiaConfigurationToolsManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>

class RheiaConfigurationPanel;

enum ConfigurationGroup
{
    cgApp = 0,
    cgLog
};

/**
*   Define a configuration tool constructor function.
*
*   When a tool is registered in the RheiaConfigurationToolsManager
*   it has to provide the manager with a pointer to its contructor
*   method. A configuration tool can be build many times during the
*   application run.
*/
typedef RheiaConfigurationPanel*(*CreateConfigurationTool)( wxWindow* parent );

/**
*   Define a configuration tool destructor function.
*
*   When a tool is registered in the RheiaConfigurationToolsManager
*   it has to provide the manager with a pointer to its destructor
*   method. A configuration tool can be build many times during the
*   application run.
*/
typedef void(*FreeConfigurationTool)(RheiaConfigurationPanel* tool);

/**
*   Define a configuration tool registration structure.
*
*   When a tool is registered in the RheiaConfigurationToolsManager
*   all its registration informations are stored in the manager using
*   this structure.
*   In normal usage you really don't have to deal with this information
*   However it has been kept public in order to keep the application as
*   generic as possible.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
struct RheiaConfigurationToolRegistration
{
    /** default constructor */
    RheiaConfigurationToolRegistration() : ctor(0), dtor(0) {}

    /** copy constructor */
	RheiaConfigurationToolRegistration(const RheiaConfigurationToolRegistration& rhs)
		: name(rhs.name),
		group(rhs.group),
		ctor(rhs.ctor),
		dtor(rhs.dtor)
	{}

    /*** members */
	wxString name;
	ConfigurationGroup group;
	CreateConfigurationTool ctor;
	FreeConfigurationTool dtor;
};

/**
*   Any configuration tools can be registered once
*   Here we associate a wxString to a RheiaConfigurationToolRegistration
*   via stl map in order to stored all RheiaConfigurationToolRegistration
*   in the manager via their name as unique key.
*/
typedef std::map< wxString , RheiaConfigurationToolRegistration > RheiaConfigurationToolRegistrationMap;


/**
*   @class RheiaConfigurationToolsManager
*
*   @brief This is the "Factory design pattern" for building configuration tools in Rheia.
*
*   This clas is a "Factory design pattern" meaning that it is able to build many different
*   kind of RheiaConfigurationTools via the RheiaConfigurationToolsManager::CreateTool
*   method.
*
*   This class is used to manage and register all available configuration tools in Rheia.
*   A configuration tool is a class derived from a RheiaConfigurationPanel and which can
*   be displayed in any configuration dialog or in the standard RheiaApplicationConfigurationDialog.
*
*   As many other manager in Rheia this class is a singleton and is available only via a global
*   instance common to all Rheia SDK's users. You cannot build this class by your own as it has been
*   written to handle common information. You have to use RheiaConfigurationToolsManager::Get() to
*   access the global instance of this class and RheiaConfigurationToolsManager::Free() to delete it.
*
*   You may not call RheiaConfigurationToolsManager::Free() by your own as RheiaManager will do it
*   when the application is closing.
*
*   From wikipedia (http://en.wikipedia.org/wiki/Factory_method_pattern):
*
*   The factory method pattern is an object-oriented design pattern. Like other creational
*   patterns, it deals with the problem of creating objects (products) without specifying
*   the exact class of object that will be created. The factory method design pattern handles
*   this problem by defining a separate method for creating the objects, whose subclasses can
*   then override to specify the derived type of product that will be created. More generally,
*   the term factory method is often used to refer to any method whose main purpose is creation
*   of objects.
*
*   The main problems of standard factories is that the basic factory class has to know the type
*   of object it can create. This can become a hudge maintenance problem if we have to develop
*   many different kind of objects at a different time, because it will change a lot the factory
*   itself and it will depends on each header of designed objects. As we need to enable the
*   development of configuration tools via plugins and other libraries without changing this
*   factory, we designed a template class for registering configuration tools in this factory.
*   The template class called RheiaConfigurationToolRegistrant is a very usefull method used in
*   different other factories in Rheia. It will simply provide the factory with the name or title
*   of the object you want to register and two pointers for building and destroying any objects
*   registered in the factory. More over this task can simply be achieve by instanciating an object
*   of the template class embeding into it your own object.
*
*   Hence, if you want to write your own configuration tool, you have to register it in this manager by using
*   the design template object written for : RheiaConfigurationToolRegistrant. If you want to temporarily
*   register a configuration panel you have to Unregister it from the manager by calling the UnregisterTool
*   method or by deleting the design template instance you used for registering your tool in the manager.
*
*   Such representations might be difficult to understand if you are new to design patterns. However,
*   You can write many different kind of objects and register them in the factory via the desig template
*   without having to manage their headers somewere in the code. But, please note that this kind of
*   methods can only be applied in Dynamic Libraries which contains all code and exports files. You cannot
*   manage to use this kind of methods in static libraries especially under windows where static and
*   dynamic libraries are really not managed the same way.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
class BASE_DLLEXPORT RheiaConfigurationToolsManager : public Singleton<RheiaConfigurationToolsManager>
{
    /** give Mrg our private members access */
    friend class Singleton<RheiaConfigurationToolsManager>;

public :
    /*******************************************************************************
    *   ACCESSORS
    *******************************************************************************/
    /**
    *   Get the list of registered tools in the manager
    *   This will provide you with an array string of registered object names
    *   but not with Configuration tool's titles.
    */
    wxArrayString GetList();

    /** Get the list for the given configuration group */
    wxArrayString GetListFor(ConfigurationGroup group);

    /**
    *   Register a configuration tool in the manager
    *   You have to provide the manager with the constructor and destructor for
    *   your tool.
    *   Basically you should never call directly this method and rather use the
    *   designed template for RheiaConfigurationToolsRegistrant.
    *   However if you still want to call this method you have to create a static
    *   method for the constructor and destructor of your configuration tool and
    *   pass their address to this method.
    *
    *   @param name configuration tool's name
    *   @param group configuration tool's group
    *   @param ctor configuration tool's constrcutor method pointer
    *   @param dtor configuration tool's destrcutor method pointer
    *
    *   @return this method returns true if the configuration tool has been properly
    *   registered in this manager. It will return false if an other tool with the
    *   same name already exists.
    */
    bool RegisterTool( const wxString& name,
        ConfigurationGroup group,
        CreateConfigurationTool ctor,
        FreeConfigurationTool dtor );

    /**
    *   Unregister a configuration tool from the manager.
    *   You may never have to use this function directly as it is managed by
    *   the RheiaConfigurationToolsRegistrant designed template.
    *   However if you don't call this method for example when the tool is comming
    *   from a plugin when the plugin is dettached the application will crash.
    *
    *   @param name configuration tool's name
    *   @return true if the tool has been properly removed from the manager. Basically
    *   it shall always return true.
    */
    bool UnregisterTool( const wxString& name );

    /**
    *   Create a tool
    *
    *   When you want to create a specific tool you simply have to call this method
    *   and give in argument the tool's name and its parent window.
    *
    *   @param name the configuration tool's name you want to create
    *   @param parent the parent wxWindow in which the tool shall be created
    *
    *   @return If the tool has not been found in the manager it will return NULL.
    *   Otherwise this method returns the tool Created in the parent.
    */
    RheiaConfigurationPanel* CreateTool( const wxString& name,
        wxWindow* parent );

    /**
    *   Get the tools registration map
    *   You may never have to use this method so if you are looking for
    *   informations about ow to create and register a tool in this manager
    *   this is not the right place :-).
    */
    const RheiaConfigurationToolRegistrationMap& GetTools() { return m_tools; };

    /** Find a tool registration structure given the tool name */
    const RheiaConfigurationToolRegistration* FindToolByName( const wxString& name );

    /**
    *   Specify if a tool has been registered in the manager or not
    *   @param name configuration tool's name to check the existence for
    */
    bool Exists( const wxString& name );

private :
    /*******************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    *******************************************************************************/
    /**
    *   Default constructor,
    *   You cannot build directly this object as it is provided as a global instance
    *   object. Use RheiaConfigurationToolsManager::Get() to get the global instance
    *   for this manager and use the public methods defined bellow.
    */
    RheiaConfigurationToolsManager();

    /**
    *   Default destructor
    *   You cannot delete this object directly as it is provided as a flobal instance
    *   object. Use RheiaConfigurationToolsManager::Free() to delete the global instance
    *   for this manager. Note that if you delete the global instance the next
    *   RheiaConfigurationToolsManager::Get() will allocate a new instance and some memory
    *   migth be loosed by the application.
    *   Usually RheiaManager will call RheiaConfigurationToolsManager::Free() when the application
    *   is exited.
    */
    ~RheiaConfigurationToolsManager();

private :
    /*******************************************************************************
    *   PRIVATE MEMBERS
    *******************************************************************************/
    RheiaConfigurationToolRegistrationMap m_tools;
};


/**
*   @class RheiaConfigurationToolRegistrant
*
*   @brief Configuration tool registration design template
*
*   Use this class to register your configuration tool with RheiaConfigurationToolsManager
*   All you have to do is instantiate a RheiaConfigurationToolRegistrant object.
*   If you are coding a RheiaConfigurationToolPlugin for the application you have to create
*   this design tempalte in the RheiaPlugin::OnPlug() method and to free it in the
*   RheiaPlugin::OnDettach() method.
*   If the configuration tool is directly build in the Rheia SDK, simply declare a global
*   object in a namesapce to enable the tool in Rheia.
*   @see RheiaConfgiurationToolsManager for more information about the role of this objects
*
*   @par
*   Example code to use in one of your plugin's source files (supposedly called "MyTool"):
*   @code
*   namespace
*   {
*     RheiaConfigurationToolRegistrant<MyTool> registration( wxT("MyTool") );
*   }
*   @endcode
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
template<class T> class RheiaConfigurationToolRegistrant
{
public:
	/**
	*   Base constructor
	*   When building this object we regiter the template class T given in the
	*   template cast and the build and destroy method.
	*	@param name The configuration tool's name, commonly it is the object name.
	*/
	RheiaConfigurationToolRegistrant( const wxString& name , ConfigurationGroup group ):t_name(name)
	{
		RheiaConfigurationToolsManager::Get()->RegisterTool( name, // plugin's name
            group,
			&Create, // creation
			&Free ); // destruction
	}

	/** default destructor */
	~RheiaConfigurationToolRegistrant()
	{
	    RheiaConfigurationToolsManager::Get()->UnregisterTool( t_name );
	}

	/**
	*   Function for creating the configuration tool
	*   @note that this method is a static method, because class function
	*   pointers are only availbale if defined static.
	*/
	static RheiaConfigurationPanel* Create( wxWindow* parent )
	{
		return new T(parent);
	}

	/**
	*   Function for freeing the configuration tool
	*
	*   @note that this method is a static method, because class function
	*   pointers are only availbale if defined static.
	*
	*	@param tool the configuration tool to free
	*/
	static void Free(RheiaConfigurationPanel* tool)
	{
		delete tool;
	}
private :
    wxString t_name;
};


/**
*   Macro for registering a configuration tool in the manager
*   This macro is a helper class used to define a global variable for registering
*   a configuration tool in the RheiaConfigurationToolManager.
*   Take care of what you did, you can use this macro at the very begining of your
*   confgiuration tool's CPP file but global variables are created when the bianary
*   is loaded and are destroyed only when it is unloaded. So if you need to register
*   temporarily your tool you have better to instanciate a RheiaConfigurationToolRegistrant
*   by your own and to destroy it when needed.
*/
#define REGISTER_CONFIGURATION_TOOL( object ) \
    namespace { \
        RheiaConfigurationToolRegistrant<object> object##Registrant( wxT(#object) , cgApp ); \
    }

#define REGISTER_LOGGER_CONFIGURATION_TOOL( object ) \
    namespace { \
        RheiaConfigurationToolRegistrant<object> object##Registrant( wxT(#object) , cgLog ); \
    }

#endif
