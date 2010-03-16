/**
* @file RheiaXulManager.cpp
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/

#include "RheiaXulManager.h"
#include "RheiaStandardPaths.h"

#include <wx/image.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>  
#include <wx/dir.h>

#include "webcontrol.h"

/** global instance for RheiaXulManager */
template<> RheiaXulManager* Singleton<RheiaXulManager>::instance = 0;
/** global instance for RheiaXulManager */
template<> bool  Singleton<RheiaXulManager>::isShutdown = false;


void RheiaXulManager::Init( const wxString& path )
{
	m_initialized = true;
	if( !wxWebControl::InitEngine(path) )
		m_initialized = false;
}

void RheiaXulManager::AddPluginPath( const wxString& path )
{
	wxWebControl::AddPluginPath(path);
}


wxString RheiaXulManager::FindXulRunner(const wxString& xulrunner_dirname)
{
    // get the location of this executable
    wxString exe_path = wxStandardPaths::Get().GetExecutablePath();
    wxString path_separator = wxFileName::GetPathSeparator();
    exe_path = exe_path.BeforeLast(path_separator[0]);
    exe_path += path_separator;

    wxString path;

    // first, check <exe_path>/<xulrunner_path>
    path = exe_path + xulrunner_dirname;
    if (wxDir::Exists(path))
        return path;

    // next, check <exe_path>/../<xulrunner_path>
    path = exe_path + wxT("..") + path_separator + xulrunner_dirname;
    if (wxDir::Exists(path))
        return path;

    // finally, check <exe_path>/../../<xulrunner_path>
    path = exe_path + wxT("..") + path_separator + wxT("..") + path_separator + xulrunner_dirname;
    if (wxDir::Exists(path))
        return path;

    return wxEmptyString;
}