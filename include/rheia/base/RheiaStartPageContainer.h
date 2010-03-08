/**
* @file RheiaStartPageContainer
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/
#ifndef RheiaStartPageContainer_h_
#define RheiaStartPageContainer_h_

#include "RheiaBaseSettings.h"
#include "RheiaPageContainer.h"
#include "RheiaGlobals.h"
#include "RheiaBookPage.h"
#include "RheiaManagedFrame.h"
#include "RheiaEventFrame.h"

/* locally defined */
class RheiaStartPage;
class wxWebControl;
class wxWebEvent;

/**
 * @class RheiaStartPageContainer
 * @brief Main class for displaying a Start page in htlm format in your applications
 *
 * This class will create a wxWenConnect control based on xulrunner it's very usefull if
 * you need to display a web page content when starting the application.
 * 
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 1.0.1
 * @date 2-March-2010
 */
class BASE_DLLEXPORT RheiaStartPageContainer : public wxEvtHandler, public RheiaPageContainer
{
public :
	/** ctor 
	 * @param file html file to display 
	 */
	RheiaStartPageContainer( RheiaManagedFrame* parent, const wxString& file = wxEmptyString );
	
	/** dtor */
	virtual ~RheiaStartPageContainer();

	/**
	*   Any project will have a window in the center pane, which will be called
	*   the project's main envrionment.
	*
	*   For this purpose, any projects must provide the application with a MainWindow
	*   which will be displayed and managed by RheiaCenterPaneManager.
	*
	*   We consider that a project cannot be provided without any MainWindow.
	*
	*   @param parent the parent window in which the project's main window shall be created
	*/
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed() {return true;};
	

	/** Get the html file displayed in the control */
	const wxString& GetHtmlFile() {return m_htmlfile;};
	
	/** Set the html file displayed in the control */
	void SetHtmlFile( const wxString& file) {m_htmlfile = file;};
	
	/** Get the page bitmap */
	virtual const wxBitmap& GetBitmap( const int& size ) {return m_bmp;}
	
	/** Rheia Frame Event */
	void OnCloseParent(RheiaFrameEvent& event);
	
private :
	RheiaManagedFrame* m_parent;
	wxString m_htmlfile;
	wxBitmap m_bmp; 
#ifndef SWIG
	DECLARE_EVENT_TABLE()
#endif
};


/**
 * @class RheiaStartPage
 * @brief Main class you shall never have to deal with.
 * 
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 1.0.1
 * @date 2-March-2010
 */
class BASE_DLLEXPORT RheiaStartPage : public RheiaBookPage
{
public :
	/** ctor
	 * @param parent parented window 
	 * @param file file url to display
	 */
	RheiaStartPage( wxWindow* parent , const wxString& file );
	
	/** DoBuildStartPage */
	void DoBuildStartPage();
	
	/**
    *   Callback method used when the page is changing in the main book.
    *   you must overload this method if you want to do specific stuff
    *   when the user is changing the current selected page
    *
    *   @return true if the application allow for page changing false else
    */
    virtual bool OnPageChanging(){return true;};

    /**
    *   Callback method used when the page is changed in the main book.
    *   you must overload this method if you want to do specific stuff
    *   when the user is changing the current selected page
    */
    virtual bool OnPageChanged(){return true;};

    /**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual void OnPageClosed() {};
	
	/**
	 * this method is called when the user right clicks on the book tab
	 * the book tab is where the page's title is displayed
	 */
	virtual void OnTabRightClicked() {};

    /**
    *   Callback used when the information has benn modified outside
    *   the application.
    *   You must overload this method in order to refresh information about
    *   the page content when its requested
    */
    virtual void OnPageUpdate() {};


    /**
    *   Callback used on OnDelete()
    */
    virtual void OnDelete() {};

    /**
    *   Callback used when creating the panel
    */
    virtual void OnCreate(){};

	/** callback used when the user selects an uri */
	void OnOpenURI( wxWebEvent& event );
private :

	wxString m_file;
	wxWebControl* m_browser;
};

#endif
