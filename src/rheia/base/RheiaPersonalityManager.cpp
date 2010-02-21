/**
*   @file RheiaPersonalityManager.cpp
*
*   Revision : 15-January-2010
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	21-Nov-2008
*	@version 0.0.2
*/
#include <RheiaPersonalityManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>

#include <wx/intl.h>
#include <wx/dir.h>
#include <wx/filename.h>

#include <wx/arrstr.h>

template<> RheiaPersonalityManager* Mgr<RheiaPersonalityManager>::instance = 0;
template<> bool  Mgr<RheiaPersonalityManager>::isShutdown = false;

wxString RheiaPersonalityManager::pers;

RheiaPersonalityManager::RheiaPersonalityManager()
{
    RheiaPersonalityManager::pers = _T("default");
}

void RheiaPersonalityManager::SetPersonality(const wxString& personality, bool createIfNotExist)
{
    pers = personality;
}

const wxString RheiaPersonalityManager::GetPersonality()
{
    return pers;
}

const wxArrayString RheiaPersonalityManager::GetPersonalitiesList()
{
    wxArrayString list;
    wxDir::GetAllFiles(RheiaStandardPaths::Directory(rspfConfig), &list, _T("*.conf"), wxDIR_FILES);
    wxDir::GetAllFiles(RheiaStandardPaths::Directory(rspfAllUser), &list, _T("*.conf"), wxDIR_FILES);

    for (size_t i = 0; i < list.GetCount(); ++i)
        list[i] = wxFileName(list[i]).GetName();

    return list;
}
