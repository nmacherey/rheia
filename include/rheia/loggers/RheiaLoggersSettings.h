/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaLoggersSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaLoggersSettings_h_
#define RheiaLoggersSettings_h_

#ifdef WIN32
#ifndef LOGGERS_DLLEXPORT
#ifdef RHEIA_LOGGERS_MAKINGDLL
#define LOGGERS_DLLEXPORT __declspec( dllexport )
#else
#define LOGGERS_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef LOGGERS_DLLEXPORT
#ifdef REHIA_LOGGERS_MAKINGDLL
#define LOGGERS_DLLEXPORT
#else
#define LOGGERS_DLLEXPORT
#endif
#endif
#endif

#endif



