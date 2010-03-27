/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEventFrame.h>

#include <wx/toolbar.h>
#include <wx/aui/auibar.h>
#include <wx/msgdlg.h>
#include <wx/xrc/xmlres.h>
#include <wx/frame.h>
#include <wx/string.h>
#include <wx/choice.h>
#include <wx/menu.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>::MgrNsMap locmap;
    int idViewToolMain = XRCID("idViewToolMain");
}

BEGIN_EVENT_TABLE( RheiaToolBarManager , wxEvtHandler )
    EVT_UPDATE_UI(idViewToolMain, RheiaToolBarManager::OnToolsUpdateUI)
    EVT_MENU(idViewToolMain, RheiaToolBarManager::OnSelectToolbarMenu)
    //EVT_FRAME_CLOSING(RheiaToolBarManager::OnCloseParent)
END_EVENT_TABLE()

/*! Global instance for the RheiaToolBarManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaToolBarManager>::m_ns = locmap;

RheiaToolBarManager::RheiaToolBarManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_parent(parent)
{
	wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcToolbarName = _T("main_toolbar");

	/*! @todo :	Here the toolbar size is not managed accordingly to the different systems
	*			this is to do
	*/
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") );
	wxSize size = wxSize(24,24);
	m_toolbar = new wxAuiToolBar(m_parent, -1, wxDefaultPosition, wxSize(24,24), wxAUI_TB_GRIPPER|wxAUI_TB_HORZ_LAYOUT );
    m_toolbar->SetToolBitmapSize(size);

    m_toolbar->AddTool( 
        idFileExit , 
        _("Exit") , 
        RheiaLoadBitmap( path + wxT("#zip:close_24.png") ), 
        wxNullBitmap, 
        wxITEM_NORMAL, 
        _("Exit from the application"), 
        wxEmptyString,
        NULL ); 

    m_toolbar->AddTool( 
        idFileFrameKill , 
        _("Close") , 
        RheiaLoadBitmap( path + wxT("#zip:close_24.png") ), 
        wxNullBitmap, 
        wxITEM_NORMAL, 
        _("Close the current frame"), 
        wxEmptyString,
        NULL ); 

    m_toolbar->Realize();
    m_toolbar->SetInitialSize();

	m_parent->PushEventHandler( this );

	wxAuiManager* m_layout = m_parent->GetLayoutManager();

	// add toolbars in docking system
    m_layout->AddPane(m_toolbar, wxAuiPaneInfo().
                           Name(wxT("MainToolbar")).
                           ToolbarPane().Top().Layer(1));

    m_auiToolbars[wxT("main")] = m_toolbar;
    m_auiToolIds[m_toolbar] = idViewToolMain;
	
	m_parent->Connect( RheiaEVT_FRAME_CLOSING , RheiaFrameEventHandler(RheiaToolBarManager::OnCloseParent) , NULL , this );
    m_index = 0;
}

RheiaToolBarManager::~RheiaToolBarManager()
{

}

void RheiaToolBarManager::OnCloseParent(RheiaFrameEvent& event)
{
    m_parent->RemoveEventHandler(this);
    event.Skip(true);
}

void RheiaToolBarManager::AddToolBar( const wxString& name , wxToolBar* toolbar )
{
    wxToolBarArray::iterator it = m_toolbars.find(name);
    if( it != m_toolbars.end() )
        return;

    m_toolbars[name] = toolbar;
    m_index++;

    int layer = m_index / 3 + 1;
    int pos = (m_index % 3);

    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    m_layout->AddPane( toolbar, wxAuiPaneInfo().
                           Name(name).
                           ToolbarPane().Top().Layer(layer).
						   Position(pos) );
						   
    wxMenuBar* menuBar = m_parent->GetMenuBar();
    int idx = menuBar->FindMenu(wxT("View"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        wxMenuItem* item = mnEdit->FindItem(XRCID("idViewToolbars"));
        wxMenu* tbmenu = item->GetSubMenu();

        m_toolIds[toolbar] = wxNewId();
        tbmenu->AppendCheckItem(m_toolIds[toolbar],name,wxT("View toolbar ") + name )->Check(true);
        Connect( m_toolIds[toolbar] , wxEVT_COMMAND_MENU_SELECTED , wxCommandEventHandler(RheiaToolBarManager::OnSelectToolbarMenu) );
        Connect( m_toolIds[toolbar] , wxEVT_UPDATE_UI , wxUpdateUIEventHandler(RheiaToolBarManager::OnToolsUpdateUI) );

    }

    m_layout->Update();
}

void RheiaToolBarManager::AddToolBar( const wxString& name , wxAuiToolBar* toolbar )
{
    wxAuiToolBarArray::iterator it = m_auiToolbars.find(name);
    if( it != m_auiToolbars.end() )
        return;

    m_auiToolbars[name] = toolbar;
    m_index++;

    int layer = m_index / 3 + 1;
    int pos = (m_index % 3);

    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    m_layout->AddPane( toolbar, wxAuiPaneInfo().
                           Name(name).
                           ToolbarPane().Top().Layer(layer).
						   Position(pos) );
						   
    wxMenuBar* menuBar = m_parent->GetMenuBar();
    int idx = menuBar->FindMenu(wxT("View"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        wxMenuItem* item = mnEdit->FindItem(XRCID("idViewToolbars"));
        wxMenu* tbmenu = item->GetSubMenu();

        m_auiToolIds[toolbar] = wxNewId();
        tbmenu->AppendCheckItem(m_auiToolIds[toolbar],name,wxT("View toolbar ") + name )->Check(true);
        Connect( m_auiToolIds[toolbar] , wxEVT_COMMAND_MENU_SELECTED , wxCommandEventHandler(RheiaToolBarManager::OnSelectToolbarMenu) );
        Connect( m_auiToolIds[toolbar] , wxEVT_UPDATE_UI , wxUpdateUIEventHandler(RheiaToolBarManager::OnToolsUpdateUI) );

    }

    m_layout->Update();
}

void RheiaToolBarManager::RemoveToolBar( const wxString& name )
{
    wxToolBarArray::iterator it = m_toolbars.find(name);
    if( it != m_toolbars.end() )
    {
        wxToolBar* toolbar = it->second;
        wxMenuBar* menuBar = m_parent->GetMenuBar();
        int idx = menuBar->FindMenu(wxT("View"));
        if( idx != wxNOT_FOUND )
        {
            wxMenu* mnEdit = menuBar->GetMenu( idx );
            wxMenuItem* item = mnEdit->FindItem(XRCID("idViewToolbars"));
            wxMenu* tbmenu = item->GetSubMenu();

            RheiaToolMenuIdMap::iterator tit = m_toolIds.find(toolbar);
            tbmenu->Delete(m_toolIds[toolbar]);
            m_toolIds.erase(tit);
        }

        wxAuiManager* m_layout = m_parent->GetLayoutManager();
        m_layout->DetachPane( toolbar );
        toolbar->Destroy();
        m_toolbars.erase(it);

        m_layout->Update();
    }

    wxAuiToolBarArray::iterator ait = m_auiToolbars.find(name);
    if( ait != m_auiToolbars.end() )
    {
        wxAuiToolBar* toolbar = ait->second;
        wxMenuBar* menuBar = m_parent->GetMenuBar();
        int idx = menuBar->FindMenu(wxT("View"));
        if( idx != wxNOT_FOUND )
        {
            wxMenu* mnEdit = menuBar->GetMenu( idx );
            wxMenuItem* item = mnEdit->FindItem(XRCID("idViewToolbars"));
            wxMenu* tbmenu = item->GetSubMenu();

            RheiaAuiToolMenuIdMap::iterator tit = m_auiToolIds.find(toolbar);
            tbmenu->Delete(m_auiToolIds[toolbar]);
            m_auiToolIds.erase(tit);
        }

        wxAuiManager* m_layout = m_parent->GetLayoutManager();
        m_layout->DetachPane( toolbar );
        toolbar->Destroy();
        m_toolbars.erase(it);

        m_layout->Update();
    }
}

void RheiaToolBarManager::OnSelectToolbarMenu(wxCommandEvent& event)
{
    wxMenuBar* menuBar = m_parent->GetMenuBar();
    int idx = menuBar->FindMenu(wxT("View"));
    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        wxMenuItem* item = mnEdit->FindItem(XRCID("idViewToolbars"));
        wxMenu* tbmenu = item->GetSubMenu();

        RheiaToolMenuIdMap::iterator tit = m_toolIds.begin();
        for( ; tit != m_toolIds.end() ; ++tit )
        {
             if( event.GetId() == tit->second )
             {
                if( tbmenu->FindItem(tit->second)->IsChecked() )
                {
                    tbmenu->FindItem(tit->second)->Check(true);
                    m_layout->GetPane(tit->first).Show(true);
                }
                else
                {
                    tbmenu->FindItem(tit->second)->Check(false);
                    m_layout->GetPane(tit->first).Show(false);
                }
                m_layout->Update();
                event.Skip();
                return;
             }
        }

        RheiaAuiToolMenuIdMap::iterator atit = m_auiToolIds.begin();
        for( ; atit != m_auiToolIds.end() ; ++atit )
        {
             if( event.GetId() == atit->second )
             {
                if( tbmenu->FindItem(atit->second)->IsChecked() )
                {
                    tbmenu->FindItem(atit->second)->Check(true);
                    m_layout->GetPane(atit->first).Show(true);
                }
                else
                {
                    tbmenu->FindItem(atit->second)->Check(false);
                    m_layout->GetPane(atit->first).Show(false);
                }
                m_layout->Update();
                event.Skip();
                return;
             }
        }
    }

    m_layout->Update();
    event.Skip();
}

void RheiaToolBarManager::OnToolsUpdateUI( wxUpdateUIEvent& WXUNUSED(event) )
{
    wxMenuBar* mbar = m_parent->GetMenuBar();
    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    mbar->Check(idViewToolMain, m_layout->GetPane(m_toolbar).IsShown() );
    RheiaToolMenuIdMap::iterator tit = m_toolIds.begin();
    for( ; tit != m_toolIds.end() ; ++tit )
        mbar->Check(tit->second, m_layout->GetPane(tit->first).IsShown() );

    RheiaAuiToolMenuIdMap::iterator atit = m_auiToolIds.begin();
    for( ; atit != m_auiToolIds.end() ; ++atit )
        mbar->Check(tit->second, m_layout->GetPane(tit->first).IsShown() );
}


