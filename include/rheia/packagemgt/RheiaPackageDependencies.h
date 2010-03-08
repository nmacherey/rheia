
/**
*   @file RheiaPackageDependencies.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageDependencies_h_
#define RheiaPackageDependencies_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageDependency;

/** define a map of dependency */
typedef std::map< wxString , RheiaPackageDependency* > RheiaPackageDependencyMap;

/**
*   @class RheiaPackageDependencies
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageDependencies
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageDependencies();

#ifdef SWIG
	%rename(RheiaPackageDependenciesCopy) RheiaPackageDependencies(const RheiaPackageDependencies& rhs);
#endif
    /** copy constructor */
    RheiaPackageDependencies(const RheiaPackageDependencies& rhs);

    /** default destructor */
    virtual ~RheiaPackageDependencies();

    /** clone method */
    virtual RheiaPackageDependencies* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get dependencies */
    const RheiaPackageDependencyMap& GetDependencies() {return m_dependencies;}

    /** Set dependencies */
    void SetDependencies(const RheiaPackageDependencyMap& dependencies) {Clear(); m_dependencies = dependencies;};

    /** Find Dependency */
    RheiaPackageDependency* FindDependency(const wxString& name);

    /** Exists */
    bool Exists(const wxString& name);

    /** Remove dependency */
    bool Remove( const wxString& name );

    /** Add dependency */
    bool Add(const wxString& name, RheiaPackageDependency* dep );

    /** Clear */
    void Clear();

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageDependencies info from the given xmlNode
    *   @return false if any Dependencies required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageDependencies info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    RheiaPackageDependencyMap m_dependencies;
};

#endif



