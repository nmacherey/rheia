/**
*   @file PyUtils.h
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@date	27-January-2010
*	@version 0.0.2
*/

#ifndef PYUTILS_H
#define PYUTILS_H

#include <wx/string.h>

extern bool PythonEvalString( const wxString& command, wxString& result );

#endif
