/**
*   @file RheiaConfigurationManager.h
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries and Reoganization
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#ifndef RheiaConfigurationManager_h_
#define RheiaConfigurationManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>
#include <RheiaManager.h>

#include <set>
#include <map>

/* libxml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;

typedef std::map< wxString , wxString > RheiaStringStringMap;

/* Rheia imports */
class RheiaConfigurationPanel;
class RheiaConfigurationPattern;
class RheiaProfileManager;

/* wxWidgets imports */
class wxArrayBool;

/**
*	@class RheiaConfigurationManager
*
*	@brief RheiaConfigurationManager provides developpers with an easy way to write xml configuration files
*   in order to keep data information between two application runs.
*
*	RheiaConfigurationManager object has been taken from the principle of the wxConfig and related
*   classes. It provides with easy methods to write and read information in an xml configuration file.
*   As in wxConfig, you can read write any basic types. However for the needs of the application it
*   has been completed with many other methods in order to write/read standard wxWidgets objects such
*   as wxArray's and wxString, and also to write/read any frame information or wxAuiManager information.
*   The macros written by wxWidgets developpers have been removed and the tool is using libxml2 to deal
*   with the xml configuration file.
*
*   This class is mainly a wrapper with the RheiaXmlManager that allows user to write their own xml
*   files (not the Rheia default configuration file) easilier than simply dealing with xml node trees
*   and namespaces.
*
*   You should abuse of using this class via RheiaManager::Get()->GetConfigurationManager() giving in
*   argument the configuration group or namespace in which you want to write information. This object
*   must be used to store any informations such as last used path for projects saving/loading or
*   workspaces saving/loading. It is an absolute necessity if you want your end user to feel comfortable
*   with the use of your application.
*
*   The main differences with the wxConfig objects are the number of methods proposed by this interface,
*   Simple Read/Write methods have been written and DoReadxxxx methods have simply been replaced by the
*   DoRead method as C++ compilers understand methods overloading with different types.
*   Moreover in order to remove the wxWidgets segmentation subject to many builds of the wxConfig class
*   for the same application, we have used a Builder Pattern working in the background in order to keep
*   simple information management in the same configuration file. Hence you might never have to build this
*   class directly and if you don't know xml you might never have to deal with for saving configuration
*   informations.
*
*   However, I'd like to thanks wxWidgets developpers for having so good and complete ideas.
*
*	@author Nicolas Macherey ( nm@graymat.fr )
*	@date	02-Dec-2008
*	@version 0.0.1
*/
class BASE_DLLEXPORT RheiaConfigurationManager
{
    /*****************************************************************************************************
    *   PRIVATE STATIC MEMBERS
    *****************************************************************************************************/
    /** this static variable specify if the manager shall reload its node or not */
    static bool m_reload;

    /*****************************************************************************************************
    *   FRIENDS
    *****************************************************************************************************/
    /** Give RheiaConfigurationPattern Access to our private members */
    friend class RheiaConfigurationPattern;

    /** Give RheiaManager Access to our private members */
    friend class RheiaManager;

    /** Give RheiaProfileManager Access to our private members */
    friend class RheiaProfileManager;

    /** Give RheiaConfigurationPathsDialog Access to our private members */
    friend class RheiaConfigurationPathsDialog;

private :
    /*****************************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    *****************************************************************************************************/
    /**
    *   Default constructor
    *   This constructor is private you should never use directly this constrcutor
    *   because RheiaConfigurationManager is a wrapper class similar to wxWidgets
    *   wxConfig class. which allow you to easily store configuration information
    *   in a dedicated xml database file.
    *   To get a proper RheiaConfigurationManager Instance you have to use
    *   RheiaManager::Get()->GetConfigurationManager( namespace );
    */
    RheiaConfigurationManager();

    /**
    *   Default constructor
    *   This constructor is private you should never use directly this constrcutor
    *   because RheiaConfigurationManager is a wrapper class similar to wxWidgets
    *   wxConfig class. which allow you to easily store configuration information
    *   in a dedicated xml database file.
    *   To get a proper RheiaConfigurationManager Instance you have to use
    *   RheiaManager::Get()->GetConfigurationManager( namespace );
    *
    *   However for axplanation RheiaConfigurationManager instances are working
    *   based on an xmlNode which correspond to its corresponding namespace root
    *   node in the global configuration file. You can easily write information
    *   in any other xml file via RheiaXmlManager. This class is principaly an
    *   helper for RheiaXmlManager to allow developper to write xml without writing
    *   any xml line and dealing with xmlNode and xmlDoc.
    */
    RheiaConfigurationManager(xmlDoc *doc, xmlNode *root);

    /** Default destructor */
    ~RheiaConfigurationManager();

public :
    /*****************************************************************************************************
    *   CONFIGURATION MANAGEMENT METHODS
    *****************************************************************************************************/
    /**
    *   Clear all nodes from your namespace
    *   This will removed all children nodes from your namespace root. After a call to this
    *   method your instance is still valid but all configuration information have been lost.
    *   If you want to definitly remove your namespace you have to call
    *   RheiaConfiguration::Delete().
    */
    void Clear();

    /**
    *   Delete all nodes from your namespace and the namespace itself
    *   WARNING : After a call to this method the instance is invalid and any call to a write
    *   or read method will resutl in unexpected behaviours. You should never call this method
    *   If you still want to do so, please be sure to do it at the very end of use.
    */
    void Delete();

#ifdef SWIG
	%rename(DeletePath) Delete( const wxString& path );
#endif
    /**
    *   Delete the children corresponding to the given path
    *   This method will delete the last children in the path given in argument
    *   All its information will be lost, the instance is still valid.
    *   @param path path name we want to delete
    */
    void Delete( const wxString& path );

    /*****************************************************************************************************
    *   FIRST LEVEL PRIMITIVES WRITING AND READING STANDARD VARIABLES
    *****************************************************************************************************/

        /*************************************************************************************
        *   STRING METHODS FOR READING AND WRITING
        *************************************************************************************/
#ifdef SWIG
	 %rename(WriteString) Write(const wxString& path,  const wxString& value,bool ignoreEmpty = false);
#endif
    /**
    *   Write a wxString in the namespace at the given path
    *   @param path path from namespace root node in which the string has to be stored
    *   @param value the string to write in the given path
    *   @param ignoreEmpty specify if empty strings shall be ignored or not
    */
    void Write(const wxString& path,  const wxString& value,bool ignoreEmpty = false);

#ifdef SWIG
	 %rename(ReadString) Read(const wxString& path, const wxString& defaultVal = wxEmptyString);
#endif
    /**
    *   Read a wxString from the given path
    *   @param path path from which the string shall be read
    *   @param defaultVal default value for the string if the path does not exists
    *   @return the string in the given path if founded the default value else
    */
    wxString Read(const wxString& path, const wxString& defaultVal = wxEmptyString);

#ifdef SWIG
	 %rename(DoReadString) DoRead(const wxString& path, wxString* str);
#endif
    /**
    *   Read a wxString from the given path
    *   @param path path from which the string shall be read
    *   @param str pointer to an allocated string in which the result shall be stored
    *   @return true if the string has been found in the given path else return false
    */
    bool DoRead(const wxString& path, wxString* str);

#ifdef SWIG
	%rename(WriteChars) Write(const wxString& path, const char* str);
#endif
    /**
    *   Write a char* in the namespace at the given path
    *   @param path path from namespace root node in which the string has to be stored
    *   @param str the string to write in the given path
    */
    void Write(const wxString& path, const char* str);

        /*************************************************************************************
        *   INT METHODS FOR READING AND WRITING
        *************************************************************************************/

#ifdef SWIG
	%rename(WriteInt) Write(const wxString& path, int value);
#endif
    /**
    *   Write an INT in the namespace at the given path
    *   @param path path from namespace root node in which the INT has to be stored
    *   @param value the INT to write in the given path
    */
    void Write(const wxString& path, int value);

#ifdef SWIG
	%rename(DoReadInt) DoRead(const wxString& path, int* value);
#endif
    /**
    *   Read an INT from the given path
    *   @param path path from which the INT shall be read
    *   @param value pointer to an allocated INT in which the result shall be stored
    *   @return true if the INT has been found in the given path else return false
    */
    bool DoRead(const wxString& path, int* value);

    /**
    *   Read an INT from the given path
    *   @param path path from which the value shall be read
    *   @param defaultVal default value for the INT if the path does not exists
    *   @return the INT in the given path if founded the default value else
    */
    int  ReadInt(const wxString& path, int defaultVal = 0);

        /*************************************************************************************
        *   BOOL METHODS FOR READING AND WRITING
        *************************************************************************************/
#ifdef SWIG
	%rename(WriteBool) Write(const wxString& path ,  bool value);
#endif
    /**
    *   Write a BOOL in the namespace at the given path
    *   @param path path from namespace root node in which the INT has to be stored
    *   @param value the BOOL to write in the given path
    */
    void Write(const wxString& path ,  bool value);

#ifdef SWIG
	%rename(DoReadBool) DoRead(const wxString& path,  bool* value);
#endif
    /**
    *   Read a BOOL from the given path
    *   @param path path from which the INT shall be read
    *   @param value pointer to an allocated BOOL in which the result shall be stored
    *   @return true if the BOOL has been found in the given path else return false
    */
    bool DoRead(const wxString& path,  bool* value);

    /**
    *   Read a BOOL from the given path
    *   @param path path from which the value shall be read
    *   @param defaultVal default value for the BOOL if the path does not exists
    *   @return the BOOL in the given path if founded the default value else
    */
    bool ReadBool(const wxString& path, bool defaultVal = false);

        /*************************************************************************************
        *   DOUBLE METHODS FOR READING AND WRITING
        *************************************************************************************/
#ifdef SWIG
	%rename(WriteDouble) Write(const wxString& path ,  bool value);
#endif
    /**
    *   Write a DOUBLE in the namespace at the given path
    *   @param path path from namespace root node in which the INT has to be stored
    *   @param value the DOUBLE to write in the given path
    */
    void Write(const wxString& path, double value);

#ifdef SWIG
	%rename(DoReadDouble) DoRead(const wxString& path, double* value);
#endif
    /**
    *   Read a DOUBLE from the given path
    *   @param path path from which the INT shall be read
    *   @param value pointer to an allocated DOUBLE in which the result shall be stored
    *   @return true if the DOUBLE has been found in the given path else return false
    */
    bool DoRead(const wxString& path, double* value);

    /**
    *   Read a DOUBLE from the given path
    *   @param path path from which the value shall be read
    *   @param defaultVal default value for the DOUBLE if the path does not exists
    *   @return the DOUBLE in the given path if founded the default value else
    */
    double ReadDouble(const wxString& path, double defaultVal = 0.0f);

    /*****************************************************************************************************
    *   SECOND LEVEL PRIMITIVES WRITING AND READING STANDARD WXWIDGETS ARRAYS
    *****************************************************************************************************/

        /*************************************************************************************
        *   ARRAY STRING METHODS FOR READING AND WRITING
        *************************************************************************************/
#ifdef SWIG
	%rename(WriteArrayString) Write(const wxString& path,  const wxArrayString& as);
#endif
    /**
    *   Write a wxArrayString in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayString has to be stored
    *   @param as the wxArrayString to write in the given path
    */
    void Write(const wxString& path,  const wxArrayString& as);

#ifdef SWIG
	%rename(DoReadArrayString) DoRead(const wxString& path, wxArrayString* as);
#endif
    /**
    *   Read a wxArrayString from the given path
    *   @param path path from which the INT shall be read
    *   @param as pointer to an allocated wxArrayString in which the result shall be stored
    *   @return true if the wxArrayString has been found in the given path else return false
    */
    void DoRead(const wxString& path, wxArrayString* as);

    /**
    *   Read a wxArrayString from the given path
    *   @param path path from which the wxArrayString shall be read
    *   @return the wxArrayString in the given path if founded, an empty else
    */
    wxArrayString ReadArrayString(const wxString& path);

        /*************************************************************************************
        *   STRING TO STRING MAP METHODS FOR READING AND WRITING
        *************************************************************************************/

#ifdef SWIG
	%rename(WriteStringStringMap) Write(const wxString& path,  const RheiaStringStringMap& as);
#endif
    /**
    *   Write a RheiaStringStringMap in the namespace at the given path
    *   @param path path from namespace root node in which the RheiaStringStringMap has to be stored
    *   @param as the RheiaStringStringMap to write in the given path
    */
    void Write(const wxString& path,  const RheiaStringStringMap& as);

#ifdef SWIG
	%rename(DoReadStringStringMap) DoRead(const wxString& path, RheiaStringStringMap* as);
#endif
    /**
    *   Read a RheiaStringStringMap from the given path
    *   @param path path from which the INT shall be read
    *   @param as pointer to an allocated RheiaStringStringMap in which the result shall be stored
    *   @return true if the RheiaStringStringMap has been found in the given path else return false
    */
    void DoRead(const wxString& path, RheiaStringStringMap* as);

    /**
    *   Read a RheiaStringStringMap from the given path
    *   @param path path from which the RheiaStringStringMap shall be read
    *   @return the RheiaStringStringMap in the given path if founded, an empty else
    */
    RheiaStringStringMap ReadStringStringMap(const wxString& path);

        /*************************************************************************************
        *   ARRAY INT METHODS FOR READING AND WRITING
        *************************************************************************************/

#ifdef SWIG
	%rename(WriteArrayInt) Write(const wxString& path,  const wxArrayInt& arrayInt);
#endif
    /**
    *   Write a wxArrayInt in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayInt has to be stored
    *   @param arrayInt the wxArrayInt to write in the given path
    */
    void Write(const wxString& path,  const wxArrayInt& arrayInt);

#ifdef SWIG
	%rename(DoReadArrayInt) DoRead(const wxString& path, wxArrayInt* arrayInt);
#endif
    /**
    *   Read a wxArrayInt from the given path
    *   @param path path from which the wxArrayInt shall be read
    *   @param arrayInt pointer to an allocated wxArrayInt in which the result shall be stored
    *   @return true if the wxArrayInt has been found in the given path else return false
    */
    void DoRead(const wxString& path, wxArrayInt* arrayInt);

    /**
    *   Read a wxArrayInt from the given path
    *   @param path path from which the wxArrayInt shall be read
    *   @return the wxArrayInt in the given path if founded, an empty else
    */
    wxArrayInt ReadArrayInt(const wxString& path);

        /*************************************************************************************
        *   ARRAY DOUBLE METHODS FOR READING AND WRITING
        *************************************************************************************/
#ifdef SWIG
	%rename(WriteArrayDouble) Write(const wxString& path, const wxArrayDouble& arrayDouble);
#endif
    /**
    *   Write a wxArrayDouble in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayDouble has to be stored
    *   @param arrayDouble the wxArrayDouble to write in the given path
    */
    void Write(const wxString& path, const wxArrayDouble& arrayDouble);

#ifdef SWIG
	%rename(DoReadArrayDouble) DoRead(const wxString& path, wxArrayDouble* arrayDouble);
#endif
    /**
    *   Read a wxArrayDouble from the given path
    *   @param path path from which the wxArrayDouble shall be read
    *   @param arrayDouble pointer to an allocated wxArrayDouble in which the result shall be stored
    *   @return true if the wxArrayDouble has been found in the given path else return false
    */
    void DoRead(const wxString& path, wxArrayDouble* arrayDouble);

    /**
    *   Read a wxArrayDouble from the given path
    *   @param path path from which the wxArrayDouble shall be read
    *   @return the wxArrayDouble in the given path if founded, an empty else
    */
    wxArrayDouble ReadArrayDouble(const wxString& path);

        /*************************************************************************************
        *   ARRAY BOOL METHODS FOR READING AND WRITING
        *************************************************************************************/
		
#ifdef SWIG
	%rename(WriteArrayBool) Write(const wxString& path, const wxArrayBool& arrayBool);
#endif
    /**
    *   Write a wxArrayBool in the namespace at the given path
    *   @param path path from namespace root node in which the wxArrayBool has to be stored
    *   @param arrayBool the wxArrayBool to write in the given path
    */
    void Write(const wxString& path, const wxArrayBool& arrayBool);

#ifdef SWIG
	%rename(DoReadArrayBool) DoRead(const wxString& path, wxArrayBool* arrayBool);
#endif
    /**
    *   Read a wxArrayBool from the given path
    *   @param path path from which the wxArrayBool shall be read
    *   @param arrayBool pointer to an allocated wxArrayBool in which the result shall be stored
    *   @return true if the wxArrayBool has been found in the given path else return false
    */
    void DoRead(const wxString& path, wxArrayBool* arrayBool);

    /**
    *   Read a wxArrayBool from the given path
    *   @param path path from which the wxArrayBool shall be read
    *   @return the wxArrayBool in the given path if founded, an empty else
    */
    wxArrayBool ReadArrayBool(const wxString& path );


    /*****************************************************************************************************
    *   SECOND LEVEL PRIMITIVES WRITING AND READING STANDARD STL ARRAYS
    *****************************************************************************************************/

        /*************************************************************************************
        *   ARRAY STRING METHODS FOR READING AND WRITING
        *************************************************************************************/

#ifdef SWIG
	%rename(WriteStdArrayString) Write(const wxString& path,  const std::vector<std::string>& arrayString);
#endif
    /**
    *   Write a std::vector<std::string> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<std::string> has to be stored
    *   @param arrayString the std::vector<std::string> to write in the given path
    */
    void Write(const wxString& path,  const std::vector<std::string>& arrayString);

#ifdef SWIG
	%rename(DoReadStdArrayString) DoRead(const wxString& path, std::vector<std::string>* arrayString);
#endif
    /**
    *   Read a std::vector<std::string> from the given path
    *   @param path path from which the std::vector<std::string> shall be read
    *   @param arrayString pointer to an allocated std::vector<std::string> in which the result shall be stored
    *   @return true if the std::vector<std::string> has been found in the given path else return false
    */
    void DoRead(const wxString& path, std::vector<std::string>* arrayString);

    /**
    *   Read a std::vector<std::string> from the given path
    *   @param path path from which the std::vector<std::string> shall be read
    *   @return the std::vector<std::string> in the given path if founded, an empty else
    */
    std::vector<std::string> ReadStdArrayString(const wxString& path);

        /*************************************************************************************
        *   ARRAY INT METHODS FOR READING AND WRITING
        *************************************************************************************/

#ifdef SWIG
	%rename(WriteStdArrayInt) Write(const wxString& path, const std::vector<int>& arrayInt);
#endif
    /**
    *   Write a std::vector<int> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<int> has to be stored
    *   @param arrayInt the std::vector<int> to write in the given path
    */
    void Write(const wxString& path, const std::vector<int>& arrayInt);

#ifdef SWIG
	%rename(DoReadStdArrayInt) DoRead(const wxString& path, std::vector<int>* arrayInt);
#endif
    /**
    *   Read a std::vector<int> from the given path
    *   @param path path from which the std::vector<int> shall be read
    *   @param arrayInt pointer to an allocated std::vector<int> in which the result shall be stored
    *   @return true if the std::vector<int> has been found in the given path else return false
    */
    void DoRead(const wxString& path, std::vector<int>* arrayInt);

    /**
    *   Read a std::vector<int> from the given path
    *   @param path path from which the std::vector<int> shall be read
    *   @return the std::vector<int> in the given path if founded, an empty else
    */
    std::vector<int> ReadStdArrayInt(const wxString& path);

        /*************************************************************************************
        *   ARRAY DOUBLE METHODS FOR READING AND WRITING
        *************************************************************************************/
		
#ifdef SWIG
	%rename(WriteStdArrayDouble) Write(const wxString& path,  const std::vector<double>& arrayDouble);
#endif
    /**
    *   Write a std::vector<double> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<double> has to be stored
    *   @param arrayDouble the std::vector<double> to write in the given path
    */
    void Write(const wxString& path,  const std::vector<double>& arrayDouble);

#ifdef SWIG
	%rename(DoReadStdArrayDouble) DoRead(const wxString& path,  std::vector<double>* arrayDouble);
#endif
    /**
    *   Read a std::vector<double> from the given path
    *   @param path path from which the std::vector<double> shall be read
    *   @param arrayDouble pointer to an allocated std::vector<double> in which the result shall be stored
    *   @return true if the std::vector<double> has been found in the given path else return false
    */
    void DoRead(const wxString& path,  std::vector<double>* arrayDouble);

    /**
    *   Read a std::vector<double> from the given path
    *   @param path path from which the std::vector<double> shall be read
    *   @return the std::vector<double> in the given path if founded, an empty else
    */
    std::vector<double> ReadStdArrayDouble(const wxString& path);

        /*************************************************************************************
        *   ARRAY BOOL METHODS FOR READING AND WRITING
        *************************************************************************************/

#ifdef SWIG
	%rename(WriteStdArrayBool) Write(const wxString& path,  const std::vector<bool>& arrayBool);
#endif
    /**
    *   Write a std::vector<bool> in the namespace at the given path
    *   @param path path from namespace root node in which the std::vector<bool> has to be stored
    *   @param arrayBool the std::vector<bool> to write in the given path
    */
    void Write(const wxString& path,  const std::vector<bool>& arrayBool);

#ifdef SWIG
	%rename(DoReadStdArrayBool) DoRead(const wxString& path, std::vector<bool>* arrayBool);
#endif
    /**
    *   Read a std::vector<bool> from the given path
    *   @param path path from which the std::vector<bool> shall be read
    *   @param arrayBool pointer to an allocated std::vector<bool> in which the result shall be stored
    *   @return true if the std::vector<bool> has been found in the given path else return false
    */
    void DoRead(const wxString& path, std::vector<bool>* arrayBool);

    /**
    *   Read a std::vector<bool> from the given path
    *   @param path path from which the std::vector<bool> shall be read
    *   @return the std::vector<bool> in the given path if founded, an empty else
    */
    std::vector<bool> ReadStdArrayBool(const wxString& path);

    /*****************************************************************************************************
    *   WXCOLOUR PRIMITIVES WRITING AND READING
    *****************************************************************************************************/

#ifdef SWIG
	%rename(WriteColour) Write(const wxString& path, const wxColour& c);
#endif
    /**
    *   Write a wxColour in the namespace at the given path
    *   @param path path from namespace root node in which the wxColour has to be stored
    *   @param c the wxColour to write in the given path
    */
    void Write(const wxString& path, const wxColour& c);

#ifdef SWIG
	%rename(DoReadColour) DoRead(const wxString& path, wxColour* value);
#endif
    /**
    *   Read a wxColour from the given path
    *   @param path path from which the wxColour shall be read
    *   @param value pointer to an allocated wxColour in which the result shall be stored
    *   @return true if the wxColour has been found in the given path else return false
    */
    bool DoRead(const wxString& path, wxColour* value);

    /**
    *   Read a wxColour from the given path
    *   @param path path from which the value shall be read
    *   @param defaultVal default value for the wxColour if the path does not exists
    *   @return the wxColour in the given path if founded the default value else
    */
    wxColour ReadColour(const wxString& path, const wxColour& defaultVal = *wxBLACK);

#ifdef SWIG
	%rename(WriteFont) Write(const wxString& name, const wxFont& font);
#endif
    /**
    *   Write a wxFont in the namespace at the given path
    *   @param path path from namespace root node in which the wxFont has to be stored
    *   @param font the wxFont to write in the given path
    */
	void Write(const wxString& name, const wxFont& font);

#ifdef SWIG
	%rename(DoReadFond) DoRead(const wxString& name, wxFont *font);
#endif
	/**
    *   Read a wxFont from the given path
    *   @param path path from which the wxFont shall be read
    *   @param value pointer to an allocated wxFont in which the result shall be stored
    *   @return true if the wxFont has been found in the given path else return false
    */
    bool DoRead(const wxString& name, wxFont *font);

    /**
    *   Read a wxFont from the given path
    *   @param path path from which the value shall be read
    *   @return the wxFont in the given path if founded the default value else
    */
    wxFont ReadFont(const wxString& name );

#ifdef SWIG
	%rename(WriteTextAttr) Write(const wxString& name, const wxTextAttr& attr);
#endif
    /**
    *   Write a wxTextAttr in the namespace at the given path
    *   @param path path from namespace root node in which the wxTextAttr has to be stored
    *   @param font the wxTextAttr to write in the given path
    */
	void Write(const wxString& name, const wxTextAttr& attr);

#ifdef SWIG
	%rename(DoReadTextAttr) Read(const wxString& name, wxTextAttr *attr);
#endif
	/**
    *   Read a wxTextAttr from the given path
    *   @param path path from which the wxTextAttr shall be read
    *   @param value pointer to an allocated wxTextAttr in which the result shall be stored
    *   @return true if the wxTextAttr has been found in the given path else return false
    */
    bool Read(const wxString& name, wxTextAttr *attr);

    /**
    *   Read a wxTextAttr from the given path
    *   @param path path from which the value shall be read
    *   @return the wxTextAttr in the given path if founded the default value else
    */
    wxTextAttr ReadTextAttr(const wxString& name );

    /*****************************************************************************************************
    *   WXAUIMANAGER PRIMITIVES FOR WRITING AND READING
    *****************************************************************************************************/

    /**
    *   Write wxAuiManager, wxAuiDockArt sash size
    *   (i.e : size of the resizing tool between pane's)
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt Sash Size shall be written
    */
    void WriteSashSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt caption size
    *   (i.e : size of the pane's caption if displayed)
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt caption Size shall be written
    */
    void WriteCaptionSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt gripper size
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt gripper Size shall be written
    */
    void WriteGripperSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane border size
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane border Size shall be written
    */
    void WritePaneBorderSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane button size
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane button Size shall be written
    */
    void WritePaneButtonSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane active caption colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane active caption colour shall be written
    */
    void WriteActiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane active caption gradient colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane active caption gradient colour shall be written
    */
    void WriteActiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane active caption text colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane active caption text colour shall be written
    */
    void WriteActiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane inactive caption colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane inactive caption colour shall be written
    */
    void WriteInactiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane inactive caption gradient colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane inactive caption gradient colour shall be written
    */
    void WriteInactiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane inactive caption text colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane inactive caption text colour shall be written
    */
    void WriteInactiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Write wxAuiManager, wxAuiDockArt pane gripper colour
    *   @param path path in which the value shall be written
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane grippers colour shall be written
    */
    void WriteGripperColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager sash size at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt sash size shall be read
    */
    void ReadSashSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager caption size at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt caption size shall be read
    */
    void ReadCaptionSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager gripper size at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt gripper size shall be read
    */
    void ReadGripperSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager pane border size at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane border size shall be read
    */
    void ReadPaneBorderSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager pane button size at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt pane button size shall be read
    */
    void ReadPaneButtonSize( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager active caption colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt active caption colour shall be read
    */
    void ReadActiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager active gradient colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt active gradient colour shall be read
    */
    void ReadActiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager active caption text colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt active caption text colour shall be read
    */
    void ReadActiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager inactive caption colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt inactive caption colour shall be read
    */
    void ReadInactiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager inactive caption gradient colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt inactive caption gradient colour shall be read
    */
    void ReadInactiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager inactive caption text colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt inactive caption text colour shall be read
    */
    void ReadInactiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   Read the Layout manager gripper colour at the given path and
    *   store it in the given wxAuiManager, wxAuiDockArt.
    *   @param path path from which the value shall be read
    *   @param LayoutManager wxAuiManager object for which the wxAuiDockArt gripper colour shall be read
    */
    void ReadGripperColor( const wxString& path, wxAuiManager* LayoutManager );

    /**
    *   wxAuiManager's perspectives are stored in a wxString in order to allow them to
    *   be easily loaded/saved in any configuration file. Here is the place to save the
    *   current perspective of the given wxAuiManager in the given path with the given name.
    *   if the overwrite_existing flag is set to true and a perspective with the same name
    *   already exists, it will be replaced by the new one.
    *
    *   @param path path name in which the perspective shall be written
    *   @param LayoutManager wxAuiManager object for which the perspective shall be written
    *   @param pName the perspective name in the configuration file
    *   @param overwrite_existing specify if we should overwrite existing perspectives with the new one
    */
    void WritePerspective( const wxString& path, wxAuiManager *LayoutManager, const wxString& pName, bool overwrite_existing );

#ifdef SWIG
	%rename(WritePerspectiveString) WritePerspective( const wxString& path, const wxString& pName, const wxString& pValue, bool overwrite_existing );
#endif
    /**
    *   wxAuiManager's perspectives are stored in a wxString in order to allow them to
    *   be easily loaded/saved in any configuration file. Here is the place to save the
    *   given perspective in the given path with the given name.
    *   If the overwrite_existing flag is set to true and a perspective with the same name
    *   already exists, it will be replaced by the new one.
    *
    *   @param path path name in which the perspective shall be written
    *   @param pName the perspective name in the configuration file
    *   @param pValue the perspective value to write in the configuration file
    *   @param overwrite_existing specify if we should overwrite existing perspectives with the new one
    */
    void WritePerspective( const wxString& path, const wxString& pName, const wxString& pValue, bool overwrite_existing );

    /**
    *   wxAuiManager's perspectives are stored in a wxString in order to allow them to
    *   be easily loaded/saved in any configuration file. Here is the place to load a
    *   perspective from the configuration file.
    *
    *   @param path path name from which the perspective shall be read
    *   @param LayoutManager wxAuiManager object for which the perspective shall be read
    *   @param pName the perspective name in the configuration file
    */
    void ReadPerspective( const wxString& path, wxAuiManager *LayoutManager, const wxString& pName );

    /**
    *   This method write all information accordingly to the given wxAuiManager
    *   It will save all the perspective given in argument and all its wxAuiDockArt
    *   settings.
    *
    *   @param path path name in which the layout shall be written
    *   @param LayoutManager wxAuiManager object for which the layout shall be written
    *   @param LayoutNames layout perspectives names
    *   @param LayoutValues layout perspectives values
    *   @param overwrite_existing specify if we should overwrite existing layout with the new one
    */
    void WriteLayout( const wxString& path, wxAuiManager* LayoutManager, const wxArrayString& LayoutNames, const wxArrayString& LayoutValues, bool overwrite_existing = true );

    /**
    *   Read the layout information at the given path and load it
    *   in the given LayoutManager.
    *
    *   @param path path name from which the layout shall be read
    *   @param LayoutManager wxAuiManager object for which the layout shall be read
    *   @param pName name of the perspective to load in the LayoutManager
    */
    void ReadLayout( const wxString& path, wxAuiManager* LayoutManager, const wxString& pName );

    /*****************************************************************************************************
    *   WXFRAME PRIMITIVES FOR WRITING AND READING
    *****************************************************************************************************/

    /**
    *   Write a boolean specifying if the frame has a status bar or
    *   not.
    *   @param path path name in which the information shall be written
    *   @param frame frame for which the information shall be written
    */
    void WriteFrameStatusBar( const wxString& path, wxFrame* frame );

    /**
    *   Read a boolean specifying if the frame has a status bar or
    *   not.
    *   @param path path name from which the information shall be read
    *   @param defaultval default value for this boolean flag
    *   @return true if the frame shall display a status bar or not
    */
    bool ReadFrameStatusBar( const wxString& path , bool defaultval = true );

    /**
    *   Write a boolean specifying if the frame is fullscreen or
    *   not.
    *   @param path path name in which the information shall be written
    *   @param frame frame for which the information shall be written
    */
    void WriteFrameFullScreen( const wxString& path, wxFrame* frame );

    /**
    *   Read a boolean specifying if the frame is fullscreen or
    *   not.
    *   @param path path name from which the information shall be read
    *   @param defaultval default value for this boolean flag
    *   @return true if the frame shall display in fullscreen mode or not
    */
    bool ReadFrameFullScreen( const wxString& path , bool defaultval = false );

    /**
    *   Write a boolean specifying if the frame is maximized or
    *   not.
    *   @param path path name in which the information shall be written
    *   @param frame frame for which the information shall be written
    */
    void WriteFrameMaximized( const wxString& path, wxFrame* frame );

    /**
    *   Read a boolean specifying if the frame is maximized or
    *   not.
    *   @param path path name from which the information shall be read
    *   @param defaultval default value for this boolean flag
    *   @return true if the frame shall display in maximized mode or not
    */
    bool ReadFrameMaximized( const wxString& path , bool defaultval = true );

    /**
    *   Write the frame position in the given path
    *   @param path path name in which the information shall be written
    *   @param frame frame for which the information shall be written
    */
    void WriteFramePosition( const wxString& path, wxFrame* frame );

    /**
    *   Read the frame position from the given path
    *   @param path path name from which the information shall be read
    *   @param defaultval default frame position if not found
    *   @return the position read from the given path if found, else the defaultVal
    */
    wxPoint ReadFramePosition( const wxString& path , wxPoint defaultval = wxDefaultPosition );

#ifdef SWIG
	%rename(ReadFramePositionAndSet) ReadFramePosition( const wxString& path , wxFrame *frame , wxPoint defaultval = wxDefaultPosition );
#endif
    /**
    *   Read the frame position from the given path and set it in the frame
    *   @param path path name from which the information shall be read
    *   @param frame the frame for which the position shall be read and setted
    *   @param defaultval default frame position if not found
    */
    void ReadFramePosition( const wxString& path , wxFrame *frame , wxPoint defaultval = wxDefaultPosition );

    /**
    *   Write the frame size in the given path
    *   @param path path name in which the information shall be written
    *   @param frame frame for which the information shall be written
    */
    void WriteFrameSize( const wxString& path, wxFrame* frame );

    /**
    *   Read the frame size from the given path
    *   @param path path name from which the information shall be read
    *   @param defaultval default frame size if not found
    *   @return the size read from the given path if found, else the defaultVal
    */
    wxSize ReadFrameSize( const wxString& path , wxSize defaultval = wxDefaultSize );

#ifdef SWIG
	%rename(ReadFrameSizeAndSet) ReadFrameSize( const wxString& path , wxFrame *frame , wxSize defaultval = wxDefaultSize );
#endif
    /**
    *   Read the frame size from the given path and set it in the frame
    *   @param path path name from which the information shall be read
    *   @param frame the frame for which the size shall be read and setted
    *   @param defaultval default frame size if not found
    */
    void ReadFrameSize( const wxString& path , wxFrame *frame , wxSize defaultval = wxDefaultSize );

    /**
    *   Write all frame's related information in the path
    *   @param path path name in which the information shall be written
    *   @param frame frame for which the information shall be written
    */
    void WriteFrameInfo( const wxString& path, wxFrame *frame );

    /**
    *   Read all frame's related information from the path
    *   @param path path name from which the information shall be read
    *   @param frame frame in which the information shall be stored after reading
    */
    void ReadFrameInfo( const wxString& path, wxFrame *frame );

    /************************************************************************************
    *   APPLICATIONS MAIN FRAMES INFORMATION WRITTING
    ************************************************************************************/
    /**
    *   This method simply use the Application's frame stored in the RheiaManager
    *   and write all its basic information using the methods above.
    *   You shall never have to call this method unless you are a Rheia Core Developper
    *   and if you need to do specific stuff for Rheia Main Frames.
    */
    void WriteBasicConfiguration( wxFrame *main_frame , wxAuiManager *LayoutManager );

    /**
    *	This function is used for listing first level childrens for
    *   the namespace managed by this instance.
    *   It will be a usefull method if you want ot check or manage version
    *   updates in your configuration file.
    */
    wxArrayString ListRootChildrens();

#ifndef SWIG
    /**
    *   Get the xmlDoc pointer of the root configuration
    *   file your namespace/group belongs to. Please remember to never
    *   call xmlFreeDoc when getting this information. You shall never have to use
    *   this method as I never do it when i am coding. You will alter all available
    *   Configuration groups already instanciated in the application and this will
    *   result in application crash.
    */
    xmlDoc* GetDocument() { return m_doc; };

    /************************************************************************************
    *   PROFILE MANAGER SPECIFIC METHODS
    ************************************************************************************/
    /**
    *	This function is used for listing first level childrens for
    *   the namespace managed by this instance. for the given property.
    *   This method is used in RheiaProfileManager in order to list all
    *   available profiles from the configuration file.
    *
    *   @param path path name to list the childrens for
    *   @param property property name to list the childrens for
    */
    wxArrayString ListRootChildrenNames(const wxString& path, const wxString& property);

    /**
    *	This method is used for adding a root children at the given path
    *   with the given property name and the given property value.
    *   It has been written for the needs of the RheiaProfileManager
    *
    *   @param path path name in which the child shall be created
    *   @param property property name to be added
    *   @param propertyValue property value to be stored
    */
    xmlNode* AddRootChildren( const wxString& path, const wxString& property, const wxString& propertyValue );

    /**
    *	This method is used for getting the first root children at the given path
    *   with given property value. This method has been designed for the needs of
    *   the RheiaProfileManager.
    *
    *   @param path path name in which the child shall be get
    *   @param property property name to be get
    *   @param propertyValue property value for sanity checks
    */
    xmlNode* GetRootChildren( const wxString& path, const wxString& property, const wxString& propertyValue );

private :
    /************************************************************************************
    *   PRIVATE MEMBERS
    ************************************************************************************/
    /** pointer to your namspace/group xmlDoc instance */
    xmlDoc* m_doc;

    /** namespace/group root node in the configuration file */
    xmlNode* m_root;

#endif

};

#endif
