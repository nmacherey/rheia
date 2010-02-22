/**
*   @file RheiaAppBase.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-February-2010
*/
#ifndef RheiaAppBase_h_
#define RheiaAppBase_h_

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
* 	A wxWidget application runs in 3 main steps :
* 		- Initialization (wxApp::OnInit) : this method is used for basic application's initialization,
* 				if returns false, the application starts will be canceled.
* 		- Running (wxApp::OnRun) : this method simulates the infinity loop in whic the application thread
* 				is running
* 		- Exit (wxApp::OnExit) : this method is called before the application exists to allow you to perform 
* 				final and global memory freeing before closing the thread.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-February-2010
*/
class BASE_DLLEXPORT RheiaAppBase : public wxApp
{

public :
	/** Basic constructor */
	RheiaAppBase() : 
		wxApp(),
		m_singleInstanceChecker(0),
		m_splash(NULL) { };
		
	/** destructor */
	virtual ~RheiaAppBase();
		
    /**********************************************************************************************
	* BASIC METHODS
	**********************************************************************************************/

	/** You have to call this method when overriding your wxApp's OnInit method
	 * This will return true if all basic initializations have been done properly
	 * This method will init the locale under linux, the clipboard and all filesystem
	 * and xmlRessource handlers from wxWidgets
	 */
	bool DoBasicInitializations();
	
	/** Using this class tou can check for single instance if you want that users can run
	 * only one instance of the application at the same time.
	 * simply skip this if you do not want to do so ... This method shall be called during OnInit 
	 * method of your application.
	 * @return false if an other instance of the application already exists
	 * and display an error in this case you simply have to return false.
	 */
	bool CheckForSingleInstance();
	
	/** This method is used to show the splash screen image... simply give the image path
	 * in input and the splash screen will be shown...
	 * @param path bitmap path in png format for the splashscreen
	 */
	void ShowSplashScreen( const wxString& path );
	
	/** If you've show the splash screen you can use this method to hide it */
	void HideSplashScreen();
	
	/**	This method is used in order to initilize all xrc resources that can be found
	 * in your resource.zip file. commonly in this zip file all Rheia panels are located
	 * however using postbuildsteps you might have to add additionnal resources. This
	 * method will ensure that they are all loaded.
	 */
	bool InitXRCStuff();
	
	/** Callback OnRun() to executes when the application starts its run */
	virtual int OnRun();
	
	/** Callback OnExit() overloads for destrying the application and its content */
	virtual int OnExit();
	
	/** When exiting the application you will need to destroy different objects 
	 * this method is called before calling RheiaManager::Get()->Close() in order
	 * to allow you freeing global variables before exiting the application
	 */
	virtual void OnPreManagerDestroy() {};
	
	/** You have to call this method at the very end of the application's OnInit method 
	 * It will notify for application finalization.
	 */
	void StartUpFinalStep();
	
	/** Get the application's name */
	wxString AppName() {return m_appName;};

protected :
	/**********************************************************************************************
	* ATTRIBUTES
	**********************************************************************************************/
	
    wxString m_appName;
    wxSingleInstanceChecker *m_singleInstanceChecker;
    RheiaSplashScreen* m_splash;
};

#endif
