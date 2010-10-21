/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaConfigurationManager.cpp
*
*   Revision : 18-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries and Reoganization
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaConfigurationManager.h>

#include <map>

#include <RheiaManager.h>
#include <RheiaToolBarManager.h>
#include <RheiaPersonalityManager.h>
#include <RheiaConfigurationPanel.h>
#include <RheiaConfigurationPattern.h>
#include <RheiaPlatform.h>
#include <RheiaException.h>
#include <RheiaXmlManager.h>
#include <RheiaInfoWindow.h>
#include <RheiaStandardPaths.h>
#include <RheiaGlobals.h>

#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

#include <wx/url.h>
#include <wx/dir.h>
#include <wx/filesys.h>
#include <wx/intl.h>
#include <wx/menu.h>
#include <wx/string.h>
#include <wx/dynlib.h>
#include <wx/filesys.h>
#include <wx/progdlg.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <wx/msgdlg.h>
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/stdpaths.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <sys/param.h>
#include <mach-o/dyld.h>
#endif

#ifdef __WXMAC__
#include "wx/osx/core/cfstring.h"
#include "wx/intl.h"

#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFURL.h>
#endif

bool RheiaConfigurationManager::m_reload = false;

/**
*	@namespace ConfigManagerPaths
*	ConfigManagerPaths is the basic namespace containing the path of the different basic xml
*	configuration components and nodes
*/
namespace ConfigManagerPaths
{
    /****************************************************************************************************
    * default m_root nodes and attributes
    ****************************************************************************************************/

    static wxString PositionNode							= wxT("position");
    static wxString SizeNode								= wxT("size");

    /****************************************************************************************************
    * layout manager m_root nodes and attributes
    ****************************************************************************************************/
    static wxString SashSize								=	wxT("SashSize");
    static wxString CaptionSize								=	wxT("CaptionSize");
    static wxString GripperSize								=	wxT("GripperSize");
    static wxString PaneBorderSize						    =	wxT("PaneBorderSize");
    static wxString PaneButtonSize						    =	wxT("PaneButtonSize");

    static wxString ActiveCaptionColor						=	wxT("ActiveCaptionColour");
    static wxString ActiveCaptionGradientColor				=	wxT("ActiveCaptionGradientColour");
    static wxString ActiveCaptionTextColor					=	wxT("ActiveCaptionTextColour");
    static wxString InactiveCaptionColor					=	wxT("InactiveCaptionColour");
    static wxString InactiveCaptionGradientColor			=	wxT("InactiveCaptionGradientColour");
    static wxString InactiveCaptionTextColor				=	wxT("InactiveCaptionTextColour");
    static wxString GripperColor							=	wxT("GripperColour");

    /* Layout information in the main frame */
    static wxString Layout								    =	wxT("Layout");
    namespace LayoutAttributes
    {
        static wxString LayoutName						    =	wxT("name");
    };

    /* default layout elements */
    static wxString Perspective								=   wxT("Perspective");
    static wxString StatusBar								=	wxT("HasStatusBar");
    static wxString FullScreen								=	wxT("IsFullScreen");
    static wxString Maximized								=	wxT("IsMaximized");
};


RheiaConfigurationManager::RheiaConfigurationManager(xmlDoc *doc, xmlNode *root) : m_doc( doc ), m_root( root )
{
}

RheiaConfigurationManager::RheiaConfigurationManager():m_doc(NULL),m_root(NULL)
{
    xmlInitParser();
    /* Create xpath evaluation context */
    xmlXPathInit();

}

RheiaConfigurationManager::~RheiaConfigurationManager()
{

}

void RheiaConfigurationManager::Delete()
{
    if( m_root == NULL || m_doc == NULL )
        return;

    RheiaConfigurationPattern * builder = RheiaConfigurationPattern::Get();
    wxString group = RheiaC2U( (const char*) m_root->name );

    xmlNode* docRoot = xmlDocGetRootElement(m_doc);
    xmlNode* child = docRoot->children;

    while( child != NULL )
    {
        wxString cname = RheiaC2U( (const char*) child->name );

        if( cname.IsSameAs( group ) )
        {
            xmlReplaceNode( child , NULL );
            return;
        }

        child = child->next;
    }

    wxCriticalSectionLocker(builder->m_criticalSection);
    RheiaConfigurationManagerMap::iterator it = builder->m_groups.find(group);
    if(it != builder->m_groups.end())
        builder->m_groups.erase(it);

    delete this;
}

void RheiaConfigurationManager::Clear()
{
    if( m_root == NULL )
        return;

    xmlNode* child = m_root->children;

    while( child != NULL )
    {
        xmlNode* sub = child->next;
        xmlReplaceNode( child , NULL );
        child = sub;
    }
}

void RheiaConfigurationManager::Delete( const wxString& path )
{
    wxString key(path);
    xmlNode* node;
    node = RheiaXmlManager::Get()->AssertPath(key,m_root);
    xmlNode* e = RheiaXmlManager::Get()->GetUniqElement( node , key );
    xmlReplaceNode( e , NULL );
}


void RheiaConfigurationManager::Write(const wxString& path,  const wxString& value, bool ignoreEmpty)
{
    RheiaXmlManager::Get()->Write( path , value , m_root , ignoreEmpty );
}

void RheiaConfigurationManager::Write(const wxString& path, const char* str)
{
    RheiaXmlManager::Get()->Write(path, RheiaC2U(str), m_root, false);
};

wxString RheiaConfigurationManager::Read(const wxString& path, const wxString& defaultVal)
{
    return RheiaXmlManager::Get()->Read(path, m_root,  defaultVal);
}

bool RheiaConfigurationManager::DoRead(const wxString& path, wxString* str )
{
    return RheiaXmlManager::Get()->Read( path , str , m_root );
}

void RheiaConfigurationManager::Write(const wxString& path, const wxColour& c)
{
    RheiaXmlManager::Get()->Write( path , m_root, c );
}

wxColour RheiaConfigurationManager::ReadColour(const wxString& path, const wxColour& defaultVal)
{
    wxColour ret;

    if (DoRead(path, &ret))
        return ret;
    else
        return defaultVal;
}

bool RheiaConfigurationManager::DoRead(const wxString& path, wxColour* ret)
{
    return RheiaXmlManager::Get()->Read( path , m_root , ret );
}

void RheiaConfigurationManager::Write(const wxString& path, int value)
{
    RheiaXmlManager::Get()->Write( path , m_root, value );
}

int  RheiaConfigurationManager::ReadInt(const wxString& path, int defaultVal)
{
    return RheiaXmlManager::Get()->ReadInt( path , m_root , defaultVal );
}

bool RheiaConfigurationManager::DoRead(const wxString& path, int* value)
{
    return RheiaXmlManager::Get()->Read( path , m_root , value );
}

void RheiaConfigurationManager::Write(const wxString& path, bool value)
{
    RheiaXmlManager::Get()->Write( path , m_root , value );
}

bool  RheiaConfigurationManager::ReadBool(const wxString& path, bool defaultVal)
{
    bool ret;

    if (DoRead(path, &ret))
        return ret;
    else
        return defaultVal;
}

bool RheiaConfigurationManager::DoRead(const wxString& path, bool* value)
{
    return RheiaXmlManager::Get()->Read( path , m_root , value );
}

void RheiaConfigurationManager::Write(const wxString& path,  double value)
{
    RheiaXmlManager::Get()->Write( path , m_root , value );
}

double  RheiaConfigurationManager::ReadDouble(const wxString& path, double defaultVal)
{
    double ret;

    if (DoRead(path, &ret))
        return ret;
    else
        return defaultVal;
}

bool RheiaConfigurationManager::DoRead(const wxString& path, double* value)
{
    return RheiaXmlManager::Get()->Read( path , m_root , value );
}

void RheiaConfigurationManager::Write(const wxString& path, const wxArrayString& arrayString)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayString );
}

void RheiaConfigurationManager::DoRead(const wxString& path, wxArrayString *arrayString)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayString );
}

wxArrayString RheiaConfigurationManager::ReadArrayString(const wxString& path)
{
    wxArrayString as;
    DoRead(path, &as);
    return as;
}

void RheiaConfigurationManager::Write(const wxString& path,  const wxArrayInt& arrayInt)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayInt );
}

void RheiaConfigurationManager::DoRead(const wxString& path, wxArrayInt *arrayInt)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayInt );
}

wxArrayInt RheiaConfigurationManager::ReadArrayInt(const wxString& path)
{
    wxArrayInt ai;
    DoRead(path, &ai);
    return ai;
}

void RheiaConfigurationManager::Write(const wxString& path, const wxArrayDouble& arrayDouble)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayDouble );
}

void RheiaConfigurationManager::DoRead(const wxString& path, wxArrayDouble *arrayDouble)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayDouble );
}

wxArrayDouble RheiaConfigurationManager::ReadArrayDouble(const wxString& path)
{
    wxArrayDouble ad;
    DoRead(path, &ad);
    return ad;
}

void RheiaConfigurationManager::Write(const wxString& path, const wxArrayBool& arrayBool)
{
    RheiaXmlManager::Get()->Write( path , m_root,  arrayBool );
}

void RheiaConfigurationManager::DoRead(const wxString& path, wxArrayBool *arrayBool)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayBool );
}

wxArrayBool RheiaConfigurationManager::ReadArrayBool(const wxString& path)
{
    wxArrayBool ab;
    DoRead(path, &ab);
    return ab;
}

void RheiaConfigurationManager::Write(const wxString& path, const std::vector<bool>& arrayBool)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayBool );
}

void RheiaConfigurationManager::DoRead(const wxString& path, std::vector<bool> *arrayBool)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayBool );
}

std::vector<bool> RheiaConfigurationManager::ReadStdArrayBool(const wxString& path)
{
    std::vector<bool> ab;
    DoRead(path, &ab);
    return ab;
}

void RheiaConfigurationManager::Write(const wxString& path, const std::vector<double>& arrayDouble)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayDouble );
}

void RheiaConfigurationManager::DoRead(const wxString& path, std::vector<double> *arrayDouble)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayDouble );
}

std::vector<double> RheiaConfigurationManager::ReadStdArrayDouble(const wxString& path)
{
    std::vector<double> ad;
    DoRead(path, &ad);
    return ad;
}

void RheiaConfigurationManager::Write(const wxString& path, const std::vector<int>& arrayInt)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayInt );
}

void RheiaConfigurationManager::DoRead(const wxString& path, std::vector<int> *arrayInt)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayInt );
}

std::vector<int> RheiaConfigurationManager::ReadStdArrayInt(const wxString& path)
{
    std::vector<int> ai;
    DoRead(path, &ai);
    return ai;
}

void RheiaConfigurationManager::Write(const wxString& path, const std::vector<std::string>& arrayString)
{
    RheiaXmlManager::Get()->Write( path , m_root, arrayString );
}

void RheiaConfigurationManager::DoRead(const wxString& path, std::vector<std::string> *arrayString)
{
    RheiaXmlManager::Get()->Read( path , m_root, arrayString );
}

std::vector<std::string> RheiaConfigurationManager::ReadStdArrayString(const wxString& path)
{
    std::vector<std::string> as;
    DoRead(path, &as);
    return as;
}

void RheiaConfigurationManager::Write(const wxString& path,  const RheiaStringStringMap& as)
{
    wxString key(path);
    xmlNode* node;
    node = RheiaXmlManager::Get()->AssertPath(key,m_root);
    xmlNode* e = RheiaXmlManager::Get()->GetUniqElement( node , key );

    /* First check if the node exist */
    xmlNode *child = e->children;
    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char *) child->name );
        xmlNode* sub = child->next;
        if ( ChildName.IsSameAs( wxT("variable") ) )
        {
            xmlReplaceNode( child , NULL );
            child = NULL;
        }
        child = sub;
    }

    RheiaStringStringMap::const_iterator it = as.begin();
    for( ; it != as.end() ; ++it )
    {
        child = xmlNewNode( NULL , (const xmlChar*) "variable" );
        xmlNewChild(child , NULL , (const xmlChar*) "name" , rxU2C(it->first) );
        xmlNewChild(child , NULL , (const xmlChar*) "value" , rxU2C(it->second) );
        xmlAddChild( e , child );
    }
}
void RheiaConfigurationManager::DoRead(const wxString& path, RheiaStringStringMap* as)
{
    wxString key(path);
    xmlNode* node;
    node = RheiaXmlManager::Get()->AssertPath(key,m_root);
    xmlNode* e = RheiaXmlManager::Get()->GetUniqElement( node , key );

    /* First check if the node exist */
    xmlNode *child = e->children;
    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char *) child->name );
        if ( ChildName.IsSameAs( wxT("variable") ) )
        {
            xmlNode* sub = child->children;
            wxString vname;
            wxString value;

            while( sub != NULL )
            {
                wxString subname = RheiaC2U( (const char*) sub->name );
                if( subname.IsSameAs( wxT("name")))
                {
                    xmlChar* content = xmlNodeGetContent( sub );
                    vname = RheiaC2U( (const char*) content );
                    xmlFree( content );
                }
                else if( subname.IsSameAs( wxT("value")))
                {
                    xmlChar* content = xmlNodeGetContent( sub );
                    value = RheiaC2U( (const char*) content );
                    xmlFree( content );
                }
                sub = sub->next;
            }

            if( !vname.IsEmpty() && !value.IsEmpty())
                (*as)[vname] = value;
        }
        child = child->next;
    }
}
RheiaStringStringMap RheiaConfigurationManager::ReadStringStringMap(const wxString& path)
{
    RheiaStringStringMap ret;
    DoRead(path, &ret);
    return ret;
}

void RheiaConfigurationManager::WriteSashSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::SashSize;
    int SashSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_SASH_SIZE );

    RheiaXmlManager::Get()->Write( key , m_root , SashSize );
}

void RheiaConfigurationManager::WriteCaptionSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::CaptionSize;
    int CaptionSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_CAPTION_SIZE );

    RheiaXmlManager::Get()->Write( key , m_root , CaptionSize );
}

void RheiaConfigurationManager::WriteGripperSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::GripperSize;
    int GripperSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_GRIPPER_SIZE );

    RheiaXmlManager::Get()->Write( key , m_root , GripperSize );
}

void RheiaConfigurationManager::WritePaneBorderSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::PaneBorderSize;
    int PaneBorderSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE );

    RheiaXmlManager::Get()->Write( key , m_root , PaneBorderSize );
}

void RheiaConfigurationManager::WritePaneButtonSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::PaneButtonSize;
    int PaneButtonSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_PANE_BUTTON_SIZE );

    RheiaXmlManager::Get()->Write( key , m_root , PaneButtonSize );
}

void RheiaConfigurationManager::WriteActiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::ActiveCaptionColor;
    wxColor ActiveCaptionColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , ActiveCaptionColor );
}
void RheiaConfigurationManager::WriteActiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::ActiveCaptionGradientColor;
    wxColor ActiveCaptionGradientColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , ActiveCaptionGradientColor );
}
void RheiaConfigurationManager::WriteActiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::ActiveCaptionTextColor;
    wxColor ActiveCaptionTextColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , ActiveCaptionTextColor );
}
void RheiaConfigurationManager::WriteInactiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::InactiveCaptionColor;
    wxColor InactiveCaptionColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , InactiveCaptionColor );
}
void RheiaConfigurationManager::WriteInactiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::InactiveCaptionGradientColor;
    wxColor InactiveCaptionGradientColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , InactiveCaptionGradientColor );
}
void RheiaConfigurationManager::WriteInactiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::InactiveCaptionTextColor;
    wxColor InactiveCaptionTextColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , InactiveCaptionTextColor );
}
void RheiaConfigurationManager::WriteGripperColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::GripperColor;
    wxColor GripperColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_GRIPPER_COLOUR );
    RheiaXmlManager::Get()->Write( key , m_root , GripperColor );
}

void RheiaConfigurationManager::WriteLayout( const wxString& path, wxAuiManager* LayoutManager, const wxArrayString& LayoutNames, const wxArrayString& LayoutValues, bool overwrite_existing )
{
    wxString key( path + wxT("/") + ConfigManagerPaths::Layout );

    for ( unsigned int i = 0 ; i < LayoutValues.GetCount() ; i++ )
    {
        WritePerspective( key , LayoutNames[i], LayoutValues[i], overwrite_existing );
    }
    WriteSashSize( key, LayoutManager );
    WriteCaptionSize( key, LayoutManager );
    WriteGripperSize( key, LayoutManager );
    WritePaneBorderSize( key, LayoutManager );
    WritePaneButtonSize( key, LayoutManager );

    WriteActiveCaptionColor( key, LayoutManager );
    WriteActiveCaptionGradientColor( key, LayoutManager );
    WriteActiveCaptionTextColor( key, LayoutManager );
    WriteInactiveCaptionColor( key, LayoutManager );
    WriteInactiveCaptionGradientColor( key, LayoutManager );
    WriteInactiveCaptionTextColor( key, LayoutManager );
    WriteGripperColor( key, LayoutManager );
}

void RheiaConfigurationManager::ReadLayout( const wxString& path, wxAuiManager* LayoutManager, const wxString& pName )
{
    wxString key( path + wxT("/") + ConfigManagerPaths::Layout );

    ReadPerspective( key , LayoutManager , pName );

    ReadSashSize( key, LayoutManager );
    ReadCaptionSize( key, LayoutManager );
    ReadGripperSize( key, LayoutManager );
    ReadPaneBorderSize( key, LayoutManager );
    ReadPaneButtonSize( key, LayoutManager );

    ReadActiveCaptionColor( key, LayoutManager );
    ReadActiveCaptionGradientColor( key, LayoutManager );
    ReadActiveCaptionTextColor( key, LayoutManager );
    ReadInactiveCaptionColor( key, LayoutManager );
    ReadInactiveCaptionGradientColor( key, LayoutManager );
    ReadInactiveCaptionTextColor( key, LayoutManager );
    ReadGripperColor( key, LayoutManager );
}

void RheiaConfigurationManager::ReadSashSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::SashSize;
    int SashSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_SASH_SIZE );
    SashSize = RheiaXmlManager::Get()->ReadInt( key , m_root , SashSize );
    LayoutManager->GetArtProvider()->SetMetric( wxAUI_DOCKART_SASH_SIZE , SashSize );
}

void RheiaConfigurationManager::ReadCaptionSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::CaptionSize;
    int CaptionSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_CAPTION_SIZE );
    CaptionSize = RheiaXmlManager::Get()->ReadInt( key , m_root , CaptionSize );
    LayoutManager->GetArtProvider()->SetMetric( wxAUI_DOCKART_CAPTION_SIZE , CaptionSize );
}

void RheiaConfigurationManager::ReadGripperSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::GripperSize;
    int GripperSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_GRIPPER_SIZE );
    GripperSize = RheiaXmlManager::Get()->ReadInt( key , m_root , GripperSize );
    LayoutManager->GetArtProvider()->SetMetric( wxAUI_DOCKART_GRIPPER_SIZE , GripperSize );
}

void RheiaConfigurationManager::ReadPaneBorderSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::PaneBorderSize;
    int PaneBorderSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE );
    PaneBorderSize = RheiaXmlManager::Get()->ReadInt( key , m_root , PaneBorderSize );
    LayoutManager->GetArtProvider()->SetMetric( wxAUI_DOCKART_PANE_BORDER_SIZE , PaneBorderSize );
}

void RheiaConfigurationManager::ReadPaneButtonSize( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::PaneButtonSize;
    int PaneButtonSize = LayoutManager->GetArtProvider()->GetMetric( wxAUI_DOCKART_PANE_BUTTON_SIZE );
    PaneButtonSize = RheiaXmlManager::Get()->ReadInt( key , m_root , PaneButtonSize );
    LayoutManager->GetArtProvider()->SetMetric( wxAUI_DOCKART_PANE_BUTTON_SIZE , PaneButtonSize );
}

void RheiaConfigurationManager::ReadActiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::ActiveCaptionColor;
    wxColor ActiveCaptionColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR );
    ActiveCaptionColor = RheiaXmlManager::Get()->ReadColour( key , m_root , ActiveCaptionColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR , ActiveCaptionColor );
}
void RheiaConfigurationManager::ReadActiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::ActiveCaptionGradientColor;
    wxColor ActiveCaptionGradientColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR );
    ActiveCaptionGradientColor = RheiaXmlManager::Get()->ReadColour( key , m_root , ActiveCaptionGradientColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR , ActiveCaptionGradientColor );
}
void RheiaConfigurationManager::ReadActiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::ActiveCaptionTextColor;
    wxColor ActiveCaptionTextColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR );
    ActiveCaptionTextColor = RheiaXmlManager::Get()->ReadColour( key , m_root , ActiveCaptionTextColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR , ActiveCaptionTextColor );
}
void RheiaConfigurationManager::ReadInactiveCaptionColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::InactiveCaptionColor;
    wxColor InactiveCaptionColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR );
    InactiveCaptionColor = RheiaXmlManager::Get()->ReadColour( key , m_root , InactiveCaptionColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR , InactiveCaptionColor );
}
void RheiaConfigurationManager::ReadInactiveCaptionGradientColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::InactiveCaptionGradientColor;
    wxColor InactiveCaptionGradientColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR );
    InactiveCaptionGradientColor = RheiaXmlManager::Get()->ReadColour( key , m_root , InactiveCaptionGradientColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR , InactiveCaptionGradientColor );
}
void RheiaConfigurationManager::ReadInactiveCaptionTextColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::InactiveCaptionTextColor;
    wxColor InactiveCaptionTextColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR );
    InactiveCaptionTextColor = RheiaXmlManager::Get()->ReadColour( key , m_root , InactiveCaptionTextColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR , InactiveCaptionTextColor );
}
void RheiaConfigurationManager::ReadGripperColor( const wxString& path, wxAuiManager* LayoutManager )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::GripperColor;
    wxColor GripperColor = LayoutManager->GetArtProvider()->GetColor( wxAUI_DOCKART_GRIPPER_COLOUR );
    GripperColor = RheiaXmlManager::Get()->ReadColour( key , m_root , GripperColor );
    LayoutManager->GetArtProvider()->SetColor( wxAUI_DOCKART_GRIPPER_COLOUR , GripperColor );
}

void RheiaConfigurationManager::WritePerspective( const wxString& path, wxAuiManager *LayoutManager, const wxString& pName, bool overwrite_existing )
{
    /* First get the node in which to write the plugin */
    wxString key(path + wxT("/perspectives"));
    xmlNode* node;
    node = RheiaXmlManager::Get()->AssertPath(key,m_root);
    xmlNode* e = RheiaXmlManager::Get()->GetUniqElement( node , key );

    xmlNode *child = e->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );

        if ( ChildName.IsSameAs( ConfigManagerPaths::Perspective ) )
        {
            wxString pname = RheiaC2U( (const char*) xmlGetProp( child ,
                                       rxU2C(ConfigManagerPaths::LayoutAttributes::LayoutName) ) ) ;

            if ( pname.IsSameAs( pName ) )
            {
                if ( overwrite_existing )
                {
                    xmlReplaceNode( child , NULL );
                    break;
                }
                else
                    return;
            }
        }
        child = child->next;
    }

    child = xmlNewNode( NULL , rxU2C(ConfigManagerPaths::Perspective ) );
    xmlNewProp( child , rxU2C(ConfigManagerPaths::LayoutAttributes::LayoutName ) ,
                rxU2C(pName ));

    xmlAddChild( e , child );

    wxString perspective = LayoutManager->SavePerspective();
    key = wxT("/perspective_string");
    RheiaXmlManager::Get()->Write( key , perspective , child );
}

void RheiaConfigurationManager::WritePerspective( const wxString& path, const wxString& pName, const wxString& pValue, bool overwrite_existing )
{
    /* First get the node in which to write the plugin */
    wxString key(path + wxT("/perspectives"));
    xmlNode* node;
    node = RheiaXmlManager::Get()->AssertPath(key,m_root);
    xmlNode* e = RheiaXmlManager::Get()->GetUniqElement( node , key );

    xmlNode *child = e->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );

        if ( ChildName.IsSameAs( ConfigManagerPaths::Perspective ) )
        {
            wxString pname = RheiaC2U( (const char*) xmlGetProp( child ,
                                       rxU2C(ConfigManagerPaths::LayoutAttributes::LayoutName) ) ) ;

            if ( pname.IsSameAs( pName ) )
            {
                if ( overwrite_existing )
                {
                    xmlReplaceNode( child , NULL );
                    break;
                }
                else
                    return;
            }
        }
        child = child->next;
    }

    child = xmlNewNode( NULL , rxU2C(ConfigManagerPaths::Perspective ) );
    xmlNewProp( child , rxU2C(ConfigManagerPaths::LayoutAttributes::LayoutName ) ,
                rxU2C(pName ));

    xmlAddChild( e , child );

    wxString perspective = pValue;
    key = wxT("/perspective_string");
    RheiaXmlManager::Get()->Write( key , perspective , child );
}

void RheiaConfigurationManager::ReadPerspective( const wxString& path, wxAuiManager *LayoutManager, const wxString& pName )
{
    /* First get the node in which to write the plugin */
    wxString key(path + wxT("/perspectives"));
    xmlNode* node;
    node = RheiaXmlManager::Get()->AssertPath(key,m_root);
    xmlNode* e = RheiaXmlManager::Get()->GetUniqElement( node , key );

    xmlNode *child = e->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );

        if ( ChildName.IsSameAs( ConfigManagerPaths::Perspective ) )
        {
            wxString pname = RheiaC2U( (const char*) xmlGetProp( child ,
                                       rxU2C(ConfigManagerPaths::LayoutAttributes::LayoutName) ) ) ;

            if ( pname.IsSameAs( pName ) )
            {
                wxString perspective = LayoutManager->SavePerspective();
                wxString path = wxT("/perspective_string");
                perspective = RheiaXmlManager::Get()->Read( path , child, perspective );
                LayoutManager->LoadPerspective( perspective );
                return;
            }
        }
        child = child->next;
    }
}

void RheiaConfigurationManager::WriteFrameStatusBar( const wxString& path, wxFrame* frame )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::StatusBar;
    bool statusBr = (frame->GetStatusBar() && frame->GetStatusBar()->IsShown());
    RheiaXmlManager::Get()->Write( key , m_root , statusBr );
}

bool RheiaConfigurationManager::ReadFrameStatusBar( const wxString& path , bool defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::StatusBar;
    bool ret = RheiaXmlManager::Get()->ReadBool( key , m_root , defaultval );
    return ret;
}

void RheiaConfigurationManager::WriteFrameFullScreen( const wxString& path, wxFrame* frame )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::FullScreen;
    bool fullScreen = frame->IsFullScreen();
    RheiaXmlManager::Get()->Write( key , m_root , fullScreen );
}

bool RheiaConfigurationManager::ReadFrameFullScreen( const wxString& path , bool defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::FullScreen;
    bool ret = RheiaXmlManager::Get()->ReadBool( key , m_root , defaultval );
    return ret;
}

void RheiaConfigurationManager::WriteFrameMaximized( const wxString& path, wxFrame* frame )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::Maximized;
    bool maximized = frame->IsMaximized();
    RheiaXmlManager::Get()->Write( key , m_root , maximized );
}

bool RheiaConfigurationManager::ReadFrameMaximized( const wxString& path , bool defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::Maximized;
    bool ret = RheiaXmlManager::Get()->ReadBool( key , m_root , defaultval );
    return ret;
}

void RheiaConfigurationManager::WriteFramePosition( const wxString& path, wxFrame* frame )
{
    wxPoint framePos = frame->GetPosition();
    wxString key = path + wxT("/") + ConfigManagerPaths::PositionNode;
    RheiaXmlManager::Get()->Write( key , m_root , framePos );
}
wxPoint RheiaConfigurationManager::ReadFramePosition( const wxString& path , wxPoint defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::PositionNode;
    return RheiaXmlManager::Get()->ReadPosition( key , m_root , defaultval );
}

void RheiaConfigurationManager::ReadFramePosition( const wxString& path , wxFrame* frame, wxPoint defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::PositionNode;
    wxPoint pos = RheiaXmlManager::Get()->ReadPosition( key , m_root , defaultval );
    frame->SetPosition( pos );
}

void RheiaConfigurationManager::WriteFrameSize( const wxString& path, wxFrame* frame )
{
    wxSize frameSize = frame->GetSize();
    wxString key = path + wxT("/") + ConfigManagerPaths::SizeNode;
    RheiaXmlManager::Get()->Write( key , m_root , frameSize );
}
wxSize RheiaConfigurationManager::ReadFrameSize( const wxString& path , wxSize defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::SizeNode;
    return RheiaXmlManager::Get()->ReadSize( key , m_root , defaultval );
}

void RheiaConfigurationManager::ReadFrameSize( const wxString& path , wxFrame* frame, wxSize defaultval )
{
    wxString key = path + wxT("/") + ConfigManagerPaths::SizeNode;
    wxSize siz = RheiaXmlManager::Get()->ReadSize( key , m_root , defaultval );
    frame->SetSize( siz );
}

void RheiaConfigurationManager::WriteFrameInfo( const wxString& path, wxFrame *frame )
{
    wxString key( path + wxT("/FrameInformation") );

    WriteFrameSize( key , frame );
    #ifndef MACOSX
    WriteFramePosition( key , frame );
    #endif
    WriteFrameFullScreen( key , frame );
    WriteFrameMaximized( key , frame );
    WriteFrameStatusBar( key , frame );
}
void RheiaConfigurationManager::ReadFrameInfo( const wxString& path, wxFrame *frame )
{
    wxString key( path + wxT("/FrameInformation") );

    ReadFrameSize( key , frame );
    #ifndef MACOSX
    ReadFramePosition( key , frame );
    #endif
    frame->Maximize( ReadFrameMaximized( key ) );
    frame->ShowFullScreen( ReadFrameFullScreen( key ) , wxFULLSCREEN_NOTOOLBAR// | wxFULLSCREEN_NOSTATUSBAR
                           | wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION );
}

wxArrayString RheiaConfigurationManager::ListRootChildrens()
{
    wxArrayString ret;
    xmlNode* child = m_root->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );
        ret.Add( ChildName );
        child = child->next;
    }

    return ret;
}

void RheiaConfigurationManager::WriteBasicConfiguration( wxFrame *main_frame , wxAuiManager *LayoutManager )
{
    wxArrayString LayoutVal;
    LayoutVal.Add( LayoutManager->SavePerspective() );

    wxArrayString LayoutName;
    LayoutName.Add( wxT("default" ) );

    WriteFrameInfo( wxT("/MainFrame") , main_frame );
    WriteLayout( wxT("/MainFrame/LayoutManager") , LayoutManager,  LayoutName , LayoutVal );
}


wxArrayString RheiaConfigurationManager::ListRootChildrenNames(const wxString& path, const wxString& property)
{
    wxArrayString ret;
    xmlNode* child = m_root->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );

        if ( ChildName.IsSameAs( path ) )
        {
            xmlAttr *prop = xmlHasProp( child , rxU2C( property ) );
            if ( prop )
            {
                wxString propValue = RheiaXmlManager::RheiaNodeGetContent( prop->children );
                ret.Add( propValue );
            }
        }

        child = child->next;
    }
    return ret;
}

xmlNode* RheiaConfigurationManager::AddRootChildren( const wxString& path, const wxString& property, const wxString& propertyValue )
{
    xmlNode *ret;
    xmlNode* child = m_root->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );

        if ( ChildName.IsSameAs( path ) )
        {
            xmlAttr *prop = xmlHasProp( child , rxU2C( property ) );
            if ( prop )
            {
                wxString propVal = RheiaXmlManager::RheiaNodeGetContent( prop->children );
                if ( propVal.IsSameAs( propertyValue) )
                    return child;

            }
        }

        child = child->next;
    }

    ret = xmlNewNode( NULL , rxU2C( path ) );
    xmlNewProp( ret , rxU2C( property ), rxU2C( propertyValue ) );
    ret = xmlAddChild( m_root , ret );
    return ret;
}

xmlNode* RheiaConfigurationManager::GetRootChildren( const wxString& path, const wxString& property, const wxString& propertyValue )
{
    xmlNode *ret;
    xmlNode* child = m_root->children;

    while ( child != NULL )
    {
        wxString ChildName = RheiaC2U( (const char*) child->name );

        if ( ChildName.IsSameAs( path ) )
        {
            xmlAttr *prop = xmlHasProp( child , rxU2C( property ) );
            if ( prop )
            {
                wxString propVal = RheiaXmlManager::RheiaNodeGetContent( prop->children );
                if ( propVal.IsSameAs( propertyValue) )
                    return child;

            }
        }

        child = child->next;
    }

    ret = xmlNewNode( NULL , rxU2C( path ) );
    xmlNewProp( ret , rxU2C( property ), rxU2C( propertyValue ) );
    ret = xmlAddChild( m_root , ret );
    return ret;
}

void RheiaConfigurationManager::Write(const wxString& name, const wxFont& font)
{
    RheiaXmlManager::Get()->Write( name , m_root , font );
}

bool RheiaConfigurationManager::DoRead(const wxString& name, wxFont *font)
{
    return RheiaXmlManager::Get()->Read( name , m_root , font );
}

wxFont RheiaConfigurationManager::ReadFont(const wxString& name )
{
    return RheiaXmlManager::Get()->ReadFont( name , m_root );
}

void RheiaConfigurationManager::Write(const wxString& name, const wxTextAttr& attr)
{
    RheiaXmlManager::Get()->Write( name , m_root , attr );
}

bool RheiaConfigurationManager::Read(const wxString& name, wxTextAttr *attr)
{
    return RheiaXmlManager::Get()->Read( name , m_root , attr );
}

wxTextAttr RheiaConfigurationManager::ReadTextAttr(const wxString& name )
{
    return RheiaXmlManager::Get()->ReadTextAttr( name , m_root );
}
