/**
*   @file RheiaInfoMgrSettingsPanel.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#ifndef RheiaInfoMgrSettingsPanel_h_
#define RheiaInfoMgrSettingsPanel_h_

#include <RheiaBaseSettings.h>
#include <RheiaConfigurationPanel.h>
#include <wx/panel.h>
#include <wx/string.h>

class RheiaBookConfigurationPanel;

/**
*   @class RheiaInfoMgrSettingsPanel
*
*   @brief This is the basic class for mamanging RheiaLoggerManager settings
*
*   Mainly this panels load the logmgrconf_panel.xrc file in order to allow the user
*   to manage the logger manager configuration options.
*   Here the user can configure the following options :
*
*       + Specify if the log window shall be auto-hided or not and when it shall
*           be displayed if it is hided.
*       + Specify the font size for any TextCtrl loggers
*       + Configure the logger manager notebook aspect
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
class BASE_DLLEXPORT RheiaInfoMgrSettingsPanel : public RheiaConfigurationPanel
{
public:
    /*******************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    *******************************************************************************/
    /**
    *   Basic constructor taking the parent in input.
    *   @param parent the parent window
    */
	RheiaInfoMgrSettingsPanel( wxWindow* parent );
	
	/** destructor */
	virtual ~RheiaInfoMgrSettingsPanel() {};

    /*******************************************************************************
    *   METHODS TO OVERLOAD
    *******************************************************************************/
	/**
	*   @see RheiaConfigurationPanel for more info
	*   @return the panel's title.
	*/
	virtual wxString GetTitle() const { return wxT("Information Window Settings"); };

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

    /*******************************************************************************
    *   EVENTS TABLE
    *******************************************************************************/
    DECLARE_EVENT_TABLE()

    RheiaBookConfigurationPanel* m_panel;
};

#endif



