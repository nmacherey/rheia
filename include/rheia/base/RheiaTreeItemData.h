/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaTreeItemData.h
* 
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 19-February-2010
*   @version 0.0.1
*/
#ifndef RheiaTreeItemData_h
#define RheiaTreeItemData_h

#include <wx/treectrl.h>
#include <RheiaBaseSettings.h>

/* Rheia's imports */
class RheiaTreeItem;

/**
*	@class RheiaTreeItemData
*
*	@brief The RheiaTreeItemData class is a class for allowing any tree item to handle a spcific event handler.
*
*	This class allows a TreeData to be created specifying which Event Handler should process its related events.
*	This is used by plugins when creating a TreeItem in the manager's left pane.
* 
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 19-February-2010
*   @version 0.0.1
*/
class BASE_DLLEXPORT RheiaTreeItemData : public wxTreeItemData, public wxObject
{
#ifndef SWIG
    DECLARE_DYNAMIC_CLASS(RheiaTreeItemData)
#endif

public:
	/**************************************************************************************************
	*	CONSTRUCTORS
	**************************************************************************************************/
	/** Default constructor */
	RheiaTreeItemData(RheiaTreeItem *item = 0L):m_owner(item){};

	/** Default destructor */
	virtual ~RheiaTreeItemData() { m_owner=0L; }

	/**************************************************************************************************
	*	METHODS
	**************************************************************************************************/
	/** Returns the owner event handler */
	RheiaTreeItem *GetOwner() { if(!this) return 0L;return m_owner; }

	/** Sets the owner event handler */
	void SetOwner(RheiaTreeItem *owner) { if(!this) return; m_owner=owner; }
	
private:

	/**************************************************************************************************
	*	PRIVATE VARIABLES
	**************************************************************************************************/
	RheiaTreeItem *m_owner;
};

#endif
