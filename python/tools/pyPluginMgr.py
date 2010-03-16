""" @file pyPluginMgr.py
@author Nicolas Macherey (nm@graymat.fr)
@version 1.0.1
@date 16-March-2009
@brief This is the main file for managing Python plugins in Rheia

You shall register all python plugins for Rheia usgin this class
"""

import wx
import rheia.packagemgt

## define alias so it will be simpler to call rheia.packagemanagement
rheia = rheia.packagemgt

""" Global variable for plugins """
s_plugins = {}

class RheiaPythonPluginManager:
    """ @class RheiaPythonPluginManager
            @brief this is the main class you shall use to register your python plugins with Rheia
            @author Nicolas Macherey (nm@graymat.fr)
            @version 1.0.1
            @date 16-March-2009
            """
    def __init__(self):
        """Constructor"""
        s_plugins={}
        return 
        
    def __del__(self):
        """destructor will destroy all plugins in the globals s_plugin variable"""
        for i in s_plugins.keys():
            del s_plugins[i]
        return
        
    def RegisterPlugin( self , name , plugin ):
        """ Register a plugin in the manager 
                    All plugins must inherit from RheiaPlugin
                    name : Plugin name for registration
                    plugin : Plugin instance
              """
        s_plugins[name] = plugin
        return
        
    def GetPlugin( self , name ):
        """ This function will return the plugin instance associated to the given plugin name
                    so RheiaPythonUtils in C++ will be able to get the plugin instance back as a 
                    RheiaPlugin and use it in the application.
                    
                    note: that your plugin shall have been registered first via RegisterPlugin
                    
                    name : plugin name 
                    """
        try:
            plugin = s_plugins[name]
        except KeyError:
            return None
    
        return s_plugins[name]
        
    def RemovePlugin(self,name):
        """ This function will remove the plugin from the global plugins array
                    It will be used when removing a python plugin from the application
                    
                    note: that your plugin shall have been registered first via RegisterPlugin
                    if the plugin is not found this method will simply return to the application
                    
                    name : plugin name to remove
                    """
        try:
            plugin = s_plugins[name]
        except KeyError:
            return
        
        del s_plugins[name]
        return
        
    def GetPluginsCount(self):
        """ return the total number of registered plugins in the global s_plugins dict"""
        return len(s_plugins)
        
    def GetPluginNameAt(self,index):
        """return the name of the plugin at the given index"""
        k = s_plugins.keys()
        return k[index]
        
    def GetPluginAt(self,index):
        """return the name of the plugin at the given index"""
        k = s_plugins.keys()
        return s_plugins[k[index]]
    
    def GetPluginNames( self ):
        """ Get a list of all plugin names """
        return s_plugins.keys()
    