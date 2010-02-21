
/**
*   @file RheiaDockSystSettingsPanel.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 17-November-2009
*/
#include "RheiaDockSystSettingsPanel.h"

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
#include <RheiaConfigurationToolsManager.h>
#include <RheiaEventsManager.h>
#include <RheiaEvents.h>

REGISTER_CONFIGURATION_TOOL( RheiaDockSystSettingsPanel )

namespace
{
    // buttons for the docking system
    int btnAuiActiveCaptionColour = XRCID("btnAuiActiveCaptionColour");
    int btnAuiActiveCaptionGradientColour = XRCID("btnAuiActiveCaptionGradientColour");
    int btnAuiActiveCaptionTextColour = XRCID("btnAuiActiveCaptionTextColour");
    int btnAuiInactiveCaptionColour = XRCID("btnAuiInactiveCaptionColour");
    int btnAuiInactiveCaptionGradientColour = XRCID("btnAuiInactiveCaptionGradientColour");
    int btnAuiInactiveCaptionTextColour = XRCID("btnAuiInactiveCaptionTextColour");
}

BEGIN_EVENT_TABLE(RheiaDockSystSettingsPanel,RheiaConfigurationPanel)
    EVT_BUTTON(btnAuiActiveCaptionColour, RheiaDockSystSettingsPanel::OnChooseColour)
    EVT_BUTTON(btnAuiActiveCaptionGradientColour, RheiaDockSystSettingsPanel::OnChooseColour)
    EVT_BUTTON(btnAuiActiveCaptionTextColour, RheiaDockSystSettingsPanel::OnChooseColour)
    EVT_BUTTON(btnAuiInactiveCaptionColour, RheiaDockSystSettingsPanel::OnChooseColour)
    EVT_BUTTON(btnAuiInactiveCaptionGradientColour, RheiaDockSystSettingsPanel::OnChooseColour)
    EVT_BUTTON(btnAuiInactiveCaptionTextColour, RheiaDockSystSettingsPanel::OnChooseColour)
END_EVENT_TABLE()

RheiaDockSystSettingsPanel::RheiaDockSystSettingsPanel( wxWindow* parent ):
    RheiaConfigurationPanel()
{
    wxString resPath = RheiaStandardPaths::DataDirectoryGlobal();
    wxString xrcDialogName = _T("panelDockSystSettings");

    wxXmlResource *myres = wxXmlResource::Get();

    if ( !myres->Load(resPath + _T("/resource.zip#zip:docksystconf_panel.xrc")) )
        wxMessageBox(_("Error loadding ressource") , _("Error") );

    myres->LoadPanel(this, parent, xrcDialogName);
    DoInitEnvironment();
}

void RheiaDockSystSettingsPanel::DoInitEnvironment()
{
    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();

    XRCCTRL(*this, "spnAuiBorder", wxSpinCtrl)->SetValue(cfg->ReadInt(_T("/environment/aui/border_size"), DEFAULT_PANE_BORDER));
    XRCCTRL(*this, "spnAuiSash", wxSpinCtrl)->SetValue(cfg->ReadInt(_T("/environment/aui/sash_size"), DEFAULT_SASH_SIZE));
    XRCCTRL(*this, "spnAuiCaption", wxSpinCtrl)->SetValue(cfg->ReadInt(_T("/environment/aui/caption_size"), DEFAULT_CAPTION_SIZE));
    XRCCTRL(*this, "btnAuiActiveCaptionColour", wxButton)->SetBackgroundColour(cfg->ReadColour(_T("/environment/aui/active_caption_colour"), DEFAULT_ACTIVE_CAPTION));
    XRCCTRL(*this, "btnAuiActiveCaptionGradientColour", wxButton)->SetBackgroundColour(cfg->ReadColour(_T("/environment/aui/active_caption_gradient_colour"), DEFAULT_ACTIVE_CAPTION_GRADIENT));
    XRCCTRL(*this, "btnAuiActiveCaptionTextColour", wxButton)->SetBackgroundColour(cfg->ReadColour(_T("/environment/aui/active_caption_text_colour"), DEFAULT_ACTIVE_TEXT_GRADIENT));
    XRCCTRL(*this, "btnAuiInactiveCaptionColour", wxButton)->SetBackgroundColour(cfg->ReadColour(_T("/environment/aui/inactive_caption_colour"), DEFAULT_INACTIVE_CAPTION));
    XRCCTRL(*this, "btnAuiInactiveCaptionGradientColour", wxButton)->SetBackgroundColour(cfg->ReadColour(_T("/environment/aui/inactive_caption_gradient_colour"), DEFAULT_INACTIVE_CAPTION_GRADIENT));
    XRCCTRL(*this, "btnAuiInactiveCaptionTextColour", wxButton)->SetBackgroundColour(cfg->ReadColour(_T("/environment/aui/inactive_caption_text_colour"), DEFAULT_INACTIVE_TEXT_GRADIENT));
}

void RheiaDockSystSettingsPanel::DoSaveEnvironment()
{
    RheiaConfigurationManager *cfg = RheiaProfileManager::Get()->GetActiveProfileManager();

    cfg->Write(_T("/environment/aui/border_size"),          (int)XRCCTRL(*this, "spnAuiBorder", wxSpinCtrl)->GetValue());
    cfg->Write(_T("/environment/aui/sash_size"),            (int)XRCCTRL(*this, "spnAuiSash", wxSpinCtrl)->GetValue());
    cfg->Write(_T("/environment/aui/caption_size"),         (int)XRCCTRL(*this, "spnAuiCaption", wxSpinCtrl)->GetValue());
    cfg->Write(_T("/environment/aui/active_caption_colour"),             XRCCTRL(*this, "btnAuiActiveCaptionColour", wxButton)->GetBackgroundColour());
    cfg->Write(_T("/environment/aui/active_caption_gradient_colour"),    XRCCTRL(*this, "btnAuiActiveCaptionGradientColour", wxButton)->GetBackgroundColour());
    cfg->Write(_T("/environment/aui/active_caption_text_colour"),        XRCCTRL(*this, "btnAuiActiveCaptionTextColour", wxButton)->GetBackgroundColour());
    cfg->Write(_T("/environment/aui/inactive_caption_colour"),           XRCCTRL(*this, "btnAuiInactiveCaptionColour", wxButton)->GetBackgroundColour());
    cfg->Write(_T("/environment/aui/inactive_caption_gradient_colour"),  XRCCTRL(*this, "btnAuiInactiveCaptionGradientColour", wxButton)->GetBackgroundColour());
    cfg->Write(_T("/environment/aui/inactive_caption_text_colour"),      XRCCTRL(*this, "btnAuiInactiveCaptionTextColour", wxButton)->GetBackgroundColour());

    wxCommandEvent event(RheiaEVT_LAYOUT_SETTINGS_CHANGED);
    RheiaEventsManager::Get()->ProcessEvent(event);
}

wxString RheiaDockSystSettingsPanel::GetBitmapBaseName() const
{
    wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") , rspfDataGlobal );
    return path + wxT("#zip:docksyst_settings");
}

bool RheiaDockSystSettingsPanel::OnApply()
{
    DoSaveEnvironment();
    return true;
}

bool RheiaDockSystSettingsPanel::OnCancel()
{
    return true;
}

void RheiaDockSystSettingsPanel::OnChooseColour(wxCommandEvent& event)
{
    wxColourData data;
    wxWindow* sender = FindWindowById(event.GetId());
    data.SetColour(sender->GetBackgroundColour());

    wxColourDialog dlg(this, &data);

    if (dlg.ShowModal() == wxID_OK)
    {
        wxColour colour = dlg.GetColourData().GetColour();
        sender->SetBackgroundColour(colour);
    }
}
