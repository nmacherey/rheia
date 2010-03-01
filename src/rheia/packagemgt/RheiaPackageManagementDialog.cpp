/**
*   @file RheiaPackageManagementDialog.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	17-Nov-2009
*	@version 0.0.1
*/
#include <RheiaPackageManagementDialog.h>
#include <RheiaManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaPackageManager.h>
#include <RheiaPackageMaintainer.h>
#include <RheiaPackageManagedFile.h>
#include <RheiaPackageManagedFiles.h>
#include <RheiaPackageVersion.h>
#include <RheiaPackageInfo.h>
#include <RheiaPackageDependency.h>
#include <RheiaPackageDependencies.h>
#include <RheiaPackageDescription.h>
#include <RheiaPackageDBManager.h>
#include <RheiaPackageControl.h>
#include <RheiaPluginManager.h>
#include <RheiaEventsManager.h>
#include <RheiaPluginManifest.h>
#include <RheiaConfigurationManager.h>
#include <RheiaAppGlobals.h>

#include <treelistctrl.h>

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
#include <wx/filedlg.h>

namespace
{
    int nbMain = XRCID("nbMain");
    int btnInstall = XRCID("bntInstallPackage");
    int btnRemove = XRCID("bntRemovePackage");
    int lstPackages = wxNewId();
    int lstPlugins = wxNewId();
    int lstLibs = wxNewId();
};

BEGIN_EVENT_TABLE( RheiaPackageManagementDialog , wxDialog )
    EVT_TREE_SEL_CHANGED( lstPackages , RheiaPackageManagementDialog::OnPackageListSelection )
    EVT_TREE_ITEM_ACTIVATED( lstPackages , RheiaPackageManagementDialog::OnPackageListSelection )

    EVT_BUTTON( btnInstall , RheiaPackageManagementDialog::OnInstallPackage )
    EVT_BUTTON( btnRemove , RheiaPackageManagementDialog::OnRemovePackage )
END_EVENT_TABLE()

RheiaPackageManagementDialog::RheiaPackageManagementDialog( wxWindow* parent )
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgPackageManagement");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:package_management_dialog.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, xrcDialogName);


    DoBuildPackagesPage();
    DoBuildPluginsPage();
    DoBuilLibsPage();

    RegiserEvents();
    
    SetSize(800,600);
    //GetSizer()->SetSizeHints(this);
    CentreOnParent();
}

RheiaPackageManagementDialog::~RheiaPackageManagementDialog()
{
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RemoveAllEventMethodsFor( this );
}

void RheiaPackageManagementDialog::DoBuildPackagesPage()
{
    wxPanel* pnl = XRCCTRL(*this,"pnlPackagesList",wxPanel);
    pnl->SetMinSize( wxSize(700,400) );
    wxSizer* sizer = pnl->GetSizer();

    m_treelist = new wxTreeListCtrl(pnl,lstPackages,wxDefaultPosition,wxSize(400,400),wxTR_HAS_BUTTONS|wxTR_SINGLE|wxTR_HIDE_ROOT|wxTR_NO_LINES|wxBORDER_THEME);

    m_treelist->AddColumn( wxT("Packages"),200,wxALIGN_LEFT);
    m_treelist->AddColumn( wxT("Version"),200,wxALIGN_LEFT);
    m_treelist->AddColumn( wxT("Description"),400,wxALIGN_LEFT);

    m_root = m_treelist->AddRoot (_T("Root"));

    wxArrayString pkgNames = RheiaPackageDBManager::Get()->GetPackageList();

    for( unsigned int i = 0; i < pkgNames.GetCount() ; ++i )
    {
        int n = 0;
        RheiaPackageInfo* info = RheiaPackageDBManager::Get()->FindPackageByName(pkgNames[i]);
        RheiaPackageTreeItemData* data = new RheiaPackageTreeItemData( info );

        wxTreeItemId parent = m_treelist->AppendItem(m_root, info->GetControl()->GetTitle(),-1,-1,data);
        m_packageIds[info->GetControl()->GetName()] = parent;

        m_treelist->SetItemText(parent,1,wxString::Format(wxT("%d.%d.%d"),info->GetControl()->GetVersion()->GetMajor(),
                                                        info->GetControl()->GetVersion()->GetMinor() ,
                                                        info->GetControl()->GetVersion()->GetBuild()));

        m_treelist->SetItemText(parent,2,info->GetControl()->GetDescription()->GetShort());

        RheiaPackageManagedFiles* files = info->GetManagedFiles();
        RheiaPackageManagedFileMap filesm = files->GetManagedFiles();
        RheiaPackageManagedFileMap::iterator fit = filesm.begin();

        wxTreeItemId plugins;
        wxTreeItemId libs;
        wxTreeItemId fils;

        for( ; fit != filesm.end() ; ++fit )
        {
            RheiaPackageManagedFile* file = fit->second;

            if( file->GetType().IsSameAs(wxT("plugin")) )
            {
                if( !plugins.IsOk() )
                    plugins = m_treelist->AppendItem( parent, wxT("Plugins") );

                wxString name = file->GetName();
                RheiaPluginRegistration* reg = RheiaPluginManager::Get()->FindElement(name);

                if( reg != NULL )
                {
                    RheiaPackageTreeItemData* datab = new RheiaPackageTreeItemData( info );
                    wxTreeItemId item = m_treelist->AppendItem (plugins, name,-1,-1,datab);

                    m_treelist->SetItemText(item,1,wxString::Format(wxT("%d.%d.%d"),reg->info->GetVersion()->GetMajor(),
                                                        reg->info->GetVersion()->GetMinor() ,
                                                        reg->info->GetVersion()->GetBuild()));

                    m_treelist->SetItemText(item,2,reg->info->GetTitle());
                }
            }
            else if( file->GetType().IsSameAs(wxT("lib")) )
            {
                if( !libs.IsOk() )
                    libs = m_treelist->AppendItem( parent, wxT("Libraries") );

                wxString name = file->GetName();
                RheiaPackageTreeItemData* datab = new RheiaPackageTreeItemData( info );
                wxTreeItemId item = m_treelist->AppendItem (libs, name,-1,-1,datab);

                m_treelist->SetItemText(item,2,file->GetPath());
            }
            else if( file->GetType().IsSameAs(wxT("file")) )
            {
                if( !fils.IsOk() )
                    fils = m_treelist->AppendItem( parent, wxT("Files") );

                wxString name = file->GetName();
                RheiaPackageTreeItemData* datab = new RheiaPackageTreeItemData( info );
                wxTreeItemId item = m_treelist->AppendItem (fils, name,-1,-1,datab);

                m_treelist->SetItemText(item,2,file->GetPath());
            }
        }
    }

    sizer->Add( m_treelist , 1 , wxALL | wxEXPAND );
}

void RheiaPackageManagementDialog::DoUpdatePackageTree()
{
    wxArrayString pkgNames = RheiaPackageDBManager::Get()->GetPackageList();

    // first add missing packages in the list
    for( unsigned int i = 0; i < pkgNames.GetCount() ; ++i )
    {
        TreeItemIdMap::iterator tit = m_packageIds.find( pkgNames[i] );

        if( tit == m_packageIds.end() )
        {
            int n = 0;
            RheiaPackageInfo* info = RheiaPackageDBManager::Get()->FindPackageByName(pkgNames[i]);
            RheiaPackageTreeItemData* data = new RheiaPackageTreeItemData( info );

            wxTreeItemId parent = m_treelist->AppendItem(m_root, info->GetControl()->GetTitle(),-1,-1,data);
            m_packageIds[info->GetControl()->GetName()] = parent;

            m_treelist->SetItemText(parent,1,wxString::Format(wxT("%d.%d.%d"),info->GetControl()->GetVersion()->GetMajor(),
                                                            info->GetControl()->GetVersion()->GetMinor() ,
                                                            info->GetControl()->GetVersion()->GetBuild()));

            m_treelist->SetItemText(parent,2,info->GetControl()->GetDescription()->GetShort());

            RheiaPackageManagedFiles* files = info->GetManagedFiles();
            RheiaPackageManagedFileMap filesm = files->GetManagedFiles();
            RheiaPackageManagedFileMap::iterator fit = filesm.begin();

            wxTreeItemId plugins;
            wxTreeItemId libs;
            wxTreeItemId fils;

            for( ; fit != filesm.end() ; ++fit )
            {
                RheiaPackageManagedFile* file = fit->second;

                if( file->GetType().IsSameAs(wxT("plugin")) )
                {
                    if( !plugins.IsOk() )
                        plugins = m_treelist->AppendItem( parent, wxT("Plugins") );

                    wxString name = file->GetName();
                    RheiaPluginRegistration* reg = RheiaPluginManager::Get()->FindElement(name);

                    RheiaPackageTreeItemData* datab = new RheiaPackageTreeItemData( info );
                    wxTreeItemId item = m_treelist->AppendItem (plugins, name,-1,-1,datab);

                    m_treelist->SetItemText(item,1,wxString::Format(wxT("%d.%d.%d"),reg->info->GetVersion()->GetMajor(),
                                                            reg->info->GetVersion()->GetMinor() ,
                                                            reg->info->GetVersion()->GetBuild()));

                    m_treelist->SetItemText(item,2,reg->info->GetTitle());
                }
                else if( file->GetType().IsSameAs(wxT("lib")) )
                {
                    if( !libs.IsOk() )
                        libs = m_treelist->AppendItem( parent, wxT("Libraries") );

                    wxString name = file->GetName();
                    RheiaPackageTreeItemData* datab = new RheiaPackageTreeItemData( info );
                    wxTreeItemId item = m_treelist->AppendItem (libs, name,-1,-1,datab);

                    m_treelist->SetItemText(item,2,file->GetPath());
                }
                else if( file->GetType().IsSameAs(wxT("file")) )
                {
                    if( !fils.IsOk() )
                        fils = m_treelist->AppendItem( parent, wxT("Files") );

                    wxString name = file->GetName();
                    RheiaPackageTreeItemData* datab = new RheiaPackageTreeItemData( info );
                    wxTreeItemId item = m_treelist->AppendItem (fils, name,-1,-1,datab);

                    m_treelist->SetItemText(item,2,file->GetPath());
                }
            }
        }
    }

    // then remove old packages
    TreeItemIdMap::iterator tit = m_packageIds.begin( );
    TreeItemIdMap old = m_packageIds;

    for( ; tit != m_packageIds.end() ; ++tit )
    {
        int index = pkgNames.Index( tit->first );
        if( index == wxNOT_FOUND )
        {
            m_treelist->Delete( tit->second );
            TreeItemIdMap::iterator tit2 = old.find( tit->first );

            if( tit2 != old.end() )
                old.erase(tit2);
        }
    }

    m_packageIds = old;
}

void RheiaPackageManagementDialog::DoBuildPluginsPage()
{

}

void RheiaPackageManagementDialog::DoBuilLibsPage()
{

}

void RheiaPackageManagementDialog::OnPackageListSelection(wxTreeEvent& event)
{
    wxTreeItemId item = event.GetItem();
    RheiaPackageTreeItemData* data = (RheiaPackageTreeItemData*) m_treelist->GetItemData(item);
    event.Skip();

    if( data == 0L )
        return;

    RheiaPackageInfo* info = data->GetInfo();

    if( info == 0L )
        return;


    DoUpdatePackageInfoFor( info );

}

void RheiaPackageManagementDialog::DoUpdatePackageInfoFor( RheiaPackageInfo* info )
{
    wxStaticText* txtName = XRCCTRL(*this,"txtPackageName",wxStaticText);
    wxStaticText* txtPackageVersion = XRCCTRL(*this,"txtPackageVersion",wxStaticText);
    wxStaticText* txtPackageDescriptionShort = XRCCTRL(*this,"txtPackageDescriptionShort",wxStaticText);
    wxStaticText* txtPackageDescription = XRCCTRL(*this,"txtPackageDescription",wxStaticText);

    txtName->SetLabel( info->GetControl()->GetName() );

    wxString vers = wxString::Format(wxT("%d.%d.%d"),info->GetControl()->GetVersion()->GetMajor(),
                                                        info->GetControl()->GetVersion()->GetMinor() ,
                                                        info->GetControl()->GetVersion()->GetBuild());

    txtPackageVersion->SetLabel( vers );
    txtPackageDescriptionShort->SetLabel( info->GetControl()->GetDescription()->GetShort() );
    txtPackageDescription->SetLabel( info->GetControl()->GetDescription()->GetFull() );

    RheiaPackageMaintainer* maint = info->GetControl()->GetMaintainer();

    wxStaticText* txtMaintainerName = XRCCTRL(*this,"txtMaintainerName",wxStaticText);
    wxStaticText* txtMaintainerEmail = XRCCTRL(*this,"txtMaintainerEmail",wxStaticText);
    wxStaticText* txtMaintainerWebsite = XRCCTRL(*this,"txtMaintainerWebsite",wxStaticText);

    txtMaintainerName->SetLabel( maint->GetName() );
    txtMaintainerEmail->SetLabel( maint->GetEmail() );
    txtMaintainerWebsite->SetLabel( maint->GetWebSite() );
}

void RheiaPackageManagementDialog::OnInstallPackage( wxCommandEvent& event )
{
    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_package_path") , RheiaStandardPaths::HomeDirectory() );

    wxFileDialog dialog( this,
                         wxT("Select the workspace files you want to load..."),
                         LastOpenPath,
                         wxEmptyString,
                         FileExt::PACKAGE_EXT_FILE,
                         wxFD_OPEN | wxFD_MULTIPLE );

    if ( dialog.ShowModal() != wxID_OK )
    {
        return;
    }

    wxArrayString filepaths;
    dialog.GetPaths(filepaths);

    wxFileName lastPath( filepaths[0] );
    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_package_path") , lastPath.GetPath() );
    RheiaPackageManager::Get()->Clear();

    for ( unsigned int i = 0; i < filepaths.size() ; i++ )
        RheiaPackageManager::Get()->AddPackageToList(filepaths[i]);

    if( !RheiaPackageManager::Get()->InstallPackages( false , false , false , true ) )
        wxMessageBox( wxT("Something wrong with your package installation contac your administrator ! ") );

    RheiaPackageDBManager::Get()->Save();
    RheiaPluginManager::Get()->LoadAllPlugins();

    DoUpdatePackageTree();
}

void RheiaPackageManagementDialog::OnRemovePackage( wxCommandEvent& event )
{

}

void RheiaPackageManagementDialog::OnPackageInstalled( RheiaEvent& event )
{
    DoUpdatePackageTree();
}

void RheiaPackageManagementDialog::OnPackageRemoved( RheiaEvent& event )
{
    DoUpdatePackageTree();
}

void RheiaPackageManagementDialog::RegiserEvents()
{
    RheiaEventsManager* pm = RheiaEventsManager::Get();

    pm->RegisterEventMethod(RheiaEVT_PACKAGE_INSTALLED, new RheiaEventFunctor<RheiaPackageManagementDialog>(this, RheiaEventHandler(RheiaPackageManagementDialog::OnPackageInstalled)));
    pm->RegisterEventMethod(RheiaEVT_PACKAGE_REMOVED, new RheiaEventFunctor<RheiaPackageManagementDialog>(this, RheiaEventHandler(RheiaPackageManagementDialog::OnPackageRemoved)));
}
