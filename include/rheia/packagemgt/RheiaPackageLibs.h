/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/

/**
*   @file RheiaPackageLibs.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageLibs_h_
#define RheiaPackageLibs_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageLib;

/** define a map of Lib */
typedef std::map< wxString , RheiaPackageLib* > RheiaPackageLibMap;

/**
*   @class RheiaPackageLibs
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageLibs
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageLibs();

#ifdef SWIG
	%rename(RheiaPackageLibsCopy) RheiaPackageLibs(const RheiaPackageLibs& rhs);
#endif
    /** copy constructor */
    RheiaPackageLibs(const RheiaPackageLibs& rhs);

    /** default destructor */
    virtual ~RheiaPackageLibs();

    /** clone method */
    virtual RheiaPackageLibs* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get libs */
    const RheiaPackageLibMap& GetLibs() {return m_libs;}

    /** Set libs */
    void SetLibs(const RheiaPackageLibMap& libs) {Clear(); m_libs = libs;};

    /** Find Lib */
    RheiaPackageLib* FindLib(const wxString& name);

    /** Exists */
    bool Exists(const wxString& name);

    /** Remove Lib */
    bool Remove( const wxString& name );

    /** Add Lib */
    bool Add(const wxString& name, RheiaPackageLib* dep );

    /** Clear */
    void Clear();

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageLibs info from the given xmlNode
    *   @return false if any Libs required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageLibs info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    RheiaPackageLibMap m_libs;
};

#endif




