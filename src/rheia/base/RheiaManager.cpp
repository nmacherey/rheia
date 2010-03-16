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
#include <RheiaMenuManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaProfileManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEnvironementManager.h>
#include <RheiaPersonalityManager.h>
#include <RheiaProfileManager.h>
#include <RheiaXmlManager.h>
#include <RheiaEventsManager.h>

/*! Global instance of the manager */
static RheiaManager *instance = 0;

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
	
	RheiaDebug::Log( wxT("Before deleting..." ) );
    /** Finally Free all Rheia Managers */
    RheiaCenterPaneManager::Free();
    RheiaMenuManager::Free();
    RheiaMenuFunctorManager::Free();
    RheiaToolBarManager::Free();
    RheiaStatusBarManager::Free();
    RheiaPersonalityManager::Free();
    RheiaProfileManager::Free();
    RheiaEnvironementManager::Free();
    RheiaConfigurationPattern::Free(); // only terminate config at the very last moment
    RheiaXmlManager::Free();
	RheiaDebug::Log( wxT("Before deleting..." ) );
	RheiaDebug::Free();
}

/***********************************************************************************************
										STATIC METHODS
***********************************************************************************************/

/* Get Method, use GmManger::Get() instead
*	This method returns the global object instanciated in the RheiaManager.cpp
*	The aim is to provide the same object to all users
*/
RheiaManager* RheiaManager::Get( void )
{
    if( instance == 0 )
        instance = new RheiaManager;
    return instance;
}

/* Never, EVER, call this function! It is the last function called on shutdown.... */
void RheiaManager::Free()
{
    if( instance != 0 )
        delete instance;
}

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
