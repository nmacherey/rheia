/**
*   @file RheiaFindFilesDialog.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef RheiaFind_FILES_DOALOG_H
#define RheiaFind_FILES_DOALOG_H

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

#include "RheiaEditorSettings.h"

/**
*   @class RheiaFindFilesDialog
*   @brief Basic dialog for Finding text in files
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaFindFilesDialog : public wxDialog
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

    RheiaFindFilesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find in files"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 516,421 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
    ~RheiaFindFilesDialog();

};

#endif //RheiaFind_FILES_DOALOG_H

