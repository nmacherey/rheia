/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPluginManager.cpp
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 25-November-2009
*       Changes : Commentaries and addaptation accordingly to the RheiaPackageManager
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaPluginManager.h>
#include <RheiaPlugin.h>
#include <RheiaEvents.h>
#include <RheiaGlobals.h>
#include <RheiaAppGlobals.h>
#include <RheiaException.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEnvironementManager.h>
#include <RheiaConfigurationPanel.h>
#include <RheiaPlatform.h>
#include <RheiaInfoWindow.h>
#include <RheiaPackageManager.h>
#include <RheiaPackageDBManager.h>
#include <RheiaPackageManagedFile.h>
#include <RheiaPackageManagedFiles.h>
#include <RheiaPluginManifest.h>
#include <RheiaPackageVersion.h>
#include <RheiaLibLoader.h>
#include <RheiaLoggerManager.h>
#include <RheiaLogger.h>
#include <RheiaEventsManager.h>
#include <RheiaEventPlugin.h>

#include "sdkversion.h"

#include <map>
#include <iostream>
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
#include <wx/filefn.h>

/*! Global instance for the plugin manager */
template<> RheiaPluginManager* Singleton<RheiaPluginManager>::instance = 0;
template<> bool  Singleton<RheiaPluginManager>::isShutdown = false;

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaFramePluginManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaWorkspaceManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaFramePluginManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaFramePluginManager>::m_ns = locmap;

namespace {
	class PluginCleaner : public RheiaComponentCleaner
	{
	public :
		virtual void DoCleanUp(){
			RheiaPluginManager::Free();
			RheiaFramePluginManager::Free();
			RheiaPackageDBManager::Free();
			RheiaPackageManager::Free();
			RheiaLibLoader::Free();
		}
	};
	
	REGISTER_COMPONENT_CLEANER(PluginCleaner);
}

BEGIN_EVENT_TABLE(RheiaPluginManager, wxEvtHandler)
    //
END_EVENT_TABLE()

// class constructor
RheiaPluginManager::RheiaPluginManager()
{
}

// class destructor
RheiaPluginManager::~RheiaPluginManager()
{
    UnloadAllPlugins();
}

void RheiaPluginManager::CreateMenu(wxMenuBar* WXUNUSED(menuBar))
{

}

void RheiaPluginManager::ReleaseMenu(wxMenuBar* WXUNUSED(menuBar))
{

}

bool RheiaPluginManager::AttachPlugin(RheiaPlugin* plugin)
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Attaching plugin...") , RheiaLogging::info );

    if (!plugin)
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Plugin refered to NULL...") , RheiaLogging::warning );
        return false;
    }

    if (plugin->IsPlugged())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Your plugin has already been attached...") , RheiaLogging::info );
        return true;
    }

    plugin->Plug();
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Your plugin has been attached sucessfully...") , RheiaLogging::success );

    return true;
}

bool RheiaPluginManager::DetachPlugin(RheiaPlugin* plugin)
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Detaching plugin...") , RheiaLogging::info );

    if (!plugin)
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Plugin refered to NULL...") , RheiaLogging::warning );
        return false;
    }
    if (!plugin->IsPlugged())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Your plugin is not attached...") , RheiaLogging::info );
        return true;
    }

    if( !RheiaManager::IsAppShuttingDown() )
    {
		RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Removing related projects for plugin ...") , RheiaLogging::info );
		RheiaPluginEvent event( RheiaEVT_ENVPLUGIN_REQUEST_DETACH , 0 , plugin );
		RheiaEventsManager::Get()->ProcessEvent(event);

        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Removing event functions for plugin ...") , RheiaLogging::info );
        RheiaEventsManager::Get()->RemoveAllEventMethodsFor(plugin);
    }

    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Releasing our plugin ...") , RheiaLogging::info );
    plugin->Unplug(RheiaManager::IsAppShuttingDown());

    return true;
}

bool RheiaPluginManager::RegisterPlugin(const wxString& name,
                                        CreatePluginProcess createProc,
                                        FreePluginProcess freeProc )
{
    // sanity checks
    if ( name.IsEmpty() || !createProc || !freeProc )
	{
		RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::RegisterPlugin wrong plugin : ") + name + wxT(" ...") , RheiaLogging::error );
		return false;
	}

    // first check to see it's not already loaded
    if (FindElement(name))
	{
		RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::RegisterPlugin plugin exists : ") + name + wxT(" ...") , RheiaLogging::error );
		return false;
	}

    // read manifest file for plugin

    wxString resName = name;

    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && resName.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        resName = resName.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

    wxString libName = name;
    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && !libName.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        libName = FileExt::DYNAMIC_LIBRARY_PREFIX + libName + FileExt::PLUGIN_EXT;

    RheiaPluginManifest* manifest = ReadManifestFile( resName + wxT("_res") );
    if ( manifest == NULL )
    {
        wxMessageBox(wxT("Error reading manifest for ") + name,_("Error"));
        return false;
    }

    // now perform the SDK version number (extra check)
    RheiaPackageVersion* sdkversion = manifest->GetSDKVersion();
    long major = sdkversion->GetMajor();
    long minor = sdkversion->GetMinor();
    //long build = sdkversion->GetBuild();

    long dmajor = AutoVersion::MAJOR;
    long dminor = AutoVersion::MINOR;

    if( CompareVersions( dmajor , dminor , major , minor ) < 0 ) //package is made for a newer version than the current one
    {
		RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::RegisterPlugin version problem : ") + name + wxT(" ...") , RheiaLogging::error );
        delete manifest;
        return false;
    }

    // all done
    // register this plugin in the map so that the plugin can be attached later
    RheiaPluginRegistration registration;
    registration.name = name;
    registration.createProcess = createProc;
    registration.freeProcess = freeProc;
    registration.info = manifest;

    RegisteredPlugins.push_back(registration);
    return true;
}

RheiaPluginManifest* RheiaPluginManager::ReadManifestFile(
        const wxString& pluginFilename )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Reading plugin manifest file : ") + pluginFilename + wxT(" ...") , RheiaLogging::info );

    wxString pluginFname = pluginFilename;

    // first check if the plugin can be found
    if (pluginFname.IsEmpty())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Plugin manifest file : ") + pluginFilename + wxT(" is empty...") , RheiaLogging::error );
        return NULL;
    }

    wxFileName fname(pluginFilename);
    fname.SetExt(wxT("zip"));
    wxString actual = fname.GetFullName();

    // remove dynamic library prefix from plugin name (if any)
    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && actual.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX))
        actual.Remove(0, FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

    actual = RheiaFileFinder::FindFile( actual, rspfPluginsUser | rspfDataUser | rspfPluginsGlobal | rspfDataGlobal );

    // check if the plugin resource exists
    if (actual.IsEmpty())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Plugin manifest file : ") + pluginFilename + wxT(" not found...") , RheiaLogging::error );
        return false;
    }

    // load XML from ZIP
    wxString contents;
    wxFileSystem* fs = new wxFileSystem;
    wxFSFile* f = fs->OpenFile(actual + _T("#zip:manifest.xml") );

    if (f)
    {
        wxInputStream* is = f->GetStream();
        char tmp[1024] = {};
        while (!is->Eof() && is->CanRead())
        {
            memset(tmp, 0, sizeof(tmp));
            is->Read(tmp, sizeof(tmp) - 1);
            contents <<  RheiaC2U(tmp);
        }
        delete f;
    }
    else
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Cannot extract plugin manifest file : ") + actual + wxT("#zip:manifest.xml...") , RheiaLogging::error );
        delete fs;
        return false;
    }
    delete fs;

    xmlDoc* doc = xmlParseMemory( rcU2C(contents) , contents.size() );

    if (!doc)
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Cannot load xml document from memory : ") + actual + wxT("#zip:manifest.xml...") , RheiaLogging::error );
        return NULL;
    }

    xmlNode* root = xmlDocGetRootElement( doc );
    wxString rname = RheiaC2U( (const char*) root->name );

    if( !rname.IsSameAs( wxT("RheiaPluginManifest") ) )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Root node for xml document : ") + actual + wxT("#zip:manifest.xml is not RheiaPluginManifest...") + rname , RheiaLogging::error );
        xmlFreeDoc( doc );
        return NULL;
    }

    RheiaPluginManifest* manifest = new RheiaPluginManifest;

    xmlNode* child = root->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs(wxT("Plugin")) )
        {
            if( !manifest->DoReadFromNode(child) )
            {
                RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Problem reading the xml document content from memory (manifest->DoReadFromNode(root) returns false) : ") + actual + wxT("#zip:manifest.xml is not RheiaPluginManifest...") , RheiaLogging::error );
                delete manifest;
                xmlFreeDoc( doc );
                return NULL;
            }
            break;
        }

        child = child->next;
    }

    xmlFreeDoc( doc );
    return manifest;
}

bool RheiaPluginManager::LoadPlugin( const wxString& pluginName )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Loading plugin : ") + pluginName + wxT(" ...") , RheiaLogging::info );

    // firt load the library...
    RheiaDynamicLibrary* plugin = RheiaLibLoader::Get()->LoadLibrary(pluginName);
    if ( plugin == NULL || !plugin->lib->IsLoaded())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Cannot load plugin : ") + pluginName + wxT(" ...") , RheiaLogging::error );
        RheiaLibLoader::Get()->RemoveLibrary(plugin->lib);

        return false;
    }

    wxString filename = wxFileName( pluginName ).GetName();

    wxString version;
    if (filename.Contains(wxT('-')))
    {
        version = filename.AfterFirst(wxT('-'));
        filename = filename.BeforeFirst(wxT('-'));
    }

    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

//    // by now, the library has loaded and its global variables are initialized.
//    // this means it has already called RegisterPlugin()
//    // now we can actually create the plugin(s) instance(s) :)
//    // try to load the plugin(s)
//    std::vector<RheiaPluginRegistration>::iterator it;
//    for (it = RegisteredPlugins.begin(); it != RegisteredPlugins.end(); it++)
//    {
//        RheiaPluginRegistration& registrant = *it;
//
//        if( registrant.name.IsSameAs( filename ) )
//        {
//            if( registrant.plugin == NULL )
//                registrant.plugin = registrant.createProcess();
//
//            registrant.dylib = plugin;
//
//            break;
//        }
//    }

    if (RegisteredPlugins.empty())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Plugin : ") + pluginName + wxT(" seams to be not loaded...") , RheiaLogging::warning );
        // no plugins loaded from this library, but it's not an error
        RheiaLibLoader::Get()->RemoveLibrary(plugin->lib);
    }
    return true;
}

bool RheiaPluginManager::LoadLibrary(const wxString& fileName )
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Loading Library : ") + fileName + wxT(" ...") , RheiaLogging::info );

    // firt load the library...
    RheiaDynamicLibrary* plugin = RheiaLibLoader::Get()->LoadLibrary(fileName);
    if ( plugin == NULL || !plugin->lib->IsLoaded())
    {
        RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Cannot load library : ") + fileName + wxT(" ...") , RheiaLogging::error );
        RheiaLibLoader::Get()->RemoveLibrary(plugin->lib);

        return false;
    }

    return true;
}

void RheiaPluginManager::LoadAllPlugins()
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Loading all registered plugins in RheiaPackageDBManager ...") , RheiaLogging::info );

    // check if a plugin crashed the app last time
    wxArrayString failedPlugins = RheiaManager::Get()->GetConfigurationManager(_T("plugins"))->ReadArrayString(_T("/last_activation_try"));
    wxArrayString tryActivation;

    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Checking for last activation failed plugins ...") , RheiaLogging::info );

    if ( failedPlugins.GetCount() > 0 )
    {
        wxString msg = wxT("Plugins :\n\n");

        for( int i = 0; i < (int) failedPlugins.GetCount() ; ++i )
        {
            msg += failedPlugins[i] + wxT("\n");
        }

        msg += wxT("failed to load last time Rheia was executed.\nDo you want to disable this plugin from loading?");

        int retCode = wxMessageBox( msg , wxT("Warning") , wxYES_NO );

        if (retCode == wxID_NO)
            failedPlugins.Clear();
    }

    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Receiving plugin list from RheiaPackageDBManager ...") , RheiaLogging::info );
    RheiaPackageMangedFileArray plugins = RheiaPackageDBManager::Get()->GetLoadingList();
    RheiaPackageMangedFileArray::iterator pit = plugins.begin();

    for( ; pit != plugins.end() ; ++pit )
    {
        wxString filepath = (*pit)->GetPath();
        wxString filename = (*pit)->GetName();

        wxFileName fname(filepath);
        wxString nfname = fname.GetName() + wxT(".") + fname.GetExt();
        filepath = RheiaFileFinder::FindFile( nfname );

        if( filepath.IsEmpty() )
        {
            RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Cannot find your file : ") + nfname + wxT(" ...") , RheiaLogging::info );
            continue;
        }

        wxString version;
        if (filename.Contains(wxT('-')))
        {
            version = filename.AfterFirst(wxT('-'));
            filename = filename.BeforeFirst(wxT('-'));
        }

        if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
            filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

        wxString type = (*pit)->GetType();

        if( type.IsSameAs(wxT("lib")) )
        {
            RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Loading library : ") + filename + wxT(" ...") , RheiaLogging::info );
            bool loaded = LoadLibrary( filepath );

            if( !loaded )
            {
                wxString msg;
                msg.Printf(_("Library \"%s\" failed to load...\n"
                            "Do you want to disable this library from loading next time?"), filename.c_str());

                int retCode = wxMessageBox( msg , wxT("Warning") , wxICON_QUESTION|wxYES_NO );

                if (retCode == wxID_YES)
                    tryActivation.Add( filename );

                continue;
            }
        }
        else
        {
            RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Receiving plugin information for : ") + filename + wxT(" ...") , RheiaLogging::info );
            RheiaPluginRegistration* registrant = FindElement( filename );

            if( registrant != NULL && registrant->plugin != NULL && registrant->plugin->IsPlugged() )
            {
                RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Plugin already attached : ") + filename + wxT(" , continuing happily...") , RheiaLogging::warning );
                continue;
            }

            bool loaded = LoadPlugin( filepath );

            wxString baseKey;
            baseKey << _T("/") << filename;
            bool loadPlugin = RheiaManager::Get()->GetConfigurationManager(_T("plugins"))->ReadBool(baseKey, true);

            int index = failedPlugins.Index( filename );
            if (loadPlugin && index != wxNOT_FOUND)
            {
                RheiaManager::Get()->GetConfigurationManager(_T("plugins"))->Write(baseKey, false);
                loadPlugin = false;
            }

            if( !loaded )
            {
                wxString msg;
                msg.Printf(_("Plugin \"%s\" failed to load...\n"
                            "Do you want to disable this plugin from loading next time?"), filename.c_str());

                int retCode = wxMessageBox( msg , wxT("Warning") , wxICON_QUESTION|wxYES_NO );

                if (retCode == wxID_YES)
                    tryActivation.Add( filename );

                continue;
            }

            if( loadPlugin )
            {
                RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Loading plugin : ") + filename + wxT(" ...") , RheiaLogging::info );
                registrant = FindElement( filename );

                if( registrant == NULL )
                {
                    wxString msg;
                    msg.Printf(_("Plugin \"%s\" failed to load...\n"
                                "Do you want to disable this plugin from loading next time?"), filename.c_str());

                    int retCode = wxMessageBox( msg , wxT("Warning") , wxICON_QUESTION|wxYES_NO );

                    if (retCode == wxID_YES)
                        tryActivation.Add( filename );

                    continue;
                }

                /*if( !registrant->plugin->IsPlugged() )
                    registrant->plugin->Plug();*/
            }
        }
    }

    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Installed plugins loaded ..."), RheiaLogging::success );
    RheiaManager::Get()->GetConfigurationManager(_T("plugins"))->Write(_T("/last_activation_try"), tryActivation );
}

void RheiaPluginManager::UnloadAllPlugins()
{
    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Unloading all registered plugins in RheiaPackageDBManager ...") , RheiaLogging::info );

    RheiaPluginRegistrationTable::iterator it = RegisteredPlugins.begin();
	
	for( ; it != RegisteredPlugins.end() ; ++it )
    {
		RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Remove plugin library : ") + (*it).name + wxT("...") , RheiaLogging::info );
		if( it->dylib )
			RheiaLibLoader::Get()->RemoveLibrary( it->dylib );
			
		if( it->info )
			delete it->info;

		RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Unregistering plugin : ") + (*it).name + wxT("...") , RheiaLogging::info );
    }

    RheiaLoggerManager::sdLog( wxT("RheiaPluginManager::Cleaning memory ...") , RheiaLogging::info );
    RegisteredPlugins.clear();
    RheiaLibLoader::Get()->Cleanup();
}

RheiaFramePluginManager::RheiaFramePluginManager(RheiaManagedFrame* parent):
	m_parent(parent)
{
	m_parent->PushEventHandler(this);

	RheiaFrameEventsManager::Get(m_parent)->RegisterEventMethod(RheiaEVT_FRAME_CLOSING,
		new RheiaEventFunctor<RheiaFramePluginManager>(this, RheiaFrameEventHandler(RheiaFramePluginManager::OnCloseParent)));
}

RheiaFramePluginManager::~RheiaFramePluginManager()
{
}

bool RheiaFramePluginManager::LoadPlugin(const wxString& name)
{
	wxString filename = name;
    wxString version;
    if (filename.Contains(wxT('-')))
    {
        version = filename.AfterFirst(wxT('-'));
        filename = filename.BeforeFirst(wxT('-'));
    }
	
	if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());
		
	RheiaPluginRegistration* info = RheiaPluginManager::Get()->FindElement(name);
	if( info == NULL )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaFramePluginManager::LoadPlugin ") + name + wxT(" info not found ...") , RheiaLogging::warning );
		return false;
    }
		
	RheiaPluginMap::iterator it = m_plugins.find(filename);
	if( it != m_plugins.end() ) // here return true because the plugin is already loaded
	{
        RheiaLoggerManager::sdLog( wxT("RheiaFramePluginManager::LoadPlugin ") + name + wxT(" plugin already in frame ...") , RheiaLogging::warning );
		return true;
    }
	
    RheiaPlugin* plugin = info->createProcess(m_parent);
    RheiaPluginManager::Get()->AttachPlugin(plugin);
	m_plugins[filename] = plugin;
    RheiaLoggerManager::sdLog( wxT("RheiaFramePluginManager::LoadPlugin ") + name + wxT(" plugin attached to frame ...") , RheiaLogging::warning );
	return true;
}

bool RheiaFramePluginManager::UnloadPlugin( const wxString& name )
{
	wxString filename = name;
    wxString version;
    if (filename.Contains(wxT('-')))
    {
        version = filename.AfterFirst(wxT('-'));
        filename = filename.BeforeFirst(wxT('-'));
    }
	
	if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());
		
	RheiaPluginRegistration* info = RheiaPluginManager::Get()->FindElement(name);
	if( info == NULL )
    {
        RheiaLoggerManager::sdLog( wxT("RheiaFramePluginManager::UnloadingPlugin ") + name + wxT(" info not found ...") , RheiaLogging::warning );
		return false;
    }
		
	RheiaPluginMap::iterator it = m_plugins.find(filename);
	if( it == m_plugins.end() ) // here return true because the plugin is already loaded
    {
        RheiaLoggerManager::sdLog( wxT("RheiaFramePluginManager::UnloadingPlugin ") + name + wxT(" plugin not attached to the frame ...") , RheiaLogging::warning );
		return false;
    }
		
	RheiaPluginManager::Get()->DetachPlugin(it->second);
	delete it->second;
	m_plugins.erase(it);
    
    RheiaLoggerManager::sdLog( wxT("RheiaFramePluginManager::UnloadingPlugin ") + name + wxT(" unloaded ...") , RheiaLogging::info );
	
    return true;
}

void RheiaFramePluginManager::LoadAllPlugins()
{
	RheiaPluginRegistrationTable& RegisteredPlugins = RheiaPluginManager::Get()->RegisteredPlugins;

    RheiaPluginRegistrationTable::iterator it = RegisteredPlugins.begin();
    for( ; it != RegisteredPlugins.end() ; ++it )
        LoadPlugin((*it).name);
}

void RheiaFramePluginManager::UnloadAllPlugins()
{
	RheiaPluginMap::iterator it = m_plugins.begin();
	
	for( ; it != m_plugins.end() ; ++it )
	{
		RheiaPluginManager::Get()->DetachPlugin(it->second);
		delete it->second;
	}
	
	m_plugins.clear();
}

RheiaPlugin* RheiaFramePluginManager::FindPlugin(const wxString& pluginName)
{
    wxString filename = pluginName;
    wxString version;
    if (filename.Contains(wxT('-')))
    {
        version = filename.AfterFirst(wxT('-'));
        filename = filename.BeforeFirst(wxT('-'));
    }

    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

    RheiaPluginMap::iterator it = m_plugins.find(filename);
    if( it != m_plugins.end() )
		return it->second;

    return 0;
}

void RheiaFramePluginManager::NotifyPlugins(RheiaEvent& event)
{
    RheiaEventsManager::Get()->ProcessEvent(event);
}

RheiaPluginsArray RheiaFramePluginManager::GetOffersFor( RheiaPluginType type )
{
    RheiaPluginsArray ret;

    RheiaPluginMap::iterator it = m_plugins.begin();
    for( ; it != m_plugins.end() ; ++it )
    {
        RheiaPlugin* plugin = it->second;
        if (plugin && plugin->IsPlugged() && plugin->GetType() == type)
            ret.Add( plugin );
    }

    return ret;

}

RheiaPluginRegistration* RheiaFramePluginManager::FindElement(const wxString& pluginName)
{
    wxString filename = pluginName;
    wxString version;
    if (filename.Contains(wxT('-')))
    {
        version = filename.AfterFirst(wxT('-'));
        filename = filename.BeforeFirst(wxT('-'));
    }

    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());
		
	RheiaPluginRegistrationTable& RegisteredPlugins = RheiaPluginManager::Get()->RegisteredPlugins;

    RheiaPluginRegistrationTable::iterator it = RegisteredPlugins.begin();
    for( ; it != RegisteredPlugins.end() ; ++it )
    {
        if ((*it).name == filename)
            return &(*it);
    }

    return NULL;
}

RheiaPluginRegistration* RheiaPluginManager::FindElement(const wxString& pluginName)
{
    wxString filename = pluginName;
    wxString version;
    if (filename.Contains(wxT('-')))
    {
        version = filename.AfterFirst(wxT('-'));
        filename = filename.BeforeFirst(wxT('-'));
    }

    if ( !FileExt::DYNAMIC_LIBRARY_PREFIX.IsEmpty() && !platform::windows && filename.StartsWith(FileExt::DYNAMIC_LIBRARY_PREFIX) )
        filename = filename.Remove(0,FileExt::DYNAMIC_LIBRARY_PREFIX.Length());

    RheiaPluginRegistrationTable::iterator it = RegisteredPlugins.begin();
    for( ; it != RegisteredPlugins.end() ; ++it )
    {
        if ((*it).name == filename)
            return &(*it);
    }

    return NULL;
}
 
RheiaPluginRegistration* RheiaFramePluginManager::FindElement(RheiaPlugin* plugin)
{
	RheiaPluginRegistrationTable& RegisteredPlugins = RheiaPluginManager::Get()->RegisteredPlugins;
	
	RheiaPluginMap::iterator pit = m_plugins.begin();
	wxString name;
	
	for( ; pit != m_plugins.end() ; pit++ )
	{
		if( pit->second == plugin )
		{
			name = pit->first;
			break;
		}
	}
	
	if( name.IsEmpty() )
		return NULL;
	
    RheiaPluginRegistrationTable::iterator it = RegisteredPlugins.begin();
    for( ; it != RegisteredPlugins.end() ; ++it )
    {
        if ((*it).name == name)
            return &(*it);
    }

    return NULL;
}

void RheiaFramePluginManager::OnCloseParent( RheiaFrameEvent& event )
{
	m_parent->RemoveEventHandler(this);
	UnloadAllPlugins();
    event.Skip();
}