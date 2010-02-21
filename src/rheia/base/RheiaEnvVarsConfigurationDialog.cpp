
/**
*	@file RheiaEnvVarsConfigurationDialog.cpp
*
*   Dialog for environement variables configuration
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#include <RheiaEnvVarsConfigurationDialog.h>
#include <RheiaEnvVarsSelectionDialog.h>
#include <RheiaEnvironementManager.h>

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
#include <wx/dirdlg.h>
#include <wx/imaglist.h>
#include <wx/settings.h>
#include <wx/stattext.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>

namespace{

    int wxCALLBACK sortByTitle(long item1, long item2, long sortData)
    {
        const wxString *elem1 = (const wxString*)item1;
        const wxString *elem2 = (const wxString*)item2;

        return elem1->CompareTo(*elem2);
    }

    int btnEVCreate = XRCID("btnEVCreate");
    int btnEVDelete = XRCID("btnEVDelete");
    int btnEVEdit = XRCID("btnEVEdit");
    int btnEPCreate = XRCID("btnEPCreate");
    int btnEPDelete = XRCID("btnEPDelete");
};

BEGIN_EVENT_TABLE(RheiaEnvVarsConfigurationDialog,wxDialog)
    EVT_BUTTON(btnEVCreate , RheiaEnvVarsConfigurationDialog::OnAddNewVariable )
    EVT_BUTTON(btnEVDelete , RheiaEnvVarsConfigurationDialog::OnDeleteVariable )
    EVT_BUTTON(btnEVEdit , RheiaEnvVarsConfigurationDialog::OnEditVariable )

    EVT_BUTTON(btnEPCreate , RheiaEnvVarsConfigurationDialog::OnAddNewPath )
    EVT_BUTTON(btnEPDelete , RheiaEnvVarsConfigurationDialog::OnDeletePath )
END_EVENT_TABLE()

RheiaEnvVarsConfigurationDialog::RheiaEnvVarsConfigurationDialog(wxWindow* parent):wxDialog()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgEnvVarsSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:envars_conf_dialog.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, xrcDialogName);

    DoUpdateList();
    DoUpdatePathList();
}

void RheiaEnvVarsConfigurationDialog::DoUpdateList()
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailableVars", wxListCtrl);
    const RheiaStringStringMap& m_envars = RheiaEnvironementManager::Get()->GetVariables();
    RheiaStringStringMap::const_iterator it = m_envars.begin();

    list->ClearAll();

    if (list->GetColumnCount() == 0)
    {
        list->InsertColumn(0, _T("Name"));
        list->InsertColumn(1, _T("Value"));
    }

    for( int i = 0 ; it != m_envars.end() ; ++it, ++i )
    {
        long idx = list->InsertItem(i, it->first);
        list->SetItem(idx, 1, it->second);
        list->SetItemData(idx, (long)(&(it->first)));
    }

    list->SetColumnWidth(0, wxLIST_AUTOSIZE);
    list->SetColumnWidth(1, wxLIST_AUTOSIZE );

    list->SortItems(sortByTitle, 0);
}

void RheiaEnvVarsConfigurationDialog::DoUpdatePathList()
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailablePaths", wxListCtrl);
    wxArrayString& m_envars = RheiaEnvironementManager::Get()->GetPathsList();

    list->ClearAll();

    if (list->GetColumnCount() == 0)
    {
        list->InsertColumn(0, _T("Value"));
    }

    for( unsigned int i = 0 ; i < m_envars.GetCount() ; ++i )
    {
        long idx = list->InsertItem(i, m_envars[i]);
        list->SetItemData(idx, (long)(&(m_envars[i])));
    }

    list->SetColumnWidth(0, wxLIST_AUTOSIZE);
    list->SortItems(sortByTitle, 0);
}

void RheiaEnvVarsConfigurationDialog::OnUpdateUI(wxUpdateUIEvent& event)
{

}

void RheiaEnvVarsConfigurationDialog::EndModal(int retCode)
{
    wxDialog::EndModal( retCode );
}

void RheiaEnvVarsConfigurationDialog::OnAddNewVariable( wxCommandEvent& event )
{
    RheiaEnvVarsSelectionDialog dialog( this );

    if( dialog.ShowModal() == wxID_CANCEL )
        return;

    RheiaEnvironementManager::Get()->Add( dialog.GetKey() , dialog.GetValue() );
    DoUpdateList();
}

void RheiaEnvVarsConfigurationDialog::OnAddNewPath( wxCommandEvent& event )
{
    wxDirDialog dialog( this , wxT("Choose a directory") );

    if( dialog.ShowModal() == wxID_CANCEL )
        return;

    RheiaEnvironementManager::Get()->AddPath( dialog.GetPath() );
    DoUpdatePathList();
}

void RheiaEnvVarsConfigurationDialog::OnDeleteVariable( wxCommandEvent& event )
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailableVars", wxListCtrl);

    long sel = -1;

    while (true)
    {
        sel = list->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (sel == -1)
            break;

        const wxString* elem = (const wxString*)list->GetItemData(sel);
        RheiaEnvironementManager::Get()->Remove( *elem );
    }
    DoUpdateList();
}

void RheiaEnvVarsConfigurationDialog::OnDeletePath( wxCommandEvent& event )
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailablePaths", wxListCtrl);

    long sel = -1;

    while (true)
    {
        sel = list->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (sel == -1)
            break;

        const wxString* elem = (const wxString*)list->GetItemData(sel);
        RheiaEnvironementManager::Get()->RemovePath( *elem );
    }
    DoUpdatePathList();
}

void RheiaEnvVarsConfigurationDialog::OnEditVariable( wxCommandEvent& event )
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailableVars", wxListCtrl);

    long sel = -1;

    sel = list->GetNextItem(sel, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (sel == -1)
        return;

    const wxString* elem = (const wxString*)list->GetItemData(sel);
    wxString value = RheiaEnvironementManager::Get()->FindVariableByName( *elem );

    RheiaEnvVarsSelectionDialog dialog( this );

    dialog.SetKey( *elem );
    dialog.SetValue( value );

    if( dialog.ShowModal() == wxID_CANCEL )
        return;

    RheiaEnvironementManager::Get()->Change( dialog.GetKey() , dialog.GetValue() );
    DoUpdateList();
}
