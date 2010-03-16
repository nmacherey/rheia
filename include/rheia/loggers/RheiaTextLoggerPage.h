/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaTextLoggerPage.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*/

#ifndef RheiaTextLoggerPage_h_
#define RheiaTextLoggerPage_h_

#include "RheiaGlobals.h"
#include "RheiaLoggersSettings.h"
#include "RheiaBookPage.h"

class RheiaTextLogger;
class wxRichTextCtrl;
class wxRichTextBuffer;

/**
*   @class RheiaTextLoggerPage
*
*   @brief this is the main panel that any project shall create in order to view
*   the page in the center pane when the project is created
*
*   This page is derived from a wxPanel an can be created more than once by the application.
*   Any project derived from RheiaProject shall build it's on derived RheiaTextLoggerPage
*   in order to manage specific stuff in the Rheia's center pane.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*
*/

class LOGGERS_DLLEXPORT RheiaTextLoggerPage : public RheiaBookPage
{
public :

    /**
    *   Basic constructor
    *
    *   @param parent the parent window in which the panel shall be created
    */
    RheiaTextLoggerPage( wxWindow* parent , RheiaTextLogger* logger );

    /** Default destructor */
    virtual ~RheiaTextLoggerPage();

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
    virtual void OnPageClosed();

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

    /** Get the containing text control */
    wxRichTextCtrl* GetTextCtrl() { return m_window; };

    /** Get the content */
    void GetContent(wxRichTextBuffer* content);

    /** Set the content */
    void SetContent(wxRichTextBuffer* content);

protected :
    RheiaTextLogger* m_logger;
    wxRichTextCtrl* m_window;
};

#endif



