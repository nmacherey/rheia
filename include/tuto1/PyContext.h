/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */
#ifndef PYCONTEXT_H
#define PYCONTEXT_H

#include "PyEditorContext.h"

/**
*   @class PyContext
*   @brief this is the basic class for handling styled text control informations
*/
class PyContext : public PyEditorContext
{
    DECLARE_DYNAMIC_CLASS(PyContext)

public :
    /**************************************************************************************
    *   CONSTRUCTORS
    **************************************************************************************/
    /** default ctor */
    PyContext(){}

    /** default dtor */
    virtual ~PyContext(){}

    /** get the lexer */
    virtual int GetLexer(){return wxSTC_LEX_PYTHON;};

    /** get keywords sets */
    virtual wxArrayString GetKeywords();

    /** set the syles for the given control */
    virtual void SetStyles( wxStyledTextCtrl* control );
};

#endif
