/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaHtmlLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#ifndef RheiaHtmlLogger_h_
#define RheiaHtmlLogger_h_

#include "RheiaLogger.h"
#include "RheiaGlobals.h"
#include "RheiaFileLogger.h"

#include <wx/colour.h>
#include <wx/font.h>
#include <wx/ffile.h>
#include <wx/textctrl.h>

class RheiaHtmlLoggerPage;

/**
*   @struct RheiaHtmlHeader
*
*   @brief This is the basic information structure for RheiaHtmlLoggers
*
*   Any Html Loggers can write their info into an html file, but they can also
*   display their information in an wxHtmlWindow. This structure has been written
*   in order to facilitate html writting via loggers. It is very simple as the
*   wxHtmlWindow is just a very very very basic html window and does not manage
*   lot of things.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
struct LOGGERS_DLLEXPORT RheiaHtmlHeader
{
    wxString message;
    wxString warning;
    wxString success;
    wxString error;
    wxString fatalerror;
    wxString info;
    wxString status;
    wxString syserror;
    wxString debug;
    wxString trace;
    wxString h1;
    wxString h2;
    wxString timestamp;

    RheiaHtmlHeader();
#ifdef SWIG
	%rename(RheiaHtmlHeaderCopy) RheiaHtmlHeader(const RheiaHtmlHeader& rhs);
#endif
    RheiaHtmlHeader(const RheiaHtmlHeader& rhs);
};

/**
*	@class RheiaHtmlLogger
*
*	@brief RheiaHtmlLogger is the basic class for logging into a given html file
*   and optionnaly in a wxHtmlWindow by setting the file in the path.
*
*   Any Html Loggers can write their info into an html file, but they can also
*   display their information in an wxHtmlWindow. This structure has been written
*   in order to facilitate html writting via loggers. It is very simple as the
*   wxHtmlWindow is just a very very very basic html window and does not manage
*   lot of things.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaHtmlLogger : public RheiaFileLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaHtmlLogger )
#endif

    friend class RheiaHtmlLoggerPage;
public:
    /***************************************************************************
	*  CONSTRUCTORS AND DESTRUCTORS
	***************************************************************************/
#ifdef SWIG
	%rename(RheiaHtmlLoggerCopy) RheiaHtmlLogger(const wxString& filename);
#endif
    /**
    *   Basic builder using the file name in input.
    *   When the logger will be created by the RheiaLoggerManager, the manager will
    *   check for its configuration group en set the file for it.
    *   Anyway, the file can be changed using the SetFile method.
    *
    *   @param filename the full file path of the file in which to log
    */
    RheiaHtmlLogger(const wxString& filename);

    /**
    *   Default builder
    *   This builder is used if no files are defined for this logger,
    *   However the default filename for a file logger will be the logger's
    *   name.txt and it will be located in the User's data directory.
    */
    RheiaHtmlLogger();

    /** default destrcutor */
    virtual ~RheiaHtmlLogger(){ Close(); };

    /**
    *   Constructor method
    *   This method will close the existing file before doing anything
    *   if the file exists and then will Open the new file.
    *   If the open failed, no message will be loagged into the file and
    *   it will return safely.
    *   @param filename the full file path of the file in which to log
    */
    virtual bool SetFile(const wxString& filename);

    /**
    *   Set the Html header info (cna be viewed as a very very very simple css)
    *   @param header RheiaHtmlHeader to set in the file.
    */
    void SetHeader(const RheiaHtmlHeader& header) { m_header = header; };

    /**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log( const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message );

    /**
    *   Same as SetFile for nomenclature convenience
    *   You can prefer this method if you like
    *   @param filename the full file path of the file in which to log
    */
    virtual bool Open(const wxString& filename);

    /** Close the file if opened and safely save the content */
    virtual void Close();

    /**
    *   RheiaLogger::GetLogWindow method overload (@see RheiaLogger::GetLogWindow)
    *   @param parent the parent window in which the log window shall be created
    *   @return NULL if the logger is not displaying in a log window (default)
    */
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed(){m_window=NULL;return true;};

protected :
    RheiaHtmlHeader m_header;
    RheiaHtmlLoggerPage* m_window;
    wxString m_page;
};

/**
*	@class RheiaTimeStampableHtmlLogger
*
*	@brief RheiaTimeStampableHtmlLogger is the basic class for logging into a given html file
*   and optionnaly in a wxHtmlWindow by setting the file in the path.
*
*   Any Html Loggers can write their info into an html file, but they can also
*   display their information in an wxHtmlWindow. This structure has been written
*   in order to facilitate html writting via loggers. It is very simple as the
*   wxHtmlWindow is just a very very very basic html window and does not manage
*   lot of things.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaTimeStampableHtmlLogger : public RheiaHtmlLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaTimeStampableHtmlLogger )
#endif

public:
    /***************************************************************************
	*  CONSTRUCTORS AND DESTRUCTORS
	***************************************************************************/
#ifdef SWIG
	%rename(RheiaTimeStampableHtmlLoggerCopy) RheiaTimeStampableHtmlLogger(const wxString& filename);
#endif
    /**
    *   Basic builder using the file name in input.
    *   When the logger will be created by the RheiaLoggerManager, the manager will
    *   check for its configuration group en set the file for it.
    *   Anyway, the file can be changed using the SetFile method.
    *
    *   @param filename the full file path of the file in which to log
    */
    RheiaTimeStampableHtmlLogger(const wxString& filename):RheiaHtmlLogger(filename) {};

    /**
    *   Default builder
    *   This builder is used if no files are defined for this logger,
    *   However the default filename for a file logger will be the logger's
    *   name.txt and it will be located in the User's data directory.
    */
    RheiaTimeStampableHtmlLogger():RheiaHtmlLogger(){};

    /**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log( const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message );
};

#endif

