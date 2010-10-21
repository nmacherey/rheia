/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageFile.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageFile_h_
#define RheiaPackageFile_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaPackageFile
*
*   @brief This is the basic class for handling package associated files in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageFile
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageFile();

#ifdef SWIG
	%rename(RheiaPackageFileCopy) RheiaPackageFile(const RheiaPackageFile& rhs);
#endif
    /** copy constructor */
    RheiaPackageFile(const RheiaPackageFile& rhs);

    /** default destructor */
    virtual ~RheiaPackageFile();

    /** clone method */
    virtual RheiaPackageFile* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the File name */
    const wxString& GetName() {return m_name;};

    /** set the File name */
    void SetName(const wxString& name) {m_name = name;};

    /** get the File type */
    const wxString& GetType() {return m_type;};

    /** set the File type */
    void SetType(const wxString& type) {m_type = type;};

    /** get the File path */
    const wxString& GetPath() {return m_path;};

    /** set the File path */
    void SetPath(const wxString& path) {m_path = path;};

    /** specify if the file shall be completely removed from the hard drive when deleting the file from the data base */
    bool Remove() { return remove; };

    /** set the remove flag */
    void SetRemove( bool value ) { remove = value; };

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageFile info from the given xmlNode
    *   @return false if any File required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageFile info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    wxString m_name;
    wxString m_path;
    wxString m_type;
    bool remove;
};

#endif


