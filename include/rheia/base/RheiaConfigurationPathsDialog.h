/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaConfigurationPathsDialog.h
*
*   Revision : 20-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#ifndef RheiaConfigurationPathsDialog_h_
#define RheiaConfigurationPathsDialog_h_

#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>


class wxListbookEvent;
class wxCheckListBox;

/**
*	@class RheiaConfigurationPathsDialog
*
*   @brief Main dialog for displaying RheiaStandardPaths in developer's mode.
*
*   This dialog will only be accessible if the RHEIA_DEVELOPER preprocessor option
*   is defined at compilation time. It has been written to help new Rheia Developers
*   to know on each machine they run Rheia what are the Standard path used either
*   in Release or Debug mode.
*
*   If you are not a Rheia Developer you may not worry about this dialog.
*   @note that this dialog is very simple and is loading itself from the paths_dialog.xrc
*   file. You may not find here very complex things about dialog management in Rheia.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/

class BASE_DLLEXPORT RheiaConfigurationPathsDialog : public wxDialog
{
public:
    /******************************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ******************************************************************************************************/
    /**
    *   Default constructor taking the parent in input
    *   @param parent parent window in which the dialog shall be created
    */
    RheiaConfigurationPathsDialog(wxWindow* parent);
	
	/** default destructor */
	virtual ~RheiaConfigurationPathsDialog() {};

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

protected:

    /******************************************************************************************************
    *   PRIVATE METHODS
    ******************************************************************************************************/
    /**
    *   Update the list
    *   This method is used to update the Release Paths list
    */
    void DoUpdateList();

    /**
    *   Update the list Debug
    *   This method is used to update the Debug path list
    */
    void DoUpdateDebugList();

private:
    /******************************************************************************************************
    *   EVENT TABLE
    ******************************************************************************************************/
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#endif

