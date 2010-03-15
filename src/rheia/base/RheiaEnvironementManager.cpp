/**
*	@file RheiaEnvironementManager.cpp
*
*   This file defines the singleton desing template manager for dealing with local applications environement variables
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/

#include "RheiaEnvironementManager.h"
#include "RheiaManagedFrame.h"
#include "RheiaEventsManager.h"
#include "RheiaConfigurationManager.h"
#include "RheiaEnvVarsConfigurationDialog.h"

#ifdef LINUX
#include <unistd.h>
#endif

#include <wx/menu.h>

/*! Global instance for the environement manager */
template<> RheiaEnvironementManager* Singleton<RheiaEnvironementManager>::instance = 0;
/*! Global isShutdown for the environement manager */
template<> bool  Singleton<RheiaEnvironementManager>::isShutdown = false;

BEGIN_EVENT_TABLE(RheiaEnvironementManager,wxEvtHandler)
    //EVT_FRAME_CLOSING( RheiaEnvironementManager::OnCloseFrame )
END_EVENT_TABLE()


RheiaEnvironementManager::RheiaEnvironementManager():
        wxEvtHandler()
{
    m_envars = RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->ReadStringStringMap( wxT("/variables") );
    m_libpaths = RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->ReadArrayString( wxT("/libs") );

    RheiaStringStringMap::iterator it = m_envars.begin();

    for ( ; it != m_envars.end() ; ++it )
        wxSetEnv( it->first , it->second );

    for ( unsigned int i = 0; i < m_libpaths.GetCount() ; ++i )
    {
        wxString env;
#if defined( WIN32 )
        wxGetEnv( wxT("PATH") , &env );
        env += wxT(";") + m_libpaths[i];
        wxSetEnv( wxT("PATH") , env );
#elif defined( LINUX )
        wxGetEnv( wxT("LD_LIBRARY_PATH") , &env );
        env += m_libpaths[i] + wxT(":");
        wxSetEnv( wxT("LD_LIBRARY_PATH") , env );
#elif defined( MACOSX )
        wxGetEnv( wxT("DYLD_LIBRARY_PATH") , &env );
        env += m_libpaths[i] + wxT(":");
        wxSetEnv( wxT("DYLD_LIBRARY_PATH") , env );
#endif
    }

    RheiaEventsManager* pm = RheiaEventsManager::Get();
    pm->RegisterEventMethod(RheiaEVT_FRAME_CLOSING, new RheiaEventFunctor<RheiaEnvironementManager>(this, RheiaFrameEventHandler(RheiaEnvironementManager::OnCloseFrame)));
}

RheiaEnvironementManager::~RheiaEnvironementManager()
{
    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/variables") , m_envars );
    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/libs") , m_libpaths );
}

bool RheiaEnvironementManager::Add( const wxString& name , const wxString& value )
{
    RheiaStringStringMap::iterator it = m_envars.find( name );

    if ( it != m_envars.end() )
        return false;

    m_envars[name] = value;
    wxSetEnv( name , value );

    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/variables") , m_envars );

    return true;
}

bool RheiaEnvironementManager::Change( const wxString& name , const wxString& value )
{
    m_envars[name] = value;
    wxSetEnv( name , value );

    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/variables") , m_envars );

    return true;
}

bool RheiaEnvironementManager::Remove( const wxString& name )
{
    RheiaStringStringMap::iterator it = m_envars.find( name );

    if ( it == m_envars.end() )
        return false;

    m_envars.erase(it);
    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/variables") , m_envars );

    return true;
}

wxString RheiaEnvironementManager::FindVariableByName( const wxString& name )
{
    RheiaStringStringMap::iterator it = m_envars.find( name );

    if ( it == m_envars.end() )
    {
        wxString env;
        wxGetEnv( name , &env );
        return env;
    }

    return it->second;
}

bool RheiaEnvironementManager::Exists( const wxString& name )
{
    RheiaStringStringMap::iterator it = m_envars.find( name );

    if ( it == m_envars.end() )
        return false;

    return true;
}

bool RheiaEnvironementManager::AddPath( const wxString& path )
{
    int index = m_libpaths.Index( path );
    if ( index != wxNOT_FOUND )
        return false;

    m_libpaths.Add( path );
    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/libs") , m_libpaths );

    wxString env;
#if defined( WIN32 )
    wxGetEnv( wxT("PATH") , &env );
    env += wxT(";") + path;
    wxSetEnv( wxT("PATH") , env );
#elif defined( LINUX )
    wxGetEnv( wxT("LD_LIBRARY_PATH") , &env );
    env += path + wxT(":");
    wxSetEnv( wxT("LD_LIBRARY_PATH") , env );
#elif defined( MACOSX )
    wxGetEnv( wxT("DYLD_LIBRARY_PATH") , &env );
    env += path + wxT(":");
    wxSetEnv( wxT("DYLD_LIBRARY_PATH") , env );
#endif

    return true;
}

bool RheiaEnvironementManager::RemovePath( const wxString& path )
{
    int index = m_libpaths.Index( path );
    if ( index == wxNOT_FOUND )
        return false;

    m_libpaths.RemoveAt( index );
    RheiaManager::Get()->GetConfigurationManager( wxT("environement_manger") )->Write( wxT("/libs") , m_libpaths );

    return true;
}

bool RheiaEnvironementManager::PathExists( const wxString& path )
{
    int index = m_libpaths.Index( path );
    if ( index == wxNOT_FOUND )
        return false;

    return true;
}

void RheiaEnvironementManager::BuildMenu( RheiaManagedFrame* parent, wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx == wxNOT_FOUND )
        return;

    RheiaManagedFrameIdMap::iterator it = m_frameIds.find(parent);
    if( it == m_frameIds.end() )
    {
        m_frameIds[parent] = wxNewId();
        parent->PushEventHandler(this);
    }

    wxMenu* mnSettings = menuBar->GetMenu( idx );
    mnSettings->Append( m_frameIds[parent] , wxT("&Environment Variables") , wxT("Configure environment variables and paths") );
    Connect(m_frameIds[parent],wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEnvironementManager::OnManageEnvironmentVariables));
}

void RheiaEnvironementManager::ReleaseMenu( RheiaManagedFrame* parent, wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("Settings"));
    if( idx == wxNOT_FOUND )
        return;

    RheiaManagedFrameIdMap::iterator it = m_frameIds.find(parent);
    if( it == m_frameIds.end() )
        return;

    wxMenu* mnSettings = menuBar->GetMenu( idx );
    mnSettings->Delete( m_frameIds[parent] );
    Disconnect(m_frameIds[parent],wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEnvironementManager::OnManageEnvironmentVariables));
    m_frameIds.erase(it);
    parent->RemoveEventHandler(this);
}

void RheiaEnvironementManager::OnManageEnvironmentVariables(wxCommandEvent& event)
{
    int menuId = event.GetId();
    RheiaManagedFrameIdMap::iterator it = m_frameIds.begin();

    for( ; it != m_frameIds.end() ; ++it )
        if( it->second == menuId )
        {
            RheiaEnvVarsConfigurationDialog dialog(it->first);
            dialog.ShowModal();
            return;
        }

    return;
}

void RheiaEnvironementManager::OnCloseFrame(RheiaFrameEvent& event)
{
    ReleaseMenu( event.GetFrame() , event.GetFrame()->GetMenuBar() );
    event.Skip();
}
