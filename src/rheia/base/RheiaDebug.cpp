/**
*   @file RheiaDebug.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 21-February-2009
*/

#include "RheiaDebug.h"

#ifdef RHEIA_DEBUG
wxLog* RheiaDebug::m_debugLogTarget = NULL;
#endif

void RheiaDebug::Log( const wxChar* format, ... )
{
#ifdef RHEIA_DEBUG
	if( m_debugLogTarget == NULL )
	{
		wxLog* log = wxLog::SetActiveTarget( NULL );
		m_debugLogTarget = new wxLogWindow( NULL, wxT( "Logging" ) );
		wxLog::SetActiveTarget( log );
	}
	wxLog* oldTarget = wxLog::SetActiveTarget( m_debugLogTarget );
	va_list argptr;
	va_start(argptr, format);

	wxString s;
	s.PrintfV(format, argptr);

	wxLogMessage(s);

	va_end(argptr);
	wxLog::SetActiveTarget( oldTarget );
#endif
}

void RheiaDebug::Free()
{
#ifdef RHEIA_DEBUG
	if( m_debugLogTarget != NULL )
		delete m_debugLogTarget;
#endif
}