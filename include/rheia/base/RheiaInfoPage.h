/**
*   @file RheiaInfoPage.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*/

#ifndef RheiaInfoPage_h_
#define RheiaInfoPage_h_

#include "RheiaGlobals.h"
#include "RheiaBaseSettings.h"

/**
*   @class RheiaInfoPage
*
*   @brief This is the class from which any page displayed in the information pane maager shall
*   be derived from
*
*   This page is derived from a wxPanel an can be created more than once by the application. For example
*   when the user close the page and wants to display it again. As it is derived from wxPanel it provides
*   you with it's methods as well.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*
*/
class BASE_DLLEXPORT RheiaInfoPage : public wxPanel
{
public :

    /**
    *   Basic constructor
    *
    *   @param parent the parent window in which the panel shall be created
    */
    RheiaInfoPage( wxWindow* parent );

    /** Default destructor */
    virtual ~RheiaInfoPage();

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
    *   Callback used when the page is requested to be closed in the info pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual void OnPageClosed() = 0;

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

    /**
    *   Get the bitmap at the given size
    */
    virtual wxBitmap& GetBitmap( int size ) = 0;

protected :
};

#endif

