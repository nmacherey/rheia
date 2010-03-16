/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaPackageInfo.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-October-2009
*/
#include <RheiaPackageInfo.h>
#include <RheiaPackageControl.h>
#include <RheiaPackageManagedFiles.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

RheiaPackageInfo::RheiaPackageInfo():
    m_control(NULL),
    m_files(NULL)
{
}

RheiaPackageInfo::~RheiaPackageInfo()
{
    if( m_control != NULL )
        delete m_control;

    if( m_files != NULL )
        delete m_files;
}

RheiaPackageInfo::RheiaPackageInfo(const RheiaPackageInfo& rhs):
    m_control(NULL),
    m_files(NULL)
{
    if( rhs.m_control != NULL )
        m_control = new RheiaPackageControl( *(rhs.m_control) );

    if( rhs.m_files != NULL )
        m_files = new RheiaPackageManagedFiles( *(rhs.m_files) );
}

RheiaPackageInfo* RheiaPackageInfo::Clone()
{
    return new RheiaPackageInfo(*this);
}

void RheiaPackageInfo::SetControl(RheiaPackageControl* control)
{
    if( m_control != NULL )
        delete m_control;

    m_control = control;
}

void RheiaPackageInfo::SetManagedFiles(RheiaPackageManagedFiles* files)
{
    if( m_files != NULL )
        delete m_files;

    m_files = files;
}

bool RheiaPackageInfo::DoReadFromNode( xmlNode* parent )
{
    xmlNode* child = parent->children;

    if( m_control != NULL )
        delete m_control;

    if( m_files != NULL )
        delete m_files;

    m_control = NULL;
    m_files = NULL;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( wxT("PackageControl") ) )
        {
            m_control = new RheiaPackageControl();
            bool ret = m_control->DoReadFromNode(child);

            if( !ret )
                return false;
        }
        else if( cname.IsSameAs( wxT("Files") ) )
        {
            m_files = new RheiaPackageManagedFiles();
            bool ret = m_files->DoReadFromNode(child);

            if( !ret )
                return false;
        }

        child = child->next;
    }

    if( m_control == NULL ||
       m_files == NULL
       )
       return false;

    return true;
}

bool RheiaPackageInfo::DoWriteToNode( xmlNode* parent )
{
    xmlNode* child = parent->children;
    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );
        xmlNode* sub = child->next;
        if( cname.IsSameAs( wxT("PackageControl") )
           || cname.IsSameAs( wxT("Files") ) )
        {
            xmlReplaceNode(child,NULL);
        }

        child = sub;
    }

    if( m_control != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "PackageControl" );
        m_control->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    if( m_files != NULL )
    {
        child = xmlNewNode(NULL,(const xmlChar*) "Files" );
        m_files->DoWriteToNode(child);
        xmlAddChild(parent,child);
    }

    return true;
}
