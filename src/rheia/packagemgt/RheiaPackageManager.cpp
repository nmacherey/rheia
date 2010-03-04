/**
*   @file RheiaPackageManager.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/

#include <RheiaPackageDBManager.h>
#include <RheiaPackageInfo.h>
#include <RheiaPackageManager.h>
#include <RheiaPackageManagedFile.h>
#include <RheiaPackageManagedFiles.h>
#include <RheiaPackageFile.h>
#include <RheiaPackageFiles.h>
#include <RheiaPackageDependencies.h>
#include <RheiaPackageDependency.h>
#include <RheiaPackageVersion.h>
#include <RheiaPackageControl.h>
#include <RheiaStandardPaths.h>
#include <RheiaPlatform.h>
#include <RheiaAppGlobals.h>
#include <RheiaConfigurationManager.h>
#include <RheiaInfoWindow.h>
#include <RheiaLogger.h>
#include <RheiaLoggerManager.h>
#include <RheiaEventsManager.h>
#include <RheiaPackageManagementDialog.h>
#include <RheiaEvents.h>

#include "sdkversion.h"

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#include <list>
#include <algorithm>

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
#include <wx/filefn.h>

/*! declare global instance for the RheiaPackageManager */
template<> RheiaPackageManager* Mgr<RheiaPackageManager>::instance = 0;
/*! declare global isShutdown for the RheiaPackageManager */
template<> bool Mgr<RheiaPackageManager>::isShutdown = false;

BEGIN_EVENT_TABLE(RheiaPackageManager,wxEvtHandler)
    //EVT_FRAME_CLOSING( RheiaPackageManager::OnCloseFrame )
END_EVENT_TABLE()

RheiaPackageManager::RheiaPackageManager()
{

}

RheiaPackageManager::~RheiaPackageManager()
{
    Clear();
}

bool RheiaPackageManager::AddPackageToList( const wxString& filename )
{
    wxString path = wxFileName(filename).GetPath();

    RheiaPackageScanInfo info;
    info.fullname = filename;
    info.path = path;

    wxString basename = wxFileName(filename).GetName();
    info.fullname = basename;

    wxString version;
    if (basename.Contains(wxT('-')))
    {
        version = basename.AfterFirst(wxT('-'));
        basename = basename.BeforeFirst(wxT('-'));
    }

    info.name = basename;
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::AddPackageToList::Storing file : ") + basename + wxT(" in the pending package list ...") , RheiaLogging::info );
    m_packages[info.name] = info;

    return true;
}

int RheiaPackageManager::ScanForPackages( const wxString& path )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::Scanning for packages in : ") + path + wxT(" ...") , RheiaLogging::info );

    const wxString mask = FileExt::PACKAGE_EXT_FILE;

    int count = 0;

    if (!wxDirExists(path))
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::Dir : ") + path + wxT(", does not exists...") , RheiaLogging::error );
        return count;
    }

    wxDir dir(path);

    if (!dir.IsOpened())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::Cannot open dir : ") + path + wxT(", continuing happily...") , RheiaLogging::error );
        return count;
    }

    wxString filename;
    wxString failed;
    bool ok = dir.GetFirst(&filename, mask, wxDIR_FILES);

    while (ok)
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::Scan::Find file : ") + filename + wxT(" ...") , RheiaLogging::info );
        RheiaPackageScanInfo info;
        info.fullname = filename;
        info.path = path;

        wxString basename = wxFileName(filename).GetName();
        info.fullname = basename;

        wxString version;
        if (basename.Contains(wxT('-')))
        {
            version = basename.AfterFirst(wxT('-'));
            basename = basename.BeforeFirst(wxT('-'));
        }

        info.name = basename;
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::Scan::Storing file : ") + basename + wxT(" in the pending package list ...") , RheiaLogging::info );
        m_packages[info.name] = info;
        ok = dir.GetNext(&filename);
        count++;
    }

    wxString cstr = wxString::Format( wxT("Found %d packages in path : ") , count );
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::Scan::") + cstr + wxT(" in the pending package dir : ") + path + wxT(" ...") , RheiaLogging::info );
    return count;
}

bool RheiaPackageManager::InstallPackages( bool askfor , bool globaly, bool silent , bool confirm )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Checking for packages to install in the global directory...") , RheiaLogging::info );

    // Once the scan is done, order packages by dependencies
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Computing dependencies for pending packages...") , RheiaLogging::info );
    wxArrayString packages = OrderScanByDependencies( );

    if( packages.GetCount() == 0 )
        return false;

    if( askfor )
    {
        wxString msg = wxT("The following packages are available for installation : \n\n");

        for( unsigned int i = 0 ; i < packages.GetCount() ; ++i )
            msg += packages[i] + wxT("\n");

        msg += wxT("\n");

        if (wxMessageBox(msg + wxT('\n') +
                         wxT("Do you wan to install this packages ?"),
                         wxT("Confirmation"), wxICON_QUESTION | wxYES_NO) == wxNO)
        {
            return false;
        }
    }
    // Now check dependencies for all packages
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Checking dependencies for pending packages...") , RheiaLogging::info );
    wxString msg = wxString::Format( wxT("number of packages to install %d") , packages.GetCount() );
    RheiaLoggerManager::sdLog( msg , RheiaLogging::warning );
    wxString error = CheckScanDependencies( packages );
    msg = wxString::Format( wxT("number of packages to install %d") , packages.GetCount() );
    RheiaLoggerManager::sdLog( msg , RheiaLogging::warning );
    // and install all packages in the packages array

    for( unsigned int i = 0 ; i < packages.GetCount() ; ++i )
    {
        RheiaPackageScanInfoMap::iterator it = m_packages.find( packages[i] );
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Installing package : ") + packages[i] , RheiaLogging::info );
        if( it != m_packages.end() )
        {
            RheiaPackageScanInfo info = it->second;
            wxString packagename = info.path + wxT("/") + info.fullname + FileExt::PACKAGE_EXT;

            // First check if we can access the destination file
            if (wxFileExists(packagename) && wxFile::Access(packagename, wxFile::write))
            {
                wxString str = wxT("Package : ") + it->first + wxT("\n")
                               + wxT("Fullname :") + info.fullname + wxT("\n")
                               + wxT("Path :") + info.path + wxT("\n");

                RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Installing package : \n") + str , RheiaLogging::info );

                if( InstallPackage( it->first,
                                    info.fullname ,
                                    info.path ,
                                    globaly,
                                    silent,
                                    confirm ) )
                {
                    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Package  : ") + it->first + wxT(" installed, moving package file to cache directory : ") + RheiaStandardPaths::CacheDirectory(globaly) + wxT("...") , RheiaLogging::info );
                }
                else
                {
                    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Package installation failed abording installation task...") , RheiaLogging::error );

                }
                /** @todo here add additional management if the package was not installed and some other new packages depends on the new one */

            }
            else
            {
                wxString str = wxT("Package : ") + it->first + wxT("\n")
                               + wxT("Fullname :") + info.fullname + wxT("\n")
                               + wxT("Path :") + info.path + wxT("\n");

                RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Installing package failed : \n") + str , RheiaLogging::warning );

            }
        }
        else
        {
            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Not Found package : ") + packages[i] , RheiaLogging::info );
        }
    }

    if( !error.IsEmpty() )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackages::Package checking task returns the following error : \n") + error , RheiaLogging::warning );
        return false;
    }

    return true;
}

void RheiaPackageManager::InstallPendingPackages( bool askfor )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Checking for packages to install in the global directory...") , RheiaLogging::info );

    int count = 0;
    count += ScanForPackages( RheiaStandardPaths::PackageDirectoryGlobal() );
    bool globaly = true;

    if( count != 0 )
    {

        // Once the scan is done, order packages by dependencies
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Computing dependencies for pending packages...") , RheiaLogging::info );
        wxArrayString packages = OrderScanByDependencies( );

        if( packages.GetCount() == 0 )
            return;

        if( askfor )
        {
            wxString msg = wxT("The following packages are available for installation : \n\n");

            for( unsigned int i = 0 ; i < packages.GetCount() ; ++i )
                msg += packages[i] + wxT("\n");

            msg += wxT("\n");

            if (wxMessageBox(msg + wxT('\n') +
                             wxT("Do you wan to install this packages ?"),
                             wxT("Confirmation"), wxICON_QUESTION | wxYES_NO) == wxNO)
            {
                return;
            }
        }
        // Now check dependencies for all packages
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Checking dependencies for pending packages...") , RheiaLogging::info );
        wxString msg = wxString::Format( wxT("number of packages to install %d") , packages.GetCount() );
        RheiaLoggerManager::sdLog( msg , RheiaLogging::warning );
        wxString error = CheckScanDependencies( packages );
        msg = wxString::Format( wxT("number of packages to install %d") , packages.GetCount() );
        RheiaLoggerManager::sdLog( msg , RheiaLogging::warning );
        // and install all packages in the packages array

        for( unsigned int i = 0 ; i < packages.GetCount() ; ++i )
        {
            RheiaPackageScanInfoMap::iterator it = m_packages.find( packages[i] );
            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Installing package : ") + packages[i] , RheiaLogging::info );
            if( it != m_packages.end() )
            {
                RheiaPackageScanInfo info = it->second;
                bool silent = true;
                bool confirm = false;

                wxString packagename = info.path + wxT("/") + info.fullname + FileExt::PACKAGE_EXT;

                // First check if we can access the destination file
                if (wxFileExists(packagename) && wxFile::Access(packagename, wxFile::write))
                {
                    wxString str = wxT("Package : ") + it->first + wxT("\n")
                                   + wxT("Fullname :") + info.fullname + wxT("\n")
                                   + wxT("Path :") + info.path + wxT("\n");

                    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Installing package : \n") + str , RheiaLogging::info );

                    if( InstallPackage( it->first,
                                        info.fullname ,
                                        info.path ,
                                        globaly,
                                        silent,
                                        confirm ) )
                    {
                        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Package  : ") + it->first + wxT(" installed, moving package file to cache directory : ") + RheiaStandardPaths::CacheDirectory(globaly) + wxT("...") , RheiaLogging::info );
                        wxString newname = RheiaStandardPaths::CacheDirectory(globaly) + wxT("/") + info.fullname + FileExt::PACKAGE_EXT;
                        ::wxRenameFile( packagename , newname );
                    }
                    else
                    {
                        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Package installation failed abording installation task...") , RheiaLogging::error );
                    }
                    /** @todo here add additional management if the package was not installed and some other new packages depends on the new one */

                }
                else
                {
                    wxString str = wxT("Package : ") + it->first + wxT("\n")
                                   + wxT("Fullname :") + info.fullname + wxT("\n")
                                   + wxT("Path :") + info.path + wxT("\n");

                    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Installing package failed : \n") + str , RheiaLogging::warning );
                }
            }
            else
            {
                RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Not Found package : ") + packages[i] , RheiaLogging::info );
            }
        }

        if( !error.IsEmpty() )
            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Package checking task returns the following error : \n") + error , RheiaLogging::warning );
    }

    count = 0;
    Clear();
    globaly = false;

#if !defined( _DEBUG ) && !defined( RHEIA_DEBUG )
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Checking for packages to install in the user's directory...") , RheiaLogging::info );
    count += ScanForPackages( RheiaStandardPaths::PackageDirectoryUser() );
    if( count != 0 )
    {

        // Once the scan is done, order packages by dependencies
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Computing dependencies for pending packages...") , RheiaLogging::info );
        wxArrayString packages = OrderScanByDependencies( );

        if( packages.GetCount() == 0 )
            return;

        if( askfor )
        {
            wxString msg = wxT("The following packages are available for installation : \n\n");

            for( unsigned int i = 0 ; i < packages.GetCount() ; ++i )
                msg += packages[i] + wxT("\n");

            msg += wxT("\n");

            if (wxMessageBox(msg + wxT('\n') +
                             wxT("Do you wan to install this packages ?"),
                             wxT("Confirmation"), wxICON_QUESTION | wxYES_NO) == wxNO)
            {
                return;
            }
        }
        // Now check dependencies for all packages
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Checking dependencies for pending packages...") , RheiaLogging::info );
        wxString error = CheckScanDependencies( packages );
        // and install all packages in the packages array

        for( unsigned int i = 0 ; i < packages.GetCount() ; ++i )
        {
            RheiaPackageScanInfoMap::iterator it = m_packages.find( packages[i] );
            if( it != m_packages.end() )
            {
                RheiaPackageScanInfo info = it->second;
                bool silent = true;
                bool confirm = false;

                wxString packagename = info.path + info.fullname + FileExt::PACKAGE_EXT;

                // First check if we can access the destination file
                if (wxFileExists(packagename) && wxFile::Access(packagename, wxFile::write))
                {
                    wxString str = wxT("Package : ") + it->first + wxT("\n")
                                   + wxT("Fullname :") + info.fullname + wxT("\n")
                                   + wxT("Path :") + info.path + wxT("\n");

                    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Installing package : \n") + str , RheiaLogging::info );

                    if( InstallPackage( it->first,
                                        info.fullname ,
                                        info.path ,
                                        globaly,
                                        silent,
                                        confirm ) )
                    {
                        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Package  : ") + it->first + wxT(" installed, moving package file to cache directory : ") + RheiaStandardPaths::CacheDirectory(globaly) + wxT("...") , RheiaLogging::info );
                        wxString newname = RheiaStandardPaths::CacheDirectory(globaly) + info.fullname + FileExt::PACKAGE_EXT;
                        ::wxRenameFile( packagename , newname );
                    }
                    else
                    {
                        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Package installation failed abording installation task...") , RheiaLogging::error );
                        return;
                    }
                    /** @todo here add additional management if the package was not installed and some other new packages depends on the new one */
                }
            }
        }

        if( !error.IsEmpty() )
            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPending::Package checking task returns the following error : \n") + error , RheiaLogging::info );
    }
#endif
}

bool RheiaPackageManager::ExtractFile( const wxString& package, const wxString& source, const wxString& destination )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFile::Extracting File from : ") + source + wxT(" to : ") + destination + wxT(" ..."), RheiaLogging::info );

    // First check if we can access the destination file
    if (wxFileExists(destination) && !wxFile::Access(destination, wxFile::write))
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFile::Package destination file : ") + destination + wxT(" is in use, Abborting..."), RheiaLogging::warning );
        return false;
    }

    // First check if we can access the package file
    if ( !wxFileExists(package + FileExt::PACKAGE_EXT) )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFile::Package file : ") + package + FileExt::PACKAGE_EXT + wxT(" does not exists, Abborting..."), RheiaLogging::warning );
        return false;
    }

    // make sure destination dir exists
    RheiaMakeDir(wxFileName(destination).GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR));

    wxFileSystem* fs = new wxFileSystem;
    wxFSFile* f = fs->OpenFile(package + FileExt::PACKAGE_EXT + wxT("#zip:") + source);
    if (f)
    {
        // open output file for writing
        wxFile output(destination, wxFile::write);
        if (!output.IsOpened())
        {
            wxString msg = wxString::Format(wxT("Can't open destination file '%s' for writing..."),
                                            destination.c_str());

            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFile::") + msg , RheiaLogging::error );

            delete f;
            delete fs;
            return false;
        }

        // copy file
        wxInputStream* is = f->GetStream();
        char tmp[1025] = {};
        while (!is->Eof() && is->CanRead())
        {
            memset(tmp, 0, sizeof(tmp));
            is->Read(tmp, sizeof(tmp) - 1);
            output.Write(tmp, is->LastRead());
        }
        delete f;
    }
    else
    {
        wxString msg = wxString::Format(wxT("File '%s' not found in package '%s'... Continuing happily !"),
                                        source.c_str(), package.c_str());
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFile::") + msg , RheiaLogging::error );
        delete fs;
        return false;
    }

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFile::File from : ") + source + wxT(" to : ") + destination + wxT(" successfully extracted..."), RheiaLogging::info );
    delete fs;
    return true;
}

RheiaPackageControl* RheiaPackageManager::ReadControlFileFor( const wxString& file )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ReadControlFileFor::Reading control file : ") + file + wxT(" ..."), RheiaLogging::info );

    RheiaPackageControl* ctrl = NULL;

    xmlDoc* doc = xmlParseFile( rcU2C( file ) );

    if ( doc== NULL )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ReadControlFileFor::Cannot parse xml control file : ") + file + wxT(" ..."), RheiaLogging::error );
        return NULL;
    }

    xmlNode* root = xmlDocGetRootElement( doc );

    if ( root == NULL )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ReadControlFileFor::Xml control file : ") + file + wxT(" has no root element..."), RheiaLogging::error );
        xmlFreeDoc( doc );
        return false;
    }

    wxString rname = RheiaC2U( (const char*) root->name );

    if ( !rname.IsSameAs( wxT("RheiaPackage") ) )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ReadControlFileFor::Bad root name for control file shall be RheiaPackage and it is : ") + rname + wxT(" ..."), RheiaLogging::error );
        xmlFreeDoc( doc );
        return NULL;
    }

    ctrl = new RheiaPackageControl();

    if ( !ctrl->DoReadFromNode( root ) )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ReadControlFileFor::Control file is invalid : ") + file + wxT(" ..."), RheiaLogging::error );
        delete ctrl;
        xmlFreeDoc( doc );
        return NULL;
    }

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ReadControlFileFor::Package file : ") + file + wxT(" , has been successfuly read, removing it from hard drive..."), RheiaLogging::info );
    ::wxRemoveFile( file );

    return ctrl;
}

bool RheiaPackageManager::InstallPackage( const wxString& name ,
        const wxString& fullname ,
        const wxString& path ,
        bool globaly ,
        bool silent  ,
        bool confirm )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Installing package : ") + name + wxT(" ..."), RheiaLogging::info );

    wxProgressDialog *pd = NULL;

    if ( !silent )
        pd = new wxProgressDialog( wxT("Installing: ") + name, wxT("Please wait"), 6);

    // the first thing to do is to extract the package control.xml file and to store it
    // in the temp directory
    wxString source = wxT("control.xml");
    wxString destination = RheiaStandardPaths::TempDirectory() + wxT("/") + name + wxT(".xml");

    if ( !silent )
        pd->Update( 1, wxT("RheiaPackageManager::InstallPackage::Extracting package control file...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Extracting package control file..."), RheiaLogging::info );
    if ( !ExtractFile( path + wxT("/") + fullname , source , destination ) )
    {
        if ( pd != NULL )
            pd->Destroy();

        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Cannot extract package control file..."), RheiaLogging::info );
        return false;
    }

    if ( !silent )
        pd->Update( 2, wxT("Reading package control file...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Reading package control file..."), RheiaLogging::info );
    RheiaPackageControl* ctrl = ReadControlFileFor( destination );
    if ( ctrl == NULL )
    {
        if ( pd != NULL )
            pd->Destroy();

        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Cannot read package control file..."), RheiaLogging::info );
        return false;
    }

    if ( !silent )
        pd->Update( 3, wxT("Checking for existing package...") );

    // Before doing anything, we have to check for existing packages
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Checking for existing and conflicting packages..."), RheiaLogging::info );
    if( RheiaPackageDBManager::Get()->Exists( name ) )
    {
        RheiaPackageInfo* info = RheiaPackageDBManager::Get()->FindPackageByName( name );
        if( info != NULL )
        {
            if( confirm )
            {
                wxString msg = wxT("A package with the same name is already installed.\n");
                RheiaPackageVersion* version = ctrl->GetVersion();
                RheiaPackageVersion* i_version = info->GetControl()->GetVersion();

                if (CompareVersions(version->GetMajor() , version->GetMinor() , i_version->GetMajor() , i_version->GetMinor()) < 0)
                {
                    msg = wxT("The package you are trying to install, is older  than the one currently installed.");
                }

                if (wxMessageBox(msg + wxT('\n') +
                                 wxT("If you want to proceed, the installed package will be  uninstalled first.\n Do you want to proceed?"),
                                 wxT("Confirmation"), wxICON_QUESTION | wxYES_NO) == wxNO)
                {
                    if ( pd != NULL )
                        pd->Destroy();

                    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Package installation aborted by the user..."), RheiaLogging::warning );
                    return false;
                }
            }

            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Uninstalling already installed packages..."), RheiaLogging::info );
            if( !PurgePackage( name , silent , confirm , false ) )
            {
                if ( pd != NULL )
                    pd->Destroy();

                RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Package cannot be uninstalled..."), RheiaLogging::error );
                return false;
            }
        }
    }

    if ( !silent )
        pd->Update( 4, wxT("Checking package dependencies...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Checking package dependencies..."), RheiaLogging::info );
    RheiaPackageDependencies* deps = ctrl->GetDependencies();

    /** @todo here check if all package dependecies are satisfied or not */

    if ( !silent )
        pd->Update( 5, wxT("Instaling package files...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Instaling package files..."), RheiaLogging::info );

    wxString error;
    wxArrayString installed_files;

    RheiaPackageInfo* info = new RheiaPackageInfo();
    info->SetControl( ctrl );
    RheiaPackageManagedFiles* files = new RheiaPackageManagedFiles();

    // first open the plugins directory from the package file
    wxString fpath = wxT("plugins/");
    wxString destDir = RheiaStandardPaths::PluginsDirectory( globaly ) + wxT('/');

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Extracting plugins..."), RheiaLogging::info );
    // extract plugins
    ExtractFiles( path + wxT("/") + fullname,
                  fpath,
                  FileExt::PLUGIN_EXT_FILE,
                  destDir,
                  error,
                  installed_files,
                  files,
                  wxT("plugin") );

    fpath = wxT("libs/");
    destDir = RheiaStandardPaths::PluginsDirectory( globaly ) + wxT("/libs/");

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Extracting libs..."), RheiaLogging::info );
    // extract libs
    ExtractFiles( path + wxT("/") + fullname,
                  fpath,
                  FileExt::DYNAMIC_LIBRARY_FILE_EXT,
                  destDir,
                  error,
                  installed_files,
                  files,
                  wxT("lib") );

    fpath = wxT("resources/");
    destDir = RheiaStandardPaths::DataDirectory( globaly ) + wxT("/");

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Extracting extra files..."), RheiaLogging::info );
    // extract resources
    ExtractFiles( path + wxT("/") + fullname,
                  fpath,
                  wxT("*.*"),
                  destDir,
                  error,
                  installed_files,
                  files,
                  wxT("file") );

    // Finally register files in the info structure
    info->SetManagedFiles( files );

    if( !error.IsEmpty() )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Installation aborted because installation task returns the follwoing error message : \n") + error , RheiaLogging::error );

        for( unsigned int i = 0 ; i < installed_files.GetCount() ; ++i )
            ::wxRemoveFile( installed_files[i] );

        delete info;

        if ( pd != NULL )
            pd->Destroy();

        return false;
    }

    if ( !silent )
        pd->Update( 6, wxT("Registering package in data base...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Registering package informations in the package data base..."), RheiaLogging::info );
    RheiaPackageDBManager::Get()->RegisterPackage( info );

    if ( pd != NULL )
        pd->Destroy();

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::InstallPackage::Package : ") + name + wxT(" installed ..."), RheiaLogging::info );

    RheiaEvent event( RheiaEVT_PACKAGE_INSTALLED );
    RheiaEventsManager::Get()->ProcessEvent(event);

    return true;
}

bool RheiaPackageManager::PurgePackage( const wxString& name ,
                                        bool silent,
                                        bool confirm,
                                        bool recursive )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Removing package : ") + name + wxT(" ..."), RheiaLogging::info );

    // First get the package info from the data base manager
    wxProgressDialog *pd = NULL;

    if ( !silent )
        pd = new wxProgressDialog( wxT("Removing package : ") + name, wxT("Please wait"), 3);

    RheiaPackageInfo* info = RheiaPackageDBManager::Get()->FindPackageByName( name );

    if( info == NULL )
    {
        if ( pd != NULL )
            pd->Destroy();

        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Package : ") + name + wxT(" , cannot be found in data base..."), RheiaLogging::info );

        return true;
    }

    if ( !silent )
        pd->Update( 1, wxT("Checking for dependent packages...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Checking for dependent packages ..."), RheiaLogging::info );

    wxArrayString dependents = RheiaPackageDBManager::Get()->ListDependentPackagesFor( name );

    if( dependents.GetCount() != 0 && recursive )
    {
        wxString msg = wxT("Some packages are dependent of the one you are trying to uninstall.\n\tPackages are :\n\n");
        for( unsigned int i = 0 ; i < dependents.GetCount() ; ++i )
            msg += wxT("\t\t") + dependents[i];

        if( confirm )
        {
            if (wxMessageBox(msg + wxT('\n') +
                             wxT("If you want to proceed, the installed package and all its dependencies will be uninstalled from the application.\n Do you want to proceed?"),
                             wxT("Confirmation"), wxICON_QUESTION | wxYES_NO) == wxID_NO)
            {
                if ( pd != NULL )
                    pd->Destroy();

                RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Package removal aborted by the user..."), RheiaLogging::info );

                return false;
            }
        }

        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Package has some dependencies : \n") + msg, RheiaLogging::info );

        for( unsigned int i = 0 ; i < dependents.GetCount() ; ++i )
        {
            RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Removing dependent package : ") + dependents[i] + wxT(" ..."), RheiaLogging::info );
            if( !PurgePackage( dependents[i] , silent , false , true ) )
            {
                if ( pd != NULL )
                    pd->Destroy();

                return false;
            }
        }
    }

    if ( !silent )
        pd->Update( 2, wxT("Removing package files...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Removing package files ..."), RheiaLogging::info );

    RheiaPackageManagedFiles* files = info->GetManagedFiles();
    RheiaPackageManagedFileMap m_files = files->GetManagedFiles();

    RheiaPackageManagedFileMap::iterator fit = m_files.begin();

    for( ; fit != m_files.end() ; ++fit )
    {
        if (wxFileExists(fit->second->GetPath()) && !wxFile::Access(fit->second->GetPath(), wxFile::write))
        {
            // no write-access; abort
            wxMessageBox(_("You don't have the needed privileges to uninstall this package.\n"
                           "Ask your administrator to uninstall this package for you..."),
                         _("Warning"), wxICON_WARNING);

            RheiaLoggerManager::sdLog( wxT("You don't have the needed privileges to uninstall this package.\nAsk your administrator to uninstall this package for you..."), RheiaLogging::error );

            if ( pd != NULL )
                pd->Destroy();

            return false;
        }
    }

    fit = m_files.begin();
    for( ; fit != m_files.end() ; ++fit )
    {
        wxString type = fit->second->GetType();
        if( type.IsSameAs( wxT("plugin") ) )
        {
            /** @todo remove the plugin from the plugin manager and uninstall it */

        }
        ::wxRemoveFile( fit->second->GetPath() );
    }

    if ( !silent )
        pd->Update( 3, wxT("Unregistering your package from the data base...") );

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Unregistering your package from the data base ..."), RheiaLogging::info );
    RheiaPackageDBManager::Get()->UnregisterPackage( name );

    if ( pd != NULL )
        pd->Destroy();

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::PurgePackage::Package : ") + name + wxT(" removed from your system..."), RheiaLogging::info );

    RheiaEvent event( RheiaEVT_PACKAGE_REMOVED );
    RheiaEventsManager::Get()->ProcessEvent(event);

    return true;
}

bool RheiaPackageManager::ExtractFiles( const wxString& package,
                                        const wxString& dir,
                                        const wxString& ext,
                                        const wxString& destination,
                                        wxString& error,
                                        wxArrayString& installed,
                                        RheiaPackageManagedFiles* files,
                                        const wxString& type )
{
    wxFileSystem* fs = new wxFileSystem;
    wxString fullpath = package + FileExt::PACKAGE_EXT + wxT("#zip:");

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFiles::Extracting files for package : ") + package + wxT(" ..."), RheiaLogging::info );

    wxString file_ext = ext;
    file_ext = file_ext.AfterFirst( wxT('.') );
    file_ext = wxT("*.") + file_ext;

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFiles::File extension is : ") + file_ext + wxT(" ..."), RheiaLogging::info );

    wxString real_ext = ext;
    real_ext = real_ext.AfterFirst( wxT('.') );
    real_ext = wxT(".") + real_ext;

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFiles::Real extension is : ") + real_ext + wxT(" ..."), RheiaLogging::info );

    wxString real_dest = destination;
    if( !(real_dest.Last() == wxT('/')) )
        real_dest += wxT('/');

    wxString real_dir = dir;
    if( !(real_dir.Last() == wxT('/')) )
        real_dir += wxT('/');

    wxString fulldir = fullpath + real_dir;

    RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFiles::Full dir is : ") + fulldir + wxT(" ..."), RheiaLogging::info );

    wxString filename = fs->FindFirst( fulldir + file_ext  , wxFILE );

    while( !filename.IsEmpty() )
    {
        wxString dest = real_dest + wxFileName( filename ).GetName() + wxT(".") + wxFileName( filename ).GetExt();
        wxString src = real_dir + wxFileName( filename ).GetName() + wxT(".") + wxFileName( filename ).GetExt();

        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFiles::Destination is : ") + dest + wxT(" ..."), RheiaLogging::info );
        RheiaLoggerManager::sdLog( wxT("RheiaPackageManager::ExtractFiles::Source is : ") + src + wxT(" ..."), RheiaLogging::info );

        if( !ExtractFile( package , src , dest ) )
        {
            error += wxT("Cannot extract plugin : ") + wxFileName( filename ).GetName() +
                     wxT(" from your package : ") + package + wxT('\n');
        }
        else
        {
            installed.Add( filename );
            //Register the package file in the package info
            RheiaPackageManagedFile* file = new RheiaPackageManagedFile();

            wxString fname = wxFileName( filename ).GetName();
            wxString version;
            if (fname.Contains(wxT('-')))
            {
                version = fname.AfterFirst(wxT('-'));
                fname = fname.BeforeFirst(wxT('-'));
            }

            if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && fname.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
                fname = fname.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

            file->SetName( fname );
            file->SetPath( dest );
            file->SetType( type );
            file->SetRemove( true );

            files->Add( fname , file );
        }
        filename = fs->FindNext();
    }

    delete fs;
    return true;
}

void RheiaPackageManager::Clear()
{
    RheiaPackageScanInfoMap::iterator it = m_packages.begin();
    for ( ; it != m_packages.end() ; ++it )
        if ( it->second.control != NULL )
            delete it->second.control;

    m_packages.clear();
}

typedef std::map< wxString , RheiaPackageControl* > ControlMap;

bool AddDepstoList( wxArrayString& list , ControlMap& controls , const wxString& name )
{
    ControlMap::iterator cit = controls.find(name);
    if( cit == controls.end() )
        return false;

    RheiaPackageControl* ctrl = cit->second;
    RheiaPackageDependencies* deps = ctrl->GetDependencies();
    RheiaPackageDependencyMap m_deps = deps->GetDependencies();

    RheiaPackageDependencyMap::iterator dit = m_deps.begin();
    for ( ; dit != m_deps.end() ; ++dit )
    {
        ControlMap::iterator cit2 = controls.find(dit->first);
        if( cit2 != controls.end() )
        {
            if( !AddDepstoList(list , controls , dit->first ) )
                return false;

            int idx = list.Index( dit->first );
            if( idx == wxNOT_FOUND )
                list.Add( dit->first );
        }
    }

    int idx = list.Index( name );
    if( idx == wxNOT_FOUND )
        list.Add( name );

    return true;
}

bool DoubleDepsCheck( wxArrayString& list, ControlMap& controls , const wxString& name , const wxString& depname )
{
    ControlMap::iterator cit = controls.find(depname);
    if( cit == controls.end() )
        return false;

    RheiaPackageControl* ctrl = cit->second;
    RheiaPackageDependencies* deps = ctrl->GetDependencies();
    RheiaPackageDependencyMap m_deps = deps->GetDependencies();

    RheiaPackageDependencyMap::iterator dit = m_deps.begin();
    for ( ; dit != m_deps.end() ; ++dit )
    {
        if( dit->first.IsSameAs(name) )
        {
            int idx = list.Index( name );
            if( idx == wxNOT_FOUND )
                list.Add( name );
        }
        else
        {
            ControlMap::iterator cit2 = controls.find(dit->first);
            if( cit2 != controls.end() )
                DoubleDepsCheck(list , controls , name , dit->first );
        }
    }

    return true;
}

wxArrayString RheiaPackageManager::OrderScanByDependencies( )
{
    wxArrayString ret;

    ControlMap controls;

    wxString error;

    //First extract all package controls
    RheiaPackageScanInfoMap::iterator it = m_packages.begin();
    for ( ; it != m_packages.end() ; ++it )
    {
        wxString source = wxT("control.xml");
        wxString destination = RheiaStandardPaths::TempDirectory() + wxT("/") + it->first + wxT(".xml");

        if ( ExtractFile( it->second.path + wxT("/") + it->second.fullname , source , destination ) )
        {
            RheiaPackageControl* ctrl = ReadControlFileFor( destination );
            if ( ctrl != NULL )
            {
                controls[it->first] = ctrl;
                it->second.control = ctrl;
            }
        }
    }

    // First check if I am my own dependent (dummy but for security :-))
    ControlMap::iterator cit = controls.begin();
    wxArrayString invalids;
    for ( ; cit != controls.end() ; ++cit )
    {
        RheiaPackageControl* ctrl = cit->second;
        RheiaPackageDependencies* deps = ctrl->GetDependencies();
        RheiaPackageDependencyMap m_deps = deps->GetDependencies();

        RheiaPackageDependencyMap::iterator dit = m_deps.find(cit->first);
        if( dit != m_deps.end() )
            invalids.Add( cit->first );
    }

    if( invalids.GetCount() != 0 )
    {
        for( unsigned int i = 0; i < invalids.GetCount() ; i++ )
        {
            cit = controls.find(invalids[i]);
            error += wxT("Error : self dependency error for :") + invalids[i];
            if( cit != controls.end() )
            {
                delete cit->second;
                controls.erase(cit);
            }
        }
    }

    invalids.Clear();

    cit = controls.begin();
    for ( ; cit != controls.end() ; ++cit )
    {
        RheiaPackageControl* ctrl = cit->second;
        RheiaPackageDependencies* deps = ctrl->GetDependencies();
        RheiaPackageDependencyMap m_deps = deps->GetDependencies();

        RheiaPackageDependencyMap::iterator dit = m_deps.begin();
        for ( ; dit != m_deps.end() ; ++dit )
        {
            ControlMap::iterator cit2 = controls.find(dit->first);
            if( cit2 != controls.end() )
                DoubleDepsCheck( invalids , controls , cit->first , dit->first );
        }
    }

    if( invalids.GetCount() != 0 )
    {
        for( unsigned int i = 0; i < invalids.GetCount() ; i++ )
        {
            cit = controls.find(invalids[i]);
            error += wxT("Error : double dependency error for :") + invalids[i];
            if( cit != controls.end() )
            {
                delete cit->second;
                controls.erase(cit);
            }
        }
    }

    cit = controls.begin();
    for ( ; cit != controls.end() ; ++cit )
    {
        if( !AddDepstoList(ret, controls, cit->first ) )
            error += wxT("Error : dependency error for :") + cit->first;
    }

    if ( !error.IsEmpty() )
    {
        InfoWindow::Display( wxT("WARNING") ,
                             wxT("One or more packages found in the installation pending directory have not been installed, the following errors append : \n\n" ) +
                             error );
    }

    return ret;
}

bool RheiaPackageManager::CheckDependenciesFor( RheiaPackageControl* ctrl , wxArrayString& packages , wxString& error )
{
    wxString package = ctrl->GetName();
    RheiaPackageDependencies* deps = ctrl->GetDependencies();
    RheiaPackageDependencyMap m_deps = deps->GetDependencies();

    // Now for each dependency check first if the dependency name can be found
    // And check dependency version
    RheiaPackageDependencyMap::iterator dit = m_deps.begin();
    bool valid = true;

    for ( ; dit != m_deps.end() ; ++dit )
    {
        // Here the dependency can either be before in the input list
        // or already registered in the data base
        wxString depName = dit->second->GetName();
        RheiaPackageDependency* dep = dit->second;

        RheiaPackageInfo* info = RheiaPackageDBManager::Get()->FindPackageByName( depName );
        bool found = true;

        if ( info != NULL )
        {
            // Check versions, here version check are based on MAJOR and MINOR
            RheiaPackageVersion* version = info->GetControl()->GetVersion();
            long major = version->GetMajor();
            long minor = version->GetMinor();

            long dmajor = dep->GetMajor();
            long dminor = dep->GetMinor();

            if( CompareVersions( major , minor , dmajor , dminor ) == -1 )
                found = false;
        }
        else
            found = false;

        if ( !found ) // try in the precedence of this package in the list
        {
            int idx = packages.Index( dit->first );
            int i = packages.Index( package );

            if ( idx == wxNOT_FOUND || idx > i )
            {
                error += wxT("Package ") + package +
                         wxT(" depends on ") + dit->first +
                         wxT(" but this dependency cannot be satisfied ... Abording package installation \n\n") ;

                valid = false;
            }
            else
            {
                RheiaPackageScanInfoMap::iterator citd = m_packages.find(dit->first);
                if ( citd == m_packages.end() )
                {
                    error += wxT("Package ") + package +
                             wxT(" depends on ") + dit->first +
                             wxT(" but this dependency cannot be satisfied ... Abording package installation \n\n") ;

                    valid = false;
                }
                else
                {
                    // Check the dependency number
                    RheiaPackageControl* ctrld = citd->second.control;
                    if ( ctrld == NULL )
                    {
                        error += wxT("Package ") + package +
                                 wxT(" depends on ") + dit->first +
                                 wxT(" but this dependency cannot be satisfied ... Abording package installation \n\n") ;

                        valid = false;
                    }
                    else
                    {
                        RheiaPackageVersion* version = ctrld->GetVersion();

                        long major = version->GetMajor();
                        long minor = version->GetMinor();

                        long dmajor = dep->GetMajor();
                        long dminor = dep->GetMinor();

                        if ( CompareVersions( major , minor , dmajor , dminor ) == -1 )
                        {
                            error += wxT("Package ") + package +
                                     wxT(" depends on ") + dit->first +
                                     wxString::Format( wxT(" version %d.%d.%d ") , version->GetMajor() , version->GetMinor() , version->GetBuild() ) +
                                     wxT(" but the version found mismatch : version") +
                                     wxString::Format( wxT("%d.%d.%d ") , dep->GetMajor() , dep->GetMinor() , dep->GetBuild() ) +
                                     wxT(" this dependency cannot be satisfied ... Abording package installation \n\n") ;

                            valid = false;
                        }
                    }
                }
            }
        }
    }

    return valid;
}

bool RheiaPackageManager::CheckSdkVersionFor( RheiaPackageControl* ctrl , wxString& error )
{
    wxString package = ctrl->GetName();
    RheiaPackageVersion* version = ctrl->GetSDKVersion();

    long major = version->GetMajor();
    long minor = version->GetMinor();

    long dmajor = AutoVersion::MAJOR;
    long dminor = AutoVersion::MINOR;

    bool valid = true;

    if ( CompareVersions( major , minor , dmajor , dminor ) == -1 )
    {
        error += wxT("Package ") + package +
                 wxT(" depends on sdk ") +
                 wxString::Format( wxT(" version %d.%d.%d ") , version->GetMajor() , version->GetMinor() , version->GetBuild() ) +
                 wxT(" but the version found mismatch : version") +
                 wxString::Format( wxT("%d.%d.%d \n") , AutoVersion::MAJOR , AutoVersion::MINOR , AutoVersion::BUILD ) +
                 wxT("Abording package installation \n\n") ;

        valid = false;
    }

    return valid;
}

wxString RheiaPackageManager::CheckScanDependencies( wxArrayString& packages )
{
    wxString error;
    std::vector<unsigned int> removed;

    for ( int i = 0 ; i < (int) packages.GetCount() ; ++i )
    {
        RheiaPackageScanInfoMap::iterator cit = m_packages.find(packages[i]);
        if ( cit == m_packages.end() )
        {
            error += wxT("Package has been lost : ") + packages[i] + wxT("\n\n") ;
            packages.RemoveAt( i );
            --i;
        }
        else
        {
            RheiaPackageControl* ctrl = cit->second.control;
            if ( ctrl != NULL )
            {
                bool valid = true;

                valid = CheckDependenciesFor( ctrl , packages , error );

                if( !valid )
                    error += wxT("Dependencies unsatisfied : ") + packages[i] + wxT("\n\n") ;

                // Now check for sdk version registered in the control file
                if( ! CheckSdkVersionFor( ctrl , error ) )
                {
                    error += wxT("SDK version mismatch for : ") + packages[i] + wxT("\n\n") ;
                    valid = false;
                }


                if( !valid )
                {
                    packages.RemoveAt( i );
                    --i;
                }
            }
            else // This shall never append, however still diplay an error
            {
                error += wxT("Package control has been lost : ") + packages[i] + wxT("\n\n") ;
                packages.RemoveAt( i );
                --i;
            }
        }
    }

    return error;
}

void RheiaPackageManager::BuildMenu( RheiaManagedFrame* parent, wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx == wxNOT_FOUND )
        return;

    RheiaManagedFrameIdMap::iterator it = m_frameIds.find(parent);
    if( it == m_frameIds.end() )
    {
        m_frameIds[parent] = wxNewId();
        parent->PushEventHandler(this);
		parent->Connect( RheiaEVT_FRAME_CLOSING , RheiaFrameEventHandler(RheiaPackageManager::OnCloseFrame) , NULL , this );
    }

    wxMenu* mnSettings = menuBar->GetMenu( idx );
    mnSettings->Append( m_frameIds[parent] , wxT("&Installed Softwares") , wxT("Manage installed softwares") );
    Connect(m_frameIds[parent],wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPackageManager::OnManagePackages));
}

void RheiaPackageManager::ReleaseMenu( RheiaManagedFrame* parent, wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx == wxNOT_FOUND )
        return;

    RheiaManagedFrameIdMap::iterator it = m_frameIds.find(parent);
    if( it == m_frameIds.end() )
        return;

    wxMenu* mnSettings = menuBar->GetMenu( idx );
    mnSettings->Delete( m_frameIds[parent] );
    Disconnect(m_frameIds[parent],wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPackageManager::OnManagePackages));
    m_frameIds.erase(it);
    parent->RemoveEventHandler(this);
}

void RheiaPackageManager::OnManagePackages(wxCommandEvent& event)
{
    int menuId = event.GetId();
    RheiaManagedFrameIdMap::iterator it = m_frameIds.begin();

    for( ; it != m_frameIds.end() ; ++it )
        if( it->second == menuId )
        {
            RheiaPackageManagementDialog dialog(it->first);
            dialog.ShowModal();
            return;
        }

    return;
}

void RheiaPackageManager::OnCloseFrame(RheiaFrameEvent& event)
{
    ReleaseMenu( event.GetFrame() , event.GetFrame()->GetMenuBar() );
    event.Skip();
}
