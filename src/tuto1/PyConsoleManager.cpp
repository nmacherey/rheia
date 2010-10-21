/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "PyConsoleManager.h"
#include "PyConsole.h"

namespace
{
    RheiaMgr<RheiaManagedFrame,PyConsoleManager>::MgrNsMap locmap;
}

/*! Global instance for the PyConsoleManager */
template<> RheiaMgr<RheiaManagedFrame,PyConsoleManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,PyConsoleManager>::m_ns = locmap;


PyConsoleManager::PyConsoleManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_parent(parent)
{
    m_parent->PushEventHandler(this);
    RegisterEvents();
}

PyConsoleManager::~PyConsoleManager()
{
    m_parent->RemoveEventHandler(this);
}

void PyConsoleManager::BuildMenu( wxMenuBar* menuBar )
{

}

void PyConsoleManager::ReleaseMenu( wxMenuBar* menuBar )
{

}

void PyConsoleManager::RegisterEvents()
{

}

RheiaBookPage* PyConsoleManager::BuildMainWindow( wxWindow* parent )
{
    return new PyConsole(m_parent,parent);
}
