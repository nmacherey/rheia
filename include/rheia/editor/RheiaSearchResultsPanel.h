/**
*   @file RheiaSearchResultsPanel.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef RheiaSearchResultsPanel_h
#define RheiaSearchResultsPanel_h

#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>

#include "RheiaEditorSettings.h"
#include "RheiaBookPage.h"

/* imports */
class RheiaSearchResults;

/**
*   @class RheiaSearchResultsPanel
* 	@brief main class for displaying editors search results
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
class EDITOR_DLLEXPORT RheiaSearchResultsPanel : public RheiaBookPage
{
	friend class RheiaSearchResults;
private:
	RheiaSearchResults* m_container;
	
protected:
	/**************************************************************************************
	 * PRIVATE MEMBERS
	 *************************************************************************************/
	wxListCtrl* m_listSearchResults;

	/** callback used when an item is selected in the list */
	void OnSearchResultActivated( wxListEvent& event );
	
	/** method used to update list */
	void DoUpdateList( RheiaSearchResults* container );
	
public:
	
	/**************************************************************************************
	 * CONSTRUCTORS AND DESTRUCTORS
	 *************************************************************************************/
	/** basic ctor */
	RheiaSearchResultsPanel( RheiaSearchResults* container , wxWindow* parent );
	
	/** dtor */
	~RheiaSearchResultsPanel();
	
	/** Clear contents */
	void Clear();

};

#endif //__noname__
