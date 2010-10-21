/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */
#ifndef CPPCONTEXT_H
#define CPPCONTEXT_H

#include "PyEditorContext.h"

/**
*   @class CppContext
*   @brief this is the basic class for handling styled text control informations
*/
class CppContext : public PyEditorContext
{
    DECLARE_DYNAMIC_CLASS(CppContext)

public :
    /**************************************************************************************
    *   CONSTRUCTORS
    **************************************************************************************/
    /** default ctor */
    CppContext(){}

    /** default dtor */
    virtual ~CppContext(){}

    /** get the lexer */
    virtual int GetLexer(){return wxSTC_LEX_CPP;};

    /** get keywords sets */
    virtual wxArrayString GetKeywords();

    /** set the syles for the given control */
    virtual void SetStyles( wxStyledTextCtrl* control );
};

#endif

