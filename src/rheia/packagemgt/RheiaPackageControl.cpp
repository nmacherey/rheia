/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageControl.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageControl.h>
#include <RheiaPackageDependency.h>
#include <RheiaPackageDependencies.h>
#include <RheiaPackageVersion.h>
#include <RheiaPackageDescription.h>
#include <RheiaPackageMaintainer.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageControl::RheiaPackageControl():
    m_maintainer(NULL),
    m_version(NULL),
    m_sdkversion(NULL),
    m_dependencies(NULL),
    m_description(NULL)
{
}

RheiaPackageControl::~RheiaPackageControl()
{
    if( m_maintainer != NULL )
        delete m_maintainer;

    if( m_version != NULL )
        delete m_version;

    if( m_sdkversion != NULL )
        delete m_sdkversion;

    if( m_dependencies != NULL )
        delete m_dependencies;

    if( m_description != NULL )
        delete m_description;
}

RheiaPackageControl::RheiaPackageControl(const RheiaPackageControl& rhs):
    m_name(rhs.m_name),
    m_title(rhs.m_title),
    m_archi(rhs.m_archi),
    m_os(rhs.m_os),
    m_category(rhs.m_category),
    m_maintainer(NULL),
    m_version(NULL),
    m_sdkversion(NULL),
    m_dependencies(NULL),
    m_description(NULL)
{
    if( rhs.m_maintainer != NULL )
        m_maintainer = new RheiaPackageMaintainer( *(rhs.m_maintainer) );

    if( rhs.m_version != NULL )
        m_version = new RheiaPackageVersion( *(rhs.m_version) );

    if( rhs.m_sdkversion != NULL )
        m_sdkversion = new RheiaPackageVersion( *(rhs.m_sdkversion) );

    if( rhs.m_dependencies != NULL )
        m_dependencies = new RheiaPackageDependencies( *(rhs.m_dependencies) );

    if( rhs.m_description != NULL )
        m_description = new RheiaPackageDescription( *(rhs.m_description) );
}

RheiaPackageControl* RheiaPackageControl::Clone()
{
    return new RheiaPackageControl(*this);
}

void RheiaPackageControl::SetMaintainer(RheiaPackageMaintainer* maintainer)
{
    if( m_maintainer != NULL )
        delete m_maintainer;

    m_maintainer = maintainer;
}

void RheiaPackageControl::SetVersion(RheiaPackageVersion* version)
{
    if( m_version != NULL )
        delete m_version;

    m_version = version;
}

void RheiaPackageControl::SetSDKVersion(RheiaPackageVersion* sdkversion)
{
    if( m_sdkversion != NULL )
        delete m_sdkversion;

    m_sdkversion = sdkversion;
}

void RheiaPackageControl::SetDependencies(RheiaPackageDependencies* dependencies)
{
    if( m_dependencies != NULL )
        delete m_dependencies;

    m_dependencies = dependencies;
}

void RheiaPackageControl::SetDescription(RheiaPackageDescription* description)
{
    if( m_description != NULL )
        delete m_description;

    m_description = description;
}

bool RheiaPackageControl::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    if( m_maintainer != NULL )
        delete m_maintainer;

    if( m_version != NULL )
        delete m_version;

    if( m_sdkversion != NULL )
        delete m_sdkversion;

    if( m_dependencies != NULL )
        delete m_dependencies;

    if( m_description != NULL )
        delete m_description;

    m_maintainer = NULL;
    m_version = NULL;
    m_sdkversion = NULL;
    m_dependencies = NULL;
    m_description = NULL;
    m_shlibs.Clear();

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
        else if( cname.IsSameAs( wxT("architecture") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_archi = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("os") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_os = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("category") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_category = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("maintainer") ) )
        {
            m_maintainer = new RheiaPackageMaintainer();
            bool ret = m_maintainer->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("version") ) )
        {
            m_version = new RheiaPackageVersion();
            bool ret = m_version->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("sdkversion") ) )
        {
            m_sdkversion = new RheiaPackageVersion();
            bool ret = m_sdkversion->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("dependencies") ) )
        {
            m_dependencies = new RheiaPackageDependencies();
            bool ret = m_dependencies->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("description") ) )
        {
            m_description = new RheiaPackageDescription();
            bool ret = m_description->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("shared_libraries") ) )
        {
            xmlNode* sub = child->children;

            while( sub != NULL )
            {
                wxString sname = RheiaC2U( (const char*) sub->name );

                if( sname.IsSameAs( wxT("shared") ) )
                {
                    xmlChar* content = xmlNodeGetContent(sub);
                    wxString str = RheiaC2U((const char*) content);
                    xmlFree(content);

                    m_shlibs.Add( str );
                }

                sub = sub->next;
            }
        }
        child = child->next;
    }

    if( m_name.IsEmpty() ||
       m_title.IsEmpty() ||
       m_archi.IsEmpty() ||
       m_os.IsEmpty() ||
       m_category.IsEmpty() ||
       m_maintainer == NULL ||
       m_version == NULL ||
       m_sdkversion == NULL ||
       m_dependencies == NULL ||
       m_description == NULL
       )
       return false;

    return true;
}

bool RheiaPackageControl::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;
    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;
        if( cname.IsSameAs( wxT("name") )
           || cname.IsSameAs( wxT("title") )
           || cname.IsSameAs( wxT("architecture") )
           || cname.IsSameAs( wxT("os") )
           || cname.IsSameAs( wxT("category") )
           || cname.IsSameAs( wxT("maintainer") )
           || cname.IsSameAs( wxT("version") )
           || cname.IsSameAs( wxT("sdkversion") )
           || cname.IsSameAs( wxT("dependencies") )
           || cname.IsSameAs( wxT("description") )
           || cname.IsSameAs( wxT("shared_libraries") ) )
        {
            xmlReplaceNode(child,NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "name" , rxU2C(m_name) );
    xmlNewChild( parent , NULL , (const xmlChar*) "title" , rxU2C(m_title) );
    xmlNewChild( parent , NULL , (const xmlChar*) "architecture" , rxU2C(m_archi) );
    xmlNewChild( parent , NULL , (const xmlChar*) "os" , rxU2C(m_os) );
    xmlNewChild( parent , NULL , (const xmlChar*) "category" , rxU2C(m_category) );

    if( m_maintainer != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "maintainer" );
        m_maintainer->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_version != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "version" );
        m_version->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_sdkversion != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "sdkversion" );
        m_sdkversion->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_dependencies != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "dependencies" );
        m_dependencies->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_description != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "description" );
        m_description->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    // Now write shared libraries
    if( m_shlibs.GetCount() > 0 )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "shared_libraries" );

        for( unsigned int i = 0; i < m_shlibs.GetCount() ; ++i )
            xmlNewChild( child , NULL , (const xmlChar*) "shared" , rxU2C(m_shlibs[i]) );

        xmlAddChild(parent,child);
    }

    return true;
}

