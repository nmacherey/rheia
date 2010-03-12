/**
*   @file RheiaPythonHandler.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef PYTHON_HANDLER_H
#define PYTHON_HANDLER_H

#include "RheiaEditorSettings.h"
#include "RheiaEditorManager.h"

/**
*   @class RheiaPythonHandler
*   @brief simple class for handling new file types
*
*   Any file that can be loaded in our editor shall be derived from this one
*   any handler will provide info about file loading in PyEditor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaPythonHandler : public RheiaEditorHandler
{
public :
    /** default constructor for handling a file */
    RheiaPythonHandler();

    /** destructor */
    virtual ~RheiaPythonHandler();

    /** copy ctor */
    RheiaPythonHandler(const RheiaPythonHandler& rhs);

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
