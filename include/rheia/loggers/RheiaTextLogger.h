/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaTextLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#ifndef RheiaTextLogger_h_
#define RheiaTextLogger_h_

#include "RheiaLogger.h"
#include "RheiaGlobals.h"

#include <wx/colour.h>
#include <wx/font.h>
#include <wx/ffile.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextbuffer.h>

class RheiaTextLoggerPage;
class wxRichTextBuffer;

/**
*	@class RheiaTextLogger
*
*	@brief RheiaTextLogger is the basic class for logging into a wxTextCtrl.
*
*   This is the most basic logger with a window in control. You can log into a RheiaTextLogger when
*   ever you want and it will managed specific text formatting accordingly to the log level given
*   in the log message.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaTextLogger : public RheiaLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaTextLogger )
#endif
    friend class RheiaTextLoggerPage;
public:

    /**
    *   Basic constructor
    *   This will intialize all text attributes for the default loglevels
    *   specified in the RheiaLogging::RheiaLogLevel enmeration.
    *   The user can choose colors and fonts for each log level for a given logger
    */
    RheiaTextLogger();

    virtual ~RheiaTextLogger();

    /**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message);

    /**
    *   RheiaLogger::Clear method overload (@see RheiaLogger::Clear)
    */
    virtual void Clear();

    /** Callback used when the text logger settings changed */
    void OnTextLoggerSettings(wxCommandEvent& event);

    /** Method used for registering events */
    void RegisterEvents();


//    /**
//    *   RheiaLogger::CopyAll method overload (@see RheiaLogger::CopyAll)
//    */
//    virtual void CopyAll();
//
//    /**
//    *   RheiaLogger::CopySelection method overload (@see RheiaLogger::CopySelection)
//    */
//    virtual void CopySelection();
//
//    /**
//    *   RheiaLogger::HelpOnSelection method overload (@see RheiaLogger::HelpOnSelection)
//    */
//    virtual void HelpOnSelection();
//
//    /**
//    *   RheiaLogger::BuildMenu method overload (@see RheiaLogger::BuildMenu)
//    *   @param menu the parent wxMenu in which you shall add items
//    */
//    virtual void BuildMenu( wxMenu* menu );

    /**
    *   RheiaLogger::UpdateSettings method overload (@see RheiaLogger::UpdateSettings)
    */
    virtual void UpdateSettings();

    /**
    *   RheiaLogger::GetLogWindow method overload (@see RheiaLogger::GetLogWindow)
    *   @param parent the parent window in which the log window shall be created
    *   @return NULL if the logger is not displaying in a log window (default)
    */
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );

	/**
	*   Get the TextAttributes
	*/
	wxTextAttrEx* GetTextAttributes( ) {return m_textattr;};

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed();

protected:

    RheiaTextLoggerPage* m_window;
    wxTextAttrEx m_textattr[RheiaLogging::RheiaLogLevelNumber];
    wxRichTextBuffer* m_content;
};

/**
*	@class RheiaTimeStampableTextLogger
*
*	@brief RheiaTimeStampableTextLogger is the basic class for logging into a wxTextCtrl.
*
*   This is the most basic logger with a window in control. You can log into a RheiaTextLogger when
*   ever you want and it will managed specific text formatting accordingly to the log level given
*   in the log message.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaTimeStampableTextLogger : public RheiaTextLogger
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS( RheiaTimeStampableTextLogger )
#endif
public:

    /**
    *   Basic constructor
    *   This will intialize all text attributes for the default loglevels
    *   specified in the RheiaLogging::RheiaLogLevel enmeration.
    *   The user can choose colors and fonts for each log level for a given logger
    */
    RheiaTimeStampableTextLogger();

    /**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message);
};


#endif
