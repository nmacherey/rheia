#include <RheiaToolBarManager.h>
#include <RheiaStatusBarManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEventFrame.h>

#include <wx/toolbar.h>
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
	/******************************************************************************************************************
	*	First get build the toolbar from the resources
	******************************************************************************************************************/
	wxXmlResource *myres = wxXmlResource::Get();

	wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcToolbarName = _T("main_toolbar");

	/*! @todo :	Here the toolbar size is not managed accordingly to the different systems
	*			this is to do
	*/
	wxSize size = wxSize(24,24);
	m_toolbar = new wxToolBar(m_parent, -1, wxDefaultPosition, wxSize(24,24), wxTB_FLAT | wxTB_NODIVIDER);

    m_toolbar->SetToolBitmapSize(size);
    RheiaManager::Get()->AddonToolBar(m_toolbar,xrcToolbarName);

    m_toolbar->Realize();
    m_toolbar->SetInitialSize();

	/******************************************************************************************************************
	*	Finally Push me as event handler in the main frame, so that we can receive the event from the toolbar
	******************************************************************************************************************/
	m_parent->PushEventHandler( this );

	wxAuiManager* m_layout = m_parent->GetLayoutManager();

	// add toolbars in docking system
    m_layout->AddPane(m_toolbar, wxAuiPaneInfo().
                           Name(wxT("MainToolbar")).
                           ToolbarPane().Top().Layer(1));

    m_toolbars[wxT("main")] = m_toolbar;
    m_toolIds[m_toolbar] = idViewToolMain;
	
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

    int layer = m_index / 5 + 1;
    int pos = m_index % 5;

    wxAuiManager* m_layout = m_parent->GetLayoutManager();
    m_layout->AddPane( toolbar, wxAuiPaneInfo().
                           Name(name).
                           ToolbarPane().Top().Layer(layer).Position(pos) );
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

void RheiaToolBarManager::RemoveToolBar( const wxString& name )
{
    wxToolBarArray::iterator it = m_toolbars.find(name);
    if( it == m_toolbars.end() )
        return;
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
    }

    m_layout->Update();
    event.Skip();
}

void RheiaToolBarManager::OnToolsUpdateUI( wxUpdateUIEvent& event )
{
    wxMenuBar* mbar = m_parent->GetMenuBar();
    wxAuiManager* m_layout = m_parent->GetLayoutManager();

    mbar->Check(idViewToolMain, m_layout->GetPane(m_toolbar).IsShown() );
    RheiaToolMenuIdMap::iterator tit = m_toolIds.begin();
    for( ; tit != m_toolIds.end() ; ++tit )
        mbar->Check(tit->second, m_layout->GetPane(tit->first).IsShown() );
}


