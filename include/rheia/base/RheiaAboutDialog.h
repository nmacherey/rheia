/**
*   @file RheiaAboutDialog.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	17-Nov-2009
*	@version 0.0.1
*/
#ifndef RheiaAboutDialog_h_
#define RheiaAboutDialog_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>

class wxImageList;
class wxBookCtrlEvent;
class wxListbookEvent;

/**
*   @class RheiaAboutDialog
*   @brief This class defines the Rheia About Dialog that can be displayed in the
*   Application.
*
*   If you are a Rheia Developper ou migth have to change some information in this panel
*   If you're not just do not matter about this.
*
*   This dialog is loading its information from the about_dialog.xrc file. Any tab displayed
*   in the book is associated to a 80x80 PNG bitmap, so if you manage to add a page in this
*   dialog you have to store in the resource file 2 bitmaps (one on and one with the _off extension
*   before the .png)
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	17-Nov-2009
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaAboutDialog : public wxDialog
{
public :
    /*******************************************************************************************
	*	CONSTRUCTORS
	*******************************************************************************************/
	/** basic constructor taking the parent window in input */
	RheiaAboutDialog( wxWindow* parent );

	/** default destructor */
	~RheiaAboutDialog();

protected :
    /*******************************************************************************************
	*	METHODS
	*******************************************************************************************/
	/** loads the list book image */
	void LoadListbookImages();

	/** Update the list book image */
	void UpdateListbookImages();

	/*******************************************************************************************
	*	EVENTS CALLBACKS
	*******************************************************************************************/
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

private :
    wxImageList* m_lbImages;

    /*******************************************************************************************
	*	EVENTS TABLE
	*******************************************************************************************/
	//DECLARE_EVENT_TABLE()
};

#endif
