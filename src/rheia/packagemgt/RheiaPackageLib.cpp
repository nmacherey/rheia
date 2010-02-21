/**
*   @file RheiaPackageLib.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageLib.h>
#include <RheiaPackageDependency.h>
#include <RheiaPackageDependencies.h>
#include <RheiaPackageVersion.h>
#include <RheiaPackageFile.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageLib::RheiaPackageLib():
    m_version(NULL),
    m_dependencies(NULL),
    m_file(NULL)
{
}

RheiaPackageLib::~RheiaPackageLib()
{
    if( m_version != NULL )
        delete m_version;

    if( m_dependencies != NULL )
        delete m_dependencies;

    if( m_file != NULL )
        delete m_file;
}

RheiaPackageLib::RheiaPackageLib(const RheiaPackageLib& rhs):
    m_version(NULL),
    m_dependencies(NULL),
    m_file(NULL)
{
    if( rhs.m_version != NULL )
        m_version = new RheiaPackageVersion( *(rhs.m_version) );

    if( rhs.m_dependencies != NULL )
        m_dependencies = new RheiaPackageDependencies( *(rhs.m_dependencies) );

    if( rhs.m_file != NULL )
        m_file = new RheiaPackageFile( *(rhs.m_file) );
}

RheiaPackageLib* RheiaPackageLib::Clone()
{
    return new RheiaPackageLib(*this);
}

void RheiaPackageLib::SetVersion(RheiaPackageVersion* version)
{
    if( m_version != NULL )
        delete m_version;

    m_version = version;
}

void RheiaPackageLib::SetDependencies(RheiaPackageDependencies* dependencies)
{
    if( m_dependencies != NULL )
        delete m_dependencies;

    m_dependencies = dependencies;
}

void RheiaPackageLib::SetFile(RheiaPackageFile* file)
{
    if( m_file != NULL )
        delete m_file;

    m_file = file;
}

bool RheiaPackageLib::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    if( m_version != NULL )
        delete m_version;

    if( m_dependencies != NULL )
        delete m_dependencies;

    if( m_file != NULL )
        delete m_file;

    m_version = NULL;
    m_dependencies = NULL;
    m_file = NULL;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("Version") ) )
        {
            m_version = new RheiaPackageVersion();
            bool ret = m_version->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("Dependencies") ) )
        {
            m_dependencies = new RheiaPackageDependencies();
            bool ret = m_dependencies->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("File") ) )
        {
            m_file = new RheiaPackageFile();
            bool ret = m_file->DoReadFromNode(child);

            if( !ret )
                return false;
        }

        child = child->next;
    }

    if( m_version == NULL ||
       m_dependencies == NULL ||
       m_file == NULL
       )
       return false;

    return true;
}

bool RheiaPackageLib::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;
    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;
        if( cname.IsSameAs( wxT("Version") )
           || cname.IsSameAs( wxT("Dependencies") )
           || cname.IsSameAs( wxT("File") ) )
        {
            xmlReplaceNode(child,NULL);
        }

        child = sub;
    }

    if( m_version != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Version" );
        m_version->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_dependencies != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Dependencies" );
        m_dependencies->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_file != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "File" );
        m_file->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}

