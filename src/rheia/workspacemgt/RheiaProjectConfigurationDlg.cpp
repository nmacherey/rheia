/**
*			@file RheiaProjectConfigurationDlg.cpp
*
*			@brief This file is used for loading the plugins configuration dialog in Rheia
*
*
*			This file is the property of Nicolas Macherey and cannot be used directly or indirectly by
*			any person without the written consent of the author.
*
*			@author Nicolas Macherey (nm@graymat.fr)
*			@date 03-Fev-2009
*			@version 0.0.1
*/
#include <RheiaProjectConfigurationDlg.h>

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
#include <wx/settings.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <wx/progdlg.h>
#include <wx/html/htmlwin.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaPluginManager.h>
#include <RheiaPlugin.h>
#include <RheiaProject.h>
#include <RheiaPlatform.h>
#include <RheiaProfileManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaInfoWindow.h>
#include <RheiaConfigurationPanel.h>

int btnProjectPath = XRCID("btnProjectPath");

BEGIN_EVENT_TABLE(RheiaProjectConfigurationDlg,wxDialog)

END_EVENT_TABLE()
// images by order of pages

RheiaProjectConfigurationDlg::RheiaProjectConfigurationDlg(wxWindow* parent,RheiaProject* project)
{
    m_project = project;

    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgProjectConfiguration");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:project_configuration_dlg.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, xrcDialogName);

    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    m_imageList = new wxImageList( 48 , 48 );
    lb->AssignImageList( m_imageList );

    int prjIdx = m_imageList->Add( m_project->GetBitmap( 48 ) );
    lb->SetPageImage( 0 , prjIdx );

    wxTextCtrl* m_txtprojectName = XRCCTRL( *this , "txtProjectName" , wxTextCtrl );
    m_txtprojectName->SetValue( m_project->GetName() );

    wxTextCtrl* m_txtprojectPath = XRCCTRL( *this , "txtProjectPath" , wxTextCtrl );
    m_txtprojectPath->SetValue( m_project->GetFileName() );

    DoBuildElementPages();

    GetSizer()->SetSizeHints(this);
    CentreOnParent();
}

void RheiaProjectConfigurationDlg::DoBuildElementPages()
{
//    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
//    RheiaProjectElementTable m_elems = m_project->GetProjectElementTable();
//    RheiaProjectElementTable::iterator it = m_elems.begin();
//
//    lb->Freeze();
//
//    for( ; it != m_elems.end() ; it++ )
//    {
//        RheiaConfigurationPanel* panel = it->second->BuildPage( lb );
//
//        if( panel != NULL )
//        {
//            m_pages[it->first] = panel;
//            wxBitmap bmp = it->second->GetBitmap(48);
//            int idx = m_imageList->Add( bmp );
//            lb->AddPage( panel , it->first , false , idx );
//        }
//    }
//
//    lb->Thaw();
}

RheiaProjectConfigurationDlg::~RheiaProjectConfigurationDlg()
{

}

void RheiaProjectConfigurationDlg::SetPageSelection( const wxString& page_name )
{
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);

    unsigned int Count = lb->GetPageCount();
    for ( unsigned int i = 0; i < Count ; i++ )
    {
        wxString pageText = lb->GetPageText( i );
        if ( pageText.IsSameAs( page_name ) )
        {
            lb->SetSelection( i );
            return;
        }
    }
}

#if wxCHECK_VERSION(2, 9, 0)
void RheiaProjectConfigurationDlg::OnPageChanging(wxBookCtrlEvent& WXUNUSED(event))
{
}
#else
void RheiaProjectConfigurationDlg::OnPageChanging(wxListbookEvent& WXUNUSED(event))
{
}
#endif

#if wxCHECK_VERSION(2, 9, 0)
void RheiaProjectConfigurationDlg::OnPageChanged(wxBookCtrlEvent& WXUNUSED(event))
{
}
#else
void RheiaProjectConfigurationDlg::OnPageChanged(wxListbookEvent& WXUNUSED(event))
{
}
#endif

void RheiaProjectConfigurationDlg::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
//        RheiaProjectElementConfigurationPanelMap::iterator it = m_pages.begin();
//
//        for( ; it != m_pages.end() ; it++ )
//            it->second->OnApply();
    }

    wxDialog::EndModal(retCode);
}


void RheiaProjectConfigurationDlg::LoadListbookImages()
{

}
