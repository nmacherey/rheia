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

///* Returns the Left pane manager */
//RheiaWorkspaceManager* RheiaManager::GetWorkspaceManager(RheiaManagedFrame* parent)
//{
//    return RheiaWorkspaceManager::Get(parent);
//}

/* Returns the center pane manager */
RheiaCenterPaneManager* RheiaManager::GetCenterPaneManager(RheiaManagedFrame* parent)
{
    return RheiaCenterPaneManager::Get(parent);
}

///* Returns the bottom pane manager */
//RheiaLoggerManager* RheiaManager::GetLoggerManager(RheiaManagedFrame* parent)
//{
//    return RheiaLoggerManager::Get(parent);
//}

///* Returns the bottom pane manager */
//RheiaPluginManager* RheiaManager::GetPluginManager(void)
//{
//    return RheiaPluginManager::Get();
//}

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
