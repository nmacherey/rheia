/**
*   @file RheiaPythonSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaPythonSettings_h_
#define RheiaPythonSettings_h_

#ifdef WIN32
#ifndef PYTHON_DLLEXPORT
#ifdef REHIA_PYTHON_MAKINGDLL
#define PYTHON_DLLEXPORT __declspec( dllexport )
#else
#define PYTHON_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef PYTHON_DLLEXPORT
#ifdef REHIA_PYTHON_MAKINGDLL
#define PYTHON_DLLEXPORT
#else
#define PYTHON_DLLEXPORT
#endif
#endif
#endif

#endif






