/**
*   @file RheiaEditorManager.cpp
*
*   @author Nicolas Macherey (nm@graymat.fr)
*   @date 12-March-2010
*   @version 0.0.1
*/
#include "RheiaEditorManager.h"
#include "RheiaEditorFile.h"
#include "RheiaEditorBase.h"
#include "RheiaEditorLayout.h"
#include "RheiaApplyRegExDialog.h"
#include "RheiaFindFilesDialog.h"

#include <RheiaConfigurationManager.h>
#include <RheiaCenterPaneManager.h>
#include <RheiaStandardPaths.h>
#include <RheiaToolBarManager.h>

#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/regex.h>
#include <wx/toolbar.h>

namespace
{
    RheiaMgr<RheiaManagedFrame,RheiaEditorManager>::MgrNsMap locmap;
}

/*! Global instance for the RheiaEditorManager */
template<> RheiaMgr<RheiaManagedFrame,RheiaEditorManager>::MgrNsMap RheiaMgr<RheiaManagedFrame,RheiaEditorManager>::m_ns = locmap;

/** global instance for RheiaEditorFactory */
template<> RheiaEditorFactory* Singleton<RheiaEditorFactory>::instance = 0;
/** global instance for RheiaEditorFactory */
template<> bool  Singleton<RheiaEditorFactory>::isShutdown = false;

RheiaEditorManager::RheiaEditorManager( RheiaManagedFrame* parent ):
    wxEvtHandler(),
    m_parent(parent),
    m_currentFile(NULL),
    m_currentEditor(NULL)
{
    m_parent->PushEventHandler(this);

    idCloseCurrent = wxNewId();
    idCloseAll = wxNewId();
    idCloseAllOthers = wxNewId();
    idSaveCurrent = wxNewId();
    idSaveAs = wxNewId();
    idSaveAll = wxNewId();
    idOpen = wxNewId();
    idNew = wxNewId();

    idSplitHoriz = wxNewId();
    idSplitVertical = wxNewId();
    idUnsplit = wxNewId();
    idUndo = wxNewId();
    idRedo = wxNewId();
    idCut = wxNewId();
    idCopy = wxNewId();
    idPaste = wxNewId();
    idDelete = wxNewId();
    idClearHistory = wxNewId();
    idSelectAll = wxNewId();
    idSelectLine = wxNewId();
    idFoldAll = wxNewId();
    idUnfoldAll = wxNewId();
    idToggleAllFolds = wxNewId();
    idFoldCurrentBlock = wxNewId();
    idUnfoldCurrentBlock = wxNewId();
    idToggleCurrentBlockFold = wxNewId();
    idToggleBookMark = wxNewId();
    idNextBookmark = wxNewId();
    idPreviousBookMark = wxNewId();

    idMenuSearch = wxNewId();
    idFind = wxNewId();
    idFindNext = wxNewId();
	idFindPrevious = wxNewId();
    idFindInFiles = wxNewId();
    idReplace = wxNewId();
    idReplaceNext = wxNewId();
    idReplaceInFiles = wxNewId();
    idApplyRegEx = wxNewId();

    idAutoFormatSel = wxNewId();
    idAutoFormatAll = wxNewId();
    idCommentSel = wxNewId();
    idUncommentSel = wxNewId();

    idConfigure = wxNewId();

    RegisterEvents();
}

RheiaEditorManager::~RheiaEditorManager()
{
    m_parent->RemoveEventHandler(this);
}

void RheiaEditorManager::BuildMenu( wxMenuBar* menuBar )
{
    int idx = menuBar->FindMenu(wxT("File"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnFile = menuBar->GetMenu( idx );
        mnFile->Insert( 0, idOpen , wxT("&Open File\tCtrl-O") , wxT("Open a new file from the manager") );
        mnFile->Insert( 1, idCloseCurrent , wxT("&Close the current file\tCtrl-W") , wxT("Close the current file") );
        mnFile->Insert( 2, idCloseAll , wxT("Close all opened files\tCtrl-Alt-W") , wxT("Close the current file") );
        mnFile->Insert( 3, idCloseAllOthers , wxT("Close all opened files except the active one\tCtrl-Shift-W") , wxT("Close the current file") );

        mnFile->InsertSeparator(4);

        mnFile->Insert( 5, idSaveCurrent , wxT("Save\tCtrl-S") , wxT("Save the current file") );
        mnFile->Insert( 6, idSaveAs , wxT("Save as\tCtrl-Shift-S") , wxT("Save the current file in a new file") );
        mnFile->Insert( 7, idSaveAll , wxT("Save all\tAlt-Shift-S") , wxT("Save all modified files") );
    }

    idx = menuBar->FindMenu(wxT("Edit"));
    if( idx != wxNOT_FOUND )
    {
        wxMenu* mnEdit = menuBar->GetMenu( idx );
        mnEdit->Append( idUndo , wxT("&Undo\tCtrl-Z") , wxT("Undo last action") );
        mnEdit->Append( idRedo , wxT("&Redo\tCtrl-Y") , wxT("Redo last action") );
        mnEdit->Append( idClearHistory , wxT("&Clear history") , wxT("Clear Undo/Redo History") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idCopy , wxT("Copy\tCtrl-C") , wxT("Copy the current selection") );
        mnEdit->Append( idPaste , wxT("Paste\tCtrl-V") , wxT("Paste clipboard content") );
        mnEdit->Append( idCut , wxT("Cut\tCtrl-X") , wxT("Cut selection") );
        mnEdit->Append( idDelete , wxT("Delete\tDELETE") , wxT("Delete selection") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idSelectAll , wxT("Select All\tCtrl-A") , wxT("Select All") );
        mnEdit->Append( idSelectLine , wxT("Select Line\tAlt-L") , wxT("Select the current line") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idFoldAll , wxT("Fold all\tAlt-F") , wxT("Fold all code blocks") );
        mnEdit->Append( idUnfoldAll , wxT("Unfold all\tAlt-Shift-F") , wxT("Unfold all code blocks") );
        mnEdit->Append( idToggleAllFolds , wxT("Toggle all folds\tAlt-T") , wxT("Toggle folds for all code blocks") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idFoldCurrentBlock , wxT("Fold Current Block\tCtrl-F") , wxT("Fold current code block") );
        mnEdit->Append( idUnfoldCurrentBlock , wxT("Unfold Current Block\tCtrl-Shift-F") , wxT("Unfold current code block") );
        mnEdit->Append( idToggleCurrentBlockFold , wxT("Toggle Current Block\tCtrl-Shift-T") , wxT("Toggle fols for current code block") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idToggleBookMark , wxT("Toggle bookmark\tCtrl-B") , wxT("Toggle bookmark") );
        mnEdit->Append( idNextBookmark , wxT("Next bookmark\tCtrl-Shift-B") , wxT("Next bookmark") );
        mnEdit->Append( idPreviousBookMark , wxT("Previous bookmark\tCtrl-Alt-B") , wxT("Previous bookmark") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idAutoFormatSel , wxT("Autoformat selection\tCtrl-Alt-I") , wxT("Autoformat selection") );
        mnEdit->Append( idAutoFormatAll , wxT("Autoformat all\tCtrl-I") , wxT("Autoformat all") );
        mnEdit->AppendSeparator();
        mnEdit->Append( idCommentSel , wxT("Comment selection\tCtrl-W") , wxT("Autoformat selection") );
        mnEdit->Append( idUncommentSel , wxT("Uncomment selection\tCtrl-Alt-W") , wxT("Autoformat all") );

        wxMenu* mnSearch = new wxMenu();
        mnSearch->Append( idFind , wxT("Find\tCtrl-F1") , wxT("Find Text") );
        mnSearch->Append( idFindNext , wxT("Find Next\tF3") , wxT("Find Next") );
        mnSearch->Append( idFindInFiles , wxT("Find In Files\tCtrl-F3") , wxT("Find Next") );
        mnSearch->Append( idReplace , wxT("Replace\tCtrl-Shift-L") , wxT("Find Next") );
        mnSearch->Append( idReplace , wxT("Replace Nexy\tCtrl-Shift-L") , wxT("Find Next") );
        mnSearch->Append( idReplaceInFiles , wxT("Replace In Files\tCtrl-Shift-F3") , wxT("Find Next") );
        mnEdit->AppendSeparator();
        mnSearch->Append( idApplyRegEx , wxT("Apply regular expression\tAlt-X") , wxT("Regular expression") );
        menuBar->Insert( idx +1 , mnSearch , wxT("&Search") );
    }
}

void RheiaEditorManager::BuildToolBar(wxWindow* parent)
{
	wxString path = RheiaFileFinder::FindFile( wxT("resource.zip") );
	
	m_tbPythonTools = new wxToolBar( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_tbPythonTools->AddTool( idCopy, wxT("Copy"), RheiaLoadBitmap( path + wxT("#zip:copy_24_hot.png")), wxNullBitmap, wxITEM_NORMAL, wxT("Copy Selection"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idPaste, wxT("Paste"), RheiaLoadBitmap( path + wxT("#zip:paste_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Paste selection"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idCut, wxT("Cut"), RheiaLoadBitmap( path + wxT("#zip:cut_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Cut selection"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idDelete, wxT("Delete"), RheiaLoadBitmap( path + wxT("#zip:copy_close_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Delete Selection"), wxEmptyString ); 
	m_tbPythonTools->AddSeparator(); 
	m_tbPythonTools->AddTool( idUndo, wxT("Undo"), RheiaLoadBitmap( path + wxT("#zip:back_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Undo"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idRedo, wxT("Redo"), RheiaLoadBitmap( path + wxT("#zip:next_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Redo"), wxEmptyString ); 
	m_tbPythonTools->AddSeparator(); 
	m_tbPythonTools->AddTool( idSelectAll, wxT("Select All"), RheiaLoadBitmap( path + wxT("#zip:support_ok_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Select All"), wxEmptyString ); 
	m_tbPythonTools->AddSeparator(); 
	m_tbPythonTools->AddTool( idFoldCurrentBlock, wxT("Fold "), RheiaLoadBitmap( path + wxT("#zip:folder_up_24_hot.png")), wxNullBitmap, wxITEM_NORMAL, wxT("Fold current block"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idUnfoldCurrentBlock, wxT("Unfold"), RheiaLoadBitmap( path + wxT("#zip:folder_down_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Unfold current block"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idFoldAll, wxT("Fold All"), RheiaLoadBitmap( path + wxT("#zip:folder_remove_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Fold all blocks"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idUnfoldAll, wxT("Unfold All"), RheiaLoadBitmap( path + wxT("#zip:folder_add_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Unfold all blocks"), wxEmptyString ); 
	m_tbPythonTools->AddSeparator(); 
	m_txtGoto = new wxStaticText( m_tbPythonTools, wxID_ANY, wxT("Go to :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtGoto->Wrap( -1 );
	m_tbPythonTools->AddControl( m_txtGoto );
	m_txtGotoLine = new wxTextCtrl( m_tbPythonTools, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_RICH );
	m_tbPythonTools->AddControl( m_txtGotoLine );
	m_tbPythonTools->AddSeparator(); 
	m_stFind = new wxStaticText( m_tbPythonTools, wxID_ANY, wxT("Find :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stFind->Wrap( -1 );
	m_tbPythonTools->AddControl( m_stFind );
	m_txtFind = new wxTextCtrl( m_tbPythonTools, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|wxTE_RICH );
	m_tbPythonTools->AddControl( m_txtFind );
	m_tbPythonTools->AddTool( idFindNext, wxT("Find Next"), RheiaLoadBitmap( path + wxT("#zip:support_down_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Find Next Item"), wxEmptyString ); 
	m_tbPythonTools->AddTool( idFindPrevious, wxT("Find Previous"), RheiaLoadBitmap( path + wxT("#zip:support_up_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Find Previous item"), wxEmptyString ); 
	m_tbPythonTools->Realize();
	
	RheiaToolBarManager::Get(m_parent)->AddToolBar(wxT("Editor tools"),m_tbPythonTools);
	
	
	
	m_tbEdition = new wxToolBar( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	
	m_tbEdition->AddTool( idOpen , wxT("Load"), RheiaLoadBitmap( path + wxT("#zip:doc_favorite_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Load an existing file"), wxEmptyString ); 
	m_tbEdition->AddTool( idNew, wxT("New"), RheiaLoadBitmap( path + wxT("#zip:copy_24_hot.png")), wxNullBitmap, wxITEM_NORMAL, wxT("Create a new file"), wxEmptyString ); 
	m_tbEdition->AddSeparator(); 
	m_tbEdition->AddTool( idSaveCurrent, wxT("Save"), RheiaLoadBitmap( path + wxT("#zip:diskette_24_hot.png")), wxNullBitmap, wxITEM_NORMAL, wxT("Save the current document"), wxEmptyString ); 
	m_tbEdition->AddTool( idSaveAs, wxT("Save as.."), RheiaLoadBitmap( path + wxT("#zip:copy_favorite_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Save the current document in a new file"), wxEmptyString ); 
	m_tbEdition->AddSeparator(); 
	m_tbEdition->AddTool( idToggleBookMark, wxT("Bookmark"), RheiaLoadBitmap( path + wxT("#zip:book_add_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Bookmark current line"), wxEmptyString ); 
	m_tbEdition->AddTool( idToggleBookMark, wxT("Toggle bookmark"), RheiaLoadBitmap( path + wxT("#zip:book_close_24_hot.png")), wxNullBitmap, wxITEM_NORMAL, wxT("Toggle current bookmark"), wxEmptyString ); 
	m_tbEdition->AddTool( idNextBookmark, wxT("Next bookmark"), RheiaLoadBitmap( path + wxT("#zip:book_down_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Next bookmark"), wxEmptyString ); 
	m_tbEdition->AddTool( idPreviousBookMark, wxT("Previous bookmark"), RheiaLoadBitmap( path + wxT("#zip:book_up_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Previous bookmark"), wxEmptyString ); 
	m_tbEdition->AddSeparator(); 
	m_tbEdition->AddTool( idCommentSel, wxT("Comment selection"), RheiaLoadBitmap( path + wxT("#zip:contact_add_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Comment selection"), wxEmptyString ); 
	m_tbEdition->AddTool( idUncommentSel, wxT("Toggle comment"), RheiaLoadBitmap( path + wxT("#zip:contact_remove_24_hot.png") ), wxNullBitmap, wxITEM_NORMAL, wxT("Toggle comment on selection"), wxEmptyString ); 
	m_tbEdition->Realize();
	
	RheiaToolBarManager::Get(m_parent)->AddToolBar(wxT("Editor toolbar"),m_tbEdition);
}

void RheiaEditorManager::ReleaseMenu( wxMenuBar* menuBar )
{

}

void RheiaEditorFactory::PushHandler( RheiaEditorHandler* handler )
{
    if( m_handlers.Index(handler) == wxNOT_FOUND )
        m_handlers.Add( handler );
}

void RheiaEditorFactory::RemoveHandler( RheiaEditorHandler* handler )
{
	if( m_handlers.Index(handler) == wxNOT_FOUND )
        m_handlers.Remove( handler );

	delete handler;
}

void RheiaEditorFactory::RemoveAll()
{
    for( unsigned int i = 0; i < m_handlers.GetCount() ; ++i )
        delete m_handlers[i];
}

RheiaEditorFactory::~RheiaEditorFactory()
{
	RemoveAll();
}

void RheiaEditorManager::RegisterEvents()
{
    Connect(idOpen,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnOpenFileUI));

    Connect(idCloseCurrent,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnSaveFileUI));
    Connect(idCloseAll,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnSaveFileUI));
    Connect(idCloseAllOthers,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnSaveFileUI));
    Connect(idSaveCurrent,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnSaveFileUI));
    Connect(idSaveAs,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnSaveFileUI));
    Connect(idSaveAll,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnSaveFileUI));

    Connect(idSplitHoriz,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idSplitVertical,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idUnsplit,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idUndo,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idRedo,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idCut,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idCopy,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idPaste,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idDelete,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idClearHistory,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idSelectAll,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idSelectLine,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idFoldAll,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idUnfoldAll,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idToggleAllFolds,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idFoldCurrentBlock,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idUnfoldCurrentBlock,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idToggleCurrentBlockFold,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idToggleBookMark,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idNextBookmark,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idPreviousBookMark,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idAutoFormatSel,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idAutoFormatAll,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idCommentSel,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));
    Connect(idUncommentSel,wxEVT_UPDATE_UI,wxUpdateUIEventHandler(RheiaEditorManager::OnEditUI));

    Connect(idOpen,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileOpen));
    Connect(idSaveCurrent,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileSave));
    Connect(idSaveAs,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileSaveAs));
    Connect(idSaveAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileSaveAll));
    Connect(idCloseCurrent,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileClose));
    Connect(idCloseAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileCloseAll));
    Connect(idCloseAllOthers,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnFileCloseAllExceptCurrent));
    Connect(idApplyRegEx,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnApplyRegEx));

    Connect(idSplitHoriz,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idSplitVertical,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idUnsplit,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idUndo,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idRedo,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idCut,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idCopy,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idPaste,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idDelete,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idClearHistory,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idSelectAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idSelectLine,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idFoldAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idUnfoldAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idToggleAllFolds,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idFoldCurrentBlock,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idUnfoldCurrentBlock,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idToggleCurrentBlockFold,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idToggleBookMark,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idNextBookmark,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idPreviousBookMark,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idAutoFormatSel,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idAutoFormatAll,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idCommentSel,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idUncommentSel,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));

    Connect(idFindInFiles,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idFind,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idFindNext,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idReplace,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idReplaceInFiles,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
    Connect(idReplaceNext,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(RheiaEditorManager::OnMenuEdit));
}

void RheiaEditorManager::OnOpenFileUI( wxUpdateUIEvent& event )
{
    wxMenuBar* menuBar = m_parent->GetMenuBar();
    menuBar->Enable(idOpen, (RheiaEditorFactory::Get()->m_handlers.GetCount() > 0) );
}

void RheiaEditorManager::OnSaveFileUI( wxUpdateUIEvent& event )
{
    wxMenuBar* menuBar = m_parent->GetMenuBar();
    menuBar->Enable(idCloseCurrent, (m_files.size() > 0) );
    menuBar->Enable(idCloseAll, (m_files.size() > 0) );
    menuBar->Enable(idCloseAllOthers, (m_files.size() > 0) );
    menuBar->Enable(idSaveCurrent, (m_files.size() > 0) );
    menuBar->Enable(idSaveAs, (m_files.size() > 0) );
    menuBar->Enable(idSaveAll, (m_files.size() > 0) );
}

void RheiaEditorManager::OnEditUI( wxUpdateUIEvent& event )
{
    wxMenuBar* menuBar = m_parent->GetMenuBar();
    m_currentEditor = GetCurrentEditor();

    bool hasFiles = ( m_files.size() > 0 && (m_currentEditor != NULL) );

    menuBar->Enable(idSplitHoriz, (hasFiles && m_currentEditor->CanSplit()) );
    menuBar->Enable(idSplitVertical, (hasFiles && m_currentEditor->CanSplit()) );
    menuBar->Enable(idUnsplit, (hasFiles && m_currentEditor->CanSplit()) );
    menuBar->Enable(idUndo, (hasFiles && m_currentEditor->CanUndo()) );
    menuBar->Enable(idRedo, (hasFiles && m_currentEditor->CanRedo()) );
    menuBar->Enable(idCut, (hasFiles && m_currentEditor->CanCut()) );
    menuBar->Enable(idCopy, (hasFiles && m_currentEditor->CanCopy()) );
    menuBar->Enable(idPaste, (hasFiles && m_currentEditor->CanPaste()) );
    menuBar->Enable(idDelete, (hasFiles && m_currentEditor->CanDelete()) );
    menuBar->Enable(idClearHistory, (hasFiles && m_currentEditor->CanClearHistory()) );
    menuBar->Enable(idSelectAll, (hasFiles && m_currentEditor->CanSelectAll()) );
    menuBar->Enable(idSelectLine, (hasFiles && m_currentEditor->CanSelectLine()) );
    menuBar->Enable(idFoldAll, (hasFiles && m_currentEditor->CanFold()) );
    menuBar->Enable(idUnfoldAll, (hasFiles && m_currentEditor->CanFold()) );
    menuBar->Enable(idToggleAllFolds, (hasFiles && m_currentEditor->CanFold()) );
    menuBar->Enable(idFoldCurrentBlock, (hasFiles && m_currentEditor->CanFold()) );
    menuBar->Enable(idUnfoldCurrentBlock, (hasFiles && m_currentEditor->CanFold()) );
    menuBar->Enable(idToggleCurrentBlockFold, (hasFiles && m_currentEditor->CanFold()) );
    menuBar->Enable(idToggleBookMark, (hasFiles) );
    menuBar->Enable(idNextBookmark, (hasFiles) );
    menuBar->Enable(idPreviousBookMark, (hasFiles) );
    menuBar->Enable(idAutoFormatSel, (hasFiles && m_currentEditor->CanFormatSelection() ) );
    menuBar->Enable(idAutoFormatAll, (hasFiles && m_currentEditor->CanFormat() ) );
    menuBar->Enable(idCommentSel, (hasFiles && m_currentEditor->CanComment() ) );
    menuBar->Enable(idUncommentSel, (hasFiles && m_currentEditor->CanComment() ) );
}

void RheiaEditorManager::OnFileOpen( wxCommandEvent& event )
{
    wxString f_exts;

    for( unsigned int i = 0 ; i < RheiaEditorFactory::Get()->m_handlers.GetCount() ; ++i )
    {
        wxArrayString exts = RheiaEditorFactory::Get()->m_handlers[i]->GetExtensions();
        for( unsigned int j = 0; j < exts.GetCount() ; ++j )
            f_exts += exts[j] + wxT("|");
    }

    wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_file_path") , RheiaStandardPaths::HomeDirectory() );

    wxFileDialog dialog( m_parent,
                         wxT("Select the workspace files you want to load..."),
                         LastOpenPath,
                         wxEmptyString,
                         f_exts,
                         wxFD_OPEN | wxFD_MULTIPLE );

    if ( dialog.ShowModal() != wxID_OK )
    {
        return;
    }

    wxArrayString filepaths;
    dialog.GetPaths(filepaths);

    wxFileName lastPath( filepaths[0] );
    RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_file_path") , lastPath.GetPath() );

    for ( unsigned int i = 0; i < filepaths.size() ; i++ )
        Open(filepaths[i]);
}

bool RheiaEditorManager::Open(const wxString& filename)
{
    RheiaEditorHandler* handler = NULL;

    for( unsigned int j = 0; j < RheiaEditorFactory::Get()->m_handlers.GetCount() ; ++j )
        if( RheiaEditorFactory::Get()->m_handlers[j]->CanHandle(filename) )
        {
            handler = RheiaEditorFactory::Get()->m_handlers[j];
            break;
        }

    if( handler )
    {
        RheiaEditorLayout* context = handler->CreateContext();

        RheiaEditorFile* file = new RheiaEditorFile(m_parent,context,filename);
        if( file != NULL )
           return AddFile(filename,file);
    }

    return false;
}

void RheiaEditorManager::OnFileSave( wxCommandEvent& event )
{
    m_currentEditor = GetCurrentEditor();
    if( !m_currentEditor )
        return;

    m_currentFile = m_currentEditor->GetContainer();

    if( m_currentEditor->GetModified() )
        SaveFile(m_currentFile);

    m_currentEditor = NULL;
    m_currentFile = NULL;
}

void RheiaEditorManager::OnFileSaveAs( wxCommandEvent& event )
{
    m_currentEditor = GetCurrentEditor();
    if( !m_currentEditor )
        return;

    SaveFile(m_currentFile,true);

    m_currentEditor = NULL;
    m_currentFile = NULL;
}

void RheiaEditorManager::OnFileSaveAll( wxCommandEvent& event )
{
    RheiaEditorMap::iterator it = m_files.begin();
    for( ; it != m_files.end() ; ++it )
    {
        RheiaEditorBase* editor = (RheiaEditorBase*) RheiaCenterPaneManager::Get(m_parent)->FindPageByName(it->second->GetTitle());
        if( editor != NULL && editor->GetModified() )
            SaveFile( it->second );
    }
}

void RheiaEditorManager::OnFileClose( wxCommandEvent& event )
{
    m_currentEditor = GetCurrentEditor();
    if( !m_currentEditor )
        return;

    CloseFile( m_currentFile );

    m_currentEditor = NULL;
    m_currentFile = NULL;
}

void RheiaEditorManager::OnFileCloseAll( wxCommandEvent& event )
{
    RheiaEditorMap::iterator it = m_files.begin();
    for( ; it != m_files.end() ; ++it )
    {
        if( !CloseFile( it->second ) )
            return;
    }
}

void RheiaEditorManager::OnFileCloseAllExceptCurrent( wxCommandEvent& event )
{
    m_currentEditor = GetCurrentEditor();
    if( !m_currentEditor )
        return;

    RheiaEditorMap::iterator it = m_files.begin();
    for( ; it != m_files.end() ; ++it )
    {
        if( it->second == m_currentFile && !CloseFile( it->second ) )
            return;
    }

    m_currentEditor = NULL;
    m_currentFile = NULL;
}

RheiaEditorBase* RheiaEditorManager::GetCurrentEditor()
{
    wxString active = RheiaCenterPaneManager::Get(m_parent)->GetActivePageName();
    RheiaEditorMap::iterator it = m_files.begin();
    for( ; it != m_files.end() ; ++it )
    {
        if( it->second->GetTitle() == active )
            return (RheiaEditorBase*) RheiaCenterPaneManager::Get(m_parent)->GetActivePage();
    }

    return NULL;
}

bool RheiaEditorManager::NotifyClose(RheiaEditorFile* file)
{
    RheiaEditorBase* editor = (RheiaEditorBase*) RheiaCenterPaneManager::Get(m_parent)->FindPageByName(file->GetTitle());
    if( editor != NULL )
    {
        if( editor->GetModified() )
        {
            int ret = wxMessageBox( wxT("The file : ") + file->GetTitle() + wxT(" has not been saved... Would you like to save it ?"),
                                   wxT("Warning") , wxYES_NO | wxCANCEL | wxICON_INFORMATION , m_parent );

            if( ret == wxCANCEL || ret == wxID_CANCEL )
                return false;

            if( ret == wxID_YES || ret == wxYES )
                SaveFile( file );
        }

        RheiaCenterPaneManager::Get(m_parent)->RemovePage(file->GetTitle());
    }

    wxString fileName = file->GetFileName();
    RheiaEditorMap::iterator it = m_files.find(fileName);
    if( it == m_files.end() )
        return true;

    delete it->second;
    m_files.erase(it);
    m_currentFile = NULL;
    m_currentEditor = NULL;
    return true;
}

bool RheiaEditorManager::CloseFile( RheiaEditorFile* file , bool askfor )
{
    RheiaEditorBase* editor = (RheiaEditorBase*) RheiaCenterPaneManager::Get(m_parent)->FindPageByName(file->GetTitle());
    if( editor != NULL )
    {
        if( editor->GetModified() && askfor )
        {
            int ret = wxMessageBox( wxT("The file : ") + file->GetTitle() + wxT(" has not been saved... Would you like to save it ?"),
                                   wxT("Warning") , wxYES_NO | wxCANCEL | wxICON_INFORMATION , m_parent );

            if( ret == wxCANCEL || ret == wxID_CANCEL )
                return false;

            if( ret == wxID_YES || ret == wxYES )
                SaveFile( file );
        }

        RheiaCenterPaneManager::Get(m_parent)->DeletePage(file->GetTitle());
    }

    wxString fileName = file->GetFileName();
    RheiaEditorMap::iterator it = m_files.find(fileName);
    if( it == m_files.end() )
        return true;

    delete it->second;
    m_files.erase(it);
    m_currentFile = NULL;
    m_currentEditor = NULL;
    return true;
}

bool RheiaEditorManager::SaveFile( RheiaEditorFile* file , bool force_file )
{
    if( file->GetFileName().IsEmpty() || force_file )
    {
        wxString f_exts;

        for( unsigned int i = 0 ; i < RheiaEditorFactory::Get()->m_handlers.GetCount() ; ++i )
        {
            if( RheiaEditorFactory::Get()->m_handlers[i]->CanHandle(m_currentEditor->GetContext()) )
            {
                wxArrayString exts = RheiaEditorFactory::Get()->m_handlers[i]->GetExtensions();
                for( unsigned int j = 0; j < exts.GetCount() ; ++j )
                    f_exts += exts[j] + wxT("|");
            }
        }

        if( f_exts.IsEmpty() )
            f_exts = wxT("All file (*)|*");

        wxString LastOpenPath = RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Read( wxT("/last_file_path") , RheiaStandardPaths::HomeDirectory() );

        wxFileDialog dialog( m_parent,
                             wxT("Select the workspace files you want to load..."),
                             LastOpenPath,
                             wxEmptyString,
                             f_exts,
                             wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

        if ( dialog.ShowModal() != wxID_OK )
        {
            return false;
        }

        wxString filepath;
        filepath = dialog.GetPath();
        RheiaManager::Get()->GetConfigurationManager( wxT("load_save") )->Write( wxT("/last_file_path") , wxFileName(filepath).GetPath() );

        file->SetFileName(filepath);
    }

    return file->Save();
}

bool RheiaEditorManager::AddFile( const wxString& filename , RheiaEditorFile* file )
{
    RheiaEditorMap::iterator it = m_files.find(filename);
    if( it != m_files.end() )
        return false;

    m_files[filename] = file;

    wxFileName fn(filename);
    // add file here
    file->SetTitle(filename);
    file->SetFileName(filename);
    RheiaCenterPaneManager::Get(m_parent)->AddPage( file->GetTitle() , file );

    m_currentFile = file;
    m_currentEditor = (RheiaEditorBase*) RheiaCenterPaneManager::Get(m_parent)->FindPageByName(file->GetTitle());
    return file->Load();
}

void RheiaEditorManager::OnMenuEdit( wxCommandEvent& event )
{
    m_currentEditor = GetCurrentEditor();
    if( !m_currentEditor )
        return;

    int id = event.GetId();

    if( id == idSplitHoriz && m_currentEditor->CanSplit() && !m_currentEditor->IsSplitted() )
        m_currentEditor->Split( splitHoriz );
    else if( id == idSplitVertical && m_currentEditor->CanSplit() && !m_currentEditor->IsSplitted() )
        m_currentEditor->Split( splitVertical );
    else if( id == idUnsplit && m_currentEditor->CanSplit() && m_currentEditor->IsSplitted() )
        m_currentEditor->Unsplit( );
    else if( id == idUndo && m_currentEditor->CanUndo() )
        m_currentEditor->DoUndo();
    else if( id == idRedo && m_currentEditor->CanRedo() )
        m_currentEditor->DoRedo();
    else if( id == idCut && m_currentEditor->CanCut() )
        m_currentEditor->DoCut();
    else if( id == idCopy && m_currentEditor->CanCopy() )
        m_currentEditor->DoCopy();
    else if( id == idPaste && m_currentEditor->CanPaste() )
        m_currentEditor->DoPaste();
    else if( id == idDelete && m_currentEditor->CanDelete() )
        m_currentEditor->DoDelete();
    else if( id == idClearHistory && m_currentEditor->CanClearHistory() )
        m_currentEditor->DoClearHistory();
    else if( id == idSelectAll && m_currentEditor->CanSelectAll() )
        m_currentEditor->DoSelectAll();
    else if( id == idSelectLine && m_currentEditor->CanSelectLine() )
        m_currentEditor->DoSelectLine();
    else if( id == idFind )
        {}
    else if( id == idFindNext )
        {}
    else if( id == idReplace )
        {}
    else if( id == idReplaceNext )
        {}
    else if( id == idFindInFiles )
        AskForFindInFiles();
    else if( id == idReplaceInFiles )
        {}
    else if( id == idToggleBookMark )
        m_currentEditor->ToggleBookmark();
    else if( id == idNextBookmark )
        m_currentEditor->GotoNextBookmark();
    else if( id == idPreviousBookMark )
        m_currentEditor->GotoPreviousBookmark();
    else if( id == idAutoFormatAll && m_currentEditor->CanFormat() )
        m_currentEditor->DoFormat();
    else if( id == idAutoFormatSel && m_currentEditor->CanFormatSelection() )
        m_currentEditor->DoFormatSelection();
    else if( id == idFoldAll && m_currentEditor->CanFold() )
        m_currentEditor->DoFoldAll();
    else if( id == idUnfoldAll && m_currentEditor->CanFold() )
        m_currentEditor->DoUnfoldAll();
    else if( id == idToggleAllFolds && m_currentEditor->CanFold() )
        m_currentEditor->DoToggleAllFolds();
    else if( id == idFoldCurrentBlock && m_currentEditor->CanFold() )
        m_currentEditor->DoFoldCurrentBlock();
    else if( id == idUnfoldCurrentBlock && m_currentEditor->CanFold() )
        m_currentEditor->DoUnFoldCurrentBlock();
    else if( id == idToggleCurrentBlockFold && m_currentEditor->CanFold() )
        m_currentEditor->DoToggleCurrentBlockFold();
    else if( id == idCommentSel && m_currentEditor->CanComment() )
        m_currentEditor->DoComment();
    else if( id == idUncommentSel && m_currentEditor->CanComment() )
        m_currentEditor->DoUncomment();

    m_currentEditor = NULL;
    m_currentFile = NULL;
}

void RheiaEditorManager::OnApplyRegEx( wxCommandEvent& event )
{
    RheiaApplyRegExDialog dialog(m_parent);
    if(dialog.ShowModal() != wxID_OK)
        return;

    wxRegEx regex;
    int flags = dialog.GetFlags();
    wxString expr = dialog.GetExpr();
    wxString repStr = dialog.GetReplacementString();

    regex.Compile( expr , flags );

    m_currentEditor = GetCurrentEditor();

    if( m_currentEditor && dialog.CurrentFile() )
        m_currentEditor->DoApplyRegex( regex , repStr , false , false );
    else if( m_currentEditor && dialog.SelectionOnly() )
        m_currentEditor->DoApplyRegex( regex , repStr , true , false );
    else if( dialog.AllFiles() )
    {
        RheiaEditorMap::iterator it = m_files.begin();
        for( ; it != m_files.end() ; ++it )
        {
            RheiaEditorBase* editor = (RheiaEditorBase*) RheiaCenterPaneManager::Get(m_parent)->FindPageByName(it->second->GetTitle());
            if( editor != NULL )
                editor->DoApplyRegex( regex , repStr , false , false );
        }
    }

    m_currentEditor = NULL;
}

void RheiaEditorManager::AskForFindInFiles()
{
    RheiaFindFilesDialog dialog(m_parent);
    if( dialog.ShowModal() != wxID_OK )
        return;
}

int RheiaEditorManager::FindIn( RheiaEditorBase* editor , const wxString& expr , int flag , bool selOnly )
{
	if( expr.IsEmpty() || editor == NULL )
		return -1;
	
	int start, end, pos;
	wxStyledTextCtrl* control = editor->GetControl();
	editor->HighlightOccurrences(expr,flag);
	
	if( selOnly )
	{
		start = control->GetSelectionStart();
		end = control->GetSelectionEnd();
	}
	else
	{
		start = control->GetCurrentPos();
		end = control->GetLength();
	}
	
	m_findData.start = start;
	m_findData.end = end;
	m_findData.expr = expr;
	m_findData.selOnly = selOnly;
	m_findData.flag = flag;
	m_findData.pos = start;
	
	while(1)
	{
		pos = control->FindText(start, end, expr , flag);
		m_findData.pos = pos;
		
		if( pos != -1 && start != end )
		{
			int line = control->LineFromPosition(pos);
			int onScreen = control->LinesOnScreen() >> 1;
            int l1 = line - onScreen;
            int l2 = line + onScreen;
			
            for(int l=l1; l<=l2;l+=2)       // unfold visible lines on screen
                control->EnsureVisible(l);
				
            control->GotoLine(l1);          // center selection on screen
            control->GotoLine(l2);
            control->GotoLine(line);
            control->SetSelectionStart(pos);
			control->SetSelectionEnd(pos+expr.Len());
            m_findData.start = pos;
            break; // done
			
		}//end if( pos != -1 && start != end )
		else
		{
			wxBell();
			if( pos == -1 && !selOnly && start== 0 && end == control->GetLength() )
			{
				wxString msg = expr + wxT(" not found !");
				wxMessageBox(msg,wxT("Result"),wxICON_INFORMATION,m_parent);
				return -1;
			}
			else if( pos == -1 && selOnly )
			{
				wxString msg = expr + wxT(" not found in selection ! Would you like to restart the search from the begining of the document ?");
				int ret = wxMessageBox(msg,wxT("Result"),wxICON_QUESTION|wxYES_NO,m_parent);
				if( ret == wxID_NO )
					return -1;
				else
				{
					m_findData.start = 0;
					m_findData.end = control->GetLength();
				}
			}
			else
			{
				wxString msg = expr + wxT(" not found in range ! Would you like to restart the search on the whole document ?");
				int ret = wxMessageBox(msg,wxT("Result"),wxICON_QUESTION|wxYES_NO,m_parent);
				if( ret == wxID_NO )
					return -1;
				else
				{
					m_findData.start = 0;
					m_findData.end = control->GetLength();
				}
			}
		}
	}// end while(1)
	
	return m_findData.pos;
}