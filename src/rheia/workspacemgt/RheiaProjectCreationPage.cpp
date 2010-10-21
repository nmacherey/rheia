/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaProjectCreationPage.cpp
*
*   @brief This is the main page for creating a new project from a specific category
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 03-May-2009
*   @version 0.0.1
*/

#include <RheiaProjectCreationPage.h>
#include <RheiaEnvironmentPlugin.h>
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
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/textdlg.h>
#include <wx/choicdlg.h>
#include <wx/filedlg.h>
#include <wx/choice.h>

struct ListItemData
{
	ListItemData( int i = 0 ) : Index(i) {}
	ListItemData(const ListItemData& rhs) : Index(rhs.Index) {}
	int Index;
};

BEGIN_EVENT_TABLE(RheiaProjectCreationPage, wxPanel)
    EVT_CHOICE(XRCID("cmbProjectCategories"), RheiaProjectCreationPage::OnCategoryChanged)
END_EVENT_TABLE()

RheiaProjectCreationPage::RheiaProjectCreationPage( wxWindow* parent , RheiaEnvironmentPlugin* plugin )
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("pnlProjects");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:project_creation_page.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, _T("pnlProjects"));

    XRCCTRL(*this, "listProjects", wxListCtrl)->SetImageList(new wxImageList(48, 48), wxIMAGE_LIST_NORMAL);
    XRCCTRL(*this, "listProjects", wxListCtrl)->SetImageList(new wxImageList(48, 48), wxIMAGE_LIST_SMALL);

    m_plugin = plugin;

    BuildCategories();
    BuildList();

    GetSizer()->SetSizeHints(this);
}

RheiaProjectCreationPage::~RheiaProjectCreationPage( )
{

}

void RheiaProjectCreationPage::BuildCategories()
{
    wxChoice *m_cbCategories = XRCCTRL( *this , "cmbProjectCategories" , wxChoice );
    m_cbCategories->Clear();

    m_cbCategories->Append( wxT("< All categories >") );

    /* Get the category list from the environement plugin */
    wxArrayString m_categoryList = m_plugin->GetCategoryList();
    m_cbCategories->Append( m_categoryList );

    m_cbCategories->SetSelection(0);
}

void RheiaProjectCreationPage::ClearList()
{
    wxListCtrl* list = XRCCTRL(*this, "listProjects", wxListCtrl);

    if (!list)
        return;

	for (int i = 0; i < list->GetItemCount(); ++i)
	{
		ListItemData* data = (ListItemData*)list->GetItemData(i);
		delete data;
	}

	list->ClearAll();
}

void RheiaProjectCreationPage::BuildList()
{
    wxChoice *cat = XRCCTRL( *this , "cmbProjectCategories" , wxChoice );
    wxListCtrl* list = XRCCTRL(*this, "listProjects", wxListCtrl);

    list->GetImageList(wxIMAGE_LIST_NORMAL)->RemoveAll();
    list->GetImageList(wxIMAGE_LIST_SMALL)->RemoveAll();

    wxBitmap bmp;
    bool all = cat->GetSelection() == 0;

    for (int w = 0; w < m_plugin->GetProjectsCount(); ++w)
    {
        if (all || m_plugin->GetProjectCategory(w).Matches(cat->GetStringSelection()))
        {
            int idx = m_plugin->GetProjectBitmap(w).Ok() ? list->GetImageList(wxIMAGE_LIST_NORMAL)->Add(m_plugin->GetProjectBitmap(w)) : -2;

            if (m_plugin->GetProjectBitmap(w).Ok())
                list->GetImageList(wxIMAGE_LIST_SMALL)->Add(m_plugin->GetProjectBitmap(w));

            int index = list->InsertItem(0, m_plugin->GetProjectTitle(w), idx);

            if (index != -1)
            {
                list->SetItemData(index, (long)(new ListItemData(w)));
            }
        }
    }
}

wxListCtrl* RheiaProjectCreationPage::GetList()
{
    return XRCCTRL(*this, "listProjects", wxListCtrl);
}

wxChoice* RheiaProjectCreationPage::GetCategorySelection()
{
    return XRCCTRL( *this , "cmbProjectCategories" , wxChoice );
}

int RheiaProjectCreationPage::GetSelectedProjectIndex()
{
    wxListCtrl* list = XRCCTRL(*this, "listProjects", wxListCtrl);
    if (!list)
        return -1;

    long index = list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (index == -1)
        return -1;

    ListItemData* data = (ListItemData*)list->GetItemData(index);
    return data->Index;
}

void RheiaProjectCreationPage::OnCategoryChanged(wxCommandEvent& WXUNUSED(event))
{
    ClearList();
    BuildList();
}
