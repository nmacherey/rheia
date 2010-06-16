/* Generated from configure.ac by autoheader as of 2006-07-08
 * and converted to cmake form.  cmake has no equivalent to
 * autoheader yet so this file must be maintained manually from
 * now on, i.e., if there is an addition of a configurable symbol,
 * (all done from the top-level CMakeLists.txt file)
 * it must be entered here as well in order for C/C++ programmes
 * to have access to the configured symbol.*/

/* Location of executables */
#define BIN_DIR "."

/* isnan is in math.h but not cmath */
/* #undef BROKEN_ISNAN_CXX */

/* Location of Build tree */
#define BUILD_DIR "."

/* Location of package data files */
#ifndef PLPLOT_DEBUG
#ifdef WIN32
#define DATA_DIR "./share/rheia/plplot/data"
#else
#define DATA_DIR "../share/rheia/plplot/data"
#endif
#else
#ifdef WIN32
#define DATA_DIR "./share/rheia-dbg/plplot/data"
#else
#define DATA_DIR "../share/rheia-dbg/plplot/data"
#endif
#endif
/* Location of dynamically loaded drivers */
#define DRV_DIR "."

/* Define if there is support for dynamically loaded drivers */
//#define ENABLE_DYNDRIVERS

/* Define to 1 if you have the <cmath> header file. */
#define HAVE_CMATH 1

/* Define if you have c++ accessible stdint.h */
/* #undef HAVE_CXX_STDINT_H */
#ifdef unix
#define HAVE_CXX_STDINT_H
#endif

#ifdef unix
#define HAVE_STDINT_H
#endif

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_DIRENT_H */
#ifdef unix
#define HAVE_DIRENT_H 1
#endif
/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define if finite is available */
//#define HAVE_FINITE

/* Define if _finite is available */
//#define _HAVE_FINITE

/* Define if [freetype] is available */
/* #undef HAVE_FREETYPE */

/* Define if [agg] is available */
/* #undef HAVE_AGG */

/* Define to 1 if you have the <glib.h> header file. */
/* #undef HAVE_GLIB_H */
#ifdef unix
#define HAVE_GLIB_H 1
#endif
/* Define to 1 if you have the <glib-object.h> header file. */
/* #undef HAVE_GLIB_OBJECT_H */

/* Define to 1 if you have the <gtk/gtk.h> header file. */
/* #undef HAVE_GTK_GTK_H */
#ifdef unix
#define HAVE_GTK_GTK_H 1
#endif

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define if isinf is available */
/* #undef HAVE_ISINF */

/* Define if _isinf is available */
/* #undef _HAVE_ISINF */

/* Define if isnan is available */
//#define HAVE_ISNAN

/* Define if _isnan is available */
//#define _HAVE_ISNAN

/* Define if snprintf is available */
#define PL_HAVE_SNPRINTF

/* Define if _snprintf is available */
//#ifndef _PL_HAVE_SNPRINTF
#ifdef WIN32
#define _PL_HAVE_SNPRINTF
#endif
//#endif

/* Define if [incr], [Tcl] is available */
/* #undef HAVE_ITCL */

/* Define to 1 if you have the <itclDecls.h> header file. */
/* #undef HAVE_ITCLDECLS_H */

/* Define if Tk is available */
/* #undef ENABLE_tk */

/* Define if Tcl version is greater than 8.4 */
/* #undef HAVE_TCL_GT_84 */

/* Define if [incr], [Tk] is available */
/* #undef HAVE_ITK */

/* Define to 1 if you have the <jni.h> header file. */
/* #undef HAVE_JNI_H */

/* Define to 1 if you have the <libart_lgpl/libart.h> header file. */
/* #undef HAVE_LIBART_LGPL_LIBART_H */

/* Define to 1 if you have the <libgnomecanvas/libgnomecanvas.h> header file.
   */
/* #undef HAVE_LIBGNOMECANVAS_LIBGNOMECANVAS_H */

/* Define to 1 if you have the <libgnomeprint/gnome-print.h> header file. */
/* #undef HAVE_LIBGNOMEPRINT_GNOME_PRINT_H */

/* Define if libunicode is available */
/* #undef HAVE_LIBUNICODE */

/* Define to 1 if you have the <math.h> header file. */
/* #undef HAVE_MATH_H */
#define HAVE_MATH_H

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define if python numpy is available */
#define HAVE_NUMPY

/* Define if libpango is available */
/* #undef HAVE_PANGO */

/* Define if popen is available */
/* #undef HAVE_POPEN */

/* Define if pthreads is available */
/* #undef HAVE_PTHREAD */
#ifdef unix
#define HAVE_PTHREAD
#endif

/* Define if Qhull is available */
/* #undef HAVE_QHULL */

/* Define to 1 if you have the <stdint.h> header file. */
#ifdef unix
#define HAVE_STDINT_H
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
/* #undef HAVE_STDLIB_H */
#define HAVE_STDLIB_H

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
/* #undef HAVE_SYS_STAT_H */
#ifdef unix
#define HAVE_SYS_DIR_H 1
#define HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
/* #undef HAVE_SYS_TYPES_H */
#define HAVE_SYS_TYPES_H
#endif

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
/* #undef HAVE_SYS_WAIT_H */

/* Define to 1 if you have the <termios.h> header file. */
/* #undef HAVE_TERMIOS_H */

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */
#define HAVE_UNISTD_H

/* Define if usleep is available */
/* #undef PL_HAVE_USLEEP */

/* Define to 1 if you have the `vfork' function. */
/* #undef HAVE_VFORK */

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Include sys/type.h if needed */
#define NEED_SYS_TYPE_H

/* Name of package */
#define PACKAGE "plplot"

/* Define if the win32 ltdl implementation should be used */
#ifdef WIN32
#define LTDL_WIN32
#endif
/* Define if aqt driver is present */
/* #undef PLD_aqt */

/* Define if cgm driver is present */
//#define PLD_cgm

/* Define if conex driver is present */
/* #undef PLD_conex */

/* Define if dg300 driver is present */
/* #undef PLD_dg300 */

/* Define if gcw driver is present */
/* #undef PLD_gcw */

/* Define if gif driver is present */
/* #undef PLD_gif */

/* Define if gnome driver is present */
/* #undef PLD_gnome */

/* Define if hp7470 driver is present */
//#define PLD_hp7470

/* Define if hp7580 driver is present */
//#define PLD_hp7580

/* Define if imp driver is present */
/* #undef PLD_imp */

/* Define if jpeg driver is present */
/* #undef PLD_jpeg */

/* Define if linuxvga driver is present */
/* #undef PLD_linuxvga */

/* Define if lj_hpgl driver is present */
//#define PLD_lj_hpgl

/* Define if ljii driver is present */
/* #undef PLD_ljii */

/* Define if ljiip driver is present */
/* #undef PLD_ljiip */

/* Define if mem driver is present */
//#define PLD_mem

/* Define if mskermit driver is present */
/* #undef PLD_mskermit */

/* Define if ntk driver is present */
/* #undef PLD_ntk */

/* Define if null driver is present */
//#define PLD_null

/* Define if pbm driver is present */
//#define PLD_pbm

/* Define if pdf driver is present */
/* #undef PLD_pdf */

/* Define if plmeta driver is present */
/* #undef PLD_plmeta */

/* Define if png driver is present */
/* #undef PLD_png */

/* Define if ps driver is present */
//#define PLD_ps

/* Define if pstex driver is present */
/* #undef PLD_pstex */

/* Define if psttf driver is present */
/* #undef PLD_psttf */

/* Define if svg driver is present */
//#define PLD_svg

/* Define if tek4010 driver is present */
/* #undef PLD_tek4010 */

/* Define if tek4010f driver is present */
/* #undef PLD_tek4010f */

/* Define if tek4107 driver is present */
/* #undef PLD_tek4107 */

/* Define if tek4107f driver is present */
/* #undef PLD_tek4107f */

/* Define if tk driver is present */
/* #undef PLD_tk */

/* Define if tkwin driver is present */
/* #undef PLD_tkwin */

/* Define if versaterm driver is present */
/* #undef PLD_versaterm */

/* Define if vlt driver is present */
/* #undef PLD_vlt */

/* Define if wingcc driver is present */
/* #undef PLD_wingcc */

/* Define if wxwidgets driver is present */
#define PLD_wxwidgets

/* Define if wxwidgets png driver is present */
/* #undef PLD_wxpng */

/* Define if xfig driver is present */
//#define PLD_xfig

/* Define if xterm driver is present */
/* #undef PLD_xterm */

/* Define if xwin driver is present */
/* #undef PLD_xwin */

/* Define if the Cairo external context driver is present */
/* #undef PLD_extcairo */

/* Define if Cairo PDF driver is present */
/* #undef PLD_pdfcairo */

/* Define if Cairo memory driver is present */
/* #undef PLD_memcairo */

/* Define if Cairo PNG driver is present */
/* #undef PLD_pngcairo */

/* Define if Cairo PS driver is present */
/* #undef PLD_pscairo */

/* Define if Cairo SVG driver is present */
/* #undef PLD_svgcairo */

/* Define if the cairo X windows driver is present */
/* #undef PLD_xcairo */

/* Define if the EPS Qt driver is present */
/* #undef PLD_epsqt */

/* Define if the PDF Qt driver is present */
/* #undef PLD_pdfqt */

/* Define if Qt Widget driver is present */
/* #undef PLD_qtwidget */

/* Define if SVG Qt driver is present */
/* #undef PLD_svgqt */

/* Define if bmp Qt driver is present */
/* #undef PLD_bmpqt */

/* Define if jpg Qt driver is present */
/* #undef PLD_jpgqt */

/* Define if png Qt driver is present */
/* #undef PLD_pngqt */

/* Define if ppm Qt driver is present */
/* #undef PLD_ppmqt */

/* Define if tiff Qt driver is present */
/* #undef PLD_tiffqt */

/* Define if external context Qt driver is present */
/* #undef PLD_extqt */

/* Portable definition for PTHREAD_MUTEX_RECURSIVE */
#define PLPLOT_MUTEX_RECURSIVE

/* PLplot's PLFLT floating-point is "double" by default, undefine PL_DOUBLE if
   single precision is required */
#define PL_DOUBLE

/* Directory containing fonts that are accessible from freetype */
#define PL_FREETYPE_FONT_DIR ""

/* MONO font accessible from freetype */
#define PL_FREETYPE_MONO ""

/* MONO_BOLD font accessible from freetype */
#define PL_FREETYPE_MONO_BOLD ""

/* MONO_BOLD_ITALIC font accessible from freetype */
#define PL_FREETYPE_MONO_BOLD_ITALIC ""

/* MONO_BOLD_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_MONO_BOLD_OBLIQUE ""

/* MONO_ITALIC font accessible from freetype */
#define PL_FREETYPE_MONO_ITALIC ""

/* MONO_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_MONO_OBLIQUE ""

/* SANS font accessible from freetype */
#define PL_FREETYPE_SANS ""

/* SANS_BOLD font accessible from freetype */
#define PL_FREETYPE_SANS_BOLD ""

/* SANS_BOLD_ITALIC font accessible from freetype */
#define PL_FREETYPE_SANS_BOLD_ITALIC ""

/* SANS_BOLD_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SANS_BOLD_OBLIQUE ""

/* SANS_ITALIC font accessible from freetype */
#define PL_FREETYPE_SANS_ITALIC ""

/* SANS_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SANS_OBLIQUE ""

/* SCRIPT font accessible from freetype */
#define PL_FREETYPE_SCRIPT ""

/* SCRIPT_BOLD font accessible from freetype */
#define PL_FREETYPE_SCRIPT_BOLD ""

/* SCRIPT_BOLD_ITALIC font accessible from freetype */
#define PL_FREETYPE_SCRIPT_BOLD_ITALIC ""

/* SCRIPT_BOLD_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SCRIPT_BOLD_OBLIQUE ""

/* SCRIPT_ITALIC font accessible from freetype */
#define PL_FREETYPE_SCRIPT_ITALIC ""

/* SCRIPT_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SCRIPT_OBLIQUE ""

/* SERIF font accessible from freetype */
#define PL_FREETYPE_SERIF ""

/* SERIF_BOLD font accessible from freetype */
#define PL_FREETYPE_SERIF_BOLD ""

/* SERIF_BOLD_ITALIC font accessible from freetype */
#define PL_FREETYPE_SERIF_BOLD_ITALIC ""

/* SERIF_BOLD_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SERIF_BOLD_OBLIQUE ""

/* SERIF_ITALIC font accessible from freetype */
#define PL_FREETYPE_SERIF_ITALIC ""

/* SERIF_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SERIF_OBLIQUE ""

/* Symbol font accessible from freetype */
#define PL_FREETYPE_SYMBOL ""

/* SYMBOL_BOLD font accessible from freetype */
#define PL_FREETYPE_SYMBOL_BOLD ""

/* SYMBOL_BOLD_ITALIC font accessible from freetype */
#define PL_FREETYPE_SYMBOL_BOLD_ITALIC ""

/* SYMBOL_BOLD_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SYMBOL_BOLD_OBLIQUE ""

/* SYMBOL_ITALIC font accessible from freetype */
#define PL_FREETYPE_SYMBOL_ITALIC ""

/* SYMBOL_OBLIQUE font accessible from freetype */
#define PL_FREETYPE_SYMBOL_OBLIQUE ""

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if you have the ANSI C header files. */
/* #undef STDC_HEADERS */

/* Location of Tcl stuff */
//#define TCL_DIR "./share/plplot/tcl"

/* Define if C++ compiler accepts using namespace */
#define USE_NAMESPACE

/* Version number of package */
#define VERSION "5.9.4"

/* Define if csa is desired */
#define WITH_CSA

/* Define to `char *' if <sys/types.h> does not define. */
/* #undef caddr_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */

