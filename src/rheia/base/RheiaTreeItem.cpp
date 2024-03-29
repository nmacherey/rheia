/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaTreeItem.cpp
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 19-February-2010
*   @version 0.0.1
*/
#include "RheiaTreeItem.h"
#include "RheiaTreeItemData.h"

#include <wx/imaglist.h>
#include <wx/treectrl.h>

IMPLEMENT_ABSTRACT_CLASS( RheiaTreeItem , wxEvtHandler )


RheiaTreeItem::RheiaTreeItem( int flags ):
    wxEvtHandler(),
    m_flags(flags),
    m_modified(false)
{

}

RheiaTreeItem::~RheiaTreeItem()
{
    RemoveAll();
}

RheiaTreeItem::RheiaTreeItem(const RheiaTreeItem& rhs):
    wxEvtHandler(),
    m_flags(rhs.m_flags),
    m_modified(rhs.m_modified)
{
    RheiaTreeItemMap::const_iterator it = rhs.m_items.begin();

    for( ; it != rhs.m_items.end() ; ++it )
        m_items[it->first] = it->second->Clone();
		
	m_currentChild = rhs.m_currentChild;
	m_currentChildId = rhs.m_currentChildId;
}

void RheiaTreeItem::RemoveAll()
{
    if( m_flags == rhTREE_DELETE_ON_DESTROY )
    {
        RheiaTreeItemMap::iterator it = m_items.begin();

        for( ; it != m_items.end() ; ++it )
        {
            it->second->RemoveAll();
            delete it->second;
        }
    }
	
	m_currentChild = wxEmptyString;
    m_items.clear();
}

bool RheiaTreeItem::Add( const wxString& name , RheiaTreeItem* item )
{
    RheiaTreeItemMap::iterator it = m_items.find(name);

    if( it != m_items.end() )
        return false;

    m_items[name] = item;
	m_currentChild = name;
	m_currentChildId = item->m_root;
	
    return true;
}

bool RheiaTreeItem::Remove( const wxString& name )
{
    RheiaTreeItemMap::iterator it = m_items.find(name);

    if( it == m_items.end() )
        return false;

    if( m_flags == rhTREE_DELETE_ON_DESTROY )
        delete it->second;

    m_items.erase(it);

    return true;
}

bool RheiaTreeItem::Remove( RheiaTreeItem* item )
{
    RheiaTreeItemMap::iterator it = m_items.begin();

    for( ; it != m_items.end() ; ++it )
    {
        if( it->second == item )
        {
            if( m_flags == rhTREE_DELETE_ON_DESTROY )
                delete item;

            m_items.erase(it);
            return true;
        }
    }

    return false;
}

bool RheiaTreeItem::Exists( const wxString& name )
{
    RheiaTreeItemMap::iterator it = m_items.find(name);

    if( it == m_items.end() )
        return false;

    return true;
}

bool RheiaTreeItem::Exists( const RheiaTreeItem* item )
{
    RheiaTreeItemMap::iterator it = m_items.begin();

    for( ; it != m_items.end() ; ++it )
        if( it->second == item )
            return true;

    return false;
}

RheiaTreeItem* RheiaTreeItem::Find( const wxString& name , bool recursive )
{
    RheiaTreeItemMap::iterator it = m_items.find(name);

    if( it == m_items.end() )
    {
        if( !recursive )
            return NULL;

        for( it = m_items.begin() ; it != m_items.end() ; ++it )
        {
            RheiaTreeItem* ret = it->second->Find(name,true);
            if( ret != NULL )
                return ret;
        }

        return NULL;
    }

    return it->second;
}

wxString RheiaTreeItem::GetItemName( RheiaTreeItem* item , bool WXUNUSED(recursive) )
{
    RheiaTreeItemMap::iterator it = m_items.begin();

    for( ; it != m_items.end() ; ++it )
    {
        wxString name;
        if( it->second == item )
            return it->first;
        else if( (name = it->second->GetItemName(item)) != wxEmptyString  )
            return name;
    }

    return wxEmptyString;
}

bool RheiaTreeItem::CopyTo( wxTreeCtrl* tree , wxTreeItemId root , int bmpSize , bool moveTo )
{
    RheiaTreeItemMap::iterator it = m_items.begin();

    for( ; it != m_items.end() ; ++it )
    {
        // get the bitmap
        wxImageList* ilist = tree->GetImageList();
        int idx = -1;
        if( ilist != NULL )
        {
            wxBitmap bmp = it->second->GetBitmap( bmpSize );
            idx = ilist->Add(bmp);
        }

        RheiaTreeItemData* data = new RheiaTreeItemData(it->second);
        wxTreeItemId tid = tree->AppendItem(root,it->first,idx,idx,data);
        it->second->CopyTo(tree,tid,bmpSize,moveTo);
    }

    if( moveTo )
        m_root = root;

    return true;
}

void RheiaTreeItem::CreateTree( wxTreeCtrl* tree , wxTreeItemId root , int bmpSize )
{
    RheiaTreeItemMap::iterator it = m_items.begin();

    for( ; it != m_items.end() ; ++it )
    {
        // get the bitmap
        wxImageList* ilist = tree->GetImageList();
        int idx = -1;
        if( ilist != NULL )
        {
            wxBitmap bmp = it->second->GetBitmap( bmpSize );
            idx = ilist->Add(bmp);
        }

        RheiaTreeItemData* data = new RheiaTreeItemData(it->second);
        wxTreeItemId tid = tree->AppendItem(root,it->first,idx,idx,data);
        it->second->CreateTree(tree,tid,bmpSize);
    }

    m_root = root;
}

void RheiaTreeItem::UpdateTree(  wxTreeCtrl* tree , int bmpSize )
{
    /** @todo this is working but we need to do it in a smarter way */
    RheiaTreeItemMap::iterator it = m_items.begin();
    tree->DeleteChildren( m_root );

    for( ; it != m_items.end() ; ++it )
    {
        // get the bitmap
        wxImageList* ilist = tree->GetImageList();
        int idx = -1;
        if( ilist != NULL )
        {
            wxBitmap bmp = it->second->GetBitmap( bmpSize );
            idx = ilist->Add(bmp);
        }

        RheiaTreeItemData* data = new RheiaTreeItemData(it->second);
        wxTreeItemId tid = tree->AppendItem(m_root,it->first,idx,idx,data);
        it->second->CreateTree(tree,tid,bmpSize);
    }
}

bool RheiaTreeItem::GetModified()
{
    bool modified = false;

    RheiaTreeItemMap::iterator it = m_items.begin();

    for( ; it != m_items.end() ; ++it )
    {
        if( it->second->GetModified() )
        {
            modified = true;
            break;
        }
    }

    return modified || m_modified;
}

void RheiaTreeItem::SetModified( bool value , bool recursive )
{
    m_modified = value;

    if( recursive )
    {
        RheiaTreeItemMap::iterator it = m_items.begin();

        for( ; it != m_items.end() ; ++it )
            it->second->SetModified(value,recursive);
    }
}
