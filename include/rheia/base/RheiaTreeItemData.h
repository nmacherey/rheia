#ifndef RheiaTreeItemData_h
#define RheiaTreeItemData_h

#include <wx/treectrl.h>
#include <RheiaBaseSettings.h>

/* Rheia's imports */
class RheiaTreeItem;

/*********************************************************************************************************//**
*	@class RheiaTreeItemData
*
*	@brief The RheiaTreeItemData class is a class for allowing any tree item to handle a spcific event handler.
*
*	This class allows a TreeData to be created specifying which Event Handler should process its related events.
*	This is used by plugins when creating a TreeItem in the manager's left pane.
*************************************************************************************************************/
class BASE_DLLEXPORT RheiaTreeItemData : public wxTreeItemData, public wxObject
{
    DECLARE_DYNAMIC_CLASS(RheiaTreeItemData)
public:
	/**************************************************************************************************
	*	CONSTRUCTORS
	**************************************************************************************************/
	/*! Default constructor */
	RheiaTreeItemData(RheiaTreeItem *item = 0L):m_owner(item){};

	/*! Default destructor */
	virtual ~RheiaTreeItemData() { m_owner=0L; }

	/**************************************************************************************************
	*	METHODS
	**************************************************************************************************/
	/*! Returns the owner event handler */
	RheiaTreeItem *GetOwner() { if(!this) return 0L;return m_owner; }

	/*! Sets the owner event handler */
	void SetOwner(RheiaTreeItem *owner) { if(!this) return; m_owner=owner; }
private:
	/**************************************************************************************************
	*	PRIVATE VARIABLES
	**************************************************************************************************/
	RheiaTreeItem *m_owner;									/*!< Owner event handler, the handler in which to process the events */
};

///*********************************************************************************************************//**
//*	@class RheiaProjectTreeItemData
//*
//*	@brief The RheiaProjectTreeItemData class is a class for allowing any tree item to handle a spcific event handler.
//*
//*	This class allows a TreeData to be created specifying which Event Handler should process its related events.
//*	This is used by plugins when creating a TreeItem in the manager's left pane.
//*************************************************************************************************************/
//class BASE_DLLEXPORT RheiaProjectTreeItemData : public RheiaTreeItemData
//{
//public:
//	/**************************************************************************************************
//	*	CONSTRUCTORS
//	**************************************************************************************************/
//	/*! Default constructor */
//	RheiaProjectTreeItemData(RheiaWorkspace *workspace, RheiaProject *project): RheiaTreeItemData( workspace ),Project(project)
//	{
//		TreeDataType = tdkProject;
//	};
//
//	/*! Default destructor */
//	virtual ~RheiaProjectTreeItemData() { }
//
//	/**************************************************************************************************
//	*	METHODS
//	**************************************************************************************************/
//	/*! Get my owner project */
//	RheiaProject *GetProject(void){return Project;};
//
//private:
//	/**************************************************************************************************
//	*	PRIVATE VARIABLES
//	**************************************************************************************************/
//	RheiaProject *Project;							/*!< owner project */
//};
//
///*********************************************************************************************************//**
//*	@class RheiaProjectElementTreeItemData
//*
//*	@brief The RheiaProjectElementTreeItemData class is a class for allowing any tree item to handle a spcific event handler.
//*
//*	This class allows a TreeData to be created specifying which Event Handler should process its related events.
//*	This is used by plugins when creating a TreeItem in the manager's left pane.
//*************************************************************************************************************/
//class BASE_DLLEXPORT RheiaProjectElementTreeItemData : public RheiaTreeItemData
//{
//public:
//	/**************************************************************************************************
//	*	CONSTRUCTORS
//	**************************************************************************************************/
//	/*! Default constructor */
//	RheiaProjectElementTreeItemData(RheiaWorkspace *workspace, RheiaProject *project,
//        RheiaProjectElement *element ): RheiaTreeItemData( workspace ),Project(project),Element(element)
//	{
//		TreeDataType = tdkProjectElement;
//	};
//
//	/*! Default destructor */
//	virtual ~RheiaProjectElementTreeItemData() { }
//
//	/**************************************************************************************************
//	*	METHODS
//	**************************************************************************************************/
//	/*! Get my owner project */
//	RheiaProject *GetProject(void){return Project;};
//
//    /*! Get my owner project element */
//	RheiaProjectElement *GetProjectElement(void){return Element;};
//
//private:
//	/**************************************************************************************************
//	*	PRIVATE VARIABLES
//	**************************************************************************************************/
//	RheiaProject *Project;							/*!< owner project */
//    RheiaProjectElement *Element;                   /*!< owner element */
//};

#endif
