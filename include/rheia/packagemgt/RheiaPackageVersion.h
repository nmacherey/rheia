
/**
*   @file RheiaPackageVersion.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageVersion_h_
#define RheiaPackageVersion_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaPackageVersion
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageVersion
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageVersion();

#ifdef SWIG
	%rename(RheiaPackageVersionCopy) RheiaPackageVersion(const RheiaPackageVersion& rhs);
#endif
    /** copy constructor */
    RheiaPackageVersion(const RheiaPackageVersion& rhs);

    /** default destructor */
    virtual ~RheiaPackageVersion();

    /** clone method */
    virtual RheiaPackageVersion* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the version major */
    long GetMajor() {return m_major;};

    /** set the version major */
    void SetMajor(long major) {m_major = major;}

    /** get the version minor */
    long GetMinor() {return m_minor;};

    /** set the version minor */
    void SetMinor(long minor) {m_minor = minor;}

    /** get the version build */
    long GetBuild() {return m_build;};

    /** set the version build */
    void SetBuild(long build) {m_build = build;}

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageVersion info from the given xmlNode
    *   @return false if any Version required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageVersion info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :

    long m_major;
    long m_minor;
    long m_build;
};

#endif
