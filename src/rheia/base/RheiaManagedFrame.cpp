/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaManagedFrame.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	29-January-2010
*	@version 0.0.2
*/
#include <RheiaManagedFrame.h>
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
#include <RheiaAppGlobals.h>
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaEnvironementManager.h>
#include <RheiaMenuManager.h>
#include <RheiaProfileManager.h>
#include <RheiaGlobals.h>
#include <RheiaInfoWindow.h>
#include <RheiaEvents.h>
#include <RheiaAboutDialog.h>
#include <RheiaException.h>
#include <RheiaEventsManager.h>
#include <RheiaEventFrame.h>
#include <RheiaDebug.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaManagedFrame,wxFrame)

/*! id comming from the main menu bar ressource for exiting the application*/
int idFileExit = XRCID("idFileExit");
/*! id comming from the main menu bar ressource for exiting the application*/
int idFileClose = XRCID("idFileClose");
/*! id comming from the main menu bar ressource for viewing the status bar*/
int idViewStatusbar = XRCID("idViewStatusbar");
/*! id comming from the main menu bar ressource for viewing in full screen */
int idViewFullScreen = XRCID("idViewFullScreen");

BEGIN_EVENT_TABLE(RheiaManagedFrame, wxFrame)
    EVT_MENU( idFileExit, RheiaManagedFrame::OnFileExit )
    EVT_MENU( idFileClose, RheiaManagedFrame::OnFileClose )
    EVT_MENU( wxID_ABOUT , RheiaManagedFrame::OnAboutRheia )

    /* EVENT CLOSING THE FRAME AND THE APPLICATION */
    EVT_CLOSE( RheiaManagedFrame::OnExitApp )

    EVT_UPDATE_UI(idViewStatusbar, RheiaManagedFrame::OnViewMenuUpdateUI)
    EVT_UPDATE_UI(idViewFullScreen, RheiaManagedFrame::OnViewMenuUpdateUI)

    EVT_MENU( idViewStatusbar, RheiaManagedFrame::OnToggleStatusBar )
    EVT_MENU( idViewFullScreen, RheiaManagedFrame::OnToggleFullScreen )
END_EVENT_TABLE()

RheiaManagedFrame::RheiaManagedFrame(wxWindow* parent,
       wxWindowID id,
       const wxString& title,
       const wxPoint& pos,
       const wxSize& size,
       long style):
       wxFrame(parent, id, title, pos, size, style),
       m_layout(NULL),
       m_closeOnly(true)
{
    m_layout = new wxAuiManager(this);
}

RheiaManagedFrame::~RheiaManagedFrame()
{
    m_layout->UnInit();
}

void RheiaManagedFrame::LoadLayout()
{
    if( m_layout == NULL )
        RheiaThrow( wxT("RheiaManagedFrame::Error: Trying to load layout without initializing the layout manager for this frame") );

    RheiaConfigurationManager* CfgMgr = RheiaProfileManager::Get()->GetActiveProfileManager();
    wxString LayoutName = wxT("default");
    CfgMgr->ReadLayout( wxT("/frame/layout") , m_layout , LayoutName );
    m_layout->Update();
}

void RheiaManagedFrame::RegisterEvents()
{
    //RheiaEventsManager* emgr = RheiaEventsManager::Get();
}

void RheiaManagedFrame::BuildStatusBar()
{
#if wxUSE_STATUSBAR
    wxCoord width[16]; // 16 max

    wxClientDC dc(this);
    wxFont font = dc.GetFont();
    int h;
    int num = 0;

    width[num++] = -1; // main field
    dc.GetTextExtent(_(" WORKSPACE-1234567812345678 "), &width[num++], &h);
    dc.GetTextExtent(_(" PROJECT-1234567812345678 "), &width[num++], &h);

    CreateStatusBar(num);
    SetStatusWidths(num, width);

    RheiaStatusBarManager::Get(this)->Update();

#endif // wxUSE_STATUSBAR
}

void RheiaManagedFrame::BuildMenu( )
{
    RheiaMenuManager::Get(this);
    m_menuBar = RheiaMenuManager::Get(this)->GetMainMenuBar();
}

void RheiaManagedFrame::BuildAui(void)
{
    wxSize clientsize = GetClientSize();
    RheiaCenterPaneManager::Get(this)->CreateWindow(this);

    m_layout->AddPane( RheiaCenterPaneManager::Get(this)->GetNoteBook() , wxAuiPaneInfo().
                            Name(wxT("MainPane")).Caption(_("MainBook")).
                            BestSize(wxSize(600, 600)).//MinSize(wxSize(100,100)).
                            CenterPane());

    RheiaCenterPaneManager::Get(this)->BuildMenu( m_menuBar );
    RheiaEnvironementManager::Get()->BuildMenu(this,m_menuBar);

    SetToolBar(0);

    RheiaToolBarManager::Get(this)->GetToolBar();

    m_layout->SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_TRANSPARENT_DRAG);
    m_layout->Update();

    OnBuildAui();
}

void RheiaManagedFrame::OnExitApp( wxCloseEvent &event )
{
	RheiaDebug::Log(wxT("request closing app, sending RheiaEVT_APP_START_SHUTDOWN") );
    RheiaEvent evt(RheiaEVT_APP_START_SHUTDOWN);
    RheiaEventsManager::Get()->ProcessEvent( evt );
	
	RheiaDebug::Log(wxT("Saving frame's configuration") );
    RheiaConfigurationManager* CfgMgr = RheiaProfileManager::Get()->GetActiveProfileManager();

    try
    {
        CfgMgr->WriteFrameInfo( wxT("/MainFrame") , this );
    }
    catch( RheiaException& err )
    {
        err.ShowErrorMessage();
    }

    wxArrayString LayoutVal;
    LayoutVal.Add( m_layout->SavePerspective() );

    wxArrayString LayoutName;
    LayoutName.Add( wxT("default" ) );
	
	RheiaDebug::Log(wxT("Saving layout") );
    CfgMgr->WriteLayout( wxT("/MainFrame/LayoutManager") , m_layout,  LayoutName , LayoutVal );

    m_canClose = true;
	
	RheiaDebug::Log(wxT("Sending frame's RheiaEVT_FRAME_CLOSING") );
    RheiaFrameEvent evt2( RheiaEVT_FRAME_CLOSING , -1 , this );
	
	/*wxEvtHandler* hd = PopEventHandler();
	while( hd && hd != GetEventHandler() )
	{
		RemoveEventHandler(hd);
		hd = PopEventHandler();
	}*/
		
    /*** the worst solution ever found */
	evt2.Skip(true);
    GetEventHandler()->ProcessEvent( evt2 );
	RheiaDebug::Log(wxT("Sending frame's RheiaEVT_FRAME_CLOSING") );
    RheiaEventsManager::Get()->ProcessEvent( evt2 );

    if( !m_canClose )
    {
		RheiaDebug::Log(wxT("Something wrong with the close") );
        m_closeOnly = true;
        event.Veto();
        return;
    }
	
	RheiaDebug::Log(wxT("Calling destroy") );
    Destroy();
	RheiaDebug::Free();
}

void RheiaManagedFrame::OnAboutRheia( wxCommandEvent& WXUNUSED(event) )
{
    RheiaAboutDialog dialog( this );
    dialog.ShowModal();
}

/* Used when we act on the view menu */
void RheiaManagedFrame::OnViewMenuUpdateUI( wxUpdateUIEvent& event )
{
    if (RheiaManager::isappShuttingDown())
    {
        event.Skip();
        return;
    }

    wxMenuBar* mbar = GetMenuBar();
    mbar->Check(idViewStatusbar, GetStatusBar() && GetStatusBar()->IsShown());
    mbar->Check(idViewFullScreen, IsFullScreen());

    event.Skip();
}

void RheiaManagedFrame::OnToggleStatusBar( wxCommandEvent &WXUNUSED(event) )
{
    Freeze();
    wxStatusBar* sb = GetStatusBar();
    if (sb)
    {
        sb->Hide();
        SetStatusBar(0);
        sb->Destroy();
    }
    else
    {
        BuildStatusBar();
        GetStatusBar()->SetStatusText(wxT("Rheia Framework"));
        RheiaStatusBarManager::Get(this)->Update();
    }
    Thaw();
}

void RheiaManagedFrame::OnToggleFullScreen( wxCommandEvent &WXUNUSED(event) )
{
    ShowFullScreen( !IsFullScreen(), wxFULLSCREEN_NOTOOLBAR// | wxFULLSCREEN_NOSTATUSBAR
                    | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION );
}

/* Callback called when requesting the exit of the application, generates an EVT_CLOSE in order to centralize with
other close controls */
void RheiaManagedFrame::OnFileExit( wxCommandEvent& WXUNUSED(event) )
{
    m_closeOnly = false;
    Close(true);
}

/* Callback called when requesting the exit of the application, generates an EVT_CLOSE in order to centralize with
other close controls */
void RheiaManagedFrame::OnFileClose( wxCommandEvent& WXUNUSED(event) )
{
    m_closeOnly = true;
    Close(true);
}

