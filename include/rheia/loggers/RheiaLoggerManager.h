/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaLoggerManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaLoggerManager_h_
#define RheiaLoggerManager_h_

#include <RheiaLoggersSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <RheiaLogger.h>
#include <RheiaEventFrame.h>
#include <RheiaEventsManager.h>
#include <wx/event.h>

class wxAuiNotebook;
class wxTextCtrl;
class wxMenuBar;
class wxStreamToTextRedirector;
class RheiaLoggerManager;

#ifndef SWIG
/** define a logger constructor function */
typedef RheiaLogger*(*CreateLogger)( );

/** define a logger destructor function */
typedef void(*FreeLogger)(RheiaLogger* logger);

/** define a Logger registration structure */
struct RheiaLoggerRegistration
{
    RheiaLoggerRegistration() : createLogger(0), freeLogger(0) {}
	RheiaLoggerRegistration(const RheiaLoggerRegistration& rhs)
		: name(rhs.name),
		createLogger(rhs.createLogger),
		freeLogger(rhs.freeLogger)
	{}

	wxString name;
	CreateLogger createLogger;
	FreeLogger freeLogger;
};
#endif

/** define a map of registered loggers */
typedef std::map< wxString , RheiaLoggerRegistration > RheiaRegisteredLoggersMap;

/** define a map of builded loggers */
typedef std::map< wxString , RheiaLogger* > RheiaLoggerMap;

/**
*	@class RheiaLoggerFactory
*
*	@brief RheiaLoggerFactory is the manager class registering and building log window in Rheia
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	20-April-2009
*	@version 0.0.2
*/
class LOGGERS_DLLEXPORT RheiaLoggerFactory : public Singleton<RheiaLoggerFactory>
{
	/*! Give our private member access to Singleton */
	friend class Singleton<RheiaLoggerFactory>;
	/*! Give our private member access to RheiaManager */
	friend class RheiaManager;

public :
    /******************************************************************************************
    *   REGISTERING/UNREGISTERING LOGGERS
    ******************************************************************************************/
#ifndef SWIG
	/**
    *   Register a Logger in the LoggerManager, you should never use this function directly,
    *   you have to use the REGISTER_LOGGER macro to do this.
    *
    *   @param name The logger's name
    *   @param createFunc the logger contructor
    *   @param freeFunc the logger destructor
    */
    bool RegisterLogger( const wxString& name , CreateLogger createFunc, FreeLogger freeFunc );

    /**
    *   Unregister the logger associated to the given name
    */
    bool UnregisterLogger( const wxString& name );

    /** List all registered loggers in this manager */
    wxArrayString ListRegisteredLoggers();
#endif
    /******************************************************************************************
    *   BUILDING METHODS
    ******************************************************************************************/
    /**
    *   Builder pattern method for loggers
    *   Any Rheia Developer can register new loggers in RheiaLoggerManager. Registered loggers
    *   are not directly build by the manager as you can have multiple instance of the same
    *   RheiaLogger. Hence, if you want to create a new logger, you will have to give it's type
    *   or class name and its associated name in the application. This method, will return a pointer
    *   to the RheiaNullLogger if the logger's type has not been registered in the manager via
    *   RheiaLoggerManager::RegisterLogger.
    *   If a logger has already been associated to the logger's name given in argument, this logger
    *   will be retruned with no type check. So before creating your logger please check via the
    *   RheiaLoggerManager::LogExists method if a logger with the same name already exists or not.
    */
	RheiaLogger* BuildLogger( const wxString& type, const wxString& name );

private :
	/**********************************************************************************************************
	*  CONSTRUCTORS
	**********************************************************************************************************/
	/*! Default constructor */
	RheiaLoggerFactory();

	/*! Default destructor */
	~RheiaLoggerFactory();
#ifndef SWIG
	RheiaRegisteredLoggersMap m_registeredLoggers;  /*!< map of registered loggers in the manager */
#endif
	RheiaLogger* m_nullloger;
};

/**
*	@class RheiaLoggerManager
*
*	@brief RheiaLoggerManager is the manager class for all log window in Rheia
*
*   Basically any type of RheiaLogger shall be registered in this manager using the RheiaLoggerRegistrant.
*   This can be achieved using the REGISTER_LOGGER macro defined in RheiaLoggerManager.h.
*
*   This manager acts as a Builder pattern class for loggers, any logger instanciated using this manager
*   will be registered into it and its memory will be entrely managed. (I.E : it is destroying the registered
*   loggers for you when calling RheiaLoggerManager::Free() ). After having associated a logger to a wxString
*   and register its instance in RheiaLoggerManager, you will be able to access this instance globally by calling
*   RheiaLoggerManager::GetLogger.
*
*   If the logger you've created provides the application with a RheiaInfoPage which is the page display in the
*   RheiaInfoPaneManager, RheiaLoggerManager will managed it for you and create it in Rheia's info pane. Via this
*   manager you can also reactivate closed page in the Info book. However if you log in a logger and its log window
*   has been closed, the window will automatically be redrawn in the RheiaInfoPaneManager's book.s
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	20-April-2009
*	@version 0.0.2
*/
class LOGGERS_DLLEXPORT RheiaLoggerManager : public wxEvtHandler, public RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>
{
	/*! Give our private member access to Singleton */
	friend class RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>;

	/*! Give our private member access to RheiaManager */
	friend class RheiaManager;

private :
	/**********************************************************************************************************
	*  CONSTRUCTORS
	**********************************************************************************************************/
	/*! Default constructor */
	RheiaLoggerManager( RheiaManagedFrame* parent );

	/*! Default destructor */
	~RheiaLoggerManager();

public :
	/**
	*   This method must be called when initializing the environment
	*   it will create the default graphical control for the Logger Manager
	*/
	void InitializeEnvironment();

	/** Register events */
	void RegisterEvents();

	/** Event callback used when a logger is unregistered */
	void OnUnregisterLogger(wxCommandEvent& event);

	/** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( wxMenuBar* menuBar );

	/** Callback used when the user want to manage environment variables */
	void OnConfigure(wxCommandEvent& event);
	
	/** Callback used when the user want to manage environment variables */
	void OnCloseFrame(RheiaFrameEvent& event);

    /******************************************************************************************
    *   ACTIVE LOGGER MANAGEMENT
    ******************************************************************************************/

#ifdef SWIG
	%rename(SetActiveLoggerByName) SetActiveLogger( const wxString& name );
#endif
    /**
    *   Set the active logger
    *   After a call to this method, RheiaLoggerManager will activate the logger with
    *   the given name. If the logger has not been created by a call to CreateLogger,
    *   this method will return false.
    *   If the method returns true, you will be able to log messages in the logger
    *   given in agrgument.
    */
    bool SetActiveLogger( const wxString& name );

    /**
    *   Set the active logger via its object
    *   The logger given in argument will be found in the list and check for
    *   existence, if the method returns false, (I.E: the logger cannot be found)
    *   you will not be able to log message in the logger you gave in argument via
    *   RheiaLogger manager.
    */
    bool SetActiveLogger( RheiaLogger* logger );

#ifdef SWIG
	%rename(SetActiveLoggerByNameAndObject) SetActiveLogger( const wxString& name , RheiaLogger* logger );
#endif
    /**
    *   Set the active logger and register it in the logger's map if it
    *   does not exists.
    */
    bool SetActiveLogger( const wxString& name , RheiaLogger* logger );

    /** Get the active logger */
    RheiaLogger* GetActiveLogger( ) {return m_activelog;};

    /** Get the logger assocaited to the given name */
    RheiaLogger* GetLogger( const wxString& name );

    /** Get the logger assocaited to the given name */
    RheiaLogger* GetRheiaLogger( )
    {   return GetLogger( wxT("Rheia Log") ); };

    /** Get the logger assocaited to the given name */
    RheiaLogger* GetRheiaDebugLogger( )
    {   return GetLogger( wxT("Rheia Debug Log") ); };

    /** Get the first logger of the given type */
    RheiaLogger* GetFirstLoggerOf( const wxString& type );

    /** Get the loggers name */
    wxString GetLoggerName( RheiaLogger* logger );

    /******************************************************************************************
    *   PREDEFINED STATIC LOGGING FUNCTIONS
    ******************************************************************************************/
    /**
    *   Log the given message in the active logger.
    *   In order to prevent logging in NULL logger, if the active logger has not been set,
    *   RheiaLoggerManager will log into the RheiaNullLogger.
    */
    static inline void sLog(const wxString& msg , RheiaLogging::RheiaLogLevel level = RheiaLogging::message )
    {
        MgrNsMapIt it = m_ns.begin();
        for( ; it != m_ns.end() ; ++it )
            it->second->Log(msg,level);
    }

    /**
    *   Log a message in the active logger
    *   Same as Log with only one argument
    */
	static inline void sLogMessage( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::message);
    };

    /**
    *   Log a warning message in the active logger
    */
	static inline void sLogWarning( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::warning);
    };

    /**
    *   Log a success message in the active logger
    */
	static inline void sLogSuccess( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::success);
    };

    /**
    *   Log a error message in the active logger
    */
	static inline void sLogError( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::error);
    };

    /**
    *   Log a fatal error message in the active logger
    */
	static inline void sLogFataError( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::fatalerror);
    };

    /**
    *   Log a info message in the active logger
    */
	static inline void sLogInfo( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::info);
    };

    /**
    *   Log a status message in the active logger
    */
	static inline void sLogStatus( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::status);
    };

    /**
    *   Log a system error message in the active logger
    */
	static inline void sLogSystemError( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::syserror);
    };

    /**
    *   Log a debug message in the active logger
    */
	static inline void sLogDebug( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::debug);
    };

    /**
    *   Log a trace message in the active logger
    */
	static inline void sLogTrace( const wxString& msg )
	{
	    sLog(msg, RheiaLogging::trace);
    };

    /**
    *   Log the given message in the active logger.
    *   In order to prevent logging in NULL logger, if the active logger has not been set,
    *   RheiaLoggerManager will log into the RheiaNullLogger.
    */
    static inline void sdLog(const wxString& msg , RheiaLogging::RheiaLogLevel level = RheiaLogging::message )
    {
        MgrNsMapIt it = m_ns.begin();
        for( ; it != m_ns.end() ; ++it )
        {
            RheiaLogger* deblog = it->second->GetRheiaDebugLogger();
            deblog->Log(msg,level);
        }

    }

    /**
    *   Log a message in the active logger
    *   Same as Log with only one argument
    */
	static inline void sdLogMessage( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::message);
    };

    /**
    *   Log a warning message in the active logger
    */
	static inline void sdLogWarning( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::warning);
    };

    /**
    *   Log a success message in the active logger
    */
	static inline void sdLogSuccess( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::success);
    };

    /**
    *   Log a error message in the active logger
    */
	static inline void sdLogError( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::error);
    };

    /**
    *   Log a fatal error message in the active logger
    */
	static inline void sdLogFataError( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::fatalerror);
    };

    /**
    *   Log a info message in the active logger
    */
	static inline void sdLogInfo( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::info);
    };

    /**
    *   Log a status message in the active logger
    */
	static inline void sdLogStatus( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::status);
    };

    /**
    *   Log a system error message in the active logger
    */
	static inline void sdLogSystemError( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::syserror);
    };

    /**
    *   Log a debug message in the active logger
    */
	static inline void sdLogDebug( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::debug);
    };

    /**
    *   Log a trace message in the active logger
    */
	static inline void sdLogTrace( const wxString& msg )
	{
	    sdLog(msg, RheiaLogging::trace);
    };

    /******************************************************************************************
    *   PREDEFINED LOGGING FUNCTIONS
    ******************************************************************************************/
    /**
    *   Log the given message in the active logger.
    *   In order to prevent logging in NULL logger, if the active logger has not been set,
    *   RheiaLoggerManager will log into the RheiaNullLogger.
    */
    void Log(const wxString& msg , RheiaLogging::RheiaLogLevel level = RheiaLogging::message );

    /**
    *   Log a message in the active logger
    *   Same as Log with only one argument
    */
	void LogMessage( const wxString& msg )
	{
	    Log(msg, RheiaLogging::message);
    };

    /**
    *   Log a warning message in the active logger
    */
	void LogWarning( const wxString& msg )
	{
	    Log(msg, RheiaLogging::warning);
    };

    /**
    *   Log a success message in the active logger
    */
	void LogSuccess( const wxString& msg )
	{
	    Log(msg, RheiaLogging::success);
    };

    /**
    *   Log a error message in the active logger
    */
	void LogError( const wxString& msg )
	{
	    Log(msg, RheiaLogging::error);
    };

    /**
    *   Log a fatal error message in the active logger
    */
	void LogFataError( const wxString& msg )
	{
	    Log(msg, RheiaLogging::fatalerror);
    };

    /**
    *   Log a info message in the active logger
    */
	void LogInfo( const wxString& msg )
	{
	    Log(msg, RheiaLogging::info);
    };

    /**
    *   Log a status message in the active logger
    */
	void LogStatus( const wxString& msg )
	{
	    Log(msg, RheiaLogging::status);
    };

    /**
    *   Log a system error message in the active logger
    */
	void LogSystemError( const wxString& msg )
	{
	    Log(msg, RheiaLogging::syserror);
    };

    /**
    *   Log a debug message in the active logger
    */
	void LogDebug( const wxString& msg )
	{
	    Log(msg, RheiaLogging::debug);
    };

    /**
    *   Log a trace message in the active logger
    */
	void LogTrace( const wxString& msg )
	{
	    Log(msg, RheiaLogging::trace);
    };

    /******************************************************************************************
    *   CLEARING METHODS
    ******************************************************************************************/
    /**
    *   Clear the active logger
    */
    void ClearLog();
#ifdef SWIG
	%rename(CleaLogByName) ClearLog( const wxString& name );
#endif
    /**
    *   Clear the log associated to the given name
    */
    void ClearLog( const wxString& name );

    /******************************************************************************************
    *   LISTING METHODS
    ******************************************************************************************/
    /** List all created loggers in this manager */
    wxArrayString ListLoggers();

    /**
    *   If you choose to write your own logger and you do not want to
    *   register it in this manager, you can create its instance by your own and add
    *   it in the log manager using this method.
    *   However, our experience showed that it is better to register the Logger object type
    *   in the manager using the RheiaLoggerManager::RegisterLogger method.
    */
    bool AddLogger( RheiaLogger* logger, const wxString& name );

    /******************************************************************************************
    *   DESTROYING METHODS
    ******************************************************************************************/
    /**
    *   Delete a specific logger from the manager
    *   Please take care of what you did, because if this method returns true, the logger will
    *   no longer be available in this manager and the given instance is destroyed before returning.
    *   So if you try to use the logger given in argument after a call to this method, it will
    *   results in an application crash.
    *   @param logger the logger to delete if found
    */
    bool DeleteLogger(RheiaLogger* logger);

#ifdef SWIG
	%rename(DeleteLoggerByName) DeleteLogger(const wxString& name);
#endif
    /**
    *   Delete a specific logger from the manager
    *   @param name the logger's name to delete if found
    */
    bool DeleteLogger(const wxString& name);

    	/** Notify the logger that an update of layout or any other has been made */
	void NotifyUpdate();

	/******************************************************************************************
    *   DEALING WITH RHEIA INFOPANE MANAGER
    ******************************************************************************************/
#ifdef SWIG
	%rename(ShowLoggerByName) Show(const wxString& name);
#endif
	/** Show the logger at the given index */
	void Show(const wxString& name);

	/** Show the given Logger */
    void Show(RheiaLogger* logger);

#ifdef SWIG
	%rename(GetLogPageIndexByName) GetLogPageIndex( const wxString& name );
#endif
    /** Get the page index in RheiaInfoPaneManager */
    int GetLogPageIndex( const wxString& name );

    /** Get the page index in RheiaInfoPaneManager */
    int GetLogPageIndex( RheiaLogger* logger );

    /******************************************************************************************
    *   GET LOGGERS CONFIGURATION GROUPS
    ******************************************************************************************/
    /** Get the loggers configuration group via its object reference */
    RheiaConfigurationManager* GetConfigurationGroupFor( RheiaLogger* logger );

#ifdef SWIG
	%rename(GetConfigurationGroupByNameFor) GetConfigurationGroupFor( const wxString& name );
#endif
    /** Get the logger's configuration group via its name */
    RheiaConfigurationManager* GetConfigurationGroupFor( const wxString& name );

private :
	/**********************************************************************************************************
	* PRIVATE VARIABLES
	**********************************************************************************************************/

	RheiaLoggerMap m_loggers;
	RheiaLogger* m_activelog;
	RheiaLogger* m_nullloger;
	RheiaManagedFrame* m_parent;

private :
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#ifndef SWIG
/** @brief Logger registration object.
*
* Use this class to register your new Logger with Rheia
* All you have to do is instantiate a RheiaLoggerRegistrant object.
* @par
* Example code to use in one of your plugin's source files (supposedly called "MyPlugin"):
* @code
* namespace
* {
*     RheiaLoggerRegistrant<MyLogger> registration("MyLogger");
* }
* @endcode
*/
template<class T> class RheiaLoggerRegistrant
{
public:
	/*! Base constructor
	*	@param name The logger's name.
	*/
	RheiaLoggerRegistrant(const wxString& name)
	{
		RheiaLoggerFactory::Get()->RegisterLogger(name, // plugin's name
			&CreateLogger, // creation
			&FreeLogger ); // destruction
	}

	/*! Function for creating the logger */
	static RheiaLogger* CreateLogger()
	{
		return new T;
	}

	/*! Function for freeing the logger
	*	@param logger the logger to free
	*/
	static void FreeLogger(RheiaLogger* logger)
	{
		delete logger;
	}
};

/**
*   Finally define a macro for adding a logger in one line
*   simply call REGISTER_LOGGER( MyLogger ) if you want to add
*   a new Logger in the list
*/
#define REGISTER_LOGGER( object , name ) \
    namespace { \
        RheiaLoggerRegistrant< object > registration( name );\
    }

#endif

#endif
