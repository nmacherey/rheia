/**
*   @file RheiaUtilsSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaUtilsSettings_h_
#define RheiaUtilsSettings_h_

#ifdef WIN32
#ifndef UTILS_DLLEXPORT
#ifdef RHEIA_UTILS_MAKINGDLL
#define UTILS_DLLEXPORT __declspec( dllexport )
#else
#define UTILS_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef UTILS_DLLEXPORT
#ifdef REHIA_UTILS_MAKINGDLL
#define UTILS_DLLEXPORT
#else
#define UTILS_DLLEXPORT
#endif
#endif
#endif

#endif

