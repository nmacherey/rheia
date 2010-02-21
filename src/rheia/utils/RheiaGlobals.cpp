#include <RheiaGlobals.h>

#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/listctrl.h>


#if defined(__APPLE__) && defined(__MACH__)
#include <sys/param.h>
#include <mach-o/dyld.h>
#endif

#ifdef __WXMAC__
#include "wx/osx/core/cfstring.h"
#include "wx/intl.h"

#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFURL.h>
#endif

bool RheiaMakeDirRecursively(const wxString& full_path, int perms)
{
    if (wxDirExists(full_path)) // early out
        return true;

    wxArrayString dirs;
    wxString currdir;

    {
        wxFileName tmp(full_path);
        currdir = tmp.GetVolume() + tmp.GetVolumeSeparator() + wxFILE_SEP_PATH;
        dirs = tmp.GetDirs();
    }
    for (size_t i = 0; i < dirs.GetCount(); ++i)
    {
        currdir << dirs[i];
        if (!wxDirExists(currdir) && !wxMkdir(currdir, perms))
            return false;
        currdir << wxFILE_SEP_PATH;
    }
    return true;
}

bool RheiaMakeDir(const wxString& full_path, int perms )
{
    if (wxDirExists(full_path))
        return true;

    if (!wxMkdir(full_path, perms))
        return false;

    return true;
}

wxString DetermineExecutablePath()
{
#if (__WXMSW__)
    wxChar name[MAX_PATH];
    GetModuleFileName(0L, name, MAX_PATH);
    wxFileName fname(name);
    return fname.GetPath(wxPATH_GET_VOLUME);
#else
#if (__linux__)
    char c[PATH_MAX+1];
    char *p = realpath("/proc/self/exe", &c[0]);
    if (p == 0)
        return _T(".");
    wxFileName fname(RheiaC2U(p));
    return fname.GetPath(wxPATH_GET_VOLUME);
#elif defined(sun) || defined(__sun)
    wxFileName fname(RheiaC2U(getexecname()));
    return fname.GetPath(wxPATH_GET_VOLUME);
#elif defined(__APPLE__) && defined(__MACH__)
    char path[MAXPATHLEN+1];
    uint32_t path_len = MAXPATHLEN;
    // SPI first appeared in Mac OS X 10.2
    _NSGetExecutablePath(path, &path_len);
    wxFileName fname(wxString(path, wxConvUTF8));
    return fname.GetPath(wxPATH_GET_VOLUME);
#else
    return _T(".");
#endif
#endif
};

wxString DetermineResourcesPath()
{
#if defined(__WXMAC__)
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFURLRef absoluteURL = CFURLCopyAbsoluteURL(resourcesURL); // relative -> absolute
    CFRelease(resourcesURL);
    CFStringRef cfStrPath = CFURLCopyFileSystemPath(absoluteURL,kCFURLPOSIXPathStyle);
    CFRelease(absoluteURL);
#if wxCHECK_VERSION(2, 9, 0)
    wxString str = wxCFStringRef(cfStrPath).AsString(wxLocale::GetSystemEncoding());
#else
    wxString str = wxMacCFStringHolder(cfStrPath).AsString(wxLocale::GetSystemEncoding());
#endif

    if (!str.Contains(wxString(_T("/Resources"))))
        return ::DetermineExecutablePath() + _T("/.."); // not a bundle, use relative path
    return str;
#else
    return _T(".");
#endif
};

#include <RheiaException.h>

#ifndef __WXMSW__
#include <unistd.h> // readlink
#include <sys/stat.h> // lstat
#endif

#include <wx/filename.h>
#include <wx/file.h>
#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/filesys.h>
#include <wx/filefn.h>
#include <wx/tokenzr.h>
#include <wx/dirdlg.h>
#include <wx/msgdlg.h>
#include <wx/fontmap.h>
#include <algorithm>
#include <string>

wxBitmap RheiaLoadBitmap(const wxString& filename, wxBitmapType bitmapType)
{
    wxImage im;
    wxFileSystem* fs = new wxFileSystem;
    wxFSFile* f = fs->OpenFile(filename);
    if (f)
    {
        wxInputStream* is = f->GetStream();
        im.LoadFile(*is, bitmapType);
        delete f;
    }
    delete fs;

    return wxBitmap(im);
}

DirAccessCheck RheiaDirAccessCheck(const wxString& dir)
{
    wxString actualDir = dir;
    // append ending path separator if needed
    if (actualDir.Last() != _T('/') && actualDir.Last() != _T('\\'))
        actualDir << wxFILE_SEP_PATH;

    if (!wxDirExists(actualDir))
        return dacInvalidDir;

    wxString testFile = wxFileName::CreateTempFileName(actualDir);
    if (!testFile.IsEmpty())
    {
        // ok, write-access confirmed
        // now remove the temporary file and return success
        wxRemoveFile(testFile);
        return dacReadWrite;
    }

    // if we reached here, the directory is not writable
    return dacReadOnly;
}


int CompareVersions(long major, long minor, long dmajor, long dminor)
{
#define SIGN(a) (a>0?1:(a<0?-1:0))
    int result = 0;
    result += SIGN(major - dmajor) << 2;
    result += SIGN(minor - dminor) << 1;
#undef SIGN

    if (result < 0) return -1;
    else if (result > 0) return 1;
    return 0;
}

