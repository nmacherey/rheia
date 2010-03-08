
/**
*   @file RheiaPackageDependency.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageDependency_h_
#define RheiaPackageDependency_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>
#include <RheiaPackageVersion.h>

#ifndef SWIG
/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
#endif

/**
*   @class RheiaPackageDependency
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageDependency : public RheiaPackageVersion
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageDependency();

#ifdef SWIG
	%rename(RheiaPackageDependencyCopy) RheiaPackageDependency(const RheiaPackageDependency& rhs);
#endif
    /** copy constructor */
    RheiaPackageDependency(const RheiaPackageDependency& rhs);

    /** default destructor */
    virtual ~RheiaPackageDependency();

    /** clone method */
    virtual RheiaPackageDependency* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the dependency name */
    const wxString& GetName() {return m_name;};

    /** set the dependency name */
    void SetName(const wxString& name) {m_name = name;};

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageDependency info from the given xmlNode
    *   @return false if any Dependency required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageDependency info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    wxString m_name;
};

#endif

