/**
*   @file RheiaPMgtSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaPMgtSettings_h_
#define RheiaPMgtSettings_h_

#ifdef WIN32
#ifndef PMGT_DLLEXPORT
#ifdef REHIA_PMGT_MAKINGDLL
#define PMGT_DLLEXPORT __declspec( dllexport )
#else
#define PMGT_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef PMGT_DLLEXPORT
#ifdef REHIA_PMGT_MAKINGDLL
#define PMGT_DLLEXPORT
#else
#define PMGT_DLLEXPORT
#endif
#endif
#endif

#endif




