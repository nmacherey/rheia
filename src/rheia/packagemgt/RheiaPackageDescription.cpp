/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageDescription.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageDescription.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageDescription::RheiaPackageDescription()
{
}

RheiaPackageDescription::~RheiaPackageDescription()
{
}

RheiaPackageDescription::RheiaPackageDescription(const RheiaPackageDescription& rhs):
    m_short( rhs.m_short ),
    m_full( rhs.m_full )
{

}

RheiaPackageDescription* RheiaPackageDescription::Clone()
{
    return new RheiaPackageDescription(*this);
}

bool RheiaPackageDescription::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    m_short = wxEmptyString;
    m_full = wxEmptyString;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("short") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_short = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("full") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_full = RheiaC2U((const char*) content);
            xmlFree(content);
        }

        child = child->next;
    }

    if( m_short.IsEmpty() || m_full.IsEmpty() )
       return false;

    return true;
}

bool RheiaPackageDescription::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("short") ) || cname.IsSameAs( wxT("full") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "short" , rxU2C(m_short) );
    xmlNewChild( parent , NULL , (const xmlChar*) "full" , rxU2C(m_full) );

    return true;
}



