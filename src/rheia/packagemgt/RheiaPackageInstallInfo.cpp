/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageInstallInfo.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @Libs 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageInstallInfo.h>
#include <RheiaPackageFiles.h>
#include <RheiaPackageLibs.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageInstallInfo::RheiaPackageInstallInfo():
    m_files(NULL),
    m_libs(NULL)
{
}

RheiaPackageInstallInfo::~RheiaPackageInstallInfo()
{
    if( m_files != NULL )
        delete m_files;

    if( m_libs != NULL )
        delete m_libs;
}

RheiaPackageInstallInfo::RheiaPackageInstallInfo(const RheiaPackageInstallInfo& rhs):
    m_files(NULL),
    m_libs(NULL)
{
    if( rhs.m_files != NULL )
        m_files = new RheiaPackageFiles( *(rhs.m_files) );

    if( rhs.m_libs != NULL )
        m_libs = new RheiaPackageLibs( *(rhs.m_libs) );
}

RheiaPackageInstallInfo* RheiaPackageInstallInfo::Clone()
{
    return new RheiaPackageInstallInfo(*this);
}

void RheiaPackageInstallInfo::SetFiles(RheiaPackageFiles* files)
{
    if( m_files != NULL )
        delete m_files;

    m_files = files;
}

void RheiaPackageInstallInfo::SetLibs(RheiaPackageLibs* libs)
{
    if( m_libs != NULL )
        delete m_libs;

    m_libs = libs;
}

bool RheiaPackageInstallInfo::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    if( m_files != NULL )
        delete m_files;

    if( m_libs != NULL )
        delete m_libs;
    m_files = NULL;
    m_libs = NULL;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("Files") ) )
        {
            m_files = new RheiaPackageFiles();
            bool ret = m_files->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("Libs") ) )
        {
            m_libs = new RheiaPackageLibs();
            bool ret = m_libs->DoReadFromNode(child);

            if( !ret )
                return false;
        }

        child = child->next;
    }

    if( m_files == NULL ||
       m_libs == NULL
       )
       return false;

    return true;
}

bool RheiaPackageInstallInfo::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;
    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;
        if( cname.IsSameAs( wxT("Files") )
           || cname.IsSameAs( wxT("Libs") ) )
        {
            xmlReplaceNode(child,NULL);
        }

        child = sub;
    }

    if( m_files != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Files" );
        m_files->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_libs != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Libs" );
        m_libs->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}

