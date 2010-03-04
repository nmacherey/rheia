/**
*   @file RheiaPackageDBManager.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/

#include <RheiaPackageDBManager.h>
#include <RheiaPackageInfo.h>
#include <RheiaPackageInstallInfo.h>
#include <RheiaPackageManagedFile.h>
#include <RheiaPackageManagedFiles.h>
#include <RheiaPackageFile.h>
#include <RheiaPackageFiles.h>
#include <RheiaPackageDependencies.h>
#include <RheiaPackageDependency.h>
#include <RheiaPackageControl.h>
#include <RheiaStandardPaths.h>
#include <RheiaPlatform.h>
#include <RheiaAppGlobals.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

/*! declare global instance for the RheiaPackageDBManager */
template<> RheiaPackageDBManager* Mgr<RheiaPackageDBManager>::instance = 0;
/*! declare global isShutdown for the RheiaPackageDBManager */
template<> bool Mgr<RheiaPackageDBManager>::isShutdown = false;



RheiaPackageDBManager::RheiaPackageDBManager():
    m_doc(NULL),
    m_root(NULL),
    m_proot(NULL)
{
    Reload();
}

RheiaPackageDBManager::~RheiaPackageDBManager()
{
    Save();

    RheiaPackageInfoMap::iterator pit = m_packages.begin();

    for( ; pit != m_packages.end() ; ++pit )
        if( pit->second != NULL )
            delete pit->second;

    if( m_doc != NULL )
        xmlFreeDoc( m_doc );
}

RheiaPackageInfo* RheiaPackageDBManager::FindPackageByName(const wxString& name)
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return NULL;

    return pit->second;
}

RheiaPackageInfo* RheiaPackageDBManager::FindPackageByTitle(const wxString& title)
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();

    for( ; pit != m_packages.end() ; ++pit )
        if( pit->second != NULL && pit->second->GetControl()->GetTitle().IsSameAs( title ) )
            return pit->second;

    return NULL;
}

bool RheiaPackageDBManager::Exists(const wxString& name )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    return true;
}

bool RheiaPackageDBManager::Exists( RheiaPackageInfo* info )
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();

    for( ; pit != m_packages.end() ; ++pit )
        if( pit->second != NULL && pit->second == info )
            return true;

    return false;
}

bool RheiaPackageDBManager::ExistsByTitle(const wxString& title )
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();

    for( ; pit != m_packages.end() ; ++pit )
        if( pit->second != NULL && pit->second->GetControl()->GetTitle().IsSameAs( title ) )
            return true;

    return false;
}

bool RheiaPackageDBManager::RegisterPackage( RheiaPackageInfo* info )
{
    if( Exists( info->GetControl()->GetName() ) )
        return false;

    if( m_proot == NULL )
        return false;

    /*** register the package in the containing map */
    m_packages[info->GetControl()->GetName()] = info;

    /*** write the package to the document root */
    xmlNode* child = xmlNewNode( NULL , (const xmlChar*) "PackageInfo" );
    info->DoWriteToNode( child );
    xmlAddChild( m_proot , child );

    /*** save the document */
    Save();

    return true;
}

bool RheiaPackageDBManager::UnregisterPackage( RheiaPackageInfo* info )
{
    wxString name = info->GetControl()->GetName();

    if( !Exists( name ) )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    m_packages.erase(pit);
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                xmlReplaceNode( child , NULL );
                Save();
                delete info;
                return true;
            }
        }
        child = child->next;
    }

    delete info;
    return true;
}

bool RheiaPackageDBManager::UnregisterPackage( const wxString& name )
{
    if( !Exists( name ) )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    RheiaPackageInfo* info = pit->second;
    m_packages.erase(pit);
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                xmlReplaceNode( child , NULL );
                Save();
                delete info;
                return true;
            }
        }
        child = child->next;
    }

    delete info;
    return true;
}

bool RheiaPackageDBManager::UnregisterPackageByTitle( const wxString& title )
{
    if( !ExistsByTitle( title ) )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = FindPackageByTitle(title);

    if( info == NULL )
        return false;

    wxString name = info->GetControl()->GetName();
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    m_packages.erase(pit);
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                xmlReplaceNode( child , NULL );
                Save();
                delete info;
                return true;
            }
        }
        child = child->next;
    }

    delete info;
    return true;
}

bool RheiaPackageDBManager::IsPackageNode( xmlNode* parent , const wxString& name )
{
    xmlNode* sub = parent->children;

    while( sub != NULL )
    {
        wxString sname = RheiaC2U( (const char*) sub->name );

        if( sname.IsSameAs( wxT("PackageControl") ) )
        {
            xmlNode* n = sub->children;

            while( n != NULL )
            {
                wxString nname = RheiaC2U( (const char*) n->name );

                if( nname.IsSameAs( wxT("name") ) )
                {
                    xmlChar* content = xmlNodeGetContent( n );
                    wxString str = RheiaC2U( (const char*) content );
                    xmlFree(content);

                    if( str.IsSameAs( name ) )
                        return true;
                }

                n = n->next;
            }
        }
        sub = sub->next;
    }

    return false;
}

bool RheiaPackageDBManager::RegisterFileForPackage( const wxString& name , RheiaPackageManagedFile* file )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageManagedFiles* files = info->GetManagedFiles();
                files->Add( file->GetName() , file );
                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}


bool RheiaPackageDBManager::RegisterFilesForPackage( const wxString& name , RheiaPackageManagedFiles* files )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageManagedFiles* pfiles = info->GetManagedFiles();

                RheiaPackageManagedFileMap m_files = files->GetManagedFiles();
                RheiaPackageManagedFileMap::iterator fit = m_files.begin();

                for( ; fit != m_files.end() ; ++fit )
                    pfiles->Add( fit->first , fit->second->Clone() );

                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

bool RheiaPackageDBManager::UnregisterFileForPackage( const wxString& name , const wxString& file )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageManagedFiles* pfiles = info->GetManagedFiles();
                pfiles->Remove( file );
                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

bool RheiaPackageDBManager::UnregisterFilesForPackage( const wxString& name , const wxArrayString& files )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageManagedFiles* pfiles = info->GetManagedFiles();

                for( unsigned int i = 0; i < files.GetCount() ; ++i )
                    pfiles->Remove( files[i] );

                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

bool RheiaPackageDBManager::FileIsInNode( xmlNode* parent , const wxString& name )
{
    xmlNode* sub = parent->children;

    while( sub != NULL )
    {
        wxString sname = RheiaC2U( (const char*) sub->name );

        if( sname.IsSameAs( wxT("Files") ) )
        {
            xmlNode* n = sub->children;

            while( n != NULL )
            {
                wxString nname = RheiaC2U( (const char*) n->name );

                if( nname.IsSameAs( wxT("File") ) )
                {
                    xmlNode* node = n->children;
                    while( node != NULL )
                    {
                        wxString nodeName = RheiaC2U( (const char*) node->name );
                        if( nodeName.IsSameAs( wxT("name") ) )
                        {
                            xmlChar* content = xmlNodeGetContent( node );
                            wxString str = RheiaC2U( (const char*) content );
                            xmlFree( content );

                            if( str.IsSameAs( name ) )
                                return true;
                        }
                        node = node->next;
                    }
                }
                n = n->next;
            }
        }
        sub = sub->next;
    }

    return false;
}

xmlNode* RheiaPackageDBManager::GetFileNode( xmlNode* parent , const wxString& name )
{
    xmlNode* sub = parent->children;

    while( sub != NULL )
    {
        wxString sname = RheiaC2U( (const char*) sub->name );

        if( sname.IsSameAs( wxT("Files") ) )
        {
            xmlNode* n = sub->children;

            while( n != NULL )
            {
                wxString nname = RheiaC2U( (const char*) n->name );

                if( nname.IsSameAs( wxT("File") ) )
                {
                    xmlNode* node = n->children;
                    while( node != NULL )
                    {
                        wxString nodeName = RheiaC2U( (const char*) node->name );
                        if( nodeName.IsSameAs( wxT("name") ) )
                        {
                            xmlChar* content = xmlNodeGetContent( node );
                            wxString str = RheiaC2U( (const char*) content );
                            xmlFree( content );

                            if( str.IsSameAs( name ) )
                                return node;
                        }
                        node = node->next;
                    }
                }
                n = n->next;
            }
        }
        sub = sub->next;
    }
    return NULL;
}

bool RheiaPackageDBManager::RegisterDependecyForPackage( const wxString& name , RheiaPackageDependency* dependency )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageControl* pcontrol = info->GetControl();
                RheiaPackageDependencies* pdeps = pcontrol->GetDependencies();
                pdeps->Add( dependency->GetName() , dependency );
                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

bool RheiaPackageDBManager::RegisterDependeciesForPackage( const wxString& name , RheiaPackageDependencies* dependencies )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageControl* pcontrol = info->GetControl();
                RheiaPackageDependencies* pdeps = pcontrol->GetDependencies();

                RheiaPackageDependencyMap m_deps = dependencies->GetDependencies();
                RheiaPackageDependencyMap::iterator dit = m_deps.begin();

                for( ; dit != m_deps.end() ; dit++ )
                    pdeps->Add( dit->first , dit->second->Clone() );

                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

bool RheiaPackageDBManager::UnregisterDependencyForPackage( const wxString& name , const wxString& dependency )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageControl* pcontrol = info->GetControl();
                RheiaPackageDependencies* pdeps = pcontrol->GetDependencies();
                pdeps->Remove( dependency );
                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

bool RheiaPackageDBManager::UnregisterDependenciesForPackage( const wxString& name , const wxArrayString& dependencies )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(name);

    if( pit == m_packages.end() )
        return false;

    if( m_proot == NULL )
        return false;

    RheiaPackageInfo* info = pit->second;
    xmlNode *child = m_proot->children;

    while( child != NULL)
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            if( IsPackageNode( child , name ) )
            {
                RheiaPackageControl* pcontrol = info->GetControl();
                RheiaPackageDependencies* pdeps = pcontrol->GetDependencies();

                for( unsigned int i = 0; i < dependencies.GetCount() ; ++i )
                    pdeps->Remove( dependencies[i] );

                info->DoWriteToNode( child );
                Save();
                return true;
            }
        }
        child = child->next;
    }
    return false;
}

wxArrayString RheiaPackageDBManager::GetPackageList()
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();
    wxArrayString ret;

    for( ; pit != m_packages.end() ; ++pit )
        ret.Add( pit->first );

    return ret;
}

wxArrayString RheiaPackageDBManager::GetPackageListByTitle()
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();
    wxArrayString ret;

    for( ; pit != m_packages.end() ; ++pit )
        ret.Add( pit->second->GetControl()->GetTitle() );

    return ret;
}

wxArrayString RheiaPackageDBManager::ListDependentPackagesFor( const wxString& name )
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();
    wxArrayString ret;

    for( ; pit != m_packages.end() ; ++pit )
    {
        RheiaPackageControl* ctrl = pit->second->GetControl();
        RheiaPackageDependencies* deps = ctrl->GetDependencies();
        RheiaPackageDependencyMap m_deps = deps->GetDependencies();

        RheiaPackageDependencyMap::iterator it = m_deps.find( name );

        if( it != m_deps.end() )
            ret.Add( pit->first );
    }

    return ret;
}

bool RheiaPackageDBManager::Reload()
{
    Save();

    RheiaPackageInfoMap::iterator pit = m_packages.begin();

    for( ; pit != m_packages.end() ; ++pit )
        if( pit->second != NULL )
            delete pit->second;

    if( m_doc != NULL )
        xmlFreeDoc( m_doc );

    m_doc = NULL;
    m_root = NULL;
    m_proot = NULL;

    wxString path = RheiaStandardPaths::DataDirectory(true) + wxT("/packages.xml");

    if( wxFileExists(path) )
        m_doc = xmlParseFile( rcU2C( path ) );

    if( m_doc == NULL )
    {
        m_doc = xmlNewDoc( (const xmlChar*) XML_DEFAULT_VERSION );
        m_root = xmlNewNode( NULL , (const xmlChar*) "InstalledPackages" );
        m_proot = xmlNewNode( NULL , (const xmlChar*) "Packages" );
        xmlAddChild( m_root , m_proot );
        xmlDocSetRootElement( m_doc , m_root );
        return true;
    }

    m_root = xmlDocGetRootElement( m_doc );

    m_proot = m_root->children;
    while( m_proot != NULL )
    {
        wxString rname = RheiaC2U( (const char*) m_proot->name );
        if( rname.IsSameAs( wxT("Packages") ) )
        {
            break;
        }
        m_proot = m_proot->next;
    }

    if( m_proot == NULL )
    {
        m_proot = xmlNewNode( NULL , (const xmlChar*) "Packages" );
        xmlAddChild( m_root , m_proot );
        return true;
    }

    /*** else a m_proot node exists so we will try to load all packages info from the
    *   existing packages nodes */
    xmlNode* child = m_proot->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageInfo") ) )
        {
            RheiaPackageInfo* info = new RheiaPackageInfo();

            if( info->DoReadFromNode( child ) )
                m_packages[info->GetControl()->GetName()] = info;
            else
            {
                delete info;
            }
        }
        child = child->next;
    }
    return true;
}

bool RheiaPackageDBManager::Save()
{
    if( m_doc == NULL || m_root == NULL )
        return false;

    wxDateTime date = wxDateTime::Now();
    wxString sDate = date.Format( wxT("%c") , wxDateTime::CET ) ;

    wxString info;

#ifndef __GNUC__

    info.Printf(_T( "Rheia packages data base info:\n\t application build_date:\t%s, %s \n\t data base saving date : \t%s" ), wxT(__DATE__), wxT(__TIME__), sDate);
#else
    info.Printf(_T( "Rheia packages data base info:\n"
                    "\t application build_date:\t%s, %s\n"
                    "\t data base saving date:\t%s\n"
                    "\t gcc_version:\t%d.%d.%d "), wxT(__DATE__), wxT(__TIME__),sDate.c_str(),
                __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

    if (platform::windows)
        info.append(_T("\n\t Windows "));
    if (platform::linux)
        info.append(_T("\n\t Linux "));
    if (platform::macosx)
        info.append(_T("\n\t Mac OS X "));
    if (platform::unix)
        info.append(_T("\n\t Unix "));

    info.append(platform::unicode ? _T("Unicode ") : _T("ANSI "));

    xmlNode *temp = xmlNewDocComment( m_doc , rxU2C( info ) );
    xmlNode *child = m_root->children;
    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );
        if ( ChildName.IsSameAs( wxT("comment") ) )
            xmlReplaceNode( child , NULL );
        child = child->next;
    }

    xmlAddPrevSibling(m_root->children,temp);

    wxString path = RheiaStandardPaths::DataDirectory(true) + wxT("/packages.xml");
    int ret = xmlSaveFormatFileEnc( rcU2C( path ) , m_doc , "UTF-8" , 1 );

    return (ret != -1);
}

void RheiaPackageDBManager::AddDependencyFilesFor( RheiaPackageMangedFileArray& list , const wxString& package , const wxString& type )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(package);

    if( pit == m_packages.end() )
        return;

    RheiaPackageInfo* info = (pit->second);
    RheiaPackageControl* ctrl = info->GetControl();
    RheiaPackageManagedFiles *files = info->GetManagedFiles();
    RheiaPackageManagedFileMap m_files = files->GetManagedFiles();
    RheiaPackageDependencies* deps = ctrl->GetDependencies();
    RheiaPackageDependencyMap m_deps = deps->GetDependencies();

    if( m_deps.size() > 0 )
    {
        RheiaPackageDependencyMap::iterator dit = m_deps.begin();
        for( ; dit != m_deps.end() ; ++dit )
            AddDependencyFilesFor( list , dit->first , type );
    }

    RheiaPackageManagedFileMap::iterator fit = m_files.begin();
    for( ; fit != m_files.end() ; ++fit )
    {
        RheiaPackageManagedFile* file = fit->second;
        wxString type = file->GetType();

        if( type.IsSameAs( type ) )
        {
            // check if the file is not in the list
            RheiaPackageMangedFileArray::iterator lit = list.begin();
            bool add = true;
            for( ; lit != list.end() ; ++lit )
                if( (*lit)->GetName().IsSameAs( fit->first ) )
                {
                    add = false;
                    break;
                }

            if( add )
                list.push_back( fit->second );
        }
    }
}

void RheiaPackageDBManager::AddDependencyFilesFor( RheiaPackageMangedFileArray& list , const wxString& package )
{
    RheiaPackageInfoMap::iterator pit = m_packages.find(package);

    if( pit == m_packages.end() )
        return;

    RheiaPackageInfo* info = (pit->second);
    RheiaPackageControl* ctrl = info->GetControl();
    RheiaPackageManagedFiles *files = info->GetManagedFiles();
    RheiaPackageManagedFileMap m_files = files->GetManagedFiles();
    RheiaPackageDependencies* deps = ctrl->GetDependencies();
    RheiaPackageDependencyMap m_deps = deps->GetDependencies();
    wxArrayString shared = ctrl->GetSharedLibraries();

    if( m_deps.size() > 0 )
    {
        RheiaPackageDependencyMap::iterator dit = m_deps.begin();
        for( ; dit != m_deps.end() ; ++dit )
            AddDependencyFilesFor( list , dit->first );
    }


    for( unsigned int i = 0; i < shared.GetCount() ; ++i )
    {
        /** first make sure the name is a proper name */
        wxString filename = shared[i];
        wxString version;
        if (filename.Contains(wxT('-')))
        {
            version = filename.AfterFirst(wxT('-'));
            filename = filename.BeforeFirst(wxT('-'));
        }

        if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
            filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

        RheiaPackageManagedFileMap::iterator fit = m_files.find(filename);
        if( fit != m_files.end() )
        {
            // check if the file is not in the list
            RheiaPackageMangedFileArray::iterator lit = list.begin();
            bool add = true;
            for( ; lit != list.end() ; ++lit )
                if( (*lit)->GetName().IsSameAs( fit->first ) )
                {
                    add = false;
                    break;
                }

            if( add )
                list.push_back( fit->second );
        }
    }
}

RheiaPackageMangedFileArray RheiaPackageDBManager::GetPluginsLoadingList()
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();
    RheiaPackageMangedFileArray m_list;

    for( ; pit != m_packages.end() ; ++pit )
        AddDependencyFilesFor( m_list , pit->first , wxT("plugin") );

    return m_list;
}

RheiaPackageMangedFileArray RheiaPackageDBManager::GetLibsLoadingList()
{
    RheiaPackageInfoMap::iterator pit = m_packages.begin();
    RheiaPackageMangedFileArray m_list;

    for( ; pit != m_packages.end() ; ++pit )
        AddDependencyFilesFor( m_list , pit->first , wxT("lib") );

    return m_list;
}

RheiaPackageMangedFileArray RheiaPackageDBManager::GetLoadingList()
{
    RheiaPackageMangedFileArray m_list;
    RheiaPackageInfoMap::iterator pit = m_packages.begin();

    for( ; pit != m_packages.end() ; ++pit )
        AddDependencyFilesFor( m_list , pit->first );

    return m_list;
}
