/**
*   @file RheiaAppBase.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-February-2010
*/

#include "RheiaAppBase.h"
#include "RheiaManager.h"
#include "RheiaXtraRes.h"
#include "RheiaStandardPaths.h"
#include "RheiaSplashScreen.h"
#include "RheiaProfileManager.h"
#include "RheiaException.h"
#include "RheiaEnvironementManager.h"
#include "RheiaConfigurationManager.h"
#include "RheiaEventsManager.h"
#include "RheiaEvents.h"
#include "RheiaDebug.h"

#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_wizrd.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/clipbrd.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/cmdline.h>
#include <wx/utils.h>
#include <wx/snglinst.h>


bool RheiaAppBase::DoBasicInitializations()
{
    /* Enables wxLogging for the application */
#ifndef RHEIA_DEBUG
    wxLog::EnableLogging(true);
#endif

#ifdef LINUX
    setlocale(LC_ALL,"C");
#endif

	/* Fushing the clip board */
	wxTheClipboard->Flush();

	/* Initialize File system handler for zip and memory FS */
	wxFileSystem::AddHandler(new wxZipFSHandler);
    wxFileSystem::AddHandler(new wxMemoryFSHandler);
	/* Initialising all image handlers */
    wxInitAllImageHandlers();
	/* Initialising Xml ressource handler */
    wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->AddHandler( new wxToolBarAddOnXmlHandler );

	m_appName = GetAppName();
	
	RheiaManager::Get();
	RheiaStandardPaths::InitPaths(m_appName);

	m_singleInstanceChecker = 0;
	return true;
}

bool RheiaAppBase::CheckForSingleInstance()
{
	m_singleInstanceChecker = 0;

    try
    {
        if(RheiaProfileManager::Get()->GetActiveProfileManager()->ReadBool(_T("/environment/single_instance"), true))
        {
            const wxString name = m_appName + wxT("-") + wxGetUserId();
            m_singleInstanceChecker = new wxSingleInstanceChecker(name, RheiaStandardPaths::TempDirectory());
			
            if (m_singleInstanceChecker->IsAnotherRunning())
            {
                wxMessageBox(wxT("Another program instance is already running.\nRheia is currently configured to only allow one running instance.\n\nYou can access this Setting under the menu item 'Environment Settings'."),
                            wxT("Rheia Framework"), wxOK | wxICON_ERROR);
							
                return false;
            }
        }
    }catch(RheiaException& err)
    {
        err.ShowErrorMessage();
    }
	
	return true;
}

void RheiaAppBase::ShowSplashScreen( const wxString& path )
{
	wxBitmap bmp = RheiaLoadBitmap ( path );
	m_splash = new RheiaSplashScreen(bmp);
}

void RheiaAppBase::HideSplashScreen()
{
	if (m_splash)
	{
		m_splash->Destroy();
		m_splash = NULL;
	}
}

bool RheiaAppBase::InitXRCStuff()
{
	// Try to load all resources from RheiaManager and return
	if (!RheiaManager::LoadResource(wxT("resource.zip")))
    {
        return false;
    }
    return true;
}

int RheiaAppBase::OnRun()
{
	try
    {
        int retval = wxApp::OnRun();
        return retval;
    }
    catch (...)
    {
        wxSafeShowMessage(wxT("Exception"), wxT("Unknown exception was raised. The application will terminate immediately..."));
    }
    // if we reached here, return error
    return -1;
}

/* Callback used for ending the application */
int RheiaAppBase::OnExit()
{
	/* Flushing the clipboard */
    wxTheClipboard->Flush();
	
	OnPreManagerDestroy();
	/* Freeing global manager instance at the totally end of the application */
	RheiaDebug::Log(wxT("Freeing Rheia Manager") );
	RheiaManager::Get()->Close();
    RheiaManager::Free();
    return 0;
}

void RheiaAppBase::StartUpFinalStep()
{
	RheiaEvent event(RheiaEVT_APP_STARTUP_DONE);
    RheiaEventsManager::Get()->ProcessEvent( event );
}

RheiaAppBase::~RheiaAppBase()
{
	if( m_singleInstanceChecker )
		delete m_singleInstanceChecker;
}