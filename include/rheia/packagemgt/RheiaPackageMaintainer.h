/**
*   @file RheiaPackageMaintainer.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#ifndef RheiaPackageMaintainer_h_
#define RheiaPackageMaintainer_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaPackageMaintainer
*
*   @brief This is the basic class for handling package maintainer information in Rheia
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPackageMaintainer
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPackageManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPackageMaintainer();

#ifdef SWIG
	%rename(RheiaPackageMaintainerCopy) RheiaPackageMaintainer(const RheiaPackageMaintainer& rhs);
#endif
    /** copy constructor */
    RheiaPackageMaintainer(const RheiaPackageMaintainer& rhs);

    /** default destructor */
    virtual ~RheiaPackageMaintainer();

    /** clone method */
    virtual RheiaPackageMaintainer* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the maintainer's name */
    const wxString& GetName() {return m_name;};

    /** set the maintianer's name */
    void SetName(const wxString& name) {m_name = name;};

    /** get the maintainer's address */
    const wxString& GetAddress() {return m_address;};

    /** set the maintianer's address*/
    void SetAddress(const wxString& address) {m_address = address;};

    /** get the maintainer's zipcode */
    const wxString& GetZipCode() {return m_zipcode;};

    /** set the maintianer's zipcode*/
    void SetZipCode(const wxString& zipcode) {m_zipcode = zipcode;};

    /** get the maintainer's town */
    const wxString& GetTown() {return m_town;};

    /** set the maintianer's town*/
    void SetTown(const wxString& town) {m_town = town;};

    /** get the maintainer's country */
    const wxString& GetCountry() {return m_country;};

    /** set the maintianer's country*/
    void SetCountry(const wxString& country) {m_country = country;};

    /** get the maintainer's phone */
    const wxString& GetPhone() {return m_phone;};

    /** set the maintianer's phone*/
    void SetPhone(const wxString& phone) {m_phone = phone;};

    /** get the maintainer's fax */
    const wxString& GetFax() {return m_fax;};

    /** set the maintianer's fax*/
    void SetFax(const wxString& fax) {m_fax = fax;};

    /** get the maintainer's email */
    const wxString& GetEmail() {return m_email;};

    /** set the maintianer's email*/
    void SetEmail(const wxString& email) {m_email = email;};

    /** get the maintainer's website */
    const wxString& GetWebSite() {return m_website;};

    /** set the maintianer's website*/
    void SetWebSite(const wxString& website) {m_website = website;};

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPackageMaintainer info from the given xmlNode
    *   @return false if any Maintainer required information is missing
    */
    bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPackageMaintainer info to the given node
    *   @return true if everything has been written properly
    */
    bool DoWriteToNode( xmlNode* parent );

private :

    wxString m_name;
    wxString m_address;
    wxString m_zipcode;
    wxString m_town;
    wxString m_country;
    wxString m_phone;
    wxString m_fax;
    wxString m_email;
    wxString m_website;
};

#endif
