/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageDependency.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageDependency.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageDependency::RheiaPackageDependency():RheiaPackageVersion()
{
}

RheiaPackageDependency::~RheiaPackageDependency()
{
}

RheiaPackageDependency::RheiaPackageDependency(const RheiaPackageDependency& rhs):
    RheiaPackageVersion(rhs),
    m_name( rhs.m_name )
{

}

RheiaPackageDependency* RheiaPackageDependency::Clone()
{
    return new RheiaPackageDependency(*this);
}

bool RheiaPackageDependency::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    m_name = wxEmptyString;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("name") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_name = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("version") ) )
        {
            bool ret = RheiaPackageVersion::DoReadFromNode(child);
            if( !ret )
                return false;
        }

        child = child->next;
    }

    if( m_name.IsEmpty() )
       return false;

    return true;
}

bool RheiaPackageDependency::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("name") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "name" , rxU2C(m_name) );
    child = xmlNewNode(NULL, (const xmlChar*) "version");
    RheiaPackageVersion::DoWriteToNode(child);
    xmlAddChild(parent,child);

    return true;
}


