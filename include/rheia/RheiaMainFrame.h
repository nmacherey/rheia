#ifndef RheiaMainFrame_h_
#define RheiaMainFrame_h_

#include <RheiaManagedFrame.h>
#include <wx/frame.h>
#include <wx/string.h>
#include <wx/toolbar.h>
#include <wx/aui/aui.h>
#include <wx/wizard.h>
#include <wx/listctrl.h>

#include <map>

class RheiaStartPageContainer;

/**
*   @class RheiaMainFrame
*
*   @brief RheiaMainFrame is the basic frame for applications based on the RheiaFrameWork
*
*   It is mainly composed of an aui manager which allow different panes to be drawn in the window.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	29-January-2010
*	@version 0.0.2
*/
class RheiaMainFrame : public RheiaManagedFrame
{
public :

	/**********************************************************************************************************
													CONSTRUCTORS
	**********************************************************************************************************/
	/*! Base constructor for building the main frame
	*
	*	@param parent Parent Pointer in which to Create the main frame
	*	@param id Frame's id for eventual frame events
	*	@param title Frame's title displayed on the window bar
	*	@param pos Default frame's position when creating
	*	@param size Default frame's size when creating
	*	@param style Frame's style see wxWidgets window styles for info
	*/
	RheiaMainFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

	/*! Destructor */
	~RheiaMainFrame();
	
private :

	RheiaStartPageContainer* m_startpage;

};


#endif
