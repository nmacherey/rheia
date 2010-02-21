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

#include <RheiaAppBase.h>
#include <RheiaMainFrame.h>
#include <RheiaManager.h>
#include <wx/app.h>

/************************************************************************************************//**
*	\class RheiaApp
*	\brief The RheiaApp Class is the main WxWidgets Application for the toolbox
*
*
*	@author			Nicolas Macherey (nm@graymat.fr)
*	@date			06-Nov-2008
****************************************************************************************************/

class RheiaApp : public RheiaAppBase
{
public:
	RheiaApp() : MainFrame(NULL) , m_noSplash(false){};
	/**********************************************************************************************
											METHODS
	**********************************************************************************************/
	/*! Callback OnInit() overloads for initializing the application */
	bool OnInit();

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

	/*! Membership function for initializing the main frame */
	RheiaMainFrame *InitMainFrame();

private:
	/**********************************************************************************************
											PRIVATE METHODS
	**********************************************************************************************/
	/** Loads the global configuration */
	bool LoadConfig();

private :
	/**********************************************************************************************
											PRIVATE VARIABLES
	**********************************************************************************************/
	RheiaMainFrame *MainFrame;
	bool m_noSplash;

	int start_window_point_x;
	int start_window_point_y;
	int window_width;
	int window_height;

private :
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(RheiaApp)

#endif
