/**
*   @file RheiaEditorFile.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaEditorFile.h"
#include "RheiaEditorBase.h"
#include "RheiaEditorManager.h"

IMPLEMENT_DYNAMIC_CLASS(RheiaEditorFile,wxObject)

RheiaBookPage* RheiaEditorFile::BuildMainWindow( wxWindow* parent )
{
    m_page = new RheiaEditorBase(m_parent,parent,this,m_context);
    return m_page;
}

bool RheiaEditorFile::Load()
{
    if( m_page == NULL || m_filename.IsEmpty() )
        return false;

    return m_page->Load(m_filename);
}

bool RheiaEditorFile::Save()
{
    if( m_page == NULL || m_filename.IsEmpty() )
        return false;

    return m_page->Save(m_filename);
}

bool RheiaEditorFile::OnPageClosed()
{
    if( !RheiaEditorManager::Get(m_parent)->NotifyClose(this) )
        return false;

    m_page = NULL;
    return true;
}
