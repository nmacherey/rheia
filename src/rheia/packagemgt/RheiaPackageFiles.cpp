/**
*   @file RheiaPackageFiles.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageFiles.h>
#include <RheiaPackageFile.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageFiles::RheiaPackageFiles()
{
}

RheiaPackageFiles::~RheiaPackageFiles()
{
    RheiaPackageFileMap::iterator it = m_files.begin();

    for( ; it != m_files.end() ; ++it )
        delete it->second;
}

RheiaPackageFiles::RheiaPackageFiles(const RheiaPackageFiles& rhs)
{
    RheiaPackageFileMap deps = rhs.m_files;
    RheiaPackageFileMap::iterator it = deps.begin();

    for( ; it != deps.end() ; ++it )
        m_files[it->first] = it->second->Clone();
}

RheiaPackageFiles* RheiaPackageFiles::Clone()
{
    return new RheiaPackageFiles(*this);
}

RheiaPackageFile* RheiaPackageFiles::FindFile(const wxString& name)
{
    RheiaPackageFileMap::iterator it = m_files.find(name);

    if( it == m_files.end() )
        return NULL;

    return it->second;
}

bool RheiaPackageFiles::Exists(const wxString& name)
{
    RheiaPackageFileMap::iterator it = m_files.find(name);

    if( it == m_files.end() )
        return false;

    return true;
}

bool RheiaPackageFiles::Remove( const wxString& name )
{
    RheiaPackageFileMap::iterator it = m_files.find(name);

    if( it == m_files.end() )
        return false;

    delete it->second;
    m_files.erase(it);

    return true;
}

bool RheiaPackageFiles::Add(const wxString& name, RheiaPackageFile* dep )
{
    RheiaPackageFileMap::iterator it = m_files.find(name);

    if( it != m_files.end() )
        return false;

    m_files[name] = dep;
    return true;
}

void RheiaPackageFiles::Clear()
{
    RheiaPackageFileMap::iterator it = m_files.begin();

    for( ; it != m_files.end() ; ++it )
        delete it->second;

    m_files.clear();
}

bool RheiaPackageFiles::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("File") ) )
        {
            RheiaPackageFile* dep = new RheiaPackageFile();
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

bool RheiaPackageFiles::DoWriteToNode( xmlNode* parent )
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

    RheiaPackageFileMap::iterator it = m_files.begin();
    for( ; it != m_files.end() ; ++it )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "File");
        it->second->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}





