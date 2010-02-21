/**
*   @file RheiaPackageInstallInfo.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageInstallInfo_h_
#define RheiaPackageInstallInfo_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageFiles;
class RheiaPackageLibs;

/**
*   @class RheiaPackageInstallInfo
*
*   @brief This is the basic class for handling package version InstallInformation in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageInstallInfo
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageInstallInfo();

    /** copy constructor */
    RheiaPackageInstallInfo(const RheiaPackageInstallInfo& rhs);

    /** default destructor */
    virtual ~RheiaPackageInstallInfo();

    /** clone method */
    virtual RheiaPackageInstallInfo* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** Get the files */
    RheiaPackageFiles* GetFiles() {return m_files;};

    /** Set the files */
    void SetFiles(RheiaPackageFiles* files);

    /** Get the libs */
    RheiaPackageLibs* GetLibs() {return m_libs;};

    /** Set the libs */
    void SetLibs(RheiaPackageLibs* libs);

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageInstallInfo InstallInfo from the given xmlNode
    *   @return false if any InstallInfo required InstallInformation is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageInstallInfo InstallInfo to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :

    RheiaPackageFiles* m_files;
    RheiaPackageLibs* m_libs;
};

#endif




