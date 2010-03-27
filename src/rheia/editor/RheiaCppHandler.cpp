/**
* This file is licensed under the Rheia License, Please see LICENSE.TXT for more information.
* If the LICENSE.TXT has not been distributed with this file please refer to support@rheia-framework.com. 
* Rheia is not a free software and in any case you shall use it without agreeing with the terms of the license agreement 
*/
/**
*   @file RheiaCppHandler.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaCppHandler.h"
#include "RheiaEditorFile.h"
#include "RheiaCppLayout.h"

#include <wx/filefn.h>

REGISTER_EDITOR_HANDLER(RheiaCppHandler)

namespace
{
    const wxString ext1 = wxT("cpp");
    const wxString ext2 = wxT("cxx");
    const wxString ext3 = wxT("c");
    const wxString ext4 = wxT("h");
    const wxString ext5 = wxT("hpp");
    const wxString lang = wxT("C/C++");
}

RheiaCppHandler::RheiaCppHandler():
    RheiaEditorHandler()
{

}

RheiaCppHandler::RheiaCppHandler(const RheiaCppHandler& rhs):
    RheiaEditorHandler(rhs)
{

}

RheiaCppHandler::~RheiaCppHandler()
{

}

RheiaEditorHandler* RheiaCppHandler::Clone()
{
    return new RheiaCppHandler(*this);
}

bool RheiaCppHandler::CanHandle( const wxString& file )
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

bool RheiaCppHandler::CanHandle( RheiaEditorLayout* context )
{
    if( context->IsKindOf( CLASSINFO(RheiaCppLayout) ) )
        return true;

    return false;
}

wxArrayString RheiaCppHandler::GetExtensions()
{
    wxArrayString ret;
    ret.Add( wxT("C/C++ files (*.h;*.cpp;*.hpp;*.cxx;*.c)|*.h;*.cpp;*.hpp;*.cxx;*.c") );

    return ret;
}

RheiaEditorLayout* RheiaCppHandler::CreateContext( )
{
    return new RheiaCppLayout();
}

wxArrayString RheiaCppHandler::GetLanguages()
{
    wxArrayString ret;
    ret.Add(lang);

    return ret;
}