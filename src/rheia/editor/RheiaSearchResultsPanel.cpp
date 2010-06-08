/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaSearchResultsPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/

#include "RheiaSearchResultsPanel.h"
#include "RheiaSearchResults.h"
#include "RheiaEditorManager.h"

RheiaSearchResultsPanel::RheiaSearchResultsPanel( RheiaSearchResults* container , wxWindow* parent ):
	RheiaBookPage(parent),
	m_container(container)
{
	wxPanel::Create(parent);
	
	wxBoxSizer* m_sizermain;
	m_sizermain = new wxBoxSizer( wxVERTICAL );
	
	m_listSearchResults = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	m_sizermain->Add( m_listSearchResults, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( m_sizermain );
	this->Layout();
	
	// Connect Events
	m_listSearchResults->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( RheiaSearchResultsPanel::OnSearchResultActivated ), NULL, this );
	
	DoUpdateList(m_container);
}

RheiaSearchResultsPanel::~RheiaSearchResultsPanel()
{
	// Disconnect Events
	m_listSearchResults->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( RheiaSearchResultsPanel::OnSearchResultActivated ), NULL, this );
	
}

void RheiaSearchResultsPanel::OnSearchResultActivated( wxListEvent& WXUNUSED(event) )
{
	SearchResultArray results = m_container->GetSearchResults();
	long sel = -1;
	
	sel = m_listSearchResults->GetNextItem(sel,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
	if( sel == -1 )
		return;
	
	SearchResult res = results[sel];
	
	RheiaEditorManager::Get(m_container->GetParent())->Goto( res.file , res.line , res.text );
}

void RheiaSearchResultsPanel::Clear()
{
	m_listSearchResults->ClearAll();
}

void RheiaSearchResultsPanel::DoUpdateList( RheiaSearchResults* container )
{
	m_container = container;
    m_listSearchResults->ClearAll();
	
	SearchResultArray results = m_container->GetSearchResults();

    if (m_listSearchResults->GetColumnCount() == 0)
    {
        m_listSearchResults->InsertColumn(0, _T("File"));
        m_listSearchResults->InsertColumn(1, _T("Line"));
		m_listSearchResults->InsertColumn(2, _T("Content"));
    }
	
	SearchResultArray::iterator it = results.begin();
    for( int i = 0 ; it != results.end() ; ++it, ++i )
    {
        long idx = m_listSearchResults->InsertItem(i, (*it).file);
		wxString line = wxString::Format( wxT("line: %d") , (*it).line );
        m_listSearchResults->SetItem(idx, 1, line);
        m_listSearchResults->SetItem(idx, 2, (*it).text);
    }

    m_listSearchResults->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_listSearchResults->SetColumnWidth(1, wxLIST_AUTOSIZE );
	m_listSearchResults->SetColumnWidth(2, wxLIST_AUTOSIZE );
}