/*
 * This file is part of the Rheia Python IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "PyContext.h"

IMPLEMENT_DYNAMIC_CLASS(PyContext,PyEditorContext)

namespace LexPython
{
    const wxString keywords0 = wxT("and assert break class continue def del elif else except exec finally for from global if import "
                "in is lambda None  not or pass print raise return try while yield __import__ abs basestring bool "
                "callable chr classmethod cmp compile complex delattr dict dir divmod enumerate "
                "eval execfile file filter float frozenset getattr globals "
                "hasattr hash help hex id input int isinstance issubclass "
                "iter len list locals long map max min object oct open "
                "ord pow property range raw_input reduce reload repr "
                "reversed round set setattr slice sorted staticmethod "
                "str sum super tuple type type unichr unicode vars xrange "
                "zip apply buffer coerce intern __dict__ Ellipsis False True NotImplemented "
                "__class__ __bases__ __name__ exception Exception StandardError ArithmeticError "
                "LookupError EnvironmentError AssertionError AttributeError EOFError FloatingPointError IOError "
                "ImportError IndexError KeyError KeyboardInterrupt MemoryError NameError NotImplementedError OSError "
                "OverflowError ReferenceError RuntimeError StopIteration SyntaxError SystemError SystemExit "
                "TypeError UnboundLocalError UnicodeError UnicodeEncodeError UnicodeDecodeError UnicodeTranslateError ValueError WindowsError "
                "ZeroDivisionError Warning UserWarning DeprecationWarning PendingDeprecationWarning SyntaxWarning RuntimeWarning FutureWarning");

    const wxString keywords1 = wxT("self sys gc weakref fpectl atexit types UserDict UserList UserString  operator inspect traceback linecache pickle cPickle copy_reg shelve copy marshal warnings imp zipimport pkgutil "
                 "modulefinder code codeop pprint repr new site user __builtin__ __main__ __future__ string re struct difflib fpformat StringIO cStringIO textwrap codecs encodings.idna unicodedata "
                 "stringprep pydoc doctest unittest test test.test_support decimal math cmath random whrandom bisect collections heapq array sets itertools ConfigParser fileinput calendar cmd "
                 "shlexos os.path dircache stat statcache statvfs filecmp subprocess popen2 datetime time sched mutex getpass curses curses.textpad curses.wrapper curses.ascii curses.panel getopt "
                 "optparse tempfile errno glob fnmatch shutil locale gettext logging platform signal socket select thread threading dummy_thread dummy_threading Queue mmap anydbm dbhash whichdb "
                 "bsddb dumbdbm zlib gzip bz2 zipfile tarfile readline rlcompleter posix pwd grp crypt dl dbm gdbm termios tty pty fcntl pipes posixfile resource nis syslog commands hotshot timeit "
                 "webbrowser cgi cgitb urllib urllib2 httplib ftplib gopherlib poplib imaplib nntplib smtplib smtpd telnetlib urlparse  SocketServer BaseHTTPServer SimpleHTTPServer CGIHTTPServer "
                 "cookielib Cookie xmlrpclib SimpleXMLRPCServer DocXMLRPCServer asyncore asynchat formatter email email.Message email.Parser email.Generator email.Header email.Charset email.Encoders "
                 "email.Errors email.Utils email.Iterators mailcap mailbox mhlib mimetools mimetypes MimeWriter mimify multifile rfc822 base64 binascii binhex quopri uu xdrlib netrc robotparser csv "
                 "HTMLParser sgmllib htmllib htmlentitydefs xml.parsers.expat xml.dom xml.dom.minidom xml.dom.pulldom xml.sax xml.sax.handler xml.sax.saxutils xml.sax.xmlreader xmllib audioop "
                 "imageop aifc sunau wave chunk colorsys rgbimg imghdr sndhdr ossaudiodev hmac md5 sha Tkinter Tix ScrolledText turtle parser symbol token keyword tokenize tabnanny pyclbr py_compile "
                 "compileall dis pickletools distutils");
}

wxArrayString PyContext::GetKeywords()
{
    wxArrayString ret;
    ret.Add( LexPython::keywords0 );
    ret.Add( LexPython::keywords1 );

    return ret;
}

void PyContext::SetStyles( wxStyledTextCtrl* control )
{
    control->StyleSetSpec(wxSTC_STYLE_LINENUMBER, wxString("back:#E0E0E0,face:Monospace"));
    control->StyleSetSpec(wxSTC_STYLE_CONTROLCHAR, wxString("face:Courier"));
    control->StyleSetSpec(wxSTC_STYLE_BRACELIGHT, wxString("fore:#0000FF,back:#FFFF88"));
    control->StyleSetSpec(wxSTC_STYLE_BRACEBAD, wxString("fore:#FF0000,back:#FFFF88"));

    control->StyleSetSpec(wxSTC_P_DEFAULT, wxString("face:Monospace"));
    control->StyleSetSpec(wxSTC_P_COMMENTLINE, wxString("fore:#007F00,face:Monospace"));
    control->StyleSetSpec(wxSTC_P_NUMBER, wxString("fore:#0000C0,face:Monospace"));
    control->StyleSetSpec(wxSTC_P_STRING, wxString("fore:#7F007F,face:Monospace"));
    control->StyleSetSpec(wxSTC_P_CHARACTER, wxString("fore:#7F007F,face:Monospace"));
    control->StyleSetSpec(wxSTC_P_WORD, wxString("fore:#00007F,bold"));
    control->StyleSetSpec(wxSTC_P_WORD2, wxString("fore:#00007F,italic,bold"));
    control->StyleSetSpec(wxSTC_P_TRIPLE, wxString("fore:#7F0000"));
    control->StyleSetSpec(wxSTC_P_TRIPLEDOUBLE, wxString("fore:#000033,back:#FFFFE8"));
    control->StyleSetSpec(wxSTC_P_DEFNAME, wxString("fore:#007F7F,bold"));
    control->StyleSetSpec(wxSTC_P_CLASSNAME, wxString("fore:#C00000,italic,bold"));
    control->StyleSetSpec(wxSTC_P_OPERATOR, wxString(""));
    control->StyleSetSpec(wxSTC_P_IDENTIFIER, wxString(""));
    control->StyleSetSpec(wxSTC_P_COMMENTBLOCK, wxString("fore:#7F7F7F"));
    control->StyleSetSpec(wxSTC_P_STRINGEOL, wxString("fore:#000000,face:Monospace,back:#E0C0E0,eolfilled"));

//    control->StyleSetBold(wxSTC_P_WORD, true);
//    control->StyleSetForeground(wxSTC_P_WORD, *wxBLUE);
//    control->StyleSetForeground(wxSTC_P_STRING, *wxRED);
//    control->StyleSetForeground(wxSTC_P_STRINGEOL, *wxRED);
//    control->StyleSetForeground(wxSTC_P_COMMENTBLOCK, wxColour(0, 128, 0));
//    control->StyleSetForeground(wxSTC_P_COMMENTLINE, wxColour(0, 128, 0));
//    control->StyleSetForeground(wxSTC_P_NUMBER, *wxBLUE );
}
