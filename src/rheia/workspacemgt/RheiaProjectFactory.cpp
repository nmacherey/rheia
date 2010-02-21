/**
*   @file RheiaProjectFactory.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/

#include <RheiaProjectFactory.h>
#include <RheiaProject.h>
#include <RheiaWorkspace.h>

/*! Global instance for the plugin manager */
template<> RheiaProjectFactory* Mgr<RheiaProjectFactory>::instance = 0;
/*! Global isShutdown for the Menu manager */
template<> bool  Mgr<RheiaProjectFactory>::isShutdown = false;

RheiaProjectFactory::RheiaProjectFactory()
{

}

RheiaProjectFactory::~RheiaProjectFactory()
{

}

bool RheiaProjectFactory::RegisterProject( const wxString& name ,
        const wxString& description,
        const wxString& title,
        const wxString& bitmapBaseName,
        ProjectConstructor ctor, ProjectDestructor dtor )
{
    RheiaProjectRegistrationMap::iterator it = m_RegisteredProjects.find( name );

    if ( it != m_RegisteredProjects.end() )
        return false;

    RheiaProjectRegistration registration;

    registration.name = name;
    registration.description = description;
    registration.title = title;
    registration.bitmapBaseName = bitmapBaseName;
    registration.ctor = ctor;
    registration.dtor = dtor;

    m_RegisteredProjects[name] = registration;

    return true;
}

RheiaProject* RheiaProjectFactory::CreateProject( const wxString& type,
    RheiaManagedFrame* parent,
    RheiaWorkspace* workspace,
    const wxString& name ,
    const wxString& file )
{
    RheiaProjectRegistrationMap::iterator it = m_RegisteredProjects.find( type );

    if ( it == m_RegisteredProjects.end() )
        return NULL;

    RheiaProject *project = it->second.ctor( parent , workspace , name , file );
    project->SetType( type );

    return project;
}

wxArrayString RheiaProjectFactory::GetProjectList( )
{
    wxArrayString ret;
    RheiaProjectRegistrationMap::iterator it = m_RegisteredProjects.begin();

    for( ; it != m_RegisteredProjects.end() ; it++ )
        ret.Add( it->second.name );

    return ret;
}

RheiaProjectRegistration RheiaProjectFactory::FindProjectRegistration(const wxString& name)
{
    RheiaProjectRegistration ret;

    RheiaProjectRegistrationMap::iterator it = m_RegisteredProjects.find( name );

    if ( it == m_RegisteredProjects.end() )
        return ret;

    return it->second;
}
