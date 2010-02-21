
/**
*   @file RheiaPackageFiles.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageFiles_h_
#define RheiaPackageFiles_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/* imports */
class RheiaPackageFile;

/** define a map of file */
typedef std::map< wxString , RheiaPackageFile* > RheiaPackageFileMap;

/**
*   @class RheiaPackageFiles
*
*   @brief This is the basic class for handling package version information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageFiles
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageFiles();

    /** copy constructor */
    RheiaPackageFiles(const RheiaPackageFiles& rhs);

    /** default destructor */
    virtual ~RheiaPackageFiles();

    /** clone method */
    virtual RheiaPackageFiles* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get files */
    const RheiaPackageFileMap& GetFiles() {return m_files;}

    /** Set files */
    void SetFiles(const RheiaPackageFileMap& files) {Clear(); m_files = files;};

    /** Find File */
    RheiaPackageFile* FindFile(const wxString& name);

    /** Exists */
    bool Exists(const wxString& name);

    /** Remove file */
    bool Remove( const wxString& name );

    /** Add file */
    bool Add(const wxString& name, RheiaPackageFile* dep );

    /** Clear */
    void Clear();

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageFiles info from the given xmlNode
    *   @return false if any Files required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageFiles info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    RheiaPackageFileMap m_files;
};

#endif




