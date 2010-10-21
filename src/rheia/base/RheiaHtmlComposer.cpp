/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
* @file RheiaHtmlComposer.cpp
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/
#include "RheiaHtmlComposer.h"

#include <map>

#include <RheiaManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaConfigurationPanel.h>
#include <RheiaPlatform.h>
#include <RheiaException.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#include <wx/dir.h>
#include <wx/filesys.h>
#include <wx/intl.h>
#include <wx/menu.h>
#include <wx/string.h>
#include <wx/dynlib.h>
#include <wx/filesys.h>
#include <wx/progdlg.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <wx/msgdlg.h>
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/stdpaths.h>

IMPLEMENT_DYNAMIC_CLASS(RheiaHtmlComposer,wxObject)

RheiaHtmlComposer::RheiaHtmlComposer()
{
	wxString basedoc = wxT("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html></html>");
	m_doc = xmlParseMemory(rcU2C(basedoc),basedoc.Len());
	m_root = xmlDocGetRootElement( m_doc );
	/*xmlNewProp( m_root, (const xmlChar*) "xmlns", (const xmlChar*) "http://www.w3.org/1999/xhtml" );
	xmlNewProp( m_root, (const xmlChar*) "dir", (const xmlChar*) "ltr" );*/
	//xmlDocSetRootElement( m_doc , m_root );

	BuildHead();
	BuildBody();
	BuildHeader();
	BuildNavigator();
	BuildContent();
	BuildFooter();
}

void RheiaHtmlComposer::SaveFile( const wxString& file )
{
	xmlSaveFormatFileEnc(rcU2C(file) , m_doc , "UTF-8" , 1);
}

RheiaHtmlComposer::~RheiaHtmlComposer()
{
	xmlFreeDoc( m_doc );
}

void RheiaHtmlComposer::BuildHead()
{
	m_head = xmlNewNode(NULL , (const xmlChar*) "head");
	
	xmlNode* hw1 = xmlNewNode(NULL , (const xmlChar*) "meta");
	xmlNewProp(hw1,(const xmlChar*) "http-equiv" , (const xmlChar*) "content-type" );
	xmlNewProp(hw1,(const xmlChar*) "content" , (const xmlChar*) "text/html; charset=UTF-8" );
	
	xmlAddChild( m_head , hw1 );
	xmlAddChild( m_root , m_head );
}

void RheiaHtmlComposer::BuildBody()
{
	m_body = xmlNewNode(NULL , (const xmlChar*) "body");
	xmlNewProp(m_body,(const xmlChar*) "id" , (const xmlChar*) "top" );
	xmlAddChild( m_root , m_body );
}

void RheiaHtmlComposer::BuildHeader()
{
	xmlNode* hw1 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw1,(const xmlChar*) "id" , (const xmlChar*) "header-wrapper" );
	
	xmlNode* hw2 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw2,(const xmlChar*) "id" , (const xmlChar*) "header-wrapper-2" );
	
	xmlNode* cw = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(cw,(const xmlChar*) "class" , (const xmlChar*) "center-wrapper" );
	
	m_header = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_header,(const xmlChar*) "id" , (const xmlChar*) "header" );
	
	m_headerLogo = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_headerLogo,(const xmlChar*) "id" , (const xmlChar*) "logo" );
	
	xmlNode* hdrHelp = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hdrHelp,(const xmlChar*) "id" , (const xmlChar*) "help-wrapper" );
	
	m_headerHelp = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_headerHelp,(const xmlChar*) "id" , (const xmlChar*) "help" );
	
	xmlAddChild( hdrHelp , m_headerHelp );
	
	xmlAddChild( m_header , m_headerLogo );
	xmlAddChild( m_header , hdrHelp );
	
	xmlAddChild( cw , m_header );
	xmlAddChild( hw2 , cw );
	xmlAddChild( hw1 , hw2 );
	xmlAddChild( m_body , hw1 );
}

void RheiaHtmlComposer::BuildNavigator()
{
	xmlNode* hw1 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw1,(const xmlChar*) "id" , (const xmlChar*) "navigation-wrapper" );
	
	xmlNode* hw2 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw2,(const xmlChar*) "id" , (const xmlChar*) "navigation-wrapper-2" );
	
	xmlNode* cw = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(cw,(const xmlChar*) "class" , (const xmlChar*) "center-wrapper" );
	
	xmlNode* nv = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(nv,(const xmlChar*) "id" , (const xmlChar*) "navigation" );
	
	m_navigator = xmlNewNode(NULL , (const xmlChar*) "ul");
	xmlNewProp(m_navigator,(const xmlChar*) "class" , (const xmlChar*) "tabbed" );
	xmlAddChild( nv , m_navigator );
	AddClearer( nv );
	
	xmlAddChild( cw , nv );
	xmlAddChild( hw2 , cw );
	xmlAddChild( hw1 , hw2 );
	xmlAddChild( m_body , hw1 );
}

void RheiaHtmlComposer::BuildContent()
{
	xmlNode* hw1 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw1,(const xmlChar*) "id" , (const xmlChar*) "content-wrapper" );
	
	xmlNode* hw2 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw2,(const xmlChar*) "class" , (const xmlChar*) "center-wrapper" );
	
	m_content = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_content,(const xmlChar*) "class" , (const xmlChar*) "content" );
	
	xmlAddChild( hw2 , m_content );
	xmlAddChild( hw1 , hw2 );
	xmlAddChild( m_body , hw1 );
}

void RheiaHtmlComposer::BuildFooter()
{
	xmlNode* hw1 = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(hw1,(const xmlChar*) "id" , (const xmlChar*) "footer-wrapper" );
	
	m_footer = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_footer,(const xmlChar*) "class" , (const xmlChar*) "center-wrapper" );
	
	xmlNode* m_footerLeft = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_footerLeft,(const xmlChar*) "class" , (const xmlChar*) "left" );
	
	xmlNode* m_footerRight = xmlNewNode(NULL , (const xmlChar*) "div");
	xmlNewProp(m_footerRight,(const xmlChar*) "class" , (const xmlChar*) "right" );
	
	xmlAddChild( m_footer , m_footerLeft );
	xmlAddChild( m_footer , m_footerRight );
	AddClearer( m_footer );
	
	xmlAddChild( hw1 , m_footer );
	xmlAddChild( m_body , hw1 );
}

void RheiaHtmlComposer::AddCss( const wxString& filepath )
{
	xmlNode* css = xmlNewNode(NULL,(const xmlChar*) "link" );
	xmlNewProp(css,(const xmlChar*) "rel" , (const xmlChar*) "stylesheet" );
	xmlNewProp(css,(const xmlChar*) "type" , (const xmlChar*) "text/css" );
	xmlNewProp(css,(const xmlChar*) "media" , (const xmlChar*) "screen" );
	xmlNewProp(css,(const xmlChar*) "href" , rxU2C(filepath) );
	xmlAddChild( m_head , css );
}

void RheiaHtmlComposer::SetTitle( const wxString& title )
{
	xmlNode* ntitle = xmlNewNode(NULL,(const xmlChar*) "title" );
	xmlNodeSetContent( ntitle , rxU2C(title) );
	xmlAddChild( m_head , ntitle );
}

void RheiaHtmlComposer::SetHeaderTitle(const wxString& title1, const wxString& title2 , const wxString& href )
{
	xmlNode* t1 = xmlNewNode(NULL,(const xmlChar*) "h1" );
	xmlNewProp(t1,(const xmlChar*) "id" , (const xmlChar*) "site-title" );
	
	wxString ref = href;
	if( ref.IsEmpty() )
		ref = wxT("#");
		
	xmlNode* a1 = xmlNewNode(NULL,(const xmlChar*) "a" );
	xmlNewProp(a1,(const xmlChar*) "href" , rxU2C(ref) );
	xmlNodeSetContent( a1,rxU2C(title1) );
	xmlNewChild( a1 , NULL , (const xmlChar*) "span" , rxU2C(title2) );
	xmlAddChild( t1 , a1 );
	
	xmlAddChild( m_headerLogo , t1 );
}

void RheiaHtmlComposer::SetSlogan(const wxString& slogan )
{
	xmlNode* t1 = xmlNewNode(NULL,(const xmlChar*) "h2" );
	xmlNewProp(t1,(const xmlChar*) "id" , (const xmlChar*) "site-slogan" );
	xmlNodeSetContent( t1,rxU2C(slogan) );
	
	xmlAddChild( m_headerLogo , t1 );
}

void RheiaHtmlComposer::SetHelperString1( const wxString& str, const wxString& href )
{
	xmlNode* t1 = xmlNewNode(NULL,(const xmlChar*) "a" );
	
	wxString ref = href;
	if( ref.IsEmpty() )
		ref = wxT("#");
		
	xmlNewProp(t1,(const xmlChar*) "href" , rxU2C(href) );
	xmlNodeSetContent( t1,rxU2C(str) );
	
	xmlNode* a1 = xmlNewNode(NULL,(const xmlChar*) "span" );
	xmlNewProp(a1,(const xmlChar*) "class" , (const xmlChar*) "text-separator" );
	xmlNodeSetContent( a1 , (const xmlChar*) "|" );
	
	xmlAddChild( m_headerHelp , t1 );
	xmlAddChild( m_headerHelp , a1 );
}

void RheiaHtmlComposer::SetHelperString2( const wxString& str, const wxString& href )
{
	xmlNode* t1 = xmlNewNode(NULL,(const xmlChar*) "a" );
	
	wxString ref = href;
	if( ref.IsEmpty() )
		ref = wxT("#");
		
	xmlNewProp(t1,(const xmlChar*) "href" , rxU2C(href) );
	xmlNodeSetContent( t1,rxU2C(str) );
	
	xmlNode* a1 = xmlNewNode(NULL,(const xmlChar*) "span" );
	xmlNewProp(a1,(const xmlChar*) "class" , (const xmlChar*) "text-separator" );
	xmlNodeSetContent( a1 , (const xmlChar*) "|" );
	
	xmlAddChild( m_headerHelp , t1 );
	xmlAddChild( m_headerHelp , a1 );
}

void RheiaHtmlComposer::SetHelperString3( const wxString& str, const wxString& href )
{
	xmlNode* t1 = xmlNewNode(NULL,(const xmlChar*) "a" );
	
	wxString ref = href;
	if( ref.IsEmpty() )
		ref = wxT("#");
		
	xmlNewProp(t1,(const xmlChar*) "href" , rxU2C(href) );
	xmlNodeSetContent( t1,rxU2C(str) );
	
	xmlAddChild( m_headerHelp , t1 );
}

void RheiaHtmlComposer::AddNavigationLink( const wxString& name , const wxString& href , bool isMe )
{
	xmlNode* t1 = xmlNewNode(NULL,(const xmlChar*) "li" );
	
	wxString ref = href;
	if( ref.IsEmpty() )
		ref = wxT("#");
		
	if( isMe )
		xmlNewProp(t1,(const xmlChar*) "class" , (const xmlChar*) "current_page_item" );
	
	xmlNode* a1 = xmlNewNode(NULL,(const xmlChar*) "a" );
	xmlNewProp(a1,(const xmlChar*) "href" , rxU2C(ref) );
	xmlNodeSetContent( a1 , rxU2C(name) );
	
	xmlAddChild( t1 , a1 );
	xmlAddChild( m_navigator , t1 );
}

xmlNode* RheiaHtmlComposer::AddNode( xmlNode* parent , const wxString& name, const HtmlNodeAttr& attr )
{
	xmlNode* t1 = xmlNewNode(NULL,rxU2C(name) );
	
	if( !attr.idAttr.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "id" , rxU2C(attr.idAttr) );
	
	if( !attr.classAttr.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "class" , rxU2C(attr.classAttr) );
		
	if( !attr.styleAttr.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "style" , rxU2C(attr.styleAttr) );
	
	if( !attr.hrefAttr.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "href" , rxU2C(attr.hrefAttr) );

	xmlAddChild( parent , t1 );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddDiv( xmlNode* root , const HtmlNodeAttr& divopts )
{
	xmlNode* t1 = AddNode( root , wxT("div") , divopts );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddFeaturedWrapperDiv( xmlNode* root )
{
	HtmlNodeAttr divopts;
	divopts.idAttr = wxT("featured-wrapper");
	
	return AddDiv(root,divopts);
}

xmlNode* RheiaHtmlComposer::AddFeaturedDiv( xmlNode* root )
{
	HtmlNodeAttr divopts;
	divopts.idAttr = wxT("featured");
	
	return AddDiv(root,divopts);
}

xmlNode* RheiaHtmlComposer::AddMainDiv( xmlNode* root )
{
	HtmlNodeAttr divopts;
	divopts.idAttr = wxT("main");
	
	return AddDiv(root,divopts);
}

xmlNode* RheiaHtmlComposer::AddH1( xmlNode* root , const wxString& content, const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( root , wxT("h1") , attr );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddH2( xmlNode* root , const wxString& content, const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( root , wxT("h2") , attr );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddH3( xmlNode* root , const wxString& content, const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( root , wxT("h3") , attr );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddSpan( xmlNode* root , const wxString& content , const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( root , wxT("span") , attr );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddParagraph( xmlNode* root, const wxString& content , const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( root , wxT("p") , attr );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddHRef( xmlNode* root, const wxString& content , const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( root , wxT("a") , attr );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddImage( xmlNode* root , const HtmlImgNodeAttr& attr )
{
	HtmlNodeAttr opt;
	xmlNode* t1 = AddNode( root , wxT("img") , opt );
	
	if( !attr.src.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "src" , rxU2C(attr.src) );
	
	if( !attr.width.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "width" , rxU2C(attr.width) );
		
	if( !attr.height.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "height" , rxU2C(attr.height) );
	
	if( !attr.classAttr.IsEmpty() )
		xmlNewProp(t1,(const xmlChar*) "class" , rxU2C(attr.classAttr) );
		
	return t1;
}

void RheiaHtmlComposer::AddClearer( xmlNode* parent )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("clearer");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	
	xmlNodeSetContent( t1 , (const xmlChar*) "&nbsp;" );
}

xmlNode* RheiaHtmlComposer::AddVerticalSeparator( xmlNode* parent )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("separator-vertical");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	
	return t1;
}

xmlNode* RheiaHtmlComposer::AddList( xmlNode* parent , const HtmlListElementArray& elements )
{
	HtmlNodeAttr opt;
	xmlNode* t1 = AddNode( parent , wxT("ul") , opt );
	
	for( unsigned int i = 0; i< elements.GetCount() ; ++i )
	{
		xmlNode* li = AddNode( t1 , wxT("li") , opt );
		
		if( !elements[i]->spantext.IsEmpty() )
		{
			xmlNode* span = AddNode( li , wxT("span") , opt );
			xmlNodeSetContent( span , rxU2C(elements[i]->spantext) );
		}
		
		if( !elements[i]->href.IsEmpty() && !elements[i]->hrefcontent.IsEmpty() )
		{
			HtmlNodeAttr opt2;
			opt2.hrefAttr = elements[i]->href;
			xmlNode* a = AddNode( li , wxT("a") , opt2 );
			xmlNodeSetContent( a , rxU2C(elements[i]->hrefcontent) );
		}
		
		if( !elements[i]->content.IsEmpty() )
			xmlNodeSetContent( li , rxU2C(elements[i]->content) );
	}
	
	return t1;
}

xmlNode* RheiaHtmlComposer::AddSortedList( xmlNode* parent , const HtmlListElementArray& elements )
{
	HtmlNodeAttr opt;
	xmlNode* t1 = AddNode( parent , wxT("ol") , opt );
	
	for( unsigned int i = 0; i< elements.GetCount() ; ++i )
	{
		xmlNode* li = AddNode( t1 , wxT("li") , opt );
		
		if( !elements[i]->spantext.IsEmpty() )
		{
			xmlNode* span = AddNode( li , wxT("span") , opt );
			xmlNodeSetContent( span , rxU2C(elements[i]->spantext) );
		}
		
		if( !elements[i]->href.IsEmpty() && !elements[i]->hrefcontent.IsEmpty() )
		{
			HtmlNodeAttr opt2;
			opt2.hrefAttr = elements[i]->href;
			xmlNode* a = AddNode( li , wxT("a") , opt2 );
			xmlNodeSetContent( a , rxU2C(elements[i]->hrefcontent) );
		}
		
		if( !elements[i]->content.IsEmpty() )
			xmlNodeSetContent( li , rxU2C(elements[i]->content) );
	}
	
	return t1;
}

xmlNode* RheiaHtmlComposer::AddDefList( xmlNode* parent , const HtmlDefListElementArray& elements )
{
	HtmlNodeAttr opt;
	xmlNode* t1 = AddNode( parent , wxT("dl") , opt );
	
	for( unsigned int i = 0; i< elements.GetCount() ; ++i )
	{
		wxString name = elements[i]->isTitle ? wxT("dt") : wxT("dl");
		xmlNode* li = AddNode( t1 , name , opt );
		
		if( !elements[i]->spantext.IsEmpty() )
		{
			xmlNode* span = AddNode( li , wxT("span") , opt );
			xmlNodeSetContent( span , rxU2C(elements[i]->spantext) );
		}
		
		if( !elements[i]->href.IsEmpty() && !elements[i]->hrefcontent.IsEmpty() )
		{
			HtmlNodeAttr opt2;
			opt2.hrefAttr = elements[i]->href;
			xmlNode* a = AddNode( li , wxT("a") , opt2 );
			xmlNodeSetContent( a , rxU2C(elements[i]->hrefcontent) );
		}
		
		if( !elements[i]->content.IsEmpty() )
			xmlNodeSetContent( li , rxU2C(elements[i]->content) );
	}
	
	return t1;
}

xmlNode* RheiaHtmlComposer::AddBlockquote( xmlNode* parent )
{
	HtmlNodeAttr opt;
	xmlNode* t1 = AddNode( parent , wxT("blockquote") , opt );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddCite( xmlNode* parent , const wxString& content )
{
	HtmlNodeAttr opt;
	xmlNode* t1 = AddNode( parent , wxT("cite") , opt );
	xmlNodeSetContent( t1 , rxU2C(content) );
	return t1;
}

xmlNode* RheiaHtmlComposer::AddSuccessMessage( xmlNode* parent , const wxString& content )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("success");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	xmlNodeSetContent( t1 , rxU2C(content) );
	
	return t1;
}

xmlNode* RheiaHtmlComposer::AddNoticeMessage( xmlNode* parent , const wxString& content )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("notice");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	xmlNodeSetContent( t1 , rxU2C(content) );
	
	return t1;
}

xmlNode* RheiaHtmlComposer::AddErrorMessage( xmlNode* parent , const wxString& content )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("error");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	xmlNodeSetContent( t1 , rxU2C(content) );
	
	return t1;
}

void RheiaHtmlComposer::AddSeparator( xmlNode* parent )
{
	HtmlNodeAttr opt;
	AddNode( parent , wxT("content_separator") , opt );
}

xmlNode* RheiaHtmlComposer::AddTable( xmlNode* parent , const HtmlTableLineArray& lines , const HtmlNodeAttr& attr )
{
	xmlNode* t1 = AddNode( parent , wxT("table") , attr );
	
	for( unsigned int i = 0; i < lines.GetCount() ; ++i )
	{
		xmlNode* tr = AddNode(t1, wxT("tr") , lines[i]->attr );
		
		for( unsigned int j = 0; j < lines[i]->elements.GetCount() ; ++j )
		{
			wxString name = lines[i]->elements[j]->isTitle ? wxT("th") : wxT("td");
			HtmlNodeAttr opt;
			xmlNode* li = AddNode( tr , name , opt );
		
			if( !lines[i]->elements[j]->spantext.IsEmpty() )
			{
				xmlNode* span = AddNode( li , wxT("span") , opt );
				xmlNodeSetContent( span , rxU2C(lines[i]->elements[j]->spantext) );
			}
			
			if( !lines[i]->elements[j]->href.IsEmpty() && !lines[i]->elements[j]->hrefcontent.IsEmpty() )
			{
				HtmlNodeAttr opt2;
				opt2.hrefAttr = lines[i]->elements[j]->href;
				xmlNode* a = AddNode( li , wxT("a") , opt2 );
				xmlNodeSetContent( a , rxU2C(lines[i]->elements[j]->hrefcontent) );
			}
			
			if( !lines[i]->elements[j]->content.IsEmpty() )
				xmlNodeSetContent( li , rxU2C(lines[i]->elements[j]->content) );
			}
	}
	
	return t1;
}

xmlNode* RheiaHtmlComposer::CreateSidebarWrapper( xmlNode* parent )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("sidebar-wrapper");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	
	opt.classAttr = wxT("sidebar");
	xmlNode* t2 = AddNode( t1 , wxT("div") , opt );
	
	return t2;
}

xmlNode* RheiaHtmlComposer::AddBoxContent( xmlNode* parent , const HtmlBoxContent& content )
{
	HtmlNodeAttr opt;
	opt.classAttr = wxT("box");
	xmlNode* t1 = AddNode( parent , wxT("div") , opt );
	
	opt.classAttr = wxT("box-title");
	xmlNode* t2 = AddNode( t1 , wxT("div") , opt );
	xmlNodeSetContent(t2,rxU2C(content.title));
	
	opt.classAttr = wxT("box-content");
	xmlNode* t3 = AddNode( t1 , wxT("div") , opt );
	
	opt.classAttr = wxT("nice-list");
	xmlNode* t4 = AddNode( t3 , wxT("ul") , opt );
	opt.classAttr = wxEmptyString;
	
	for( unsigned int i = 0; i< content.elements.GetCount() ; ++i )
	{
		xmlNode* li = AddNode( t4 , wxT("li") , opt );
		
		if( !content.elements[i]->spantext.IsEmpty() )
		{
			xmlNode* span = AddNode( li , wxT("span") , opt );
			xmlNodeSetContent( span , rxU2C(content.elements[i]->spantext) );
		}
		
		if( !content.elements[i]->href.IsEmpty() && !content.elements[i]->hrefcontent.IsEmpty() )
		{
			HtmlNodeAttr opt2;
			opt2.hrefAttr = content.elements[i]->href;
			xmlNode* a = AddNode( li , wxT("a") , opt2 );
			xmlNodeSetContent( a , rxU2C(content.elements[i]->hrefcontent) );
		}
		
		if( !content.elements[i]->content.IsEmpty() )
			xmlNodeSetContent( li , rxU2C(content.elements[i]->content) );
	}
	
	return t1;
}