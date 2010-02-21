/**
*   @file RheiaBaseSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaBaseSettings_h_
#define RheiaBaseSettings_h_

#ifdef WIN32
#ifndef BASE_DLLEXPORT
#ifdef REHIA_BASE_MAKINGDLL
#define BASE_DLLEXPORT __declspec( dllexport )
#else
#define BASE_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef BASE_DLLEXPORT
#ifdef REHIA_BASE_MAKINGDLL
#define BASE_DLLEXPORT
#else
#define BASE_DLLEXPORT
#endif
#endif
#endif

#endif


