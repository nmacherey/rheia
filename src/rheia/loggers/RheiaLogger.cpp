/**
*   @file RheiaLogger.h
*
*   Revision : Nicolas Macherey (nm@graymat.fr)
*       Date : 26-November-2009
*       Changes : Commentaries and rewrite
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 15-April-2009
*   @version 0.0.2
*/
#include "RheiaLogger.h"
#include "RheiaStandardPaths.h"

IMPLEMENT_ABSTRACT_CLASS( RheiaLogger , wxEvtHandler );
IMPLEMENT_DYNAMIC_CLASS( RheiaNullLogger , RheiaLogger );


RheiaLogger::RheiaLogger()
{

}

RheiaLogger::~RheiaLogger()
{

}

const wxBitmap& RheiaLogger::GetBitmap( const int& size )
{
    wxString fPath = RheiaStandardPaths::DataDirectoryGlobal() + wxString::Format( wxT("/resource.zip#zip:workspace_%d.png") , size );
    m_bmp = RheiaLoadBitmap( fPath );

    return m_bmp;
}
