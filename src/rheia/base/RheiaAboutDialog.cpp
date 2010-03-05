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
        wxT("\n\nRheia is an Application Design Pattern built with the aim\n") +
        wxT("to make the development of Commercial Graphical User interfaces\n") +
        wxT("faster. \n\n")+
        wxT("By developping with Rheia you will be able to develop your application\n")+
        wxT("faster in a proper and ergonomic environment.\n\n")+
        wxT("Its plugable architecture allows you, to integrate, maintain and evolve\n")+
        wxT("easily your application in total transparency for your End-Users.\n")+
        wxT("By this way you can add in Rheia any kind of functionality you need\n")+
        wxT("and its Standard Development Kit allows you to access to any part of the\n")+
        wxT("application you manage to change.\n\n")+
        wxT("RHEIA is a registered trademark.\n")+
        wxT("Copyrigth to GRAYMAT Research and Management 2009.");

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
    wxString devs = wxT("Developpers :\n\n" );
    const wxString thanks = devs +
                            wxT("Nicolas Macherey : Developer-Project Leader, GRAYMAT CEO\n" ) +
                            wxT("Gael Plantier : Developer, GRAYMAT Associate\n" ) +
                            wxT("Geoffroy Charollais : GIT subversion systems and forge, GRAYMAT Associate\n" ) +
                            wxT("\n" ) +
                            wxT("Contributors :\n\n" ) +
                            wxT("Cedric Roman : Project orientations and tests (NUMENGO)\n" ) +
                            wxT("Gilles Macherey : Project orientations and tests (CONCEPT TRADING)\n" ) +
                            wxT("\n" ) +
                            wxT("The wxWidgets project (http://www/wxwidgets.org)\n" ) +
                            wxT("wxScintilla (http://sourceforge.net/projects/wxscintilla)\n" ) +
                            wxT("The plplot project (http://plplot.sourceforge.net)\n" ) +
                            wxT("The irrlicht project (http://irrlicht.sourceforge.net)\n" ) +
                            wxT("The Code::Blocks project (http://www.codeblocks.org)\n" ) +
                            wxT("The GNU Software Fundation (http://www.gnu.org)\n" ) +
                            wxT("Last but not least, the open-source community.");

    txtThanks->SetLabel( thanks );

    /***************************************************************
    *   LICENSE
    ***************************************************************/
    wxStaticText* txtLicense = XRCCTRL(*this,"txtAboutLicense",wxStaticText);
    wxString first = wxT( "This software is licensed under the GRAYMAT own terms\n" );
    const wxString license = first +
                             wxT("You cannot copy distribute or modify this sofware except\n" ) +
                             wxT("under the terms described in the LICENSE.TXT file subject\n" ) +
                             wxT("to what kind of user you are.\n\n" ) +
                             wxT("GRAYMAT offers 3 type of licenses :\n\n" ) +
                             wxT("\t + Power User  : for single users (Free)\n" ) +
                             wxT("\t + Integrator  : for companies\n" ) +
                             wxT("\t + Contributor : for companies and users who whant to contribute\n" );

    txtLicense->SetLabel( license );


    GetSizer()->SetSizeHints(this);
    CentreOnParent();
}

RheiaAboutDialog::~RheiaAboutDialog()
{

}
