/**
* @file RheiaXulManager.cpp
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/

#include "RheiaXulManager.h"

#include <wx/image.h>
#include "webcontrol.h"

/** global instance for RheiaXulManager */
template<> RheiaXulManager* Mgr<RheiaXulManager>::instance = 0;
/** global instance for RheiaXulManager */
template<> bool  Mgr<RheiaXulManager>::isShutdown = false;


void RheiaXulManager::Init( const wxString& path )
{
	if( !wxWebControl::InitEngine(path) )
	{
		wxMessageBox("Failed to intialize engine");
	}
}

void RheiaXulManager::AddPluginPath( const wxString& path )
{
	wxWebControl::AddPluginPath(path);
}