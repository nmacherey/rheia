/**
*   @file RheiaListLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#ifndef RheiaListLogger_h_
#define RheiaListLogger_h_

#include "RheiaLogger.h"
#include "RheiaGlobals.h"

#include <wx/colour.h>
#include <wx/font.h>
#include <wx/ffile.h>
#include <wx/textctrl.h>

class wxListCtrl;

/**
*	@class RheiaListLogger
*
*	@brief RheiaListLogger is the basic class for logging into a wxListCtrl
*
*   By logging in a list control you will be able to properly display all your
*   messages ordered by columns, and by the way manage any user actions using
*   the wxListCtrl events.
*   In rheia this logger can be configured by the user and enables him to choose
*   for the messages colors accordingly to the log level...
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaListLogger : public RheiaLogger
{
    DECLARE_DYNAMIC_CLASS( RheiaListLogger )
public:

    /**
    *   Basic builder
    *
    *   @param titles list view as tab titles
    *   @param widths column width for the list
    *   @param fixedPitchFont specifies if the pitch font shall be fixed
    */
    RheiaListLogger(const wxArrayString& titles, const wxArrayInt& widths, bool fixedPitchFont = false);

    /** Default builder */
    RheiaListLogger(){};

/**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message)

    /**
    *   RheiaLogger::Clear method overload (@see RheiaLogger::Clear)
    */
    virtual void Clear();

    /**
    *   RheiaLogger::CopyAll method overload (@see RheiaLogger::CopyAll)
    */
    virtual void CopyAll();

    /**
    *   RheiaLogger::CopySelection method overload (@see RheiaLogger::CopySelection)
    */
    virtual void CopySelection();

    /**
    *   RheiaLogger::HelpOnSelection method overload (@see RheiaLogger::HelpOnSelection)
    */
    virtual void HelpOnSelection();

    /**
    *   RheiaLogger::BuildMenu method overload (@see RheiaLogger::BuildMenu)
    *   @param menu the parent wxMenu in which you shall add items
    */
    virtual void BuildMenu( wxMenu* menu );

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
    *   RheiaLogger::GetConfigurationTool method overload (@see RheiaLogger::GetConfigurationTool)
    *   @param parent the parent window in which the log window shall be created
    *   @return NULL if the logger is not displaying in a log window (default)
    */
	virtual RheiaConfigurationPanel* GetConfigurationTool( wxWindow* parent ) ;

    /**
    *   Get the number of items in the list
    */
    virtual size_t GetItemsCount() const;

    /**
    *   Get the full list item as text
    */
    wxString GetItemAsText(long item) const;

protected:

    wxListCtrl* control;
    bool fixed;
    wxArrayString titles;
    wxArrayInt widths;

    struct ListStyles
    {
        wxFont font;
        wxColour colour;
    };

    ListStyles style[num_levels];
};


/**
*	@class RheiaTimeStampableListLogger
*
*	@brief RheiaTimeStampableListLogger is the basic class for logging into a wxListCtrl
*
*   By logging in a list control you will be able to properly display all your
*   messages ordered by columns, and by the way manage any user actions using
*   the wxListCtrl events.
*   In rheia this logger can be configured by the user and enables him to choose
*   for the messages colors accordingly to the log level...
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	15-April-2009
*	@version 0.0.1
*/
class LOGGERS_DLLEXPORT RheiaTimeStampableListLogger : public RheiaLogger
{
    DECLARE_DYNAMIC_CLASS( RheiaTimeStampableListLogger )
public:

    /**
    *   Basic builder
    *
    *   @param titles list view as tab titles
    *   @param widths column width for the list
    *   @param fixedPitchFont specifies if the pitch font shall be fixed
    */
    RheiaTimeStampableListLogger(const wxArrayString& titles, const wxArrayInt& widths, bool fixedPitchFont = false);

    /** Default builder */
    RheiaTimeStampableListLogger(){};

/**
    *   Log function overload
    *   If the file has not been opened, no message will be loagged into the file and
    *   it will return safely.
    */
    virtual void Log(const wxString& msg, RheiaLogging::RheiaLogLevel level = RheiaLogging::message)

    /**
    *   RheiaLogger::Clear method overload (@see RheiaLogger::Clear)
    */
    virtual void Clear();

    /**
    *   RheiaLogger::CopyAll method overload (@see RheiaLogger::CopyAll)
    */
    virtual void CopyAll();

    /**
    *   RheiaLogger::CopySelection method overload (@see RheiaLogger::CopySelection)
    */
    virtual void CopySelection();

    /**
    *   RheiaLogger::HelpOnSelection method overload (@see RheiaLogger::HelpOnSelection)
    */
    virtual void HelpOnSelection();

    /**
    *   RheiaLogger::BuildMenu method overload (@see RheiaLogger::BuildMenu)
    *   @param menu the parent wxMenu in which you shall add items
    */
    virtual void BuildMenu( wxMenu* menu );

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
    *   RheiaLogger::GetConfigurationTool method overload (@see RheiaLogger::GetConfigurationTool)
    *   @param parent the parent window in which the log window shall be created
    *   @return NULL if the logger is not displaying in a log window (default)
    */
	virtual RheiaConfigurationPanel* GetConfigurationTool( wxWindow* parent ) ;

    /**
    *   Get the number of items in the list
    */
    virtual size_t GetItemsCount() const;

    /**
    *   Get the full list item as text
    */
    wxString GetItemAsText(long item) const;

protected:

    wxListCtrl* control;
    bool fixed;
    wxArrayString titles;
    wxArrayInt widths;

    struct ListStyles
    {
        wxFont font;
        wxColour colour;
    };

    ListStyles style[num_levels];
};

#endif

