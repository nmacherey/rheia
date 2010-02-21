/**
*   @file RheiaAppBase.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-February-2010
*/
#ifndef RheiaApp_h_
#define RheiaApp_h_

#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#include <RheiaBaseSettings.h>
#include <wx/app.h>

class wxSingleInstanceChecker;
class RheiaSplashScreen;

/**
*   @class RheiaAppBase
*   @brief Basic class for creating an application based on Rheia
*
*   RheiaAppBase is a base class which will provide you with a faster way to implement
*   your application. The basic methods are defined in order to start, run and exit your application
*   properly.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-February-2010
*/
class BASE_DLLEXPORT RheiaAppBase : public wxApp
{

public :
    /**********************************************************************************************
	* BASIC METHODS
	**********************************************************************************************/

	/** You have to call this method when overriding your wxApp's OnInit method
	* This will return true if all basic initializations have been done properly
	* This method will init the locale under linux, the clipboard and all filesystem
	* and xmlRessource handlers from wxWidgets
	*/
	bool DoBasicInitializations();

protected :
    wxString m_appName;
    wxSingleInstanceChecker *m_singleInstanceChecker;
    RheiaSplashScreen* m_splash;
};

#endif
