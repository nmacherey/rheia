/**
*   @file RheiaPackageLibs.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageLibs.h>
#include <RheiaPackageLib.h>
#include <RheiaPackageFile.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageLibs::RheiaPackageLibs()
{
}

RheiaPackageLibs::~RheiaPackageLibs()
{
    RheiaPackageLibMap::iterator it = m_libs.begin();

    for( ; it != m_libs.end() ; ++it )
        delete it->second;
}

RheiaPackageLibs::RheiaPackageLibs(const RheiaPackageLibs& rhs)
{
    RheiaPackageLibMap deps = rhs.m_libs;
    RheiaPackageLibMap::iterator it = deps.begin();

    for( ; it != deps.end() ; ++it )
        m_libs[it->first] = it->second->Clone();
}

RheiaPackageLibs* RheiaPackageLibs::Clone()
{
    return new RheiaPackageLibs(*this);
}

RheiaPackageLib* RheiaPackageLibs::FindLib(const wxString& name)
{
    RheiaPackageLibMap::iterator it = m_libs.find(name);

    if( it == m_libs.end() )
        return NULL;

    return it->second;
}

bool RheiaPackageLibs::Exists(const wxString& name)
{
    RheiaPackageLibMap::iterator it = m_libs.find(name);

    if( it == m_libs.end() )
        return false;

    return true;
}

bool RheiaPackageLibs::Remove( const wxString& name )
{
    RheiaPackageLibMap::iterator it = m_libs.find(name);

    if( it == m_libs.end() )
        return false;

    delete it->second;
    m_libs.erase(it);

    return true;
}

bool RheiaPackageLibs::Add(const wxString& name, RheiaPackageLib* dep )
{
    RheiaPackageLibMap::iterator it = m_libs.find(name);

    if( it != m_libs.end() )
        return false;

    m_libs[name] = dep;
    return true;
}

void RheiaPackageLibs::Clear()
{
    RheiaPackageLibMap::iterator it = m_libs.begin();

    for( ; it != m_libs.end() ; ++it )
        delete it->second;

    m_libs.clear();
}

bool RheiaPackageLibs::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("Lib") ) )
        {
            RheiaPackageLib* dep = new RheiaPackageLib();
            bool ret = dep->DoReadFromNode(child);

            if( !ret )
            {
                delete dep;
                return false;
            }
            m_libs[dep->GetFile()->GetName()] = dep;

        }
        child = child->next;
    }

    return true;
}

bool RheiaPackageLibs::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("Lib") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    RheiaPackageLibMap::iterator it = m_libs.begin();
    for( ; it != m_libs.end() ; ++it )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Lib");
        it->second->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}





