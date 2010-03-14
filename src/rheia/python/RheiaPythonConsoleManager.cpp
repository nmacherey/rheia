/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "RheiaPythonConsoleManager.h"
#include "RheiaPythonConsole.h"
#include "RheiaManagedFrame.h"

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaPythonConsoleManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>::m_ns = locmap;


RheiaPythonConsoleManager::RheiaPythonConsoleManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_parent(parent)
{
    m_parent->PushEventHandler(this);
    RegisterEvents();
}

RheiaPythonConsoleManager::~RheiaPythonConsoleManager()
{
    m_parent->RemoveEventHandler(this);
}

void RheiaPythonConsoleManager::BuildMenu( wxMenuBar* menuBar )
{

}

void RheiaPythonConsoleManager::ReleaseMenu( wxMenuBar* menuBar )
{

}

void RheiaPythonConsoleManager::RegisterEvents()
{

}

RheiaBookPage* RheiaPythonConsoleManager::BuildMainWindow( wxWindow* parent )
{
    return new RheiaPythonConsole(m_parent,parent);
}
