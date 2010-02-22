/**
*   @file RheiaWizardManager.h
*
*   @brief This is the main header file for the RheiaWizardManager
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-May-2009
*   @version 0.0.1
*/

#ifndef RheiaWizardManager_h_
#define RheiaWizardManager_h_

#include "RheiaGlobals.h"
#include "RheiaWMgtSettings.h"
#include "RheiaManager.h"
#include "RheiaManagedFrame.h"

#include <wx/wizard.h>

/* imports */
class RheiaProjectCreationWizard;
class RheiaProject;
class RheiaWorkspace;
class RheiaEnvironmentPlugin;

/************************************************************************************************
*   Defines for project wizards
************************************************************************************************/

/** define a project wizard constructor function */
typedef RheiaProjectCreationWizard*(*WizardConstructor)( wxWizard* , RheiaManagedFrame*, RheiaWorkspace* );

/** define a project wizard destructor function */
typedef void(*WizardDestructor)( RheiaProjectCreationWizard * );

/**
*   @struct RheiaProjectWizardRegistration
*
*   @brief This structure is used to store the informations about the creation of a project wizard
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
struct RheiaProjectWizardRegistration
{
    RheiaProjectWizardRegistration():ctor(0),dtor(0){};
    RheiaProjectWizardRegistration(const RheiaProjectWizardRegistration& rhs):
        name(rhs.name),
        category(rhs.category),
        bitmapBasename(rhs.bitmapBasename),
        ctor(rhs.ctor),
        dtor(rhs.dtor){};

    wxString name;
    wxString category;
    wxString bitmapBasename;
    WizardConstructor ctor;
    WizardDestructor dtor;
};

/** define a map of RheiaProjectRegistration for storing it in the factory */
typedef std::map< wxString , RheiaProjectWizardRegistration > RheiaProjectWizardRegistrationMap;

/**
*   @class RheiaWizardManager
*
*   @brief This is the main class for managing wizards in rheia
*
*   A wizard is a chain of actions defined to provide the user with different step
*   for creating/configuring projects/workspaces/tools in Rheia.
*   Any integrated environment in rheia shall provide with RheiaProjectCreationWizards in order
*   to create a project for example.
*   The RheiaWizardManager is the singleton class that manages the wizard at run-time. You do not have
*   to register your wizard in it as it shall be given by a RheiaEnvironementPlugin.
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-May-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaWizardManager : public wxEvtHandler, public RheiaMgr< RheiaManagedFrame, RheiaWizardManager >
{
    /** give Mgr our private members access */
    friend class RheiaMgr< RheiaManagedFrame, RheiaWizardManager >;
    /** give RheiaManager our private members access */
    friend class RheiaManager;
public :

    /**
    *   Method used to create a new project
    *   @param workspace the workspace in which the project shall be created
    */
    bool DoCreateNewProject( RheiaWorkspace* workspace );

    /******************************************************************************************
    *   Wizards related functions
    ******************************************************************************************/

    /**
    *   Method used for registering a project wizard in the wizard manager
    *
    *   @param name name or title for the project wizard
    *   @param category the wizard associated category
    *   @param ctor Pointer to the wizard constructor function
    *   @param dtor pointer to the wizard destructor function
    *
    *   @return true if the project wizard was properly registered in the factory
    */
    static bool RegisterProjectWizard( const wxString& name ,
                                const wxString& category,
                                const wxString& bitmapBasename,
                                WizardConstructor ctor,
                                WizardDestructor dtor );
								
	static bool UnregisterProjectWizard( const wxString& name );

    /**
    *   Get the available project wizards. This function
    *   return a wxArrayString.
    */
    static wxArrayString GetWizardList( );

    /**
    *   Get the available project wizards. This function
    *   return a wxArrayString.
    */
    static wxArrayString GetCategoryList( );

    /**
    *   Get the available project wizards. This function
    *   return a wxArrayString.
    */
    static wxArrayString GetWizardListFor( const wxString& category );

    /**
    *   Create a project wizard by finding the proper element in the map, and
    *   using the given parameters in construction.
    *
    *   @param type type or name of the project wizard to be created
    *   @param wizard the parent wizard for the project creation wizard
    *   @param workspace the workspace in which the project created by the wizard shall be attached
    *
    *   @return NULL if the project was no created properly and the created project else
    */
    static RheiaProjectCreationWizard* CreateWizard( const wxString& type,
                                wxWizard* wizard,
                                RheiaManagedFrame* parent,
                                RheiaWorkspace* workspace );

    /**
    *   Find a wizard registration structure given the wizard name
    *
    *   @param name the wizard's name to find
    *   @return an empty structure if the wizard was not found
    */
    static RheiaProjectWizardRegistration FindProjectWizardByName( const wxString& name );


    /** Get the registered wizards */
    static RheiaProjectWizardRegistrationMap& GetRegisteredWizards() {return m_RegisteredWizards;};
private :
    /**
    *   Default constructor,
    *   you cannot use this one use RheiaWizardManager::Get() instead;
    */
    RheiaWizardManager(RheiaManagedFrame* parent);

    /**
    *   Default destructor,
    *   you cannot use this one use RheiaWizardManager::Free() instead;
    */
    ~RheiaWizardManager();

protected :

    /**
    *   Callback used when a wizard page is changing
    */
    void OnPageChanging( wxWizardEvent& event );

    /**
    *   Callback used when a wizard page has changed
    */
    void OnPageChanged( wxWizardEvent& event );

    /**
    *   Callback used when the wizard is cancelled
    */
    void OnCancelWizard( wxWizardEvent& event );

    /**
    *   Callback used when the wizard is finished
    */
    void OnWizardFinish( wxWizardEvent& event );

private :

    RheiaProjectCreationWizard* m_projectWizard;
    RheiaManagedFrame* m_parent;

    static RheiaProjectWizardRegistrationMap m_RegisteredWizards;

    DECLARE_EVENT_TABLE()

};

/**
*   @class RheiaProjectWizardRegistrant
*
*   @brief This is the base class used for registering a project wizard in the project factory
*
*   You have to use this class in a global variable for your project wizard to register it into
*   the factory and to enable it access to users in Rheia.
*
*   you can use the following example to remind what to do...:
*   @code
*   namespace {
*       RheiaProjectWizardRegistrant<MyProjectWizard> registrant( "MyProjectWizard" , "MyProject" );
*   };
*   @endcode
*/
template<class T> class RheiaProjectWizardRegistrant
{
public :

    /**
    *   Base constructor
    *
    *   @param name title/name of the project wizard for registering in the factory
    *   @param category wizard project's name for the factory's organization
    */
    RheiaProjectWizardRegistrant( const wxString& name , const wxString& category, const wxString& bitmapBase )
    {
		m_type = name;
		
        RheiaWizardManager::RegisterProjectWizard( name ,
                                                    category,
                                                    bitmapBase,
                                                    &Create ,
                                                    &Free );
    }
	
	/** destructor */
	virtual ~RheiaProjectWizardRegistrant() 
	{
		RheiaWizardManager::UnregisterProjectWizard( m_type );
	}

    /**
    *   Create project function
    *
    *   @param wizard the wizard in which we want to create the project wizard
    *   @param workspace the workspace in which we want to create the project
    */
    static RheiaProjectCreationWizard* Create( wxWizard* wizard,
                                RheiaManagedFrame* parent ,
                                RheiaWorkspace* workspace )
    {
        return new T( wizard , parent , workspace );
    }

    /**
    *   Free project wizard function or pointer to the destructor
    *
    *   @param wizard the wizard to free
    */
    static void Free( RheiaProjectCreationWizard* wizard )
    {
        delete wizard;
    }
private :
	wxString m_type;
};

/** define the easy macro to register the project wizard in the factory */
#define REGISTER_PROJECT_WIZARD( object , name , category , bitmapbase ) \
    namespace { \
        RheiaProjectWizardRegistrant< object > registrant( name , category , bitmapbase ); \
    }

#endif
