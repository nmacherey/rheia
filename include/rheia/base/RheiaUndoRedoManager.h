/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com.
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement
*/
/**
*   @file RheiaUndoRedoManager.h
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 27-June-2010
*   @version 0.0.1
* 	@todo IMPLEMENT A REAL SMART PTR WITH REFERENCE COUNTING FOR THIS HERE (DON'T USE BOOST ONE TO AVOID DEPENDENCIES)
*/
#ifndef RHEIA_UNDOREDO_MANAGER_H
#define RHEIA_UNDOREDO_MANAGER_H

#include <stack>
#include <list>

#include "RheiaBaseSettings.h"

#include "RheiaManager.h"
#include "RheiaManagedFrame.h"

/** previous define for the Undo/Redo interface */
class RheiaCommand;

/** define a command stack */
typedef std::stack< RheiaCommand* > RheiaCommandStack;
typedef std::list< RheiaCommand* > RheiaCommandList;

/**
 * @class RheiaUndoRedoManager
 * @brief Manager for Undo/Redo Patterns
 *
 * @date 27-June-2010
 * @author Nicolas Macherey (nm@graymat.fr)
 */
class BASE_DLLEXPORT RheiaUndoRedoManager : public wxEvtHandler , public RheiaMgr<RheiaManagedFrame,RheiaUndoRedoManager> {

public :
	friend class RheiaMgr<RheiaManagedFrame,RheiaUndoRedoManager>;				/*!< Give our private member access to Singleton */
	friend class RheiaManager;														/*!< Give our private member access to RheiaManager */

	/**********************************************************************************************************
	*	METHODS
	**********************************************************************************************************/
	/** Execute the given RheiaCommand, mainly it will push
	 * the given command on the undoStack and pop the redoStack
	 * @param command RheiaCommand to execute
	 */
	void Execute(RheiaCommand* command);
	
	/** Execute the given RheiaCommand, mainly it will push
	 * the given command on the undoStack and pop the redoStack
	 * @param command RheiaCommand to execute
	 */
	void Push(RheiaCommand* command);
	
	/** Add an action to the top undo action */
	void ChainTop( RheiaCommand* command );

	/** Undo the first command on the undostack and pop it */
	void Undo();

	/** Redo the first command on the redo stact and pop it */
	void Redo();

	/** Clear the Undo/Redo history */
	void ClearHistory();

	/** Set the save point to the undoStack size this is mainly to notify when you saved a project */
	void SetSavePoint();

	/** Check if the save point is at the undo stack size or not */
	bool IsAtSavePoint();

	/** Check if there is some commands in hte undo stack */
	bool CanUndo();

	/** Check if there is some commands in the redo stack */
	bool CanRedo();
	
	/** Check if I am undoing some actions or not */
	bool IsUndoing() {return m_undoing;};
	
	/** Check if I am redoing some actions or not */
	bool IsRedoing() {return m_redoing;};
	
	/** Check if I am chaining or not */
	bool IsChaining( ) {return m_chaining;};
	
	/** Set Chaining */
	void SetChainingMode( bool value = true ){m_chaining = value;};
	
	/** Check if the given command is the chainer or not */
	bool IsChainer( RheiaCommand* command );

private :

	/**********************************************************************************************************
	*	CONSTRUCTORS
	**********************************************************************************************************/
	/*! Default constructor */
	RheiaUndoRedoManager(RheiaManagedFrame* parent);

	/*! Default destructor */
	~RheiaUndoRedoManager();

private :
	RheiaManagedFrame* m_parent;
	RheiaCommandStack m_undoStack;
	RheiaCommandStack m_redoStack;
	unsigned int m_savePoint;
	bool m_undoing;
	bool m_redoing;
	bool m_chaining;
};

/**
 * @class RheiaCommand
 * @brief Command to execute when redoing and undoing
 * This class is an interface that you shall derive in order to use Rheia Undo/Redo system
 *
 * @date 27-June-2010
 * @author Nicolas Macherey (nm@graymat.fr)
 */
class RheiaCommand {
	
private:
	/** Check if the command has been executed or not */
	bool m_executed;
	
	/** Command list in order to reproduce the chain */
	RheiaCommandList m_chain;

protected:
	/**
	 * Execute the command this method is the one you have to overload 
	 * for any Undo/Redo action
	 */
	virtual void DoExecute() = 0;

	/**
	 * Restore the action associated to the command, this method is the one you have to overload 
	 * for any Undo/Redo action
	 */
	virtual void DoRestore() = 0;
	
	/** This method is called when the restore is starting
	 * You can overload it if you need to do specific actions like event generation
	 * before the Command restor is starting
	 */
	virtual void OnBeginRestore() {};
	
	/** This method is called whent the restoring task is ending
	 * You can overload it if you need to perform specific actions
	 * when the command has been restored
	 */
	virtual void OnEndRestore() {};
	
	/** This method is called when the restore is starting
	 * You can overload it if you need to do specific actions like event generation
	 * before the Command restor is starting
	 */
	virtual void OnBeginExecute() {};
	
	/** This method is called whent the restoring task is ending
	 * You can overload it if you need to perform specific actions
	 * when the command has been restored
	 */
	virtual void OnEndExecute() {};

public:

	/** defualt ctor */
	RheiaCommand();
	
	/** default dtor */
	virtual ~RheiaCommand() {};
	
	/** Execute the command */
	void Execute();
	
	/** Restore the command */
	void Restore();
	
	/** Set executed */
	void SetExecuted( bool value ) { m_executed = value;};
	
	/** Add to chain */
	void Chain( RheiaCommand* command );
};

#endif
