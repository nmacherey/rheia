/**
*   @file RheiaPythonHandler.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaPythonHandler.h"
#include "RheiaEditorFile.h"
#include "RheiaPythonLayout.h"

#include <wx/filefn.h>

REGISTER_EDITOR_HANDLER(RheiaPythonHandler)

namespace
{
    const wxString ext = wxT("py");
    const wxString lang = wxT("Python");
}

RheiaPythonHandler::RheiaPythonHandler():
    RheiaEditorHandler()
{

}

RheiaPythonHandler::RheiaPythonHandler(const RheiaPythonHandler& rhs):
    RheiaEditorHandler(rhs)
{

}

RheiaPythonHandler::~RheiaPythonHandler()
{

}

RheiaEditorHandler* RheiaPythonHandler::Clone()
{
    return new RheiaPythonHandler(*this);
}

bool RheiaPythonHandler::CanHandle( const wxString& file )
{
    wxFileName fn(file);
    wxString extension = fn.GetExt();

    if( extension == ext )
        return true;

    return false;
}

bool RheiaPythonHandler::CanHandle( RheiaEditorLayout* context )
{
    if( context->IsKindOf( CLASSINFO(RheiaPythonLayout) ) )
        return true;

    return false;
}

wxArrayString RheiaPythonHandler::GetExtensions()
{
    wxArrayString ret;
    ret.Add( wxT("Python files (*.py)|*.py") );

    return ret;
}

RheiaEditorLayout* RheiaPythonHandler::CreateContext( )
{
    return new RheiaPythonLayout();
}

wxArrayString RheiaPythonHandler::GetLanguages()
{
    wxArrayString ret;
    ret.Add(lang);

    return ret;
}