/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/

/**
*   @file RheiaPackageManagedFiles.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageManagedFiles_h_
#define RheiaPackageManagedFiles_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageManagedFile;

/** define a map of file */
typedef std::map< wxString , RheiaPackageManagedFile* > RheiaPackageManagedFileMap;

/**
*   @class RheiaPackageManagedFiles
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageManagedFiles
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageManagedFiles();

#ifdef SWIG
	%rename(RheiaPackageManagedFilesCopy) RheiaPackageManagedFiles(const RheiaPackageManagedFiles& rhs);
#endif
    /** copy constructor */
    RheiaPackageManagedFiles(const RheiaPackageManagedFiles& rhs);

    /** default destructor */
    virtual ~RheiaPackageManagedFiles();

    /** clone method */
    virtual RheiaPackageManagedFiles* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get files */
    const RheiaPackageManagedFileMap& GetManagedFiles() {return m_files;}

    /** Set files */
    void SetManagedFiles(const RheiaPackageManagedFileMap& files) {Clear(); m_files = files;};

    /** Find ManagedFile */
    RheiaPackageManagedFile* FindManagedFile(const wxString& name);

    /** Exists */
    bool Exists(const wxString& name);

    /** Remove file */
    bool Remove( const wxString& name );

    /** Add file */
    bool Add(const wxString& name, RheiaPackageManagedFile* dep );

    /** Clear */
    void Clear();

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageManagedFiles info from the given xmlNode
    *   @return false if any ManagedFiles required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageManagedFiles info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    RheiaPackageManagedFileMap m_files;
};

#endif





