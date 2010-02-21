#include <RheiaProfileManager.h>
#include <RheiaEvents.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaEventsManager.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#include <wx/url.h>
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

#include <iostream>

template<> RheiaProfileManager* Mgr<RheiaProfileManager>::instance = 0;
template<> bool  Mgr<RheiaProfileManager>::isShutdown = false;

/*
*			Default constructor for RheiaProfileManager. This method is private, because
*			Only the Mrg and the Manager class can build a ProfileManager
*/
RheiaProfileManager::RheiaProfileManager()
{
    ActiveProfile = wxT("default");
    ProfileConfMgr = RheiaManager::Get()->GetConfigurationManager( wxT("Profiles") );
    ActiveProfile = RheiaManager::Get()->GetConfigurationManager( wxT("LastLoad") )->Read( wxT("/personality/profile" ) , ActiveProfile );
    ChangeActiveProfile( ActiveProfile );
}
RheiaProfileManager::~RheiaProfileManager()
{
	 /* first save the active profile in the corresponding node in the configuration file */
	 RheiaManager::Get()->GetConfigurationManager( wxT("LastLoad") )->Write( wxT("/personality/profile" ) , ActiveProfile );

	 /* Now free ou namspaces */
    RheiaConfigurationManagerMap::iterator it;
    for ( it = Profiles.begin(); it != Profiles.end(); ++it )
    {
        delete it->second;
    }
    Profiles.clear();
}
/*
*		Set the current active user profile string for reading in the configuration file
*/
void RheiaProfileManager::ChangeActiveProfile( const wxString& profile )
{
	 /**
	 *		@note this function creates the profile if not existant
	 *		and saves the current configuration in it
	 */
    ActiveProfile = profile;

    xmlNode* ret = ProfileConfMgr->GetRootChildren( wxT("profile") , wxT("name") , profile );
    xmlDoc* doc = ProfileConfMgr->GetDocument();

    RheiaConfigurationManagerMap::iterator it = Profiles.find(profile);
    if (it != Profiles.end())
    {
			ActiveProfileConfMgr = it->second;
    }else{
			ActiveProfileConfMgr = new RheiaConfigurationManager( doc , ret );
			Profiles[ profile ] = ActiveProfileConfMgr;
    }
    RheiaEvent event(RheiaEVT_PROFILE_CHANGED);
    RheiaEventsManager::Get()->ProcessEvent( event );
}

/*
*		Get All Available profiles
*/
wxArrayString RheiaProfileManager::GetAvailableProfiles( )
{
    wxArrayString ret = ProfileConfMgr->ListRootChildrenNames( wxT("profile") , wxT("name") );
    return ret;
}


/*
*		Returns the Configuration Manager associated to the given profile without
*   making it active
*/
RheiaConfigurationManager* RheiaProfileManager::GetProfileManager( const wxString& profile )
{

    xmlNode* ret = ProfileConfMgr->GetRootChildren( wxT("profile") , wxT("name") , profile );
    xmlDoc* doc = ProfileConfMgr->GetDocument();

    RheiaConfigurationManager* ReturnedProfile;

    RheiaConfigurationManagerMap::iterator it = Profiles.find(profile);
    if (it != Profiles.end())
    {
			ReturnedProfile = it->second;
    }else{
			ReturnedProfile = new RheiaConfigurationManager( doc , ret );
			Profiles[ profile ] = ReturnedProfile;
    }

    return ReturnedProfile;
}
