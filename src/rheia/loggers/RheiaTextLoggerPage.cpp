/**
*   @file RheiaTextLoggerPage.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 18-May-2009
*   @version 0.0.1
*/
#include "RheiaTextLoggerPage.h"
#include "RheiaTextLogger.h"


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
#include <wx/richtext/richtextxml.h>

RheiaTextLoggerPage::RheiaTextLoggerPage( wxWindow* parent , RheiaTextLogger* logger ):
    RheiaBookPage( parent ),
    m_logger( logger )
{
    wxPanel::Create( parent , wxID_ANY );
    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );

    m_window = new wxRichTextCtrl( this , wxID_ANY , wxEmptyString , wxDefaultPosition , wxDefaultSize , wxRE_READONLY | wxRE_MULTILINE );
    sizer->Add( m_window , 1 , wxALL | wxEXPAND );

    this->SetSizer( sizer );
    sizer->SetSizeHints(this);
    sizer->Layout();
}

RheiaTextLoggerPage::~RheiaTextLoggerPage()
{
    //m_logger->m_window = NULL;
}

void RheiaTextLoggerPage::OnPageClosed()
{
    m_logger->m_window = NULL;
}

void RheiaTextLoggerPage::GetContent(wxRichTextBuffer* content)
{
    content->Copy(m_window->GetBuffer());
}

void RheiaTextLoggerPage::SetContent(wxRichTextBuffer* content)
{
    m_window->GetBuffer().Copy(*content);
}


