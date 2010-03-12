#include <RheiaXmlManager.h>

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

/*! Global instance for the plugin manager */
template<> RheiaXmlManager* Mgr<RheiaXmlManager>::instance = 0;
template<> bool  Mgr<RheiaXmlManager>::isShutdown = false;

/********************************************************************************************************
* namespace for default node names for RheiaXmlManager
********************************************************************************************************/
namespace XmlManagerPaths
{

	/****************************************************************************************************
	* default root nodes and attributes
	****************************************************************************************************/
	/* color node */
	static wxString ColourNode = wxT("/colour");
	namespace ColourAttributes {
		static wxString Red	= wxT("red");
		static wxString Green = wxT("green");
		static wxString Blue = wxT("blue");
	};

	/* size node */
	static wxString SizeNode = wxT("/size");
	namespace SizeAttributes {
		static wxString WidthAttribute = wxT("width");
		static wxString HeightAttribute = wxT("height");
	};

	/* position node */
	static wxString PositionNode = wxT("/position");
	namespace PositionAttributes {
		static wxString XAttribute = wxT("x");
		static wxString YAttribute = wxT("y");
	};

	/* Array Node */
	static wxString ArrayNode = wxT("/array");
	namespace ArrayAttributes {
		static wxString ArrayType = wxT("type");
		namespace ArrayTypes {
			static wxString ArrayInt = wxT("wxArrayInt");
			static wxString ArrayDouble = wxT("wxArrayDouble");
			static wxString ArrayString = wxT("wxArrayString");
			static wxString ArrayBool = wxT("wxArrayBool");
			static wxString StdVectorInt = wxT("stdVectorInt");
			static wxString StdVectorDouble = wxT("stdVectorDouble");
			static wxString StdVectorString = wxT("stdVectorString");
			static wxString StdVectorBool = wxT("stdVectorBool");
		}
	};

	static wxString BinaryNode = wxT("/binary");
	namespace BinaryAttributes {
		static wxString CRCType = wxT("crc");
	};

	static wxString ArrayElementNode = wxT("ArrayElement");
	namespace ElementAttributes {
		static wxString ElementValue = wxT("value");
	};

	/* dynamic library node */
	static wxString DynLibNode = wxT("DynamicLibrary");
	namespace DynLibAttributes {
		static wxString DynLibName = wxT("path");
		static wxString DynLibPath = wxT("path");
		static wxString DynLibSubSystem = wxT("subsystem");
	};

	/* default attribute set */
	namespace DefaultAttributes {
		static wxString ValueAttribute = wxT("value");
		static wxString IntAttribute = wxT("int");
		static wxString BoolAttribute = wxT("bool");
		static wxString DoubleAttribute = wxT("double");
		static wxString StringAttribute  = wxT("string");
	};

};


wxString RheiaXmlManager::RheiaNodeGetContent( xmlNode* node )
{
	wxString str;
	xmlChar* content = xmlNodeGetContent( node );
	str = ( RheiaC2U( (const char*) content ) );
	xmlFree( content );

	return str;
}

wxString RheiaXmlManager::RheiaNodeGetProp( xmlChar* prop )
{
	wxString str;
	str = ( RheiaC2U( (const char*) prop ) );
	xmlFree( prop );

	return str;
}

inline void RheiaXmlManager::Collapse(wxString& str) const
{
	const wxChar *src = str.c_str();
	wxChar *dst = (wxChar*) src;
	wxChar c;
	size_t len = 0;

	while ((c = *src)) {
		++src;

		*dst = c;
		++dst;
		++len;

		if (c == _T('/'))
			while (*src == _T('/'))
				++src;
	}
	str.Truncate(len);
};

/*
*  Hack to enable Turkish language. wxString::Upper will convert lowercase 'i' to \u0130 instead of \u0069 in Turkish locale,
*  which will break the config file when used in a tag
*/
inline void to_upper(wxString& s)
{
#if wxCHECK_VERSION(2, 9, 0)
	wxStringCharType *p = const_cast<wxStringCharType*>(s.wx_str());
	wxStringCharType q;
#else
	wxChar *p = (wxChar*) s.c_str();
	wxChar q;
#endif
	size_t len = s.length()+1;
	for (; --len; ++p) {
		q = *p;
		if (q >= 'a' && q <= 'z')
			*p = q - 32;
	}
};

inline void to_lower(wxString& s)
{
#if wxCHECK_VERSION(2, 9, 0)
	wxStringCharType *p = const_cast<wxStringCharType*>(s.wx_str());
	wxStringCharType q;
#else
	wxChar *p = (wxChar*) s.c_str();
	wxChar q;
#endif
	size_t len = s.length()+1;
	for (; --len; ++p) {
		q = *p;
		if (q >= 'A' && q <= 'Z')
			*p = q + 32;
	}
};

xmlNode* RheiaXmlManager::AssertPath( wxString& path,
                                      xmlNode* rootNode )
{
	if ( rootNode == NULL )
		RheiaThrow( wxT("Error, you are trying to write xml elements in an inexistant xml node") );

	/**
		A path can be viewed as a directory, a key is an element contained in a path
		key and path are unique.
	*/
	Collapse(path);

	wxString illegal(_T(" -:.\"\'$&()[]<>+#"));
	size_t i = 0;
	while ((i = path.find_first_of(illegal, i)) != wxString::npos)
		path[i] = _T('_');

	xmlNode *localPath = rootNode;
	// THis works only when starting from the root node of the configuration file

	if (path.GetChar(0) == '/') { // absolute path
		path = path.Mid(1);
	}

	if (path.find(_T('/')) != wxString::npos) // need for path walking
		to_lower(path);

	wxString sub;
	wxArrayString SubPaths;

	/* Extract Sub Paths from path */

	while ( path.find(_T('/')) != wxString::npos) {
		sub = path.BeforeFirst(_T('/'));
		path = path.AfterFirst(_T('/'));
		SubPaths.Add( sub );
	}

	/* Now check all paths */
	for ( unsigned int i = 0; i < SubPaths.size() ; i++ ) {
		sub = SubPaths[i];

		if (sub.GetChar(0) < _T('a') || sub.GetChar(0) > _T('z')) {
			wxString msg = wxT("Your subpath : ");
			msg += sub;
			msg = msg + wxT(" is invalid please fix");
			RheiaThrow(msg);
		}

		xmlNode* subNode;
		subNode = localPath->children;

		/* locate subnode */
		while ( subNode != NULL ) {
			wxString nodeName = RheiaC2U( (const char*) subNode->name );
			if ( nodeName.IsSameAs(sub) ) {
				break;
			}
			subNode = subNode->next;
		}

		if ( subNode == NULL ) {
			subNode = xmlNewNode( NULL , rxU2C(sub) );
			xmlAddChild( localPath , subNode );
		}

		localPath = subNode;
	}

	to_upper(path);

	if (!path.IsEmpty() && (path.GetChar(0) < _T('A') || path.GetChar(0) > _T('Z')))
		RheiaThrow( wxT("Invalid key :") + path );

	return localPath;
}

void RheiaXmlManager::Clear(xmlNode *rootNode)
{
	xmlNode *sub = rootNode->children;
	xmlNode *child;

	while ( sub != NULL ) {
		child = sub;
		sub = sub->next;
		xmlReplaceNode( child , NULL );
	}
}

void RheiaXmlManager::Delete(xmlDoc* doc)
{
//    RheiaConfigurationPattern * bld = RheiaConfigurationPattern::Get();
//    wxString ns(cbC2U(root->Value()));
//
//    root->Clear();
//    doc->RootElement()->RemoveChild(root);
//
//    wxCriticalSectionLocker(bld->cs);
//    RheiaConfigurationManagerMap::iterator it = bld->namespaces.find(ns);
//    if(it != bld->namespaces.end())
//        bld->namespaces.erase(it);
//
//    delete this;
}

/* ------------------------------------------------------------------------------------------------------------------
*  Utility functions for writing nodes
*/
xmlNode* RheiaXmlManager::GetUniqElement(xmlNode* p, const wxString& q)
{
	if ( p == NULL )
		RheiaThrow( wxT("Error in GetUniqElement : trying to get a child from an unexisting node !!") );

	xmlNode* r = p->children;

	while ( r != NULL ) {
		wxString nodeName = RheiaC2U( (const char*) r->name );
		if ( nodeName.IsSameAs( q ) )
			return r;

		r = r->next;
	}
	r = xmlNewNode( NULL , rxU2C( q ) );
	xmlAddChild( p , r );
	return  xmlAddChild( p , r );
}

void RheiaXmlManager::SetNodeText(xmlNode* n, const char  *t)
{
	if ( n == NULL )
		RheiaThrow( wxT("Error in SetNodeText : trying to set the content of an unexisting node !!") );

	xmlNodeSetContent( n , (const xmlChar*) t );
}


/* ------------------------------------------------------------------------------------------------------------------
*  Write and read values
*  Regardless of namespaces, the string keys app_path and data_path always refer to the location of the application's executable
*  and the data path, respectively. These values are never saved to the configuration, but kept in static variables.
*  The application makes use of this by "writing" to the configuration file after determining these values at runtime.
*/
void RheiaXmlManager::Write(const wxString& path,  const wxString& value, xmlNode* rootNode, bool ignoreEmpty)
{
	if (ignoreEmpty && value.IsEmpty()) {
		//UnSet(path);
		return;
	}
	wxString key(path);
	xmlNode* e = AssertPath(key, rootNode);
	xmlNode *str = GetUniqElement(e, key);
	xmlNodeSetContent(str, rxU2C(value) );
}

void RheiaXmlManager::Write(const wxString& path, const char* str, xmlNode* rootNode)
{
	/* NOTE (mandrav#1#): Do *not* remove 'false' from the call because in ANSI builds,
	it matches this very function and overflows the stack... */
	Write(path, RheiaC2U(str), rootNode, false);
};

wxString RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, const wxString& defaultVal)
{
	wxString ret;

	if (Read(path, &ret, rootNode))
		return ret;
	else
		return defaultVal;
}

bool RheiaXmlManager::Read(const wxString& path, wxString* str, xmlNode* rootNode )
{
	wxString key(path);

	if ( rootNode == NULL )
		RheiaThrow( wxT("Error, you are trying to read from an undefined rootNode !") );

	xmlNode* e = AssertPath( key, rootNode );
	xmlNode *n = GetUniqElement(e, key);

	xmlChar* content = xmlNodeGetContent( n );
	str->assign( RheiaC2U( (const char*) content ) );
	xmlFree( content );

	return !str->IsEmpty();
}

void RheiaXmlManager::Write(const wxString& path, xmlNode *rootNode , const wxColour& c)
{
	/*
	This fonction writes a color node in the given rootNode,
	*/
	wxString key(path);

	wxString Red;
	Red.Printf( wxT("%d") , c.Red() );
	wxString Green;
	Green.Printf( wxT("%d") , c.Green() );
	wxString Blue;
	Blue.Printf( wxT("%d") , c.Blue() );
	/* Check if the path node exists in the root node otherwise create it */
	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrRed = xmlHasProp( e , rxU2C(XmlManagerPaths::ColourAttributes::Red) );
	if ( attrRed == NULL ) {
		attrRed = xmlNewProp( e , rxU2C(XmlManagerPaths::ColourAttributes::Red) , NULL);
	}
	xmlSetProp( e ,  rxU2C(XmlManagerPaths::ColourAttributes::Red) ,
	            rxU2C(Red) );

	xmlAttr* attrGreen = xmlHasProp( e , rxU2C(XmlManagerPaths::ColourAttributes::Green) );
	if ( attrGreen == NULL ) {
		attrGreen = xmlNewProp( e , rxU2C(XmlManagerPaths::ColourAttributes::Green) , NULL );
	}
	xmlSetProp( e ,  rxU2C(XmlManagerPaths::ColourAttributes::Green) ,
	            rxU2C(Green) );

	xmlAttr* attrBlue = xmlHasProp( e , rxU2C(XmlManagerPaths::ColourAttributes::Blue) );
	if ( attrBlue == NULL ) {
		attrBlue = xmlNewProp( e , rxU2C(XmlManagerPaths::ColourAttributes::Blue) , NULL);
	}
	xmlSetProp( e ,  rxU2C(XmlManagerPaths::ColourAttributes::Blue) ,
	            rxU2C(Blue) );
}

wxColour RheiaXmlManager::ReadColour(const wxString& path, xmlNode *rootNode , const wxColour& defaultVal)
{
	wxColour ret;

	if (Read(path, rootNode, &ret))
		return ret;
	else
		return defaultVal;
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode *rootNode , wxColour* ret)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr *attrRed=NULL;
	xmlAttr *attrGreen=NULL;
	xmlAttr *attrBlue=NULL;
	/* Hence we have get the node, we can check if the children's node has properties */
	if ( (attrRed = xmlHasProp(e , rxU2C(XmlManagerPaths::ColourAttributes::Red) ) ) !=NULL &&
	        (attrGreen = xmlHasProp(e , rxU2C(XmlManagerPaths::ColourAttributes::Green) )) !=NULL &&
	        (attrBlue = xmlHasProp(e , rxU2C(XmlManagerPaths::ColourAttributes::Blue) )) != NULL ) {
		double redA;
		double greenA;
		double blueA;

		wxString RedA = RheiaNodeGetContent( attrRed->children );
		wxString GreenA = RheiaNodeGetContent( attrGreen->children );
		wxString BlueA = RheiaNodeGetContent( attrBlue->children );

		RedA.ToDouble( &redA );
		GreenA.ToDouble( &greenA );
		BlueA.ToDouble( &blueA );

		ret->Set( (int) redA , (int) greenA , (int) blueA);

		return true;
	}
	return false;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  int value)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrNode = xmlHasProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::IntAttribute) );
	if ( attrNode == NULL ) {
		attrNode = xmlNewProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::IntAttribute) , NULL);
	}
	wxString val;
	val.Printf( wxT("%d") , value );

	xmlSetProp( e ,  rxU2C(XmlManagerPaths::DefaultAttributes::IntAttribute) ,
	            rxU2C(val) );
}

int  RheiaXmlManager::ReadInt(const wxString& path, xmlNode* rootNode,  int defaultVal)
{
	int ret;

	if (Read(path, rootNode, &ret))
		return ret;
	else
		return defaultVal;
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode ,  int* value)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrNode = xmlHasProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::IntAttribute) );
	if ( attrNode != NULL ) {
		double valD;
		wxString ValD = RheiaNodeGetContent( attrNode->children );
		ValD.ToDouble( &valD );

		*value = (int) valD;

		return true;
	}
	return false;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  bool value)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrNode = xmlHasProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::BoolAttribute) );
	if ( attrNode == NULL ) {
		attrNode = xmlNewProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::BoolAttribute) , NULL);
	}
	wxString val;
	val = (value ? wxT("true") : wxT("false") );

	xmlSetProp( e ,  rxU2C(XmlManagerPaths::DefaultAttributes::BoolAttribute) ,
	            rxU2C(val) );
}

bool  RheiaXmlManager::ReadBool(const wxString& path, xmlNode* rootNode,  bool defaultVal)
{
	bool ret;

	if (Read(path, rootNode, &ret))
		return ret;
	else
		return defaultVal;
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, bool* value)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrNode = xmlHasProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::BoolAttribute) );
	if ( attrNode != NULL ) {
		wxString ValD = RheiaNodeGetContent( attrNode->children );
		*value = ( ValD.IsSameAs( wxT("true") ) ? true : false );

		return true;
	}
	return false;
}

void RheiaXmlManager::Write(const wxString& path,   xmlNode* rootNode, double value)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrNode = xmlHasProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::DoubleAttribute) );
	if ( attrNode == NULL ) {
		attrNode = xmlNewProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::DoubleAttribute) , NULL);
	}
	wxString val;
	val << value ;

	xmlSetProp( e ,  rxU2C(XmlManagerPaths::DefaultAttributes::DoubleAttribute) ,
	            rxU2C(val) );
}

double  RheiaXmlManager::ReadDouble(const wxString& path,  xmlNode* rootNode,  double defaultVal)
{
	double ret;

	if (Read(path, rootNode , &ret))
		return ret;
	else
		return defaultVal;
}

bool RheiaXmlManager::Read(const wxString& path,  xmlNode* rootNode, double* value)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlAttr* attrNode = xmlHasProp( e , rxU2C(XmlManagerPaths::DefaultAttributes::DoubleAttribute) );
	if ( attrNode != NULL ) {
		wxString ValD = RheiaNodeGetContent( attrNode->children );
		ValD.ToDouble( value );

		return true;
	}
	return false;
}

void RheiaXmlManager::Set(const wxString& path, xmlNode* rootNode)
{
	wxString key(path);
	xmlNode* e = AssertPath(key, rootNode);
	GetUniqElement(e, key);
}

void RheiaXmlManager::UnSet(const wxString& path, xmlNode* rootNode)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	xmlReplaceNode( e , NULL );
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const wxArrayString& arrayString)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::ArrayString)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayString.GetCount(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( arrayString[i] ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxArrayString *arrayString)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr = RheiaNodeGetContent( Attribute->children );
				arrayString->Add( ValueAttr );
			}
			curr = curr->next;
		}
	}
}

wxArrayString RheiaXmlManager::ReadArrayString(const wxString& path, xmlNode* rootNode)
{
	wxArrayString as;
	Read(path, rootNode, &as);
	return as;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const wxArrayInt& arrayInt)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::ArrayInt)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayInt.GetCount(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		wxString temp;
		temp.Printf(wxT("%d"),arrayInt[i]);
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( temp ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxArrayInt *arrayInt)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr = RheiaNodeGetContent( Attribute->children );
				double val;
				ValueAttr.ToDouble( &val );
				arrayInt->Add( int(val) );
			}
			curr = curr->next;
		}
	}
}

wxArrayInt RheiaXmlManager::ReadArrayInt(const wxString& path, xmlNode* rootNode)
{
	wxArrayInt ai;
	Read(path, rootNode, &ai);
	return ai;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const wxArrayDouble& arrayDouble)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::ArrayDouble)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayDouble.GetCount(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		wxString temp;
		temp.Printf(wxT("%f"),arrayDouble[i]);
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( temp ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxArrayDouble *arrayDouble)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr = RheiaNodeGetContent( Attribute->children );
				double val;
				ValueAttr.ToDouble( &val );
				arrayDouble->Add( val );
			}
			curr = curr->next;
		}
	}
}

wxArrayDouble RheiaXmlManager::ReadArrayDouble(const wxString& path, xmlNode* rootNode)
{
	wxArrayDouble ad;
	Read(path, rootNode, &ad);
	return ad;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const wxArrayBool& arrayBool)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::ArrayBool)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayBool.GetCount(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		wxString temp = ( arrayBool[i] ? wxT("true") : wxT("false") );
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( temp ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxArrayBool *arrayBool)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr = RheiaNodeGetContent( Attribute->children );
				bool val = ( ValueAttr.IsSameAs( wxT("true") ) ? true : false );
				arrayBool->Add( val );
			}
			curr = curr->next;
		}
	}
}

wxArrayBool RheiaXmlManager::ReadArrayBool(const wxString& path, xmlNode* rootNode)
{
	wxArrayBool ab;
	Read(path, rootNode, &ab);
	return ab;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const std::vector<bool>& arrayBool)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::StdVectorBool)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayBool.size(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		wxString temp = ( arrayBool[i] ? wxT("true") : wxT("false") );
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( temp ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, std::vector<bool> *arrayBool)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr = RheiaNodeGetContent( Attribute->children );
				bool val = ( ValueAttr.IsSameAs( wxT("true") ) ? true : false );
				arrayBool->push_back( val );
			}
			curr = curr->next;
		}
	}
}

std::vector<bool> RheiaXmlManager::ReadStdArrayBool(const wxString& path, xmlNode* rootNode)
{
	std::vector<bool> ab;
	Read(path, rootNode, &ab);
	return ab;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const std::vector<double>& arrayDouble)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::StdVectorDouble)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayDouble.size(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		wxString temp;
		temp.Printf(wxT("%f"),arrayDouble[i]);
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( temp ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, std::vector<double> *arrayDouble)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr = RheiaNodeGetContent( Attribute->children );
				double val;
				ValueAttr.ToDouble( &val );
				arrayDouble->push_back( val );
			}
			curr = curr->next;
		}
	}
}

std::vector<double> RheiaXmlManager::ReadStdArrayDouble(const wxString& path, xmlNode* rootNode)
{
	std::vector<double> ad;
	Read(path, rootNode, &ad);
	return ad;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const std::vector<int>& arrayInt)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::StdVectorInt)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayInt.size(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		wxString temp;
		temp.Printf(wxT("%d"),arrayInt[i]);
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            rxU2C( temp ) );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, std::vector<int> *arrayInt)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				wxString ValueAttr =RheiaNodeGetContent( Attribute->children );
				double val;
				ValueAttr.ToDouble( &val );
				arrayInt->push_back( int(val) );
			}
			curr = curr->next;
		}
	}
}

std::vector<int> RheiaXmlManager::ReadStdArrayInt(const wxString& path, xmlNode* rootNode)
{
	std::vector<int> ai;
	Read(path, rootNode, &ai);
	return ai;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode,  const std::vector<std::string>& arrayString)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );
	xmlReplaceNode( e , NULL );
	e = GetUniqElement(node,key);

	xmlNewProp( e , rxU2C( XmlManagerPaths::ArrayAttributes::ArrayType),
	            rxU2C( XmlManagerPaths::ArrayAttributes::ArrayTypes::StdVectorString)) ;

	//TiXmlElement *leaf = GetUniqElement(e, key)

	for (unsigned int i = 0; i < arrayString.size(); ++i) {
		xmlNode *Child = xmlNewNode( NULL, rxU2C( XmlManagerPaths::ArrayElementNode ) );
		xmlNewProp( Child, rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ),
		            (const xmlChar*) arrayString[i].c_str() );

		xmlAddChild( e , Child );
	}
}

void RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, std::vector<std::string> *arrayString)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement( node , key );

	/* First check if the type is correct */
	if (e) {
		xmlNode *curr = e->children;
		while ( (curr != NULL) ) {
			xmlAttr *Attribute = xmlHasProp( curr , rxU2C( XmlManagerPaths::ElementAttributes::ElementValue ) );
			if ( Attribute ) {
				std::string ValueAttr = rcU2C( RheiaNodeGetContent( Attribute->children ) ) ;
				arrayString->push_back( ValueAttr );
			}
			curr = curr->next;
		}
	}
}

std::vector<std::string> RheiaXmlManager::ReadStdArrayString(const wxString& path, xmlNode* rootNode)
{
	std::vector<std::string> as;
	Read(path, rootNode, &as);
	return as;
}

wxArrayString RheiaXmlManager::EnumerateSubPaths(const wxString& path, xmlNode *rootNode)
{
	wxString key(path + _T("/dummy"));
	xmlNode* e = AssertPath(key,rootNode);
	wxArrayString ret;

	if (e) {
		xmlNode *curr = e->children;
		while ( curr != NULL ) {
			wxChar c = *(RheiaNodeGetContent( curr ).c_str());
			if (c < _T('A') || c > _T('Z')) // first char must be a letter, uppercase letters are key names
				ret.Add(RheiaNodeGetContent( curr ));

			curr = curr->next;
		}
	}
	return ret;
}

void RheiaXmlManager::DeleteSubPath(const wxString& thePath, xmlNode* rootNode)
{
	wxString path(thePath);
	to_lower(path);

	Collapse(path);

	wxString illegal(_T(" :.,;!\"\'$%&()[]<>{}?*+-|#"));
	size_t i;
	while ((i = path.find_first_of(illegal)) != wxString::npos)
		path[i] = _T('_');

	if (path.Last() == _T('/'))
		path.RemoveLast();

	if (path.IsSameAs(_T("/"))) // this function will refuse to remove root!
		return;

	xmlNode* parent = AssertPath( path , rootNode );
	xmlReplaceNode( parent , NULL );
}

wxArrayString RheiaXmlManager::EnumerateKeys(const wxString& path, xmlNode* rootNode )
{
	wxString key(path + _T("/dummy")); // the trailing slash hack is required because AssertPath expects a key path
	xmlNode* e = AssertPath(key,rootNode);
	wxArrayString ret;

	if (e) {
		xmlNode *curr = e->children;
		while ( curr != NULL ) {
			wxChar c = *(RheiaNodeGetContent( curr ).c_str());
			if (c >=_T('A') && c <= _T('Z')) // first char must be a letter, uppercase letters are key names
				ret.Add(RheiaNodeGetContent( curr ));

			curr = curr->next;
		}
	}
	return ret;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode, const wxSize& size)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	wxString Width;
	Width.Printf( wxT("%d") , size.GetWidth() );
	wxString Height;
	Height.Printf( wxT("%d") , size.GetHeight() );

	xmlAttr *widthProp = xmlHasProp( e , rxU2C( XmlManagerPaths::SizeAttributes::WidthAttribute ) );
	if ( widthProp != NULL )
		xmlSetProp( e , rxU2C( XmlManagerPaths::SizeAttributes::WidthAttribute ) , rxU2C( Width ) );
	else
		xmlNewProp( e  , rxU2C( XmlManagerPaths::SizeAttributes::WidthAttribute ) , rxU2C( Width ) );

	xmlAttr *heightProp = xmlHasProp( e , rxU2C( XmlManagerPaths::SizeAttributes::HeightAttribute ) );
	if ( heightProp != NULL )
		xmlSetProp( e , rxU2C( XmlManagerPaths::SizeAttributes::HeightAttribute ) , rxU2C( Height ) );
	else
		xmlNewProp( e  , rxU2C( XmlManagerPaths::SizeAttributes::HeightAttribute ) , rxU2C( Height ) );
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode, const wxFont& font)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	Write( wxT("/def_encoding") , e , (int) font.GetDefaultEncoding() );
	Write( wxT("/face_name") , font.GetFaceName() , e  );
	Write( wxT("/family") , e , (int) font.GetFamily() );
	Write( wxT("/point_size") , e , (int) font.GetPointSize() );
	Write( wxT("/style") , e , (int) font.GetStyle() );
	Write( wxT("/underlined") , e , (int) font.GetUnderlined() );
	Write( wxT("/weight") , e , (int) font.GetWeight() );
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxFont *font)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	font->SetDefaultEncoding( (wxFontEncoding) ReadInt( wxT("/def_encoding") , e , (int) font->GetDefaultEncoding() ) );
	font->SetFaceName(  Read( wxT("/face_name") , e , font->GetFaceName() ) );
	font->SetFamily( (wxFontFamily) ReadInt( wxT("/family") , e , (int) font->GetFamily() ) );
	font->SetPointSize( ReadInt( wxT("/point_size") , e , (int) font->GetPointSize() ) );
	font->SetStyle( ReadInt( wxT("/style") , e , (int) font->GetStyle() ) );
	font->SetUnderlined( (bool) ReadInt( wxT("/underlined") , e , (int) font->GetUnderlined() ) );
	font->SetWeight( (wxFontWeight) ReadInt( wxT("/weight") , e , (int) font->GetWeight() ) );

	return false;
}

wxFont RheiaXmlManager::ReadFont(const wxString& path, xmlNode* rootNode )
{
	wxFont ret(10, wxFONTFAMILY_SWISS , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	if ( Read( path, rootNode , &ret ) )
		return ret;

	return ret;
}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode, const wxTextAttr& attr)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	Write( wxT("/alignment") , e , (int) attr.GetAlignment() );
	Write( wxT("/background_color") , e , attr.GetBackgroundColour() );
	Write( wxT("/font") , e , attr.GetFont() );
	Write( wxT("/left_indent") , e , (int) attr.GetLeftIndent() );
	Write( wxT("/left_subindent") , e , (int) attr.GetLeftSubIndent() );
	Write( wxT("/right_indent") , e , (int) attr.GetRightIndent() );
	Write( wxT("/tabs") , e , attr.GetTabs() );
	Write( wxT("/text_colour") , e , attr.GetTextColour() );
}

wxTextAttr RheiaXmlManager::ReadTextAttr(const wxString& path, xmlNode* rootNode )
{
	wxTextAttr ret;

	if ( Read( path, rootNode , &ret ) )
		return ret;

	return ret;
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxTextAttr *attr)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	attr->SetAlignment( (wxTextAttrAlignment) ReadInt( wxT("/alignment") , e , (int) attr->GetAlignment() ) );
	attr->SetBackgroundColour( ReadColour( wxT("/background_color") , e , attr->GetBackgroundColour() ) );
	attr->SetFont( ReadFont( wxT("/font") , e ) );
	attr->SetLeftIndent( ReadInt( wxT("/left_indent") , e , (int) attr->GetLeftIndent() ) );
	//attr->SetLeftSubIndent( ReadInt( wxT("/left_subindent") , e , (int) attr->GetLeftSubIndent() ) );
	attr->SetRightIndent( ReadInt( wxT("/right_indent") , e , (int) attr->GetRightIndent() ) );
	attr->SetTabs(ReadArrayInt( wxT("/tabs") , e ) );
	attr->SetTextColour( ReadColour( wxT("/text_colour") , e , attr->GetTextColour() ) );

	return true;
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxSize *size)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	wxString Width;
	wxString Height;
	double dWidth;
	double dHeight;
	int iWidth;
	int iHeight;

	xmlAttr *widthProp = xmlHasProp( e , rxU2C( XmlManagerPaths::SizeAttributes::WidthAttribute ) );
	if ( widthProp == NULL )
		return false;

	Width = RheiaNodeGetContent( widthProp->children );
	Width.ToDouble( &dWidth );
	iWidth = int( dWidth );

	xmlAttr *heightProp = xmlHasProp( e , rxU2C( XmlManagerPaths::SizeAttributes::HeightAttribute ) );
	if ( heightProp == NULL )
		return false;

	Height = RheiaNodeGetContent( heightProp->children );
	Height.ToDouble( &dHeight );
	iHeight = int( dHeight );

	size->SetWidth( iWidth );
	size->SetHeight( iHeight );

	return true;
}

wxSize RheiaXmlManager::ReadSize(const wxString& path, xmlNode* rootNode,const wxSize& defaultSize)
{
	wxSize ret;

	if ( Read( path, rootNode , &ret ) )
		return ret;

	else
		return defaultSize;


}

void RheiaXmlManager::Write(const wxString& path, xmlNode* rootNode, const wxPoint& pos)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	wxString X;
	X.Printf( wxT("%d") , pos.x );
	wxString Y;
	Y.Printf( wxT("%d") , pos.y );

	xmlAttr *xProp = xmlHasProp( e , rxU2C( XmlManagerPaths::PositionAttributes::XAttribute ) );
	if ( xProp != NULL )
		xmlSetProp( e , rxU2C( XmlManagerPaths::PositionAttributes::XAttribute ) , rxU2C( X ) );
	else
		xmlNewProp( e  , rxU2C( XmlManagerPaths::PositionAttributes::XAttribute ) , rxU2C( X ) );

	xmlAttr *yProp = xmlHasProp( e , rxU2C( XmlManagerPaths::PositionAttributes::YAttribute ) );
	if ( yProp != NULL )
		xmlSetProp( e , rxU2C( XmlManagerPaths::PositionAttributes::YAttribute ) , rxU2C( Y ) );
	else
		xmlNewProp( e  , rxU2C( XmlManagerPaths::PositionAttributes::YAttribute ) , rxU2C( Y ) );
}

bool RheiaXmlManager::Read(const wxString& path, xmlNode* rootNode, wxPoint* pos)
{
	wxString key(path);

	xmlNode* node = AssertPath(key,rootNode);
	xmlNode* e = GetUniqElement(node,key);

	wxString X;
	wxString Y;
	double dX;
	double dY;
	int iX;
	int iY;

	xmlAttr *xProp = xmlHasProp( e , rxU2C( XmlManagerPaths::PositionAttributes::XAttribute ) );
	if ( xProp == NULL )
		return false;

	X = RheiaNodeGetContent( xProp->children );
	X.ToDouble( &dX );
	iX = int( dX );

	xmlAttr *yProp = xmlHasProp( e , rxU2C( XmlManagerPaths::PositionAttributes::YAttribute ) );
	if ( yProp == NULL )
		return false;

	Y = RheiaNodeGetContent( yProp->children );
	Y.ToDouble( &dY );
	iY = int( dY );

	pos->x = iX ;
	pos->y = iY ;

	return true;
}

wxPoint RheiaXmlManager::ReadPosition(const wxString& path, xmlNode* rootNode,const wxPoint& defaultPos)
{
	wxPoint ret;

	if ( Read( path, rootNode , &ret ) )
		return ret;

	else
		return defaultPos;


}
