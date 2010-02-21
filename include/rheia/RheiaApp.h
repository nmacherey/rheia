#ifndef RheiaApp_h_
#define RheiaApp_h_

/************************************************
This is the Header File for RheiaApp

 * Author: Nicolas Macherey
 * Date: 2008.11.6
 ************************************************/
#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#include <RheiaMainFrame.h>
#include <RheiaManager.h>
#include <wx/app.h>

class wxSingleInstanceChecker;
/************************************************************************************************//**
*	\class RheiaApp
*	\brief The RheiaApp Class is the main WxWidgets Application for the toolbox
*
*
*	@author			Nicolas Macherey (nm@graymat.fr)
*	@date			06-Nov-2008
****************************************************************************************************/

class RheiaApp : public wxApp
{
public:
	/**********************************************************************************************
											METHODS
	**********************************************************************************************/
	/*! Callback OnInit() overloads for initializing the application */
	bool OnInit();

	/*! Callback OnExit() overloads for destrying the application and its content */
	virtual int OnExit();

	/*! Callback OnRun() to executes when the application starts its run */
	virtual int OnRun();

	/*! Returns the application path */
	wxString GetAppPath() const{return wxEmptyString;};

	/*! Parse the command line given to the application
	*
	*	@param handlerFrame MainFrame handler to send info when parsing the command line
	*/
	int ParseCmdLine(RheiaMainFrame* handlerFrame);

	/*! Callback OnAppActivate, called when the application recieves the event : EVT_ACTIVATE_APP */
	void OnAppActivate(wxActivateEvent& event){};

	/*! OnCmdLineParsed() Callback overload, called when the command line has been parsed
	*
	*	@param parser The wxCmdLineParser that has parsed the command line
	*/
	bool OnCmdLineParsed(wxCmdLineParser& parser);

	/*! Execption handler callback */
	void OnFatalException(){};

	/*! Membership function for initializing the main frame */
	RheiaMainFrame *InitMainFrame();

private:
	/**********************************************************************************************
											PRIVATE METHODS
	**********************************************************************************************/
	/*! Launches a dialog to complain a bad install if somme errors append during the initialisation */
	void ComplainBadInstall(){};

	/*! Setup Layout info and user options of the application */
	void SetupPersonality(const wxString& personality){};

	/*! Load files given in argument throug the command line parser */
	void LoadDelayedFiles(RheiaMainFrame* frame){};

	/*! Init the global application ressources */
	bool InitXRCStuff();

	/** Loads the global configuration */
	bool LoadConfig();

private :
	/**********************************************************************************************
											PRIVATE VARIABLES
	**********************************************************************************************/
	RheiaMainFrame *MainFrame;

	int start_window_point_x;
	int start_window_point_y;
	int window_width;
	int window_height;

	bool m_HasProject;
	bool m_HasWorkSpace;
	bool m_NoSplash;
	bool m_HasDebugLog;
	bool m_NoCrashHandler;

	wxString m_Script;
	wxString m_AutoFile;
	wxString m_Prefix;

	wxSingleInstanceChecker *m_singleInstanceChecker;

private :
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(RheiaApp)

#endif
