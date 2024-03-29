/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaMenuManager.cpp
*
*   Revision : 15-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Commentaries
*
*   Revision : 8-February-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes :   Added RheiaMenuFunctorManager and modifications of RheiaMenuManager to
*                   associated to a RheiaManagedFrame.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaMenuManager.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaException.h>

#include <wx/menu.h>
#include <wx/xrc/xmlres.h>
#include <wx/msgdlg.h>
#include <wx/frame.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaMenuManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaMenuManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaMenuManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaMenuManager>::m_ns = locmap;

/*! Global instance for the RheiaMenuFunctorManager */
template<> RheiaMenuFunctorManager* Singleton<RheiaMenuFunctorManager>::instance = 0;
/*! Global isShutdown for the RheiaMenuFunctorManager */
template<> bool  Singleton<RheiaMenuFunctorManager>::isShutdown = false;

/**********************************************************************************************************
*	CONSTRUCTORS
**********************************************************************************************************/
/* Default constructor */
RheiaMenuManager::RheiaMenuManager( RheiaManagedFrame* parent ):
    wxEvtHandler(),
    m_parent(parent)
{
    if( m_parent )
    {
        CreateMenuBar();
        m_parent->PushEventHandler(this);
		RheiaFrameEventsManager::Get(m_parent)->RegisterEventMethod(RheiaEVT_FRAME_CLOSING,
			new RheiaEventFunctor<RheiaMenuManager>(this, RheiaFrameEventHandler(RheiaMenuManager::OnFrameClosing)));
    }

    RegisterEvents();
}

/* Destructor */
RheiaMenuManager::~RheiaMenuManager()
{

}

void RheiaMenuManager::OnFrameClosing(RheiaFrameEvent& event)
{
    m_parent->RemoveEventHandler(this);
    event.Skip();
}

void RheiaMenuManager::RecreateMenuBar()
{
    if( !m_parent )
        RheiaThrow( wxT("RheiaMenuManager::Error::RecreateMenuBar trying to recreate a menu bar with an empty parent") );

    wxMenuBar* m = m_parent->GetMenuBar();
    m_parent->SetMenuBar(0); // unhook old menubar
    CreateMenuBar(); // create new menubar
    delete m; // delete old menubar

    SendEvent( RheiaEVT_MENU_REBUILT );
}

void RheiaMenuManager::CreateMenuBar()
{
    if( !m_parent )
        RheiaThrow( wxT("RheiaMenuManager::Error::CreateMenuBar trying to recreate a menu bar with an empty parent") );

    MainMenuBar=0L;

    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxXmlResource *myres = wxXmlResource::Get();

    /* Initialize resource */
    if (!myres->Load(resPath + _T("/resource.zip#zip:main_menu.xrc")))
        wxMessageBox(_T("An error append while loading ressource path invalid"),_("Rehia error !!!"));

    MainMenuBar = myres->LoadMenuBar(_T("main_menu_bar"));

    if (!MainMenuBar)
    {
        MainMenuBar = new wxMenuBar(); // Some error happened.
        m_parent->SetMenuBar(MainMenuBar);
    }
    else
    {
        /* If the menu bar has correctly been initialized from the ressource,
        Get the different menu items for providing the user with these informations
        */
        m_parent->SetMenuBar(MainMenuBar);
    }

    RheiaMenuFunctorArray m_funcs = RheiaMenuFunctorManager::Get()->GetFunctors();
    RheiaMenuFunctorArray::iterator it = m_funcs.begin();

    for( ; it != m_funcs.end() ; ++it )
    {
        (*it)->Call(MainMenuBar);
    }
}

void RheiaMenuManager::OnMenuCallbackAdded( wxCommandEvent& WXUNUSED(event) )
{
    RecreateMenuBar();
}

void RheiaMenuManager::OnMenuCallbackRemoved( wxCommandEvent& WXUNUSED(event) )
{
    RecreateMenuBar();
}

void RheiaMenuManager::RegisterEvents()
{
    /* Register events for plugin installation and uninstallation */
    RheiaEventsManager* pm = RheiaEventsManager::Get();

    pm->RegisterEventMethod(RheiaEVT_MENU_CALLBACK_ADDED, new RheiaEventFunctor<RheiaMenuManager>(this, wxCommandEventHandler(RheiaMenuManager::OnMenuCallbackAdded)));
    pm->RegisterEventMethod(RheiaEVT_MENU_CALLBACK_REMOVED, new RheiaEventFunctor<RheiaMenuManager>(this, wxCommandEventHandler(RheiaMenuManager::OnMenuCallbackRemoved)));
    
}

void RheiaMenuManager::SendEvent( const wxEventType& type )
{
    wxCommandEvent event( type );
    m_parent->GetEventHandler()->ProcessEvent( event );
}

/***********************************************************************************************
*   RheiaMenuFunctorManager definitions
***********************************************************************************************/

RheiaMenuFunctorManager::RheiaMenuFunctorManager()
{

}

RheiaMenuFunctorManager::~RheiaMenuFunctorManager()
{
    RheiaMenuFunctorArray::iterator it = m_funcs.begin();

    for( ; it != m_funcs.end() ; ++it )
    {
        RheiaMenuFunctorBase* functor = (*it);
        UnregisterMenufunction(functor);
        delete functor;
    }
}


void RheiaMenuFunctorManager::RegisterMenuFunction( RheiaMenuFunctorBase* func )
{
    m_funcs.push_back(func);
    SendEvent( RheiaEVT_MENU_CALLBACK_ADDED );
}

void RheiaMenuFunctorManager::UnregisterMenufunction( RheiaMenuFunctorBase* func )
{
    RheiaMenuFunctorArray::iterator it = m_funcs.begin();

    for( ; it != m_funcs.end() ; ++it )
        if( (*it) == func )
        {
            m_funcs.erase(it);
            break;
        }

    SendEvent( RheiaEVT_MENU_CALLBACK_REMOVED );
}

void RheiaMenuFunctorManager::SendEvent( const wxEventType& type )
{
    wxCommandEvent event( type );
    RheiaEventsManager::Get()->ProcessEvent(event);
}
