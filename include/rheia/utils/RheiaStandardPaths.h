/**
*   @file RheiaStandardPaths.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	18-November-2009
*	@version 0.0.2
*/
#ifndef RheiaStandardPaths_h_
#define RheiaStandardPaths_h_

#include <RheiaUtilsSettings.h>
#include <RheiaGlobals.h>

/**
*   The RheiaStandardPaths is a global static class that allow the developper to find
*   some files in different standard dirs. This has been taken from the wxStandardPath object
*   in wxWidgets and we have added some information in order to help their definition.
*/
enum RheiaStandardPathsFlags
{
    rspfHome            					    = 0x0001, 								/*!< User's home directory          */
    rspfInstall            						= 0x0002, 								/*!< Rheia's installation directory */
    rspfTemp            						= 0x0004, 								/*!< General temp dir            */
    rspfPath            						= 0x0008, 								/*!< All dirs in the PATH environment variable  */
    rspfLddir            						= 0x000a, 								/*!< All dirs in the LD_LIBRARY_PATH environment variable   */
    rspfConfig          						= 0x000b, 								/*!< Standard application's confgiuration dir  */
    rspfAllBase          						= 0x000f, 								/*!< All dirs in the standard base  */
    rspfPluginsUser     			            = 0x0010, 								/*!< Plugins dir in user's dir   */
    rspfDataUser        				        = 0x0020, 								/*!< Data dir in user's dir      */
    rspfPackageUser                             = 0x0040,
    rspfCacheUser                               = 0x0080,
    rspfAllUser         					    = 0x00f0,								/*!< All users directories */
    rspfPluginsGlobal   			            = 0x0100, 								/*!< Plugins dir in rheia installation directory     */
    rspfDataGlobal      				        = 0x0200, 								/*!< Data dir in rheia installation directory        */
    rspfPackageGlobal                           = 0x0400,
    rspfCacheGlobal                             = 0x0800,
    rspfAllGlobal       					    = 0x0f00, 								/*!< All dirs in rheia installation directories */
    rspfAllKnown        					    = 0xffff, 								/*!< All dirs above           */
};

/**
*   @class RheiaStandardPaths
*
*   @brief This class is regroupping all standard paths that can be used in Rheia
*
*   wxStandardPaths object is providing any wxWidgets applications with system
*   specific paths known as standard paths. For use in Rheia we have managed different
*   additionnal paths for plugins and plugins data.
*   This class has been designed in order to provide Rheia developpers with an easy
*   interface an platform independent standard path.
*   By this way you can know at any time during execution where your files are located.
*
*   This class has no constrcutors, you do not need to build or free it as all of its
*   method are defined static.
*
*   A special case is for plugins. Any plugin can be located at two different places, in the
*   Rheia Global Plugins Directory, on unix like systems for examples they are located in
*   /usr/share/rheia/plugins, thus they will be installed for all users of a given machine or
*   they can be located in the user plugins path ~/.rheia/share/rheia/plugins, thus they will
*   only be available for the user who installed the plugin.
*
*   <p>
*   When the debug flag RHEIA_DEBUG or _DEBUG is defined by the PREPROCESSOR, Standard paths
*   changed, the configuration directory, the user data path and the plugin user path are fixed
*   to the global values. This allows you to test your new plugin configuration in a working
*   directory without altering the funtionment of an older one installed on your system.
*   </p>
*   <p>
*   The following standard paths are available via RheiaStandardPaths :
*   <ul>
*       <li> config_dir : the folder in which the configuration files shall be found </li>
*       <li> home_dir : the user's home folder </li>
*       <li> data_dir_user : the folder in which the users specific resource files shall be found </li>
*       <li> data_dir_global : the folder in which the applications resource files shall be found </li>
*       <li> plugin_dir_global : the folder in which the systems wide user's plugins are installed </li>
*       <li> plugin_dir_user : the folder in which the user's plugins are installed </li>
*       <li> package_dir_global : the folder in which the systems wide user's packages are installed </li>
*       <li> package_dir_user : the folder in which the user's packages are installed </li>
*       <li> app_dir : the parent folder in which the application is running </li>
*       <li> temp_dir : the temporary folder in which temporary files are stored </li>
*   </ul>
*   </p>
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	18-November-2009
*	@version 0.0.2
*/
class UTILS_DLLEXPORT RheiaStandardPaths
{
    /** Give RheiaApp our private members access */
    friend class RheiaApp;

    /** Give RheiaManager our private members access */
    friend class RheiaManager;

    /** Give RheiaConfigurationPathsDialog access to our private members */
    friend class RheiaConfigurationPathsDialog;

public :

    /**
    *   This metod is used at application startup in order to initialize
    *   all RheiaStandardPaths from this class. This class is not a manager
    *   it more lile a namespace in which you will find all dir relative
    *   to the application.
    */
    static void InitPaths();

    /*****************************************************************************************************
    *   ACCESSORS
    *****************************************************************************************************/
    /** Get the application directory */
    static const wxString& AppDirectory() {   return app_dir; };

    /** Get the global data directory */
    static const wxString& DataDirectoryGlobal() {   return data_dir_global; };

    /** Get the plugins global directory */
    static const wxString& PluginDirectoryGlobal() {   return plugin_dir_global; };

    /** Get the user plugins directory */
    static const wxString& PluginDirectoryUser() {   return plugin_dir_user; };

    /** Get the packages global directory */
    static const wxString& PackageDirectoryGlobal() {   return package_dir_global; };

    /** Get the user packages directory */
    static const wxString& PackageDirectoryUser() {   return package_dir_user; };

    /** Get the cache global directory */
    static const wxString& CacheDirectoryGlobal() {   return cache_dir_global; };

    /** Get the user cache directory */
    static const wxString& CacheDirectoryUser() {   return cache_dir_user; };

    /** Get the user data directory */
    static const wxString& DataDirectoryUser() {   return data_dir_user; };

    /** Get the user home directory */
    static const wxString& HomeDirectory() {   return home_dir; };

    /** Get the application configuration directory */
    static const wxString& ConfigDirectory() {   return config_dir; };

    /** Find a directory given its RheiaStandardPathsFlags flag */
    static wxString Directory(RheiaStandardPathsFlags flag);

    /** Get the plugins directory either global or user */
    static wxString PluginsDirectory(bool global = true) {   return Directory(global ? rspfPluginsGlobal : rspfPluginsUser); };

    /** Get the packages directory either global or user */
    static wxString PackageDirectory(bool global = true) {   return Directory(global ? rspfPackageGlobal : rspfPackageUser); };

    /** Get the cache directory either global or user */
    static wxString CacheDirectory(bool global = true) {   return Directory(global ? rspfCacheGlobal : rspfCacheUser); };

    /** Get the data directory either global or user */
    static const wxString& DataDirectory(bool global = true) {   return global ? data_dir_global : data_dir_user; };

    /** Get the application directory */
    static const wxString& ExecutableDirectory() {   return app_dir; };

    /**
    *   Get the system temp directory in order to allow you to store temporary files
    *   when the application is running.
    */
    static wxString GetTempDirectory() {   return Directory(rspfTemp); };


    /**
    *   Get the system temp directory in order to allow you to store temporary files
    *   when the application is running.
    */
    static const wxString& TempDirectory() {   return temp_dir; };

private :

    /*****************************************************************************************************
    *   PRIVATE MEMEBERS
    *****************************************************************************************************/
    static wxString config_dir;
    static wxString home_dir;
    static wxString data_dir_user;
    static wxString data_dir_global;
    static wxString plugin_dir_global;
    static wxString package_dir_global;
    static wxString cache_dir_global;
    static wxString plugin_dir_user;
    static wxString package_dir_user;
    static wxString cache_dir_user;
    static wxString app_dir;
    static wxString temp_dir;
};

namespace RheiaFileFinder
{
    /**
    *   @brief Platform Independent File Localizer.
    *
    *   You should always use this method if you need to locate a data file which is used in
    *   Rheia Framework. This method simply use the wxPathList object to locate your file in
    *   the given directories. You have to provide the full file name with extension in order
    *   to get its valid path.
    *
    *   @param filename name of the file to search for
    *   @param rspf A bit-mask of RheiaStandardPathFlags of directories to include in the search.
    *   @return A wxEmptyString if the file has not been found
    */
    extern wxString UTILS_DLLEXPORT FindFile(const wxString& filename, int rspf = rspfAllKnown);
};

#endif
