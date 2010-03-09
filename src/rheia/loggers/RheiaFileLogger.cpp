/**
*   @file RheiaFileLogger.cpp
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#include "RheiaFileLogger.h"
#include "RheiaLoggerManager.h"

IMPLEMENT_DYNAMIC_CLASS( RheiaFileLogger , RheiaLogger );
IMPLEMENT_DYNAMIC_CLASS( RheiaTimeStampableFileLogger , RheiaFileLogger );

namespace FileLogger
{
    REGISTER_LOGGER( RheiaFileLogger , wxT("FileLogger") );
};

namespace TimeFileLogger
{
    REGISTER_LOGGER( RheiaTimeStampableFileLogger , wxT("TimeFileLogger") );
};


RheiaFileLogger::RheiaFileLogger(const wxString& filename) :
    m_file(filename, wxT("wb"))
{
}


bool RheiaFileLogger::SetFile(const wxString& filename)
{
    RheiaFileLogger::Close();

    m_file.Open( filename, _T("wb") );
    return m_file.IsOpened();
}

void RheiaFileLogger::Log( const wxString& msg, RheiaLogging::RheiaLogLevel level )
{
    if(!m_file.IsOpened())
        return;

    wxString premsg = ( level == RheiaLogging::error ) ? wxT("Error : ") : wxT("");
    const char* message = rcU2C( premsg + msg );

    fputs( message , m_file.fp() );
    fputs( "\n" , m_file.fp());
}


RheiaConfigurationPanel* RheiaFileLogger::GetConfigurationTool( wxWindow* WXUNUSED(parent) )
{
    return NULL;
}


void RheiaTimeStampableFileLogger::Log( const wxString& msg, RheiaLogging::RheiaLogLevel level )
{
    if(!m_file.IsOpened())
        return;

    wxString premsg = ( level == RheiaLogging::error ) ? wxT("Error : ") : wxT("");

    wxDateTime timestamp(wxDateTime::UNow());
    premsg += wxString::Format( wxT("[%2.2d:%2.2d:%2.2d.%3.3d] "),
        timestamp.GetHour(),
        timestamp.GetMinute(),
        timestamp.GetSecond(),
        timestamp.GetMillisecond() );

    RheiaFileLogger::Log( msg , level );
};
