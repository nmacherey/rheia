/**
*   @file RheiaPackageVersion.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageVersion.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageVersion::RheiaPackageVersion()
{
}

RheiaPackageVersion::~RheiaPackageVersion()
{
}

RheiaPackageVersion::RheiaPackageVersion(const RheiaPackageVersion& rhs):
    m_major(rhs.m_major),
    m_minor(rhs.m_minor),
    m_build(rhs.m_build)
{

}

RheiaPackageVersion* RheiaPackageVersion::Clone()
{
    return new RheiaPackageVersion(*this);
}

bool RheiaPackageVersion::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    m_major = -1;
    m_minor = -1;
    m_build = -1;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("Major") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            wxString str = RheiaC2U((const char*) content);
            str.ToLong( &m_major );
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("Minor") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            wxString str = RheiaC2U((const char*) content);
            str.ToLong( &m_minor );
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("Build") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            wxString str = RheiaC2U((const char*) content);
            str.ToLong( &m_build );
            xmlFree(content);
        }

        child = child->next;
    }

    if( m_major == -1 ||
       m_minor == -1 ||
       m_build == -1
       )
       return false;

    return true;
}

bool RheiaPackageVersion::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("Major") )
           || cname.IsSameAs( wxT("Minor") )
           || cname.IsSameAs( wxT("Build") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "Major" , rxU2C(wxString::Format(wxT("%d"),m_major)) );
    xmlNewChild( parent , NULL , (const xmlChar*) "Minor" , rxU2C(wxString::Format(wxT("%d"),m_minor)) );
    xmlNewChild( parent , NULL , (const xmlChar*) "Build" , rxU2C(wxString::Format(wxT("%d"),m_build)) );

    return true;
}

