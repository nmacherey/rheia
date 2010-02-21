/**
*   @file RheiaApplicationConfigurationDialog.cpp
*
*   Revision : Nicolas Macherey (nm@graymat.fr) the 17 November 2009
*   Changes : Commentaries and management of configuration tools via
*       the RheiaConfigurationToolsManager
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.2
*   @date 24-September-2009
*/
#include <RheiaApplicationConfigurationDialog.h>

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

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaConfigurationToolsManager.h>
#include <RheiaConfigurationPanel.h>

namespace
{
    int nbMain = XRCID("nbMain");
}

BEGIN_EVENT_TABLE(RheiaApplicationConfigurationDialog,wxDialog)
    EVT_LISTBOOK_PAGE_CHANGING(nbMain, RheiaApplicationConfigurationDialog::OnPageChanging)
    EVT_LISTBOOK_PAGE_CHANGED(nbMain, RheiaApplicationConfigurationDialog::OnPageChanged)
END_EVENT_TABLE()

RheiaApplicationConfigurationDialog::RheiaApplicationConfigurationDialog(wxWindow* parent)
{
    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();

    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgEnvironmentSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:environement_dialog.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, _T("dlgEnvironmentSettings"));

    int siz = cfg->ReadInt(_T("/environment/application_dialog/settings_size"), 80);

    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    m_lbImages = new wxImageList( siz , siz );
    lb->AssignImageList( m_lbImages );

    DoLoadConfigurationTools();
    // make sure everything is laid out properly
    GetSizer()->SetSizeHints(this);
    CentreOnParent();
}

RheiaApplicationConfigurationDialog::~RheiaApplicationConfigurationDialog()
{
}

void RheiaApplicationConfigurationDialog::SetPageSelection( const wxString& page_name )
{
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    int idx = FindPageIndexByName( page_name );

    if( idx == wxNOT_FOUND )
        return;

    lb->SetSelection(idx);
}

#if wxCHECK_VERSION(2, 9, 0)
void RheiaApplicationConfigurationDialog::OnPageChanging(wxBookCtrlEvent& event)
#else
void RheiaApplicationConfigurationDialog::OnPageChanging(wxListbookEvent& event)
#endif
{

}

#if wxCHECK_VERSION(2, 9, 0)
void RheiaApplicationConfigurationDialog::OnPageChanged(wxBookCtrlEvent& event)
#else
void RheiaApplicationConfigurationDialog::OnPageChanged(wxListbookEvent& event)
#endif
{
    UpdateListbookImages();
}

void RheiaApplicationConfigurationDialog::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        RheiaConfigurationPageInfoMap::iterator pit = m_pages.begin();

        for( ; pit != m_pages.end() ; ++pit )
            if( !pit->second.page->OnApply() )
                return;
    }
    else if (retCode == wxID_CANCEL)
    {
        RheiaConfigurationPageInfoMap::iterator pit = m_pages.begin();

        for( ; pit != m_pages.end() ; ++pit )
            pit->second.page->OnCancel();
    }

    wxDialog::EndModal(retCode);
}

void RheiaApplicationConfigurationDialog::DoLoadConfigurationTools()
{
    const wxString base = RheiaStandardPaths::DataDirectory() + _T("/images/settings/");
    wxArrayString cfgTools = RheiaConfigurationToolsManager::Get()->GetListFor(cgApp);
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);

    for( unsigned int i = 0; i < cfgTools.GetCount() ; ++i )
    {
        RheiaConfigurationPanel* page =
            RheiaConfigurationToolsManager::Get()->CreateTool( cfgTools[i] , lb );

        if( page != NULL )
        {
            wxString title = page->GetTitle();
            if( !AddPage( title , page ) )
                page->Destroy();
        }
    }
    UpdateListbookImages();
}

void RheiaApplicationConfigurationDialog::UpdateListbookImages()
{
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    int sel = lb->GetSelection();

    if( sel == -1 )
        return;

    wxString selection = lb->GetPageText(sel);
    RheiaConfigurationPageInfoMap::iterator pit = m_pages.begin();

    for( ; pit != m_pages.end() ; ++pit  )
    {
        int idx = FindPageIndexByName( pit->first );
        if( pit->second.title.IsSameAs( selection ) )
            lb->SetPageImage( idx , pit->second.idxOn );
        else
            lb->SetPageImage( idx , pit->second.idxOff );
    }

    XRCCTRL(*this, "lblBigTitle", wxStaticText)->SetLabel(selection);
}

bool RheiaApplicationConfigurationDialog::AddPage( wxString name, RheiaConfigurationPanel* page )
{
    RheiaConfigurationPageInfoMap::iterator pit = m_pages.find(name);
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);

    if( pit != m_pages.end() )
        return false;

    RheiaConfigurationPageInfo info;
    info.page = page;
    info.title = name;

    wxString bmpBase = page->GetBitmapBaseName();
    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();
    int siz = cfg->ReadInt(_T("/environment/application_dialog/settings_size"), 80);

    wxString path;
    path = bmpBase;
    wxBitmap bmpOn = RheiaLoadBitmap( path + wxString::Format( wxT("_%d.png") , siz ) );
    wxBitmap bmpOff = RheiaLoadBitmap( path + wxString::Format( wxT("_%d-off.png") , siz ) );

    int idxOn = m_lbImages->Add( bmpOn );
    int idxOff  = m_lbImages->Add( bmpOff );

    info.idxOn = idxOn;
    info.idxOff = idxOff;

    m_pages[name] = info;
    bool show = ( lb->GetPageCount() == 0 );

    lb->AddPage( page , name , show , idxOn );
    return true;
}

bool RheiaApplicationConfigurationDialog::DeletePage( const wxString& name )
{
    RheiaConfigurationPageInfoMap::iterator pit = m_pages.find(name);

    if( pit == m_pages.end() )
        return false;

    int idx = FindPageIndexByName( name );
    if( idx == wxNOT_FOUND )
        return false;

    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);

    lb->DeletePage( idx );
    m_pages.erase( pit );
    return true;
}

bool RheiaApplicationConfigurationDialog::ActivatePage( wxString name )
{
    int idx = FindPageIndexByName( name );
    if( idx == wxNOT_FOUND )
        return false;

    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);

    lb->SetSelection( idx );
    return true;
}

RheiaConfigurationPanel* RheiaApplicationConfigurationDialog::FindPageByName( const wxString& name )
{
    RheiaConfigurationPageInfoMap::iterator pit = m_pages.find(name);

    if( pit == m_pages.end() )
        return NULL;

    return pit->second.page;
}

RheiaConfigurationPageInfo* RheiaApplicationConfigurationDialog::FindPageInfoByName( const wxString& name )
{
    RheiaConfigurationPageInfoMap::iterator pit = m_pages.find(name);

    if( pit == m_pages.end() )
        return NULL;

    return &(pit->second);
}

int RheiaApplicationConfigurationDialog::FindPageIndexByName( const wxString& name )
{
    RheiaConfigurationPageInfoMap::iterator it = m_pages.find( name );

    if( it == m_pages.end() )
        return wxNOT_FOUND;

    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);

    for( unsigned int i = 0; i < lb->GetPageCount() ; ++i )
    {
        wxString title = lb->GetPageText(i);
        if( title.IsSameAs(name) )
            return i;
    }

    return wxNOT_FOUND;
}

wxString RheiaApplicationConfigurationDialog::FindPageNameByObject( RheiaConfigurationPanel* page )
{
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    RheiaConfigurationPageInfoMap::iterator pit = m_pages.begin();

    for( ; pit != m_pages.end() ; ++pit  )
    {
        if( pit->second.page == page )
            return pit->first;
    }

    return wxEmptyString;
}

int RheiaApplicationConfigurationDialog::FindPageIndexByObject( RheiaConfigurationPanel* page )
{
    wxString name = FindPageNameByObject( page );
    if( name.IsEmpty() )
        return wxNOT_FOUND;

    return FindPageIndexByName( name );
}

