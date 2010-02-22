/**
*	@file RheiaEventFrame.h
*
*   Revision : 4-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaFrameEvents_h_
#define RheiaFrameEvents_h_

#include <RheiaBaseSettings.h>
#include <RheiaEvents.h>
#include <wx/intl.h>
#include <wx/event.h>

class RheiaManagedFrame;

/**
*	@class RheiaFrameEvent
*
*	@brief This is the basic event data container for Rheia frames.
*
*	This event can handle a frame when a frame is generating the event, in other case the pointer
*	will be null.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaFrameEvent : public RheiaEvent
{
public:
	/*******************************************************************************************************
	*	CONSTRCUTORS
	*******************************************************************************************************/
	/**
	*   The constructor builds the event with the given wxEventType, the given Id and the given RheiaManagedFrame
	*
	*	@param commandType wxEventType handled by the object
	*	@param id Id of the generator
	*	@param frame Pointer to RheiaManagedFrame that handle the event
	*	@param workspace Pointer to RheiaWorkspace that own the event
	*/
	RheiaFrameEvent(wxEventType commandType = wxEVT_NULL,
            int id = 0,
            RheiaManagedFrame* frame = 0L,
            const wxString& name = wxEmptyString )
		: RheiaEvent(commandType, id ),
        m_frame(frame),
        m_name( name )
		{}

	/** Copy Constructor
	*	@param event RheiaEvent from which to copy
	*/
	RheiaFrameEvent(const RheiaFrameEvent& event)
		: RheiaEvent(event),
		m_frame( event.m_frame ),
		m_name(event.m_name)
		{}
		
	virtual ~RheiaFrameEvent() {m_frame = 0L;};

	/*******************************************************************************************************
	*	METHODS
	*******************************************************************************************************/
	/*! This method overloads the clone virtual method for creating a new event from this one */
	virtual wxEvent *Clone() const { return new RheiaFrameEvent(*this); }

	/*! This method returns the frame concerned by the event */
	RheiaManagedFrame* GetFrame() const { return m_frame; }

	/** Set the frame */
	void SetFrame( RheiaManagedFrame* frame ){m_frame = frame;};

	/** Get the frame's name */
	wxString GetFrameName(){return m_name;};

	/** Set the frame's name */
	void SetFrameName( const wxString& name ) {m_name = name;};

protected:
	/*******************************************************************************************************
	*	PRIVATE VRIABLES
	*******************************************************************************************************/
	RheiaManagedFrame* m_frame;									/*! Concerned frame by the event */
	wxString m_name;

private:
	DECLARE_DYNAMIC_CLASS(RheiaFrameEvent)
};

typedef void (wxEvtHandler::*RheiaFrameEventFunction)(RheiaFrameEvent&);

#define RheiaFrameEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)wxStaticCastEvent(RheiaFrameEventFunction, &func)

/**************************************************************************
*   PLUGIN EVENTS EVENTS
**************************************************************************/
extern BASE_DLLEXPORT const wxEventType RheiaEVT_FRAME_CREATED;
#define EVT_FRAME_CREATED(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_FRAME_CREATED, wxID_ANY, wxID_ANY, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)wxStaticCastEvent(RheiaFrameEventFunction, &fn), (wxObject *) NULL ),
extern BASE_DLLEXPORT const wxEventType RheiaEVT_FRAME_CLOSING;
#define EVT_FRAME_CLOSING(fn) DECLARE_EVENT_TABLE_ENTRY( RheiaEVT_FRAME_CLOSING, wxID_ANY, wxID_ANY, (wxObjectEventFunction)(wxEventFunction)(RheiaEventFunction)wxStaticCastEvent(RheiaFrameEventFunction, &fn), (wxObject *) NULL ),

#endif



