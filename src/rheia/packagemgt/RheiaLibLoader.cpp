/**
*   @file RheiaLibLoader.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	25-November-2009
*	@version 0.0.2
*/
#include <RheiaLibLoader.h>

/** Global instance for the RheiaLibLoader */
template<> RheiaLibLoader* Mgr<RheiaLibLoader>::instance = 0;
/** Global instance for the RheiaLibLoader */
template<> bool  Mgr<RheiaLibLoader>::isShutdown = false;

RheiaLibLoader::RheiaLibLoader()
{

}

RheiaLibLoader::~RheiaLibLoader()
{
    if (!RheiaManager::IsAppShuttingDown())
        Cleanup();
}

RheiaDynamicLibrary* RheiaLibLoader::LoadLibrary(const wxString& filename)
{
    wxString libname = wxFileName( filename ).GetName() ;

    RheiaDynamicLibraryMap::iterator it = m_libraries.find(libname);

    // if the lib exists simply return its reference
    if (it != m_libraries.end())
        return &(it->second);

    // else we have to create a new library
    RheiaDynamicLibrary library;
    library.name = libname;
    library.path = filename;
    library.lib = new wxDynamicLibrary;
    library.lib->Load( filename , wxDL_GLOBAL | wxDL_NOW  );

    m_libraries[libname] = library;
    // finally add the library in the library list

    return &(m_libraries[libname]);
}

bool RheiaLibLoader::RemoveLibrary(wxDynamicLibrary* lib)
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.begin();

    for ( ; it != m_libraries.end(); ++it)
    {
        RheiaDynamicLibrary& library = it->second;
        if (library.lib == lib)
        {
            if (!RheiaManager::IsAppShuttingDown())
                delete library.lib;

            m_libraries.erase(it);
            return true;
        }
    }

    return false;
}

bool RheiaLibLoader::RemoveLibrary(RheiaDynamicLibrary* lib)
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.begin();

    for ( ; it != m_libraries.end(); ++it)
    {
        RheiaDynamicLibrary& library = it->second;
        if (library.lib == lib->lib)
        {
            if (!RheiaManager::IsAppShuttingDown())
                delete library.lib;

            m_libraries.erase(it);
            return true;
        }
    }

    return false;
}

bool RheiaLibLoader::RemoveLibrary(const wxString& name)
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.find(name);

    if( it == m_libraries.end() )
        return false;

    RheiaDynamicLibrary& library = it->second;

    if (!RheiaManager::IsAppShuttingDown())
        delete library.lib;

    m_libraries.erase(it);
    return true;
}

bool RheiaLibLoader::Exists( wxDynamicLibrary* lib )
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.begin();

    for ( ; it != m_libraries.end(); ++it)
    {
        RheiaDynamicLibrary& library = it->second;
        if (library.lib == lib)
            return true;
    }

    return false;
}

bool RheiaLibLoader::Exists( RheiaDynamicLibrary* lib )
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.begin();

    for ( ; it != m_libraries.end(); ++it)
    {
        RheiaDynamicLibrary& library = it->second;
        if (library.lib == lib->lib)
            return true;
    }

    return false;
}

bool RheiaLibLoader::Exists( const wxString& name )
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.find(name);

    if( it == m_libraries.end() )
        return false;

    return true;
}

RheiaDynamicLibrary* RheiaLibLoader::FindLibrary(const wxString& name)
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.find(name);

    if( it == m_libraries.end() )
        return NULL;

    return &(it->second);
}

RheiaDynamicLibrary* RheiaLibLoader::FindLibrary(wxDynamicLibrary* lib)
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.begin();

    for ( ; it != m_libraries.end(); ++it)
    {
        RheiaDynamicLibrary& library = it->second;
        if (library.lib == lib)
            return &(it->second);
    }

    return NULL;
}

void RheiaLibLoader::Cleanup()
{
    RheiaDynamicLibraryMap::iterator it = m_libraries.begin();

    for ( ; it != m_libraries.end(); ++it)
    {
        RheiaDynamicLibrary& library = it->second;

        if (!RheiaManager::IsAppShuttingDown())
            delete library.lib;
    }

    m_libraries.clear();
}


