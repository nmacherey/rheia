/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */
#ifndef PYEDITOR_CONTEXT_H
#define PYEDITOR_CONTEXT_H

#include <RheiaGlobals.h>
#include <wx/stc/stc.h>
#include <map>

typedef std::map<wxString,wxString> wxStcPropertyMap;

/**
*   @class PyEditorContext
*   @brief this is the basic class for handling styled text control informations
*/
class PyEditorContext : public wxObject
{
    DECLARE_ABSTRACT_CLASS(PyEditorContext)

public :
    /**************************************************************************************
    *   CONSTRUCTORS
    **************************************************************************************/
    /** default ctor */
    PyEditorContext(){}

    /** default dtor */
    virtual ~PyEditorContext(){}

    /** get the lexer */
    virtual int GetLexer() = 0;

    /** get keywords sets */
    virtual wxArrayString GetKeywords() = 0;

    /** get use tabs */
    virtual bool UseTabs() {return false;}

    /** get use tabs */
    virtual bool TabIndents() {return true;}

    /** get tab width */
    virtual int TabWidth() {return 4;};

    /** get indent size in spaces */
    virtual int GetIndents() {return 4;};

    /** get backspace unindent */
    virtual bool BackspaceUnIndents() {return true;}

    /** view eol */
    virtual bool ViewEOL() {return false;}

    /** View white space */
    virtual bool ViewWhiteSpace() {return false;}

    /** get property map */
    virtual wxStcPropertyMap GetPropertyMap()
    {
        wxStcPropertyMap m_props;
        m_props[ wxT("fold")] = wxT("1");
        m_props[ wxT("fold.html")] = wxT("1");
        m_props[ wxT("styling.within.preprocessor")] = wxT("1");
        m_props[ wxT("fold.comment")] = wxT("1");
        m_props[ wxT("fold.compact")] = wxT("1");
        m_props[ wxT("fold.comment.python")] = wxT("1");
        m_props[ wxT("fold.quotes.python")] = wxT("1");
        m_props[ wxT("fold.at.else")] = wxT("1");

        return m_props;
    }

    /** Get mode event mask */
    virtual int GetModEventMask() {return (wxSTC_MOD_DELETETEXT | wxSTC_MOD_INSERTTEXT  | wxSTC_PERFORMED_UNDO  | wxSTC_PERFORMED_REDO | wxSTC_MOD_BEFOREDELETE);}

    /** Get the xCarret policy */
    virtual int GetXCaretPolicy()
    {
        int caretSlop = 1;
        int caretStrict = 0;
        int caretEven = 0;
        int caretJumps = 0;

        return (caretStrict | caretSlop | caretEven | caretJumps);
    }

    virtual int GetXCaretZone() {return 20 ;}

    /** Get the YCaret policy */
    virtual int GetYCaretPolicy()
    {
        int caretSlop = 1;
        int caretStrict = 4;
        int caretEven = 8;
        int caretJumps = 0;

        return (caretStrict | caretSlop | caretEven | caretJumps);
    }

    virtual int GetYCaretZone() {return 1 ;}

    /** get fold flags */
    virtual int GetFoldFlags() {return wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED;}

    /** get edgemode */
    virtual int GetEdgeMode() {return 0;}

    /** get edge colour */
    virtual wxColour GetEdgeColour() {return *wxLIGHT_GREY;};

    /** get the edge column */
    virtual int GetEdgeColumn() {return 80;}

    /** get the folding style */
    virtual wxString GetFoldStyle() {return wxT("Arrows");}

    /** get indentation guides */
    virtual bool GetIndentationGuides(){return true;}

    /** get the layout cache */
    virtual int GetLayoutCache() {return wxSTC_CACHE_DOCUMENT;}

    /** set the syles for the given control */
    virtual void SetStyles( wxStyledTextCtrl* control ) = 0;
};

#endif
