/*
 * This file was originally taken from Code::Blocks IDE, some methods have been added,
 * It is licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */
 
/**
*   @file RheiaException.h
*   @brief RheiaExecption is the basic class for Rheia's error handling unit.
*
*   Two macros are defined to help error handling in Rheia:
*   RheiaThrow() and RheiaAssert().
*
*   @note RheiaAssert() does nothing in release mode. For debug mode, compile with -DRHEIA_DEBUG
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@version 0.0.1
*	@date 03-Jan-2009
*/
#ifndef RheiaException_h_
#define RheiaException_h_

#include <wx/string.h>
#include <wx/log.h> // for wxSafeShowMessage()
#include <RheiaUtilsSettings.h>

/**
*	@class RheiaException
*	@brief The base Rheia exception object.
*
*	In the Rheia FrameWork you can manage errors handled by the different elements and objects by using the RheiaExcpetion object.
*	All errors and exeptions must use as base exception class RheiaException.
*
*	@author Nicolas Macherey (nm@graymat.fr)
*	@version 0.0.1
*	@date 03-Jan-2009
*/
class UTILS_DLLEXPORT RheiaException
{
public:
    RheiaException(const wxString& msg, const wxString& file, int line);
    virtual ~RheiaException();

    /**
    *   @brief Display exception error message.
    *   @param safe If true, wxSafeShowMessage will be used to display the error,
    *             else a normal message box will be used.
    */
    void ShowErrorMessage(bool safe = true);

    // public members
    wxString Message; ///< The exception's error message.
    wxString File; ///< The file where the exception was raised.
    int Line; ///< The line in the file where the exception was raised.
};

#if wxUSE_UNICODE
#define RheiaThrow(message) throw RheiaException(message, RheiaC2U(__FILE__), __LINE__)
#else
#define RheiaThrow(message) throw RheiaException(message, __FILE__, __LINE__)
#endif

#ifndef RHEIA_DEBUG
#define RheiaAssert(expr)
#else
// In unix we use kill to terminate the application, that makes gdb
// keep it alive which makes debugging easier.
// (thanks go to an unknown author)
#ifdef __WXMSW__
#define DIE() exit(1)
#else
#include <csignal>
#define DIE() kill(0, SIGTERM)
#endif

#if wxUSE_UNICODE
#define RheiaAssertMessage(expr) \
            wxString err; \
            err.Printf(_T("Assertion failed in %s at %s:%d.\n\n%s"), RheiaC2U(__PRETTY_FUNCTION__).c_str(), RheiaC2U(__FILE__).c_str(), __LINE__, RheiaC2U(#expr).c_str());
#else
#define RheiaAssertMessage(expr) \
            wxString err; \
            err.Printf(_T("Assertion failed in %s at %s:%d.\n\n%s"), __PRETTY_FUNCTION__, __FILE__, __LINE__, #expr);
#endif

// non-fatal assertion
#define RheiaAssertNonFatal(expr) \
        if (!(expr)) \
        { \
            RheiaAssertMessage(expr); \
            wxSafeShowMessage(_T("Assertion error"), err); \
        }

// fatal assertion
#define RheiaAssert(expr) \
        if (!(expr)) \
        { \
            RheiaAssertMessage(expr); \
            wxSafeShowMessage(_T("Fatal assertion error"), err); \
            DIE(); \
        }
#endif

#endif
