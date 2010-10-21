/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "PyFile.h"
#include "PyEditorBase.h"
#include "PyFileManager.h"

IMPLEMENT_DYNAMIC_CLASS(PyFile,wxObject)

RheiaBookPage* PyFile::BuildMainWindow( wxWindow* parent )
{
    m_page = new PyEditorBase(m_parent,parent,this,m_context);
    return m_page;
}

bool PyFile::Load()
{
    if( m_page == NULL || m_filename.IsEmpty() )
        return false;

    return m_page->Load(m_filename);
}

bool PyFile::Save()
{
    if( m_page == NULL || m_filename.IsEmpty() )
        return false;

    return m_page->Save(m_filename);
}

bool PyFile::OnPageClosed()
{
    if( !PyFileManager::Get(m_parent)->NotifyClose(this) )
        return false;

    m_page == NULL;
    return true;
}
