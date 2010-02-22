/**
*   @file RheiaWorkspaceLoader.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
#ifndef RheiaWorkspaceLoader_h_
#define RheiaWorkspaceLoader_h_

#include <RheiaWMgtSettings.h>
#include <RheiaGlobals.h>

/* imports */
class RheiaWorkspace;
class RheiaProject;
class RheiaWorkspaceManager;

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaWorkspaceLoader
*
*   @brief This is the basic class for loading/saving a workspace from/into a file
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaWorkspaceLoader
{
public :
    /**
    *   Basic constructor for loading/saving a workspace
    *
    *   @param workspace the workspace to load or save
    */
    RheiaWorkspaceLoader( RheiaWorkspace *workspace );
	
	/** destructor */
	virtual ~RheiaWorkspaceLoader() {};

    /**
    *   Load the content of the given file in the workspace and return
    *   @param file the full file path to load
    *
    *   @return returns true if the file has properly been loaded else returns false
    */
    bool Open( const wxString& file );

    /**
    *   Save the content of the workspace in the given file and returns
    *   @param file the full file path in which to save
    *
    *   @return returns true if the file has properly been saved else returns false
    */
    bool Save( const wxString& file );

private :

    /**
    *   Load all the projects attached in the given workspace
    *
    *   @param parent the parent Node in which projects nodes are contained
    *
    *   @return returns true if everything has been loaded properly else returns false
    */
    bool DoLoadProjects( xmlNode* parent );

    /**
    *   Load the project contained in the given node and return it
    *
    *   @param parent the parent Node in which the project is contained
    *
    *   @return returns the project if the project has properly been loaded
    *           else returns NULL
    */
    RheiaProject* DoLoadProjectFromNode( xmlNode* parent );

    /**
    *   Save all the projects attached in the given workspace
    *
    *   @param parent the parent Node in which projects nodes must be saved
    *
    *   @return returns true if everything has been saved properly else returns false
    */
    bool DoSaveProjects( xmlNode* parent );

    /**
    *   Save the project in the given node
    *
    *   @param project the RheiaProject to save
    *   @param parent the parent Node in which the project must be saved
    *
    *   @return returns the true if the project has properly been saved
    *           else returns false
    */
    bool DoSaveProjectToNode( RheiaProject *project, xmlNode* parent );

private :

    RheiaWorkspace *m_workspace;
};

#endif
