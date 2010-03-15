/**
*	@file RheiaEventsManager.h
*   @todo add here macros for managing events quickly
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	04-January-2010
*	@version 0.0.1
*/
#ifndef RheiaEventsManager_h_
#define RheiaEventsManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>
#include <RheiaFunctor.h>

#include <wx/string.h>
#include <set>
#include <map>

/*** Rheia imports */
class RheiaEvent;

/**
*   @class RheiaEventsManager
*
*   @brief This is the main class for generating events in Rheia, you can register and/or generate any
*   events with this class.
* 	
* 	This class can handle any event derived from a wxEvent... To do this you have to register the event 
* 	method using the RegisterEventMethod and the RheiaEventFunctor template. The method in your template 
* 	shall be registered properly using a RheiaFooEventHandler ok wxCommandEventHandler macro
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	04-January-2010
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaEventsManager : public Singleton<RheiaEventsManager>
{
    /************************************************************************************
    *   FRIENDS
    ************************************************************************************/
    /** Give our private members access to the rheia manager */
    friend class RheiaManager;
    /** Give Singleton class access to our private members */
    friend class Singleton<RheiaEventsManager>;

public :
    /************************************************************************************
    *   METHODS
    ************************************************************************************/
    /** Process to the given event */
	bool ProcessEvent(wxEvent& event);

	/** Register Event sink for a RheiaEvent */
	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase* functor);

	/** Removes all the processed event sinks for a specified owner */
	void RemoveAllEventMethodsFor(void* owner);

	/** Removes all the processed event sinks for a specified owner */
	void RemoveAllEventMethods();

private :

    /************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ************************************************************************************/
    /**
    *   Basic constrcutor,
    *   As any other singleton in Rheia, you have to use RheiaEventsManager::Get()
    *   to get the global instance for this class. However you should never have to
    *   use this unless you are a Rheia core Developper.
    */
    RheiaEventsManager();

    /**
    *   Default destructor,
    *   As any other singleton in Rheia, you have to use RheiaEventsManager::Free()
    *   to free the global instance of this manager. However, you should never have to
    *   use this unless you are a Rheie core Developper
    */
    ~RheiaEventsManager();

protected :

    /************************************************************************************
    *   MEMBERS
    ************************************************************************************/
	typedef std::vector< RheiaEventFunctorBase* > EventMethodsArray;
	typedef std::map< wxEventType, EventMethodsArray > EventMethodsMap;

	EventMethodsMap EventMethods;
};

#endif
