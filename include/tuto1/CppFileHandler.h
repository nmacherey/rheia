/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef CPP_FILE_HANDLER_H
#define CPP_FILE_HANDLER_H

#include "PyFileManager.h"

/**
*   @class CppFileHandler
*   @brief simple class for handling new file types
*
*   Any file that can be loaded in our editor shall be derived from this one
*   any handler will provide info about file loading in PyEditor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class CppFileHandler : public PyFileHandler
{
public :
    /** default constructor for handling a file */
    CppFileHandler();

    /** destructor */
    virtual ~CppFileHandler();

    /** copy ctor */
    CppFileHandler(const CppFileHandler& rhs);

    /** Clone method that you have to overload */
    virtual PyFileHandler* Clone();

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( const wxString& file );

    /** check if the given file can be handled by the handler */
    virtual bool CanHandle( PyEditorContext* context );

    /** Get global extensions */
    virtual wxArrayString GetExtensions();

    /** Create a new file */
    virtual PyEditorContext* CreateContext( );

    /** Get the file names list */
    virtual wxArrayString GetLanguages();
};

#endif

