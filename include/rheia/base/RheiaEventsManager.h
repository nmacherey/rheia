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
//class RheiaProjectEvent;
//class RheiaPluginEvent;
//class RheiaWorkspaceEvent;
class RheiaFrameEvent;

/**
*   @class RheiaEventsManager
*
*   @brief This is the main class for generating events in Rheia, you can register and/or generate any
*   events with this class.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	04-January-2010
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaEventsManager : public Mgr<RheiaEventsManager>
{
    /************************************************************************************
    *   FRIENDS
    ************************************************************************************/
    /** Give our private members access to the rheia manager */
    friend class RheiaManager;
    /** Give Mgr class access to our private members */
    friend class Mgr<RheiaEventsManager>;

public :
    /************************************************************************************
    *   METHODS
    ************************************************************************************/
    /** Process to the given event */
	bool ProcessEvent(wxEvent& event);

//	/** Process to the given event */
//	bool ProcessEvent(wxCommandEvent& event);

//	/** Process to the given event */
//	bool ProcessEvent(RheiaProjectEvent& event);
//
//	/** Process to the given event */
//	bool ProcessEvent(RheiaPluginEvent& event);
//
//	/** Process to the given event */
//	bool ProcessEvent(RheiaWorkspaceEvent& event);

//	/** Process to the given event */
//	bool ProcessEvent(RheiaFrameEvent& event);

	/** Register Event sink for a RheiaEvent */
	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase* functor);

//	/** Register Event sink for a RheiaEvent */
//	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<wxCommandEvent>* functor);

//	/** Register Event sink for a RheiaProjectEvent */
//	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaProjectEvent>* functor);
//
//	/** Register Event sink for a RheiaPluginEvent */
//	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaPluginEvent>* functor);
//
//	/** Register Event sink for a RheiaWorkspaceEvent */
//	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaWorkspaceEvent>* functor);

//	/** Register Event sink for a RheiaWorkspaceEvent */
//	void RegisterEventMethod(wxEventType eventType, RheiaEventFunctorBase<RheiaFrameEvent>* functor);

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

//	typedef std::vector< RheiaEventFunctorBase<RheiaProjectEvent>* > ProjectEventMethodsArray;
//	typedef std::map< wxEventType, ProjectEventMethodsArray > ProjectEventMethodsMap;

//	typedef std::vector< RheiaEventFunctorBase<wxCommandEvent>* > CommandEventMethodsArray;
//	typedef std::map< wxEventType, CommandEventMethodsArray > CommandEventMethodsMap;

//	typedef std::vector< RheiaEventFunctorBase<RheiaPluginEvent>* > PluginEventMethodsArray;
//	typedef std::map< wxEventType, PluginEventMethodsArray > PluginEventMethodsMap;
//
//	typedef std::vector< RheiaEventFunctorBase<RheiaWorkspaceEvent>* > WorkspaceEventMethodsArray;
//	typedef std::map< wxEventType, WorkspaceEventMethodsArray > WorkspaceEventMethodsMap;

//	typedef std::vector< RheiaEventFunctorBase<RheiaFrameEvent>* > FrameEventMethodsArray;
//	typedef std::map< wxEventType, FrameEventMethodsArray > FrameEventMethodsMap;

	EventMethodsMap EventMethods;
//    ProjectEventMethodsMap ProjectEventMethods;
//    CommandEventMethodsMap CommandEventMethods;
//    PluginEventMethodsMap PluginEventMethods;
//    WorkspaceEventMethodsMap WorkspaceEventMethods;
//    FrameEventMethodsMap FrameEventMethods;
};

#endif
