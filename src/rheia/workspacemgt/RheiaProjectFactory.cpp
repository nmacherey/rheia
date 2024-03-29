/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
template<> RheiaProjectFactory* Singleton<RheiaProjectFactory>::instance = 0;
/*! Global isShutdown for the Menu manager */
template<> bool  Singleton<RheiaProjectFactory>::isShutdown = false;

namespace {
	class ProjectCleaner : public RheiaComponentCleaner
	{
	public :
		virtual void DoCleanUp(){
			RheiaProjectFactory::Free();
		}
	};
	
	REGISTER_COMPONENT_CLEANER(ProjectCleaner);
}

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

bool RheiaProjectFactory::UnregisterProject( const wxString& name )
{
	RheiaProjectRegistrationMap::iterator it = m_RegisteredProjects.find( name );

    if ( it == m_RegisteredProjects.end() )
        return false;
		
	m_RegisteredProjects.erase(it);
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
