/**
*   @file RheiaPackageManager.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 23-November-2009
*/
#ifndef RheiaPackageManager_h_
#define RheiaPackageManager_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaEventFrame.h>

#include <map>

/* Rheia imports */
class RheiaPackageInfo;
class RheiaPackageControl;
class RheiaPackageManagedFiles;
class wxMenuBar;

/** define an information for packages scan */
struct RheiaPackageScanInfo
{
    RheiaPackageScanInfo():control(NULL){};

#ifdef SWIG
	~RheiaPackageScanInfo() {};
	%rename(RheiaPackageScanInfoCopy) RheiaPackageScanInfo( const RheiaPackageScanInfo& rhs );
#endif
    RheiaPackageScanInfo( const RheiaPackageScanInfo& rhs ):
        name(rhs.name),
        fullname(rhs.fullname),
        path(rhs.path),
        control(rhs.control)
    {}

    wxString name;
    wxString fullname;
    wxString path;
    RheiaPackageControl* control;
};

/** define a map of scanned packages */
typedef std::map< wxString , RheiaPackageScanInfo > RheiaPackageScanInfoMap;

/**
*   @class RheiaPackageManager
*
*   @brief Main manager class for registering and managing RheiaPackages.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 23-November-2009
*/
class PMGT_DLLEXPORT RheiaPackageManager : public wxEvtHandler, public Mgr<RheiaPackageManager>
{
    /** give RheiaManager our private members access */
    friend class RheiaManager;

    /** give Mgr our private members access */
    friend class Mgr<RheiaPackageManager>;

public :

    /**************************************************************************************
    *   MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   This method will scan all packages files available in the given path.
    *   A rheia package is a zip file with the rpack extension or the one defined
    *   RheiaAppGlobals.h hearder file.
    *   This will simply list all files in the given direxctory and try to load any
    *   packages founded.
    *   This method will return the total number of packages founded in the directory
    *   and register all packages names in the RheiaPackageInfoList.
    *
    *   @param path directory to scan packages in
    *   @return the total number of packages registered in this managers
    */
    int ScanForPackages( const wxString& path );

    /** Add the given package to the package list */
    bool AddPackageToList( const wxString& filename );

    void InstallPendingPackages( bool askfor = true );

    bool InstallPackages( bool askfor = true , bool globaly = false , bool silent = true , bool confirm = false );

    /** This method is used to build the menu for this manager in RheiaManagedFrame's menubar */
	void BuildMenu( RheiaManagedFrame* parent, wxMenuBar* menuBar );

	/** This method is used to desstroy the menu for this manager from RheiaManagedFrame's menubar */
	void ReleaseMenu( RheiaManagedFrame* parent , wxMenuBar* menuBar );

	/** Callback used when the user want to manage environment variables */
	void OnManagePackages(wxCommandEvent& event);

	/** Callback used when the user want to manage environment variables */
	void OnCloseFrame(RheiaFrameEvent& event);

    /**
    *   Extract a file from the package zip file and save it into the
    *   given destination file.
    *   The aim for this function is to extract from the package .rpack file
    *   the control.xml file and to save it into a temp directory before reading
    *   it.
    *   If the file extraction failed, this commonly means that the package does not
    *   provide the application with the first level control file. So this means that
    *   you miss some step in the package build and you should check what you've done !
    *
    *   @param package this is the package file name with the full extension
    *   @param source is the name of the file in the rpack file to read
    *   @param destination is the full file path in which the extraction process shall store the readed information
    *   @return true if the extraction succeed, else return false
    */
    bool ExtractFile( const wxString& package,
		const wxString& source,
		const wxString& destination );

    bool ExtractFiles( const wxString& package,
		const wxString& dir,
		const wxString& ext,
		const wxString& destination,
		wxString& error,
		wxArrayString& installed,
		RheiaPackageManagedFiles* files,
		const wxString& type );

    /**
    *   This method is used to read the control.xml file associated to the package
    *   The aim is first to extract the package information without having to load
    *   all its content.
    *   If the control.xml integrity is not good, this method will return a NULL
    *   package control. This usually means that you forgot to write an information
    *   in the package control.xml and you shall have a look to PackageControl.xsd
    *   file in order to validate it.
    *
    *   @param file file path to read
    *   @return NULL if the file is not in the proper format
    */
    RheiaPackageControl* ReadControlFileFor( const wxString& file );

    /**
    *   This method is used to install a package in Rheia, the aim is first
    *   to extract the control file, then to read the file and extract the RheiaPackageControl
    *   object associated to it. The next step is to determine if all the package dependencies are
    *   satisfied or not. Finally the package files will be installed into respective directories.
    *   You can either choose to install the package silently or to show a progress dialog during
    *   the installation process.
    *
    *   @param package package name to install
    *   @param path package path, where the package is located
    *   @param silent set to false if you want to show the installation progress
    *   @return false if the package has not been registered in the data base
    */
    bool InstallPackage( const wxString& name ,
        const wxString& fullname ,
        const wxString& path ,
        bool globaly = false,
        bool silent = false ,
        bool confirm = true );

    /**
    *   Uninstall a package and optionnally remove all package which depend on the
    *   removed one.
    */
    bool PurgePackage( const wxString& name ,
        bool silent = false,
        bool confirm = true,
        bool recursive = true );

    /**
    *   This method is used to order the package scanned list by dependencies, the first
    *   package returned will be the one to install first....
    *   This method will not identify missing dependencies, the only check performed here
    *   is for inter-dependencies, what means that a package foo1 depends en foo2 and the
    *   package foo2 depends on foo1 which must never append !!!!!!!
    *
    *   @return the package installation ordered list.
    */
    wxArrayString OrderScanByDependencies( );

    /**
    *   This method will check for all unsatisfied dependencies for the given
    *   package list. For a package in the list the dependency is either before in the list
    *   or already registered in the package data base.
    */
    wxString CheckScanDependencies( wxArrayString& packages );

    /**
    *   Check the dependencies for the given package control
    */
    bool CheckDependenciesFor( RheiaPackageControl* ctrl , wxArrayString& packages , wxString& error );

    /**
    *   Check the sdk version with which the package has been built
    */
    bool CheckSdkVersionFor( RheiaPackageControl* ctrl , wxString& error );


    void Clear();

private :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /**
    *   Default constructor.
    *   As many other Manager in Rheia, you cannot build directly this class,
    *   use RheiaPackageManager::Get() to get the global instance of this class.
    *   Unless if you are a Rheia Developer you shall never have to deal with this
    *   class as it is a core function of Rheia. However if you manage to develop
    *   a plugin in order to accurate package management in Rheia this class shall
    *   provide you with all the methods you need.
    */
    RheiaPackageManager();

    /**
    *   Default destrcutor.
    *   You cannot call this destrcutor directly in your code, more over this may
    *   result in unexpected behaviour while the application is running. RheiaManager
    *   Is responsible for destroying this class via RheiaPackageManager::Free();
    */
    ~RheiaPackageManager();

private :
    RheiaPackageScanInfoMap m_packages;
    RheiaManagedFrameIdMap m_frameIds;
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#endif
