/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaEnvVarsConfigurationDialog.h
*
*   Revision : 20-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#ifndef RheiaEnvVarsConfigurationDialog_h_
#define RheiaEnvVarsConfigurationDialog_h_

#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>


class wxListbookEvent;
class wxCheckListBox;

/**
*	@class RheiaEnvVarsConfigurationDialog
*
*   @brief Dialog for managing Rheia environment variables
*
*   Environment variables are difficult task, because for each os you have different
*   environment varibales tables. The global one which is set for any program session
*   just before the initialisation of the program and the local one which can be
*   changed by the program itself and all its children processes will inherit of it.
*   There is an exception for the system PATH and LD_LIBRARY_PATH under linux which cannot
*   be modified at run time except for new processes.
*
*   However paths setted in the second panel of this will be used to look for libraries when
*   loading plugins and try to manage dependencies in it. mainly this is not very usefull for
*   your EndUsers as you have to set properly your environment variables for your plugins and
*   the application during the installation process.
*
*   With this dialog you can setup a new environment variable which is mainly assocaiting
*   a name in UPPERCASE with a path. And you can manage different paths that will be used
*   by rheia if a plugin loading failed.
*
*   @note that system variables will always be treated first by the application.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/

class BASE_DLLEXPORT RheiaEnvVarsConfigurationDialog : public wxDialog
{
public:
    /******************************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ******************************************************************************************************/
    /**
    *   Default constructor taking the parent in input
    *   @param parent parent window in which the dialog shall be created
    */
    RheiaEnvVarsConfigurationDialog(wxWindow* parent);
	
	/** destructor */
	virtual ~RheiaEnvVarsConfigurationDialog() {};

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
    *   Update the list of environment variables used by the application
    *   This is for the first list displayed in the dialog (up list)
    */
    void DoUpdateList();

    /**
    *   Update the list of paths used by the application
    *   This is for the second list displayed in the dialog (down list)
    */
    void DoUpdatePathList();

    /******************************************************************************************************
    *   EVENTS
    ******************************************************************************************************/
    /** Update ui event */
    void OnUpdateUI(wxUpdateUIEvent& event);

    /** Callback used when the user wants to add a new variable */
    void OnAddNewVariable( wxCommandEvent& event );

    /** Callback used when the user wants to delete a variable */
    void OnDeleteVariable( wxCommandEvent& event );

    /** Callback used when the user wants to edit a variable */
    void OnEditVariable( wxCommandEvent& event );

    /** Callback used when the user wants to add a new path */
    void OnAddNewPath( wxCommandEvent& event );

    /** Callback used when the user wants to delete a path */
    void OnDeletePath( wxCommandEvent& event );

private:
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#endif
