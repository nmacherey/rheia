#include "Tuto1MainFrame.h"
#include "PyFileManager.h"
#include "PyConsoleManager.h"
#include "PythonFileHandler.h"
#include "CppFileHandler.h"

#include <wx/xrc/xmlres.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/dcclient.h>
#include <wx/statusbr.h>
#include <wx/msgdlg.h>
#include <wx/bmpbuttn.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <wx/dirdlg.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/imaglist.h>

#include <iostream>

#include <RheiaManager.h>
#include <RheiaDebug.h>
#include <RheiaAppGlobals.h>
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaPluginManager.h>
#include <RheiaMenuManager.h>
#include <RheiaEnvironementManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaApplicationConfigurationDialog.h>
#include <RheiaEnvVarsConfigurationDialog.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaWorkspaceLoader.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaLeftPaneManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaLogger.h>
#include <RheiaInfoPaneManager.h>
#include <RheiaProfileManager.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaWorkspace.h>
#include <RheiaProject.h>
#include <RheiaProjectLoader.h>
#include <RheiaProjectCreationDlg.h>
#include <RheiaProjectCreationWizard.h>
#include <RheiaGlobals.h>
#include <RheiaAppGlobals.h>
#include <RheiaInfoWindow.h>
#include <RheiaEvents.h>
#include <RheiaWizardPageBase.h>
#include <RheiaWizardManager.h>
#include <RheiaConfigurationPathsDialog.h>
#include <RheiaAboutDialog.h>
#include <RheiaException.h>
#include <RheiaPackageDBManager.h>
#include <RheiaPackageManager.h>
#include <RheiaEventsManager.h>
#include <RheiaPackageManagementDialog.h>

Tuto1MainFrame::Tuto1MainFrame(wxWindow* parent,
       wxWindowID id,
       const wxString& title,
       const wxPoint& pos,
       const wxSize& size,
       long style):
       RheiaManagedFrame(parent, id, title, pos, size, style)
{
	RheiaDebug::Log( wxT("Starting the frame...") );
    BuildMenu();
	
	RheiaDebug::Log( wxT("Building the Aui") );
    /* First build the aui components */
    BuildAui();

    PyFileManager::PushHandler( new PythonFileHandler );
    PyFileManager::PushHandler( new CppFileHandler );
    PyFileManager::Get(this)->BuildMenu( m_menuBar );

    /* build the info window */
    wxAuiNotebook* book = RheiaInfoPaneManager::Get(this)->CreateWindow(this);
    RheiaInfoPaneManager::Get(this)->BuildMenu( m_menuBar );

    m_layout->AddPane( book , wxAuiPaneInfo().
                            Name(wxT("InfoPane")).Caption(_("Information")).
                            BestSize(600,300).MinSize(wxSize(400,300)).//PinButton(true).Floatable(false).
                            Left().Layer(0));

    PyConsoleManager* cmgr = PyConsoleManager::Get(this);
    RheiaInfoPaneManager::Get(this)->AddPage(wxT("Python console"), cmgr);

    BuildStatusBar();

    /* Displays a welcome message in the status bar */
#if wxUSE_STATUSBAR
    SetStatusText(_("Welcome to Rheia !"));
#endif // wxUSE_STATUSBAR

    LoadLayout();
    m_layout->Update();
}

Tuto1MainFrame::~Tuto1MainFrame()
{
}
