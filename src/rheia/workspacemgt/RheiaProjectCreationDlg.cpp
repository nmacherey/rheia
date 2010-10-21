/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaProjectCreationDlg.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 25-April-2009
*   @version 0.0.1
*/

#include <RheiaProjectCreationDlg.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProject.h>
#include <RheiaWorkspace.h>
#include <RheiaWizardManager.h>

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
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/textdlg.h>
#include <wx/choicdlg.h>
#include <wx/filedlg.h>
#include <wx/dir.h>
#include <wx/choice.h>

int cbProject = XRCID("cbProject");

BEGIN_EVENT_TABLE( RheiaProjectCreationDlg , wxDialog )
    EVT_UPDATE_UI(-1, RheiaProjectCreationDlg::OnUpdateUI)
    EVT_RADIOBOX(XRCID("rbListView"), RheiaProjectCreationDlg::OnViewChange)

    EVT_LIST_ITEM_ACTIVATED( wxID_ANY , RheiaProjectCreationDlg::OnWizardActivated )
    EVT_CHOICE( cbProject , RheiaProjectCreationDlg::OnChangeCategory )
END_EVENT_TABLE()

RheiaProjectCreationDlg::RheiaProjectCreationDlg(wxWindow* parent)
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgProjectCreation");

    wxXmlResource *myres = wxXmlResource::Get();

    myres->LoadDialog(this, parent, _T("dlgProjectCreation"));

    m_lstImages = new wxImageList( 48 , 48 );
    wxListCtrl* lst = XRCCTRL( *this , "lstWizards" , wxListCtrl );
    lst->AssignImageList( m_lstImages , wxIMAGE_LIST_NORMAL );

    BuildList();
    XRCCTRL(*this, "rbListView", wxRadioBox)->SetSelection(RheiaManager::Get()->GetConfigurationManager(_T("new_project"))->ReadInt(_T("/view"), 0));
    ChangeView();

    GetSizer()->SetSizeHints(this);
    CentreOnParent();
}

RheiaProjectCreationDlg::~RheiaProjectCreationDlg()
{
}

void RheiaProjectCreationDlg::OnChangeCategory(wxCommandEvent& WXUNUSED(event))
{
    wxChoice* m_cbCat = XRCCTRL(*this,"cbProject",wxChoice);
    BuildListFor(m_cbCat->GetStringSelection());
}

void RheiaProjectCreationDlg::BuildList()
{
    wxArrayString categories = RheiaWizardManager::GetCategoryList();
    wxChoice* m_cbCat = XRCCTRL(*this,"cbProject",wxChoice);

    m_cbCat->Clear();
    m_cbCat->Append(categories);
    if( categories.GetCount()> 0 )
    {
        m_cbCat->SetSelection(0);
        wxString cat = categories[0];
        BuildListFor(cat);
    }
}

void RheiaProjectCreationDlg::BuildListFor( const wxString& category )
{
    wxListCtrl* lst = XRCCTRL( *this , "lstWizards" , wxListCtrl );
    lst->ClearAll();
    m_lstImages->RemoveAll();
    int sel = XRCCTRL(*this, "rbListView", wxRadioBox)->GetSelection();
    int style = sel == 0 ? wxLC_ICON : wxLC_LIST;
    lst->SetSingleStyle( style );

    wxArrayString wizards = RheiaWizardManager::GetWizardListFor( category );

    for( unsigned int i = 0; i < wizards.GetCount() ; ++i )
    {
        RheiaProjectWizardRegistration reg = RheiaWizardManager::FindProjectWizardByName(wizards[i]);
        wxString path = RheiaFileFinder::FindFile( reg.resName );
        wxString bmpbase = path + wxT("#zip:") + reg.bitmapBasename + wxT("_48.png");
        
        wxBitmap bmp = RheiaLoadBitmap( bmpbase );

        int lidx = m_lstImages->Add( bmp );
        long item = lst->InsertItem(i,reg.name,lidx);

        if( i == 0 )
            lst->SetItemState(item,wxLIST_STATE_SELECTED ,wxLIST_STATE_SELECTED );
    }

}

void RheiaProjectCreationDlg::OnUpdateUI(wxUpdateUIEvent& WXUNUSED(event))
{
    wxListCtrl* lst = XRCCTRL( *this , "lstWizards" , wxListCtrl );
    int sel = lst->GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	XRCCTRL(*this, "wxID_OK", wxButton)->Enable(sel != -1);
}

void RheiaProjectCreationDlg::ChangeView()
{
    int sel = XRCCTRL(*this, "rbListView", wxRadioBox)->GetSelection();
    int style = sel == 0 ? wxLC_ICON : wxLC_LIST;
    wxListCtrl* lst = XRCCTRL( *this , "lstWizards" , wxListCtrl );
    lst->SetSingleStyle(style);
}

void RheiaProjectCreationDlg::OnViewChange(wxCommandEvent& WXUNUSED(event))
{
    ChangeView();
}

void RheiaProjectCreationDlg::EndModal(int retCode)
{
    if( retCode == wxID_OK )
    {
        // save view prefs
        int sel = XRCCTRL(*this, "rbListView", wxRadioBox)->GetSelection();
        RheiaManager::Get()->GetConfigurationManager(_T("new_project"))->Write(_T("/view"), (int)sel);

        wxListCtrl* lst = XRCCTRL( *this , "lstWizards" , wxListCtrl );

        sel = lst->GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
        if( sel == -1 )
            return;

        m_selwizard = lst->GetItemText(sel);

        wxCheckBox* chkWksp = XRCCTRL(*this,"chkWorkspace",wxCheckBox);
        m_newwksp = chkWksp->IsChecked();
    }

    wxDialog::EndModal(retCode);
}

void RheiaProjectCreationDlg::OnWizardActivated( wxListEvent& WXUNUSED(event) )
{
    EndModal( wxID_OK );
}
