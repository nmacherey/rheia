/**
*   @file RheiaHtmlLogger.cpp
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#include "RheiaHtmlLogger.h"
#include "RheiaGlobals.h"
#include "RheiaLoggerManager.h"
#include "RheiaStandardPaths.h"
#include "RheiaConfigurationManager.h"
#include "RheiaManager.h"
#include "RheiaHtmlLoggerPage.h"

IMPLEMENT_DYNAMIC_CLASS( RheiaHtmlLogger , RheiaFileLogger );
IMPLEMENT_DYNAMIC_CLASS( RheiaTimeStampableHtmlLogger , RheiaHtmlLogger );

namespace HtmlLogger
{
    REGISTER_LOGGER( RheiaHtmlLogger , wxT("HtmlLogger") );
};

namespace TimeHtmlLogger
{
    REGISTER_LOGGER( RheiaTimeStampableHtmlLogger , wxT("TimeHtmlLogger") );
};

RheiaHtmlHeader::RheiaHtmlHeader() :
    message     (wxT("font-size: 12pt;")),
    info        (wxT("color: black; font-size: 12pt;")),
    warning     (wxT("color: blue; margin-left: 2em;")),
    success     (wxT("margin-left: 2em; border-left: 1px solid black;")),
    error       (wxT("margin-left: 2em; border-left: 1px solid red;")),
    fatalerror  (wxT("color: red; font-weight: bold;")),
    syserror    (wxT("color: maroon;")),
    status      (wxT("color: green; font-style: italic;")),
    debug       (wxT("color: blue; font-style: italic;")),
    trace       (wxT("color: blue; font-style: italic;")),
    h1          (wxT("font-size: 16pt;")),
    h2          (wxT("font-size: 14pt;")),
    timestamp   (wxT("font-family: Arial, Helvetica, \"Bitstream Vera Sans\", sans; font-style: italic;"))
{
}

RheiaHtmlHeader::RheiaHtmlHeader(const RheiaHtmlHeader& rhs):
    message(rhs.message),
    warning(rhs.warning),
    success( rhs.success ),
    error( rhs.error ),
    fatalerror( rhs.fatalerror ),
    info(rhs.info),
    status( rhs.status ),
    syserror( rhs.syserror ),
    debug( rhs.debug ),
    trace( rhs.trace ),
    h1(rhs.h1),
    h2(rhs.h2),
    timestamp(rhs.timestamp)
{
}

RheiaHtmlLogger::RheiaHtmlLogger(const wxString& filename):
    RheiaFileLogger( filename ),
    m_window(NULL)
{
    SetFile(filename);
}

RheiaHtmlLogger::RheiaHtmlLogger() :
    m_window(NULL)
{
    wxString path = RheiaStandardPaths::DataDirectoryUser( ) + wxT("/htmllog.html");
    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager( wxT("RheiaHtmlLogger") );
    path = cfg->Read( wxT("/default_file") , path );
    SetFile(path);
}

bool RheiaHtmlLogger::SetFile(const wxString& filename)
{
    m_page.Clear();
    RheiaFileLogger::Open(filename);

    m_page = wxT("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en-US\" lang=\"en-US\">\n<head>\n<title>Html log</title>\n<style>\n");

    if( !m_header.message.IsEmpty() )
        m_page += wxT(".message { ") + m_header.message + wxT(" }\n");
    if( !m_header.warning.IsEmpty() )
        m_page += wxT(".warning { ") + m_header.warning + wxT(" }\n");
    if( !m_header.success.IsEmpty() )
        m_page += wxT(".success { ") + m_header.success + wxT(" }\n");
    if( !m_header.error.IsEmpty() )
        m_page += wxT(".error { ") + m_header.error + wxT(" }\n");
    if( !m_header.fatalerror.IsEmpty() )
        m_page += wxT(".fatalerror { ") + m_header.fatalerror + wxT(" }\n");
    if( !m_header.info.IsEmpty() )
        m_page += wxT(".info { ") + m_header.info + wxT(" }\n");
    if( !m_header.status.IsEmpty() )
        m_page += wxT(".status { ") + m_header.status + wxT(" }\n");
    if( !m_header.syserror.IsEmpty() )
        m_page += wxT(".syserror { ") + m_header.syserror + wxT(" }\n");
    if( !m_header.debug.IsEmpty() )
        m_page += wxT(".debug { ") + m_header.debug + wxT(" }\n");
    if( !m_header.trace.IsEmpty() )
        m_page += wxT(".trace { ") + m_header.trace + wxT(" }\n");
    if( !m_header.h1.IsEmpty() )
        m_page += wxT("h1 { ") + m_header.h1 + wxT(" }\n");
    if( !m_header.h2.IsEmpty() )
        m_page += wxT("h2 { ") + m_header.h2 + wxT(" }\n");
    if( !m_header.timestamp.IsEmpty() )
        m_page += wxT(".timestamp { ") + m_header.timestamp + wxT(" }\n");

    m_page += wxT("</style>\n</head>\n\n<body>");

    fprintf(m_file.fp(), "%s", rcU2C(m_page));

    return true;
}

void RheiaHtmlLogger::Log( const wxString& msg, RheiaLogging::RheiaLogLevel level )
{
    wxString message;
    if( level == RheiaLogging::message )
        message += wxT("\n\t<span class=\"message\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::warning )
        message += wxT("\n\t<span class=\"warning\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::success )
        message += wxT("\n\t<span class=\"success\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::error )
        message += wxT("\n\t<span class=\"error\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::fatalerror )
        message += wxT("\n\t<span class=\"fatalerror\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::info )
        message += wxT("\n\t<span class=\"info\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::status )
        message += wxT("\n\t<span class=\"status\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::syserror )
        message += wxT("\n\t<span class=\"syserror\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::debug )
        message += wxT("\n\t<span class=\"debug\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::trace )
        message += wxT("\n\t<span class=\"trace\">") + msg + wxT("</span>");

    message += wxT("\n\t<br/>");

    fputs(rcU2C(message), m_file.fp());
    m_page += message;

    if( m_window != NULL )
        m_window->SetPage( m_page + wxT("\n</body>\n</html>\n") );
}

bool RheiaHtmlLogger::Open(const wxString& filename)
{
    return SetFile( filename );
}

void RheiaHtmlLogger::Close()
{
    fputs("\n</body>\n</html>\n", m_file.fp());
    RheiaFileLogger::Close();
}

RheiaBookPage* RheiaHtmlLogger::BuildMainWindow( wxWindow* parent )
{
    m_window = new RheiaHtmlLoggerPage( parent , this );
    return m_window;
}


void RheiaTimeStampableHtmlLogger::Log( const wxString& msg, RheiaLogging::RheiaLogLevel level )
{
    wxString message;

    if( level == RheiaLogging::message )
        message += wxT("\n\t<span class=\"message\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::warning )
        message += wxT("\n\t<span class=\"warning\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::success )
        message += wxT("\n\t<span class=\"success\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::error )
        message += wxT("\n\t<span class=\"error\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::fatalerror )
        message += wxT("\n\t<span class=\"fatalerror\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::info )
        message += wxT("\n\t<span class=\"info\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::status )
        message += wxT("\n\t<span class=\"status\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::syserror )
        message += wxT("\n\t<span class=\"syserror\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::debug )
        message += wxT("\n\t<span class=\"debug\">") + msg + wxT("</span>");
    else if( level == RheiaLogging::trace )
        message += wxT("\n\t<span class=\"trace\">") + msg + wxT("</span>");

    message += wxT("\n\t<br/>");

    wxString premsg;

    wxDateTime timestamp(wxDateTime::UNow());
    premsg += wxString::Format( wxT("[%2.2d:%2.2d:%2.2d.%3.3d] :"),
        timestamp.GetHour(),
        timestamp.GetMinute(),
        timestamp.GetSecond(),
        timestamp.GetMillisecond() );

    wxString fullmsg = wxT("\n\t<span class=\"timestamp\">") + premsg + wxT("</span>");
    fullmsg += message;

    fputs(rcU2C(fullmsg), m_file.fp());
    m_page += fullmsg;

    if( m_window != NULL )
        m_window->SetPage( m_page + wxT("\n</body>\n</html>\n") );
}
