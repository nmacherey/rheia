/**
*   @file RheiaWizardManager.cpp
*
*   @brief This is the main source file for the RheiaWizardManager
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-May-2009
*   @version 0.0.1
*/

#include "RheiaWizardManager.h"
#include "RheiaProject.h"
#include "RheiaProjectCreationWizard.h"
#include "RheiaCenterPaneManager.h"
#include "RheiaWorkspace.h"
#include "RheiaWizardPageBase.h"
#include "RheiaProjectCreationDlg.h"
#include "RheiaWorkspaceManager.h"
#include "RheiaManager.h"
#include "RheiaEventsManager.h"
#include "RheiaEvents.h"
#include "RheiaEventProject.h"

#include <wx/frame.h>
#include <wx/sizer.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaWizardManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaWizardManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaWizardManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaWizardManager>::m_ns = locmap;
RheiaProjectWizardRegistrationMap RheiaWizardManager::m_RegisteredWizards;

BEGIN_EVENT_TABLE( RheiaWizardManager , wxEvtHandler )
    EVT_WIZARD_PAGE_CHANGED( wxID_ANY , RheiaWizardManager::OnPageChanged )
    EVT_WIZARD_PAGE_CHANGING( wxID_ANY, RheiaWizardManager::OnPageChanging )
    EVT_WIZARD_CANCEL( wxID_ANY, RheiaWizardManager::OnCancelWizard )
    EVT_WIZARD_FINISHED( wxID_ANY, RheiaWizardManager::OnWizardFinish )
END_EVENT_TABLE()

RheiaWizardManager::RheiaWizardManager( RheiaManagedFrame* parent ):
    wxEvtHandler(),
    m_parent(parent)
{
    if( m_parent )
        m_parent->PushEventHandler( this );
}

RheiaWizardManager::~RheiaWizardManager()
{
    if( m_parent )
        m_parent->RemoveEventHandler( this );
}

bool RheiaWizardManager::DoCreateNewProject( RheiaWorkspace* workspace )
{
    RheiaProjectCreationDlg dialog( m_parent );

    if( dialog.ShowModal() == wxID_CANCEL )
        return false;

    wxString wizname = dialog.GetSelectedWizard();

    if( wizname.IsEmpty() )
        return false;

    wxWizard* m_wizard = new wxWizard;

    m_projectWizard = CreateWizard( wizname , m_wizard , m_parent , workspace );

    if( m_projectWizard == NULL )
    {
        m_wizard->Destroy();
        return false;
    }

    m_wizard->Create(m_parent, wxID_ANY,
                    m_projectWizard->GetTitle(),
                    m_projectWizard->GetBitmap(),
                    wxDefaultPosition,
                    wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

    m_projectWizard->BuildPages();
    WizardPagesArray m_pages = m_projectWizard->GetPages();

    if( m_wizard->RunWizard( m_pages[0] ) )
    {
        RheiaProject* m_project = m_projectWizard->GetProject();

        if( m_project == NULL )
        {
            delete m_projectWizard;
            m_projectWizard = NULL;
            m_wizard->Destroy();
            return false;
        }

        workspace->Add( m_project->GetName() , m_project );

        wxTreeCtrl* m_tree = RheiaWorkspaceManager::Get(m_parent)->GetManagementTree();
        wxTreeItemId m_root = RheiaWorkspaceManager::Get(m_parent)->GetManagementTreeRoot();

        workspace->UpdateTree( m_tree , 16 );
        RheiaCenterPaneManager::Get(m_parent)->AddPage( m_project->GetName() , m_project );

        RheiaProject* project = m_projectWizard->GetProject();
        RheiaProjectEvent event(RheiaEVT_PROJECT_CREATED,
                0,
                m_project,
                m_project->GetName()
                );

        m_parent->GetEventHandler()->ProcessEvent(event);
    }

    m_wizard->Destroy();

    return true;
}

void RheiaWizardManager::OnPageChanging( wxWizardEvent& event )
{
    RheiaWizardPageBase* m_page = (RheiaWizardPageBase*) event.GetPage();
    if( !m_page->OnPageChanging() )
    {
        event.Veto();
        return;
    }
    event.Skip();
    return;
}

void RheiaWizardManager::OnPageChanged( wxWizardEvent& event )
{
    RheiaWizardPageBase* m_page = (RheiaWizardPageBase*) event.GetPage();

    wxSize siz = m_page->GetSize();
    wxSize dlgs = m_projectWizard->m_wizard->GetSize();

    wxSize newSize( siz.GetX() + 200 , siz.GetY() + 100 );
    m_projectWizard->m_wizard->SetSize(newSize);

    if( !m_page->OnPageChanged() )
    {
        event.Skip();
        return;
    }
    event.Skip();
    return;
}

void RheiaWizardManager::OnCancelWizard( wxWizardEvent& event )
{
    int code = wxMessageBox( wxT("Are you sure you want to cancel ?") , wxT("Warning") , wxYES_NO );
    if( code == wxNO )
    {
        event.Veto();
        return;
    }

    m_projectWizard->OnWizardCancel();
    delete m_projectWizard;
    return;
}

void RheiaWizardManager::OnWizardFinish( wxWizardEvent& event )
{
    m_projectWizard->OnWizardFinished();
}

bool RheiaWizardManager::RegisterProjectWizard( const wxString& name ,
        const wxString& category,
        const wxString& resName,
        const wxString& bitmapBasename,
        WizardConstructor ctor,
        WizardDestructor dtor )
{
    RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.find( name );

    if ( it != m_RegisteredWizards.end() )
        return false;

    RheiaProjectWizardRegistration registration;

    registration.name = name;
    registration.category = category;
    registration.resName = resName;
    registration.bitmapBasename = bitmapBasename;
    registration.ctor = ctor;
    registration.dtor = dtor;

    m_RegisteredWizards[name] = registration;

    return true;
}

bool RheiaWizardManager::UnregisterProjectWizard( const wxString& name )
{
	RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.find( name );

    if ( it == m_RegisteredWizards.end() )
        return false;
		
	m_RegisteredWizards.erase(it);
	return true;
}

wxArrayString RheiaWizardManager::GetWizardList( )
{
    wxArrayString ret;
    RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.begin();

    for ( ; it != m_RegisteredWizards.end() ; it++ )
        ret.Add( it->first );

    return ret;
}

wxArrayString RheiaWizardManager::GetCategoryList( )
{
    wxArrayString ret;
    RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.begin();

    for ( ; it != m_RegisteredWizards.end() ; it++ )
    {
        int idx = ret.Index( it->second.category );

        if( idx == wxNOT_FOUND )
            ret.Add( it->second.category );
    }

    return ret;
}

wxArrayString RheiaWizardManager::GetWizardListFor( const wxString& category )
{
    wxArrayString ret;
    RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.begin();

    for ( ; it != m_RegisteredWizards.end() ; it++ )
    {
        int idx = ret.Index( it->second.category );

        if( it->second.category.IsSameAs(category) )
            ret.Add( it->first );
    }

    return ret;
}

RheiaProjectCreationWizard* RheiaWizardManager::CreateWizard( const wxString& type,
        wxWizard* wizard,
        RheiaManagedFrame* parent ,
        RheiaWorkspace* workspace )
{
    RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.find( type );

    if ( it == m_RegisteredWizards.end() )
        return NULL;

    return it->second.ctor( wizard , parent , workspace );
}

RheiaProjectWizardRegistration RheiaWizardManager::FindProjectWizardByName( const wxString& name )
{
    RheiaProjectWizardRegistrationMap::iterator it = m_RegisteredWizards.find( name );

    RheiaProjectWizardRegistration ret;

    if ( it == m_RegisteredWizards.end() )
        return ret;

    return it->second;
}

