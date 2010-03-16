/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaApplicationGeneralPanel.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#ifndef RheiaApplicationGeneralPanel_h_
#define RheiaApplicationGeneralPanel_h_

#include <RheiaBaseSettings.h>
#include <RheiaConfigurationPanel.h>
#include <wx/panel.h>
#include <wx/string.h>

/**
*   @class RheiaApplicationGeneralPanel
*
*   @brief This is the basic class for mamanging application's general configuration
*
*   Mainly this panels load the appconf_panel.xrc file in order to allow the user
*   to manage general application configuration options.
*   Here the user can configure the following options :
*
*       + Show or not the welcome screen during application loading
*       + Show the application Start page
*       + Specify if the user do not want to have multile instance of the application
*           loaded at the same time
*       + Manage files associations (Windows Only)
*       + Choose what to do on application start, either open the last workspaces or open
*           a new empty workspace.
*       + Select the shell to run commands in when the application has specific commands to
*           run outside the application.
*       + Select the default terminal in which the shell shall be launched
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
class BASE_DLLEXPORT RheiaApplicationGeneralPanel : public RheiaConfigurationPanel
{
public:
    /*******************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    *******************************************************************************/
    /**
    *   Basic constructor taking the parent in input.
    *   @param parent the parent window
    */
	RheiaApplicationGeneralPanel( wxWindow* parent );
	
	/** default destrcutor */
	virtual ~RheiaApplicationGeneralPanel() {};

    /*******************************************************************************
    *   METHODS TO OVERLOAD
    *******************************************************************************/
	/**
	*   @see RheiaConfigurationPanel for more info
	*   @return the panel's title.
	*/
	virtual wxString GetTitle() const { return wxT("General Settings"); };

	/**
	*   This method is used to get the bitmap base name for the configuration tool.
	*   @see RheiaConfigurationPanel for more info
	*
	*   @return the panel's bitmap base name. You must supply two bitmaps:
	*/
	virtual wxString GetBitmapBaseName() const;

	/**
	*   @see RheiaConfigurationPanel for more info
	*   @return If this method returns true the user's action will be validated.
	*/
	virtual bool OnApply();

	/**
	*   @see RheiaConfigurationPanel for more info
	*   @return This method shall simply returns true, if the configuration tool can
	*   be cancelled or false if it can't.
	*/
	virtual bool OnCancel();

protected :
    /*******************************************************************************
    *   PRIVATE MEMBERS
    *******************************************************************************/
    /**
    *   This method is used to initialize the default environment for this configuration
    *   tool. Basically it is loading the default informations from the configuration
    *   manager and the default user profile.
    */
    void DoInitEnvironment();

    /**
    *   This method is used to save the configuration options setted by the user
    *   it will store it's informations in application's general user configuration
    */
    void DoSaveEnvironment();
};

#endif

