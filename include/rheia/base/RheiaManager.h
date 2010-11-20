/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaManager.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaManager_h_
#define RheiaManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaFunctor.h>
#include <wx/event.h>
#include <vector>
#include <map>

#include "RheiaComponentCleaner.h"

/* Define used Rheia classes from sdk */
class RheiaWorkspaceManager;
class RheiaCenterPaneManager;
class RheiaLoggerManager;
class RheiaMenuManager;
class RheiaToolBarManager;
class RheiaConfigurationManager;
class RheiaEvent;
class RheiaProjectEvent;
class RheiaPluginManager;
class RheiaStatusBarManager;
class RheiaProfileManager;
class RheiaManagedFrame;

/** define a map for associating a frame to an event id */
typedef std::map<RheiaManagedFrame*,int> RheiaManagedFrameIdMap;

/*! @class Singleton
*
*	@brief Singleton is the class used for simulating static manager.
*
*	To use this class simply inherit your object from Singleton<YourModule> and instanciate
*	instance and isShutdown static variables for the Singleton<YourModule> then you will
*	have access to your object global instance quite similarly to RheiaManager :
*	YourModule::Get().
*
*	@note this class has been taken from the Code::Blocks IDE
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date 02-Dec-2008
*	@version 0.0.1
*/
template <class MgrT> class Singleton
{
    static MgrT *instance;										/*!< global instance for the module */
    static bool isShutdown;										/*!< is the module shutting down */

    explicit Singleton(const Singleton<MgrT>&){};							/*!< copy constructor */
    Singleton<MgrT>& operator=(Singleton<MgrT> const&){return *this;};		/*!< operator = overload */

protected:

    Singleton(){assert(Singleton<MgrT>::instance == 0);}					/*!< Default constructor */
    virtual ~Singleton(){Singleton<MgrT>::instance = 0;}					/*!< Default destructor */

public:

	/*! Specifies is the manager is valid or not */
	static inline bool Valid(){return (instance!=0) ? true : false;}
	
	/*! Check if the manager is down or not */
	static inline bool IsDown(){return isShutdown;};

	/*! Use this function to have access to the managers global instance */
    static inline MgrT* Get()
    {
        if(instance == 0 && isShutdown == false)
            instance = new MgrT();

        return instance;
    }

	/*! NEVER call this function, it called by the application when closing */
    static void Free()
    {
        isShutdown = true;
        delete instance;
        instance = 0;
    }
};

/* wxWidget imports */
class wxWindow;
class wxFrame;
class wxString;
class wxAuiManager;
class wxToolBar;

/**
*	@class RheiaManager
*	@brief RheiaManager is the manager class available for managing the main application
*
*	RheiaManager ist the most central class of Rheia Standard Development Kit. It contains
*	all information about an instance of the main application. Rheia Standard Development Kit allows
*	users to develop specific plugins for using the Rheia's Framework.
*	The manager is a global instance and most methods are static. In the Rheia's SDK anyone can access
*	to the main frame components and info via the manager. However other manager includes must be done
*	to use them.
*
*	Please, if you have to use the manager donc instanciate it use instead RheiaManager::Get().
*
*	@note : if you are a developer for Rheia's SDK, all managers must be used in this class.
*	@note : the principle for this file has been taken from the Code::Blocks IDE
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaManager : public Singleton<RheiaManager>
{
	friend class Singleton<RheiaManager>;
	
public :
	/***********************************************************************************************
	*	CONSTRUCTORS
	***********************************************************************************************/
	/*! Default constructor...
	*	Please do not derive this class by using an other constructor,
	*	as a lot of its members are static !
	*
	*/
	RheiaManager();

	/*! Destructor, freeing memory */
	~RheiaManager();

	/***********************************************************************************************
	*	STATIC METHODS
	***********************************************************************************************/

    /*! Close method for finishing all manager tasks */
    void Close();

	/*! This function is for loading resource to make them available */
	static bool LoadResource( const wxString& file );

	/*! Returns the center pane manager */
	RheiaCenterPaneManager *GetCenterPaneManager(RheiaManagedFrame* parent);

	/*! Returns the menu manager */
	RheiaMenuManager *GetMenuManager(RheiaManagedFrame* parent);

	/*! Returns the toolbar manager */
	RheiaToolBarManager *GetToolBarManager(RheiaManagedFrame* parent);

	/*! Returns the statusbar manager */
	RheiaStatusBarManager *GetStatusBarManager(RheiaManagedFrame* parent);

	/*! Returns the ProfileManager */
	RheiaProfileManager * GetProfileManager(void);

	/*! Returns the ConfigurationManager */
	RheiaConfigurationManager * GetConfigurationManager(const wxString &name_space);
	
	/** Register a component cleaner in this manager */
	void RegisterComponentCleaner(RheiaComponentCleaner* component) { m_components.push_back(component); };
	
	/** Check if the application is shutting down or not */
	static bool IsAppShuttingDown(){return appShuttingDown;};
	/** Check if the application is shutting down or not */
    static bool isappShuttingDown(){return RheiaManager::IsAppShuttingDown();};
	
	/** Create a tool bar from resource */
	static void AddonToolBar(wxToolBar* toolBar,wxString resid);

private :
	/***********************************************************************************************
	* PRIVATE VARIABLES
	***********************************************************************************************/
	static bool appShuttingDown;						/*!< specifies if the application is shutting down or not */
	RheiaComponentCleanerArray m_components;
};

/**
*   @class RheiaMgr
*
*   @brief template class for generalizing the builder desing pattern
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	03-February-2008
*	@version 0.0.2
*/
template <class F, class T> class RheiaMgr
{
public :
    /** associated a wxFramme to an instance of the given class in argument */
    typedef typename std::map<const F*,T*> MgrNsMap;
    typedef typename std::map<const F*,T*>::iterator MgrNsMapIt;

protected :

    static MgrNsMap m_ns;
#ifndef SWIG
    explicit RheiaMgr(const RheiaMgr<F,T>&){};							/*!< copy constructor */
    RheiaMgr<F,T>& operator=(RheiaMgr<F,T> const&){return *this;};		/*!< operator = overload */
#endif
    RheiaMgr(){};					/*!< Default constructor */
    virtual ~RheiaMgr(){};			/*!< Default destructor */

public :

    /** Get method to return an instance of the class accordingly to the F class */
    static inline T* Get( const F* in )
    {
        MgrNsMapIt it = m_ns.find( in );

        if( it == m_ns.end() )
        {
            T* obj = new T( (F*) in );
            m_ns[in] = obj;
            return obj;
        }

        return it->second;
    }

    /** Check if exists for the given input class */
    static inline bool Exists( const F* in )
    {
        MgrNsMapIt it = m_ns.find( in );

        if( it == m_ns.end() )
            return false;

        return true;
    }

    /** method for freeing an object */
#ifdef SWIG
	%rename(FreeByInstance) Free( const F* in );
#endif
    static inline void Free( F* in )
    {
        MgrNsMapIt it = m_ns.find( in );
        if( it == m_ns.end() )
            return;

        delete it->second;
        m_ns.erase( it );
    }

    /** Method for freeing all managers from this class */
    static inline void Free()
    {
        MgrNsMapIt it = m_ns.begin();
        for( ; it != m_ns.end() ; ++it )
            delete it->second;

        m_ns.clear();
    }
};

/**
*   @class RheiaMgrNPtr
*
*   @brief template class for generalizing the builder desing pattern
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	03-February-2010
*	@version 0.0.2
*/
template <class F, class T> class RheiaMgrNPtr
{
protected :
    /** associated a wxFramme to an instance of the given class in argument */
    typedef typename std::map<F,T*> MgrNsMap;
    typedef typename std::map<F,T*>::iterator MgrNsMapIt;

    static MgrNsMap m_ns;
#ifndef SWIG
    explicit RheiaMgrNPtr(const RheiaMgrNPtr<F,T>&){};							/*!< copy constructor */
    RheiaMgrNPtr<F,T>& operator=(RheiaMgrNPtr<F,T> const&){return *this;};		/*!< operator = overload */
#endif
    RheiaMgrNPtr(){};					/*!< Default constructor */
    virtual ~RheiaMgrNPtr(){};			/*!< Default destructor */

public :

    /** Get method to return an instance of the class accordingly to the F class */
    static inline T* Get( const F& in )
    {
        MgrNsMapIt it = m_ns.find( in );

        if( it == m_ns.end() )
        {
            T* obj = new T( in );
            m_ns[in] = obj;
            return obj;
        }

        return it->second;
    }

    /** Check if exists for the given input class */
    static inline bool Exists( const F& in )
    {
        MgrNsMapIt it = m_ns.find( in );

        if( it == m_ns.end() )
            return false;

        return true;
    }

    /** method for freeing an object */
#ifdef SWIG
	%rename(FreeByInstance) Free( const F& in );
#endif
    static inline void Free( const F& in )
    {
        MgrNsMapIt it = m_ns.find( in );
        if( it == m_ns.end() )
            return;

        delete it->second;
        m_ns.erase( it );
    }

    /** Method for freeing all managers from this class */
    static inline void Free()
    {
        MgrNsMapIt it = m_ns.begin();
        for( ; it != m_ns.end() ; ++it )
            delete it->second;

        m_ns.clear();
    }
};

/** @class RheiaComponentCleanerRegistrant
 * @brief main template class for registering a component cleaner in RheiaManager
 */
template<class T> class RheiaComponentCleanerRegistrant
{
public :
	/** Constructor */
	RheiaComponentCleanerRegistrant( const wxString& WXUNUSED(name) ) {
		RheiaManager::Get()->RegisterComponentCleaner(new T());
	}
};

/** define a macro for registering a component cleaner */
#define REGISTER_COMPONENT_CLEANER( object ) \
	namespace ns##object { \
		RheiaComponentCleanerRegistrant<object> registrant( wxT(#object) ); \
	};

#endif
