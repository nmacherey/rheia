/**
*   @file RheiaAppBase.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 18-February-2010
*/

#include "RheiaAppBase.h"
#include "RheiaManager.h"
#include "RheiaXtraRes.h"
#include "RheiaStandardPaths.h"

#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_wizrd.h>
#include <wx/fs_zip.h>
#include <wx/menu.h>
#include <wx/app.h>
#include <wx/toolbar.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/clipbrd.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/cmdline.h>
#include <wx/utils.h>
#include <wx/snglinst.h>


bool RheiaAppBase::DoBasicInitializations()
{
    /* Enables wxLogging for the application */
#ifndef RHEIA_ENABLE_WXLOGGING
    wxLog::EnableLogging(false);
#endif

#ifdef LINUX
    setlocale(LC_ALL,"C");
#endif

	/* Fushing the clip board */
	wxTheClipboard->Flush();

	/* Initialize File system handler for zip and memory FS */
	wxFileSystem::AddHandler(new wxZipFSHandler);
    wxFileSystem::AddHandler(new wxMemoryFSHandler);
	/* Initialising all image handlers */
    wxInitAllImageHandlers();
	/* Initialising Xml ressource handler */
    wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->AddHandler( new wxToolBarAddOnXmlHandler );

	RheiaManager::Get();
	RheiaStandardPaths::InitPaths();

	m_singleInstanceChecker = 0;

	m_appName = GetAppName();
}
