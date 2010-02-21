/**
*   @file RheiaProjectCreationWizard.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 27-April-2009
*   @version 0.0.1
*/

#ifndef RheiaProjectCreationWizard_h_
#define RheiaProjectCreationWizard_h_

#include <RheiaWMgtSettings.h>
#include <RheiaGlobals.h>

/* wxWidgets imports */
class wxWizardPageSimple;
class wxWizard;
class RheiaWorkspace;
class RheiaProject;
class RheiaWizardPageBase;
class RheiaWizardManager;
class RheiaManagedFrame;

/** Define an array of wizard pages */
WX_DEFINE_ARRAY(RheiaWizardPageBase*, WizardPagesArray);

/**
*   @class RheiaProjectCreationWizard
*
*   @brief This is the main abstract class for defining a project creation wizard in rheia
*
*   Any project in rheia must provide the application with a wizard that will perform its
*   first configuration steps.
*   A wizard is a set of pages that will represents different steps for the creation of a project.
*
*   A wizard for a specific project shall be registered in RheiaProjectWizardFactory in order
*   to associate a project to a wizard.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 27-April-2009
*   @version 0.0.1
*/

class WMGT_DLLEXPORT RheiaProjectCreationWizard : public wxEvtHandler
{
    friend class RheiaWizardManager;
public :

    /**
    *   Basic constructor for the wizard pages
    */
    RheiaProjectCreationWizard( wxWizard* wizard,RheiaManagedFrame* parent, RheiaWorkspace *workspace );

    /**
    *   Basic destructor
    */
    virtual ~RheiaProjectCreationWizard();

    /**
    *   Method used when the wizard pages needs to be built.
    *   this method is simply loading calling DoBuildPages before
    *   chaining the pages for the wizard.
    */
    void BuildPages();

    /**
    *   method used to get the wizard bitmap
    */
    const wxBitmap& GetBitmap() {m_wizardPNG = DoLoadBitmap() ; return m_wizardPNG;}

    /**
    *   Get the wizard title
    */
    wxString GetTitle() { m_title = DoSetTitle(); return m_title ;};

    /**
    *   Get the pages array for the wizard
    */
    WizardPagesArray& GetPages(){return m_pages;};

    /**
    *   Method that you have to overload in order to get the project
    *   back to the main application.
    *   If anything is wrong or the wizard is cancelled you shall return
    *   NULL.
    */
    virtual RheiaProject* GetProject() = 0;

    /**
    *   Method that you have to overload in order to achieve your specific stuff when
    *   the wizard is cancelled.
    */
    virtual void OnWizardCancel() = 0;

    /**
    *   Method that you have to overload in order to achieve your specific stuff when
    *   the wizard is finished
    */
    virtual void OnWizardFinished() = 0;

protected :

    /**
    *   This method is used when the wizard pages needs to be built
    *   you have to overload this method in order to add pages to the
    *   object's pages array in order to be chained before launching the
    *   wizard.
    *
    *   @note that the pages shall be added in the array in the wright order
    *   that has to be chained
    */
    virtual void DoBuildPages() = 0;

    /**
    *   method used to load the wizard image
    *   you have to overload this method in order to load your wizard
    *   bitmap.
    *   This method will be called by the BuildPages method
    */
    virtual wxBitmap& DoLoadBitmap() = 0;

    /**
    *   Method used to set the wizard title
    *   You have to overload this methid in order to set
    *   the private title variable
    */
    virtual wxString DoSetTitle() = 0;

private :
    wxString m_title;
    wxBitmap m_wizardPNG;
    wxString m_xrc;

protected :
    WizardPagesArray m_pages;
    wxWizard* m_wizard;
    RheiaWorkspace *m_workspace;
    RheiaManagedFrame* m_parent;
};

#endif
