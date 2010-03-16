/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaTreeItem.h
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 19-February-2010
*   @version 0.0.1
*/
#ifndef RheiaTreeItem_h_
#define RheiaTreeItem_h_

#include "RheiaGlobals.h"
#include "RheiaBaseSettings.h"

#include <wx/event.h>
#include <wx/string.h>
#include <wx/treectrl.h>

#include <map>

/* import */
class RheiaTreeItem;

/** define a map of tree item */
typedef std::map< wxString , RheiaTreeItem* > RheiaTreeItemMap;

/** define flags for RheiaTreeItemManager */
const int rhTREE_DELETE_ON_DESTROY = 0x0001;
const int rhTREE_CLEAR_ON_DESTROY = 0x0002;
const int rhTREE_DEFAULT = rhTREE_DELETE_ON_DESTROY;

/**
*   @class RheiaTreeItemManager
*   @brief This is a basic class for managing a set of tree items
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 19-February-2010
*   @version 0.0.1
*/
class BASE_DLLEXPORT RheiaTreeItem : public wxEvtHandler, public virtual RheiaObjectWithBitmap
{
#ifndef SWIG
    DECLARE_ABSTRACT_CLASS(RheiaTreeItem)
#endif
public :
    /******************************************************************************
    *   CONSTUCTORS
    ******************************************************************************/
    /** Default contructor
    *   You can set the flag value to rhTREE_DELETE_ON_DESTROY if you want that the
    *   tree deletes all it's items when deleting it or rhTREE_CLEAR_ON_DESTROY if
    *   you want to keep the memory intact from the map.
    */
    RheiaTreeItem( int flags = rhTREE_DEFAULT);

    /** dtor */
    virtual ~RheiaTreeItem();

#ifdef SWIG
    %rename(RheiaTreeItemCopy) RheiaTreeItem (const RheiaTreeItem& rhs);
#endif
    /** copy ctor */
    RheiaTreeItem (const RheiaTreeItem& rhs);

    /** Clone method */
    virtual RheiaTreeItem* Clone() = 0;


    /** Get the root node for this Item */
    wxTreeItemId GetRoot() {return m_root;};

    /** Copy to the given root node
    *   if moveTo is set to true , root item for this tree will be change to the given
    *   argument and all children items for this tree will be copied in the new one.
    *   @param root new root for this tree
    *   @param moveTo specify if it is a copy or a move
    *   @return true if everything has been done properly
    */
    bool CopyTo( wxTreeCtrl* tree , wxTreeItemId root , int bmpSize , bool moveTo = true );

    /** Remove all childrens
    *   if the flags has been set to rhTREE_DELETE_ON_DESTROY the destructor
    *   for each childrens will be called.
    */
    void RemoveAll();

    /** Build the tree and use the given root as root item */
    void CreateTree( wxTreeCtrl* tree , wxTreeItemId root , int bmpSize );

    /** Build the tree and use the given root as root item */
    void UpdateTree(  wxTreeCtrl* tree , int bmpSize );

    /** Set the flags to the given one
    *   if flags = rhTREE_DELETE_ON_DESTROY any remove will corresponds to a delete of the item
    *   if flags = rhTREE_CLEAR_ON_DESTROY the item will simply be removed from the map
    */
    void SetFlags( int flags ) {m_flags = flags;}

    /**********************************************************************************
    *   EVENT RELATED METHODS
    **********************************************************************************/
    /** this method is called when the user will act on the tree by simply selecting the item */
    virtual void OnItemSelected() {};

    /** this method is called when the user double cliks on the item tree */
    virtual void OnItemActivated() {};
	
	/** this method is called when the user double cliks on the item tree */
    virtual void OnItemRightClick() {};

    /** this method is used to build specific menu information about the item when the user
    *   request it
    */
    virtual void OnRequestContextMenu( wxMenu* ) {};

    /** this method is used whent the item is about to be deleted */
    virtual void OnPreDelete() {};

    /** this method is used whent the item is about to be dragged */
    virtual bool OnBeginDrag() {return false;};

    /** this method is used whent the item is about to be dragged */
    virtual bool OnEndDrag() {return false;};

    /** check if the item has been modified or not */
    virtual bool GetModified();

    /** Set the modification flag */
    virtual void SetModified( bool value = true , bool recursive = false );

    /**********************************************************************************
    *   MANAGEMENT METHODS
    **********************************************************************************/
    /** Add an item in the tree map
    *   If the item already exists this method will return false
    *   @param name item name to be inserted in the tree
    *   @param
    */
    bool Add( const wxString& name , RheiaTreeItem* item );

    /** remove the tree map
    *   If the item already exists this method will return false
    *   @param name item name to be removed
    *   @return true if the item has been found
    *   @note if the flag is set to rhTREE_DELETE_ON_DESTROY the item will be delete to
    */
    bool Remove( const wxString& name );

#ifdef SWIG
    %rename(RemoveItem) Remove( RheiaTreeItem* item );
#endif
    /** remove the tree map
    *   If the item already exists this method will return false
    *   @param item item ref to be removed
    *   @return true if the item has been found
    *   @note if the flag is set to rhTREE_DELETE_ON_DESTROY the item will be delete to
    *   so the intance will no longer exists and any try to do something on the given argument
    *   will make an applicatoin crash
    */
    bool Remove( RheiaTreeItem* item );

    /** Check if an item exists
    *   @param name item name to check the existance for
    *   @return tue if the item exists in the map
    */
    bool Exists( const wxString& name );

#ifdef SWIG
    %rename(ItemExists) Exists( const RheiaTreeItem* item );
#endif
    /** Check if an item exists
    *   @param name item ref to check the existance for
    *   @return tue if the item exists in the map
    */
    bool Exists( const RheiaTreeItem* item );

    /** Find an Item by its name */
    RheiaTreeItem* Find( const wxString& name , bool recursive = true );

    /** Find item name by it's object ref */
    wxString GetItemName( RheiaTreeItem* item , bool recursive = true );

    /** get item table */
    RheiaTreeItemMap& GetItems() {return m_items;}

protected :

    RheiaTreeItemMap m_items;
    wxTreeItemId m_root;
    int m_flags;
    bool m_modified;
};

#endif
