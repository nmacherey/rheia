/**
*   @file RheiaPackageManagedFile.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageManagedFile_h_
#define RheiaPackageManagedFile_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaPackageManagedFile
*
*   @brief This is the basic class for handling package associated ManagedFiles in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageManagedFile
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageManagedFile();

    /** copy constructor */
    RheiaPackageManagedFile(const RheiaPackageManagedFile& rhs);

    /** default destructor */
    virtual ~RheiaPackageManagedFile();

    /** clone method */
    virtual RheiaPackageManagedFile* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the ManagedFile name */
    const wxString& GetName() {return m_name;};

    /** set the ManagedFile name */
    void SetName(const wxString& name) {m_name = name;};

    /** get the ManagedFile type */
    const wxString& GetType() {return m_type;};

    /** set the ManagedFile type */
    void SetType(const wxString& type) {m_type = type;};

    /** get the ManagedFile path */
    const wxString& GetPath() {return m_path;};

    /** set the ManagedFile path */
    void SetPath(const wxString& path) {m_path = path;};

    /** get the ManagedFile remove flag */
    bool GetRemove() {return m_remove;};

    /** set the remove flag*/
    void SetRemove(bool remove) {m_remove = remove;};

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageManagedFile info from the given xmlNode
    *   @return false if any ManagedFile required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageManagedFile info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    wxString m_name;
    wxString m_path;
    wxString m_type;
    bool m_remove;
};

#endif



