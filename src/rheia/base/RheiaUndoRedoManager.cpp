/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com.
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement
*/
/**
*   @file RheiaUndoRedoManager.cpp
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 27-June-2010
*   @version 0.0.1
*/

#include "RheiaUndoRedoManager.h"

namespace {
RheiaMgr<RheiaManagedFrame,RheiaUndoRedoManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaUndoRedoManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaUndoRedoManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaUndoRedoManager>::m_ns = locmap;

RheiaUndoRedoManager::RheiaUndoRedoManager(RheiaManagedFrame* parent):
	m_parent(parent),
	m_savePoint( 0 ),
	m_undoing(false),
	m_redoing(false) {
}

RheiaUndoRedoManager::~RheiaUndoRedoManager() {

}

void RheiaUndoRedoManager::Execute(RheiaCommand* command) {
	command->Execute();
	m_undoStack.push(command);

	while (!m_redoStack.empty()) {
		m_redoStack.pop();
	}
}

void RheiaUndoRedoManager::Undo() {
	m_undoing = true;
	if (!m_undoStack.empty()) {
		RheiaCommand* command = m_undoStack.top();
		m_undoStack.pop();

		command->Restore();
		m_redoStack.push(command);
	}
	m_undoing = false;
}

void RheiaUndoRedoManager::Redo() {
	m_redoing = true;
	if (!m_redoStack.empty()) {
		RheiaCommand* command = m_redoStack.top();
		m_redoStack.pop();

		command->Execute();
		m_undoStack.push(command);
	}
	m_redoing = false;
}

void RheiaUndoRedoManager::ClearHistory() {
	while (!m_redoStack.empty())
		m_redoStack.pop();

	while (!m_undoStack.empty())
		m_undoStack.pop();

	m_savePoint = 0;
}

bool RheiaUndoRedoManager::CanUndo() {
	return (!m_undoStack.empty());
}
bool RheiaUndoRedoManager::CanRedo() {
	return (!m_redoStack.empty());
}

void RheiaUndoRedoManager::SetSavePoint() {
	m_savePoint = m_undoStack.size();
}

bool RheiaUndoRedoManager::IsAtSavePoint() {
	return m_undoStack.size() == m_savePoint;
}

/****** RHEIA COMMAND **********/

RheiaCommand::RheiaCommand() {
	m_executed = false;
}

void RheiaCommand::Execute() {
	if (!m_executed) {
		DoExecute();
		m_executed = true;
	}
}

void RheiaCommand::Restore() {
	if (m_executed) {
		DoRestore();
		m_executed = false;
	}
}
