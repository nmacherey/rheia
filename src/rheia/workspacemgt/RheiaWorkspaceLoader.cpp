/**
*   @file RheiaWorkspaceLoader.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 24-April-2009
*   @version 0.0.1
*/
#include <RheiaWorkspaceLoader.h>
#include <RheiaAppGlobals.h>
#include <RheiaProjectLoader.h>
#include <RheiaWorkspaceManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaMenuManager.h>
#include <RheiaWorkspace.h>
#include <RheiaProject.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaTreeItemData.h>
#include <RheiaInfoWindow.h>
#include <RheiaStatusBarManager.h>
#include <RheiaPlatform.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>
#include <RheiaEventWorkspace.h>

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

RheiaWorkspaceLoader::RheiaWorkspaceLoader( RheiaWorkspace *workspace )
{
    m_workspace = workspace;
}

bool RheiaWorkspaceLoader::Open( const wxString& file )
{
    xmlDoc* doc = NULL;
    xmlNode* root;
    xmlNode* workspace;

    doc = xmlParseFile( rcU2C( file ) );

    if( doc == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot load document : ") + file );
        return false;
    }

    root = xmlDocGetRootElement( doc );

    wxString rootName = RheiaC2U( (const char*) root->name );

    if( !rootName.IsSameAs( wxT("RheiaWorkspaceFile") ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Invalid root in document : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    workspace = root->children;

    while( workspace != NULL )
    {
        wxString workspaceNodeName = RheiaC2U( (const char*) workspace->name );

        if( workspaceNodeName.IsSameAs( wxT("Workspace") ) )
        {
            break;
        }

        workspace = workspace->next;
    }

    if( workspace == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot find the workspace node in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    wxString WorkspaceName;
    xmlAttr* workspaceAttr = xmlHasProp( workspace , (const xmlChar*) "name" );

    if( workspaceAttr == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Workspace has no name attribute in file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    WorkspaceName = RheiaC2U( (const char*) xmlNodeGetContent( workspaceAttr->children ) );

    /** Now check if a workspace with the same name exists or not */
    if( RheiaWorkspaceManager::Get(m_workspace->m_parent)->Exists( WorkspaceName ) )
    {
        int retcode = wxMessageBox( wxT("A workspace with the same name exists ... \n")
                    wxT("Do you want to close it ?\n\n\n")
                    wxT("NOTE : If you choose no the workspace will ot be loaded..."), wxT("Already existing workspace!"),
                    wxYES | wxNO | wxCENTER );

        if( retcode == wxID_NO )
        {
            xmlFreeDoc( doc );
            return false;
        }

        RheiaWorkspace *workspace = RheiaWorkspaceManager::Get(m_workspace->m_parent)->FindWorkspace( WorkspaceName );
        if ( workspace )
        {
            if ( workspace->GetModified() )
            {
                int retId = wxMessageBox( wxT("The workspace has changed do you want to save it ?") , wxT("Alert")
                , wxYES | wxNO | wxCANCEL | wxCENTER );

                if ( retId == wxYES )
                {
                    RheiaWorkspaceManager::Get(m_workspace->m_parent)->SaveWorkspace( workspace );
                    workspace->SetModified(false);
                }
                else if ( retId == wxCANCEL )
                {
                    xmlFreeDoc( doc );
                    return false;
                }
            }

            RheiaWorkspaceManager::Get(m_workspace->m_parent)->RemoveWorkspace( workspace->GetName() );
        }
    }

    if( !DoLoadProjects( workspace ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Problems while loading projects from file : ") + file );
        xmlFreeDoc( doc );
        return false;
    }

    m_workspace->SetName( WorkspaceName );
    m_workspace->SetFileName( file );

    /* Finally add the workspace in the workspace manager */
    RheiaWorkspaceManager::Get(m_workspace->m_parent)->AddWorkspace( m_workspace , WorkspaceName );

    /* And change the currently selected workspace from the status bar manager */
    RheiaStatusBarManager::Get(m_workspace->m_parent)->SetWorkspace( WorkspaceName );
    m_workspace->SetModified( false );
    xmlFreeDoc( doc );
    return true;
}

bool RheiaWorkspaceLoader::Save( const wxString& file )
{
    xmlDoc* doc;
    xmlNode* root;
    xmlNode* workspace;

    doc = xmlNewDoc( (const xmlChar*) "1.0" );

    if( !doc )
        return false;

    root = xmlNewNode( NULL , (const xmlChar*) "RheiaWorkspaceFile" );
    workspace = xmlNewNode( NULL , (const xmlChar*) "Workspace" );

    xmlNewProp( workspace , (const xmlChar*) "name" , rxU2C( m_workspace->GetName() ) );

    if( !DoSaveProjects( workspace ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Error while saving your project to file : ") + file );
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

    info.Printf(_( " workspace info:\n"
                    "\t application build_date:\t%s, %s \n"
                    "\t workspace saving date : \t%s" ), wxT(__DATE__), wxT(__TIME__), sDate);
#else
    info.Printf(_T( " workspace info:\n"
                    "\t application build_date:\t%s, %s\n"
                    "\t workspace saving date:\t%s\n"
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
    xmlAddChild( root , workspace );
    xmlDocSetRootElement( doc , root );
    xmlSaveFormatFileEnc( rcU2C( file ) , doc , "UTF-8", 1 );

    m_workspace->SetModified( false );
    xmlFreeDoc( doc );

    return true;
}

bool RheiaWorkspaceLoader::DoLoadProjects( xmlNode* parent )
{
    xmlNode* child = parent->children;

    RheiaWorkspaceEvent evt(RheiaEVT_WORKSPACE_BEGIN_ADD_PROJECTS,0,m_workspace);
    m_workspace->m_parent->GetEventHandler()->ProcessEvent(evt);

    while ( child != NULL )
    {
        wxString childName = RheiaC2U( (const char*) child->name );
        if ( childName.IsSameAs( wxT("Project") ) )
        {
            RheiaProject *prj = DoLoadProjectFromNode( child );

            if( prj == NULL )
            {
                RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_END_ADD_PROJECTS,0,m_workspace);
                m_workspace->m_parent->GetEventHandler()->ProcessEvent(evt2);
                return false;
            }

            m_workspace->Add( prj->GetName() , prj );
        }
        child = child->next;
    }

    RheiaWorkspaceEvent evt2(RheiaEVT_WORKSPACE_END_ADD_PROJECTS,0,m_workspace);
    m_workspace->m_parent->GetEventHandler()->ProcessEvent(evt2);

    return true;
}

bool RheiaWorkspaceLoader::DoSaveProjects( xmlNode* parent )
{

    RheiaTreeItemMap m_map = m_workspace->GetItems();
    RheiaTreeItemMap::iterator it = m_map.begin();

    for( ; it != m_map.end() ; it++ )
    {
        if( it->second->IsKindOf(CLASSINFO(RheiaProject)) )
        {
            xmlNode* child = xmlNewNode( NULL , (const xmlChar*) "Project" );
            RheiaProject* prj = dynamic_cast<RheiaProject*>(it->second);
            DoSaveProjectToNode( prj , child );
            xmlAddChild( parent , child );
        }
    }

    return true;
}

RheiaProject* RheiaWorkspaceLoader::DoLoadProjectFromNode( xmlNode* parent )
{
    xmlAttr* fileAttr = xmlHasProp( parent , (const xmlChar*) "file" );

    if( fileAttr == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Project element has no file attribute") );
        return NULL;
    }

    wxString file = RheiaC2U( (const char*) xmlNodeGetContent( fileAttr->children ) );

    RheiaProjectLoader loader;
    if( !loader.Open( file , m_workspace->m_parent, m_workspace ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot load the document : ") + file );
        return NULL;
    }

    RheiaProject *prj = loader.GetProject();

    if( prj == NULL )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot load project from the document : ") + file );
        return NULL;
    }

    return prj;
}

bool RheiaWorkspaceLoader::DoSaveProjectToNode( RheiaProject *project, xmlNode* parent )
{
    wxString file = project->GetFileName();

    if( file.IsEmpty() )
    {
        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_project_path") , RheiaStandardPaths::HomeDirectory() );

        wxFileDialog dialog( m_workspace->m_parent ,
                             wxT("Select the project file in whihc to save..."),
                             LastOpenPath,
                             project->GetName() + FileExt::PRJ_EXT,
                             FileExt::PRJ_EXT_FILE,
                             wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

        if ( dialog.ShowModal() != wxID_OK )
        {
            return false;
        }

        file = dialog.GetPath();

        wxFileName lastPath( file );
        RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_project_path") , lastPath.GetPath() );
    }



    xmlNewProp( parent , (const xmlChar*) "file" , rxU2C( file ) );

    RheiaProjectLoader saver( project );
    if( !saver.Save( file ) )
    {
        InfoWindow::Display( wxT("WARNING") , wxT("Cannot save the document : ") + file );
        return false;
    }

    return true;
}
