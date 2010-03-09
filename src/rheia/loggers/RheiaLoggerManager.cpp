/**
*   @file RheiaLoggerManager.cpp
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaLoggerManager.h>
#include <RheiaInfoPaneManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaConfigurationDialog.h>
#include <RheiaLogMgrSettingsPanel.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaException.h>
#include <RheiaBookPage.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/menu.h>
#include <wxStreamedTextCtrl.h>

#include <iostream>

/*! declare global instance for RheiaLoggerManager */
template<> RheiaLoggerFactory* Mgr<RheiaLoggerFactory>::instance = 0;
/*! declare global isShutdown variable for RheiaLoggerManager */
template<> bool  Mgr<RheiaLoggerFactory>::isShutdown = false;

namespace
{
    int menuId = wxNewId();

    RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaLoggerManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaLoggerManager>::m_ns = locmap;

BEGIN_EVENT_TABLE( RheiaLoggerManager, wxEvtHandler )
    EVT_MENU( menuId , RheiaLoggerManager::OnConfigure )
END_EVENT_TABLE()

/**********************************************************************************************************
*  CONSTRUCTORS
**********************************************************************************************************/
RheiaLoggerManager::RheiaLoggerManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_parent(parent)
{
    m_nullloger = new RheiaNullLogger;
    m_activelog = m_nullloger;
}

RheiaLoggerManager::~RheiaLoggerManager()
{
    RheiaLoggerMap::iterator it = m_loggers.begin();

    for( ; it != m_loggers.end() ; ++it )
        delete it->second;

    if( m_nullloger != NULL )
        delete m_nullloger;

    if( m_parent )
        m_parent->RemoveEventHandler(this);
}

RheiaLoggerFactory::RheiaLoggerFactory()
{
    m_nullloger = new RheiaNullLogger;
}


RheiaLoggerFactory::~RheiaLoggerFactory()
{
    if( m_nullloger != NULL )
        delete m_nullloger;
}

void RheiaLoggerManager::InitializeEnvironment()
{
//    /*************************************************************************
//    * Create the log window
//    *************************************************************************/
//#if wxHAS_TEXT_WINDOW_STREAM
//    LogWindow = new wxTextCtrl( Book, wxID_ANY, _("This is the log window\n"), wxDefaultPosition,
//                                wxDefaultSize, wxNO_BORDER | wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE );
//    redirector = new wxStreamToTextRedirector( LogWindow );
//#else
//    LogWindow = new wxStreamedTextCtrl( Book, wxID_ANY, _("This is the log window\n"), wxDefaultPosition,
//                                        wxDefaultSize, wxNO_BORDER | wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE );
//    redirector = new wxStreamToTextRedirector( (wxStreamedTextCtrl*) LogWindow , std::cout );
//#endif
//    std::cout << "Standard cout stream redirected to the log window..." << std::endl;
//
//    // Set user profile book configuration
//    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("log_manager"));
//
//    /* Now sets the log font size */
//    int FontSize = (int) icfg->ReadInt(_T("/aspect/log_font_size"), 8);
//    wxTextCtrl *iText = LogWindow;
//    wxFont font = iText->GetFont();
//    font.SetPointSize( FontSize );
//    iText->SetFont( font );
//
//    for(size_t i = 0; i < max_logs; ++i)
//    {
//        slot[i].index = i;
//        slot[i].log = &g_null_log;
//    }
//
//    SetLog(new RheiaTextCtrlLogger, app_log);
//    SetLog(new RheiaStdoutLogger, stdout_log);
//    SetLog(new RheiaTextCtrlLogger, debug_log);
//    slot[app_log].title = _T("Rheia");
//    slot[debug_log].title = _T("Rheia Debug");
//    slot[stdout_log].title = _T("stdout");
//
//    wxString path = RheiaStandardPaths::DataDirectoryGlobal() + _T("/images/edit_16x16.png");
//    defaultBitmap = RheiaLoadBitmap(path, wxBITMAP_TYPE_PNG);
//
//    wxRegisterId(baseID + num_pages);
//    for(int i = 0; i < num_pages; ++i)
//    {
//        page[i] = Page();
//    }
//
//    wxWindow* log;
//
//    for(size_t i = app_log; i < ::max_logs; ++i)
//    {
//        if((log = Slot(i).GetLogger()->CreateControl(Book)))
//            AddLogger(Slot(i).GetLogger(), log, Slot(i).title, Slot(i).icon);
//    }
//
//    /*************************************************************************
//    * Add the log window to the page
//    *************************************************************************/
//    Book->AddPage( LogWindow , _("Logs") , false , defaultBitmap );

    /***
    *   Global loggers shall now be registered
    *   Create standard RheiaLoggers name Rheia Log, Rheia Debug Log
    */
    RheiaLogger* log = RheiaLoggerFactory::Get()->BuildLogger( wxT("TimeTextLogger") , wxT("Rheia Log") );

    if( log != NULL )
    {
        AddLogger(log,wxT("Rheia Log"));
        log->Log( wxT("Rheia Log initialized ...") , RheiaLogging::success );
        log->Log( wxT("You will find here all standard Rheia Logging Info ...") , RheiaLogging::info );
        SetActiveLogger( wxT("Rheia Log") );
    }

//#if defined( RHEIA_DEBUG ) || defined( _DEBUG )
    RheiaLogger* debuglog = RheiaLoggerFactory::Get()->BuildLogger( wxT("TimeTextLogger") , wxT("Rheia Debug Log") );

    if( debuglog != NULL )
    {
        AddLogger(debuglog,wxT("Rheia Debug Log"));
        debuglog->Log( wxT("Rheia Debug Log initialized ...") , RheiaLogging::success );
    }
//#endif
    if( m_parent )
	{
        m_parent->PushEventHandler( this );
		m_parent->Connect( RheiaEVT_FRAME_CLOSING , RheiaFrameEventHandler(RheiaLoggerManager::OnCloseFrame) , NULL , this );
	}
}

void RheiaLoggerManager::OnCloseFrame(RheiaFrameEvent& event)
{
	m_parent->RemoveEventHandler( this );
	event.Skip();
}

void RheiaLoggerManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_LOGGER_REMOVED, new RheiaEventFunctor<RheiaLoggerManager>(this, wxCommandEventHandler(RheiaLoggerManager::OnUnregisterLogger)));
}

void RheiaLoggerManager::OnUnregisterLogger(wxCommandEvent& event)
{
    wxString name = event.GetString();
    // Remove all loggers of the given type, this is due to prevent
    // loggers models from plugins dll unloading
    RheiaLogger* logger = GetFirstLoggerOf( name );
    while( logger != NULL )
    {
        DeleteLogger( logger );
        logger = GetFirstLoggerOf( name );
    }
}

void RheiaLoggerManager::BuildMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx == wxNOT_FOUND )
        return;

    wxMenu* mnSettings = menuBar->GetMenu( idx );
    mnSettings->Append( menuId , wxT("&Logger Settings") , wxT("Configure the logger manager") );
}

void RheiaLoggerManager::ReleaseMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx == wxNOT_FOUND )
        return;

    wxMenu* mnSettings = menuBar->GetMenu( idx );
    mnSettings->Delete( menuId );
}

void RheiaLoggerManager::OnConfigure(wxCommandEvent& WXUNUSED(event) )
{
    RheiaConfigurationDialog dialog( m_parent );
    RheiaLogMgrSettingsPanel* m_panel = new RheiaLogMgrSettingsPanel(&dialog);
    dialog.SetConfigurationTool( m_panel );

    dialog.ShowModal();
}

//void RheiaLoggerManager::OnCopy(wxCommandEvent& event)
//{
//	int i = GetPageIndexByWindow(Book->GetPage(Book->GetSelection()));
//	if (page[i].islogger)
//	{
//		if (event.GetId() == idCopyAllToClipboard)
//			page[i].logger->CopyContentsToClipboard(false);
//		else if (event.GetId() == idCopySelectedToClipboard)
//			page[i].logger->CopyContentsToClipboard(true);
//	}
//}
//
//void RheiaLoggerManager::OnClear(wxCommandEvent& event)
//{
//	int i = GetPageIndexByWindow(Book->GetPage(Book->GetSelection()));
//	if (page[i].islogger)
//		page[i].logger->Clear();
//}
//
//void RheiaLoggerManager::OnMenu(wxCommandEvent& event)
//{
//    if(event.GetId() < baseID || event.GetId() > baseID + num_pages)
//    {
//		event.Skip();
//		return;
//    }
//
//    int i = event.GetId() - baseID; // get back our index
//	Toggle(i);
//}
//
//void RheiaLoggerManager::ContextMenu(wxContextMenuEvent& event)
//{
//    wxMenu menu;
//	wxMenu* view;
//    bool any_nonloggers = false;
//
//	if (page[GetPageIndexByWindow(Book->GetPage(Book->GetSelection()))].islogger)
//	{
//		view = new wxMenu;
//
//		menu.Append(idCopyAllToClipboard, _("Copy contents to clipboard"));
//		menu.Append(idCopySelectedToClipboard, _("Copy selection to clipboard"));
//		menu.AppendSeparator();
//		menu.Append(idClear, _("Clear contents"));
//		menu.AppendSeparator();
//	}
//	else
//		view = &menu;
//
//    for(int i = 0; i < num_pages; ++i)
//    {
//        if(page[i].window)
//        {
//            if(page[i].islogger)
//            {
//                view->Append(baseID + i, page[i].title, wxEmptyString, wxITEM_CHECK);
//				view->Check(baseID + i, page[i].indexInNB != -1);
//            }
//            else
//            {
//                any_nonloggers = true;
//            }
//        }
//    }
//
//    if(any_nonloggers)
//    {
//        view->AppendSeparator();
//        for(int i = 0; i < num_pages; ++i)
//        {
//            if(page[i].window && !page[i].islogger)
//            {
//                view->Append(baseID + i, page[i].title, wxEmptyString, wxITEM_CHECK);
//				view->Check(baseID + i, page[i].indexInNB != -1);
//            }
//        }
//    }
//
//	if (&menu != view)
//		menu.AppendSubMenu(view, _("Toggle..."));
//
//    Book->PopupMenu(&menu);
//}

bool RheiaLoggerFactory::RegisterLogger( const wxString& name , CreateLogger createFunc, FreeLogger freeFunc )
{
    RheiaRegisteredLoggersMap::iterator it = m_registeredLoggers.find( name );
    if( it != m_registeredLoggers.end() )
        return false;

    RheiaLoggerRegistration newLogger;
    newLogger.name = name;
    newLogger.createLogger = createFunc;
    newLogger.freeLogger = freeFunc;

    m_registeredLoggers[name] = newLogger;

    return true;
}

bool RheiaLoggerFactory::UnregisterLogger( const wxString& name )
{
    RheiaRegisteredLoggersMap::iterator it = m_registeredLoggers.find( name );
    if( it == m_registeredLoggers.end() )
        return false;

    wxCommandEvent event( RheiaEVT_LOGGER_REMOVED );
    event.SetString( name );
    RheiaEventsManager::Get()->ProcessEvent(event);

    m_registeredLoggers.erase(it);
    return true;
}

bool RheiaLoggerManager::SetActiveLogger( const wxString& name )
{
    RheiaLoggerMap::iterator it = m_loggers.find( name );
    if( it == m_loggers.end() )
        return false;

    m_activelog = it->second;

    /*** activate the page in the book or recreate it if it does not exists */
    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);

    if( !ip->PageExists(name) )
        ip->AddPage( name , m_activelog );

    ip->ActivatePage( name );

    return true;
}

bool RheiaLoggerManager::SetActiveLogger( RheiaLogger* logger )
{
    RheiaLoggerMap::iterator it = m_loggers.begin();

    for( ; it != m_loggers.end() ; ++it )
        if( it->second == logger )
            break;

    if( it == m_loggers.end() )
        return false;

    m_activelog = it->second;
    wxString name = it->first;

    /*** activate the page in the book or recreate it if it does not exists */
    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
    if( !ip->PageExists(name) )
        ip->AddPage( name , m_activelog );

    ip->ActivatePage( name );

    return true;
}

bool RheiaLoggerManager::SetActiveLogger( const wxString& name , RheiaLogger* logger )
{
    RheiaLoggerMap::iterator it = m_loggers.find( name );
    if( it == m_loggers.end() )
    {
        it = m_loggers.begin();

        for( ; it != m_loggers.end() ; ++it )
            if( it->second == logger )
                break;

        if( it != m_loggers.end() ) // instance registered with an other name
            return false;

        m_loggers[name] = logger;
    }
    else if( it->second != logger )
        return false;

    m_activelog = logger;

    /*** activate the page in the book or recreate it if it does not exists */
    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
    if( !ip->PageExists(name) )
        ip->AddPage( name , m_activelog );

    ip->ActivatePage( name );

    return true;
}

wxString RheiaLoggerManager::GetLoggerName( RheiaLogger* logger )
{
    RheiaLoggerMap::iterator it = m_loggers.begin();

    for( ; it != m_loggers.end() ; ++it )
        if( it->second == logger )
            return it->first;

    return wxEmptyString;
}

RheiaLogger* RheiaLoggerManager::GetLogger( const wxString& name )
{
    RheiaLoggerMap::iterator it = m_loggers.find( name );

    if( it == m_loggers.end() )
        return m_nullloger;

    return it->second;
}

RheiaLogger* RheiaLoggerManager::GetFirstLoggerOf( const wxString& type )
{
    RheiaLoggerMap::iterator it = m_loggers.begin();

    for( ; it != m_loggers.end() ; ++it )
        if( it->second->GetType().IsSameAs( type ) )
            return it->second;

    return NULL;
}

void RheiaLoggerManager::Log(const wxString& msg , RheiaLogging::RheiaLogLevel level )
{
    wxString name = GetLoggerName( m_activelog );

    if( !name.IsEmpty() )
    {
        /*** activate the page in the book or recreate it if it does not exists */
        RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
        if( !ip->PageExists(name) )
            ip->AddPage( name , m_activelog );

        ip->ActivatePage( name );
    }
    m_activelog->Log( msg , level );
}

void RheiaLoggerManager::ClearLog()
{
    wxString name = GetLoggerName( m_activelog );

    if( !name.IsEmpty() )
    {
        /*** activate the page in the book or recreate it if it does not exists */
        RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
         if( !ip->PageExists(name) )
            ip->AddPage( name , m_activelog );

        ip->ActivatePage( name );
    }

    m_activelog->Clear();
}

void RheiaLoggerManager::ClearLog( const wxString& name )
{
    RheiaLogger* logger = GetLogger( name );

    if( logger == m_nullloger )
        return;

    if( !name.IsEmpty() )
    {
        /*** activate the page in the book or recreate it if it does not exists */
        RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
        if( !ip->PageExists(name) )
            ip->AddPage( name , m_activelog );

        ip->ActivatePage( name );
    }

    logger->Clear();
}

wxArrayString RheiaLoggerManager::ListLoggers()
{
    RheiaLoggerMap::iterator it = m_loggers.begin();
    wxArrayString ret;

    for( ; it != m_loggers.end() ; ++it )
        ret.Add(it->first);

    return ret;
}

wxArrayString RheiaLoggerFactory::ListRegisteredLoggers()
{
    RheiaRegisteredLoggersMap::iterator it = m_registeredLoggers.begin();
    wxArrayString ret;

    for( ; it != m_registeredLoggers.end() ; ++it )
        ret.Add(it->first);

    return ret;
}

RheiaLogger* RheiaLoggerFactory::BuildLogger( const wxString& type, const wxString& WXUNUSED(name) )
{
    RheiaRegisteredLoggersMap::iterator rit = m_registeredLoggers.find(type);

    if( rit == m_registeredLoggers.end() )
        return m_nullloger;

    RheiaLogger* logger = rit->second.createLogger();
    logger->SetType(type);

    return logger;
}

bool RheiaLoggerManager::AddLogger( RheiaLogger* logger, const wxString& name )
{
    RheiaLoggerMap::iterator it = m_loggers.find( name );

    if( it != m_loggers.end() )
        return false;

    m_loggers[name] = logger;

    // Add the loggers page if requested
    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
    ip->AddPage( name , logger );

    logger->UpdateSettings();

    return true;
}

bool RheiaLoggerManager::DeleteLogger(RheiaLogger* logger)
{
    wxString name = GetLoggerName( logger );

    if( name.IsEmpty() )
        return false;

    return DeleteLogger( name );
}

bool RheiaLoggerManager::DeleteLogger(const wxString& name)
{
    RheiaLoggerMap::iterator it = m_loggers.find( name );

    if( it == m_loggers.end() )
        return false;

    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
    ip->DeletePage( name );

    delete it->second;
    m_loggers.erase(it);

    return true;
}

void RheiaLoggerManager::NotifyUpdate()
{
    RheiaLoggerMap::iterator it = m_loggers.begin( );

    for( ; it != m_loggers.end() ; ++it )
        it->second->UpdateSettings();
}

void RheiaLoggerManager::Show(const wxString& name)
{
    RheiaLoggerMap::iterator it = m_loggers.find( name );

    if( it == m_loggers.end() )
        return;

    RheiaLogger* logger = it->second;
    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
    if( !ip->PageExists(name) )
        ip->AddPage( name , logger );

    ip->ActivatePage( name );
}

void RheiaLoggerManager::Show(RheiaLogger* logger)
{
    wxString name = GetLoggerName( logger );

    if( name.IsEmpty() )
        return;

    Show( name );
}

int RheiaLoggerManager::GetLogPageIndex( const wxString& name )
{
    RheiaInfoPaneManager* ip = RheiaInfoPaneManager::Get(m_parent);
    return ip->FindPageIndexByName( name );
}

int RheiaLoggerManager::GetLogPageIndex( RheiaLogger* logger )
{
    wxString name = GetLoggerName( logger );

    if( name.IsEmpty() )
        return wxNOT_FOUND;

    return GetLogPageIndex( name );
}

RheiaConfigurationManager* RheiaLoggerManager::GetConfigurationGroupFor( RheiaLogger* logger )
{
    wxString name = GetLoggerName( logger );

    if( name.IsEmpty() )
        return NULL;

    return GetConfigurationGroupFor( name );
}

RheiaConfigurationManager* RheiaLoggerManager::GetConfigurationGroupFor( const wxString& name )
{
    if( name.IsEmpty() )
        return NULL;

    RheiaLoggerMap::iterator it = m_loggers.find( name );

    if( it == m_loggers.end() )
        return NULL;

    return RheiaManager::Get()->GetConfigurationManager( name );
}
