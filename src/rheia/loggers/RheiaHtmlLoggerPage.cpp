/**
*   @file RheiaHtmlLoggerPage.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*/
#include "RheiaHtmlLoggerPage.h"
#include "RheiaHtmlLogger.h"


#include <wx/button.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>
#include <wx/colordlg.h>
#include <wx/msgdlg.h>
#include <wx/imaglist.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include <wx/sizer.h>
#include <wx/html/htmlwin.h>

RheiaHtmlLoggerPage::RheiaHtmlLoggerPage( wxWindow* parent , RheiaHtmlLogger* logger ):
    RheiaBookPage( parent ),
    m_logger( logger )
{
    wxPanel::Create( parent , wxID_ANY );
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    m_window = new wxHtmlWindow( this , wxID_ANY );
    sizer->Add( m_window , 1 , wxALL | wxEXPAND );

    this->SetSizer( sizer );
    sizer->SetSizeHints(this);
    sizer->Layout();
}

RheiaHtmlLoggerPage::~RheiaHtmlLoggerPage()
{
    m_logger->m_window = NULL;
}

void RheiaHtmlLoggerPage::OnPageClosed()
{
    m_logger->m_window = NULL;
}

void RheiaHtmlLoggerPage::SetPage( const wxString& page )
{
    m_window->SetPage( page );
}
