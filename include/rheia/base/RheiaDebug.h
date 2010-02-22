/**
*   @file RheiaDebug.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 21-February-2009
*/
#ifndef RheiaDebug_h_
#define RheiaDebug_h_

#include "RheiaBaseSettings.h"

#include <wx/log.h>

/**
*   @class RheiaDebug
*	@breif basic debugging window which do nothing if RHEIA_DEBUG is not defined
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 21-February-2009
*/
class BASE_DLLEXPORT RheiaDebug
{
public :
	static void Log( const wxChar* format, ... );
	static void Free();
	
private :
#ifdef RHEIA_DEBUG
	static wxLog* m_debugLogTarget;
#endif
};

#endif
