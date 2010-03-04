/**
*   @file RheiaProjectLoader.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
#include <RheiaProjectLoader.h>
#include <RheiaConfigurationManager.h>
#include <RheiaProfileManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaPluginManager.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaMenuManager.h>
#include <RheiaWorkspace.h>
#include <RheiaProject.h>
#include <RheiaProjectFactory.h>
#include <RheiaTreeItemData.h>
#include <RheiaInfoWindow.h>
#include <RheiaProject.h>
#include <RheiaStatusBarManager.h>
#include <RheiaPlatform.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>

#include <wx/aui/aui.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/choice.h>
#include <wx/xrc/xmlres.h>
#include <wx/toolbar.h>
#include <wx/filedlg.h>
#include <wx/menu.h>

#include <iostream>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaProjectLoader::RheiaProjectLoader( RheiaProject *project )
{
    m_project = project;
}

RheiaProjectLoader::RheiaProjectLoader( )
{
    m_project = NULL;
}

bool RheiaProjectLoader::Open( const wxString& file, RheiaManagedFrame* parent, RheiaWorkspace *workspace )
{
    xmlDoc* doc = NULL;
    xmlNode* root;
    xmlNode* project;

    doc = xmlParseFile( rcU2C( file ) );

    if( doc == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot load document : ") + file );
        return false;
    }

    root = xmlDocGetRootElement( doc );

    wxString rootName = RheiaC2U( (const char*) root->name );

    if( !rootName.IsSameAs( wxT("RheiaProjectFile") ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Invalid root in document : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    project = root->children;

    while( project != NULL )
    {
        wxString projectNodeName = RheiaC2U( (const char*) project->name );

        if( projectNodeName.IsSameAs( wxT("Project") ) )
        {
            break;
        }

        project = project->next;
    }

    if( project == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot find the project node in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    /*********************************************************************************************
    *   Get the project name
    *********************************************************************************************/
    wxString ProjectName;
    xmlAttr* projectAttr = xmlHasProp( project , (const xmlChar*) "name" );

    if( projectAttr == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Project has no name attribute in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    ProjectName = RheiaC2U( (const char*) xmlNodeGetContent( projectAttr->children ) );

    /*********************************************************************************************
    *   Get the project type
    *********************************************************************************************/
    wxString ProjectType;
    xmlAttr* typeAttr = xmlHasProp( project , (const xmlChar*) "type" );

    if( typeAttr == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Project has no type attribute in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    ProjectType = RheiaC2U( (const char*) xmlNodeGetContent( typeAttr->children ) );
    m_project = RheiaProjectFactory::Get()->CreateProject(ProjectType,parent,workspace,ProjectName,file);

    if( m_project == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot find the project type in the factory to load your project from file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    /*********************************************************************************************
    *   Now Load the default project options from the project node
    *********************************************************************************************/
    if( !DoLoadProjectOptions( project ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot Load options from project in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    m_project->SetModified( false );
    xmlFreeDoc( doc );
    return true;
}

bool RheiaProjectLoader::Save( const wxString& file )
{
    if( m_project == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Empty project cannot be saved in file : ") + file );
        return false;
    }

    xmlDoc* doc;
    xmlNode* root;
    xmlNode* project;

    doc = xmlNewDoc( (const xmlChar*) "1.0" );

    if( !doc )
        return false;

    root = xmlNewNode( NULL , (const xmlChar*) "RheiaProjectFile" );
    project = xmlNewNode( NULL , (const xmlChar*) "Project" );

    wxString ProjectName = m_project->GetName();
    wxString ProjectType = m_project->GetType();

    xmlNewProp( project , (const xmlChar*) "name" , rxU2C( ProjectName ) );
    xmlNewProp( project , (const xmlChar*) "type" , rxU2C( ProjectType ) );

    if( !DoSaveProjectOptions( project ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Error while saving project options in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    /*
    *	Writing basinc project configuration
    */
    wxDateTime date = wxDateTime::Now();
    wxString sDate = date.Format( wxT("%c") , wxDateTime::CET ) ;

    wxString info;

#ifndef __GNUC__

    info.Printf(_( " project info:\n"
                    "\t application build_date:\t%s, %s \n"
                    "\t workspace saving date : \t%s" ), wxT(__DATE__), wxT(__TIME__), sDate);
#else
    info.Printf(_T( " project info:\n"
                    "\t application build_date:\t%s, %s\n"
                    "\t project saving date:\t%s\n"
                    "\t gcc_version:\t%d.%d.%d "), wxT(__DATE__), wxT(__TIME__),sDate.c_str(),
                __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

    if (platform::windows)
        info.append(_T("\n\t Windows "));
    if (platform::linux)
        info.append(_T("\n\t Linux "));
    if (platform::macosx)
        info.append(_T("\n\t Mac OS X "));
    if (platform::unix)
        info.append(_T("\n\t Unix "));

    info.append(platform::unicode ? _T("Unicode ") : _T("ANSI "));

    xmlNode *temp = xmlNewDocComment( doc , rxU2C( info ) );

    xmlAddChild( root , temp );

    xmlAddChild( root , project );
    xmlDocSetRootElement( doc , root );
    xmlSaveFormatFileEnc( rcU2C( file ) , doc , "UTF-8", 1 );

    m_project->SetModified( false );
    xmlFreeDoc( doc );

    return true;
}

bool RheiaProjectLoader::DoLoadProjectOptions( xmlNode* parent )
{
    m_project->DoLoadProjectOptions( parent );
    return true;
}

bool RheiaProjectLoader::DoSaveProjectOptions( xmlNode* parent )
{
    m_project->DoSaveProjectOptions( parent );
    return true;
}
