/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaProjectCreationPage.h
*
*   @brief This is the main page for creating a new project from a specific category
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 03-May-2009
*   @version 0.0.1
*/

#ifndef RheiaProjectCreationPage_h_
#define RheiaProjectCreationPage_h_

#include <RheiaWMgtSettings.h>
#include <RheiaGlobals.h>

/* imports */
class RheiaEnvironmentPlugin;
class wxListCtrl;
class wxChoice;

/**
*   @class RheiaProjectCreationPage
*
*   @brief This is the main class for managing available projects for a given category
*
*   When you create a new project in Rheia a dialog is displayed. As many different kind of
*   projects can be provided by different plugins, each project is ordered in a given category.
*   More over any project is specific to a class of application or a company. For theses reasons
*   this page is managing the projects categories for a given class of application.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 03-May-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectCreationPage : public wxPanel
{

public :

    /**
    *   Basic constructor
    *   @param parent parent window for this page
    *   @param appClass the given class of application name
    */
    RheiaProjectCreationPage( wxWindow* parent , RheiaEnvironmentPlugin* plugin );

    /**
    *   Default destructor
    */
    virtual ~RheiaProjectCreationPage();

    /**
    *   Callback used when the category changed
    */
    void OnCategoryChanged(wxCommandEvent& event);

    /**
    *   Build the categories combo box
    */
    void BuildCategories();

    /**
    *   Build the list
    */
    void BuildList();

    /**
    *   Clear the list
    */
    void ClearList();

    /**
    *   Get the selected project
    */
    wxString GetProject(){return m_projectName;};

    /**
    *   Get the selected project category
    */
    wxString GetCategory(){return m_categoryName;};

    /**
    *   Get the listctrl from the page
    */
    wxListCtrl* GetList();

    /**
    *   Get the combobox from this page
    */
    wxChoice* GetCategorySelection();

    /**
    *   Get the selected project index from the list
    */
    int GetSelectedProjectIndex();

private :

    RheiaEnvironmentPlugin* m_plugin;

    wxString m_appClass;
    wxString m_projectName;
    wxString m_categoryName;
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#endif
