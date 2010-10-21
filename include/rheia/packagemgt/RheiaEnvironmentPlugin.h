/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*	@file RheiaEnvironmentPlugin.h
*
*   Revision : 20-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	15-Nov-2008
*	@version 0.0.1
*/
#ifndef RheiaEnvironmentPlugin_h_
#define RheiaEnvironmentPlugin_h_

#include <RheiaPMgtSettings.h>
#include <RheiaPlugin.h>

#include <map>

#include <wx/string.h>
#include <wx/image.h>

class RheiaWorkspace;
class RheiaProject;
class wxWizard;
class RheiaWorkspaceManager;
class RheiaProjectManager;
class RheiaProjectCreationWizard;
class RheiaSaver;

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;

/** Associate a string to a bitmap for project offers */
typedef std::map< wxString , wxImage* > RheiaProjectOffers;

/**
*	@class RheiaEnvironmentPlugin
*
*	@brief RheiaEnvironmentPlugin is the base class for providing Rheia with an environment
*
*	Anyone who wants to develop a full application with Rheia shall know everything about
*   RheiaEnvironmentPlugin's. RheiaEnvironment Plugin is the basic class for providing Rheia
*   with your environment. Actually, an environment is a set of projects, classes and
*   configuration tools that will add core functionnalities in your application.
*
*   Rheia is a Workspace/Projects based application made for scientific applications and not
*   for stand alone editors. RheiaEnvironment plugin's allow anyone to mix different environment
*   in the same application without having to reload or multiply its instances. Any Environment
*   plugins shall provide the user with at least one project derived from RheiaProject and the
*   respective wizards that the user can use in order to create such projects. Wizards must all
*   be derived from RheiaProjectCreationWizard.
*
*   More over the projects can be organized in different categories in Rheia so the user can
*   now where to find a project if your environment provides many different kind of projects.
*   We can take as example a Development Task in C++ which can be organized in different categories
*   such as Libraries, Graphical User Interfaces, Console Applications, OpenGL Applications...
*
*   If you are new to Rheia you can view RheiaEnvironmentPlugin's as local data base providing
*   the application with a table of Project Categories and a table of Projects that can be
*   ordered by categories. This class seems to be simple, however behind this simple wrapper
*   you can simply link a full application with many functionalities. This is the place to
*   take care of what you are doing :-) !.
*
*   We concil developers to store all projects they can develop in "Factory design patterns" in
*   order to keep the maintainability of their applications. Environment plugins can contain a
*   very hudge amount of code as they defin core functionnalities for your application and make
*   technical proprietary libraries available in the application.
*
*   To know hoaw to develop an environment plugin you have to deal with many models available
*   in Rheia. So before continuing please be sure to read the entire application's documentation
*   specially for :
*
*       + RheiaProject
*       + RheiaBookPage
*       + RheiaStandardPaths
*       + RheiaPlugin
*       + RheiaProjectElement
*       + RheiaWorkspace
*       + RheiaProjectCreationWizard
*       + RheiaWizardPageBase
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	15-Nov-2008
*	@version 0.0.1
*/
class PMGT_DLLEXPORT RheiaEnvironmentPlugin : public RheiaPlugin
{
    /** Give our private member access to the workspace manager */
    friend class RheiaWorkspaceManager;

public :
    /*******************************************************************************************************
    *	CONSTRUCTORS
    *******************************************************************************************************/
    /**
    *   Default constructor
    *   As RheiaEnvironmentPlugin object is a model for developers
    *   who want to integrate a full environment in Rheia, there is
    *   really nothing to do here.s
    */
    RheiaEnvironmentPlugin(RheiaManagedFrame* parent);

    /*******************************************************************************************************
    *	METHODS
    *******************************************************************************************************/
    /**
    *   Any environment plugin has a special configuration group, RhEnvironment.
    *   This configuration group is used to recast this information for exemple
    *   when the user watns to create a project. Usually you will never have to
    *   change the configuration group for your plugins as it is manage by the
    *   model you are using.
    */
    virtual int GetConfigurationGroup() const
    {
        return RhCore;
    }

    /**
    *   Any environment plugin shall provide Rheia with their visual identity.
    *   Here is the place to load the bitmap of your environment and to return
    *   it to the application.
    *   This method can be called at any time for many different reasons. Moreover
    *   the application may request different size for your environment bitmap :
    *       + 80x80
    *       + 48x48
    *       + 16x16
    *       + 22x22
    *       + 128x128
    *
    *   So you have to provide Rheia with all of this bitmaps (PNG preferable) and
    *   this method is the place to load the bitmap from your resource.
    *
    *   @param size requested size of the bitmap to load
    */
    virtual const wxBitmap& GetBitmap( int size ) = 0;

    /*******************************************************************************************************
    *  PROJECTS MANAGEMENT METHODS
    *******************************************************************************************************/
    /**
    *   Any environment plugin must provide the application with at least
    *   on RheiaProject. Here is the place to give the total number of
    *   projects the environment can create. This is used in the project
    *   creation dialog in order to enable users to choose for the project
    *   they want to create.
    *   Please note that any project must be associated to a Wizard to guide
    *   users in the creation of such projects.
    *
    *   @return the number of projects this plugin contains
    */
    virtual int GetProjectsCount() const = 0;

    /**
    *   Get The project's category lists
    *   @return an array string containing the project's categories
    */
    virtual wxArrayString GetCategoryList() = 0;

    /**
    *   List the available project's titles for the specified
    *   category.
    *
    *   @param category the category's name to list projects for
    *
    *   @note if the category is All you have to list all avaliable projects
    *   for all categories
    *
    *   @return an array string of available projects for the given category
    */
    virtual wxArrayString GetProjectsFor( const wxString& category ) = 0;

    /**
    *   Get the category for the given project index
    *
    *   @param index the project index.
    *   @return the name of the specified project'ss category at @c index
    */
    virtual wxString GetProjectCategory(int index) const = 0;

    /**
    *   Get the project title at the given index
    *
    *   @param index the project's index.
    *   @return the project's title
    */
    virtual wxString GetProjectTitle(int index) const = 0;

    /**
    *   Get the project description at the given index
    *
    *   @param index the project's index.
    *   @return the project's description
    */
    virtual wxString GetProjectDescription(int index) const = 0;

    /**
    *   Get the project's bitmap at the given index
    *
    *   @param index the prject's index.
    *   @return the project's bitmap
    */
    virtual const wxBitmap& GetProjectBitmap(int index) const = 0;

    /**
    *   When this is called, the wizard must get to work ;). You have to implement your wizard here.
    *   In Rheia a Project Wizard must return the created project after the steps you need to define
    *   in order to create your projects.
    *
    *   @param index the project's index.
    *   @param parent the parent wizard in which anything will be run
    *   @param workspace the workspace in which the project shall be built
    *   @param createdFilename if provided, on return it should contain the main filename
    *                         this wizard created. You have to ask the user for the file name he wants to create
    *
    *   @return a pointer to the generated RheiaProject. NULL for everything else (failure too).
    */
    virtual RheiaProjectCreationWizard* GetWizard(int index,
                                    wxWizard* parent,
                                    RheiaWorkspace *workspace,
                                    wxString* createdFilename = 0) = 0; // do your work ;)

    /*******************************************************************************************************
    *  LOADING MANAGEMENT METHODS
    *******************************************************************************************************/
    /**
    *   You have to overload this method in order to tell the project loader if you can handle the project
    *   accordingly to its type.
    *
    *   @param type the loaded project's type
    *   @return true if the project can be created by the plugin
    */
    virtual bool CanHandleProject( const wxString& type ) = 0;

    /**
    *   Create an empty project given its type name and file. You have to overload this method
    *   in order to allow the application to create a project which is not owned by rheia
    *
    *   @param type type or name of the project template to be created
    *   @param workspace the workspace in which the project shall be attached
    *   @param name the project's name
    *   @param file the project file path for saving
    *
    *   @return NULL if the project was no created properly and the created project else
    */
    virtual RheiaProject* CreateProject( const wxString& type, RheiaWorkspace* workspace,
                                const wxString& name = wxEmptyString ,
                                const wxString& file = wxEmptyString ) = 0;
};

#endif
