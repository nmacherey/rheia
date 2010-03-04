/**
*   @file RheiaConfigurationPattern.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	19-November-2009
*	@version 0.0.2
*/
#include <RheiaConfigurationManager.h>
#include <RheiaConfigurationPattern.h>
#include <RheiaManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaPersonalityManager.h>
#include <RheiaConfigurationPanel.h>
#include <RheiaConfigurationPattern.h>
#include <RheiaPlatform.h>
#include <RheiaException.h>
#include <RheiaXmlManager.h>
#include <RheiaInfoWindow.h>
#include <RheiaStandardPaths.h>
#include <RheiaGlobals.h>
#include "sdkversion.h"

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

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

/** global instance for RheiaConfigurationPattern */
template<> RheiaConfigurationPattern* Mgr<RheiaConfigurationPattern>::instance = 0;
/** global instance for RheiaConfigurationPattern */
template<> bool  Mgr<RheiaConfigurationPattern>::isShutdown = false;

namespace
{
    const wxString ConfigurationVersion = wxT("1.0.1");
}

RheiaConfigurationPattern::RheiaConfigurationPattern() : m_doc(0), m_tempDoc(0)
{
    wxString personality(RheiaPersonalityManager::Get()->GetPersonality());
    m_configFile = RheiaFileFinder::FindFile( personality + _T(".conf") );

    if (m_configFile.IsEmpty())
    {
        m_configFile = RheiaStandardPaths::ConfigDirectory() + wxFILE_SEP_PATH + personality + _T(".conf");
        m_doc = xmlNewDoc( NULL );
        xmlNode *root = xmlNewNode( NULL , (const xmlChar*) "RheiaConfiguration" );
        xmlNewProp( root, (const xmlChar*) "version", rxU2C( ConfigurationVersion ) );
        xmlDocSetRootElement( m_doc , root );
        return;
    }

    ChangeConfigurationTo(m_configFile);
}

void RheiaConfigurationPattern::ChangeConfigurationTo(const wxString& file)
{
    m_doc = xmlParseFile( rcU2C( file ) );

    if ( m_doc == NULL )
        RheiaThrow(wxT("Error accessing file:\n") + file);

    xmlNode* docroot = xmlDocGetRootElement( m_doc );
    xmlChar* prop = xmlGetProp( docroot , (const xmlChar*) "version" );
    wxString version = RheiaC2U( (const char*) prop );
    xmlFree(prop);

    if (!version.IsSameAs( ConfigurationVersion ) )
        InfoWindow::Display( wxT("WARNING!!!!") , wxT("Unknown configuration file version continuing happily !") , 5000 );

    wxString revision = wxString::Format( wxT("%2.2f") , AutoVersion::UBUNTU_VERSION_STYLE );

    wxString info;
    wxDateTime date = wxDateTime::Now();
    wxString sDate =  date.Format( wxT("%c") , wxDateTime::CET ) ;

#ifndef __GNUC__

    info.Printf(_T( " application info:\n\t version :\t%s\n\t build date :\t%s, %s \n\t saving date : \t%s" ), revision, wxT(__DATE__), wxT(__TIME__), sDate);
#else
    info.Printf(_T( " application info:\n"
                    "\t version :\t%s\n"
                    "\t build date :\t%s, %s\n"
                    "\t saving date :\t%s\n"
                    "\t gcc version :\t%d.%d.%d "), revision.c_str(), wxT(__DATE__), wxT(__TIME__),sDate.c_str(),
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

    xmlNode *child = docroot->children;
    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );
        if ( ChildName.IsSameAs( wxT("comment") ) )
            xmlReplaceNode( child , NULL );
        child = child->next;
    }

    xmlNode *temp = xmlNewDocComment( m_doc , rxU2C( info ) );
    xmlAddPrevSibling(docroot->children,temp);

}

RheiaConfigurationPattern::~RheiaConfigurationPattern()
{
    /** Free all managers in the configuration m_groups */
    RheiaConfigurationManagerMap::iterator it;

    for ( it = m_groups.begin(); it != m_groups.end(); ++it )
        delete it->second;

    /** Clear all m_groups */
    m_groups.clear();

    Save();
}

void RheiaConfigurationPattern::Save()
{
    if (m_doc)
    {
        if (!xmlSaveFormatFileEnc(rcU2C(m_configFile) , m_doc , "UTF-8" , 1))
            wxSafeShowMessage(_T("Could not save config file..."), _("Warning"));

        xmlFreeDoc( m_doc );
    }
    m_doc = 0;

    if( m_tempDoc )
        xmlFreeDoc( m_tempDoc );

    m_tempDoc = 0;
}

RheiaConfigurationManager* RheiaConfigurationPattern::Build(const wxString& group)
{
    if (group.IsEmpty())
        RheiaThrow(_T("You attempted to get a configuration manager instance without providing a configuration group."));

    wxCriticalSectionLocker locker(m_criticalSection);

    RheiaConfigurationManagerMap::iterator it = m_groups.find(group);

    if (it != m_groups.end())
        return it->second;

    xmlNode* docroot;
    wxString sub_group;

    if (group.StartsWith(_T("temp:")))
    {
        if (!m_tempDoc)
        {
            m_tempDoc = xmlNewDoc(NULL);
            docroot = xmlNewNode( NULL , (const xmlChar*) "RheiaConfiguration" );
            xmlDocSetRootElement( m_tempDoc , docroot );
        }
        docroot = xmlDocGetRootElement(m_tempDoc);
        sub_group = group.AfterFirst(_T(':'));
    }
    else
    {
        docroot = xmlDocGetRootElement(m_doc);
        if (!docroot)
        {
            wxString err(_("Fatal error parsing supplied configuration file.\n"));
            RheiaThrow(err);
        }
        sub_group = group;
    }

    wxString illegal(_T(" -:.\"\'$&()[]<>+#"));
    size_t i = 0;
    while ((i = sub_group.find_first_of(illegal, i)) != wxString::npos)
        sub_group[i] = _T('_');

    /*** Check if the node exist in the docroot but has not been used yet */
    xmlNode* root = docroot->children;
    while ( root != NULL )
    {
        wxString name = RheiaC2U( (const char*) root->name ) ;

        if ( name.IsSameAs( sub_group ) )
            break;

        root = root->next;
    }

    /*** if the node does ot exists create it */
    if ( root == NULL ) // namespace does not exist
    {
        root = xmlNewNode( NULL , rxU2C( sub_group ) );
        xmlAddChild( docroot , root );
    }

    if ( root == NULL ) // now what!
        RheiaThrow(_T("Unable to create group in document tree (actually not possible..?)"));

    RheiaConfigurationManager *cfg = new RheiaConfigurationManager(m_doc,root);
    m_groups[group] = cfg;

    return cfg;
}
