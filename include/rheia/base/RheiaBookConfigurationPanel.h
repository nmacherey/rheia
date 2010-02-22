/**
*   @file RheiaBookConfigurationPanel.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#ifndef RheiaBookConfigurationPanel_h_
#define RheiaBookConfigurationPanel_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaConfigurationPanel.h>
#include <wx/panel.h>
#include <wx/string.h>

class RheiaConfigurationManager;

/**
*   @class RheiaBookConfigurationPanel
*
*   @brief This is the base class for defining a configuration panel in Rheia
*
*   Configuration panel's can have many different usage in Rheia. Mainly they are
*   used in Rheia's configuration dialog for managing special options in the main
*   application such as Application Startup configuration or network configuration.
*   However you have to derive your configuration panel from this class if you want
*   it to be properly managed by the application.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
class BASE_DLLEXPORT RheiaBookConfigurationPanel : public RheiaConfigurationPanel
{
public:
    /*******************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    *******************************************************************************/
    /**
    *   Default constructor
    *   This constructor has been kept without any parent Window and Id to allow
    *   the creation of this panel using the wxWidget XML Resource system, if you
    *   do not want to do so simply call wxPanel::Create.
    */
	RheiaBookConfigurationPanel(wxWindow *parent,RheiaConfigurationManager* cfg);
	
	/** default destructor */
	virtual ~RheiaBookConfigurationPanel() {};

    /*******************************************************************************
    *   METHODS TO OVERLOAD
    *******************************************************************************/
	/**
	*   This method is used to display the panel's title either in a dialog
	*   if the application loads it in a configuration dialog or in a book page
	*   title if it is loaded with other configuration tools.
	*   You have to overload this method in order to provide the application with
	*   the configuration tool title.
	*
	*   @return the panel's title.
	*/
	virtual wxString GetTitle() const {return wxT("Book configuration panel");};

	/**
	*   This method is used to get the bitmap base name for the configuration tool.
	*   Any configuration panel can be loaded in a book displaying bitmaps to help
	*   application users to remember the configuration tool.
	*
	*   Rheia Configuration tools can have two different bitmap sizes : 48x48 and 80x80
	*   Hence you must supply the application with 4 bitmaps which will be loaded by Rheia
	*   accordingly to the following rule :
	*   \<basename\>_\<size\>.png and \<basename\>_\<size\>-off.png...
	*   The extension -off is used when the panel is not selected by the user in order to
	*   display a proper information.
	*
	*   @note that bitmaps in rheia must be PNG bitmaps
	*
	*   For example il you bitmap is called "app_conf", you have to provide with the four
	*   following bitmaps :
	*       + app_conf_48.png
	*       + app_conf_48-off.png
	*       + app_conf_80.png
	*       + app_conf_80-off.png
	*
	*   @return the panel's bitmap base name. You must supply two bitmaps:
	*/
	virtual wxString GetBitmapBaseName() const {return wxEmptyString;};


	/**
	*   As the application doesn't know what kind of configuration you've done,
	*   this method will be called when the configuration task is validated by
	*   the user. You can perform here any kind of validation and if something is
	*   wrong simply display an error message and return false. The validation will
	*   be cancelled.
	*
	*   @return If this method returns true the user's action will be validated.
	*/
	virtual bool OnApply();

	/**
	*   Any configuration panels are loaded in a parent control either a dialog or
	*   a wizard. If the user cancels the action this method is called in order to
	*   allow you to perform specfic management when such an action is made.
	*   @return This method shall simply returns true, if the configuration tool can
	*   be cancelled or false if it can't.
	*/
	virtual bool OnCancel();

private :
    RheiaConfigurationManager* m_cfg;
};

#endif

