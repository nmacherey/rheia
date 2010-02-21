/**
*   @file RheiaPackageManagedFiles.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageManagedFiles.h>
#include <RheiaPackageManagedFile.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageManagedFiles::RheiaPackageManagedFiles()
{
}

RheiaPackageManagedFiles::~RheiaPackageManagedFiles()
{
    RheiaPackageManagedFileMap::iterator it = m_files.begin();

    for( ; it != m_files.end() ; ++it )
        delete it->second;
}

RheiaPackageManagedFiles::RheiaPackageManagedFiles(const RheiaPackageManagedFiles& rhs)
{
    RheiaPackageManagedFileMap deps = rhs.m_files;
    RheiaPackageManagedFileMap::iterator it = deps.begin();

    for( ; it != deps.end() ; ++it )
        m_files[it->first] = it->second->Clone();
}

RheiaPackageManagedFiles* RheiaPackageManagedFiles::Clone()
{
    return new RheiaPackageManagedFiles(*this);
}

RheiaPackageManagedFile* RheiaPackageManagedFiles::FindManagedFile(const wxString& name)
{
    RheiaPackageManagedFileMap::iterator it = m_files.find(name);

    if( it == m_files.end() )
        return NULL;

    return it->second;
}

bool RheiaPackageManagedFiles::Exists(const wxString& name)
{
    RheiaPackageManagedFileMap::iterator it = m_files.find(name);

    if( it == m_files.end() )
        return false;

    return true;
}

bool RheiaPackageManagedFiles::Remove( const wxString& name )
{
    RheiaPackageManagedFileMap::iterator it = m_files.find(name);

    if( it == m_files.end() )
        return false;

    delete it->second;
    m_files.erase(it);

    return true;
}

bool RheiaPackageManagedFiles::Add(const wxString& name, RheiaPackageManagedFile* dep )
{
    RheiaPackageManagedFileMap::iterator it = m_files.find(name);

    if( it != m_files.end() )
        return false;

    m_files[name] = dep;
    return true;
}

void RheiaPackageManagedFiles::Clear()
{
    RheiaPackageManagedFileMap::iterator it = m_files.begin();

    for( ; it != m_files.end() ; ++it )
        delete it->second;

    m_files.clear();
}

bool RheiaPackageManagedFiles::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("File") ) )
        {
            RheiaPackageManagedFile* dep = new RheiaPackageManagedFile();
            bool ret = dep->DoReadFromNode(child);

            if( !ret )
            {
                delete dep;
                return false;
            }
            m_files[dep->GetName()] = dep;

        }
        child = child->next;
    }

    return true;
}

bool RheiaPackageManagedFiles::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;

        if( cname.IsSameAs( wxT("File") ) )
        {
            xmlReplaceNode(child , NULL);
        }

        child = sub;
    }

    RheiaPackageManagedFileMap::iterator it = m_files.begin();
    for( ; it != m_files.end() ; ++it )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "File");
        it->second->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}






