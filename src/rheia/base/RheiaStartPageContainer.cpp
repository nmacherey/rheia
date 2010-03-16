/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
* @file RheiaStartPageContainer.cpp
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/

#include "RheiaStartPageContainer.h"
#include "RheiaConfigurationManager.h"
#include "RheiaStandardPaths.h"
#include "RheiaDebug.h"
#include "RheiaHtmlComposer.h"
#include "RheiaToolBarManager.h"
 
#include <wx/image.h>
#include "webcontrol.h" 
#include "dom.h" 
#include <wx/sizer.h>

BEGIN_EVENT_TABLE( RheiaStartPageContainer , wxEvtHandler )

END_EVENT_TABLE()

RheiaStartPageContainer::RheiaStartPageContainer( RheiaManagedFrame* parent, const wxString& file ):
	m_parent(parent),
	m_htmlfile(file)
{
	m_parent->PushEventHandler(this);
	m_parent->Connect( RheiaEVT_FRAME_CLOSING , RheiaFrameEventHandler(RheiaStartPageContainer::OnCloseParent) , NULL , this );
	
	/** build the toolbar */
}

RheiaStartPageContainer::~RheiaStartPageContainer()
{
	RheiaToolBarManager::Get(m_parent)->RemoveToolBar(wxT("Navigation Toolbar"));
	m_parent->RemoveEventHandler(this);
}

RheiaBookPage* RheiaStartPageContainer::BuildMainWindow( wxWindow* parent )
{
	return new RheiaStartPage(parent,m_htmlfile);
}

void RheiaStartPageContainer::OnCloseParent(RheiaFrameEvent& event)
{
	m_parent->RemoveEventHandler(this);
	event.Skip();
}

RheiaStartPage::RheiaStartPage( wxWindow* parent , const wxString& file ):
	RheiaBookPage(parent),
	m_file(file)
{
	wxPanel::Create( parent , wxID_ANY );
	wxBoxSizer* m_sizer = new wxBoxSizer(wxVERTICAL);
	
	// create the main browser control
    m_browser = new wxWebControl(this, wxID_ANY, wxPoint(0,0), wxSize(10,10));
	
	wxWebPreferences webprefs = wxWebControl::GetPreferences();
    webprefs.SetIntPref(wxT("network.cookie.cookieBehavior"), 2 /* disable all cookies */);
    webprefs.SetIntPref(wxT("privacy.popups.policy"), 2 /* reject popups */);    
	
	wxString path = RheiaFileFinder::FindFile(file);
    if( path.IsEmpty() )
        path = RheiaStandardPaths::DataDirectoryGlobal() + wxT("/") + file;
	// open the home location
    m_file = path;
	wxString m_uri_home = wxT("file://") + path;
	DoBuildStartPage();
	
    m_browser->OpenURI(m_uri_home);
	
	m_sizer->Add( m_browser , 1 , wxALL | wxEXPAND );
	m_browser->Connect( wxID_ANY , wxEVT_WEB_OPENURI , wxWebEventHandler(RheiaStartPage::OnOpenURI) , NULL , this );
	m_browser->Connect( wxID_ANY , wxEVT_WEB_LOCATIONCHANGE , wxWebEventHandler(RheiaStartPage::OnOpenURI) , NULL , this );
	SetSizer(m_sizer);
}

void RheiaStartPage::DoBuildStartPage()
{
	RheiaHtmlComposer* m_composer = new RheiaHtmlComposer();
	
	/** First build title and others */
	m_composer->AddCss(wxT("style.css"));
	m_composer->SetTitle(wxT("Rheia Framework : Rapid Application Development and Deployment"));
	
	m_composer->SetHeaderTitle( wxT("Rheia") , wxT("Framework") , wxT("http://www.rheia-framework.com") );
	m_composer->SetSlogan( wxT("Rapid Application Development and Deployment") );
	
	m_composer->SetHelperString1(wxT("Developers") , wxT("http://forge.rheia-framework.com") );
	m_composer->SetHelperString2(wxT("Web site") , wxT("http://www.rheia-framework.com") );
	m_composer->SetHelperString3(wxT("Tutorials") , wxT("http://forge.rheia-framework.com") );
	
	/** add navigation links */
	m_composer->AddNavigationLink(wxT("Start Page") , wxT("#") , true );
	
	/** add some content */
	xmlNode* content = m_composer->GetNodeContent();
	xmlNode* fwdiv = m_composer->AddMainDiv( content );
	xmlNode* fdiv = m_composer->AddVerticalSeparator( fwdiv );
	HtmlNodeAttr divopts;
	divopts.classAttr = wxT("col2 left");
	xmlNode* ldiv = m_composer->AddDiv( fdiv , divopts );
	
	HtmlNodeAttr attr2;
	attr2.classAttr = wxT("left");
	m_composer->AddH3(ldiv,wxT("Introduction") , attr2 );
	m_composer->AddClearer(ldiv);
	attr2.classAttr = wxT("content-separator");
	m_composer->AddDiv(ldiv,attr2);
	attr2.classAttr = wxT("");
	
	m_composer->AddClearer(ldiv);
	m_composer->AddParagraph(ldiv,wxT("Rheia is an application Framework for Rapid Application Development and Integration.") , attr2 );
	m_composer->AddParagraph(ldiv,wxT("Rheia is a component and plugin based application framework." ) , attr2 );						
	m_composer->AddParagraph(ldiv,wxT("Rheia is ready for maintainance and evolutability.") , attr2 );
									
	m_composer->AddClearer(ldiv);
	
	/** add this at the end or it wiil be in the footer */
	m_composer->AddClearer(fdiv);
	m_composer->SaveFile(m_file);
}

void RheiaStartPage::OnOpenURI( wxWebEvent& event )
{
	wxString href = event.GetHref();
	RheiaDebug::Log( href );
	event.Veto();
}
