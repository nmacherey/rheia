/**
*   @file RheiaLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.2
*/
#ifndef RheiaLogger_h_
#define RheiaLogger_h_

#include <wx/string.h>
#include "RheiaLoggersSettings.h"
#include "RheiaGlobals.h"
#include "RheiaPageContainer.h"

class wxWindow;
class RheiaConfigurationPanel;
class RheiaInfoPage;

namespace RheiaLogging
{
    /**
    *   In Rheia Log levels are used to notify the logger for specific display about the log
    *   message. Levels principle have been taken from the wxWidgets wxLog classes where you will
    *   find wxLogFatalError, wxLogError, wxLogWarning, wxLogMessage, wxLogVerbose, wxLogStatus,
    *   wxLogSysError, wxLogDebug and wxLogTrace.
    *
    *   Hence for a given logger you might have to display the given message to Log in a different
    *   way for the different levels. You can also choose to skip this and simply display the message
    *   to your convenience. However properly displaying log messages can be very usefull for your
    *   end user to help him to understand what's wrong :-).
    *
    *   Logging is very important especially when your are developping additionnal functionalities
    *   in Rheia and you don't really know if what you've done will alterate or not the apllication
    *   run.
    */
    enum RheiaLogLevel {
        message = 0,
        warning,
        success,
        error,
        fatalerror,
        info,
        status,
        syserror,
        debug,
        trace };

    /** store the total number of log levels */
    const int RheiaLogLevelNumber = trace + 1;
}

/**
*	@class RheiaLogger
*
*	@brief RheiaLogger is the basic class for logging info in Rheia's Bottom Pane
*
*   RheiaLogger is the basic class for logging information in Rheia. Rheia provide any developers
*   with different kind of loggers. You can also choose to register/add a own made logger for your
*   own requirements and needs.
*
*   A logger in rheia is a tool for which different kind of log levels can be defined, and which can
*   display the logged info in a window. Any logger windows are created in Rheia's Loggers Pane. Mainly
*   in the bottom pane if you did not move it by your own.
*
*   If you want to write a logger by your own, it has to be derived from this abstract class.
*
*   This class is derived from wxObject and implements the wxWidgets RTTI system. Hence you
*   can at any time get the classinfo for the logger.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaLogger : public wxEvtHandler, public virtual RheiaPageContainer
{
#ifndef SWIG
    DECLARE_ABSTRACT_CLASS( RheiaLogger )
#endif
public:
    /***************************************************************************
	*  CONSTRUCTORS AND DESTRUCTORS
	***************************************************************************/
    /**
    *   Default ocnstructor
    *   For the moment there is really nothing to do here...
    *   However the constructor has been written to prevent specific
    *   default initialisations in the logger when building it.
    */
    RheiaLogger();

    /**
    *   Default Destructor
    *   For the moment there is really nothing to do here...
    *   However the destructor has been written to prevent specific
    *   default freed in the logger when destroying it.
    */
    virtual ~RheiaLogger();

    /***************************************************************************
	*  METHODS
	***************************************************************************/
	/** Get the loggers type */
	const wxString& GetType() { return m_type; };

	/** Set the loggers type */
	void SetType( const wxString& type ) { m_type = type; };

	/**
	*   This is the most important function that any logger shall have properly written.
	*   You must overload this method if you are writting a logger. What you have to know is
	*   that this method must work with or without the GUI environment. Hence, if you want
	*   to log all messaged in a window you have to check first if the related window has
	*   been built or not. If you don't, you might cause the application to crash in some
	*   specific usage cases. However you can really do what you want here.
	*
	*   @param msg message to log
	*   @param level message level as explained in RheiaLogging::RheiaLogLevel
	*/
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message) = 0;

    /**
    *   As any loggers can be asked by the user to be cleared, you have to overload this
    *   method in order to properly clear your logger content.
    *   @note that this method is optional if you want to write a basic logger with no
    *   options, simply ignore this method.
    */
    virtual void Clear() {};

    /**
    *   RheiaLoggerManager is managing for you a context menu with very basic options
    *   Such as Copy All to clipboard, coppy selection to clipboard, clear...
    *   Here is the place to implement the copy of all the logger's content if you need...
    *   @note As the Clear() method this one is optional so if you want to write a basic
    *   logger with no options, simply ignore this method.
    */
    virtual void CopyAll() {};

    /**
    *   RheiaLoggerManager is managing for you a context menu with very basic options
    *   Such as Copy All to clipboard, coppy selection to clipboard, clear...
    *   Here is the place to implement the copy of the logger's selection if you need...
    *   @note As the Clear() method this one is optional so if you want to write a basic
    *   logger with no options, simply ignore this method.
    */
    virtual void CopySelection() {};

    /**
    *   RheiaLoggerManager is managing for you a context menu with very basic options
    *   Such as Copy All to clipboard, coppy selection to clipboard, clear, help on selection...
    *   Here is the place to implement options for displaying help about the error selected
    *   by the user...
    *   @note As the Clear() method this one is optional so if you want to write a basic
    *   logger with no options, simply ignore this method.
    */
    virtual void HelpOnSelection() {};

    /**
    *   When the user left clicks on your logger window, a context menu is displayed, if you want
    *   to add specific menu options when receiving such requests you have to overload
    *   this method.
    *   @param menu the parent wxMenu in which you shall add items
    */
    virtual void BuildMenu( wxMenu* menu ) {};

    /**
    *   The logger manager can be configured via RheiaApplicationSettingsDialog....
    *   You now that you can add specific configuration panels in this dialog or
    *   register it in the RheiaLoggerManager to be displayed in its own configuration
    *   panel.
    *   This method shall be used when the related configuration panel is applied by the
    *   user in order to allow you to set specific configuration settings for your logger.
    */
    virtual void UpdateSettings() {};

    /**
    *   As any logger can create a log page in Rheia's information's pane,
    *   you can overload this method in order to create your own log window in
    *   order to display as your convenience log messages.
    *   @param parent the parent window in which the log window shall be created
    *   @return NULL if the logger is not displaying in a log window (default)
    */
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent ) { return NULL; };

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed(){return true;};

	/**
	*   Get the project bitmap to the given size,
	*   size could be 16x16, 32x32, 48x48, 80x80 or 128x128
	*/
	virtual const wxBitmap& GetBitmap( const int& size );

private :
    wxString m_type;
    wxBitmap m_bmp;
};

/**
*	@class RheiaNullLogger
*
*	@brief RheiaNullLogger is the logger with no window and that do nothing
*
*   This class is used in the RheiaLoggerManager "Builder Pattern" wich allow
*   you to get the registered logger via it's name. If the name was not found,
*   or the requested logger was not registered in the manager, RheiaNullLogger
*   instance will be returned in order to prevent returning an empty object
*   reference.
*
*   This class is derived from wxObject and implements the wxWidgets RTTI system. Hence you
*   can at any time get the classinfo for the logger.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaNullLogger : public RheiaLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaNullLogger )
#endif
public:

    /** Simply overload the Log method in order to do nothing */
    virtual void Log( const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message ){};
};

#endif
