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
class BASE_DLLEXPORT RheiaManager
{
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

	/*! Get Method, use GmManger::Get() instead
	*	This method returns the global object instanciated in the RheiaManager.cpp
	*	The aim is to provide the same object to all users
	*/
	static RheiaManager *Get( void );

	/*! Never, EVER, call this function! It is the last function called on shutdown.... */
    static void Free();

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

	static bool IsAppShuttingDown(){return appShuttingDown;};
    static bool isappShuttingDown(){return RheiaManager::IsAppShuttingDown();};

	static void AddonToolBar(wxToolBar* toolBar,wxString resid);

private :
	/***********************************************************************************************
										  PRIVATE VARIABLES
	***********************************************************************************************/
	static bool appShuttingDown;						/*!< specifies if the application is shutting down or not */
};


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
    typedef typename std::map<F*,T*> MgrNsMap;
    typedef typename std::map<F*,T*>::iterator MgrNsMapIt;

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
    static inline T* Get( F* in )
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
    static inline bool Exists( F* in )
    {
        MgrNsMapIt it = m_ns.find( in );

        if( it == m_ns.end() )
            return false;

        return true;
    }

    /** method for freeing an object */
#ifdef SWIG
	%rename(FreeByInstance) Free( F* in );
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

#endif
