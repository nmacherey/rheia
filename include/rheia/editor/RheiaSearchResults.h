/**
*   @file RheiaSearchResults.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/

#ifndef RheiaSearchResults_h
#define RheiaSearchResults_h


#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>

#include <vector>

#include "RheiaEditorSettings.h"
#include "RheiaPageContainer.h"
#include "RheiaManagedFrame.h"

class RheiaSearchResultsPanel;

/** @struct SearchResult
 * @brief basic structure for handling a search result in RheiaEditor
 */
struct SearchResult
{
	SearchResult():line(-1){};
#ifndef SWIG
	SearchResult(const SearchResult& rhs):
		file(rhs.file),
		line(rhs.line),
		text(rhs.text)
		{};
	
	SearchResult& operator=(const SearchResult& rhs)
	{
		file = rhs.file;
		line = rhs.line;
		text = rhs.text;
		
		return (*this);
	}
	
	~SearchResult() {};
#endif

	wxString file;
	int line;
	wxString text;
};

typedef std::vector<SearchResult> SearchResultArray;

/**
*   @class RheiaSearchResultsPanel
* 	@brief main class for displaying editors search results
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
class EDITOR_DLLEXPORT RheiaSearchResults : public RheiaPageContainer
{
private:
	SearchResultArray m_searchResults;
	RheiaSearchResultsPanel* m_panel;
	RheiaManagedFrame* m_parent;
	wxBitmap m_bmp;
	
public :
	/** ctor */
	RheiaSearchResults(RheiaManagedFrame* parent):
		m_panel(NULL),
		m_parent(parent)
	{
		
	}

	/** dtor */
	virtual ~RheiaSearchResults()
	{}

	/***********************************************************************
	 * ACCESSORS
	 **********************************************************************/
	/** Get the registered search results */
	SearchResultArray& GetSearchResults() {return m_searchResults;};
	
	/** Get the parented managed frame */
	RheiaManagedFrame* GetParent() {return m_parent;};
	
	/** Clear old search results */
	void Clear();
	
	/** Add a search result */
	void Add(SearchResult& res) {m_searchResults.push_back(res);};
	
	/** Remove at the given index */
	void Remove( unsigned int index )
	{
		if( index < m_searchResults.size() )
		{
			SearchResultArray::iterator it = m_searchResults.begin() + index;
			m_searchResults.erase(it);
		}
			
	}
	
	/** method when the panel is destroyed */
	virtual bool OnPageClosed() {m_panel == NULL;}
	
	/** update method */
	void Update(SearchResultArray& search);
	
	/**
	*   Get the project bitmap to the given size,
	*   size could be 16x16, 32x32, 48x48, 80x80 or 128x128
	*/
	virtual const wxBitmap& GetBitmap( const int& size ){return m_bmp;};
	
	/**
	*   Any project will have a window in the center pane, which will be called
	*   the project's main envrionment.
	*
	*   For this purpose, any projects must provide the application with a MainWindow
	*   which will be displayed and managed by RheiaCenterPaneManager.
	*
	*   We consider that a project cannot be provided without any MainWindow.
	*
	*   @param parent the parent window in which the project's main window shall be created
	*/
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );
};

#endif
