/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaApplyRegExDialog.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef RheiaApply_REGEX_DIALOG_H
#define RheiaApply_REGEX_DIALOG_H

#include <wx/string.h>
#include <wx/combobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/regex.h>

#include "RheiaEditorSettings.h"

#define MAX_REGEX_HIST 30

/**
*   @class RheiaApplyRegExDialog
*   @brief This class is a basic wrapper for defining an editor in the python editor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaApplyRegExDialog : public wxDialog
{
private:
    bool m_selOnly;
    bool m_currentFile;
    bool m_allFiles;
    int m_flags;
    wxString m_expr;
    wxString m_replace;

    wxRegEx m_regex;
    wxArrayString m_history;
    wxArrayString m_rephistory;

protected:
    wxComboBox* cbRegEx;
    wxComboBox* cbReplacement;
    wxRadioBox* rbReApply;
    wxCheckBox* chkReExtended;
    wxCheckBox* chkReAdvanced;
    wxCheckBox* chkReBasic;
    wxCheckBox* chkReIgnore;
    wxCheckBox* chkReNosub;
    wxCheckBox* chkReNewline;
    wxStaticText* m_staticText9;

    wxStaticText* m_staticText10;

    wxCheckBox* chkReStartLine;
    wxCheckBox* chkReEnd;
    wxStaticLine* m_staticline4;
    wxStdDialogButtonSizer* m_sdbSizer2;
    wxButton* m_sdbSizer2OK;
    wxButton* m_sdbSizer2Cancel;

public:

    RheiaApplyRegExDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Apply regular expression"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 836,533 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
    ~RheiaApplyRegExDialog();

    void EndModal(int retCode );

    bool SelectionOnly() {return m_selOnly;};
    bool CurrentFile() {return m_currentFile;}
    bool AllFiles() {return m_allFiles;}
    int GetFlags() {return m_flags; };
    wxString GetExpr() {return m_expr;}
    wxString GetReplacementString() {return m_replace;}
};

#endif //RheiaApply_REGEX_DIALOG_H

