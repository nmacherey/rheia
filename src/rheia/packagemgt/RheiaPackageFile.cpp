/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageFile.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageFile.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageFile::RheiaPackageFile():remove(false)
{
}

RheiaPackageFile::~RheiaPackageFile()
{
}

RheiaPackageFile::RheiaPackageFile(const RheiaPackageFile& rhs):
    m_name( rhs.m_name ),
    m_path( rhs.m_path ),
    m_type( rhs.m_type ),
    remove( rhs.remove )
{

}

RheiaPackageFile* RheiaPackageFile::Clone()
{
    return new RheiaPackageFile(*this);
}

bool RheiaPackageFile::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    m_name = wxEmptyString;
    m_path = wxEmptyString;
    m_type = wxEmptyString;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("name") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_name = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("type") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_type = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("path") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_path = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("remove") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            remove = RheiaC2U((const char*) content).IsSameAs(wxT("true"));
            xmlFree(content);
        }

        child = child->next;
    }

    if( m_name.IsEmpty() || m_path.IsEmpty()  || m_type.IsEmpty() )
       return false;

    return true;
}

bool RheiaPackageFile::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("name") ) ||
            cname.IsSameAs( wxT("type") ) ||
            cname.IsSameAs( wxT("remove") ) ||
            cname.IsSameAs( wxT("path") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "name" , rxU2C(m_name) );
    xmlNewChild( parent , NULL , (const xmlChar*) "type" , rxU2C(m_type) );
    xmlNewChild( parent , NULL , (const xmlChar*) "path" , rxU2C(m_path) );
    xmlNewChild( parent , NULL , (const xmlChar*) "remove" , (const xmlChar*) (const char*) (remove ? "true" : "false") );

    return true;
}




