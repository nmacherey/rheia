/**
*	@file RheiaEnvVarsSelectionDialog.h
*
*   Dialog for environement variables configuration
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/
#ifndef RheiaEnvVarsSelectionDialog_h_
#define RheiaEnvVarsSelectionDialog_h_

#include <wx/dialog.h>
#include <wx/aui/aui.h>
#include <RheiaBaseSettings.h>
#include <RheiaGlobals.h>


class wxListbookEvent;
class wxCheckListBox;

/**
*	@class RheiaEnvVarsSelectionDialog
*
*   Revision : 20-November-2009
*       Nicolas Macherey (nm@graymat.fr)
*       Changes : Commentaries
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date 23-September-2009
*	@version 0.0.1
*/

class BASE_DLLEXPORT RheiaEnvVarsSelectionDialog : public wxDialog
{
public:
    /******************************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    ******************************************************************************************************/
    /** default constructor taking the parent in input */
    RheiaEnvVarsSelectionDialog(wxWindow* parent);

    /******************************************************************************************************
    *   METHODS
    ******************************************************************************************************/
    /** end modal function overload */
    virtual void EndModal(int retCode);

    /** Set the key */
    void SetKey( const wxString& name );

    /** Set the value */
    void SetValue( const wxString& value );

    /** Get the key */
    wxString GetKey( ) {return m_key;}

    /** Get the value */
    wxString GetValue( ) {return m_value;}

protected:

    /******************************************************************************************************
    *   PRIVATE METHODS
    ******************************************************************************************************/
    /** Update the list */
    void DoUpdateList();

    /******************************************************************************************************
    *   EVENTS
    ******************************************************************************************************/
    /** Update ui event */
    void OnUpdateUI(wxUpdateUIEvent& event);

    /** Callback used when the user wants to edit a variable */
    void OnBrowse( wxCommandEvent& event );

private:
    wxString m_key;
    wxString m_value;
    DECLARE_EVENT_TABLE()
};

#endif

