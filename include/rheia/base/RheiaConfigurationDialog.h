/**
*	@file RheiaConfigurationDialog.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 10-February-2010
*	@version 0.0.1
*/
#ifndef RheiaEnvVarsConfigurationDialog_h_
#define RheiaEnvVarsConfigurationDialog_h_

#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>

class RheiaConfigurationPanel;

/**
*	@class RheiaConfigurationDialog
*
*   @brief Dialog for managing configuration tools
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 10-February-2010
*	@version 0.0.1
*/

class BASE_DLLEXPORT RheiaConfigurationDialog : public wxDialog
{
public:
    /******************************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ******************************************************************************************************/
    /**
    *   Default constructor taking the parent in input
    *   @param parent parent window in which the dialog shall be created
    */
    RheiaConfigurationDialog(wxWindow* parent);

    /******************************************************************************************************
    *   METHODS
    ******************************************************************************************************/
    /**
    *   End modal function overload
    *   This method is used to perform some checks when the user acts
    *   on the OK or CANCEL button in the dialog. It will call wxDialog::EndModal
    *   at the end.
    *   @param retCode button Id that has been clicked by the user. For this dialog it
    *   is respectively wxID_OK or wxID_CANCEL for OK and CANCEL buttons.
    */
    virtual void EndModal(int retCode);

    /** Associated the configuration panel */
    void SetConfigurationTool( RheiaConfigurationPanel* panel );

private:
    RheiaConfigurationPanel* m_panel;
    wxBoxSizer* m_sizer;
};

#endif

