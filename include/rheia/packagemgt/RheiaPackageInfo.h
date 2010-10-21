/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageInfo.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageInfo_h_
#define RheiaPackageInfo_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageControl;
class RheiaPackageManagedFiles;

/**
*   @class RheiaPackageInfo
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageInfo
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageInfo();

#ifdef SWIG
	%rename(RheiaPackageInfoCopy) RheiaPackageInfo(const RheiaPackageInfo& rhs);
#endif
    /** copy constructor */
    RheiaPackageInfo(const RheiaPackageInfo& rhs);

    /** default destructor */
    virtual ~RheiaPackageInfo();

    /** clone method */
    virtual RheiaPackageInfo* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/

    /** Get the package control */
    RheiaPackageControl* GetControl() {return m_control;};

    /** Set the package control */
    void SetControl(RheiaPackageControl* control);

    /** Get the package files */
    RheiaPackageManagedFiles* GetManagedFiles() {return m_files;};

    /** Set the package files */
    void SetManagedFiles(RheiaPackageManagedFiles* files);

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageInfo info from the given xmlNode
    *   @return false if any Info required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageInfo info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :

    RheiaPackageControl* m_control;
    RheiaPackageManagedFiles* m_files;
};

#endif



