/**
*   @file RheiaAppGlobals.h
*   This file is used to define general paths and extensions that will be used by Rheia Application.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaAppGlobals_h_
#define RheiaAppGlobals_h_

#include <wx/string.h>

#ifndef __WXMAC__
const wxString DEFAULT_CONSOLE_TERM  = _T("xterm -T $TITLE -e");
#else
const wxString DEFAULT_CONSOLE_TERM  = _T("osascript -e 'tell app \"Terminal\"' -e 'activate' -e 'do script \"$SCRIPT\"' -e 'end tell'");
#endif
const wxString DEFAULT_CONSOLE_SHELL = _T("/bin/sh -c");

/**
*	@namespace FileExt
*
*	@brief FileExt contains all the definitions corresponding to the files extension definitions
*   either for dynamic libraries, plugins and packages
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.1
*/
namespace FileExt{
    /**
    *   This is the basic extension for saving/loading workspace
    *   this extension is expressed using the dot before the extension name
    *   use WKSP_EXT_FILE to get the extension with the star before the extension
    *   use WKSP_EXT_FILE_STADARD to get the extension without any dot or star
    */
	static const wxString WKSP_EXT = wxT(".rwksp");

	/**
    *   This is the basic extension for saving/loading workspace
    *   this extension is expressed using the star before the extension name
    *   use WKSP_EXT to get the extension with the dot before the extension
    *   use WKSP_EXT_FILE_STADARD to get the extension without any dot or star
    */
	static const wxString WKSP_EXT_FILE = wxT("*.rwksp");

	/**
    *   This is the basic extension for saving/loading workspace
    *   this extension is expressed using the extension name only
    *   use WKSP_EXT to get the extension with the dot before the extension name
    *   use WKSP_EXT_FILE to get the extension with the star before the extension name
    */
	static const wxString WKSP_EXT_STANDARD = wxT("rwksp");

    /**
    *   This is the basic extension for saving/loading projects
    *   this extension is expressed using the dot before the extension name
    *   use PRJ_EXT_FILE to get the extension with the star before the extension
    *   use PRJ_EXT_FILE_STADARD to get the extension without any dot or star
    */
	static const wxString PRJ_EXT = wxT(".rprj");

	/**
    *   This is the basic extension for saving/loading projects
    *   this extension is expressed using the star before the extension name
    *   use PRJ_EXT to get the extension with the dot before the extension
    *   use PRJ_EXT_FILE_STADARD to get the extension without any dot or star
    */
	static const wxString PRJ_EXT_FILE = wxT("*.rprj");

	/**
    *   This is the basic extension for saving/loading projects
    *   this extension is expressed using the extension name only
    *   use PRJ_EXT to get the extension with the dot before the extension name
    *   use PRJ_EXT_FILE to get the extension with the star before the extension name
    */
	static const wxString PRJ_EXT_STANDARD = wxT("rprj");

    /**
    *   This is the basic extension for packages
    *   this extension is expressed using the dot before the extension name
    *   use PACKAGE_EXT_FILE to get the extension with the star before the extension
    *   use PACKAGE_EXT_FILE_STADARD to get the extension without any dot or star
    */
	static const wxString PACKAGE_EXT = wxT(".rpack");

	/**
    *   This is the basic extension for packages
    *   this extension is expressed using the star before the extension name
    *   use PACKAGE_EXT to get the extension with the dot before the extension
    *   use PACKAGE_EXT_FILE_STADARD to get the extension without any dot or star
    */
	static const wxString PACKAGE_EXT_FILE = wxT("*.rpack");

	/**
    *   This is the basic extension for packages
    *   this extension is expressed using the extension name only
    *   use PACKAGE_EXT to get the extension with the dot before the extension name
    *   use PACKAGE_EXT_FILE to get the extension with the star before the extension name
    */
	static const wxString PACKAGE_EXT_STANDARD = wxT("rpack");

	/**
    *   This is the basic extension for plugins
    *   this extension is expressed using the dot before the extension name
    *   use PLUGIN_FILE_EXT_STANDARD to get the extension without any dot or star
    */
    static const wxString PLUGIN_EXT = wxT(".rplugin");

    /**
    *   This is the basic extension for plugins
    *   this extension is expressed using the extension name only
    *   use PLUGIN_FILE_EXT to get the extension with the dot before the extension name
    */
    static const wxString PLUGIN_EXT_STANDARD = wxT("rplugin");

    /** This is the basic prefix for plugins */
    static const wxString PLUGIN_EXT_FILE = wxT("*.rplugin");

#if   defined ( __WIN32__ )
    /**
    *   This is the basic extension for dynamic libraries
    *   this extension is expressed using the dot before the extension name
    *   use DYNAMIC_LIBRARY_FILE_EXT_STANDARD to get the extension without any dot or star
    */
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".dll");

    /**
    *   This is the basic extension for dynamic libraries
    *   this extension is expressed using the extension name only
    *   use PACKAGE_EXT to get the extension with the dot before the extension name
    */
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("dll");

    /** This is the basic prefix for dynamic libraries */
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("");

    /**
    *   This option simply specify if the library prefix shall be managed by
    *   the application when dealing with dynamic libraries.
    */
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = false;
#elif defined ( __WXMAC__ )  || defined ( __WXCOCOA__ )
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".dylib");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("dylib");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#elif defined ( __linux__ )  || defined ( LINUX )
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".so");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("so");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#elif defined ( FREEBSD )    || defined ( __FREEBSD__ )
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".so");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("so");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#elif defined ( NETBSD )     || defined ( __NETBSD__ )
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".so");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("so");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#elif defined ( OPENBSD )    || defined ( __OPENBSD__ )
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".so");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("so");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#elif defined ( DARWIN )     || defined ( __APPLE__ )
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".dylib");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("dylib");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#elif defined(sun) || defined(__sun)
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".so");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("so");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#else
#warning("Cannot determine your os dynamic libraries extensions setted to default .so")
    static const wxString DYNAMIC_LIBRARY_FILE_EXT = wxT(".so");
    static const wxString DYNAMIC_LIBRARY_FILE_EXT_STANDARD = wxT("so");
    static const wxString DYNAMIC_LIBRARY_PREFIX = wxT("lib");
    static bool MANAGE_DYNAMIC_LIBRARY_PREFIX = true;
#endif
};

#endif
