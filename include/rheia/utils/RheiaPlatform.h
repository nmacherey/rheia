#ifndef RheiaPlatform_h_
#define RheiaPlatform_h_

#include <wx/string.h>

/**
*	The namespace platform is used to determine on which host the application is running.
*   This is very important because Rheia has some functionnalities that are managed differently
*   in different platforms
*/
namespace platform
{
    enum identifier
    {
        platform_unknown,				/// Unknown platform
        platform_windows,				/// Windows host
        platform_linux,						/// Linux Hosts
        platform_freebsd,				/// Free Bsd hosts
        platform_netbsd,					/// netbsd hosts
        platform_openbsd,				/// openbsd hosts
        platform_darwin,					/// darwin hosts
        platform_solaris,					/// solaris hosts
        platform_macosx					/// macosx hosts
    };

    // unfortunately we still need to use the preprocessor here...
#if ( wxUSE_UNICODE )
    const bool unicode = true;
#else
    const bool unicode = false;
#endif

#if   defined ( __WIN32__ )
    const identifier id = platform_windows;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("Win64");
#else
    const wxString subsystem = wxT("Win32");
#endif
#elif defined ( __WXMAC__ )  || defined ( __WXCOCOA__ )
    const identifier id = platform_macosx;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("MacOsX64");
#else
    const wxString subsystem = wxT("MacOsX32");
#endif
#elif defined ( __linux__ )  || defined ( LINUX )
    const identifier id = platform_linux;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("Linux64");
#else
    const wxString subsystem = wxT("Linux32");
#endif
#elif defined ( FREEBSD )    || defined ( __FREEBSD__ )
    const identifier id = platform_freebsd;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("FreeBsd64");
#else
    const wxString subsystem = wxT("FreeBsd32");
#endif
#elif defined ( NETBSD )     || defined ( __NETBSD__ )
    const identifier id = platform_netbsd;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("NetBsd64");
#else
    const wxString subsystem = wxT("NetBsd32");
#endif
#elif defined ( OPENBSD )    || defined ( __OPENBSD__ )
    const identifier id = platform_openbsd;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("OpenBsd64");
#else
    const wxString subsystem = wxT("OpenBsd32");
#endif
#elif defined ( DARWIN )     || defined ( __APPLE__ )
    const identifier id = platform_darwin;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("Darwin64");
#else
    const wxString subsystem = wxT("Darwin32");
#endif
#elif defined(sun) || defined(__sun)
    const identifier id = platform_solaris;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("Solaris64");
#else
    const wxString subsystem = wxT("Solaris32");
#endif
#else
    const identifier id = platform_unknown;
#if defined( _RHEIA_64_BYTES )
    const wxString subsystem = wxT("Unknown64");
#else
    const wxString subsystem = wxT("Unknown32");
#endif
#endif

#if   defined ( __WXGTK__ )
    const bool gtk = true;
#else
    const bool gtk = false;
#endif

#if   defined ( __WXMAC__ )
    const bool carbon = true;
#else
    const bool carbon = false;
#endif

#if   defined ( __WXCOCOA__ )
    const bool cocoa = true;
#else
    const bool cocoa = false;
#endif

#if defined ( linux )
#undef linux
#endif

#if defined ( unix )
#undef unix
#endif

    const bool windows = (id == platform_windows);
    const bool macosx  = (id == platform_macosx);
    const bool linux   = (id == platform_linux);
    const bool freebsd = (id == platform_freebsd);
    const bool netbsd  = (id == platform_netbsd);
    const bool openbsd = (id == platform_openbsd);
    const bool darwin  = (id == platform_darwin);
    const bool solaris = (id == platform_solaris);
    const bool unix    = (linux | freebsd | netbsd | openbsd | darwin | solaris);

    const int bits = 8*sizeof(void*);


#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 2)
    //const int gcc = Version<__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__>::eval;
#define pure_function       __attribute__ ((pure, nothrow))
#define const_function      __attribute__ ((const, nothrow))
#define force_inline        __attribute__ ((always_inline))
#define warn_unused         __attribute__ ((warn_unused_result))
#define deprecated_function __attribute__ ((deprecated))
#else
    const int gcc = 0;
#define pure_function
#define const_function
#define force_inline
#define warn_unused
#define deprecated_function
#endif
};

#endif
