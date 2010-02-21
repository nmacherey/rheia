#ifndef RheiaProfileManager_h_
#define RheiaProfileManager_h_

#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>

#include <RheiaManager.h>
#include <RheiaConfigurationPattern.h>

#include <vector>
#include <map>

#include <wx/event.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/string.h>
#include <wx/dynlib.h>

/**
*		@class RheiaProfileManager
*
*		@brief RheiaProfileManager is the manager class for profiles.
*
*		A user can define different profiles in which he has specific configuration information.
*		Hence each profile is a full configuration node in the configuration xml
*		In rheia a default profile is defined, in which can be found the default layout information
*		that can be used by the user.
*		The profile does not contain all the configuration information, mainly it contains the info
*		that can be specified by the user in Rheia such as frame information, layout manager's informations
*		themes for toolbars and menus.
*
*		@author Nicolas MACHEREY (nm@graymat.fr)
*		@date 27-Jan-2009
*/
class BASE_DLLEXPORT RheiaProfileManager : public wxEvtHandler, public Mgr<RheiaProfileManager>
{
		/*! Give our private members access to Mrg */
		friend class Mgr< RheiaProfileManager >;
		/*! Give our private members access to RheiaManager */
		friend class RheiaManager;

public :
		/**
		*		Get the current active user profile string for reading in the configuration file
		*/
		wxString& GetActiveProfile() { return ActiveProfile;};

		/**
		*		Get the current active user profile string for reading in the configuration file
		*/
		RheiaConfigurationManager* GetActiveProfileManager() { return ActiveProfileConfMgr;};

		/**
		*		Returns the Configuration Manager associated to the given profile without
		*   making it active
		*/
		RheiaConfigurationManager* GetProfileManager( const wxString& profile );

		/**
		*		Set the current active user profile string for reading in the configuration file
		*/
		void ChangeActiveProfile( const wxString& profile );

		/**
		*		Get All Available profiles
		*/
		wxArrayString GetAvailableProfiles( );

private :
		/**
		*			Default constructor for RheiaProfileManager. This method is private, because
		*			Only the Mrg and the Manager class can build a ProfileManager
		*/
		RheiaProfileManager();

		/**
		*			Default constructor for RheiaProfileManager. This method is private, because
		*			Only the Mrg and the Manager class can build a ProfileManager
		*/
		~RheiaProfileManager();

private :
		/*--------------------------------------------------------------------------------------------------------------------------------------
		* PRIVATE VARIABLES
		---------------------------------------------------------------------------------------------------------------------------------------*/
		wxString ActiveProfile;
		RheiaConfigurationManager *ProfileConfMgr;
		RheiaConfigurationManager *ActiveProfileConfMgr;

		RheiaConfigurationManagerMap Profiles;
};

#endif
