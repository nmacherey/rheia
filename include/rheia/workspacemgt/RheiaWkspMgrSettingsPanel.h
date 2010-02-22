/**
*   @file RheiaWkspMgrSettingsPanel.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#ifndef RheiaWkspMgrSettingsPanel_h_
#define RheiaWkspMgrSettingsPanel_h_

#include <RheiaWMgtSettings.h>
#include <RheiaConfigurationPanel.h>
#include <wx/panel.h>
#include <wx/string.h>

/**
*   @class RheiaWkspMgrSettingsPanel
*
*   @brief This is the basic class for mamanging Rheia's Management pane's settings
*
*   Mainly this panels load the wkspmgrconf_panel.xrc file in order to allow the user
*   to manage the left pane's configuration options.
*   Here the user can configure the following options :
*
*       + Configure the workspace manager notebook aspect
*       + Configure the tree control appearence
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
class WMGT_DLLEXPORT RheiaWkspMgrSettingsPanel : public RheiaConfigurationPanel
{
public:
    /*******************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    *******************************************************************************/
    /**
    *   Basic constructor taking the parent in input.
    *   @param parent the parent window
    */
	RheiaWkspMgrSettingsPanel( wxWindow* parent );
	
	/** destructor */
	virtual ~RheiaWkspMgrSettingsPanel() {};

    /*******************************************************************************
    *   METHODS TO OVERLOAD
    *******************************************************************************/
	/**
	*   @see RheiaConfigurationPanel for more info
	*   @return the panel's title.
	*/
	virtual wxString GetTitle() const { return wxT("Management Window Settings"); };

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



