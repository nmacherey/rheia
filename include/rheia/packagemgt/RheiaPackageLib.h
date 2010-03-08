/**
*   @file RheiaPackageLib.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageLib_h_
#define RheiaPackageLib_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageDependencies;
class RheiaPackageFile;
class RheiaPackageVersion;

/**
*   @class RheiaPackageLib
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageLib
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageLib();

#ifdef SWIG
	%rename(RheiaPackageLibCopy) RheiaPackageLib(const RheiaPackageLib& rhs);
#endif
    /** copy constructor */
    RheiaPackageLib(const RheiaPackageLib& rhs);

    /** default destructor */
    virtual ~RheiaPackageLib();

    /** clone method */
    virtual RheiaPackageLib* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** Get the package version */
    RheiaPackageVersion* GetVersion() {return m_version;};

    /** Set the package version */
    void SetVersion(RheiaPackageVersion* version);

    /** Get the package dependencies */
    RheiaPackageDependencies* GetDependencies() {return m_dependencies;};

    /** Set the package dependencies */
    void SetDependencies(RheiaPackageDependencies* dependencies);

    /** Get the package file */
    RheiaPackageFile* GetFile() {return m_file;};

    /** Set the package file */
    void SetFile(RheiaPackageFile* file);

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageLib info from the given xmlNode
    *   @return false if any Lib required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageLib info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :

    RheiaPackageVersion* m_version;
    RheiaPackageDependencies* m_dependencies;
    RheiaPackageFile* m_file;
};

#endif




