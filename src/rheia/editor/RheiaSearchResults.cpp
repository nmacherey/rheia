/**
*   @file RheiaSearchResults.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/

#include "RheiaSearchResults.h"
#include "RheiaSearchResultsPanel.h"

RheiaBookPage* RheiaSearchResults::BuildMainWindow( wxWindow* parent )
{
	m_panel = new RheiaSearchResultsPanel(this,parent);
	return m_panel;
}

void RheiaSearchResults::Clear() 
{
	m_searchResults.clear();
	
	if( m_panel != NULL )
		m_panel->Clear();
};

void RheiaSearchResults::Update(SearchResultArray& search)
{
	m_searchResults = search;
	if( m_panel != NULL )
		m_panel->DoUpdateList(this);
}