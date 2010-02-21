/**
*   @file RheiaAboutDialog.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	17-Nov-2009
*	@version 0.0.1
*/
#include <RheiaAboutDialog.h>
#include <RheiaStandardPaths.h>

#include <wx/button.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>
#include <wx/colordlg.h>
#include <wx/msgdlg.h>
#include <wx/imaglist.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include <wx/sizer.h>

#include "sdkversion.h"

namespace
{
    int nbMain = XRCID("nbMain");
};

RheiaAboutDialog::RheiaAboutDialog( wxWindow* parent )
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgAboutRheia");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:about_dialog.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, xrcDialogName);

    /***************************************************************
    *   DESCRIPTION
    ***************************************************************/
    const wxString version = wxString::Format( wxT("%6.2f") , AutoVersion::UBUNTU_VERSION_STYLE );
    const wxString description = wxT("Welcome to Rheia Framework version :") + version +
        wxT("\n\nRheia is an Application Design Pattern built with the aim\n"
            "to make the development of Commercial Graphical User interfaces\n"
            "faster. \n\n"
            "By developping with Rheia you will be able to develop your application\n"
            "faster in a proper and ergonomic environment.\n\n"
            "Its plugable architecture allows you, to integrate, maintain and evolve\n"
            "easily your application in total transparency for your End-Users.\n"
            "By this way you can add in Rheia any kind of functionality you need\n"
            "and its Standard Development Kit allows you to access to any part of the\n"
            "application you manage to change.\n\n"
            "RHEIA is a registered trademark.\n"
            "Copyrigth to GRAYMAT Research and Management 2009." );

    wxStaticText* txtDescription = XRCCTRL(*this,"txtAboutDescription",wxStaticText);
    txtDescription->SetLabel( description );

    /***************************************************************
    *   INFORMATIONS
    ***************************************************************/
    wxStaticText* txtName = XRCCTRL(*this,"txtAboutName",wxStaticText);
    wxStaticText* txtVersion = XRCCTRL(*this,"txtAboutVersion",wxStaticText);
    wxStaticText* txtAuthor = XRCCTRL(*this,"txtAboutAuthor",wxStaticText);
    wxStaticText* txtEmail = XRCCTRL(*this,"txtAboutEmail",wxStaticText);
    wxStaticText* txtWebsite = XRCCTRL(*this,"txtAboutWebsite",wxStaticText);

    txtName->SetLabel( wxT("Rheia Framework") );
    txtVersion->SetLabel( version );
    txtAuthor->SetLabel( wxT("The Rheia Team") );
    txtEmail->SetLabel( wxT("support@graymat.fr") );
    txtWebsite->SetLabel( wxT("http://www.graymat.fr") );

    /***************************************************************
    *   THANKS TO
    ***************************************************************/
    wxStaticText* txtThanks = XRCCTRL(*this,"txtAboutThanksTo",wxStaticText);
    const wxString thanks = wxT("Developpers :\n\n"
                                "Nicolas Macherey : Developer-Project Leader, GRAYMAT CEO\n"
                                "Gael Plantier : Developer, GRAYMAT Associate\n"
                                "Geoffroy Charollais : GIT subversion systems and forge, GRAYMAT Associate\n"
                                "\n"
                                "Contributors :\n\n"
                                "Cedric Roman : Project orientations and tests (NUMENGO)\n"
                                "Gilles Macherey : Project orientations and tests (CONCEPT TRADING)\n"
                                "\n"
                                "The wxWidgets project (http://www/wxwidgets.org)\n"
                                "wxScintilla (http://sourceforge.net/projects/wxscintilla)\n"
                                "The plplot project (http://plplot.sourceforge.net)\n"
                                "The irrlicht project (http://irrlicht.sourceforge.net)\n"
                                "The Code::Blocks project (http://www.codeblocks.org)\n"
                                "The GNU Software Fundation (http://www.gnu.org)\n"
                                "Last but not least, the open-source community.");

    txtThanks->SetLabel( thanks );

    /***************************************************************
    *   LICENSE
    ***************************************************************/
    wxStaticText* txtLicense = XRCCTRL(*this,"txtAboutLicense",wxStaticText);
    const wxString license = wxT( "This software is licensed under the GRAYMAT own terms\n"
                                "You cannot copy distribute or modify this sofware except\n"
                                "under the terms described in the LICENSE.TXT file subject\n"
                                "to what kind of user you are.\n\n"
                                "GRAYMAT offers 3 type of licenses :\n\n"
                                "\t + Power User  : for single users (Free)\n"
                                "\t + Integrator  : for companies\n"
                                "\t + Contributor : for companies and users who whant to contribute\n" );

    txtLicense->SetLabel( license );


    GetSizer()->SetSizeHints(this);
    CentreOnParent();
}

RheiaAboutDialog::~RheiaAboutDialog()
{

}
