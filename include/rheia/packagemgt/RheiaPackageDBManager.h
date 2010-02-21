/**
*   @file RheiaPackageDBManager.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/

#ifndef RheiaPackageDBManager_h_
#define RheiaPackageDBManager_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>

#include <set>
#include <map>

class RheiaPackageInfo;
class RheiaPackageInstallInfo;
class RheiaPackageManagedFile;
class RheiaPackageManagedFiles;
class RheiaPackageFile;
class RheiaPackageFiles;
class RheiaPackageDependencies;
class RheiaPackageDependency;

/** define a map of RheiaPackageInfo in order to manage it in the manager */
typedef std::map< wxString , RheiaPackageInfo* > RheiaPackageInfoMap;

/** define an array of RheiaPackageManagedFile's */
typedef std::vector< RheiaPackageManagedFile* > RheiaPackageMangedFileArray;

/* libxml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaPackageDBManager
*
*   @brief This is the basic class for managing installed packages in Rheia
*
*   RheiaPackageDBManager is writing its information in a file called packages.xml which corresponds
*   to the local packages data base for packages.
*
*   @note Please take care when you are installing Rheia in different systems as the global packages
*   database has to be in read/write access mode for the user. So do not forget to set its access rights
*   when installing Rheia.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageDBManager : public Mgr<RheiaPackageDBManager>
{
    /** give Mrg<RheiaConfigurationManager> our private members access */
    friend class Mgr<RheiaPackageDBManager>;

    /** give RheiaManager our private memebers access */
    friend class RheiaManager;

public :
    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/

    /**
    *   Find a package by its package name
    *   @param name package name
    *   @return null if the package has not been found
    */
    RheiaPackageInfo* FindPackageByName(const wxString& name);

    /**
    *   Find a package by its package title
    *   @param title package title
    *   @return null if the package has not been found
    */
    RheiaPackageInfo* FindPackageByTitle(const wxString& title);

    /**
    *   Specify if a package exists by its package name
    *   @param name package name
    *   @return false if the package has not been found
    */
    bool Exists(const wxString& name );

    /**
    *   Specify if a package exists by its package address
    *   @param info RheiaPackageInfo object to check the existence for
    *   @return false if the package has not been found
    */
    bool Exists( RheiaPackageInfo* info );

    /**
    *   Specify if a package exists by its package title
    *   @param title package title
    *   @return false if the package has not been found
    */
    bool ExistsByTitle(const wxString& title );

    /**
    *   Register a new package in the data base
    *   @param info RheiaPackageInfo object to be registered in the data base
    *   @return false if the package has not been registered in the data base
    */
    bool RegisterPackage( RheiaPackageInfo* info );

    /**
    *   Unregister a package from the data base
    *   @param info RheiaPackageInfo object to be removed from the data base
    *   @return false if the package has not been removed from the data base
    */
    bool UnregisterPackage( RheiaPackageInfo* info );

    /**
    *   Unregister a package from the data base
    *   @param name package name to be removed from the data base
    *   @return false if the package has not been removed from the data base
    */
    bool UnregisterPackage( const wxString& name );

    /** Check if the given node is the related package node */
    bool IsPackageNode( xmlNode* parent , const wxString& name );

    /**
    *   Unregister a package from the data base
    *   @param title package title to be removed from the data base
    *   @return false if the package has not been removed from the data base
    */
    bool UnregisterPackageByTitle( const wxString& title );

    /**
    *   Register a package file dependency for a given package
    *   @param name package name to register the file for
    *   @param file RheiaPackageManagedFile to be registered for the given package
    *   @return false if the file has not been registered
    */
    bool RegisterFileForPackage( const wxString& name , RheiaPackageManagedFile* file );

    /**
    *   Register a package files dependency for a given package
    *   @param name package name to register the file for
    *   @param files RheiaPackageManagedFiles to be registered for the given package
    *   @return false if the files have not been registered
    */
    bool RegisterFilesForPackage( const wxString& name , RheiaPackageManagedFiles* files );

    /**
    *   Unregister a package file dependency for a given package
    *   @param name package name to register the file for
    *   @param file file name that shall be unregistered
    *   @return false if at least one of the file has not been removed
    */
    bool UnregisterFileForPackage( const wxString& name , const wxString& file );

    /** Check if the file is in the given node */
    bool FileIsInNode( xmlNode* parent , const wxString& name );

    /** Get the file node from the given node */
    xmlNode* GetFileNode( xmlNode* parent , const wxString& name );

    /**
    *   Register a package files dependency for a given package
    *   @param name package name to register the file for
    *   @param files array of files that qhall be unregistered from the data base for the given package
    *   @return false if at least one of the files have not been removed
    */
    bool UnregisterFilesForPackage( const wxString& name , const wxArrayString& files );

     /**
    *   Register a package dependency for a given package
    *   @param name package name to register the dependency for
    *   @param dependency RheiaPackageDependecy to be registered for the given package
    *   @return false if the dependency has not been registered
    */
    bool RegisterDependecyForPackage( const wxString& name , RheiaPackageDependency* dependency );

    /**
    *   Register a package dependencies for a given package
    *   @param name package name to register the dependencies for
    *   @param dependencies RheiaPackageDependecies to be registered for the given package
    *   @return false if the dependencies have not been registered
    */
    bool RegisterDependeciesForPackage( const wxString& name , RheiaPackageDependencies* dependencies );

    /**
    *   Unregister a package dependency for a given package
    *   @param name package name to register the dependency for
    *   @param dependency dependency name that shall be unregistered
    *   @return false if at least one of the dependency has not been removed
    */
    bool UnregisterDependencyForPackage( const wxString& name , const wxString& dependency );

    /**
    *   Register a package dependencies for a given package
    *   @param name package name to register the dependencies for
    *   @param dependencies array of dependencies that shall be unregistered from the data base for the given package
    *   @return false if at least one of the dependencies have not been removed
    */
    bool UnregisterDependenciesForPackage( const wxString& name , const wxArrayString& dependencies );

    /** Get the full package list by names */
    wxArrayString GetPackageList();

    /** Get the full package list by packages titles */
    wxArrayString GetPackageListByTitle();

    /** List all packages dependent from the given one */
    wxArrayString ListDependentPackagesFor( const wxString& name );

    /** Get an ordered plugin list for loading */
    RheiaPackageMangedFileArray GetLibsLoadingList();

    /** Get an ordered plugin list for loading */
    RheiaPackageMangedFileArray GetPluginsLoadingList();

    /** Get the ordered loading list for both libraries and plugins */
    RheiaPackageMangedFileArray GetLoadingList();

    /** Get the packages map */
    const RheiaPackageInfoMap& GetPackages() {return m_packages;};

    /** Reload the package data base */
    bool Reload();

    /** Save the package Data base */
    bool Save();

private :

    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default builder */
    RheiaPackageDBManager();

    /** default destrcutor */
    ~RheiaPackageDBManager();

    /**************************************************************************************
    *   METHODS
    **************************************************************************************/
    /** recursive method for determining package dependency list */
    void AddDependencyFilesFor( RheiaPackageMangedFileArray& list , const wxString& package , const wxString& type );

    /** recursive method for determining package dependency list */
    void AddDependencyFilesFor( RheiaPackageMangedFileArray& list , const wxString& package );

private :

    RheiaPackageInfoMap m_packages;
    xmlDoc* m_doc;
    xmlNode* m_root;
    xmlNode* m_proot;
};

#endif
