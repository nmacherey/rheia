/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
* 	
* 	This class allow you to have a Debug window indepent of the application displayed 
* 	which will show you the wxWidgets logs in. 
* 	This class is static and is more like a global namespace, use RheiaDebug::Log( ) to log in the window
* 	
* 	You should don't care about removing calls to this class in Release mode because in this mode it is really doing
* 	nothing...
* 
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 21-February-2009
*/
class BASE_DLLEXPORT RheiaDebug
{
public :
#ifndef SWIG
	/** The log method is working as the wxString::Format method which is like the
	 * printf one but with wxStrings,
	 * this will create and redirect the wxLog to the independent Log window 
	 */
	static void Log( const wxChar* format, ... );
#else
	static void Log( const wxString& str )
	{
		RheiaDebug::Log( str );
	}
#endif
	
	/** You shal don't care about this method it is called in the RheiaManager::Close method
	 * at the very end of the application shut down => so you shall be able to use this class
	 * at anytime Rheia gives you the hand on the application
	 */
	static void Free();
	
private :

//#ifdef RHEIA_DEBUG
	static wxLogWindow* m_debugLogTarget;
//#endif
};

#endif
