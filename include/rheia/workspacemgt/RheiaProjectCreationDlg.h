/**
*   @file RheiaProjectCreationDlg.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 25-April-2009
*   @version 0.0.1
*/

#ifndef RheiaProjectCreationDlg_h_
#define RheiaProjectCreationDlg_h_

#include <vector>
#include <RheiaWMgtSettings.h>
#include <RheiaGlobals.h>
#include <RheiaPluginManager.h>
#include <wx/listctrl.h>

/* imports */
class RheiaEnvironmentPlugin;
class RheiaProjectCreationPage;

/* wxWidgets imports */
class wxImageList;
class wxListCtrl;
class wxChoice;

/**
*   @class RheiaProjectCreationDlg
*
*   @brief This is the basic class for creating a project in rheia
*
*   When the user request to create a new project, he will be ask for a choice
*   of what kind of project he wants to create.
*   This class deals with RheiaProjectFactory for defining which projects are available
*   and list the number of categories in which projects are defined.
*
*   At the end if the user accept the creation, a project wizard will be launched and
*   additional steps will be achieved. However the above steps are defined by the project
*   itself and cannot be achieve untill the project has not been selected.
*
*   The created project will be added in the active workspace.
*
*   @note that the dialog is created from a wx xrc file...
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 25-April-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectCreationDlg : public wxDialog
{
public :
    /** Default constructor for building the dialog */
    RheiaProjectCreationDlg( wxWindow* parent );

    /** Default destructor */
    virtual ~RheiaProjectCreationDlg();

    /** End of dialog modal mode */
    virtual void EndModal(int retCode);

    /** Get the selected wizard name/title */
    const wxString& GetSelectedWizard(){return m_selwizard;};

    /** Check if the project shall be created in a new workspace or not */
    bool CreateInNewWorkspace() {return m_newwksp;};

protected:

    /** Used when something is done on the dialog */
    void OnUpdateUI(wxUpdateUIEvent& event);

    /** On change category selection */
    void OnChangeCategory(wxCommandEvent& event);

    /** Builds the list book pages */
    void BuildListFor(const wxString& category);

    /** Build the wizard list */
    void BuildList();

    /** Change the list view from the list control */
    void ChangeView();

    /** Callback used when the list view is requested to change */
    void OnViewChange(wxCommandEvent& event);

    /** Callback used when any list is activateded */
    void OnWizardActivated( wxListEvent& event );

private :
    /*********************************************************************************
    *   PRIVATE VARIABLES
    *********************************************************************************/
    wxImageList *m_lstImages;
    wxString m_selwizard;
    bool m_newwksp;

    DECLARE_EVENT_TABLE()
};

#endif
