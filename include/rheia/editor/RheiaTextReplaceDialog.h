/**
*   @file RheiaTextReplaceDialog.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 13-March-2010
*/
#ifndef RheiaTextReplaceDialog_h
#define RheiaTextReplaceDialog_h

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

/**
*   @class RheiaEditorPropertyPanel
*
*   @brief panel for enabling user editor configuration
* 
*   @author Nicolas Macherey (nm@graymat.fr)
*   @version 0.0.1
*   @date 13-March-2010
*/
class RheiaTextReplaceDialog : public wxDialog
{
private:

protected:
	wxStaticText* m_staticText1;
	wxStaticText* m_staticText2;
	wxCheckBox* m_chkAllDocuments;
	wxStaticLine* m_staticline1;
	wxButton* m_btnYes;
	wxButton* m_btnNo;
	wxButton* m_btnCancel;
	wxButton* m_btnAll;
	int idAll;
	bool m_applyAll;
	bool m_all;
	
	/** Apply to all end modal when clicking the all btn */
	void OnApplyAll( wxCommandEvent& event );

public:
	/** basic ctor */
	RheiaTextReplaceDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Replace text"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 570,162 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER );
	
	/** basic dtor */
	virtual ~RheiaTextReplaceDialog();
	
	/** btn end */
	void OnBtnClick( wxCommandEvent& event );
	
	/** btn end */
	void OnBtnNo( wxCommandEvent& event );
	
	/** Dialog End modal overload */
	virtual void EndModal( int retCode );
	
	/** Check if we shall apply to all other documents or not */
	bool AppyToAllDocuments() {return m_applyAll;};
	
	/** Check if the all btn was clicked */
	bool ApplyAll() {return m_all;};

};

#endif
