/**
*   @file RheiaTextLogger.cpp
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.1
*/
#include "RheiaTextLogger.h"
#include "RheiaGlobals.h"
#include "RheiaLoggerManager.h"
#include "RheiaStandardPaths.h"
#include "RheiaConfigurationManager.h"
#include "RheiaManager.h"
#include "RheiaEventsManager.h"
#include "RheiaEvents.h"
#include "RheiaTextLoggerPage.h"
#include "RheiaTextLoggerConfigurationPanel.h"

IMPLEMENT_DYNAMIC_CLASS( RheiaTextLogger , RheiaLogger );
IMPLEMENT_DYNAMIC_CLASS( RheiaTimeStampableTextLogger , RheiaTextLogger );

namespace TextLogger
{
    REGISTER_LOGGER( RheiaTextLogger , wxT("TextLogger") );
};

namespace TimeTextLogger
{
    REGISTER_LOGGER( RheiaTimeStampableTextLogger , wxT("TimeTextLogger") );
};

RheiaTextLogger::RheiaTextLogger():
    m_window(NULL),
    m_content(NULL)
{

}

RheiaTextLogger::~RheiaTextLogger()
{
    if( m_content != NULL )
        delete m_content;
}

void RheiaTextLogger::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_TXT_LOGGER_SETTINGS, new RheiaEventFunctor<RheiaTextLogger>(this, wxCommandEventHandler(RheiaTextLogger::OnTextLoggerSettings)));
}

void RheiaTextLogger::OnTextLoggerSettings(wxCommandEvent& event)
{
    UpdateSettings();
}

void RheiaTextLogger::UpdateSettings()
{
    RheiaConfigurationManager* cfg = RheiaManager::Get()->GetConfigurationManager( wxT("RheiaTextLogger") );
    bool isFirstTime = true;

    isFirstTime = (bool) cfg->ReadInt( wxT("/first_time") , (int) true );

    if( isFirstTime )
    {
        int size = 10;
        wxFont default_font(size, wxFONTFAMILY_SWISS , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        wxFont bold_font(size, wxFONTFAMILY_SWISS , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        wxFont italic_font(size, wxFONTFAMILY_SWISS , wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);

        bold_font.SetWeight(wxFONTWEIGHT_BOLD);

        wxFont bigger_font(bold_font);
        bigger_font.SetPointSize(size + 2);

        wxFont small_font(default_font);
        small_font.SetPointSize(size - 4);

        for(unsigned int i = 0; i < RheiaLogging::RheiaLogLevelNumber ; ++i)
        {
            m_textattr[i].SetFlags( wxTEXT_ATTR_FONT | wxTEXT_ATTR_ALIGNMENT );
            m_textattr[i].SetFont(default_font);
            m_textattr[i].SetAlignment(wxTEXT_ALIGNMENT_LEFT);
            m_textattr[i].SetTextColour(*wxBLACK);
            m_textattr[i].SetBackgroundColour(*wxWHITE);
        }

        m_textattr[RheiaLogging::warning].SetFont(italic_font);
        m_textattr[RheiaLogging::warning].SetTextColour(*wxBLUE);

        m_textattr[RheiaLogging::success].SetAlignment(wxTEXT_ALIGNMENT_CENTRE);
        bigger_font.SetUnderlined(true);
        m_textattr[RheiaLogging::success].SetFont(bigger_font);
        m_textattr[RheiaLogging::success].SetTextColour(*wxBLUE);

        m_textattr[RheiaLogging::error].SetFont(bold_font);
        m_textattr[RheiaLogging::error].SetTextColour(*wxRED);

        m_textattr[RheiaLogging::fatalerror].SetFont(bold_font);
        m_textattr[RheiaLogging::fatalerror].SetTextColour(*wxWHITE);
        m_textattr[RheiaLogging::fatalerror].SetBackgroundColour(*wxRED);

        m_textattr[RheiaLogging::syserror].SetFont(bold_font);
        m_textattr[RheiaLogging::syserror].SetTextColour(*wxWHITE);
        m_textattr[RheiaLogging::syserror].SetBackgroundColour(*wxBLUE);

        m_textattr[RheiaLogging::info].SetFont(italic_font);

        m_textattr[RheiaLogging::status].SetFont(bold_font);
        m_textattr[RheiaLogging::status].SetTextColour(*wxGREEN);

        m_textattr[RheiaLogging::debug].SetFont(italic_font);
        m_textattr[RheiaLogging::debug].SetTextColour(*wxGREEN);

        m_textattr[RheiaLogging::trace].SetFont(italic_font);
        m_textattr[RheiaLogging::trace].SetTextColour(*wxGREEN);

        if( cfg != NULL )
        {
            cfg->Write( wxT("/message") , m_textattr[RheiaLogging::message] );
            cfg->Write( wxT("/warning") , m_textattr[RheiaLogging::warning] );
            cfg->Write( wxT("/success") , m_textattr[RheiaLogging::success] );
            cfg->Write( wxT("/error") , m_textattr[RheiaLogging::error] );
            cfg->Write( wxT("/fatalerror") , m_textattr[RheiaLogging::fatalerror] );
            cfg->Write( wxT("/info") , m_textattr[RheiaLogging::info] );
            cfg->Write( wxT("/status") , m_textattr[RheiaLogging::status] );
            cfg->Write( wxT("/syserror") , m_textattr[RheiaLogging::syserror] );
            cfg->Write( wxT("/debug") , m_textattr[RheiaLogging::debug] );
            cfg->Write( wxT("/trace") , m_textattr[RheiaLogging::trace] );
            cfg->Write( wxT("/first_time") , (int) false );
        }

        return;
    }

    m_textattr[RheiaLogging::message] = cfg->ReadTextAttr( wxT("/message") );
    m_textattr[RheiaLogging::warning] = cfg->ReadTextAttr( wxT("/warning") );
    m_textattr[RheiaLogging::success] = cfg->ReadTextAttr( wxT("/success") );
    m_textattr[RheiaLogging::error] = cfg->ReadTextAttr( wxT("/error") );
    m_textattr[RheiaLogging::fatalerror] = cfg->ReadTextAttr( wxT("/fatalerror") );
    m_textattr[RheiaLogging::info] = cfg->ReadTextAttr( wxT("/info") );
    m_textattr[RheiaLogging::status] = cfg->ReadTextAttr( wxT("/status") );
    m_textattr[RheiaLogging::syserror] = cfg->ReadTextAttr( wxT("/syserror") );
    m_textattr[RheiaLogging::debug] = cfg->ReadTextAttr( wxT("/debug") );
    m_textattr[RheiaLogging::trace] = cfg->ReadTextAttr( wxT("/trace") );
}

void RheiaTextLogger::Log( const wxString& msg, RheiaLogging::RheiaLogLevel level )
{
    if(m_window == NULL)
        return;

    wxRichTextCtrl* control = m_window->GetTextCtrl();

    control->BeginStyle(m_textattr[level]);

    control->AppendText(msg);
    control->AppendText(wxT("\n"));

    control->EndAllStyles();
}

void RheiaTextLogger::Clear()
{
    if(m_window == NULL)
        return;

    wxRichTextCtrl* control = m_window->GetTextCtrl();
    control->Clear();
}

RheiaBookPage* RheiaTextLogger::BuildMainWindow( wxWindow* parent )
{
    m_window = new RheiaTextLoggerPage( parent , this );
    if( m_content != NULL )
        m_window->SetContent(m_content);

    return m_window;
}

RheiaTimeStampableTextLogger::RheiaTimeStampableTextLogger():
    RheiaTextLogger()
{

}

void RheiaTimeStampableTextLogger::Log( const wxString& msg, RheiaLogging::RheiaLogLevel level )
{
    wxString premsg;

    wxDateTime timestamp(wxDateTime::UNow());
    premsg += wxString::Format( wxT("[%2.2d:%2.2d:%2.2d.%3.3d] : "),
        timestamp.GetHour(),
        timestamp.GetMinute(),
        timestamp.GetSecond(),
        timestamp.GetMillisecond() );

    RheiaTextLogger::Log( premsg + msg , level );
}

bool RheiaTextLogger::OnPageClosed()
{
    if( m_content == NULL )
        m_content = new wxRichTextBuffer();

    m_window->GetContent(m_content);
    m_window=NULL;

    return true;
}

