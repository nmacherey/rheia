
/**
*   @file RheiaStdLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#ifndef RheiaStdLogger_h_
#define RheiaStdLogger_h_

#include "RheiaLogger.h"
#include "RheiaGlobals.h"

#include <wx/colour.h>
#include <wx/font.h>
#include <wx/ffile.h>
#include <wx/textctrl.h>

class wxListCtrl;

/**
*	@class RheiaStdLogger
*
*	@brief RheiaStdoutLogger is the basic class for logging into the standard streams...
*
*   This class will choose accordingly to the given RheiaLogging::RheiaLogLevel the stream
*   in which to log. This logger cannot be configured and does not provide the application
*   with a specific configuration tool.
*
*   @note that in Rheia a specific window is displayed in the RheiaInformationManager's book
*   which is based on a wxTextCtrl and the redirection of std::cerr and std::cout streams are
*   made for this text control. Thus, it will never really display the messages in the real
*   standard streams and you can also used std::cout and std::cerr to log into this wxTextCtrl.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaStdLogger : public RheiaLogger
{
    DECLARE_DYNAMIC_CLASS( RheiaStdLogger )
public:
    /** log function overloads */
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message )
    {
        wxString premsg = ( level == RheiaLogging::error ) ? wxT("Error : ") : wxT("");
        const char* message = rcU2C( premsg + msg );

        if( level == RheiaLogging::error )
            std::cerr << message << std::endl;
        else
            std::cout << message << std::endl;
    }
};

/**
*	@class RheiaTimeStampableStdLogger
*
*	@brief RheiaTimeStampableStdLogger is the basic class for logging into the standard streams...
*
*   This class will choose accordingly to the given RheiaLogging::RheiaLogLevel the stream
*   in which to log. This logger cannot be configured and does not provide the application
*   with a specific configuration tool.
*
*   @note that in Rheia a specific window is displayed in the RheiaInformationManager's book
*   which is based on a wxTextCtrl and the redirection of std::cerr and std::cout streams are
*   made for this text control. Thus, it will never really display the messages in the real
*   standard streams and you can also used std::cout and std::cerr to log into this wxTextCtrl.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaTimeStampableStdLogger : public RheiaLogger
{
    DECLARE_DYNAMIC_CLASS( RheiaTimeStampableStdLogger )
public:
    /** log function overloads */
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message )
    {
        wxString premsg = ( level == RheiaLogging::error ) ? wxT("Error : ") : wxT("");

        wxDateTime timestamp(wxDateTime::UNow());
        premsg += wxString::Format( wxT("[%2.2d:%2.2d:%2.2d.%3.3d] "),
            timestamp.GetHour(),
            timestamp.GetMinute(),
            timestamp.GetSecond(),
            timestamp.GetMillisecond() );

        const char* message = rcU2C( premsg + msg );

        if( level == RheiaLogging::error )
            std::cerr << message << std::endl;
        else
            std::cout << message << std::endl;
    }
};

#endif
