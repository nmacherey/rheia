/**
*   @file RheiaLibLoader.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	25-November-2009
*	@version 0.0.2
*/
#ifndef RheiaLibLoader_h_
#define RheiaLibLoader_h_

#include <RheiaPMgtSettings.h>
#include <RheiaGlobals.h>

#include <RheiaManager.h>

#include <map>
#include <vector>

#include <wx/event.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/string.h>
#include <wx/dynlib.h>

/**
*   @struct RheiaDynamicLibrary
*   @brief For mapping libraries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	25-November-2009
*	@version 0.0.1
*/
struct RheiaDynamicLibrary
{
    RheiaDynamicLibrary() : lib(NULL) {}

#ifdef SWIG
	~RheiaDynamicLibrary(){}
	%rename(RheiaDynamicLibraryCopy) RheiaDynamicLibrary( const RheiaDynamicLibrary& rhs );
#endif
    RheiaDynamicLibrary( const RheiaDynamicLibrary& rhs ):
        path( rhs.path ),
        name( rhs.name ),
        lib( rhs.lib )
        {};

    wxString path;
    wxString name;
    wxDynamicLibrary* lib;
};

/**
*   Here we associated a map of libraries in order to register them
*   in RheiaLibLoader.
*/
typedef std::map< wxString , RheiaDynamicLibrary > RheiaDynamicLibraryMap;

/**
*	@class RheiaLibLoader
*
*	@brief This is the main class for managing dynamic library loading in Rheia
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	25-November-2009
*	@version 0.0.1
**/

class PMGT_DLLEXPORT RheiaLibLoader : public Singleton<RheiaLibLoader>
{
	/** Give Singleton access to our private members */
	friend class Singleton<RheiaLibLoader>;
	/** Give RheiaManager Access to our private memebers */
	friend class RheiaManager;
public :
    /**
    *   This method will load the dynamic library and register it in this
    *   manager. You have to check if the library has been properly loaded
    *   by calling RheiaDyanmicLibrary::lib->IsLoaded();
    *   @param filename full path to the library to load using wxWidgets library
    *       loading tools
    *   @return the registered RheiaDynamicLibrary reference
    */
    RheiaDynamicLibrary* LoadLibrary(const wxString& filename);

    /**
    *   Remove a library using its wxDynamicLibrary reference.
    *   This method will find the library in the registered libraries and
    *   unload/unmap it from the OS, finally will remove its information from
    *   this manager.Please take care after a call to this method the given
    *   argument will no longer be available.
    *
    *   @param lib wxDynamicLibrary reference to remove
    *   @return true if the library has been removed
    */
    bool RemoveLibrary(wxDynamicLibrary* lib);

#ifdef SWIG
	%rename(RemoveLibraryByObject) RemoveLibrary(RheiaDynamicLibrary* lib);
#endif
    /**
    *   Remove a library using its RheiaDynamicLibrary reference.
    *   This method will find the library in the registered libraries and
    *   unload/unmap it from the OS, finally will remove its information from
    *   this manager. Please take care after a call to this method the given
    *   argument will no longer be available.
    *
    *   @param lib RheiaDynamicLibrary reference to remove
    *   @return true if the library has been removed
    */
    bool RemoveLibrary(RheiaDynamicLibrary* lib);

#ifdef SWIG
	%rename(RemoveLibraryByName) RemoveLibrary(const wxString& name);
#endif
    /**
    *   Remove a library using its name.
    *   This method will find the library in the registered libraries and
    *   unload/unmap it from the OS, finally will remove its information from
    *   this manager.
    *
    *   @param name library name to remove
    *   @return true if the library has been removed
    */
    bool RemoveLibrary(const wxString& name);

#ifdef SWIG
	%rename(LibraryExists) Exists( wxDynamicLibrary* lib );
#endif
    /**
    *   Check if the given library is referenced in this manager
    *   @param lib wxDynamicLibrary reference to find
    *   @return true if the library has been found
    */
    bool Exists( wxDynamicLibrary* lib );

#ifdef SWIG
	%rename(LibraryExistsByObject) Exists( RheiaDynamicLibrary* lib );
#endif
    /**
    *   Check if the given library is referenced in this manager
    *   @param lib RheiaDynamicLibrary reference to find
    *   @return true if the library has been found
    */
    bool Exists( RheiaDynamicLibrary* lib );


#ifdef SWIG
	%rename(LibraryExistsByName) Exists( const wxString& name );
#endif
    /**
    *   Check if the given library is referenced in this manager
    *   @param name library name to find
    *   @return true if the library has been found
    */
    bool Exists( const wxString& name );

#ifdef SWIG
	%rename(FindLibraryByName) FindLibrary(const wxString& name);
#endif
    /**
    *   Find a dynamic library by its name
    *   If the library was not found this method will return NULL
    *   @param name library name to find
    *   @return true if the library has been found
    */
    RheiaDynamicLibrary* FindLibrary(const wxString& name);

    /**
    *   Find a dynamic library by its wxDynamicLibrary reference
    *   If the library was not found this method will return NULL
    *   @param lib wxDynamicLibrary reference to find
    *   @return true if the library has been found
    */
    RheiaDynamicLibrary* FindLibrary(wxDynamicLibrary* lib);

    /**
    *   Unload and remove all information contained in this
    *   manager. After this call any loaded dynamic library will
    *   no longer be availble. You should never have to call this method.
    */
    void Cleanup();

private :
    /**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/**
	*   Default constructor
	*   You cannot use directly this constrcutor, you have to call
	*   RheiaLibLoader::Get() to get the global instance of this class.
	*/
	RheiaLibLoader();

	/**
	*   Default destructor
	*   You cannot directly destroy this manager, you have to call
	*   RheiaLibLoader::Free() to do this. However you may NEVER
	*   call RheiaLibLoader::Free() this might result in big troubles
	*   in rheia. For information, RheiaManager will free this manager at application
	*   ShutDown.
	*/
	~RheiaLibLoader();

private :
    RheiaDynamicLibraryMap m_libraries;
};

#endif
