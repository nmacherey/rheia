
%feature("pythonprepend") RheiaApplicationGeneralPanel::RheiaApplicationGeneralPanel(wxWindow* parent) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%feature("pythonprepend") RheiaBookConfigurationPanel::RheiaBookConfigurationPanel(wxWindow* parent, RheiaConfigurationManager* cfg) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%feature("pythonprepend") RheiaCenterMgrSettingsPanel::RheiaCenterMgrSettingsPanel(wxWindow* parent) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%feature("pythonprepend") RheiaDockSystSettingsPanel::RheiaDockSystSettingsPanel(wxWindow* parent) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%feature("pythonprepend") RheiaInfoMgrSettingsPanel::RheiaInfoMgrSettingsPanel(wxWindow* parent) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%feature("pythonprepend") RheiaInfoPage::RheiaInfoPage(wxWindow* parent) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%feature("pythonprepend") RheiaLeftMgrSettingsPanel::RheiaLeftMgrSettingsPanel(wxWindow* parent) %{
	wx.Panel.__init__(self,args[0],wx.ID_ANY);
%}

%include "RheiaApplicationGeneralPanel.h"
%include "RheiaBookConfigurationPanel.h"
%include "RheiaCenterMgrSettingsPanel.h"
%include "RheiaDockSystSettingsPanel.h"
%include "RheiaInfoMgrSettingsPanel.h"
%include "RheiaInfoPage.h"
%include "RheiaLeftMgrSettingsPanel.h"
