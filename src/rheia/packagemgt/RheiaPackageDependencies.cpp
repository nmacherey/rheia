/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageDependencies.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageDependencies.h>
#include <RheiaPackageDependency.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageDependencies::RheiaPackageDependencies()
{
}

RheiaPackageDependencies::~RheiaPackageDependencies()
{
    RheiaPackageDependencyMap::iterator it = m_dependencies.begin();

    for( ; it != m_dependencies.end() ; ++it )
        delete it->second;
}

RheiaPackageDependencies::RheiaPackageDependencies(const RheiaPackageDependencies& rhs)
{
    RheiaPackageDependencyMap deps = rhs.m_dependencies;
    RheiaPackageDependencyMap::iterator it = deps.begin();

    for( ; it != deps.end() ; ++it )
        m_dependencies[it->first] = it->second->Clone();
}

RheiaPackageDependencies* RheiaPackageDependencies::Clone()
{
    return new RheiaPackageDependencies(*this);
}

RheiaPackageDependency* RheiaPackageDependencies::FindDependency(const wxString& name)
{
    RheiaPackageDependencyMap::iterator it = m_dependencies.find(name);

    if( it == m_dependencies.end() )
        return NULL;

    return it->second;
}

bool RheiaPackageDependencies::Exists(const wxString& name)
{
    RheiaPackageDependencyMap::iterator it = m_dependencies.find(name);

    if( it == m_dependencies.end() )
        return false;

    return true;
}

bool RheiaPackageDependencies::Remove( const wxString& name )
{
    RheiaPackageDependencyMap::iterator it = m_dependencies.find(name);

    if( it == m_dependencies.end() )
        return false;

    delete it->second;
    m_dependencies.erase(it);

    return true;
}

bool RheiaPackageDependencies::Add(const wxString& name, RheiaPackageDependency* dep )
{
    RheiaPackageDependencyMap::iterator it = m_dependencies.find(name);

    if( it != m_dependencies.end() )
        return false;

    m_dependencies[name] = dep;
    return true;
}

void RheiaPackageDependencies::Clear()
{
    RheiaPackageDependencyMap::iterator it = m_dependencies.begin();

    for( ; it != m_dependencies.end() ; ++it )
        delete it->second;

    m_dependencies.clear();
}

bool RheiaPackageDependencies::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("Dependency") ) )
        {
            RheiaPackageDependency* dep = new RheiaPackageDependency();
            bool ret = dep->DoReadFromNode(child);

            if( !ret )
            {
                delete dep;
                return false;
            }
            m_dependencies[dep->GetName()] = dep;

        }
        child = child->next;
    }

    return true;
}

bool RheiaPackageDependencies::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("Dependency") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    RheiaPackageDependencyMap::iterator it = m_dependencies.begin();
    for( ; it != m_dependencies.end() ; ++it )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Dependency");
        it->second->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}




