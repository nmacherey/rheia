/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#include <RheiaManager.h>

#include <wx/xrc/xmlres.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/msgdlg.h>
#include <wx/aui/aui.h>

#include <RheiaEvents.h>
#include <RheiaDebug.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaCenterPageManager.h>
#include <RheiaMenuManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaProfileManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaConfigurationToolsManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEnvironementManager.h>
#include <RheiaPersonalityManager.h>
#include <RheiaProfileManager.h>
#include <RheiaXmlManager.h>
#include <RheiaInfoPaneManager.h>
#include <RheiaLeftPaneManager.h>
#include <RheiaXulManager.h>
#include <RheiaEventsManager.h>

/*! Global instance of the manager */
/*! declare global instance for RheiaManager */
template<> RheiaManager* Singleton<RheiaManager>::instance = 0;
/*! declare global isShutdown variable for RheiaManager */
template<> bool  Singleton<RheiaManager>::isShutdown = false;

/***********************************************************************************************
										CONSTRUCTORS
***********************************************************************************************/
/* Default constructor...
*	Please do not derive this class by using an other constructor,
*	as a lot of its members are static !
*
*/
RheiaManager::RheiaManager()
{

}

/* Destructor, freeing memory */
RheiaManager::~RheiaManager()
{

}

void RheiaManager::Close()
{
    appShuttingDown = true;
	
    RheiaEventsManager::Get()->RemoveAllEventMethods();
	
	/** free components */
	for( unsigned int i = 0; i < m_components.size() ; ++i ) {
		m_components[i]->DoCleanUp();
		delete m_components[i];
	}
	
	m_components.clear();
	
    /** Finally Free all Rheia Managers */
	RheiaConfigurationToolsManager::Free();
	RheiaXulManager::Free();
    RheiaCenterPaneManager::Free();
	RheiaCenterPageManager::Free();
	RheiaInfoPaneManager::Free();
	RheiaLeftPaneManager::Free();
    RheiaMenuManager::Free();
    RheiaMenuFunctorManager::Free();
    RheiaToolBarManager::Free();
    RheiaStatusBarManager::Free();
    RheiaPersonalityManager::Free();
    RheiaProfileManager::Free();
    RheiaEnvironementManager::Free();
    RheiaConfigurationPattern::Free(); // only terminate config at the very last moment
    RheiaXmlManager::Free();
	RheiaDebug::Free();
	
    RheiaEventsManager::Get()->RemoveAllEventMethods();
	RheiaEventsManager::Free();
}

/***********************************************************************************************
										STATIC METHODS
***********************************************************************************************/

bool RheiaManager::LoadResource(const wxString& file)
{
    wxString resourceFile = RheiaStandardPaths::data_dir_global + _T("/") + file;
    wxString memoryFile = _T("memory:") + file;

    if(wxFile::Access(resourceFile, wxFile::read) == false)
        return false;

    wxFile f(resourceFile, wxFile::read);
    char *buf = 0;

    try
    {
        size_t len = f.Length();
        buf = new char[len];
        f.Read(buf, len);
        {
            wxMemoryFSHandler::AddFile(file, buf, len);
        }
        wxXmlResource::Get()->Load(memoryFile);
        delete[] buf;
        return true;
    }
    catch (...)
    {
        delete[] buf;
        return false;
    }
}

/* Returns the center pane manager */
RheiaCenterPaneManager* RheiaManager::GetCenterPaneManager(RheiaManagedFrame* parent)
{
    return RheiaCenterPaneManager::Get(parent);
}

/* Returns the profile manager */
RheiaProfileManager* RheiaManager::GetProfileManager(void)
{
    return RheiaProfileManager::Get();
}

/* Returns the menu manager */
RheiaMenuManager* RheiaManager::GetMenuManager(RheiaManagedFrame* parent)
{
    return RheiaMenuManager::Get(parent);
}

/* Returns the toolbar manager */
RheiaToolBarManager* RheiaManager::GetToolBarManager(RheiaManagedFrame* parent)
{
    return RheiaToolBarManager::Get(parent);
}

/* Returns the statusbar manager */
RheiaStatusBarManager* RheiaManager::GetStatusBarManager(RheiaManagedFrame* parent)
{
    return RheiaStatusBarManager::Get(parent);
}

/* Returns the configuration manager */
RheiaConfigurationManager* RheiaManager::GetConfigurationManager(const wxString &name_space)
{
    return RheiaConfigurationPattern::Get()->Build(name_space);
}

void RheiaManager::AddonToolBar(wxToolBar* toolBar,wxString resid)
{
    if(!toolBar)
        return;
    if( !wxXmlResource::Get()->LoadObject(toolBar,NULL,resid,_T("wxToolBarAddOn")) )
    {
        wxMessageBox( _("Error cannot load ressource") , _("Error Toolbar") );
        return;
    }
}

bool RheiaManager::appShuttingDown = false;
