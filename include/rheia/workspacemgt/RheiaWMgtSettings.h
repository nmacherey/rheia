/**
*   @file RheiaWMgtSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaWMgtSettings_h_
#define RheiaWMgtSettings_h_

#ifdef WIN32
#ifndef WMGT_DLLEXPORT
#ifdef RHEIA_WMGT_MAKINGDLL
#define WMGT_DLLEXPORT __declspec( dllexport )
#else
#define WMGT_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef WMGT_DLLEXPORT
#ifdef REHIA_WMGT_MAKINGDLL
#define WMGT_DLLEXPORT
#else
#define WMGT_DLLEXPORT
#endif
#endif
#endif

#endif





