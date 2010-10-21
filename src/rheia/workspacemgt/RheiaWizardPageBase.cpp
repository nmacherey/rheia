/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaWizardPageBase.cpp
*
*   This file defines the main object from which any wizard page
*   you want to create shall derive
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 11-May-2009
*   @version 0.0.1
*/


#include "RheiaWizardPageBase.h"

RheiaWizardPageBase::RheiaWizardPageBase( const wxString& name, wxWizard* parent, RheiaWorkspace* workspace , const wxBitmap& bitmap ):
    wxWizardPageSimple( parent , NULL , NULL , bitmap )
{
    m_name = name;
    m_workspace = workspace;
}

RheiaWizardPageBase::~RheiaWizardPageBase()
{

}
