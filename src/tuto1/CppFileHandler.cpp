/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "CppFileHandler.h"
#include "PyFile.h"
#include "CppContext.h"

#include <wx/filefn.h>

namespace
{
    const wxString ext1 = wxT("cpp");
    const wxString ext2 = wxT("cxx");
    const wxString ext3 = wxT("c");
    const wxString ext4 = wxT("h");
    const wxString ext5 = wxT("hpp");
    const wxString lang = wxT("C/C++");
}

CppFileHandler::CppFileHandler():
    PyFileHandler()
{

}

CppFileHandler::CppFileHandler(const CppFileHandler& rhs):
    PyFileHandler(rhs)
{

}

CppFileHandler::~CppFileHandler()
{

}

PyFileHandler* CppFileHandler::Clone()
{
    return new CppFileHandler(*this);
}

bool CppFileHandler::CanHandle( const wxString& file )
{
    wxFileName fn(file);
    wxString extension = fn.GetExt();

    if( extension == ext1 ||
        extension == ext2 ||
        extension == ext3 ||
        extension == ext4 ||
        extension == ext5 )
        return true;

    return false;
}

bool CppFileHandler::CanHandle( PyEditorContext* context )
{
    if( context->IsKindOf( CLASSINFO(CppContext) ) )
        return true;

    return false;
}

wxArrayString CppFileHandler::GetExtensions()
{
    wxArrayString ret;
    ret.Add( wxT("C/C++ files (*.h;*.cpp;*.hpp;*.cxx;*.c)|*.h;*.cpp;*.hpp;*.cxx;*.c") );

    return ret;
}

PyEditorContext* CppFileHandler::CreateContext( )
{
    return new CppContext();
}

wxArrayString CppFileHandler::GetLanguages()
{
    wxArrayString ret;
    ret.Add(lang);

    return ret;
}

