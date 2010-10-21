/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaEventPlugin.h
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaPluginEvents_h_
#define RheiaPluginEvents_h_

#include <RheiaPMgtSettings.h>
#include <RheiaEvents.h>
#include <wx/intl.h>
#include <wx/event.h>

class RheiaPlugin;

/**
*	@class RheiaPluginEvent
*
*	@brief This is the basic event data container for Rheia plugins.
*
*	This event can handle a plugin when a plugin is generating the event, in other case the pointer
*	will be null.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class PMGT_DLLEXPORT RheiaPluginEvent : public RheiaEvent
{
public:
	/*******************************************************************************************************
	*	CONSTRCUTORS
	*******************************************************************************************************/
	/**
	*   The constructor builds the event with the given wxEventType, the given Id and the given RheiaPlugin
	*
	*	@param commandType wxEventType handled by the object
	*	@param id Id of the generator
	*	@param plugin Pointer to RheiaPlugin that handle the event
	*	@param workspace Pointer to RheiaWorkspace that own the event
	*/
	RheiaPluginEvent(wxEventType commandType = wxEVT_NULL,
            int id = 0,
            RheiaPlugin* plugin = 0L,
            const wxString& name = wxEmptyString )
		: RheiaEvent(commandType, id ),
        m_plugin(plugin),
        m_name( name )
		{}

	/*! Copy Constructor
	*	@param event RheiaEvent from which to copy
	*/
	RheiaPluginEvent(const RheiaPluginEvent& event)
		: RheiaEvent(event),
		m_plugin( event.m_plugin ),
		m_name(event.m_name)
		{}

	/*******************************************************************************************************
	*	METHODS
	*******************************************************************************************************/
	/*! This method overloads the clone virtual method for creating a new event from this one */
	virtual wxEvent *Clone() const { return new RheiaPluginEvent(*this); }

	/*! This method returns the plugin concerned by the event */
	RheiaPlugin* GetPlugin() const { return m_plugin; }

	/** Set the plugin */
	void SetPlugin( RheiaPlugin* plugin ){m_plugin = plugin;};

	/** Get the plugin's name */
	wxString GetPluginName(){return m_name;};

	/** Set the plugin's name */
	void SetPluginName( const wxString& name ) {m_name = name;};

protected:
	/*******************************************************************************************************
	*	PRIVATE VRIABLES
	*******************************************************************************************************/
	RheiaPlugin* m_plugin;									/*! Concerned plugin by the event */
	wxString m_name;

private:
	DECLARE_DYNAMIC_CLASS(RheiaPluginEvent)
};

typedef void (wxEvtHandler::*RheiaPluginEventFunction)(RheiaPluginEvent&);

#define RheiaPluginEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(RheiaPluginEventFunction, &func)

/**************************************************************************
*   PLUGIN EVENTS EVENTS
**************************************************************************/
extern PMGT_DLLEXPORT const wxEventType RheiaEVT_PLUGIN_ATTACHED;
#define EVT_PLUGIN_ATTACHED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PLUGIN_ATTACHED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),
extern PMGT_DLLEXPORT const wxEventType RheiaEVT_PLUGIN_RELEASED;
#define EVT_PLUGIN_RELEASED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_PLUGIN_RELEASED, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),
extern PMGT_DLLEXPORT const wxEventType RheiaEVT_ENVPLUGIN_REQUEST_DETACH;
#define EVT_ENVPLUGIN_REQUEST_DETACH(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_ENVPLUGIN_REQUEST_DETACH, -1, -1, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)&fn, (wxObject *) NULL ),

#endif


