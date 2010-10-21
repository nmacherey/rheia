/*
 * This file was originally taken from Code::Blocks IDE, some methods have been added,
 * It is licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */
#ifndef RheiaGlobals_h_
#define RheiaGlobals_h_

#include <RheiaUtilsSettings.h>

/** Icons styles for settings dialogs.
  */
enum SettingsIconsStyle
{
    sisLargeIcons    = 0, ///< Large icons (default)
    sisNoIcons       = 1, ///< No icons, just text
};

#include <wx/listctrl.h>

/** This function loads a bitmap from disk.
  * Always use this to load bitmaps because it takes care of various
  * issues with pre-XP windows (actually common controls < 6.00).
  */
extern UTILS_DLLEXPORT wxBitmap RheiaLoadBitmap(const wxString& filename, wxBitmapType bitmapType = wxBITMAP_TYPE_PNG);

/// Known plugin types
enum RheiaPluginType
{
    ptNone = 1,				/*!< unknown type                   */
    ptEnvironment,			/*!< workspace plugins              */
    ptOption,				/*!< options manager plugins        */
    ptOther					/*!< others                         */
};

#include <vector>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>

/*! Function used for creating a directory with wxMkdir */
bool UTILS_DLLEXPORT RheiaMakeDir(const wxString& full_path, int perms = 0775 );
bool UTILS_DLLEXPORT RheiaMakeDirRecursively(const wxString& full_path, int perms = 0775 );

wxString UTILS_DLLEXPORT DetermineExecutablePath();
wxString UTILS_DLLEXPORT DetermineResourcesPath();

#include <wx/string.h>
#include <wx/treectrl.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/intl.h>
#include <wx/msgdlg.h>
#include <wx/bitmap.h>
#include <set>
#include <string>

/// Return @c str as a proper unicode-compatible string
inline wxString RheiaC2U(const char* str)
{
#if wxUSE_UNICODE
    return wxString(str, wxConvUTF8);
#else
    return wxString(str);
#endif
}

/// Return @c str as a proper unicode-compatible string
inline std::string RheiaU2C(const wxString& str)
{
    std::string sstr;

#if wxUSE_UNICODE
    sstr = (const char*) str.mb_str(wxConvUTF8);
#else
    sstr = (const char*) str.mb_str();
#endif

    return sstr;
}

#define rxU2C( str ) reinterpret_cast<const xmlChar*>( RheiaU2C( str ).c_str() )
#define rcU2C( str ) RheiaU2C( str ).c_str()

/** wxMessageBox wrapper.
  *
  * Use this instead of wxMessageBox(), as this uses PlaceWindow() to show it in the correct monitor.
  * @note The return value for wxOK would be wxID_OK and so on for other buttons.
  * So, read wxMessageDialog 's documentation, *not* wxMessageBox 's...
  */
inline int RheiaMessageBox(const wxString& message, const wxString& caption = wxEmptyString, int style = wxOK, wxWindow *parent = NULL, int x = -1, int y = -1)
{
    // Cannot create a wxMessageDialog with a NULL as parent
    if (!parent)
    {
        // wxMessage*Box* returns any of: wxYES, wxNO, wxCANCEL, wxOK.
        int answer = wxMessageBox(message, caption, style, parent, x, y);
        switch (answer)
        {
            // map answer to the one of wxMessage*Dialog* to ensure compatibility
        case (wxOK):
            return wxID_OK;
        case (wxCANCEL):
            return wxID_CANCEL;
        case (wxYES):
            return wxID_YES;
        case (wxNO):
            return wxID_NO;
        default:
            return -1; // NOTE: Cannot happen unless wxWidgets API changes
        }
    }

    wxMessageDialog dlg(parent, message, caption, style, wxPoint(x,y));
    // wxMessage*Dialog* returns any of wxID_OK, wxID_CANCEL, wxID_YES, wxID_NO
    return dlg.ShowModal();
};

/// Result values of cbDirAccessCheck()
enum DirAccessCheck
{
    dacInvalidDir, ///< Invalid directory (does not exist).
    dacReadWrite, ///< Current user has read-write access to the directory.
    dacReadOnly ///< Current user has read-only access to the directory.
};

/** Check what access the current user has in a directory.
*
* @param dir The directory in question.
*            It may or may not contain an ending path separator.
* @return The type of access the current user has in the directory.
*/
extern UTILS_DLLEXPORT DirAccessCheck RheiaDirAccessCheck(const wxString& dir);

/**
*   Compare The plugin version with its last known version
*	@param new_version extracted string from the manifest file
*	@param old_version las version string known
*
*	@return returns -1 if new is less then old, 0 if equal and 1 if new is greater than old
*/
extern UTILS_DLLEXPORT int CompareVersions(long major, long minor, long dmajor, long dminor);


/****************************************************************************************
* DEFAULT COLOURS FOR AUI MANAGERS
****************************************************************************************/
const int DEFAULT_PANE_BORDER = 2;
const int DEFAULT_SASH_SIZE = 2;
const int DEFAULT_CAPTION_SIZE = 10;

const wxColour DEFAULT_ACTIVE_CAPTION = *wxBLUE;
const wxColour DEFAULT_ACTIVE_CAPTION_GRADIENT = *wxBLUE;
const wxColour DEFAULT_ACTIVE_TEXT_GRADIENT = *wxWHITE;

const wxColour DEFAULT_INACTIVE_CAPTION = *wxLIGHT_GREY;
const wxColour DEFAULT_INACTIVE_CAPTION_GRADIENT = *wxLIGHT_GREY;
const wxColour DEFAULT_INACTIVE_TEXT_GRADIENT = *wxBLACK;


/****************************************************************************************
* Rheia OBJECT with Bitmap
****************************************************************************************/
class UTILS_DLLEXPORT RheiaObjectWithBitmap
{
public :
    /**
	*   Get the project bitmap to the given size,
	*   size could be 16x16, 32x32, 48x48, 80x80 or 128x128
	*/
	virtual const wxBitmap& GetBitmap( const int& size ) = 0;
};

#endif
