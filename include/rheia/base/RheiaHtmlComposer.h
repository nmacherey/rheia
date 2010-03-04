/**
* @file RheiaHtmlComposer.h
* @author Nicolas Macherey (nm@graymat.fr)
* @version 1.0.1
* @date 2-March-2010
*/
#ifndef RheiaHtmlComposer_h_
#define RheiaHtmlComposer_h_

#include "RheiaBaseSettings.h"
#include "RheiaManager.h"
#include "RheiaGlobals.h"
#include <vector>

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlAttr xmlAttr;

WX_DEFINE_ARRAY( xmlNode* , xmlNodeArray );
WX_DEFINE_ARRAY( xmlAttr* , xmlAttrArray );

/** enumerates the HtmlPart types helping to choose the root node */
enum HtmlPartType
{
	hptHeader = 0,
	hptBody,
	hptFooter
};

/** @struct HtmlNodeAttr
 * @brief basic options to add a div in a node
 */
struct HtmlNodeAttr
{
	HtmlNodeAttr(){};
	HtmlNodeAttr(const HtmlNodeAttr& rhs):
		idAttr(rhs.idAttr),
		classAttr(rhs.classAttr),
		styleAttr(rhs.styleAttr),
		hrefAttr(rhs.hrefAttr){};
	
	wxString idAttr;
	wxString classAttr;
	wxString styleAttr;
	wxString hrefAttr;
};

/** @struct HtmlImgNodeAttr
 * @brief basic options to add a div in a node
 */
struct HtmlImgNodeAttr
{
	HtmlImgNodeAttr(){};
	HtmlImgNodeAttr(const HtmlImgNodeAttr& rhs):
		src(rhs.src),
		width(rhs.width),
		height(rhs.height),
		alt(rhs.alt),
		classAttr(rhs.classAttr){};
	
	wxString src;
	wxString width;
	wxString height;
	wxString alt;
	wxString classAttr;
};

/** @struct HtmlListElement
 * @brief class for displaying a list element
 */
struct HtmlListElement
{
	HtmlListElement(){};
	HtmlListElement(const HtmlListElement& rhs):
		spantext(rhs.spantext),
		href(rhs.href),
		hrefcontent(rhs.hrefcontent),
		content(rhs.content)
	{};
	
	wxString spantext;
	wxString href;
	wxString hrefcontent;
	wxString content;
};

/** @struct HtmlDefListElement
 * @brief class for displaying a list element
 */
struct HtmlDefListElement
{
	HtmlDefListElement():isTitle(false){};
	HtmlDefListElement(const HtmlDefListElement& rhs):
		spantext(rhs.spantext),
		href(rhs.href),
		hrefcontent(rhs.hrefcontent),
		content(rhs.content),
		isTitle(rhs.isTitle)
	{};
	
	wxString spantext;
	wxString href;
	wxString hrefcontent;
	wxString content;
	bool isTitle;
};

/** @struct HtmlTableElement
 * @brief class for displaying a table element
 */
struct HtmlTableElement
{
	HtmlTableElement():isTitle(false){};
	HtmlTableElement(const HtmlTableElement& rhs):
		spantext(rhs.spantext),
		href(rhs.href),
		hrefcontent(rhs.hrefcontent),
		content(rhs.content),
		isTitle(rhs.isTitle)
	{};
	
	wxString spantext;
	wxString href;
	wxString hrefcontent;
	wxString content;
	bool isTitle;
};

/** define an array of HtmlTableElement */
WX_DEFINE_ARRAY( HtmlTableElement* , HtmlTableElementArray );

/** @struct HtmlTableLine
 * @brief class for displaying a table lines
 */
struct HtmlTableLine
{
	HtmlTableLine(){};
	HtmlTableLine(const HtmlTableLine& rhs):
		attr(rhs.attr),
		elements(rhs.elements)
	{};
	
	HtmlNodeAttr attr;
	HtmlTableElementArray elements;
};

/** define an array of HtmlTableElement */
WX_DEFINE_ARRAY( HtmlTableLine* , HtmlTableLineArray );

/** define an array of HtmlListElement */
WX_DEFINE_ARRAY( HtmlListElement* , HtmlListElementArray );

/** define an array of HtmlDefListElement */
WX_DEFINE_ARRAY( HtmlDefListElement* , HtmlDefListElementArray );


/** @struct HtmlBoxContent
 * @brief class for displaying a box in a side bar
 */
struct HtmlBoxContent
{
	HtmlBoxContent(){};
	HtmlBoxContent(const HtmlBoxContent& rhs):
		title(rhs.title),
		attr(rhs.attr),
		elements(rhs.elements)
	{};
	
	wxString title;
	HtmlNodeAttr attr;
	HtmlListElementArray elements;
};

/**
 * @class RheiaHtmlComposer
 * @brief Main class for managing html pages contents in your applications
 * 
 * @author Nicolas Macherey (nm@graymat.fr)
 * @version 1.0.1
 * @date 2-March-2010
 */
class BASE_DLLEXPORT RheiaHtmlComposer : public wxObject
{
	DECLARE_DYNAMIC_CLASS(RheiaHtmlComposer);
	
public :
	/** ctor 
	 * THis method will create the document and basic nodes 
	 */
	RheiaHtmlComposer();
	
	/** dtor */
	virtual ~RheiaHtmlComposer();
	
	/** save the file in the given path */
	void SaveFile( const wxString& file );
	
	/********************************************************************************************
	 * CSS CONTENT MANAGEMENT
	********************************************************************************************/
	/** Add the given css file into the list 
	 * @param full file path to the css 
	 */
	void AddCss( const wxString& filepath );
	
	/********************************************************************************************
	 * PAGE TITLE MANGEMENT
	********************************************************************************************/
	/** Set the Html page title */
	void SetTitle( const wxString& title );
	
	/********************************************************************************************
	 * BODY HEADER MANAGEMENT
	********************************************************************************************/
	/** Here are the page title and slogan given in arguments for that page 
	 * Page displayed titles are in two parts, like Rheia Framework 
	 * @param title1 first title's part
	 * @param title2 second title's part
	 * @param href fill it with a link if you want to link the logo to a specific html link
	 */
	void SetHeaderTitle(const wxString& title1, const wxString& title2 , const wxString& href );
	
	/** Set the page slogan */
	void SetSlogan( const wxString& slogan );
	
	/** Set the help string 1 
	 * @param str string to set 
	 * @param href link reference if you want to link the user to a specific location 
	 */
	void SetHelperString1( const wxString& str, const wxString& href );
	
	/** Set the help string 2 
	 * @param str string to set 
	 * @param href link reference if you want to link the user to a specific location 
	 */
	void SetHelperString2( const wxString& str, const wxString& href );
	
	/** Set the help string 3 
	 * @param str string to set 
	 * @param href link reference if you want to link the user to a specific location 
	 */
	void SetHelperString3( const wxString& str, const wxString& href );
	
	/********************************************************************************************
	 * BODY NAVIGATION BAR MANAGEMENT
	********************************************************************************************/
	
	/** Add a navigation link in the main page 
	 * @param name displayed link name 
	 * @param href reference where the link points to
	 * @param isMe specified if I am concerned by this page 
	 */
	void AddNavigationLink( const wxString& name , const wxString& href , bool isMe = false );
	
	/********************************************************************************************
	 * CONTENT MANAGEMENT
	********************************************************************************************/
	
	/** Add a featured div to the given parent node 
	 * @param root node in which the featured wrapper shall be aded
	 * @param divopts attributes options for that div
	 */
	xmlNode* AddDiv( xmlNode* root , const HtmlNodeAttr& divopts );
	
	/** Add a featured-wrapper div to the given parent node 
	 * @param root node in which the featured wrapper shall be aded
	 */
	xmlNode* AddFeaturedWrapperDiv( xmlNode* root );
	
	/** Add a featured div to the given parent node 
	 * @param root node in which the featured wrapper shall be aded
	 */
	xmlNode* AddFeaturedDiv( xmlNode* root );
	
	/** Add a main div to the given parent node 
	 * @param root node in which the featured wrapper shall be aded
	 */
	xmlNode* AddMainDiv( xmlNode* root );
	
	/** Add an h1 */
	xmlNode* AddH1( xmlNode* root , const wxString& content, const HtmlNodeAttr& attr );
	
	/** Add an h2 */
	xmlNode* AddH2( xmlNode* root , const wxString& content, const HtmlNodeAttr& attr );
	
	/** Add an h3 */
	xmlNode* AddH3( xmlNode* root , const wxString& content, const HtmlNodeAttr& attr );
	
	/** Add a span */
	xmlNode* AddSpan( xmlNode* root , const wxString& content , const HtmlNodeAttr& attr );
	
	/** Add a paragraph */
	xmlNode* AddParagraph( xmlNode* root, const wxString& content , const HtmlNodeAttr& attr );
	
	/** Add a hyperlink reference */
	xmlNode* AddHRef( xmlNode* root, const wxString& content , const HtmlNodeAttr& attr );
	
	/** Add an image */
	xmlNode* AddImage( xmlNode* root , const HtmlImgNodeAttr& attr );
	
	/** Add a clearer */
	void AddClearer( xmlNode* parent );
	
	/** Add a vertical separator */
	xmlNode* AddVerticalSeparator( xmlNode* parent );
	
	/** Add list in the given root node */
	xmlNode* AddList( xmlNode* parent , const HtmlListElementArray& elements );
	
	/** Add definition list in the given root node */
	xmlNode* AddDefList( xmlNode* parent , const HtmlDefListElementArray& elements );
	
	/** Add sorted list in the given root node */
	xmlNode* AddSortedList( xmlNode* parent , const HtmlListElementArray& elements );
	
	/** Add a blockquote */
	xmlNode* AddBlockquote( xmlNode* parent );
	
	/** Add a cite */
	xmlNode* AddCite( xmlNode* parent , const wxString& content );
	
	/** Add a table in the root node */
	xmlNode* AddTable( xmlNode* parent , const HtmlTableLineArray& lines , const HtmlNodeAttr& attr );
	
	/** Add success message */
	xmlNode* AddSuccessMessage( xmlNode* parent , const wxString& content );
	
	/** Add notice message */
	xmlNode* AddNoticeMessage( xmlNode* parent , const wxString& content );
	
	/** Add error message */
	xmlNode* AddErrorMessage( xmlNode* parent , const wxString& content );
	
	/** Create a side bar wrapper */
	xmlNode* CreateSidebarWrapper( xmlNode* parent );
	
	/** Add a box content */
	xmlNode* AddBoxContent( xmlNode* parent , const HtmlBoxContent& content );
	
	/** add a node of the given name and the given attributes in the given root node */
	xmlNode* AddNode( xmlNode* parent , const wxString& name, const HtmlNodeAttr& attr );
	
	/** Add separator */
	void AddSeparator( xmlNode* parent );
	
	/** Get content node */
	xmlNode* GetNodeContent(){return m_content;};
	
private :
	/********************************************************************************************
	 * UTILITY FUNCTIONS
	********************************************************************************************/
	/** Builds the basic html head structre */
	void BuildHead();
	
	/** Builds the basic html body structre */
	void BuildBody();
	
	/** Builds the basic header structure in the body 
	 * @note that the header is contained in the body so you shall always 
	 * call BuildBody before
	 */
	void BuildHeader();
	
	/** Builds the basic navigator structure in the body 
	 * @note that the navigator is contained in the body so you shall always 
	 * call BuildBody before
	 */
	void BuildNavigator();
	
	/** Builds the basic content structure in the body 
	 * @note that the content is contained in the body so you shall always 
	 * call BuildBody before
	 */
	void BuildContent();
	
	/** Builds the basic html footer structre 
	 * @note that the footer is contained in the body so you shall always 
	 * call BuildBody before
	 */
	void BuildFooter();
	
private :
	
	xmlDoc* m_doc;
	xmlNode* m_root;
	xmlNode* m_head;
	xmlNode* m_body;
	
	xmlNode* m_title;
	xmlNode* m_header;
	xmlNode* m_headerLogo;
	xmlNode* m_headerHelp;
	xmlNode* m_navigator;
	xmlNode* m_content;
	xmlNode* m_footer;
	xmlNode* m_footerLeft;
	xmlNode* m_footerRight;
};

#endif
