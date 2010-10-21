/** @file dialogs.i
* This file defines derivations for various rheia dialogs in rheia python port
*/

/*%feature("pythonprepend") RheiaConfigurationDialog::RheiaConfigurationDialog(wxWindow* parent) %{
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);
%}

%feature("pythonprepend") RheiaApplicationConfigurationDialog::RheiaApplicationConfigurationDialog(wxWindow* parent) %{
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);
%}

%feature("pythonprepend") RheiaConfigurationPathsDialog::RheiaConfigurationPathsDialog(wxWindow* parent) %{
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);
%}

%feature("pythonprepend") RheiaEnvVarsConfigurationDialog::RheiaEnvVarsConfigurationDialog(wxWindow* parent) %{
	wx.Dialog.__init__(self,args[0],wx.ID_ANY,u"Rheia Configuration Dialog",size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.CAPTION|wx.RESIZE_BORDER|wx.SYSTEM_MENU|wx.CLOSE_BOX|wx.MAXIMIZE_BOX|wx.MINIMIZE_BOX);
%}*/

%include "RheiaConfigurationDialog.h"
%include "RheiaApplicationConfigurationDialog.h"
%include "RheiaConfigurationPathsDialog.h"
%include "RheiaEnvVarsConfigurationDialog.h"

%extend RheiaConfigurationDialog {
	int Display(bool show = true) {return self->Show(show);};
	int DisplayModal() {return self->ShowModal();};
}

%extend RheiaApplicationConfigurationDialog {
	int Display(bool show = true) {return self->Show(show);};
	int DisplayModal() {return self->ShowModal();};
}

%extend RheiaConfigurationPathsDialog {
	int Display(bool show = true) {return self->Show(show);};
	int DisplayModal() {return self->ShowModal();};
}

