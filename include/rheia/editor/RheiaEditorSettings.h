/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaEditorSettings.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaEditorSettings_h_
#define RheiaEditorSettings_h_

#ifdef WIN32
#ifndef EDITOR_DLLEXPORT
#ifdef RHEIA_EDITOR_MAKINGDLL
#define EDITOR_DLLEXPORT __declspec( dllexport )
#else
#define EDITOR_DLLEXPORT __declspec( dllimport )
#endif
#endif
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4996 )
#pragma warning( disable: 4661 )
#else
#ifndef EDITOR_DLLEXPORT
#ifdef REHIA_EDITOR_MAKINGDLL
#define EDITOR_DLLEXPORT
#else
#define EDITOR_DLLEXPORT
#endif
#endif
#endif

#endif





