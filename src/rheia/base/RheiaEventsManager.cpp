/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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
template<> RheiaEventsManager* Singleton<RheiaEventsManager>::instance = 0;
/** global instance for RheiaEventsManager */
template<> bool  Singleton<RheiaEventsManager>::isShutdown = false;

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

void RheiaEventsManager::RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase* functor)
{
    EventMethods[eventType].push_back(functor);
}

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
}
