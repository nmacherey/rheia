/**
*   @file RheiaPackageMaintainer.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageMaintainer.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageMaintainer::RheiaPackageMaintainer()
{
}

RheiaPackageMaintainer::~RheiaPackageMaintainer()
{
}

RheiaPackageMaintainer::RheiaPackageMaintainer(const RheiaPackageMaintainer& rhs):
    m_name(rhs.m_name),
    m_address(rhs.m_address),
    m_zipcode(rhs.m_zipcode),
    m_town(rhs.m_town),
    m_country(rhs.m_country),
    m_phone(rhs.m_phone),
    m_fax(rhs.m_fax),
    m_email(rhs.m_email),
    m_website(rhs.m_website)
{

}

RheiaPackageMaintainer* RheiaPackageMaintainer::Clone()
{
    return new RheiaPackageMaintainer(*this);
}

bool RheiaPackageMaintainer::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    m_name = wxEmptyString;
    m_address = wxEmptyString;
    m_zipcode = wxEmptyString;
    m_town = wxEmptyString;
    m_country = wxEmptyString;
    m_phone = wxEmptyString;
    m_fax = wxEmptyString;
    m_email = wxEmptyString;
    m_website = wxEmptyString;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("name") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_name = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("address") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_address = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("zipcode") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_zipcode = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("town") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_town = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("country") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_country = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("phone") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_phone = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("fax") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_fax = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("email") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_email = RheiaC2U((const char*) content);
            xmlFree(content);
        }
        else if( cname.IsSameAs( wxT("website") ) )
        {
            xmlChar* content = xmlNodeGetContent(child);
            m_website = RheiaC2U((const char*) content);
            xmlFree(content);
        }

        child = child->next;
    }

    if( m_name.IsEmpty() ||
       m_address.IsEmpty() ||
       m_zipcode.IsEmpty() ||
       m_town.IsEmpty() ||
       m_country.IsEmpty() ||
       m_phone.IsEmpty() ||
       m_fax.IsEmpty() ||
       m_email.IsEmpty() ||
       m_website.IsEmpty()
       )
       return false;

    return true;
}

bool RheiaPackageMaintainer::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("name") )
           || cname.IsSameAs( wxT("address") )
           || cname.IsSameAs( wxT("zipcode") )
           || cname.IsSameAs( wxT("town") )
           || cname.IsSameAs( wxT("country") )
           || cname.IsSameAs( wxT("phone") )
           || cname.IsSameAs( wxT("fax") )
           || cname.IsSameAs( wxT("email") )
           || cname.IsSameAs( wxT("website") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    xmlNewChild( parent , NULL , (const xmlChar*) "name" , rxU2C(m_name) );
    xmlNewChild( parent , NULL , (const xmlChar*) "address" , rxU2C(m_address) );
    xmlNewChild( parent , NULL , (const xmlChar*) "zipcode" , rxU2C(m_zipcode) );
    xmlNewChild( parent , NULL , (const xmlChar*) "town" , rxU2C(m_town) );
    xmlNewChild( parent , NULL , (const xmlChar*) "country" , rxU2C(m_country) );
    xmlNewChild( parent , NULL , (const xmlChar*) "phone" , rxU2C(m_phone) );
    xmlNewChild( parent , NULL , (const xmlChar*) "fax" , rxU2C(m_fax) );
    xmlNewChild( parent , NULL , (const xmlChar*) "email" , rxU2C(m_email) );
    xmlNewChild( parent , NULL , (const xmlChar*) "website" , rxU2C(m_website) );

    return true;
}
