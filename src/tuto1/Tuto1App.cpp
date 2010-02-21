#include <Tuto1App.h>
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

#include <RheiaXtraRes.h>
#include <RheiaException.h>
#include <RheiaGlobals.h>
#include <RheiaSplashScreen.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaEnvironementManager.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaEventFrame.h>
#include <RheiaPythonUtils.h>

/************************************************
This is the Source File for Tuto1App

 * Author: Nicolas Macherey
 * Date: 2008.11.6
 ************************************************/
IMPLEMENT_APP(Tuto1App)

BEGIN_EVENT_TABLE(Tuto1App, wxApp)

END_EVENT_TABLE()

bool Tuto1App::OnInit(){
	/** Call basic initializations */
	DoBasicInitializations();

	if( !CheckForSingleInstance() )
		return false;
	
	RheiaConfigurationManager* cmgr = RheiaProfileManager::Get()->GetActiveProfileManager();
	bool showSplash = cmgr->ReadBool( wxT("show_splash") , true );
	
	if( showSplash )
		ShowSplashScreen(RheiaStandardPaths::DataDirectoryGlobal() + wxT("/resource.zip#zip:splash_screen.png") );

	/* Initialize resource */
	if(!InitXRCStuff())
	{
		wxMessageBox(wxT("Resources cannot be loaded properly the application will terminate immediately"),wxT("Rheia : ERROR") );
		return false;
	}

	/* Initialize the Main Frame of the application */
	MainFrame = InitMainFrame();

	/* Setting the window and showing the frame */
	SetTopWindow(MainFrame);
    MainFrame->Show();

    try
    {
        cmgr->ReadFrameInfo( wxT("/MainFrame") , MainFrame );
    }
    catch(RheiaException& err)
    {

    }
    HideSplashScreen();
	
    StartUpFinalStep();
    return true;
}

/* Membership function for initializing the main frame */
Tuto1MainFrame *Tuto1App::InitMainFrame(void)
{
	Tuto1MainFrame *frame = new Tuto1MainFrame(NULL,
		wxID_ANY,
		_T("Rheia"),wxDefaultPosition,wxSize(1200,600));

	return frame;
}


