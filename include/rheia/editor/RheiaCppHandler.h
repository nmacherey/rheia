/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaCppHandler.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef Cpp_HANDLER_H
#define Cpp_HANDLER_H

#include "RheiaEditorSettings.h"
#include "RheiaEditorManager.h"

/**
*   @class RheiaCppHandler
*   @brief simple class for handling new file types
*
*   Any file that can be loaded in our editor shall be derived from this one
*   any handler will provide info about file loading in PyEditor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaCppHandler : public RheiaEditorHandler
{
public :
    /** default constructor for handling a file */
    RheiaCppHandler();

    /** destructor */
    virtual ~RheiaCppHandler();

    /** copy ctor */
    RheiaCppHandler(const RheiaCppHandler& rhs);

    /** Clone method that you have to overload */
    virtual RheiaEditorHandler* Clone();

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( const wxString& file );

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( RheiaEditorLayout* context );

    /** Get global extensions */
    virtual wxArrayString GetExtensions();

    /** Create a new file */
    virtual RheiaEditorLayout* CreateContext( );

    /** Get the file names list */
    virtual wxArrayString GetLanguages();
};

#endif
