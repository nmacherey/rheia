/**
*   @file RheiaWizardPageBase.h
*
*   This file defines the main object from which any wizard page
*   you want to create shall derive
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 11-May-2009
*   @version 0.0.1
*/

#ifndef RheiaWizardPageBase_h_
#define RheiaWizardPageBase_h_

#include "RheiaWMgtSettings.h"
#include "RheiaGlobals.h"

#include <wx/wizard.h>

/* imports */
class RheiaWorkspace;


/**
*   @class RheiaWizardPageBase
*
*   @brief this is the main abstract class for defining a wizard page
*
*   In rheia you can define RheiaProjectCreationWizard to provide the application
*   with a way to build a proprietary project in a wizard.
*   The wizard object is managed by the main application. To define a new project you
*   have to define it's wizard in order to allow its creation. Any RheiaProjectCreationWizard
*   must return an array of pages all based on the RheiaWizardPageBase object in order to be properly
*   managed by the application.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 11-May-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaWizardPageBase : public wxWizardPageSimple
{
public :

    /**
    *   Basic constructor
    *
    *   Here the page has to be named by the developper. The parent his given by default and is the parent
    *   wizard given to the RheiaProjectCreationWizard.
    *   If you want to use a different bitmap for the given page, you can give it in argument to
    *   this constructor, it will be automatically changed.
    *
    *   @param name Wizard's page's name
    *   @param parent the parent wizard in which the page is created
    *   @param workspace the workspace in which the project will be created if you need it, it will be available
    *   @param bitmap the page bitmap if different from the wizard's one
    */
    RheiaWizardPageBase( const wxString& name, wxWizard* parent, RheiaWorkspace* workspace, const wxBitmap& bitmap = wxNullBitmap );

    /**
    *   Default destructor
    */
    virtual ~RheiaWizardPageBase();

    /**
    *   Get the page name
    */
    wxString GetPageName() const {return m_name;}

    /**
    *   On page change method
    *
    *   This method will be called by the parent wizard when a page has changed
    *   you have to return true or false in order to specify if the content of
    *   the page is correct.
    */
    virtual bool OnPageChanged() = 0;

    /**
    *   On page changing method
    *
    *   This method is called by the parent wizard when a page is going to be
    *   changed. You have to overload this method in order to specify if the event
    *   shall be vetoed or not by the wizard and if the content is ok before changing the page
    *   you may also set some informations about the project that shall be created.
    */
    virtual bool OnPageChanging() = 0;

protected :

    wxString m_name;
    RheiaWorkspace* m_workspace;
};

#endif
