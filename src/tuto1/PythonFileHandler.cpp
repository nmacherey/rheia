/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "PythonFileHandler.h"
#include "PyFile.h"
#include "PyContext.h"

#include <wx/filefn.h>

namespace
{
    const wxString ext = wxT("py");
    const wxString lang = wxT("Python");
}

PythonFileHandler::PythonFileHandler():
    PyFileHandler()
{

}

PythonFileHandler::PythonFileHandler(const PythonFileHandler& rhs):
    PyFileHandler(rhs)
{

}

PythonFileHandler::~PythonFileHandler()
{

}

PyFileHandler* PythonFileHandler::Clone()
{
    return new PythonFileHandler(*this);
}

bool PythonFileHandler::CanHandle( const wxString& file )
{
    wxFileName fn(file);
    wxString extension = fn.GetExt();

    if( extension == ext )
        return true;

    return false;
}

bool PythonFileHandler::CanHandle( PyEditorContext* context )
{
    if( context->IsKindOf( CLASSINFO(PyContext) ) )
        return true;

    return false;
}

wxArrayString PythonFileHandler::GetExtensions()
{
    wxArrayString ret;
    ret.Add( wxT("Python files (*.py)|*.py") );

    return ret;
}

PyEditorContext* PythonFileHandler::CreateContext( )
{
    return new PyContext();
}

wxArrayString PythonFileHandler::GetLanguages()
{
    wxArrayString ret;
    ret.Add(lang);

    return ret;
}
