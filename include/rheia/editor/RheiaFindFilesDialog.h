/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
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

#define MAX_FIND_HIST 30

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
	/****************************************************************************
	 * GUI ELEMENTS
	 ***************************************************************************/
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
	
	wxArrayString m_history;
	
	/****************************************************************************
	 * PRIVATE MEMBERS FOR GETTING USER SELECTION BACK TO THE APPLICATION
	 ***************************************************************************/
	wxString m_expr;
	bool m_wholeWord;
	bool m_startWord;
	bool m_matchCase;
	bool m_wrapAtEOF;
	int m_scope; // 0: current, 1: Open files, 2: path
	
	wxString m_path;
	wxString m_masks;
	bool m_recursive;
	bool m_hiddenFiles;
	
	/****************************************************************************
	 * EVENT IDs
	 ***************************************************************************/
	int idRbScope;
	int idSelectpath;
	
	/****************************************************************************
	 * HELPERS
	 ***************************************************************************/
	/** enable/disable all controls in serach paths */
	void EnableSearchPaths(bool value = false);
public:
	/****************************************************************************
	 * CONSTRUCTORS AND DESTRUCTORS
	 ***************************************************************************/
	/** ctor */
    RheiaFindFilesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find in files"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 516,421 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
    
	/** dtor */
	virtual ~RheiaFindFilesDialog();
	
	/****************************************************************************
	 * METHODS
	 ***************************************************************************/
	/** overloads the EndModal method for managing information */
	virtual void EndModal( int retCode );
	
	/****************************************************************************
	 * EVENTS
	 ***************************************************************************/
	/** Callback used when the user change the scope */
	void OnScopeChange(wxCommandEvent& event);
	
	/** Callback used when the user wants to select a path for the search */
	void OnBtnSearchPath(wxCommandEvent& event);
	
	/****************************************************************************
	 * ACCESSORS
	 ***************************************************************************/
	/** Check if whole words are concerned by the find */
	bool WholeWord(){return m_wholeWord;};
	
	/** Check if the find concerned also start words */
	bool StartWord(){return m_startWord;};
	
	/** Check if the find shall concider case matching */
	bool MatchCase(){return m_matchCase;};
	
	/** Get the search scope */
	int Scope() {return m_scope;};
	
	/** Get the search path */
	wxString GetPath() {return m_path;};
	
	/** Get the search masks */
	wxString GetMasks() {return m_masks;};
	
	/** Check if the search shall be recursive or not */
	bool Recursive() {return m_recursive;};
	
	/** Check if the search shall include hidden files or not */
	bool Hiddens() {return m_hiddenFiles;};
	
	/** Get the expression to find */
	wxString GetExpr() {return m_expr;};
};

#endif //RheiaFind_FILES_DOALOG_H

