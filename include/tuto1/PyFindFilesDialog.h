/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef PYFIND_FILES_DOALOG_H
#define PYFIND_FILES_DOALOG_H

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/dialog.h>

/**
*   @class PyFindFilesDialog
*   @brief Basic dialog for Finding text in files
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class PyFindFilesDialog : public wxDialog
{
private:

protected:
    wxStaticText* m_staticText11;
    wxComboBox* cbFindText;
    wxCheckBox* chkWholeWord;
    wxCheckBox* chkStartWord;
    wxCheckBox* chkMatchCase;
    wxCheckBox* chkWrapAtEof;
    wxRadioBox* rbScope;
    wxStaticText* m_staticText14;
    wxTextCtrl* txtPath;
    wxButton* btnSelPath;
    wxStaticText* m_staticText15;
    wxTextCtrl* txtMask;

    wxStaticText* m_staticText17;
    wxCheckBox* chkRecursive;
    wxCheckBox* chkHiddenFiles;
    wxStaticLine* m_staticline6;
    wxStdDialogButtonSizer* m_sdbSizer5;
    wxButton* m_sdbSizer5OK;
    wxButton* m_sdbSizer5Cancel;

public:

    PyFindFilesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find in files"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 516,421 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
    ~PyFindFilesDialog();

};

#endif //PYFIND_FILES_DOALOG_H

