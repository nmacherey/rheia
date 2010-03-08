
/**
*   @file RheiaPackageDescription.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageDescription_h_
#define RheiaPackageDescription_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaPackageDescription
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageDescription
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageDescription();

#ifdef SWIG
	%rename(RheiaPackageDescriptionCopy) RheiaPackageDescription(const RheiaPackageDescription& rhs);
#endif
    /** copy constructor */
    RheiaPackageDescription(const RheiaPackageDescription& rhs);

    /** default destructor */
    virtual ~RheiaPackageDescription();

    /** clone method */
    virtual RheiaPackageDescription* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the Description short */
    const wxString& GetShort() {return m_short;};

    /** set the Description short */
    void SetShort(const wxString& short_d) {m_short = short_d;};

    /** get the Description full */
    const wxString& GetFull() {return m_full;};

    /** set the Description full */
    void SetFull(const wxString& full) {m_full = full;};

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageDescription info from the given xmlNode
    *   @return false if any Description required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageDescription info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    wxString m_short;
    wxString m_full;
};

#endif


