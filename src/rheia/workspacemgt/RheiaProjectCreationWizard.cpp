/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
#include <RheiaProjectCreationWizard.h>

#include <RheiaWorkspace.h>
#include <RheiaEnvironmentPlugin.h>
#include <RheiaProject.h>
#include <RheiaAppGlobals.h>
#include <RheiaWizardPageBase.h>

#include <wx/image.h>
#include <wx/wizard.h>
#include <wx/imaglist.h>
#include <wx/msgdlg.h>
#include <wx/choice.h>
#include <wx/xrc/xmlres.h>
#include <wx/toolbar.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/dirdlg.h>

RheiaProjectCreationWizard::RheiaProjectCreationWizard( wxWizard* wizard,RheiaManagedFrame* parent, RheiaWorkspace *workspace )
{
    m_wizard = wizard;
    m_workspace = workspace;
    m_parent = parent;
}

RheiaProjectCreationWizard::~RheiaProjectCreationWizard()
{

}

void RheiaProjectCreationWizard::BuildPages()
{
    DoBuildPages();

    for (size_t i = 1; i < m_pages.GetCount(); ++i)
        wxWizardPageSimple::Chain(m_pages[i - 1], m_pages[i]);

    // allow the wizard to size itself around the pages
    for (size_t i = 0; i < m_pages.GetCount(); ++i)
        m_wizard->GetPageAreaSizer()->Add(m_pages[i]);

    m_wizard->Fit();
}
