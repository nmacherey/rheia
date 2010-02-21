/**
*   @file RheiaStandardPaths.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	18-November-2009
*	@version 0.0.2
*/
#include <RheiaStandardPaths.h>
#include <RheiaPlatform.h>
#include <RheiaGlobals.h>

#include <wx/url.h>
#include <wx/dir.h>
#include <wx/filesys.h>
#include <wx/intl.h>
#include <wx/menu.h>
#include <wx/string.h>
#include <wx/dynlib.h>
#include <wx/filesys.h>
#include <wx/progdlg.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <wx/msgdlg.h>
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/stdpaths.h>

wxString RheiaStandardPaths::app_name;
wxString RheiaStandardPaths::config_dir;
wxString RheiaStandardPaths::home_dir;
wxString RheiaStandardPaths::data_dir_user;
wxString RheiaStandardPaths::data_dir_global;
wxString RheiaStandardPaths::plugin_dir_global;
wxString RheiaStandardPaths::plugin_dir_user;
wxString RheiaStandardPaths::package_dir_global;
wxString RheiaStandardPaths::package_dir_user;
wxString RheiaStandardPaths::cache_dir_global;
wxString RheiaStandardPaths::cache_dir_user;
wxString RheiaStandardPaths::app_dir;
wxString RheiaStandardPaths::temp_dir;


void RheiaStandardPaths::InitPaths(const wxString& appname)
{
	app_name = appname;
    wxStandardPaths StdPaths;

#if defined( _DEBUG ) || defined( RHEIA_DEBUG )
    RheiaStandardPaths::config_dir = DetermineExecutablePath();
#else
    RheiaStandardPaths::config_dir = StdPaths.GetUserDataDir();
#endif
    RheiaStandardPaths::home_dir = StdPaths.GetUserConfigDir();
    RheiaStandardPaths::app_dir = DetermineExecutablePath();
    wxString res_dir = DetermineResourcesPath();

    // if non-empty, the app has overriden it (e.g. "--prefix" was passed in the command line)
    if (data_dir_global.IsEmpty())
    {
        if (platform::windows)
            RheiaStandardPaths::data_dir_global = app_dir + _T("/share/") + app_name;
        else if (platform::macosx)
            RheiaStandardPaths::data_dir_global = res_dir + _T("/share/") + app_name;
        else
            RheiaStandardPaths::data_dir_global = StdPaths.GetDataDir();
    }

    //RheiaStandardPaths::app_prefix = StdPaths.GetInstallPrefix();

    if (plugin_dir_global.IsEmpty())
    {
        if (platform::windows || platform::macosx)
            RheiaStandardPaths::plugin_dir_global = data_dir_global + wxT("/plugins");
        else
            RheiaStandardPaths::plugin_dir_global = data_dir_global + _T("/plugins");
    }

    if (package_dir_global.IsEmpty())
    {
        if (platform::windows || platform::macosx)
            RheiaStandardPaths::package_dir_global = data_dir_global + wxT("/packages");
        else
            RheiaStandardPaths::package_dir_global = data_dir_global + _T("/packages");
    }

    if (cache_dir_global.IsEmpty())
    {
        if (platform::windows || platform::macosx)
            RheiaStandardPaths::cache_dir_global = data_dir_global + wxT("/cache");
        else
            RheiaStandardPaths::cache_dir_global = data_dir_global + _T("/cache");
    }

    RheiaMakeDirRecursively(RheiaStandardPaths::plugin_dir_global);
    RheiaMakeDirRecursively(RheiaStandardPaths::package_dir_global);
    RheiaMakeDirRecursively(RheiaStandardPaths::cache_dir_global);

    RheiaStandardPaths::temp_dir = StdPaths.GetTempDir();

#if defined( _DEBUG ) || defined( RHEIA_DEBUG )
    RheiaStandardPaths::data_dir_user = data_dir_global;

    RheiaMakeDirRecursively(RheiaStandardPaths::data_dir_user   + _T("/plugins/"));
    RheiaMakeDirRecursively(RheiaStandardPaths::data_dir_user   + _T("/packages/"));
    RheiaMakeDirRecursively(RheiaStandardPaths::data_dir_user   + _T("/cache/"));

    if (plugin_dir_user.IsEmpty())
    {
        RheiaStandardPaths::plugin_dir_user = data_dir_user + wxT("/plugins");
    }

    if (package_dir_user.IsEmpty())
    {
        RheiaStandardPaths::package_dir_user = data_dir_user + wxT("/packages");
    }

    if (cache_dir_user.IsEmpty())
    {
        RheiaStandardPaths::cache_dir_user = data_dir_user + wxT("/packages");
    }
#else
    RheiaStandardPaths::data_dir_user = RheiaStandardPaths::config_dir + wxT("/share/") + app_name;

    RheiaMakeDirRecursively(RheiaStandardPaths::config_dir);
    RheiaMakeDirRecursively(RheiaStandardPaths::data_dir_user   + _T("/plugins/"));
    RheiaMakeDirRecursively(RheiaStandardPaths::data_dir_user   + _T("/packages/"));
    RheiaMakeDirRecursively(RheiaStandardPaths::data_dir_user   + _T("/cache/"));

    if (plugin_dir_user.IsEmpty())
    {
        RheiaStandardPaths::plugin_dir_user = data_dir_user + wxT("/plugins");
    }

    if (package_dir_user.IsEmpty())
    {
        RheiaStandardPaths::package_dir_user = data_dir_user + wxT("/packages");
    }

    if (cache_dir_user.IsEmpty())
    {
        RheiaStandardPaths::cache_dir_user = data_dir_user + wxT("/cache");
    }
#endif
}

wxString RheiaStandardPaths::Directory(RheiaStandardPathsFlags flag)
{
    switch (flag)
    {
    case rspfHome:
        return RheiaStandardPaths::home_dir;

    case rspfInstall:
        return RheiaStandardPaths::app_dir;

    case rspfTemp:
        return RheiaStandardPaths::temp_dir;

    case rspfConfig:
        return RheiaStandardPaths::config_dir;

    case rspfPluginsGlobal:
        return RheiaStandardPaths::plugin_dir_global;

    case rspfPluginsUser:
        return RheiaStandardPaths::plugin_dir_user;

    case rspfPackageGlobal:
        return RheiaStandardPaths::package_dir_global;

    case rspfPackageUser:
        return RheiaStandardPaths::package_dir_user;

    case rspfCacheGlobal:
        return RheiaStandardPaths::cache_dir_global;

    case rspfCacheUser:
        return RheiaStandardPaths::cache_dir_user;

    case rspfDataGlobal:
        return RheiaStandardPaths::data_dir_global;

    case rspfDataUser:
        return RheiaStandardPaths::data_dir_user;

    default:
        return wxEmptyString;
    }
}

namespace RheiaFileFinder
{
    wxString UTILS_DLLEXPORT FindFile(const wxString& filename, int rspf)
    {
        wxPathList pathsList;

        /*** test user paths */
        if (rspf & rspfPluginsUser)
            pathsList.Add(RheiaStandardPaths::PluginsDirectory(false));
        if (rspf & rspfPackageUser)
            pathsList.Add(RheiaStandardPaths::PackageDirectory(false));
        if (rspf & rspfCacheUser)
            pathsList.Add(RheiaStandardPaths::CacheDirectory(false));
        if (rspf & rspfDataUser)
            pathsList.Add(RheiaStandardPaths::DataDirectory(false));

        /*** then test for global paths */
        if (rspf & rspfPluginsGlobal)
            pathsList.Add(RheiaStandardPaths::PluginsDirectory(true));
        if (rspf & rspfPackageGlobal)
            pathsList.Add(RheiaStandardPaths::PackageDirectory(true));
        if (rspf & rspfCacheGlobal)
            pathsList.Add(RheiaStandardPaths::CacheDirectory(true));
        if (rspf & rspfDataGlobal)
            pathsList.Add(RheiaStandardPaths::DataDirectory(true));

        /*** always add the current working directory */
        pathsList.Add(::wxGetCwd());

        /*** then test all other paths */
        if (rspf & rspfHome)
            pathsList.Add(RheiaStandardPaths::HomeDirectory());
        if (rspf & rspfInstall)
            pathsList.Add(RheiaStandardPaths::ExecutableDirectory());
        if (rspf & rspfTemp)
            pathsList.Add(RheiaStandardPaths::TempDirectory());
        if (rspf & rspfConfig)
            pathsList.Add(RheiaStandardPaths::ConfigDirectory());

        /*** then test all other paths */
        if (rspf & rspfPath)
            pathsList.AddEnvList(_T("PATH"));
        if( platform::linux && (rspf & rspfLddir) )
            pathsList.AddEnvList(_T("LD_LIBRARY_PATH"));
        if( platform::macosx && (rspf & rspfLddir) )
            pathsList.AddEnvList(_T("DYLD_LIBRARY_PATH"));

        return pathsList.FindValidPath(filename);
    }
};
