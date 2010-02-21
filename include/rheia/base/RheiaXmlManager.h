#ifndef RheiaXmlManager_h_
#define RheiaXmlManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>

#include <set>

/* ------------------------------------------------------------------------------------------------------------------
*  Interface Serializable
*  ConfigManager can save arbitrary objects and even sets/maps of objects, provided they implement Serializable.
*
*  Usage:
*  ------
*   class MySerializableLongIntClass : public ISerializable
*   {
*   //...
*   wxString SerializeOut() const {wxString tmp; tmp << m_int; return tmp;};
*   void SerializeIn(const wxString& s){s.ToLong(&m_int);};
*   //...
*   long int m_int;
*   };
*/
class ISerializable
{
public:
    ISerializable();
    virtual ~ISerializable();
    virtual wxString SerializeOut() const = 0;
    virtual void SerializeIn(const wxString& s) = 0;
};


/* ------------------------------------------------------------------------------------------------------------------
*  Containers supported by ConfigManager
*/
namespace XmlManagerContainer
{
    typedef std::map<wxString, wxString> StringToStringMap;
    typedef std::map<int, wxString> IntToStringMap;
    typedef std::set<wxString> StringSet;;

    typedef std::map<wxString, ISerializable*> SerializableObjectMap;
};

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;
typedef unsigned char xmlChar;

class RheiaConfigurationManager;
class RheiaSaver;
class RheiaProjectManager;

/* define the wxArrayBool containing bool values */
WX_DEFINE_ARRAY_INT(bool,wxArrayBool);

/*************************************************************************************************************//**
*	@class RheiaXmlManager
*
*	@brief RheiaXmlManager is a module for managing node writing and reading in different xml documents
*	nodes and paths.
*
*	RheiaXmlManager is the manager class that simplifies the use of xml files for saving information in Rheia
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	11-Jan-2009
*	@version 0.0.1
*****************************************************************************************************************/
class BASE_DLLEXPORT RheiaXmlManager : public Mgr<RheiaXmlManager> , public wxEvtHandler
{
	/*! Give Mgr access to our private members */
	friend class Mgr<RheiaXmlManager>;
	/*! Give RheiaManager Access to our private members */
	friend class RheiaManager;
	friend class RheiaConfigurationManager;
	friend class RheiaProjectManager;
	friend class RheiaSaver;

public :

    static wxString RheiaNodeGetContent( xmlNode* node );
    static wxString RheiaNodeGetProp( xmlChar* prop );

	 /* -----------------------------------------------------------------------------------------------------
    *  Path functions for navigation within your configuration namespace
    */
    /** Enumerates the first level subpath (child node names that are paths)
    *  @param path path to enumerate from rootNode
    *	 @param rootNode root node from which to start the path node find
    */
    wxArrayString EnumerateSubPaths(const wxString& path, xmlNode* rootNode);

    /** Enumerates the first level keys (child node names that are keys)
    *  @param path path to enumerate from rootNode
    *	 @param rootNode root node from which to start the path node find
    *
    * @note keys are different from paths, keys are unique.
    */
    wxArrayString EnumerateKeys(const wxString& path, xmlNode* rootNode);

    /** Delete the node given by the path starting from root node
    *  @param strPath subpath to delete from rootNode
    *	 @param rootNode root node from which to start the path node find
    */
    void DeleteSubPath(const wxString& strPath, xmlNode *rootNode);

     /* -----------------------------------------------------------------------------------------------------
	 *  Clear and delete nodes and xml documents
    */
    void Clear( xmlNode* node );
    void Delete( xmlDoc* doc );

	 /* -----------------------------------------------------------------------------------------------------
    *  Standard primitives for reading and writing standard calues in XmlNodes
    */
    void Write(const wxString& name,  const wxString& value, xmlNode* pathNode, bool ignoreEmpty = false);
    wxString Read(const wxString& key, xmlNode* rootNode, const wxString& defaultVal = wxEmptyString);
    bool Read(const wxString& key, wxString* str, xmlNode* rootNode);
    void Write(const wxString& key, const char* str, xmlNode* pathNode);

    void Write(const wxString& name, xmlNode* rootNode,  int value);
    bool Read(const wxString& name, xmlNode* rootNode,  int* value);
    int  ReadInt(const wxString& name, xmlNode* rootNode,  int defaultVal = 0);

    void Write(const wxString& name,xmlNode* rootNode,  bool value);
    bool Read(const wxString& name,xmlNode* rootNode,  bool* value);
    bool ReadBool(const wxString& name,xmlNode* rootNode,  bool defaultVal = false);

    void Write(const wxString& name, xmlNode* rootNode, double value);
    bool Read(const wxString& name, xmlNode* rootNode,  double* value);
    double ReadDouble(const wxString& name, xmlNode* rootNode, double defaultVal = 0.0f);

    /* -----------------------------------------------------------------------------------------------------
    *  Set and unset keys, or test for existence. Note that these functions cannot be used to remove paths
    *  or test existence of paths (it may be used to implicitely create paths, though).
    */
    //bool Exists(const wxString& name);
    void Set(const wxString& name, xmlNode *rootNode );
    void UnSet(const wxString& name, xmlNode* rootNode);

     /* -----------------------------------------------------------------------------------------------------
    *  Compound objects
    */
    void Write(const wxString& name,  xmlNode* rootNode, const wxArrayString& as);
    void Read(const wxString& name, xmlNode* rootNode, wxArrayString* as);
    wxArrayString ReadArrayString(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name,  xmlNode* rootNode, const wxArrayInt& arrayInt);
    void Read(const wxString& name, xmlNode* rootNode, wxArrayInt* arrayInt);
    wxArrayInt ReadArrayInt(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name,  xmlNode* rootNode, const wxArrayDouble& arrayDouble);
    void Read(const wxString& name, xmlNode* rootNode, wxArrayDouble* arrayDouble);
    wxArrayDouble ReadArrayDouble(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name,  xmlNode* rootNode, const wxArrayBool& arrayBool);
    void Read(const wxString& name, xmlNode* rootNode, wxArrayBool* arrayBool);
    wxArrayBool ReadArrayBool(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name,  xmlNode* rootNode, const std::vector<std::string>& arrayString);
    void Read(const wxString& name, xmlNode* rootNode, std::vector<std::string>* arrayString);
    std::vector<std::string> ReadStdArrayString(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name,  xmlNode* rootNode, const std::vector<int>& arrayInt);
    void Read(const wxString& name, xmlNode* rootNode, std::vector<int>* arrayInt);
    std::vector<int> ReadStdArrayInt(const wxString& name,xmlNode* rootNode);

	 void Write(const wxString& name,  xmlNode* rootNode, const std::vector<double>& arrayDouble);
    void Read(const wxString& name, xmlNode* rootNode, std::vector<double>* arrayDouble);
    std::vector<double> ReadStdArrayDouble(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name,  xmlNode* rootNode, const std::vector<bool>& arrayBool);
    void Read(const wxString& name, xmlNode* rootNode, std::vector<bool>* arrayBool);
    std::vector<bool> ReadStdArrayBool(const wxString& name,xmlNode* rootNode);

    void Write(const wxString& name, xmlNode *rootNode,  const wxColour& c);
    bool Read(const wxString& name, xmlNode *rootNode, wxColour* value);
    wxColour ReadColour(const wxString& name, xmlNode *rootNode, const wxColour& defaultVal = *wxBLACK);

//	 /* -----------------------------------------------------------------------------------------------------
//    *  Single serializable objects
//    */
//    void Write(const wxString& name, const ISerializable& object){};
//    bool Read(const wxString& name, ISerializable* object){return true;};
//
//    /* -----------------------------------------------------------------------------------------------------
//    *  Maps and sets of primitive types
//    */
//    void Write(const wxString& name, const XmlManagerContainer::StringToStringMap& map);
//    void Read(const wxString& name, XmlManagerContainer::StringToStringMap* map);
//    XmlManagerContainer::StringToStringMap ReadSSMap(const wxString& name);
//
//    void Write(const wxString& name, const XmlManagerContainer::IntToStringMap& map);
//    void Read(const wxString& name, XmlManagerContainer::IntToStringMap* map);
//    XmlManagerContainer::IntToStringMap ReadISMap(const wxString& name);
//
//    void Write(const wxString& name, const XmlManagerContainer::StringSet& set);
//    void Read(const wxString& name, XmlManagerContainer::StringSet* map);
//    XmlManagerContainer::StringSet ReadSSet(const wxString& name);

   /* ------------------------------------------------------------------------------------------------------
   *	functions for dynamic libraries Read and Write
   */
//	void Write( const wxString name, xmlNode* rootNode , const RheiaDynamicLibrary& dynamicLibrary, bool overwrite_existing = true );
//	void Write( const wxString name, xmlNode* rootNode , const RheiaDynamicLibraryTable& dynamicLibraries, bool overwrite_existing = true );
//
//	void Read( const wxString name, xmlNode* rootNode, const wxString& LibName, RheiaDynamicLibrary* dynamicLibrary );
//	void Read( const wxString name, xmlNode* rootNode , RheiaDynamicLibraryTable* dynamicLibraries );
//
//	RheiaDynamicLibrary ReadDynamicLibrary( const wxString& name, xmlNode* rootNode, const wxString LibName );
//	RheiaDynamicLibraryTable ReadDynamicLibraryTable( const wxString& name, xmlNode* rootNode );



	/*--------------------------------------------------------------------------------------------------------------
	* Functions for size and positions
	*/
	void Write(const wxString& name, xmlNode* rootNode, const wxSize& size);
    bool Read(const wxString& name, xmlNode* rootNode, wxSize *size);
    wxSize ReadSize(const wxString& name, xmlNode* rootNode, const wxSize& defaultSize = wxDefaultSize );

    void Write(const wxString& name, xmlNode* rootNode, const wxPoint& pos);
    bool Read(const wxString& name, xmlNode* rootNode, wxPoint *pos);
    wxPoint ReadPosition(const wxString& name, xmlNode* rootNode, const wxPoint& defaultPos = wxDefaultPosition );

    /** functions for fonts */
	void Write(const wxString& name, xmlNode* rootNode, const wxFont& font);
    bool Read(const wxString& name, xmlNode* rootNode, wxFont *font);
    wxFont ReadFont(const wxString& name, xmlNode* rootNode );

    /** functions for wxTextAttr */
	void Write(const wxString& name, xmlNode* rootNode, const wxTextAttr& attr);
    bool Read(const wxString& name, xmlNode* rootNode, wxTextAttr *attr);
    wxTextAttr ReadTextAttr(const wxString& name, xmlNode* rootNode );

    /* -----------------------------------------------------------------------------------------------------
    *  Maps of serialized objects. You are responsible for deleting the objects in the map/set.
    *
    *
    *  Usage:
    *  ------
    *  typedef std::map<wxString, MySerializableClass *> MyMap;
    *  MyMap objMap;
    *  cfg->Read("name", &objMap);
    *  map["somekey"]->DoSomething();
    */
//    void Write(const wxString& name, const XmlManagerContainer::SerializableObjectMap* map);
//
//    template <typename T> void Read(const wxString& name, std::map<wxString, T*> *map)
//    {
////        wxString key(name);
////        TiXmlHandle ph(AssertPath(key));
////        TiXmlElement* e = 0;
////        if(TiXmlNode *n = ph.FirstChild(key.mb_str(wxConvUTF8)).FirstChild("objmap").Node())
////            while(n->IterateChildren(e) && (e = n->IterateChildren(e)->ToElement()))
////            {
////                T *obj = new T;
////                obj->SerializeIn(wxBase64::Decode(cbC2U(e->FirstChild()->ToText()->Value())));
////                (*map)[cbC2U(e->Value())] = obj;
////            }
//    };
private :

	 xmlNode* AssertPath( wxString& path,
																xmlNode* pathNode );

    xmlNode* GetUniqElement(xmlNode* p, const wxString& q);
    void SetNodeText(xmlNode *n, const char* t);
    inline void Collapse(wxString& str) const;
    wxString InvalidNameMessage(const wxString& what, const wxString& sub, xmlNode *localPath) const;
};

#endif
