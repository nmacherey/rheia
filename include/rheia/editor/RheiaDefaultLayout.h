/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaDefaultLayout.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef RheiaDefaultLayout_H
#define RheiaDefaultLayout_H

#include "RheiaEditorLayout.h"

/**
*   @class RheiaDefaultLayout
*   @brief this is the basic class for handling styled text control informations
*/
class EDITOR_DLLEXPORT RheiaDefaultLayout : public RheiaEditorLayout
{
    DECLARE_DYNAMIC_CLASS(RheiaDefaultLayout)

public :
    /**************************************************************************************
    *   CONSTRUCTORS
    **************************************************************************************/
    /** default ctor */
    RheiaDefaultLayout(){}

    /** default dtor */
    virtual ~RheiaDefaultLayout(){}

    /** get the lexer */
    virtual int GetLexer(){return wxSTC_LEX_CPP;};

    /** get keywords sets */
    virtual wxArrayString GetKeywords();

    /** set the syles for the given control */
    virtual void SetStyles( wxStyledTextCtrl* control );
};

#endif
