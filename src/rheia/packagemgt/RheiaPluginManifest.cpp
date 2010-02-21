/**
*   @file RheiaPluginManifest.cpp
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	25-November-2009
*	@version 0.0.2
*/
#include <RheiaPluginManifest.h>
#include <RheiaPackageDescription.h>
#include <RheiaPackageMaintainer.h>
#include <RheiaPackageVersion.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPluginManifest::RheiaPluginManifest():
    m_description(NULL),
    m_version(NULL),
    m_sdkversion(NULL),
    m_author(NULL)
{
}

RheiaPluginManifest::~RheiaPluginManifest()
{
    if( m_description != NULL )
        delete m_description;

    if( m_version != NULL )
        delete m_version;

    if( m_sdkversion != NULL )
        delete m_sdkversion;

    if( m_author != NULL )
        delete m_author;
}

RheiaPluginManifest::RheiaPluginManifest(const RheiaPluginManifest& rhs):
    m_name( rhs.m_name ),
    m_title( rhs.m_title ),
    m_thanks( rhs.m_thanks ),
    m_class( rhs.m_class ),
    m_description(NULL),
    m_version(NULL),
    m_sdkversion(NULL),
    m_author(NULL)
{
    if( rhs.m_description != NULL )
        m_description = rhs.m_description->Clone();

    if( rhs.m_version != NULL )
        m_version = rhs.m_version->Clone();

    if( rhs.m_sdkversion != NULL )
        m_sdkversion = rhs.m_sdkversion->Clone();

    if( rhs.m_author != NULL )
        m_author = rhs.m_author->Clone();
}

RheiaPluginManifest* RheiaPluginManifest::Clone()
{
    return new RheiaPluginManifest(*this);
}

void RheiaPluginManifest::SetDescription( RheiaPackageDescription* description )
{
    if( m_description != NULL )
        delete m_description;

    m_description = description;
}

void RheiaPluginManifest::SetVersion( RheiaPackageVersion* version )
{
    if( m_version != NULL )
        delete m_version;

    m_version = version;
}

void RheiaPluginManifest::SetSDKVersion( RheiaPackageVersion* version )
{
    if( m_sdkversion != NULL )
        delete m_sdkversion;

    m_sdkversion = version;
}

void RheiaPluginManifest::SetAuthor( RheiaPackageMaintainer* author )
{
    if( m_author != NULL )
        delete m_author;

    m_author = author;
}

bool RheiaPluginManifest::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    m_name = wxEmptyString;
    m_title = wxEmptyString;
    m_thanks = wxEmptyString;
    m_class = wxEmptyString;

    if( m_description != NULL )
        delete m_description;

    if( m_version != NULL )
        delete m_version;

    if( m_sdkversion != NULL )
        delete m_sdkversion;

    if( m_author != NULL )
        delete m_author;

    m_description = (NULL);
    m_version = (NULL);
    m_sdkversion = (NULL);
    m_author = (NULL);

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("name") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_name = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("title") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_title = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("thanks_to") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_thanks = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("class_of_application") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_class = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("description") ) )
        {
            m_description = new RheiaPackageDescription();
            if( !m_description->DoReadFromNode( child ) )
            {
                delete m_description;
                m_description = NULL;
            }
        }
        else if( cname.IsSameAs( wxT("version") ) )
        {
            m_version = new RheiaPackageVersion();
            if( !m_version->DoReadFromNode( child ) )
            {
                delete m_version;
                m_version = NULL;
            }
        }
        else if( cname.IsSameAs( wxT("sdkversion") ) )
        {
            m_sdkversion = new RheiaPackageVersion();
            if( !m_sdkversion->DoReadFromNode( child ) )
            {
                delete m_sdkversion;
                m_sdkversion = NULL;
            }
        }
        else if( cname.IsSameAs( wxT("author") ) )
        {
            m_author = new RheiaPackageMaintainer();
            if( !m_author->DoReadFromNode( child ) )
            {
                delete m_author;
                m_author = NULL;
            }
        }

        child = child->next;
    }

    if( m_name.IsEmpty() ||
        m_title.IsEmpty() ||
        m_class.IsEmpty() ||
        m_description == NULL ||
        m_version == NULL ||
        m_sdkversion == NULL ||
        m_author == NULL
        )
       return false;

    return true;
}

bool RheiaPluginManifest::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("name") ) ||
            cname.IsSameAs( wxT("title") ) ||
            cname.IsSameAs( wxT("thanks_to") ) ||
            cname.IsSameAs( wxT("class_of_application") ) ||
            cname.IsSameAs( wxT("description") ) ||
            cname.IsSameAs( wxT("version") ) ||
            cname.IsSameAs( wxT("sdkversion") ) ||
            cname.IsSameAs( wxT("author") )
            )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "name" , rxU2C(m_name) );
    xmlNewChild( parent , NULL , (const xmlChar*) "title" , rxU2C(m_title) );
    xmlNewChild( parent , NULL , (const xmlChar*) "thanks_to" , rxU2C(m_thanks) );
    xmlNewChild( parent , NULL , (const xmlChar*) "class_of_application" , rxU2C(m_class) );

    if( m_description != NULL )
    {
        child = xmlNewNode( NULL , (const xmlChar*) "description");
        m_description->DoWriteToNode( child );
        xmlAddChild( parent , child );
    }

    if( m_version != NULL )
    {
        child = xmlNewNode( NULL , (const xmlChar*) "version");
        m_version->DoWriteToNode( child );
        xmlAddChild( parent , child );
    }

    if( m_sdkversion != NULL )
    {
        child = xmlNewNode( NULL , (const xmlChar*) "sdkversion");
        m_sdkversion->DoWriteToNode( child );
        xmlAddChild( parent , child );
    }

    if( m_author != NULL )
    {
        child = xmlNewNode( NULL , (const xmlChar*) "author");
        m_author->DoWriteToNode( child );
        xmlAddChild( parent , child );
    }

    return true;
}

