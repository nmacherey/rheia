/**
*   @file RheiaEditorFile.h
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#ifndef RheiaEditorFile_H
#define RheiaEditorFile_H

#include <RheiaManager.h>
#include <RheiaPageContainer.h>
#include <RheiaBookPage.h>

#include "RheiaEditorSettings.h"

#include <wx/event.h>
#include <wx/treectrl.h>
#include <wx/string.h>
#include <wx/stc/stc.h>
#include <wx/filefn.h>
#include <wx/filesys.h>
#include <map>

/* imports */
class RheiaEditorBase;
class RheiaEditorLayout;

/**
*   @class RheiaEditorFile
*   @brief This class is a basic container for files displayed in the editor
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 14-February-2009
*   @version 0.1.0
*/
class EDITOR_DLLEXPORT RheiaEditorFile : public wxObject, public RheiaPageContainer
{
    DECLARE_DYNAMIC_CLASS(RheiaEditorFile)
public :

    /**************************************************************************************
    *   CONSTRUCTORS AND DESTRUCTORS
    **************************************************************************************/
    /**
    *   Base ctor,
    *   @param parent the parent window in which the editor shall be created
    *   @param container the RheiaEditorFile which handles the data displayed in the container
    */
    RheiaEditorFile():m_parent(NULL),m_page(NULL){};

    RheiaEditorFile( RheiaManagedFrame* parent , RheiaEditorLayout* context , const wxString& filename = wxEmptyString ):
        m_parent(parent),
        m_page(NULL),
        m_context(context),
        m_filename(filename)
        {

        }

    void Create( RheiaManagedFrame* parent )
    {
        m_parent = parent;
    }

    /**
	*   Any project will have a window in the center pane, which will be called
	*   the project's main envrionment.
	*
	*   For this purpose, any projects must provide the application with a MainWindow
	*   which will be displayed and managed by RheiaCenterPaneManager.
	*
	*   We consider that a project cannot be provided without any MainWindow.
	*
	*   @param parent the parent window in which the project's main window shall be created
	*/
	virtual RheiaBookPage* BuildMainWindow( wxWindow* parent );

	/**
	*   Get the project bitmap to the given size,
	*   size could be 16x16, 32x32, 48x48, 80x80 or 128x128
	*/
	virtual const wxBitmap& GetBitmap( const int& /*size*/ ) {return m_bitmap;};

	/**
    *   Callback used when the page is requested to be closed in the center pane
    *   You must overload this method in order to save information/content
    *   of the page when the user is closing it.
    */
    virtual bool OnPageClosed();

    const wxString GetTitle() {return m_title;};

    void SetTitle( const wxString& title ){m_title = title;};

    virtual bool Load();

    virtual bool Save();

    const wxString& GetFileName() {return m_filename;}

    void SetFileName( const wxString& filename ){m_filename = filename;}
	
	RheiaEditorBase* GetPage() {return m_page;};

protected :
    wxBitmap m_bitmap;
    RheiaManagedFrame* m_parent;
    RheiaEditorBase* m_page;
    RheiaEditorLayout* m_context;
    wxString m_title;
    wxString m_filename;

};

#endif


