/**
*   @file RheiaProjectLoader.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
#ifndef RheiaProjectLoader_h_
#define RheiaProjectLoader_h_

#include <RheiaWMgtSettings.h>
#include <RheiaGlobals.h>

/* imports */
class RheiaProject;
class RheiaWorkspace;
class RheiaProjectManager;
class RheiaProjectElement;
class RheiaManagedFrame;

/* lib xml2 imports */
typedef struct _xmlNode xmlNode;
typedef struct _xmlDoc xmlDoc;

/**
*   @class RheiaProjectLoader
*
*   @brief This is the basic class for loading/saving a project from/into a file
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
class WMGT_DLLEXPORT RheiaProjectLoader
{
public :
    /**
    *   Basic constructor for loading/saving a workspace
    *
    *   @param project the project to load or save
    */
    RheiaProjectLoader( RheiaProject *project );

#ifdef SWIG
	%rename(PreRheiaProjectLoader) RheiaProjectLoader( );
#endif
    /**
    *   Default constructor with no project
    */
    RheiaProjectLoader( );
	
	/** destructor */
	virtual ~RheiaProjectLoader() {};

    /**
    *   Load the content of the given file in the project and return
    *   @param file the full file path to load
    *
    *   @return returns true if the file has properly been loaded else returns false
    */
    bool Open( const wxString& file, RheiaManagedFrame* parent, RheiaWorkspace *workspace );

    /**
    *   Save the content of the project in the given file and returns
    *   @param file the full file path in which to save
    *
    *   @return returns true if the file has properly been saved else returns false
    */
    bool Save( const wxString& file );

    /** Set the current project */
    void SetProject( RheiaProject* project ){m_project = project;};

    /** Get the current project */
    RheiaProject* GetProject(){return m_project;};

private :
    /**
    *   Load the project options from the given node
    *
    *   @param parent the parent node from which to load the project options
    *   @return true if the project options have properly been loaded
    */
    bool DoLoadProjectOptions( xmlNode* parent );

    /**
    *   Save the project options to the given node
    *
    *   @param parent the parent node in which to save the project options
    *   @return true if the options have been saved properly
    */
    bool DoSaveProjectOptions( xmlNode* parent );

private :

    RheiaProject *m_project;
};

#endif

