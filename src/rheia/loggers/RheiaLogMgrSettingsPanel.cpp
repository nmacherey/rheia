/**
*   @file RheiaLogMgrSettingsPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaLogMgrSettingsPanel.h"

#include <wx/button.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>
#include <wx/colordlg.h>
#include <wx/msgdlg.h>
#include <wx/imaglist.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>

#include <RheiaManager.h>
#include <RheiaConfigurationManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaProfileManager.h>
#include <RheiaLoggerManager.h>
#include <RheiaConfigurationToolsManager.h>
#include <RheiaEvents.h>
#include <RheiaEventsManager.h>

REGISTER_CONFIGURATION_TOOL( RheiaLogMgrSettingsPanel )


namespace
{
    int chkAutoHideLogs = XRCID("chkAutoHideLogs");
};

BEGIN_EVENT_TABLE(RheiaLogMgrSettingsPanel,RheiaConfigurationPanel)
    EVT_CHECKBOX(chkAutoHideLogs, RheiaLogMgrSettingsPanel::OnAutoHideLogs)
END_EVENT_TABLE()

RheiaLogMgrSettingsPanel::RheiaLogMgrSettingsPanel( wxWindow* parent ):
    RheiaConfigurationPanel()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("panelLogMgrSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:logmgrconf_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);
    DoInitEnvironment();
}

void RheiaLogMgrSettingsPanel::DoInitEnvironment()
{
    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("log_manager"));

    bool en = icfg->ReadBool(_T("/comportment/auto_hide"), false);
    XRCCTRL(*this, "chkAutoHideLogs", wxCheckBox)->SetValue(en);
    XRCCTRL(*this, "chkAutoShowLogsOnWarning", wxCheckBox)->SetValue(icfg->ReadBool(_T("/comportment/auto_show_warnings"), true));
    XRCCTRL(*this, "chkAutoShowLogsOnError", wxCheckBox)->SetValue(icfg->ReadBool(_T("/comportment/auto_show_errors"), true));
    XRCCTRL(*this, "chkAutoShowLogsOnInformation", wxCheckBox)->SetValue(icfg->ReadBool(_T("/comportment/auto_show_infos"), true));
    XRCCTRL(*this, "chkAutoShowLogsOnWarning", wxCheckBox)->Enable(en);
    XRCCTRL(*this, "chkAutoShowLogsOnError", wxCheckBox)->Enable(en);
    XRCCTRL(*this, "chkAutoShowLogsOnInformation", wxCheckBox)->Enable(en);


    // Now build loggers pages
    wxArrayString loggers = RheiaConfigurationToolsManager::Get()->GetListFor( cgLog );

    wxNotebook* nb = XRCCTRL( *this , "nbMain" , wxNotebook );

    for( int i = 0 ; i < loggers.GetCount() ; ++i )
    {
        RheiaConfigurationPanel* page = RheiaConfigurationToolsManager::Get()->CreateTool( loggers[i] , nb );

        if( page != NULL )
        {
            nb->AddPage( page , page->GetTitle() , false );
            RheiaLoggerPageInfo info;
            info.name = loggers[i];
            info.page = page;

            m_pages[info.name] = info;
        }
    }
}

void RheiaLogMgrSettingsPanel::DoSaveEnvironment()
{
    RheiaConfigurationManager *icfg = RheiaManager::Get()->GetConfigurationManager(_T("log_manager"));

    icfg->Write(_T("/comportment/auto_hide"),                        (bool) XRCCTRL(*this, "chkAutoHideLogs", wxCheckBox)->GetValue());
    icfg->Write(_T("/comportment/auto_show_warnings"),                 (bool) XRCCTRL(*this, "chkAutoShowLogsOnWarning", wxCheckBox)->GetValue());
    icfg->Write(_T("/comportment/auto_show_errors"),         (bool) XRCCTRL(*this, "chkAutoShowLogsOnError", wxCheckBox)->GetValue());
    icfg->Write(_T("/comportment/auto_show_infos"),           (bool) XRCCTRL(*this, "chkAutoShowLogsOnInformation", wxCheckBox)->GetValue());
}

wxString RheiaLogMgrSettingsPanel::GetBitmapBaseName() const
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    return path + wxT("#zip:logmgr_settings");
}

bool RheiaLogMgrSettingsPanel::OnApply()
{
    DoSaveEnvironment();

    RheiaLoggerPageInfoMap::iterator it = m_pages.begin();

    for( ; it != m_pages.end() ; ++it )
        it->second.page->OnApply();

    wxCommandEvent event(RheiaEVT_LOGGER_SETTINGS);
    RheiaEventsManager::Get()->ProcessEvent(event);

    return true;
}

bool RheiaLogMgrSettingsPanel::OnCancel()
{
    return true;
}

void RheiaLogMgrSettingsPanel::OnAutoHideLogs(wxCommandEvent& event)
{
    bool en = XRCCTRL(*this, "chkAutoHideLogs", wxCheckBox)->GetValue();
    XRCCTRL(*this, "chkAutoShowLogsOnWarning", wxCheckBox)->Enable(en);
    XRCCTRL(*this, "chkAutoShowLogsOnError", wxCheckBox)->Enable(en);
    XRCCTRL(*this, "chkAutoShowLogsOnInformation", wxCheckBox)->Enable(en);
}

