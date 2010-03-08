/**
*   @file RheiaFileLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#ifndef RheiaFileLogger_h_
#define RheiaFileLogger_h_

#include "RheiaLogger.h"
#include "RheiaGlobals.h"

#include <wx/colour.h>
#include <wx/font.h>
#include <wx/ffile.h>
#include <wx/textctrl.h>

class wxListCtrl;

/**
*	@class RheiaFileLogger
*
*	@brief RheiaFileLogger is the basic class for logging into a given file
*
*   Enables logging into a file. Any file loggers can be configured and the
*   user will be able to choose the file in which he wants to log. This file
*   will be stored in the logger's configuration group, which you can access
*   using the RheiaLoggerManager::Get()->GetCOnfigurationGroupFor( logger ).
*
*   By default file logger's have their filename set to the logger's name and
*   are located in the user's data directory you can access it via RheiaStandardPaths
*   and RheiaFileFinder.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaFileLogger : public RheiaLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaFileLogger )
#endif
public:
    /***************************************************************************
	*  CONSTRUCTORS AND DESTRUCTORS
	***************************************************************************/
#ifdef SWIG
	%rename(RheiaFileLoggerCopy) RheiaFileLogger(const wxString& filename);
#endif
    /**
    *   Basic builder using the file name in input.
    *   When the logger will be created by the RheiaLoggerManager, the manager will
    *   check for its configuration group en set the file for it.
    *   Anyway, the file can be changed using the SetFile method.
    *
    *   @param filename the full file path of the file in which to log
    */
    RheiaFileLogger(const wxString& filename);

    /**
    *   Default builder
    *   This builder is used if no files are defined for this logger,
    *   However the default filename for a file logger will be the logger's
    *   name.txt and it will be located in the User's data directory.
    */
    RheiaFileLogger() {};

    /** Default destructor */
    virtual ~RheiaFileLogger()
    {
        Close();
    };

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
    virtual bool Open(const wxString& filename)
    {
        return RheiaFileLogger::SetFile( filename );
    };

    /** Close the file if opened and safely save the content */
    virtual void Close()
    {
        if(m_file.IsOpened())
            m_file.Close();
    };

    /** GetConfigurationTool method overload (@see RheiaLogger::GetConfigurationTool)*/
    virtual RheiaConfigurationPanel* GetConfigurationTool( wxWindow* parent );

protected :

    wxFFile m_file;
};

/**
*	@class RheiaTimeStampableFileLogger
*
*	@brief RheiaTimeStampableFileLogger is the basic class for logging into a given file
*
*   Enables logging into a file. Any file loggers can be configured and the
*   user will be able to choose the file in which he wants to log. This file
*   will be stored in the logger's configuration group, which you can access
*   using the RheiaLoggerManager::Get()->GetCOnfigurationGroupFor( logger ).
*
*   By default file logger's have their filename set to the logger's name and
*   are located in the user's data directory you can access it via RheiaStandardPaths
*   and RheiaFileFinder.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaTimeStampableFileLogger : public RheiaFileLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaTimeStampableFileLogger )
#endif
public:
    /***************************************************************************
	*  CONSTRUCTORS AND DESTRUCTORS
	***************************************************************************/
#ifdef SWIG
	%rename(RheiaTimeStampableFileLoggerCopy) RheiaTimeStampableFileLogger(const wxString& filename);
#endif
    /**
    *   Basic builder using the file name in input.
    *   When the logger will be created by the RheiaLoggerManager, the manager will
    *   check for its configuration group en set the file for it.
    *   Anyway, the file can be changed using the SetFile method.
    *
    *   @param filename the full file path of the file in which to log
    */
    RheiaTimeStampableFileLogger(const wxString& filename) : RheiaFileLogger(filename) {};

    /**
    *   Default builder
    *   This builder is used if no files are defined for this logger,
    *   However the default filename for a file logger will be the logger's
    *   name.txt and it will be located in the User's data directory.
    */
    RheiaTimeStampableFileLogger() {};

    /**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log( const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message );
};


#endif
