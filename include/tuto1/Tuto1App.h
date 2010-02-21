#ifndef Tuto1App_h_
#define Tuto1App_h_

/************************************************
This is the Header File for Tuto1App

 * Author: Nicolas Macherey
 * Date: 2008.11.6
 ************************************************/
#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#include <Tuto1MainFrame.h>
#include <RheiaManager.h>
#include <wx/app.h>

/************************************************************************************************//**
*	\class Tuto1App
*	\brief The Tuto1App Class is the main WxWidgets Application for the toolbox
*
*
*	@author			Nicolas Macherey (nm@graymat.fr)
*	@date			06-Nov-2008
****************************************************************************************************/

class Tuto1App : public wxApp
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

	/*! Membership function for initializing the main frame */
	Tuto1MainFrame *InitMainFrame();

private:

	/*! Init the global application ressources */
	bool InitXRCStuff();

	/** Loads the global configuration */
	bool LoadConfig();

	int ParseCmdLine(Tuto1MainFrame* handlerFrame);

private :
	/**********************************************************************************************
											PRIVATE VARIABLES
	**********************************************************************************************/
	Tuto1MainFrame *MainFrame;

	int start_window_point_x;
	int start_window_point_y;
	int window_width;
	int window_height;

private :
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(Tuto1App)

#endif

