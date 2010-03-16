/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaDefaultLayout.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaDefaultLayout.h"

IMPLEMENT_DYNAMIC_CLASS(RheiaDefaultLayout,RheiaEditorLayout)

namespace LexDefault
{
    const wxString keywords0 = _("");
    const wxString keywords1 = _("");
}

wxArrayString RheiaDefaultLayout::GetKeywords()
{
    wxArrayString ret;

    return ret;
}

void RheiaDefaultLayout::SetStyles( wxStyledTextCtrl* WXUNUSED(control) )
{
}
