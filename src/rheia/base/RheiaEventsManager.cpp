/**
*	@file RheiaEventsManager.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	04-January-2010
*	@version 0.0.1
*/
#include <RheiaEventsManager.h>
#include <RheiaManager.h>
#include <RheiaEvents.h>
//#include <RheiaEventProject.h>
//#include <RheiaEventWorkspace.h>
//#include <RheiaEventPlugin.h>
#include <RheiaEventFrame.h>

#include <wx/xrc/xmlres.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/msgdlg.h>
#include <wx/aui/aui.h>

/** global instance for RheiaEventsManager */
template<> RheiaEventsManager* Mgr<RheiaEventsManager>::instance = 0;
/** global instance for RheiaEventsManager */
template<> bool  Mgr<RheiaEventsManager>::isShutdown = false;

RheiaEventsManager::RheiaEventsManager()
{

}

RheiaEventsManager::~RheiaEventsManager()
{

}

bool RheiaEventsManager::ProcessEvent( wxEvent &event )
{
    if (RheiaManager::IsAppShuttingDown())
        return false;

    EventMethodsMap::iterator mit = EventMethods.find(event.GetEventType());
    if (mit != EventMethods.end())
    {
        for (EventMethodsArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
        {
            (*it)->Call(event);
        }
    }
    return true;
}

//bool RheiaEventsManager::ProcessEvent( RheiaProjectEvent &event )
//{
//    if (RheiaManager::IsAppShuttingDown())
//        return false;
//
//    ProjectEventMethodsMap::iterator mit = ProjectEventMethods.find(event.GetEventType());
//    if (mit != ProjectEventMethods.end())
//    {
//        for (ProjectEventMethodsArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
//        {
//            (*it)->Call(event);
//        }
//    }
//    return true;
//}
//
//bool RheiaEventsManager::ProcessEvent( RheiaPluginEvent &event )
//{
//    if (RheiaManager::IsAppShuttingDown())
//        return false;
//
//    PluginEventMethodsMap::iterator mit = PluginEventMethods.find(event.GetEventType());
//    if (mit != PluginEventMethods.end())
//    {
//        for (PluginEventMethodsArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
//        {
//            (*it)->Call(event);
//        }
//    }
//    return true;
//}
//
//bool RheiaEventsManager::ProcessEvent( RheiaWorkspaceEvent &event )
//{
//    if (RheiaManager::IsAppShuttingDown())
//        return false;
//
//    WorkspaceEventMethodsMap::iterator mit = WorkspaceEventMethods.find(event.GetEventType());
//    if (mit != WorkspaceEventMethods.end())
//    {
//        for (WorkspaceEventMethodsArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
//        {
//            (*it)->Call(event);
//        }
//    }
//    return true;
//}

//bool RheiaEventsManager::ProcessEvent( RheiaFrameEvent &event )
//{
//    if (RheiaManager::IsAppShuttingDown())
//        return false;
//
//    FrameEventMethodsMap::iterator mit = FrameEventMethods.find(event.GetEventType());
//    if (mit != FrameEventMethods.end())
//    {
//        for (FrameEventMethodsArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
//        {
//            (*it)->Call(event);
//        }
//    }
//    return true;
//}
//
//bool RheiaEventsManager::ProcessEvent( wxCommandEvent &event )
//{
//    if (RheiaManager::IsAppShuttingDown())
//        return false;
//
//    CommandEventMethodsMap::iterator mit = CommandEventMethods.find(event.GetEventType());
//    if (mit != CommandEventMethods.end())
//    {
//        for (CommandEventMethodsArray::iterator it = mit->second.begin(); it != mit->second.end(); ++it)
//        {
//            (*it)->Call(event);
//        }
//    }
//    return true;
//}

void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase* functor)
{
    EventMethods[eventType].push_back(functor);
}

//void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaProjectEvent>* functor)
//{
//    ProjectEventMethods[eventType].push_back(functor);
//}
//
//void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaPluginEvent>* functor)
//{
//    PluginEventMethods[eventType].push_back(functor);
//}
//
//void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaWorkspaceEvent>* functor)
//{
//    WorkspaceEventMethods[eventType].push_back(functor);
//}

//void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaFrameEvent>* functor)
//{
//    FrameEventMethods[eventType].push_back(functor);
//}
//
//void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<wxCommandEvent>* functor)
//{
//    CommandEventMethods[eventType].push_back(functor);
//}

void RheiaEventsManager::RemoveAllEventMethodsFor(void* owner)
{
    for (EventMethodsMap::iterator mit = EventMethods.begin(); mit != EventMethods.end(); ++mit)
    {
        EventMethodsArray::iterator it = mit->second.begin();
        bool endIsInvalid = false;
        while (!endIsInvalid && it != mit->second.end())
        {
            if ((*it) && (*it)->GetThis() == owner)
            {
                EventMethodsArray::iterator it2 = it++;
                endIsInvalid = it == mit->second.end();
                delete (*it2);
                mit->second.erase(it2);
            }
            else
                ++it;
        }
    }

//    for (ProjectEventMethodsMap::iterator mit = ProjectEventMethods.begin(); mit != ProjectEventMethods.end(); ++mit)
//    {
//        ProjectEventMethodsArray::iterator it = mit->second.begin();
//        bool endIsInvalid = false;
//        while (!endIsInvalid && it != mit->second.end())
//        {
//            if ((*it) && (*it)->GetThis() == owner)
//            {
//                ProjectEventMethodsArray::iterator it2 = it++;
//                endIsInvalid = it == mit->second.end();
//                delete (*it2);
//                mit->second.erase(it2);
//            }
//            else
//                ++it;
//        }
//    }
//
//    for (PluginEventMethodsMap::iterator mit = PluginEventMethods.begin(); mit != PluginEventMethods.end(); ++mit)
//    {
//        PluginEventMethodsArray::iterator it = mit->second.begin();
//        bool endIsInvalid = false;
//        while (!endIsInvalid && it != mit->second.end())
//        {
//            if ((*it) && (*it)->GetThis() == owner)
//            {
//                PluginEventMethodsArray::iterator it2 = it++;
//                endIsInvalid = it == mit->second.end();
//                delete (*it2);
//                mit->second.erase(it2);
//            }
//            else
//                ++it;
//        }
//    }
//
//    for (WorkspaceEventMethodsMap::iterator mit = WorkspaceEventMethods.begin(); mit != WorkspaceEventMethods.end(); ++mit)
//    {
//        WorkspaceEventMethodsArray::iterator it = mit->second.begin();
//        bool endIsInvalid = false;
//        while (!endIsInvalid && it != mit->second.end())
//        {
//            if ((*it) && (*it)->GetThis() == owner)
//            {
//                WorkspaceEventMethodsArray::iterator it2 = it++;
//                endIsInvalid = it == mit->second.end();
//                delete (*it2);
//                mit->second.erase(it2);
//            }
//            else
//                ++it;
//        }
//    }

//    for (FrameEventMethodsMap::iterator mit = FrameEventMethods.begin(); mit != FrameEventMethods.end(); ++mit)
//    {
//        FrameEventMethodsArray::iterator it = mit->second.begin();
//        bool endIsInvalid = false;
//        while (!endIsInvalid && it != mit->second.end())
//        {
//            if ((*it) && (*it)->GetThis() == owner)
//            {
//                FrameEventMethodsArray::iterator it2 = it++;
//                endIsInvalid = it == mit->second.end();
//                delete (*it2);
//                mit->second.erase(it2);
//            }
//            else
//                ++it;
//        }
//    }
//
//    for (CommandEventMethodsMap::iterator mit = CommandEventMethods.begin(); mit != CommandEventMethods.end(); ++mit)
//    {
//        CommandEventMethodsArray::iterator it = mit->second.begin();
//        bool endIsInvalid = false;
//        while (!endIsInvalid && it != mit->second.end())
//        {
//            if ((*it) && (*it)->GetThis() == owner)
//            {
//                CommandEventMethodsArray::iterator it2 = it++;
//                endIsInvalid = it == mit->second.end();
//                delete (*it2);
//                mit->second.erase(it2);
//            }
//            else
//                ++it;
//        }
//    }
}

void RheiaEventsManager::RemoveAllEventMethods()
{
    /** First remove all events sinks from the manager */
    for (EventMethodsMap::iterator mit = EventMethods.begin(); mit != EventMethods.end(); ++mit)
    {
        EventMethodsArray::iterator it = mit->second.begin();

        for( ; it != mit->second.end() ; ++it )
            if( (*it) )
                delete (*it);
    }

    EventMethods.clear();

//    for (ProjectEventMethodsMap::iterator mit = ProjectEventMethods.begin(); mit != ProjectEventMethods.end(); ++mit)
//    {
//        ProjectEventMethodsArray::iterator it = mit->second.begin();
//        for( ; it != mit->second.end() ; ++it )
//            if( (*it) )
//                delete (*it);
//    }
//
//    ProjectEventMethods.clear();
//
//    for (PluginEventMethodsMap::iterator mit = PluginEventMethods.begin(); mit != PluginEventMethods.end(); ++mit)
//    {
//        PluginEventMethodsArray::iterator it = mit->second.begin();
//        for( ; it != mit->second.end() ; ++it )
//            if( (*it) )
//                delete (*it);
//    }
//
//    PluginEventMethods.clear();
//
//    for (WorkspaceEventMethodsMap::iterator mit = WorkspaceEventMethods.begin(); mit != WorkspaceEventMethods.end(); ++mit)
//    {
//        WorkspaceEventMethodsArray::iterator it = mit->second.begin();
//        for( ; it != mit->second.end() ; ++it )
//            if( (*it) )
//                delete (*it);
//    }
//
//    WorkspaceEventMethods.clear();

//    for (FrameEventMethodsMap::iterator mit = FrameEventMethods.begin(); mit != FrameEventMethods.end(); ++mit)
//    {
//        FrameEventMethodsArray::iterator it = mit->second.begin();
//        for( ; it != mit->second.end() ; ++it )
//            if( (*it) )
//                delete (*it);
//    }
//
//    FrameEventMethods.clear();
//
//    for (CommandEventMethodsMap::iterator mit = CommandEventMethods.begin(); mit != CommandEventMethods.end(); ++mit)
//    {
//        CommandEventMethodsArray::iterator it = mit->second.begin();
//        for( ; it != mit->second.end() ; ++it )
//            if( (*it) )
//                delete (*it);
//    }
//
//    CommandEventMethods.clear();
}
