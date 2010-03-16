/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPluginManifest.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	25-November-2009
*	@version 0.0.2
*/
#ifndef RheiaPluginManifest_h_
#define RheiaPluginManifest_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

class RheiaPackageMaintainer;
class RheiaPackageVersion;
class RheiaPackageDescription;

/**
*   @class RheiaPluginManifest
*
*   @brief Manifest file information container for RheiaPlugins
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
class PMGT_DLLEXPORT RheiaPluginManifest
{
    /** give RheiaPackageManager our private members access */
    friend class RheiaPluginManager;
public :
    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /** default constrcutor */
    RheiaPluginManifest();

#ifdef SWIG
	%rename(RheiaPluginManifestCopy) RheiaPluginManifest(const RheiaPluginManifest& rhs);
#endif
    /** copy constructor */
    RheiaPluginManifest(const RheiaPluginManifest& rhs);

    /** default destructor */
    virtual ~RheiaPluginManifest();

    /** clone method */
    virtual RheiaPluginManifest* Clone();

    /**************************************************************************************
    *   ACCESSORS
    **************************************************************************************/
    /** get the plugin name */
    const wxString& GetName() {return m_name;};

    /** set the plugin name */
    void SetName(const wxString& name) {m_name = name;};

    /** get the plugin title */
    const wxString& GetTitle() {return m_title;};

    /** set the plugin title */
    void SetTitle(const wxString& title) {m_title = title;};

    /** get the plugin thanks */
    const wxString& GetThanksTo() {return m_thanks;};

    /** set the plugin title */
    void SetThanksTo(const wxString& thanks) {m_thanks = thanks;};

    /** get the plugin class of applications */
    const wxString& GetClass() {return m_class;};

    /** set the plugin title */
    void SetClass(const wxString& classt) {m_class = classt;};

    /** get the plugins description */
    RheiaPackageDescription* GetDescription() {return m_description;};

    /** set the plugin's description */
    void SetDescription( RheiaPackageDescription* description );

    /** get the plugin's version */
    RheiaPackageVersion* GetVersion() {return m_version;};

    /** set the plugin's version */
    void SetVersion( RheiaPackageVersion* version );

    /** get the plugin's sdkversion */
    RheiaPackageVersion* GetSDKVersion() {return m_sdkversion;};

    /** set the plugin's sdkversion */
    void SetSDKVersion( RheiaPackageVersion* version );

    /** get the plugin's author */
    RheiaPackageMaintainer* GetAuthor() {return m_author;};

    /** set the plugin's author */
    void SetAuthor( RheiaPackageMaintainer* author );

    /**************************************************************************************
    *   XML MANAGEMENT METHODS
    **************************************************************************************/
    /**
    *   Read the RheiaPluginManifest info from the given xmlNode
    *   @return false if any Description required information is missing
    */
    virtual bool DoReadFromNode( xmlNode* parent );

    /**
    *   Write the RheiaPluginManifest info to the given node
    *   @return true if everything has been written properly
    */
    virtual bool DoWriteToNode( xmlNode* parent );

private :
    wxString m_name;
    wxString m_title;
    wxString m_thanks;
    wxString m_class;
    RheiaPackageDescription* m_description;
    RheiaPackageVersion* m_version;
    RheiaPackageVersion* m_sdkversion;
    RheiaPackageMaintainer* m_author;
};

#endif
