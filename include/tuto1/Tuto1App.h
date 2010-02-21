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

#include <RheiaAppBase.h>
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

class Tuto1App : public RheiaAppBase
{
public:
	/**********************************************************************************************
											METHODS
	**********************************************************************************************/
	/*! Callback OnInit() overloads for initializing the application */
	bool OnInit();

	/*! Membership function for initializing the main frame */
	Tuto1MainFrame *InitMainFrame();

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

