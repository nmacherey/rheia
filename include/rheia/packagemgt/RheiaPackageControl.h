/**
*   @file RheiaPackageControl.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageControl_h_
#define RheiaPackageControl_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageDependencies;
class RheiaPackageDependency;
class RheiaPackageDescription;
class RheiaPackageMaintainer;
class RheiaPackageVersion;

/**
*   @class RheiaPackageControl
*
*   @brief This is the basic class for handling package Control files in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageControl
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageControl();

    /** copy constructor */
    RheiaPackageControl(const RheiaPackageControl& rhs);

    /** default destructor */
    virtual ~RheiaPackageControl();

    /** clone method */
    virtual RheiaPackageControl* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the package's name */
    const wxString& GetName() {return m_name;};

    /** set the package's name */
    void SetName(const wxString& name) {m_name = name;};

    /** get the package's title */
    const wxString& GetTitle() {return m_title;};

    /** set the package's title */
    void SetTitle(const wxString& title) {m_title = title;};

    /** get the package's archi */
    const wxString& GetArchitecture() {return m_archi;};

    /** set the package's title */
    void SetArchitecture(const wxString& archi) {m_archi = archi;};

    /** get the package's os */
    const wxString& GetOperatingSystem() {return m_os;};

    /** set the package's os */
    void SetOperatingSystem(const wxString& os) {m_os = os;};

    /** get the package's category */
    const wxString& GetCategory() {return m_category;};

    /** set the package's category */
    void SetCategory(const wxString& category) {m_category = category;};

    /** Get the maintainer */
    RheiaPackageMaintainer* GetMaintainer() {return m_maintainer;};

    /** Set the maintainer */
    void SetMaintainer(RheiaPackageMaintainer* maintainer);

    /** Get the package version */
    RheiaPackageVersion* GetVersion() {return m_version;};

    /** Set the package version */
    void SetVersion(RheiaPackageVersion* version);

    /** Get the package SDK version */
    RheiaPackageVersion* GetSDKVersion() {return m_sdkversion;};

    /** Set the package SDK version */
    void SetSDKVersion(RheiaPackageVersion* sdkversion);

    /** Get the package dependencies */
    RheiaPackageDependencies* GetDependencies() {return m_dependencies;};

    /** Set the package dependencies */
    void SetDependencies(RheiaPackageDependencies* dependencies);

    /** Get the package description */
    RheiaPackageDescription* GetDescription() {return m_description;};

    /** Set the package description */
    void SetDescription(RheiaPackageDescription* description);

    /** Get the package shared library list */
    wxArrayString GetSharedLibraries() {return m_shlibs;};

    /** Set the package shared library list */
    void SetSharedLibraries( const wxArrayString& shlibs ) { m_shlibs = shlibs;};

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageControl Control from the given xmlNode
    *   @return false if any Control required Controlrmation is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageControl Control to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :

    wxString m_name;
    wxString m_title;
    wxString m_archi;
    wxString m_os;
    wxString m_category;
    RheiaPackageMaintainer* m_maintainer;
    RheiaPackageVersion* m_version;
    RheiaPackageVersion* m_sdkversion;
    RheiaPackageDependencies* m_dependencies;
    RheiaPackageDescription* m_description;
    wxArrayString m_shlibs;
};

#endif




