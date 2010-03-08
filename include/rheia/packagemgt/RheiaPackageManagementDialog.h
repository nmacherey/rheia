/**
*   @file RheiaPackageManagementDialog.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	01-February-2010
*	@version 0.0.1
*/
#ifndef RheiaPackageManagementDialog_h_
#define RheiaPackageManagementDialog_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>
#include <RheiaEvents.h>
#include <treelistctrl.h>

#include <map>

class wxImageList;
class wxBookCtrlEvent;
class wxListbookEvent;
class RheiaPackageInfo;
class wxTreeListCtrl;

typedef std::map< wxString , wxTreeItemId > TreeItemIdMap;

/**
*   @class RheiaPackageManagementDialog
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	17-Nov-2009
*	@version 0.0.1
*/
class PMGT_DLLEXPORT RheiaPackageManagementDialog : public wxDialog
{
public :
    /*******************************************************************************************
	*	CONSTRUCTORS
	*******************************************************************************************/
	/** basic constructor taking the parent window in input */
	RheiaPackageManagementDialog( wxWindow* parent );

	/** default destructor */
	~RheiaPackageManagementDialog();

protected :
    /*******************************************************************************************
	*	METHODS
	*******************************************************************************************/

    /** Fill the package page */
    void DoBuildPackagesPage();

    /** Fill the plugins page */
    void DoBuildPluginsPage();

    /** Fill the library page */
    void DoBuilLibsPage();

	/*******************************************************************************************
	*	EVENTS CALLBACKS
	*******************************************************************************************/
    /** Callback used whent he user acts on the tree list ctrl for packages */
    void OnPackageListSelection(wxTreeEvent& event);

    /** On Install package */
    void OnInstallPackage( wxCommandEvent& event );

    /** On Remove package */
    void OnRemovePackage( wxCommandEvent& event );

    /** Callback used when the package is installed */
    void OnPackageInstalled( RheiaEvent& event );

    /** Callback used when the package is removed */
    void OnPackageRemoved( RheiaEvent& event );

private :
    /*******************************************************************************************
	*	METHODS
	*******************************************************************************************/
	/** Update package info for the given object */
	void DoUpdatePackageInfoFor( RheiaPackageInfo* info );

	/** Update the package tree */
	void DoUpdatePackageTree();

	/** Register Events in RheiaEventsManager */
	void RegiserEvents();

    /*******************************************************************************************
	*	MEMBERS
	*******************************************************************************************/
    wxTreeListCtrl *m_treelist;
    TreeItemIdMap m_packageIds;
    wxTreeItemId m_root;

    /*******************************************************************************************
	*	EVENTS TABLE
	*******************************************************************************************/
#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};


#include <wx/treectrl.h>

/**
*   @class RheiaPackageTreeItemData
*
*   This is the basic class for handling data in a tree control in rheia python
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	29-January-2010
*	@version 0.0.2
*/
class RheiaPackageTreeItemData : public wxTreeItemData
{
public:
    /**********************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **********************************************************************************************/
    /** default ctor */
    RheiaPackageTreeItemData(RheiaPackageInfo* pkgInfo =  0L) : m_pkgInfo(pkgInfo) {}

    /** dtor */
    virtual ~RheiaPackageTreeItemData()
    {
        m_pkgInfo=0L;
    }

    RheiaPackageInfo* GetInfo() {return m_pkgInfo;};

    void SetInfo( RheiaPackageInfo* pkgInfo ) {m_pkgInfo = pkgInfo;};

private :

    RheiaPackageInfo* m_pkgInfo;
};

#endif
