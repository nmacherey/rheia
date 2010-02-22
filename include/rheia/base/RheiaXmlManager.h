#ifndef RheiaXmlManager_h_
#define RheiaXmlManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>

#include <set>

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

/**
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
*/
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
	
	/** Helper methods to hel conversion */
    static wxString RheiaNodeGetContent( xmlNode* node );
	
	/** Helper methods to hel conversion */
    static wxString RheiaNodeGetProp( xmlChar* prop );

    /** Enumerates the first level subpath (child node names that are paths)
    *  	@param path path to enumerate from rootNode
    *	@param rootNode root node from which to start the path node find
    */
    wxArrayString EnumerateSubPaths(const wxString& path, xmlNode* rootNode);

    /** Enumerates the first level keys (child node names that are keys)
    *  	@param path path to enumerate from rootNode
    *	@param rootNode root node from which to start the path node find
    *
    * 	@note keys are different from paths, keys are unique.
    */
    wxArrayString EnumerateKeys(const wxString& path, xmlNode* rootNode);

    /** Delete the node given by the path starting from root node
    *  	@param strPath subpath to delete from rootNode
    *	@param rootNode root node from which to start the path node find
    */
    void DeleteSubPath(const wxString& strPath, xmlNode *rootNode);

	/*****************************************************************************************************
    *   CLEARING AND DELETING
    *****************************************************************************************************/
	/** Clear the given node and all it's childrens */
    void Clear( xmlNode* node );
	
	/** Delete the given document after a call to this, the instance will be invalid */
    void Delete( xmlDoc* doc );
	
    void Set(const wxString& path, xmlNode *rootNode );
    void UnSet(const wxString& path, xmlNode* rootNode);

	/*****************************************************************************************************
    *   FIRST LEVEL PRIMITIVES WRITING AND READING STANDARD VARIABLES
    *****************************************************************************************************/
	
	    /*************************************************************************************
        *   STRING METHODS FOR READING AND WRITING
        *************************************************************************************/
	
	/**
    *   Write a wxString in the namespace at the given path
    *   @param path path from namespace root node in which the string has to be stored
    *   @param value the string to write in the given path
	* 	@param rootNode root Node of the path
    *   @param ignoreEmpty specify if empty strings shall be ignored or not
    */
    void Write(const wxString& path,  const wxString& value, xmlNode* rootNode, bool ignoreEmpty = false);
	
	/**
    *   Read a wxString from the given path
    *   @param path path from which the string shall be read
	* 	@param rootNode root node of the path
    *   @param defaultVal default value for the string if the path does not exists
    *   @return the string in the given path if founded the default value else
    */
    wxString Read(const wxString& path, xmlNode* rootNode, const wxString& defaultVal = wxEmptyString);
	
	/**
    *   Read a wxString from the given path
    *   @param path path from which the string shall be read
    *   @param str pointer to an allocated string in which the result shall be stored
	* 	@param rootNode root node of the path
    *   @return true if the string has been found in the given path else return false
    */
    bool Read(const wxString& path, wxString* str, xmlNode* rootNode);
	
	/**
    *   Write a char* in the namespace at the given path
    *   @param path path from namespace root node in which the string has to be stored
    *   @param str the string to write in the given path
	* 	@param rootNode root node of the path
    */
    void Write(const wxString& path, const char* str, xmlNode* rootNode);
	
		/*************************************************************************************
        *   INT METHODS FOR READING AND WRITING
        *************************************************************************************/
	
	/**
    *   Write an INT in the namespace at the given path
    *   @param path path from namespace root node in which the INT has to be stored
	* 	@param rootNode root node of the path
    *   @param value the INT to write in the given path
    */
    void Write(const wxString& path, xmlNode* rootNode,  int value);
	
	/**
    *   Read an INT from the given path
    *   @param path path from which the INT shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated INT in which the result shall be stored
    *   @return true if the INT has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode* rootNode,  int* value);
	
	/**
    *   Read an INT from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @param defaultVal default value for the INT if the path does not exists
    *   @return the INT in the given path if founded the default value else
    */
    int  ReadInt(const wxString& path, xmlNode* rootNode,  int defaultVal = 0);

		/*************************************************************************************
        *   BOOL METHODS FOR READING AND WRITING
        *************************************************************************************/
		
	/**
    *   Write a BOOL in the namespace at the given path
    *   @param path path from namespace root node in which the INT has to be stored
	* 	@param rootNode root node of the path
    *   @param value the BOOL to write in the given path
    */	
    void Write(const wxString& path,xmlNode* rootNode,  bool value);
	
	/**
    *   Read a BOOL from the given path
    *   @param path path from which the INT shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated BOOL in which the result shall be stored
    *   @return true if the BOOL has been found in the given path else return false
    */
    bool Read(const wxString& path,xmlNode* rootNode,  bool* value);
	
	/**
    *   Read a BOOL from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @param defaultVal default value for the BOOL if the path does not exists
    *   @return the BOOL in the given path if founded the default value else
    */
    bool ReadBool(const wxString& path,xmlNode* rootNode,  bool defaultVal = false);
	
	    /*************************************************************************************
        *   DOUBLE METHODS FOR READING AND WRITING
        *************************************************************************************/
		
	/**
    *   Write a DOUBLE in the namespace at the given path
    *   @param path path from namespace root node in which the INT has to be stored
	* 	@param rootNode root node of the path
    *   @param value the DOUBLE to write in the given path
    */
    void Write(const wxString& path, xmlNode* rootNode, double value);
	
	/**
    *   Read a DOUBLE from the given path
    *   @param path path from which the INT shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated DOUBLE in which the result shall be stored
    *   @return true if the DOUBLE has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode* rootNode,  double* value);
	
	/**
    *   Read a DOUBLE from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @param defaultVal default value for the DOUBLE if the path does not exists
    *   @return the DOUBLE in the given path if founded the default value else
    */
    double ReadDouble(const wxString& path, xmlNode* rootNode, double defaultVal = 0.0f);

    /*****************************************************************************************************
    *   SECOND LEVEL PRIMITIVES WRITING AND READING STANDARD WXWIDGETS ARRAYS
    *****************************************************************************************************/
	
	    /*************************************************************************************
        *   ARRAY STRING METHODS FOR READING AND WRITING
        *************************************************************************************/
		
	/**
    *   Write a wxArrayString in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayString has to be stored
	* 	@param rootNode root node of the path
    *   @param as the wxArrayString to write in the given path
    */
    void Write(const wxString& path,  xmlNode* rootNode, const wxArrayString& as);
	
	/**
    *   Read a wxArrayString from the given path
    *   @param path path from which the INT shall be read
	* 	@param rootNode root node of the path
    *   @param as pointer to an allocated wxArrayString in which the result shall be stored
    *   @return true if the wxArrayString has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, wxArrayString* as);
	
	/**
    *   Read a wxArrayString from the given path
    *   @param path path from which the wxArrayString shall be read
	* 	@param rootNode root node of the path
    *   @return the wxArrayString in the given path if founded, an empty else
    */
    wxArrayString ReadArrayString(const wxString& path,xmlNode* rootNode);
	
		/*************************************************************************************
        *   ARRAY INT METHODS FOR READING AND WRITING
        *************************************************************************************/
		
	/**
    *   Write a wxArrayInt in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayInt has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayInt the wxArrayInt to write in the given path
    */	
    void Write(const wxString& path,  xmlNode* rootNode, const wxArrayInt& arrayInt);
	
	/**
    *   Read a wxArrayInt from the given path
    *   @param path path from which the wxArrayInt shall be read
	* 	@param rootNode root node of the path
    *   @param arrayInt pointer to an allocated wxArrayInt in which the result shall be stored
    *   @return true if the wxArrayInt has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, wxArrayInt* arrayInt);
	
	/**
    *   Read a wxArrayInt from the given path
    *   @param path path from which the wxArrayInt shall be read
	* 	@param rootNode root node of the path
    *   @return the wxArrayInt in the given path if founded, an empty else
    */
    wxArrayInt ReadArrayInt(const wxString& path,xmlNode* rootNode);
		
		/*************************************************************************************
        *   ARRAY DOUBLE METHODS FOR READING AND WRITING
        *************************************************************************************/

	/**
    *   Write a wxArrayDouble in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayDouble has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayDouble the wxArrayDouble to write in the given path
    */
    void Write(const wxString& path,  xmlNode* rootNode, const wxArrayDouble& arrayDouble);
	
	/**
    *   Read a wxArrayDouble from the given path
    *   @param path path from which the wxArrayDouble shall be read
	* 	@param rootNode root node of the path
    *   @param arrayDouble pointer to an allocated wxArrayDouble in which the result shall be stored
    *   @return true if the wxArrayDouble has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, wxArrayDouble* arrayDouble);
	
	/**
    *   Read a wxArrayDouble from the given path
    *   @param path path from which the wxArrayDouble shall be read
	* 	@param rootNode root node of the path
    *   @return the wxArrayDouble in the given path if founded, an empty else
    */
    wxArrayDouble ReadArrayDouble(const wxString& path,xmlNode* rootNode);
		
		/*************************************************************************************
        *   ARRAY BOOL METHODS FOR READING AND WRITING
        *************************************************************************************/
	
	/**
    *   Write a wxArrayBool in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayBool has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayBool the wxArrayBool to write in the given path
    */
    void Write(const wxString& path,  xmlNode* rootNode, const wxArrayBool& arrayBool);
	
	/**
    *   Read a wxArrayBool from the given path
    *   @param path path from which the wxArrayBool shall be read
	* 	@param rootNode root node of the path
    *   @param arrayBool pointer to an allocated wxArrayBool in which the result shall be stored
    *   @return true if the wxArrayBool has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, wxArrayBool* arrayBool);
	
	/**
    *   Read a wxArrayBool from the given path
    *   @param path path from which the wxArrayBool shall be read
	* 	@param rootNode root node of the path
    *   @return the wxArrayBool in the given path if founded, an empty else
    */
    wxArrayBool ReadArrayBool(const wxString& path,xmlNode* rootNode);
	
	/*****************************************************************************************************
    *   SECOND LEVEL PRIMITIVES WRITING AND READING STANDARD STL ARRAYS
    *****************************************************************************************************/

        /*************************************************************************************
        *   ARRAY STRING METHODS FOR READING AND WRITING
        *************************************************************************************/
	
	/**
    *   Write a std::vector<std::string> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<std::string> has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayString the std::vector<std::string> to write in the given path
    */
    void Write(const wxString& path,  xmlNode* rootNode, const std::vector<std::string>& arrayString);
	
	/**
    *   Read a std::vector<std::string> from the given path
    *   @param path path from which the std::vector<std::string> shall be read
	* 	@param rootNode root node of the path
    *   @param arrayString pointer to an allocated std::vector<std::string> in which the result shall be stored
    *   @return true if the std::vector<std::string> has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, std::vector<std::string>* arrayString);
	
	/**
    *   Read a std::vector<std::string> from the given path
    *   @param path path from which the std::vector<std::string> shall be read
	* 	@param rootNode root node of the path
    *   @return the std::vector<std::string> in the given path if founded, an empty else
    */
    std::vector<std::string> ReadStdArrayString(const wxString& path,xmlNode* rootNode);
	
		/*************************************************************************************
        *   ARRAY INT METHODS FOR READING AND WRITING
        *************************************************************************************/
	
	/**
    *   Write a std::vector<int> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<int> has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayInt the std::vector<int> to write in the given path
    */
    void Write(const wxString& path,  xmlNode* rootNode, const std::vector<int>& arrayInt);
	
	/**
    *   Read a std::vector<int> from the given path
    *   @param path path from which the std::vector<int> shall be read
	* 	@param rootNode root node of the path
    *   @param arrayInt pointer to an allocated std::vector<int> in which the result shall be stored
    *   @return true if the std::vector<int> has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, std::vector<int>* arrayInt);
	
	/**
    *   Read a std::vector<int> from the given path
    *   @param path path from which the std::vector<int> shall be read
	* 	@param rootNode root node of the path
    *   @return the std::vector<int> in the given path if founded, an empty else
    */
    std::vector<int> ReadStdArrayInt(const wxString& path,xmlNode* rootNode);
	
		/*************************************************************************************
        *   ARRAY DOUBLE METHODS FOR READING AND WRITING
        *************************************************************************************/
	
	/**
    *   Write a std::vector<double> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<double> has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayDouble the std::vector<double> to write in the given path
    */
	void Write(const wxString& path,  xmlNode* rootNode, const std::vector<double>& arrayDouble);
	
	/**
    *   Read a std::vector<double> from the given path
    *   @param path path from which the std::vector<double> shall be read
	* 	@param rootNode root node of the path
    *   @param arrayDouble pointer to an allocated std::vector<double> in which the result shall be stored
    *   @return true if the std::vector<double> has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, std::vector<double>* arrayDouble);
	
	/**
    *   Read a std::vector<double> from the given path
    *   @param path path from which the std::vector<double> shall be read
	* 	@param rootNode root node of the path
    *   @return the std::vector<double> in the given path if founded, an empty else
    */
    std::vector<double> ReadStdArrayDouble(const wxString& path,xmlNode* rootNode);
		
		/*************************************************************************************
        *   ARRAY BOOL METHODS FOR READING AND WRITING
        *************************************************************************************/
		
	/**
    *   Write a std::vector<bool> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<bool> has to be stored
	* 	@param rootNode root node of the path
    *   @param arrayBool the std::vector<bool> to write in the given path
    */	
    void Write(const wxString& path,  xmlNode* rootNode, const std::vector<bool>& arrayBool);
	
	/**
    *   Read a std::vector<bool> from the given path
    *   @param path path from which the std::vector<bool> shall be read
	* 	@param rootNode root node of the path
    *   @param arrayBool pointer to an allocated std::vector<bool> in which the result shall be stored
    *   @return true if the std::vector<bool> has been found in the given path else return false
    */
    void Read(const wxString& path, xmlNode* rootNode, std::vector<bool>* arrayBool);
	
	/**
    *   Read a std::vector<bool> from the given path
    *   @param path path from which the std::vector<bool> shall be read
	* 	@param rootNode root node of the path
    *   @return the std::vector<bool> in the given path if founded, an empty else
    */
    std::vector<bool> ReadStdArrayBool(const wxString& path,xmlNode* rootNode);
	
	/*****************************************************************************************************
    *   WXCOLOUR PRIMITIVES WRITING AND READING
    *****************************************************************************************************/
	
	/**
    *   Write a wxColour in the namespace at the given path
    *   @param path path from namespace root node in which the wxColour has to be stored
	* 	@param rootNode root node of the path
    *   @param c the wxColour to write in the given path
    */
    void Write(const wxString& path, xmlNode *rootNode,  const wxColour& c);
	
	/**
    *   Read a wxColour from the given path
    *   @param path path from which the wxColour shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated wxColour in which the result shall be stored
    *   @return true if the wxColour has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode *rootNode, wxColour* value);
	
	/**
    *   Read a wxColour from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @param defaultVal default value for the wxColour if the path does not exists
    *   @return the wxColour in the given path if founded the default value else
    */
    wxColour ReadColour(const wxString& path, xmlNode *rootNode, const wxColour& defaultVal = *wxBLACK);

	/**
    *   Write a wxSize in the namespace at the given path
    *   @param path path from namespace root node in which the wxSize has to be stored
	* 	@param rootNode root node of the path
    *   @param size the wxSize to write in the given path
    */
	void Write(const wxString& path, xmlNode* rootNode, const wxSize& size);
	
	/**
    *   Read a wxSize from the given path
    *   @param path path from which the wxFont shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated wxSize in which the result shall be stored
    *   @return true if the wxSize has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode* rootNode, wxSize *size);
	
	/**
    *   Read a wxSize from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @return the wxSize in the given path if founded the default value else
    */
    wxSize ReadSize(const wxString& path, xmlNode* rootNode, const wxSize& defaultSize = wxDefaultSize );
	
	/**
    *   Write a wxPoint in the namespace at the given path
    *   @param path path from namespace root node in which the wxPoint has to be stored
	* 	@param rootNode root node of the path
    *   @param pos the wxPoint to write in the given path
    */
    void Write(const wxString& path, xmlNode* rootNode, const wxPoint& pos);
	
	/**
    *   Read a wxPoint from the given path
    *   @param path path from which the wxFont shall be read
	* 	@param rootNode root node of the path
    *   @param pos pointer to an allocated wxPoint in which the result shall be stored
    *   @return true if the wxPoint has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode* rootNode, wxPoint *pos);
	
	/**
    *   Read a wxPoint from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @return the wxPoint in the given path if founded the default value else
    */
    wxPoint ReadPosition(const wxString& path, xmlNode* rootNode, const wxPoint& defaultPos = wxDefaultPosition );

    /**
    *   Write a wxFont in the namespace at the given path
    *   @param path path from namespace root node in which the wxFont has to be stored
	* 	@param rootNode root node of the path
    *   @param font the wxFont to write in the given path
    */
	void Write(const wxString& path, xmlNode* rootNode, const wxFont& font);
	
	/**
    *   Read a wxFont from the given path
    *   @param path path from which the wxFont shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated wxFont in which the result shall be stored
    *   @return true if the wxFont has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode* rootNode, wxFont *font);
	
	/**
    *   Read a wxFont from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @return the wxFont in the given path if founded the default value else
    */
    wxFont ReadFont(const wxString& path, xmlNode* rootNode );

    /**
    *   Write a wxTextAttr in the namespace at the given path
    *   @param path path from namespace root node in which the wxTextAttr has to be stored
	* 	@param rootNode root node of the path
    *   @param font the wxTextAttr to write in the given path
    */
	void Write(const wxString& path, xmlNode* rootNode, const wxTextAttr& attr);
	
	/**
    *   Read a wxTextAttr from the given path
    *   @param path path from which the wxTextAttr shall be read
	* 	@param rootNode root node of the path
    *   @param value pointer to an allocated wxTextAttr in which the result shall be stored
    *   @return true if the wxTextAttr has been found in the given path else return false
    */
    bool Read(const wxString& path, xmlNode* rootNode, wxTextAttr *attr);
	
	/**
    *   Read a wxTextAttr from the given path
    *   @param path path from which the value shall be read
	* 	@param rootNode root node of the path
    *   @return the wxTextAttr in the given path if founded the default value else
    */
    wxTextAttr ReadTextAttr(const wxString& path, xmlNode* rootNode );

private :

	xmlNode* AssertPath( wxString& path, xmlNode* rootNode );
    xmlNode* GetUniqElement(xmlNode* p, const wxString& q);
    void SetNodeText(xmlNode *n, const char* t);
    inline void Collapse(wxString& str) const;
    wxString InvalidNameMessage(const wxString& what, const wxString& sub, xmlNode *localPath) const;
};

#endif
