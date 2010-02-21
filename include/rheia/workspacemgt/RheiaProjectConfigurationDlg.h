/**
*	@file RheiaProjectConfigurationDlg.h
*
*	@brief This file is used for loading the plugins configuration dialog in Rheia
*
*
*	This file is the property of Nicolas Macherey and cannot be used directly or indirectly by
*	any person without the written consent of the author.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 03-Fev-2009
*	@version 0.0.1
*/

#ifndef RheiaProjectConfigurationDlg_h_
#define RheiaProjectConfigurationDlg_h_

#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <RheiaWMgtSettings.h>
#include <RheiaGlobals.h>
#include <RheiaPluginManager.h>

class wxBookCtrlEvent;
class wxListbookEvent;
class RheiaProject;
class wxImageList;
class RheiaConfigurationPanel;

typedef std::map< wxString , RheiaConfigurationPanel* > RheiaProjectElementConfigurationPanelMap;

/**
*	@class RheiaProjectConfigurationDlg
*
*	@brief Configure projects in rheia dialog definition
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	03-Fev-2009
*	@version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectConfigurationDlg : public wxDialog
{

public:

    /**
    *	@brief Default constructor
    *
    *	The default constructor is taking the parent window as argument
    *	and builds the dialog by loading ressources and getting plugin information
    *	from the plugin manager.
    *
    *	@param parent parent window in which to launch the dialog
    */
    RheiaProjectConfigurationDlg(wxWindow* parent,RheiaProject* project);

    /**
    *	@brief Change the ListCtrl Page selection whitout user interface
    *
    *	This function is used for changing the page Selection in the dialog
    *	Simply give the name of the page you want to view to start the dialog
    *	on this specific page.
    *
    *	@param page_name name of the page you want to view first
    */
    void SetPageSelection( const wxString& page_name );

    /**
    *	@brief Default desctructor
    */
    virtual ~RheiaProjectConfigurationDlg();

    /**
    *	@brief Used to end the dialog show modal mode and save info if required
    *
    *	@param retCode returned user code when the dialog ends can be on of both
    *							WX_OK or WX_CANCEL
    */
    virtual void EndModal(int retCode);

protected:

    /**
    *   @brief Used before a page selection is made
    *
    *	@param event Generated wxEvent
    */
#if wxCHECK_VERSION(2, 9, 0)
    void OnPageChanging(wxBookCtrlEvent& event);
#else
    void OnPageChanging(wxListbookEvent& event);
#endif

    /**
     *	@brief Used after a page selection is made
     *
     *	@param event Generated wxEvent
     */
#if wxCHECK_VERSION(2, 9, 0)
    void OnPageChanged(wxBookCtrlEvent& event);
#else
    void OnPageChanged(wxListbookEvent& event);
#endif

    /**
     *	@brief Used when a control of the dialog is updated
     *
     *	@param event Generated wxEvent
     */
    void OnUpdateUI(wxUpdateUIEvent& event);


private:

    /**
     *	@brief Used for loading the listbook images
     *
     *	This function is used to load the list book wxImageList in the list ctrl items
     */
    void LoadListbookImages();

    /** Build pages for project elements */
    void DoBuildElementPages();

    RheiaProject* m_project;
    wxImageList* m_imageList;

    RheiaProjectElementConfigurationPanelMap m_pages;

    DECLARE_EVENT_TABLE()
};

#endif

