/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaProjectFactory.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/

#ifndef _RheiaProjectFactory_h_
#define _RheiaProjectFactory_h_

#include <RheiaWMgtSettings.h>
#include <RheiaManager.h>
#include <RheiaManagedFrame.h>
#include <map>

/* imports */
class RheiaProject;
class RheiaWorkspace;

/** define a project constructor function */
typedef RheiaProject*(*ProjectConstructor)( RheiaManagedFrame* , RheiaWorkspace* , const wxString& , const wxString& );

/** define a project destructor function */
typedef void(*ProjectDestructor)( RheiaProject * );

/**
*   @struct RheiaProjectRegistration
*
*   @brief This structure is used to store the informations about the creation of a project
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
struct RheiaProjectRegistration
{
    RheiaProjectRegistration():ctor(0),dtor(0){};

#ifndef SWIG
    RheiaProjectRegistration(const RheiaProjectRegistration& rhs):
        name(rhs.name),
        description( rhs.description ),
        title(rhs.title),
        bitmapBaseName( rhs.bitmapBaseName ),
        ctor(rhs.ctor),
        dtor(rhs.dtor){};
#endif

    wxString name;
    wxString description;
    wxString title;
    wxString bitmapBaseName;
    ProjectConstructor ctor;
    ProjectDestructor dtor;
};

/** define a map of RheiaProjectRegistration for storing it in the factory */
typedef std::map< wxString , RheiaProjectRegistration > RheiaProjectRegistrationMap;

/**
*   @class RheiaProjectFactory
*
*   @brief This is the base class for registering new projects in Rheia.
*
*   RheiaProjectFactory is the class used for registering available project that
*   can be created by the user in the GUI.
*
*   A project has to be created from this class by usgin the CreateProject function.
*   Before anaything the project shall have been registered using the REGISTER_PROJECT macros.
*
*   A project can be attached to a specific cathegory that will then be displayed in the creation
*   wizard as well.
*
*   RheiaProjectFactory is working as the managers and to access to its functionalities you have to
*   use RheiaProjectFactory::Get().
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectFactory : public Singleton<RheiaProjectFactory>
{
    /*! give our private members acces to Singleton */
    friend class Singleton<RheiaProjectFactory>;
    /*! give our private members acces to RheiaManager */
    friend class RheiaManager;

public :
    /*****************************************************************************************************
    * PUBLIC METHODS
    *****************************************************************************************************/

    /**
    *   Get the available project for a given category. This function
    *   return a RheiaCategoryMap in which each key is the name of the category
    *   and each item contains the list of available projects for the category
    */
    wxArrayString GetProjectList( );

    /**
    *   Create a project by finding the proper element in the map, and
    *   using the given parameters in construction.
    *
    *   @param type type or name of the project template to be created
    *   @param workspace the workspace in which the project shall be attached
    *   @param name the project's name
    *   @param file the project file path for saving
    *
    *   @return NULL if the project was no created properly and the created project else
    */
    RheiaProject* CreateProject( const wxString& type,
                                RheiaManagedFrame* parent,
                                RheiaWorkspace* workspace,
                                const wxString& name = wxEmptyString ,
                                const wxString& file = wxEmptyString );

    /**
    *   Method used for registering a project in the project factory
    *
    *   @param name name or title for the project
    *   @param ctor Pointer to the project constructor function
    *   @param dtor pointer to the project destructor function
    *
    *   @return true if the project was properly registered in the factory
    */
    bool RegisterProject( const wxString& name ,
                        const wxString& description,
                        const wxString& title,
                        const wxString& bitmapBaseName,
                        ProjectConstructor ctor, ProjectDestructor dtor );
						
	/** Unregister a project */
	bool UnregisterProject( const wxString& name );

    /** Get registered projects map from the factory */
    RheiaProjectRegistrationMap& GetRegisteredProjects(){return m_RegisteredProjects;};

    /**
    *   Find a project registration structure by giving the project name
    *
    *   @param name the project's name to find the registration for
    *
    *   @return an empty RheiaProjectRegistration if the project has not been found else return
    *   the project's registration structure
    */
    RheiaProjectRegistration FindProjectRegistration(const wxString& name);

protected :
    /*****************************************************************************************************
    * PRIVATE CONSTRUCTORS AND DESTRUCTORS
    *****************************************************************************************************/
    /** Default Constructor */
    RheiaProjectFactory();

    /** Default Destructor */
    ~RheiaProjectFactory();

private :
    /*****************************************************************************************************
    * PRIVATE VARIABLES
    *****************************************************************************************************/
    RheiaProjectRegistrationMap m_RegisteredProjects;
};

#ifndef SWIG
/**
*   @class RheiaProjectRegistrant
*
*   @brief This is the base class used for registering a project in the project factory
*
*   You have to use this class in a global variable for your project to register it into
*   the factory and to enable it access to users in Rheia.
*
*   you can use the following example to remind what to do...:
*   @code
*   namespace {
*       RheiaProjectRegistrant<MyProject> registrant( "MyProject" , "MyProjectCategory" );
*   };
*   @endcode
*/
template<class T> class RheiaProjectRegistrant
{
public :

    /**
    *   Base constructor
    *
    *   @param name title/name of the project for registering in the factory
    *   @param category projects category for the factory's organization
    */
    RheiaProjectRegistrant( const wxString& name )
    {
		m_projectType = name;
		
        RheiaProjectFactory::Get()->RegisterProject( name ,
                                                    T::description ,
                                                    T::title ,
                                                    T::bitmapBaseName ,
                                                    &Create ,
                                                    &Free );
    }
	
	/** destructor */
	virtual ~RheiaProjectRegistrant() {
		RheiaProjectFactory::Get()->UnregisterProject( m_projectType );
	}

    /**
    *   Create project function
    *
    *   @param workspace the workspace in which we want to create the project
    *   @param name project's name in the workspace
    *   @param file project's file for saving
    */
    static RheiaProject* Create( RheiaManagedFrame*parent,
                                RheiaWorkspace* workspace ,
                                const wxString& name = wxEmptyString,
                                const wxString& file = wxEmptyString )
    {
        return new T( parent , workspace , file , name );
    }

    /**
    *   Free project function or pointer to the destructor
    *
    *   @param project the project to free
    */
    static void Free( RheiaProject* project )
    {
        delete project;
    }
	
private :
	wxString m_projectType;
};

/** define the easy macro to register the project in the factory */
#define REGISTER_PROJECT( object , title ) \
    namespace ns##object { \
        RheiaProjectRegistrant< object > object##registrant( title ); \
    }
#endif
#endif
