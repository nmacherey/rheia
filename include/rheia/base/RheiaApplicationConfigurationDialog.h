/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaApplicationConfigurationDialog.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr) the 17 November 2009
*   Changes : Commentaries and management of configuration tools via
*       the RheiaConfigurationToolsManager
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.2
*   @date 24-September-2009
*/
#ifndef RheiaApplicationConfigurationDialog_h_
#define RheiaApplicationConfigurationDialog_h_

#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>

#include <map>

/* imports */
class wxBookCtrlEvent;
class wxListbookEvent;
class wxCheckListBox;
class wxImageList;

/* Rheia imports */
class RheiaConfigurationPanel;

/**
*   Define a page info structure for this dialog.
*   A page info structure is used for handling page info in the
*   RheiaApplicationConfigurationDialog. It handles the image index
*   and the page Title in order to be properly managed in the dialog.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
struct RheiaConfigurationPageInfo
{
    /** default constructor */
    RheiaConfigurationPageInfo():page(NULL),idxOn(-1),idxOff(-1) {};

#ifdef SWIG
	%rename(RheiaConfigurationPageInfoCopy) RheiaConfigurationPageInfo( const RheiaConfigurationPageInfo& rhs );
#endif
    /** copy constructor */
    RheiaConfigurationPageInfo( const RheiaConfigurationPageInfo& rhs ):
        page(rhs.page),
        idxOn(rhs.idxOn),
        idxOff(rhs.idxOff),
        title(rhs.title)
        {};
		
	/** destructor */
	~RheiaConfigurationPageInfo(){page=NULL;}

#ifndef SWIG
	/** operator = overload */
	RheiaConfigurationPageInfo& operator= (const RheiaConfigurationPageInfo& rhs )
	{
		page = rhs.page;
		idxOn = rhs.idxOn;
		idxOff = rhs.idxOff;
		title = rhs.title;

        return *this;
	}
#endif

    RheiaConfigurationPanel* page;
    int idxOn;
    int idxOff;
    wxString title;
};

/**
*   Associate a wxString to a page info in order
*   to properly manage configuration tools in the manager
*/
typedef std::map< wxString , RheiaConfigurationPageInfo > RheiaConfigurationPageInfoMap;

/**
*   @class RheiaApplicationConfigurationDialog
*
*   @brief This is the main dialog for configuring Rheia.
*
*   This dialog uses registered configuration tools in the RheiaConfigurationToolsManager.
*   You shall never directly modify this objact in order to add a configuration tool in
*   Rheia. To do this, you have to derive an object from a RheiaConfigurationPanel and
*   to register it in the RheiaConfigurationToolsManager.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.2
*   @date 17-November-2009
*/
class BASE_DLLEXPORT RheiaApplicationConfigurationDialog : public wxDialog
{
public:
    /***********************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ***********************************************************************/
    /**
    *   default constructor
    *   @param parent the parent window in which the dialog shall be created
    */
    RheiaApplicationConfigurationDialog( wxWindow* parent );

    /** destructor */
    virtual ~RheiaApplicationConfigurationDialog();

    /***********************************************************************
    *   METHODS
    ***********************************************************************/
    /** Activate the given page in the note book */
    void SetPageSelection( const wxString& page_name );

    /** End modal function overload for use when the user clikcs ok or cancel */
    virtual void EndModal(int retCode);

protected:

    /***********************************************************************
    *   EVENTS RELATED CALLBACKS
    ***********************************************************************/
    /** Used when a notebook page is about to be changed */
#if wxCHECK_VERSION(2, 9, 0)
    void OnPageChanging(wxBookCtrlEvent& event);
#else
    void OnPageChanging(wxListbookEvent& event);
#endif

    /** Used when a notebook page has been changed */
#if wxCHECK_VERSION(2, 9, 0)
    void OnPageChanged(wxBookCtrlEvent& event);
#else
    void OnPageChanged(wxListbookEvent& event);
#endif

    /***********************************************************************
    *   PRIVATE METHODS
    ***********************************************************************/
    /** method used to load registered configuration tools */
    void DoLoadConfigurationTools();

    /** method used to update all the listbook images */
    void UpdateListbookImages();

    /************************************************************************************
    *   PAGE MANAGEMENT METHODS
    ************************************************************************************/
    /**
    *   Add network notebook page for the given network
    *   @param name network name
    *   @param page the network page object to be added
    *   @return false if the page has not been added properly
    */
    bool AddPage( wxString name, RheiaConfigurationPanel* page );

    /**
    *   Remove a page from the notebook
    *   @return false if the page cannot be removed
    */
    bool DeletePage( const wxString& name );

    /** Get the active page name */
    wxString GetActivePageName();

    /**
    *   Activate a page in the center pane book
    *   @return false if the page has not been added properly
    */
    bool ActivatePage( wxString name );

    /**
    *   Find a page given its name
    *   @param name the page's name to find
    */
    RheiaConfigurationPanel* FindPageByName( const wxString& name );

    /**
    *   Find a page given its name
    *   @param name the page's name to find
    */
    RheiaConfigurationPageInfo* FindPageInfoByName( const wxString& name );

    /**
    *   Find a page index given its name
    *   @param name the page's name to find the index for
    */
    int FindPageIndexByName( const wxString& name );

    /**
    *   Find a page given its page pointer
    *   @param page the page's pointer to find the name for
    */
    wxString FindPageNameByObject( RheiaConfigurationPanel* page );

    /**
    *   Find a page index given its name
    *   @param name the page's name to find the index for
    */
    int FindPageIndexByObject( RheiaConfigurationPanel* page );

private :
    /***********************************************************************
    *   PRIVATE MEMBERS
    ***********************************************************************/
    RheiaConfigurationPageInfoMap m_pages;
    wxImageList* m_lbImages;

private:
#ifndef SWIG
    DECLARE_EVENT_TABLE()
#endif
};

#endif
