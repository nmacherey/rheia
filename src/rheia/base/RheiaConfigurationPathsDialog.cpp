/**
*	@file RheiaConfigurationPathsDialog.cpp
*
*   Dialog for environement variables configuration
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#include <RheiaConfigurationPathsDialog.h>
#include <RheiaPlatform.h>

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
#include <wx/stdpaths.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>


#if defined(__APPLE__) && defined(__MACH__)
#include <sys/param.h>
#include <mach-o/dyld.h>
#endif

#ifdef __WXMAC__
#include "wx/osx/core/cfstring.h"
#include "wx/intl.h"

#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFURL.h>
#endif

namespace
{

int wxCALLBACK sortByTitle(long item1, long item2, long WXUNUSED(sortData) )
{
    const wxString *elem1 = (const wxString*)item1;
    const wxString *elem2 = (const wxString*)item2;

    return elem1->CompareTo(*elem2);
}

wxString DetermineExecutablePath()
{
#if (__WXMSW__)
    wxChar name[MAX_PATH];
    GetModuleFileName(0L, name, MAX_PATH);
    wxFileName fname(name);
    return fname.GetPath(wxPATH_GET_VOLUME);
#else
#if (__linux__)
    char c[PATH_MAX+1];
    char *p = realpath("/proc/self/exe", &c[0]);
    if (p == 0)
        return _T(".");
    wxFileName fname(RheiaC2U(p));
    return fname.GetPath(wxPATH_GET_VOLUME);
#elif defined(sun) || defined(__sun)
    wxFileName fname(RheiaC2U(getexecname()));
    return fname.GetPath(wxPATH_GET_VOLUME);
#elif defined(__APPLE__) && defined(__MACH__)
    char path[MAXPATHLEN+1];
    uint32_t path_len = MAXPATHLEN;
    // SPI first appeared in Mac OS X 10.2
    _NSGetExecutablePath(path, &path_len);
    wxFileName fname(wxString(path, wxConvUTF8));
    return fname.GetPath(wxPATH_GET_VOLUME);
#else
    return _T(".");
#endif
#endif
};

wxString DetermineResourcesPath()
{
#if defined(__WXMAC__)
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFURLRef absoluteURL = CFURLCopyAbsoluteURL(resourcesURL); // relative -> absolute
    CFRelease(resourcesURL);
    CFStringRef cfStrPath = CFURLCopyFileSystemPath(absoluteURL,kCFURLPOSIXPathStyle);
    CFRelease(absoluteURL);
    #if wxCHECK_VERSION(2, 9, 0)
            wxString str = wxCFStringRef(cfStrPath).AsString(wxLocale::GetSystemEncoding());
    #else
            wxString str = wxMacCFStringHolder(cfStrPath).AsString(wxLocale::GetSystemEncoding());
    #endif

    if (!str.Contains(wxString(_T("/Resources"))))
        return ::DetermineExecutablePath() + _T("/.."); // not a bundle, use relative path
    return str;
#else
    return _T(".");
#endif
};
};

BEGIN_EVENT_TABLE(RheiaConfigurationPathsDialog,wxDialog)

END_EVENT_TABLE()

RheiaConfigurationPathsDialog::RheiaConfigurationPathsDialog(wxWindow* parent):wxDialog()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("dlgPathsSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:paths_dialog.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadDialog(this, parent, xrcDialogName);

    DoUpdateList();
    DoUpdateDebugList();
}

void RheiaConfigurationPathsDialog::DoUpdateList()
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailablePaths", wxListCtrl);
    wxStandardPaths StdPaths;
    list->ClearAll();

    if (list->GetColumnCount() == 0)
    {
        list->InsertColumn(0, _T("Name"));
        list->InsertColumn(1, _T("Value"));
    }

    wxString config_folder = StdPaths.GetUserDataDir();
    wxString home_folder = StdPaths.GetUserConfigDir();
    wxString app_path = ::DetermineExecutablePath();
    wxString res_path = ::DetermineResourcesPath();
    wxString data_path_global;
    wxString plugin_path_global;

    // if non-empty, the app has overriden it (e.g. "--prefix" was passed in the command line)
    if (data_path_global.IsEmpty())
    {
        if (platform::windows)
            data_path_global = app_path + _T("/share/rheia");
        else if (platform::macosx)
            data_path_global = res_path + _T("/share/rheia");
        else
            data_path_global = StdPaths.GetDataDir();
    }

    //RheiaConfigurationManager::app_prefix = StdPaths.GetInstallPrefix();

    if (plugin_path_global.IsEmpty())
    {
        if (platform::windows || platform::macosx)
            plugin_path_global = data_path_global + wxT("/plugins");
        else
            plugin_path_global = data_path_global + _T("/plugins");
    }

    wxString temp_folder = StdPaths.GetTempDir();

    wxString data_path_user = RheiaConfigurationManager::m_reload ? data_path_global : config_folder + _T("/share/rheia");
    wxString plugin_path_user;

    if (plugin_path_user.IsEmpty())
    {
        plugin_path_user = data_path_user + wxT("/plugins");
    }


    long idx = list->InsertItem(0, wxT("Home Folder"));
    list->SetItem(idx, 1, home_folder);
    idx = list->InsertItem(1, wxT("Application Path"));
    list->SetItem(idx, 1, app_path);
    idx = list->InsertItem(2, wxT("Resource Path"));
    list->SetItem(idx, 1, res_path);
    idx = list->InsertItem(3, wxT("Data Path Global"));
    list->SetItem(idx, 1, data_path_global);
    idx = list->InsertItem(4, wxT("Plugin Path Global"));
    list->SetItem(idx, 1, plugin_path_global);
    idx = list->InsertItem(5, wxT("Temp Folder"));
    list->SetItem(idx, 1, temp_folder);
    idx = list->InsertItem(6, wxT("Data Path User"));
    list->SetItem(idx, 1, data_path_user);
    idx = list->InsertItem(7, wxT("Plugin Path User"));
    list->SetItem(idx, 1, plugin_path_user);
    idx = list->InsertItem(8, wxT("Configuration Folder"));
    list->SetItem(idx, 1, config_folder);

    list->SetColumnWidth(0, wxLIST_AUTOSIZE);
    list->SetColumnWidth(1, wxLIST_AUTOSIZE );
}

void RheiaConfigurationPathsDialog::DoUpdateDebugList()
{
    wxListCtrl* list = XRCCTRL(*this, "lstAvailableDebugPaths", wxListCtrl);
    wxStandardPaths StdPaths;
    list->ClearAll();

    if (list->GetColumnCount() == 0)
    {
        list->InsertColumn(0, _T("Name"));
        list->InsertColumn(1, _T("Value"));
    }

    wxString config_folder = ::DetermineExecutablePath();
    wxString home_folder = StdPaths.GetUserConfigDir();
    wxString app_path = ::DetermineExecutablePath();
    wxString res_path = ::DetermineResourcesPath();
    wxString data_path_global;
    wxString plugin_path_global;

    // if non-empty, the app has overriden it (e.g. "--prefix" was passed in the command line)
    if (data_path_global.IsEmpty())
    {
        if (platform::windows)
            data_path_global = app_path + _T("/share/rheia");
        else if (platform::macosx)
            data_path_global = res_path + _T("/share/rheia");
        else
            data_path_global = StdPaths.GetDataDir();
    }

    //RheiaConfigurationManager::app_prefix = StdPaths.GetInstallPrefix();

    if (plugin_path_global.IsEmpty())
    {
        if (platform::windows || platform::macosx)
            plugin_path_global = data_path_global + wxT("/plugins");
        else
            plugin_path_global = data_path_global + _T("/plugins");
    }

    wxString temp_folder = StdPaths.GetTempDir();

    wxString data_path_user = data_path_global;
    wxString plugin_path_user;

    if (plugin_path_user.IsEmpty())
    {
        plugin_path_user = data_path_user + wxT("/plugins");
    }


    long idx = list->InsertItem(0, wxT("Home Folder"));
    list->SetItem(idx, 1, home_folder);
    idx = list->InsertItem(1, wxT("Application Path"));
    list->SetItem(idx, 1, app_path);
    idx = list->InsertItem(2, wxT("Resource Path"));
    list->SetItem(idx, 1, res_path);
    idx = list->InsertItem(3, wxT("Data Path Global"));
    list->SetItem(idx, 1, data_path_global);
    idx = list->InsertItem(4, wxT("Plugin Path Global"));
    list->SetItem(idx, 1, plugin_path_global);
    idx = list->InsertItem(5, wxT("Temp Folder"));
    list->SetItem(idx, 1, temp_folder);
    idx = list->InsertItem(6, wxT("Data Path User"));
    list->SetItem(idx, 1, data_path_user);
    idx = list->InsertItem(7, wxT("Plugin Path User"));
    list->SetItem(idx, 1, plugin_path_user);
    idx = list->InsertItem(8, wxT("Configuration Folder"));
    list->SetItem(idx, 1, config_folder);

    list->SetColumnWidth(0, wxLIST_AUTOSIZE);
    list->SetColumnWidth(1, wxLIST_AUTOSIZE );
}

void RheiaConfigurationPathsDialog::EndModal(int retCode)
{
    wxDialog::EndModal( retCode );
}

