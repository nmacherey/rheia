/**
*   @file RheiaConfigurationToolsManager.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include <RheiaConfigurationToolsManager.h>

/*! declare global instance for the RheiaConfigurationToolsManager */
template<> RheiaConfigurationToolsManager* Mgr<RheiaConfigurationToolsManager>::instance = 0;
/*! declare global isShutdown variable for the RheiaConfigurationToolsManager */
template<> bool  Mgr<RheiaConfigurationToolsManager>::isShutdown = false;


RheiaConfigurationToolsManager::RheiaConfigurationToolsManager()
{

}

RheiaConfigurationToolsManager::~RheiaConfigurationToolsManager()
{

}

wxArrayString RheiaConfigurationToolsManager::GetList()
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.begin();
    wxArrayString ret;

    for( ; it != m_tools.end() ; ++it )
        ret.Add( it->first );

    return ret;
}

wxArrayString RheiaConfigurationToolsManager::GetListFor(ConfigurationGroup group)
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.begin();
    wxArrayString ret;

    for( ; it != m_tools.end() ; ++it )
        if(it->second.group == group )
        ret.Add( it->first );

    return ret;
}

bool RheiaConfigurationToolsManager::RegisterTool( const wxString& name,
        ConfigurationGroup group,
        CreateConfigurationTool ctor,
        FreeConfigurationTool dtor )
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.find( name );

    if( it != m_tools.end() )
        return false;

    RheiaConfigurationToolRegistration info;
    info.name = name;
    info.group = group;
    info.ctor = ctor;
    info.dtor = dtor;

    m_tools[name] = info;

    return true;
}

bool RheiaConfigurationToolsManager::UnregisterTool( const wxString& name )
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.find( name );

    if( it == m_tools.end() )
        return true;

    m_tools.erase(it);
    return true;
}

RheiaConfigurationPanel* RheiaConfigurationToolsManager::CreateTool( const wxString& name,
        wxWindow* parent )
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.find( name );

    if( it == m_tools.end() )
        return NULL;

    return it->second.ctor( parent );
}

const RheiaConfigurationToolRegistration* RheiaConfigurationToolsManager::FindToolByName( const wxString& name )
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.find( name );

    if( it == m_tools.end() )
        return NULL;

    return &(it->second);
}

bool RheiaConfigurationToolsManager::Exists( const wxString& name )
{
    RheiaConfigurationToolRegistrationMap::iterator it = m_tools.find( name );

    if( it == m_tools.end() )
        return false;

    return true;
}
