
/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "CppContext.h"

IMPLEMENT_DYNAMIC_CLASS(CppContext,PyEditorContext)

namespace LexCpp
{
    const wxString keywords0 = _("asm auto bool break case catch char class const const_cast continue default delete do double dynamic_cast else enum explicit export extern "
                                   "false float for friend goto if inline int long mutable namespace new operator private protected public register reinterpret_cast restrict return short signed "
                                   "sizeof static static_cast struct switch template this throw true try typedef typeid typename union unsigned using virtual void volatile while "
                                   "int8_t uint8_t int16_t uint16_t int32_t uint32_t int64_t uint64_t int_least8_t uint_least8_t int_least16_t uint_least16_t int_least32_t uint_least32_t "
                                   "int_least64_t uint_least64_t int_fast8_t uint_fast8_t int_fast16_t uint_fast16_t int_fast32_t uint_fast32_t int_fast64_t uint_fast64_t "
                                   "intptr_t uintptr_t intmax_t uintmax_t wint_t wchar_t wctrans_t wctype_t size_t time_t and and_eq bitand bitor compl not not_eq or or_eq xor xor_eq "
                                   " complex imaginary _Complex _Imaginary _Bool _Pragma");

    const wxString keywords1 = wxT("");

    const wxString keywords2 = _("a addindex addtogroup anchor arg attention author b brief bug c class code date def defgroup deprecated "
                                   "dontinclude e em endcode endhtmlonly endif endlatexonly endlink endverbatim enum example exception f$ f[ f] file fn "
                                   "hideinitializer htmlinclude htmlonly if image include ingroup internal invariant interface latexonly li line link mainpage name "
                                   "namespace nosubgrouping note overload p page par param post pre ref relates remarks return retval sa section see showinitializer "
                                   "since skip skipline struct subsection test throw todo typedef union until var verbatim verbinclude version warning weakgroup "
                                   "$ @ \\ & < > # { }");
}

wxArrayString CppContext::GetKeywords()
{
    wxArrayString ret;
    ret.Add( LexCpp::keywords0 );
    ret.Add( LexCpp::keywords1 );
    ret.Add( LexCpp::keywords2 );

    return ret;
}

void CppContext::SetStyles( wxStyledTextCtrl* control )
{
    control->StyleSetSpec(wxSTC_STYLE_LINENUMBER, wxT("back:#E0E0E0,face:Monospace"));
    control->StyleSetSpec(wxSTC_STYLE_CONTROLCHAR, wxT("face:Courier"));
    control->StyleSetSpec(wxSTC_STYLE_BRACELIGHT, wxT("fore:#0000FF,back:#FFFF88"));
    control->StyleSetSpec(wxSTC_STYLE_BRACEBAD, wxT("fore:#FF0000,back:#FFFF88"));
    control->StyleSetSpec(wxSTC_C_PREPROCESSOR, wxT("fore:#7F007F,face:Monospace"));
    control->StyleSetSpec(wxSTC_C_GLOBALCLASS, wxT("fore:#FF0000,bold,italic"));

    control->StyleSetSpec(wxSTC_C_DEFAULT, wxT("face:Monospace"));
    control->StyleSetSpec(wxSTC_C_COMMENTLINE, wxT("fore:#007F00,face:Monospace"));
    control->StyleSetSpec(wxSTC_C_NUMBER, wxT("fore:#0000C0,face:Monospace"));
    control->StyleSetSpec(wxSTC_C_STRING, wxT("fore:#7F007F,face:Monospace,italic"));
    control->StyleSetSpec(wxSTC_C_STRINGEOL, wxT("fore:#7F007F,face:Monospace"));
    control->StyleSetSpec(wxSTC_C_CHARACTER, wxT("fore:#7F007F,face:Monospace"));
    control->StyleSetSpec(wxSTC_C_WORD, wxT("fore:#00007F,bold"));
    control->StyleSetSpec(wxSTC_C_WORD2, wxT("fore:#00007F,italic,bold"));
    control->StyleSetSpec(wxSTC_C_OPERATOR, wxT(""));
    control->StyleSetSpec(wxSTC_C_IDENTIFIER, wxT(""));
    control->StyleSetSpec(wxSTC_C_COMMENTDOC, wxT("fore:#OO7F7F"));
    control->StyleSetSpec(wxSTC_C_COMMENTDOCKEYWORD, wxT("fore:#OO7F7F"));
    control->StyleSetSpec(wxSTC_C_COMMENTLINEDOC, wxT("fore:#OO7F7F"));
    control->StyleSetSpec(wxSTC_C_STRINGEOL, wxT("fore:#000000,face:Monospace,back:#E0C0E0,eolfilled"));
}
