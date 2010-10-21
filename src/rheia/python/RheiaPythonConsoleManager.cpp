/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "RheiaPythonConsoleManager.h"
#include "RheiaPythonConsole.h"
#include "RheiaManagedFrame.h"
#include "RheiaPythonUtils.h"
#include "RheiaConfigurationManager.h"
#include "RheiaStandardPaths.h"
#include "RheiaManager.h"

#include <iostream>
#include <wx/filedlg.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaPythonConsoleManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaPythonConsoleManager>::m_ns = locmap;

namespace {
	class PythonCleaner : public RheiaComponentCleaner
	{
	public :
		virtual void DoCleanUp(){
			RheiaPythonConsoleManager::Free();
			RheiaPythonUtils::Free();
		}
	};
	
	REGISTER_COMPONENT_CLEANER(PythonCleaner);
}

RheiaPythonConsoleManager::RheiaPythonConsoleManager(RheiaManagedFrame* parent):
    wxEvtHandler(),
    m_parent(parent)
{
	idSendFile = wxNewId();
	
    RegisterEvents();
}

RheiaPythonConsoleManager::~RheiaPythonConsoleManager()
{

}

void RheiaPythonConsoleManager::BuildMenu( wxMenuBar* menuBar )
{
	int idx = menuBar->FindMenu(wxT("Edit"));
    if( idx != wxNOT_FOUND )
    {
		int i = 0;
        wxMenu* mnConsole = new wxMenu();
		mnConsole->Insert( i++, idSendFile , wxT("&Send File\tCtrl-M") , wxT("Send a file to the python console") );
		menuBar->Insert(idx+1,mnConsole,wxT("Python"));
		
		this->Connect(idSendFile,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaPythonConsoleManager::OnSendFile));
    }
}

void RheiaPythonConsoleManager::OnSendFile(wxCommandEvent& event)
{
	wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("pyconsole") )->Read( wxT("/last_file") , RheiaStandardPaths::HomeDirectory() );

    wxFileDialog dialog( m_parent,
                         wxT("Select the python files you want to load..."),
                         LastOpenPath,
                         wxEmptyString,
                         wxT("Python files (*.py)|*.py"),
                         wxFD_OPEN );

    if ( dialog.ShowModal() != wxID_OK )
    {
        return;
    }
	
	wxString path = dialog.GetPath();
	
	if( path.IsEmpty() )
		return;
		
    RheiaManager::Get()->GetConfigurationManager( wxT("pyconsole") )->Write( wxT("/last_file") , wxFileName(path).GetPath(true) );
	
	wxString res;
	wxString pyPath = wxFileName(path).GetPath(true);
#ifdef WIN32
	pyPath.Replace(wxT("\\"),wxT("\\\\"));
    pyPath = wxFileName(path).GetVolume() + wxFileName(path).GetVolumeSeparator() + pyPath;
#endif
	wxString command = wxT("sys.path = ['") + pyPath + wxT("'] + sys.path");
	RheiaPythonUtils::Get()->PythonEvalString(command,res,0);
	
	if( !res.IsEmpty() )
		std::cout << RheiaU2C(res) << std::endl << ">>> ";
		
	command = wxT("import ") + wxFileName(path).GetName();
	RheiaPythonUtils::Get()->PythonEvalString(command,res,0);
	
	if( !res.IsEmpty() )
		std::cout << RheiaU2C(res) << std::endl << ">>> ";
	
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
