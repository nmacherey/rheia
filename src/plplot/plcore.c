/* $Id: plcore.c 9869 2009-05-01 15:11:49Z smekal $

	Central dispatch facility for PLplot.
	Also contains the PLplot main data structures, external access
	routines, and initialization calls.

	This stuff used to be in "dispatch.h", "dispatch.c", and "base.c".


  Copyright (C) 2004  Joao Cardoso
  Copyright (C) 2004, 2005  Rafael Laboissiere
  Copyright (C) 2004, 2006  Andrew Ross
  Copyright (C) 2004  Andrew Roach
  Copyright (C) 2005  Alan W. Irwin
  Copyright (C) 2005  Thomas J. Duck

  This file is part of PLplot.

  PLplot is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Library Public License as published
  by the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  PLplot is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with PLplot; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

*/

#define DEBUG

#define NEED_PLDEBUG
#include "plcore.h"

#ifdef ENABLE_DYNDRIVERS
#ifndef LTDL_WIN32
#include <ltdl.h>
#else
#include "ltdl_win32.h"
#endif
#endif

#if HAVE_DIRENT_H
/* The following conditional is a workaround for a bug in the MacOSX system.
   When  the dirent.h file will be fixed upstream by Apple Inc, this should
   go away. */
# ifdef NEED_SYS_TYPE_H
#  include <sys/types.h>
# endif
# include <dirent.h>
# define NAMLEN(dirent) strlen((dirent)->d_name)
#else
# if defined(_MSC_VER)
#  include "dirent_msvc.h"
# else
#  define dirent direct
#  define NAMLEN(dirent) (dirent)->d_namlen
#  if HAVE_SYS_NDIR_H
#   include <sys/ndir.h>
#  endif
#  if HAVE_SYS_DIR_H
#   include <sys/dir.h>
#  endif
#  if HAVE_NDIR_H
#   include <ndir.h>
#  endif
# endif
#endif

/* AM: getcwd has a somewhat strange status on Windows, its proper
   name is _getcwd, this is a problem in the case of DLLs, like with
   the Java bindings. The functions _getcwd() and chdir() are
   declared in direct.h for Visual C++. Since chdir() is deprecated
   (but still available) in Visual C++ we redefine chdir to _chdir.
*/
#if defined(_MSC_VER)
#  include <direct.h>
#  define getcwd _getcwd
#  define chdir _chdir
#endif

#define BUFFER_SIZE 80
#define BUFFER2_SIZE 300
#define DRVSPEC_SIZE 400

/*--------------------------------------------------------------------------*\
 * Driver Interface
 *
 * These routines are the low-level interface to the driver -- all calls to
 * driver functions must pass through here.  For implementing driver-
 * specific functions, the escape function is provided.  The command stream
 * gets duplicated to the plot buffer here.
 *
 * All functions that result in graphics actually being plotted (rather than
 * just a change of state) are filtered as necessary before being passed on.
 * The default settings do not require any filtering, i.e.  PLplot physical
 * coordinates are the same as the device physical coordinates (currently
 * this can't be changed anyway), and a global view equal to the entire page
 * is used.
 *
 * The reason one wants to put view-specific filtering here is that if
 * enabled, the plot buffer should receive the unfiltered data stream.  This
 * allows a specific view to be used from an interactive device (e.g. TCL/TK
 * driver) but be restored to the full view at any time merely by
 * reprocessing the contents of the plot buffer.
 *
 * The metafile, on the other hand, *should* be affected by changes in the
 * view, since this is a crucial editing capability.  It is recommended that
 * the initial metafile be created without a restricted global view, and
 * modification of the view done on a per-plot basis as desired during
 * subsequent processing.
 *
\*--------------------------------------------------------------------------*/

enum {AT_BOP, DRAWING, AT_EOP};

/* Initialize device. */
/* The plot buffer must be called last. */

/* The following array of chars is used both here and in plsym.c for
 * translating the Greek characters from the #g escape sequences into
 * the Hershey and Unicode codings
 */
const char plP_greek_mnemonic[] = "ABGDEZYHIKLMNCOPRSTUFXQWabgdezyhiklmncoprstufxqw";

void
plP_init(void)
{
    plsc->page_status = AT_EOP;

    (*plsc->dispatch_table->pl_init) ((struct PLStream_struct *) plsc);

    if (plsc->plbuf_write)
        plbuf_init(plsc);
}

/* End of page */
/* The plot buffer must be called first. */
/* Ignore instruction if already at eop. */

void
plP_eop(void)
{
    int skip_driver_eop = 0;

    if (plsc->page_status == AT_EOP)
        return;

    plsc->page_status = AT_EOP;

    if (plsc->plbuf_write)
        plbuf_eop(plsc);

    /* Call user eop handler if present. */

    if (plsc->eop_handler != NULL)
        (*plsc->eop_handler) (plsc->eop_data, &skip_driver_eop);

    if (!skip_driver_eop)
        (*plsc->dispatch_table->pl_eop) ((struct PLStream_struct *) plsc);
}

/* Set up new page. */
/* The plot buffer must be called last. */
/* Ignore if already at bop. */
/* It's not actually necessary to be AT_EOP here, so don't check for it. */

void
plP_bop(void)
{
    int skip_driver_bop = 0;

    plP_subpInit();
    if (plsc->page_status == AT_BOP)
        return;

    plsc->page_status = AT_BOP;
    plsc->nplwin = 0;

    /* Call user bop handler if present. */

    if (plsc->bop_handler != NULL)
        (*plsc->bop_handler) (plsc->bop_data, &skip_driver_bop);

    if (!skip_driver_bop)
        (*plsc->dispatch_table->pl_bop) ((struct PLStream_struct *) plsc);

    if (plsc->plbuf_write)
        plbuf_bop(plsc);
}

/* Tidy up device (flush buffers, close file, etc). */

void
plP_tidy(void)
{
    if (plsc->tidy)
    {
        (*plsc->tidy) (plsc->tidy_data);
        plsc->tidy = NULL;
        plsc->tidy_data = NULL;
    }

    (*plsc->dispatch_table->pl_tidy) ((struct PLStream_struct *) plsc);

    if (plsc->plbuf_write)
    {
        plbuf_tidy(plsc);
    }

    plsc->OutFile = NULL;

}

/* Change state. */

void
plP_state(PLINT op)
{
    if (plsc->plbuf_write) plbuf_state(plsc, op);

    (*plsc->dispatch_table->pl_state) ((struct PLStream_struct *) plsc, op);
}

/* Escape function, for driver-specific commands. */

void
plP_esc(PLINT op, void *ptr)
{
    PLINT clpxmi, clpxma, clpymi, clpyma;
    EscText* args;

    /* The plot buffer must be called first */
    if (plsc->plbuf_write) plbuf_esc(plsc, op, ptr);

    /* Text coordinates must pass through the driver interface filter */
    if ((op==PLESC_HAS_TEXT && plsc->dev_unicode)||
            (op==PLESC_END_TEXT && plsc->alt_unicode))
    {

        /* Apply the driver interface filter */
        if (plsc->difilt)
        {
            args = (EscText*)ptr;
            difilt(&(args->x),&(args->y),1,&clpxmi,&clpxma,&clpymi,&clpyma);
        }
    }

    (*plsc->dispatch_table->pl_esc) ((struct PLStream_struct *) plsc, op, ptr);
}

/* Set up plot window parameters. */
/* The plot buffer must be called first */
/* Some drivers (metafile, Tk) need access to this data */

void
plP_swin(PLWindow *plwin)
{
    PLWindow *w;
    PLINT clpxmi, clpxma, clpymi, clpyma;

    /* Provide plot buffer with unfiltered window data */

    if (plsc->plbuf_write)
        plbuf_esc(plsc, PLESC_SWIN, (void *) plwin);

    w = &plsc->plwin[plsc->nplwin++ % PL_MAXWINDOWS];

    w->dxmi = plwin->dxmi;
    w->dxma = plwin->dxma;
    w->dymi = plwin->dymi;
    w->dyma = plwin->dyma;

    if (plsc->difilt)
    {
        xscl[0] = plP_dcpcx(w->dxmi);
        xscl[1] = plP_dcpcx(w->dxma);
        yscl[0] = plP_dcpcy(w->dymi);
        yscl[1] = plP_dcpcy(w->dyma);

        difilt(xscl, yscl, 2, &clpxmi, &clpxma, &clpymi, &clpyma);

        w->dxmi = plP_pcdcx(xscl[0]);
        w->dxma = plP_pcdcx(xscl[1]);
        w->dymi = plP_pcdcy(yscl[0]);
        w->dyma = plP_pcdcy(yscl[1]);
    }

    w->wxmi = plwin->wxmi;
    w->wxma = plwin->wxma;
    w->wymi = plwin->wymi;
    w->wyma = plwin->wyma;

    /* If the driver wants to process swin commands, call it now */
    /* It must use the filtered data, which it can get from *plsc */

    if (plsc->dev_swin)
    {
        (*plsc->dispatch_table->pl_esc) ( (struct PLStream_struct *) plsc,
                                          PLESC_SWIN, NULL );
    }
}

/*--------------------------------------------------------------------------*\
 *  Drawing commands.
\*--------------------------------------------------------------------------*/

/* Draw line between two points */
/* The plot buffer must be called first so it gets the unfiltered data */

void
plP_line(short *x, short *y)
{
    PLINT i, npts = 2, clpxmi, clpxma, clpymi, clpyma;

    plsc->page_status = DRAWING;

    if (plsc->plbuf_write)
        plbuf_line(plsc, x[0], y[0], x[1], y[1]);

    if (plsc->difilt)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = x[i];
            yscl[i] = y[i];
        }
        difilt(xscl, yscl, npts, &clpxmi, &clpxma, &clpymi, &clpyma);
        plP_pllclp(xscl, yscl, npts, clpxmi, clpxma, clpymi, clpyma, grline);
    }
    else
    {
        grline(x, y, npts);
    }
}

/* Draw polyline */
/* The plot buffer must be called first */

void
plP_polyline(short *x, short *y, PLINT npts)
{
    PLINT i, clpxmi, clpxma, clpymi, clpyma;

    plsc->page_status = DRAWING;

    if (plsc->plbuf_write)
        plbuf_polyline(plsc, x, y, npts);

    if (plsc->difilt)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = x[i];
            yscl[i] = y[i];
        }
        difilt(xscl, yscl, npts, &clpxmi, &clpxma, &clpymi, &clpyma);
        plP_pllclp(xscl, yscl, npts, clpxmi, clpxma, clpymi, clpyma,
                   grpolyline);
    }
    else
    {
        grpolyline(x, y, npts);
    }
}

/* Fill polygon */
/* The plot buffer must be called first */
/* Here if the desired area fill capability isn't present, we mock up */
/* something in software */

static int foo;

void
plP_fill(short *x, short *y, PLINT npts)
{
    PLINT i, clpxmi, clpxma, clpymi, clpyma;

    plsc->page_status = DRAWING;

    if (plsc->plbuf_write)
    {
        plsc->dev_npts = npts;
        plsc->dev_x = x;
        plsc->dev_y = y;
        plbuf_esc(plsc, PLESC_FILL, NULL);
    }

    /* Account for driver ability to do fills */

    if (plsc->patt == 0 && ! plsc->dev_fill0)
    {
        if ( ! foo)
        {
            plwarn("Driver does not support hardware solid fills, switching to software fill.\n");
            foo = 1;
        }
        plsc->patt = 8;
        plpsty(plsc->patt);
    }
    if (plsc->dev_fill1)
    {
        plsc->patt = -ABS(plsc->patt);
    }

    /* Perform fill.  Here we MUST NOT allow the software fill to pass through the
       driver interface filtering twice, else we get the infamous 2*rotation for
       software fills on orientation swaps.
    */

    if (plsc->patt > 0)
        plfill_soft(x, y, npts);

    else
    {
        if (plsc->difilt)
        {
            for (i = 0; i < npts; i++)
            {
                xscl[i] = x[i];
                yscl[i] = y[i];
            }
            difilt(xscl, yscl, npts, &clpxmi, &clpxma, &clpymi, &clpyma);
            plP_plfclp(xscl, yscl, npts, clpxmi, clpxma, clpymi, clpyma,
                       grfill);
        }
        else
        {
            grfill(x, y, npts);
        }
    }
}

/* Account for driver ability to draw text itself */
/*
#define DEBUG_TEXT
*/

/*--------------------------------------------------------------------------*\
 *  int text2num( char *text, char end, PLUNICODE *num)
 *       char *text - pointer to the text to be parsed
 *       char end   - end character (i.e. ')' or ']' to stop parsing
 *       PLUNICODE *num - pointer to an PLUNICODE to store the value
 *
 *    Function takes a string, which can be either hex or decimal,
 *    and converts it into an PLUNICODE, stopping at either a null,
 *    or the character pointed to by 'end'. This implementation using
 *    the C library strtoul replaces the original brain-dead version
 *    and should be more robust to invalid control strings.
\*--------------------------------------------------------------------------*/

int text2num( const char *text, char end, PLUNICODE *num)
{

    char *endptr;
    char msgbuf[BUFFER_SIZE];

    *num = strtoul(text,&endptr,0);

    if (end != endptr[0])
    {
        snprintf(msgbuf,BUFFER_SIZE,"text2num: invalid control string detected - %c expected",end);
        plwarn(msgbuf);
    }

    return (int)(endptr - text);

}

/*--------------------------------------------------------------------------*\
 *  int text2fci( char *text, unsigned char *hexdigit, unsigned char *hexpower)
 *       char *text - pointer to the text to be parsed
 *       unsigned char *hexdigit - pointer to hex value that is stored.
 *       unsigned char *hexpower - pointer to hex power (left shift) that is stored.
 *
 *    Function takes a pointer to a string, which is looked up in a table
 *    to determine the corresponding FCI (font characterization integer)
 *    hex digit value and hex power (left shift).  All matched strings
 *    start with "<" and end with the two characters "/>".
 *    If the lookup succeeds, hexdigit and hexpower are set to the appropriate
 *    values in the table, and the function returns the number of characters
 *    in text that are consumed by the matching string in the table lookup.
 *
 *    If the lookup fails, hexdigit is set to 0, hexpower is set to and
 *    impossible value, and the function returns 0.
\*--------------------------------------------------------------------------*/

int text2fci( const char *text, unsigned char *hexdigit, unsigned char *hexpower)
{
    typedef struct
    {
        char *ptext;
        unsigned char hexdigit;
        unsigned char hexpower;
    }
    TextLookupTable;
    /* This defines the various font control commands and the corresponding
     * hexdigit and hexpower in the FCI.
     */
#define N_TextLookupTable 10
    const TextLookupTable lookup[N_TextLookupTable] =
    {
        {"<sans-serif/>", PL_FCI_SANS, PL_FCI_FAMILY},
        {"<serif/>", PL_FCI_SERIF, PL_FCI_FAMILY},
        {"<monospace/>", PL_FCI_MONO, PL_FCI_FAMILY},
        {"<script/>", PL_FCI_SCRIPT, PL_FCI_FAMILY},
        {"<symbol/>", PL_FCI_SYMBOL, PL_FCI_FAMILY},
        {"<upright/>", PL_FCI_UPRIGHT, PL_FCI_STYLE},
        {"<italic/>", PL_FCI_ITALIC, PL_FCI_STYLE},
        {"<oblique/>", PL_FCI_OBLIQUE, PL_FCI_STYLE},
        {"<medium/>", PL_FCI_MEDIUM, PL_FCI_WEIGHT},
        {"<bold/>", PL_FCI_BOLD, PL_FCI_WEIGHT}
    };
    int i, length;
    for (i=0; i<N_TextLookupTable; i++)
    {
        length = strlen(lookup[i].ptext);
        if (! strncmp(text, lookup[i].ptext, length))
        {
            *hexdigit = lookup[i].hexdigit;
            *hexpower = lookup[i].hexpower;
            return(length);
        }
    }
    *hexdigit = 0;
    *hexpower = PL_FCI_HEXPOWER_IMPOSSIBLE;
    return(0);
}

static PLUNICODE unicode_buffer[1024];

void
plP_text(PLINT base, PLFLT just, PLFLT *xform, PLINT x, PLINT y,
         PLINT refx, PLINT refy, const char *string)
{

    if (plsc->dev_text)   /* Does the device render it's own text ? */
    {
        EscText args;
        short len=0;
        char skip;
        unsigned short i,j;
        PLUNICODE code;
        char esc;
        int idx;

        args.base = base;
        args.just = just;
        args.xform = xform;
        args.x = x;
        args.y = y;
        args.refx = refx;
        args.refy = refy;
        args.string = string;

        if (plsc->dev_unicode)   /* Does the device also understand unicode? */
        {
            PLINT ig;
            PLUNICODE fci, fcisave;
            unsigned char hexdigit, hexpower;

            /* Now process the text string */

            if (string!=NULL) {        /* If the string isn't blank, then we will
                                     * continue
				     */

                len=strlen(string);     /* this length is only used in the loop
				     * counter, we will work out the length of
				     * the unicode string as we go */
                plgesc(&esc);

                /* At this stage we will do some translations into unicode, like
                 * conversion to Greek , and will save other translations such as
                 * superscript for the driver to do later on. As we move through
                 * the string and do the translations, we will get
                 * rid of the esc character sequence, just replacing it with
                 * unicode.
                 */

                /* Obtain FCI (font characterization integer) for start of
                 * string. */
                plgfci(&fci);

                if (plsc->alt_unicode)
                {
                    args.n_fci = fci;
                    plP_esc(PLESC_BEGIN_TEXT, &args);
                }
                for (j=i=0;i<len;i++) {    /* Walk through the string, and convert
					* some stuff to unicode on the fly */
                    skip=0;

                    if (string[i]==esc)
                    {
                        switch (string[i+1])
                        {
                        case '(':  /* hershey code */
                            i+=2+text2num(&string[i+2],')',&code);
                            idx=plhershey2unicode(code);
                            /* momentarily switch to symbol font. */
                            fcisave = fci;
                            plP_hex2fci(PL_FCI_SYMBOL, PL_FCI_FAMILY, &fci);
                            unicode_buffer[j++]= fci;
                            unicode_buffer[j++] = \
                                                  (PLUNICODE)hershey_to_unicode_lookup_table[idx].Unicode;

                            if (plsc->alt_unicode)
                            {
                                args.n_fci = fci;
                                args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                plP_esc(PLESC_CONTROL_CHAR, &args);
                                args.n_char =					\
                                                  (PLUNICODE)hershey_to_unicode_lookup_table[idx].Unicode;
                                plP_esc(PLESC_TEXT_CHAR, &args);
                            }

                            /* if unicode_buffer[j-1] corresponds to the escape
                             * character must unescape it by appending one more.
                             * This will probably always be necessary since it is
                             * likely unicode_buffer will always have to contain
                             * escape characters that are interpreted by the device
                             * driver.
                             */
                            if (unicode_buffer[j-1]==esc) unicode_buffer[j++]=esc;
                            fci = fcisave;
                            unicode_buffer[j]= fci;
                            skip=1;
                            break;

                        case '[':  /* unicode */
                            i+=2+text2num(&string[i+2],']',&code);
                            /* momentarily switch to symbol font. */
                            fcisave = fci;
                            plP_hex2fci(PL_FCI_SYMBOL, PL_FCI_FAMILY, &fci);
                            unicode_buffer[j++]= fci;
                            unicode_buffer[j++]=code;

                            if (plsc->alt_unicode)
                            {
                                args.n_fci = fci;
                                args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                plP_esc(PLESC_CONTROL_CHAR, &args);
                                args.n_char = code;
                                plP_esc(PLESC_TEXT_CHAR, &args);
                            }

                            /* if unicode_buffer[j-1] corresponds to the escape
                             * character must unescape it by appending one more.
                             * This will probably always be necessary since it is
                             * likely unicode_buffer will always have to contain
                             * escape characters that are interpreted by the device
                             * driver.
                             */
                            if (unicode_buffer[j-1]==esc) unicode_buffer[j++]=esc;
                            fci = fcisave;
                            unicode_buffer[j] = fci;
                            skip=1;
                            break;

                        case '<':  /* change font*/
                            if ('0' <= string[i+2] && string[i+2] <= '9' )
                            {
                                i+=2+text2num(&string[i+2],'>', &code);
                                if (code & PL_FCI_MARK)
                                {
                                    /* code is a complete FCI (font characterization
                                     * integer): change FCI to this value.
                                     */
                                    fci = code;
                                    unicode_buffer[j]=fci;
                                    skip=1;

                                    if (plsc->alt_unicode)
                                    {
                                        args.n_fci = fci;
                                        args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                        plP_esc(PLESC_CONTROL_CHAR, &args);
                                    }
                                }
                                else
                                {
                                    /* code is not complete FCI. Change
                                     * FCI with hex power in rightmost hex
                                     * digit and hex digit value in second rightmost
                                     * hex digit.
                                     */
                                    hexdigit = (code >> 4) & PL_FCI_HEXDIGIT_MASK;
                                    hexpower = code & PL_FCI_HEXPOWER_MASK;
                                    plP_hex2fci(hexdigit, hexpower, &fci);
                                    unicode_buffer[j]=fci;
                                    skip=1;

                                    if (plsc->alt_unicode)
                                    {
                                        args.n_fci = fci;
                                        args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                        plP_esc(PLESC_CONTROL_CHAR, &args);
                                    }
                                }
                            }

                            else
                            {
                                i+=text2fci(&string[i+1], &hexdigit, &hexpower);
                                if (hexpower < 7)
                                {
                                    plP_hex2fci(hexdigit, hexpower, &fci);
                                    unicode_buffer[j]=fci;
                                    skip=1;

                                    if (plsc->alt_unicode)
                                    {
                                        args.n_fci = fci;
                                        args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                        plP_esc(PLESC_CONTROL_CHAR, &args);
                                    }
                                }
                            }
                            break;

                        case 'f':  /* Deprecated Hershey-style font change*/
                        case 'F':  /* Deprecated Hershey-style font change*/
                            /* We implement an approximate response here so that
                             * reasonable results are obtained for unicode fonts,
                             * but this method is deprecated and the #<nnn> or
                             * #<command string> methods should be used instead
                             * to change unicode fonts in mid-string.
                             */
                            fci = PL_FCI_MARK;
                            if (string[i+2] == 'n')
                            {
                                /* medium, upright, sans-serif */
                                plP_hex2fci(PL_FCI_SANS, PL_FCI_FAMILY, &fci);
                            }
                            else if (string[i+2] == 'r')
                            {
                                /* medium, upright, serif */
                                plP_hex2fci(PL_FCI_SERIF, PL_FCI_FAMILY, &fci);
                            }
                            else if (string[i+2] == 'i')
                            {
                                /* medium, italic, serif */
                                plP_hex2fci(PL_FCI_ITALIC, PL_FCI_STYLE, &fci);
                                plP_hex2fci(PL_FCI_SERIF, PL_FCI_FAMILY, &fci);
                            }
                            else if (string[i+2] == 's')
                            {
                                /* medium, upright, script */
                                plP_hex2fci(PL_FCI_SCRIPT, PL_FCI_FAMILY, &fci);
                            }
                            else
                                fci = PL_FCI_IMPOSSIBLE;

                            if (fci != PL_FCI_IMPOSSIBLE)
                            {
                                i+=2;
                                unicode_buffer[j] = fci;
                                skip = 1;

                                if (plsc->alt_unicode)
                                {
                                    args.n_fci = fci;
                                    args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                    plP_esc(PLESC_CONTROL_CHAR, &args);
                                }
                            }
                            break;

                        case 'g':  /* Greek font */
                        case 'G':  /* Greek font */
                            /* Get the index in the lookup table
                             * 527 = upper case alpha displacement in Hershey Table
                             * 627 = lower case alpha displacement in Hershey Table
                             */
                            /* momentarily switch to symbol font. */
                            fcisave = fci;
                            plP_hex2fci(PL_FCI_SYMBOL, PL_FCI_FAMILY, &fci);
                            unicode_buffer[j++]= fci;

                            if (plsc->alt_unicode)
                            {
                                args.n_fci = fci;
                                args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                plP_esc(PLESC_CONTROL_CHAR, &args);
                            }

                            ig = plP_strpos(plP_greek_mnemonic, string[i+2]);
                            if (ig >= 0)
                            {
                                if (ig >= 24)
                                    ig = ig + 100 - 24;
                                idx=plhershey2unicode(ig+527);
                                unicode_buffer[j++] = \
                                                      (PLUNICODE)hershey_to_unicode_lookup_table[idx].Unicode;
                                i+=2;
                                skip=1;  /* skip is set if we have copied something
				  * into the unicode table */

                                if (plsc->alt_unicode)
                                {
                                    args.n_char =					\
                                                      (PLUNICODE)hershey_to_unicode_lookup_table[idx].Unicode;
                                    plP_esc(PLESC_TEXT_CHAR, &args);
                                }
                            }
                            else
                            {
                                /* Use "unknown" unicode character if string[i+2]
                                 * is not in the Greek array.*/
                                unicode_buffer[j++]=(PLUNICODE)0x00;
                                i+=2;
                                skip=1;  /* skip is set if we have copied something
				  * into  the unicode table */

                                if (plsc->alt_unicode)
                                {
                                    args.n_char =					\
                                                      (PLUNICODE)hershey_to_unicode_lookup_table[idx].Unicode;
                                    plP_esc(PLESC_TEXT_CHAR, &args);
                                }
                            }
                            fci = fcisave;
                            unicode_buffer[j]= fci;

                            if (plsc->alt_unicode)
                            {
                                args.n_fci = fci;
                                args.n_ctrl_char = PLTEXT_FONTCHANGE;
                                plP_esc(PLESC_CONTROL_CHAR, &args);
                            }
                            break;

                        case 'u':
                            if (plsc->alt_unicode)
                            {
                                args.n_ctrl_char = PLTEXT_SUPERSCRIPT;
                                plP_esc(PLESC_CONTROL_CHAR, &args);
                                i += 1;
                                skip = 1;
                            }
                            break;

                        case 'd':
                            if (plsc->alt_unicode)
                            {
                                args.n_ctrl_char = PLTEXT_SUBSCRIPT;
                                plP_esc(PLESC_CONTROL_CHAR, &args);
                                i += 1;
                                skip = 1;
                            }
                            break;
                        }
                    }

                    if (skip==0)
                    {
                        PLUNICODE unichar = 0;
#ifdef HAVE_LIBUNICODE
                        char* ptr = unicode_get_utf8 (string + i, &unichar);
#else
                        char* ptr = utf8_to_ucs4 (string + i, &unichar);
#endif
                        if (ptr == NULL)
                        {
                            char buf[BUFFER_SIZE];
                            strncpy (buf, string, 30);
                            buf[30] = '\0';
                            snprintf (buf, BUFFER_SIZE, "UTF-8 string is malformed: %s%s",
                                      buf, strlen (string) > 30 ? "[...]" : "");
                            plabort (buf);
                            return;
                        }
                        unicode_buffer [j] = unichar;
                        i += ptr - (string + i) - 1;

                        /* Search for escesc (an unescaped escape) in the input
                         * string and adjust unicode_buffer accordingly).
                         */
                        if (unicode_buffer[j] == esc && string[i+1] == esc)
                        {
                            i++;
                            unicode_buffer[++j] = esc;
                            args.n_char = esc;
                        }
                        else
                        {
                            args.n_char = unichar;
                        }
                        if (plsc->alt_unicode)
                        {
                            plP_esc(PLESC_TEXT_CHAR, &args);
                        }
                    }
                    j++;
                }
                if (j > 0)
                {
                    args.unicode_array_len=j; /* Much easier to set the length than
					  * work it out later :-) */
                    args.unicode_array=&unicode_buffer[0]; /* Get address of the
						       * unicode buffer (even
						       * though it is
						       * currently  static) */
                }
                else
                    /* Don't print anything, if there is no unicode to print! */
                    return;
            }

            if (plsc->alt_unicode)
            {
                plP_esc(PLESC_END_TEXT, &args);
            }
        }

        if (plsc->dev_unicode)
        {
            args.string=NULL; /* We are using unicode */
        }
        else
        {
            args.string = string;
        }

        if (!plsc->alt_unicode)
        {
            plP_esc(PLESC_HAS_TEXT, &args);
        }
#ifndef DEBUG_TEXT
    }
    else
    {
#endif
        plstr(base, xform, refx, refy, string);
    }
}

/* convert utf8 string to ucs4 unichar */
static char *
utf8_to_ucs4(const char *ptr, PLUNICODE *unichar)
{
    char tmp;
    int isFirst = 1;
    int cnt = 0;

    do
    {
        /* Get next character in string */
        tmp = *ptr++;
        if (isFirst)   /* First char in UTF8 sequence */
        {
            isFirst = 0;
            /* Determine length of sequence */
            if ((unsigned char)(tmp & 0x80) == 0x00)   /* single char */
            {
                *unichar = (unsigned int)tmp & 0x7F;
                cnt = 0;
            }
            else if ((unsigned char)(tmp & 0xE0) == 0xC0)   /* 2 chars */
            {
                *unichar = (unsigned int)tmp & 0x1F;
                cnt = 1;
            }
            else if ((unsigned char)(tmp & 0xF0) == 0xE0)   /* 3 chars */
            {
                *unichar = (unsigned char)tmp & 0x0F;
                cnt = 2;
            }
            else if ((unsigned char)(tmp & 0xF8) == 0xF0)   /* 4 chars */
            {
                *unichar = (unsigned char)tmp & 0x07;
                cnt = 3;
            }
            else if ((unsigned char)(tmp & 0xFC) == 0xF8)   /* 5 chars */
            {
                *unichar = (unsigned char)tmp & 0x03;
                cnt = 4;
            }
            else if ((unsigned char)(tmp & 0xFE) == 0xFC)   /* 6 chars */
            {
                *unichar = (unsigned char)tmp & 0x01;
                cnt = 5;
            }
            else   /* Malformed */
            {
                ptr = NULL;
                cnt = 0;
            }
        }
        else   /* Subsequent char in UTF8 sequence */
        {
            if ((unsigned char)(tmp & 0xC0) == 0x80)
            {
                *unichar = (*unichar << 6) | ((unsigned int)tmp & 0x3F);
                cnt--;
            }
            else   /* Malformed */
            {
                ptr = NULL;
                cnt = 0;
            }
        }
    }
    while (cnt > 0);
    return (char *) ptr;
}

/* convert ucs4 unichar to utf8 string */
int
ucs4_to_utf8(PLUNICODE unichar, char *ptr)
{
    unsigned char *tmp;
    int len;

    tmp = (unsigned char *)ptr;

    if ( (unichar & 0xffff80) == 0 )    /* single byte */
    {
        *tmp = (unsigned char) unichar;
        tmp++;
        len = 1;
    }
    else if ( (unichar & 0xfff800) == 0)   /* two bytes */
    {
        *tmp = (unsigned char) 0xc0 | (unichar >> 6);
        tmp++;
        *tmp = (unsigned char) 0x80 | (unichar & 0x3f);
        tmp++;
        len = 2;
    }
    else if ( (unichar & 0xff0000) == 0)   /* three bytes */
    {
        *tmp = (unsigned char) 0xe0 | (unichar >> 12);
        tmp++;
        *tmp = (unsigned char) 0x80 | ((unichar >> 6) & 0x3f);
        tmp++;
        *tmp = (unsigned char) 0x80 | (unichar & 0x3f);
        tmp++;
        len = 3;
    }
    else if ( (unichar & 0xe0000) == 0)  /* four bytes */
    {
        *tmp = (unsigned char) 0xf0 | (unichar >> 18);
        tmp++;
        *tmp = (unsigned char) 0x80 | ((unichar >> 12) & 0x3f);
        tmp++;
        *tmp = (unsigned char) 0x80 | ((unichar >> 6) & 0x3f);
        tmp++;
        *tmp = (unsigned char) 0x80 | (unichar & 0x3f);
        tmp++;
        len = 4;
    }
    else    /* Illegal coding */
    {
        len = 0;
    }
    *tmp = '\0';

    return len;
}

static void
grline(short *x, short *y, PLINT npts)
{
    (*plsc->dispatch_table->pl_line) ( (struct PLStream_struct *) plsc,
                                       x[0], y[0], x[1], y[1] );
}

static void
grpolyline(short *x, short *y, PLINT npts)
{
    (*plsc->dispatch_table->pl_polyline) ( (struct PLStream_struct *) plsc,
                                           x, y, npts );
}

static void
grfill(short *x, short *y, PLINT npts)
{
    plsc->dev_npts = npts;
    plsc->dev_x = x;
    plsc->dev_y = y;

    (*plsc->dispatch_table->pl_esc) ( (struct PLStream_struct *) plsc,
                                      PLESC_FILL, NULL );
}

/*--------------------------------------------------------------------------*\
 * void difilt
 *
 * Driver interface filter -- passes all coordinates through a variety
 * of filters.  These include filters to change :
 *
 *	- mapping of meta to physical coordinates
 *	- plot orientation
 *	- window into plot (zooms)
 *	- window into device (i.e set margins)
 *
 * The filters are applied in the order specified above.  Because the
 * orientation change comes first, subsequent window specifications affect
 * the new coordinates (i.e. after a 90 degree flip, what was x is now y).
 * This is the only way that makes sense from a graphical interface
 * (e.g. TCL/TK driver).
 *
 * Where appropriate, the page clip limits are modified.
\*--------------------------------------------------------------------------*/

void
difilt(PLINT *xscl, PLINT *yscl, PLINT npts,
       PLINT *clpxmi, PLINT *clpxma, PLINT *clpymi, PLINT *clpyma)
{
    PLINT i, x, y;

    /* Map meta coordinates to physical coordinates */

    if (plsc->difilt & PLDI_MAP)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = (PLINT)(plsc->dimxax * xscl[i] + plsc->dimxb);
            yscl[i] = (PLINT)(plsc->dimyay * yscl[i] + plsc->dimyb);
        }
    }

    /* Change orientation */

    if (plsc->difilt & PLDI_ORI)
    {
        for (i = 0; i < npts; i++)
        {
            x = (PLINT)(plsc->dioxax * xscl[i] + plsc->dioxay * yscl[i] + plsc->dioxb);
            y = (PLINT)(plsc->dioyax * xscl[i] + plsc->dioyay * yscl[i] + plsc->dioyb);
            xscl[i] = x;
            yscl[i] = y;
        }
    }

    /* Change window into plot space */

    if (plsc->difilt & PLDI_PLT)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = (PLINT)(plsc->dipxax * xscl[i] + plsc->dipxb);
            yscl[i] = (PLINT)(plsc->dipyay * yscl[i] + plsc->dipyb);
        }
    }

    /* Change window into device space and set clip limits */
    /* (this is the only filter that modifies them) */

    if (plsc->difilt & PLDI_DEV)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = (PLINT)(plsc->didxax * xscl[i] + plsc->didxb);
            yscl[i] = (PLINT)(plsc->didyay * yscl[i] + plsc->didyb);
        }
        *clpxmi = plsc->diclpxmi;
        *clpxma = plsc->diclpxma;
        *clpymi = plsc->diclpymi;
        *clpyma = plsc->diclpyma;
    }
    else
    {
        *clpxmi = plsc->phyxmi;
        *clpxma = plsc->phyxma;
        *clpymi = plsc->phyymi;
        *clpyma = plsc->phyyma;
    }
}

void
sdifilt(short *xscl, short *yscl, PLINT npts,
        PLINT *clpxmi, PLINT *clpxma, PLINT *clpymi, PLINT *clpyma)
{
    int i;
    short x, y;

    /* Map meta coordinates to physical coordinates */

    if (plsc->difilt & PLDI_MAP)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = (PLINT)(plsc->dimxax * xscl[i] + plsc->dimxb);
            yscl[i] = (PLINT)(plsc->dimyay * yscl[i] + plsc->dimyb);
        }
    }

    /* Change orientation */

    if (plsc->difilt & PLDI_ORI)
    {
        for (i = 0; i < npts; i++)
        {
            x = (PLINT)(plsc->dioxax * xscl[i] + plsc->dioxay * yscl[i] + plsc->dioxb);
            y = (PLINT)(plsc->dioyax * xscl[i] + plsc->dioyay * yscl[i] + plsc->dioyb);
            xscl[i] = x;
            yscl[i] = y;
        }
    }

    /* Change window into plot space */

    if (plsc->difilt & PLDI_PLT)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = (PLINT)(plsc->dipxax * xscl[i] + plsc->dipxb);
            yscl[i] = (PLINT)(plsc->dipyay * yscl[i] + plsc->dipyb);
        }
    }

    /* Change window into device space and set clip limits */
    /* (this is the only filter that modifies them) */

    if (plsc->difilt & PLDI_DEV)
    {
        for (i = 0; i < npts; i++)
        {
            xscl[i] = (PLINT)(plsc->didxax * xscl[i] + plsc->didxb);
            yscl[i] = (PLINT)(plsc->didyay * yscl[i] + plsc->didyb);
        }
        *clpxmi = (PLINT)(plsc->diclpxmi);
        *clpxma = (PLINT)(plsc->diclpxma);
        *clpymi = (PLINT)(plsc->diclpymi);
        *clpyma = (PLINT)(plsc->diclpyma);
    }
    else
    {
        *clpxmi = plsc->phyxmi;
        *clpxma = plsc->phyxma;
        *clpymi = plsc->phyymi;
        *clpyma = plsc->phyyma;
    }
}

/*--------------------------------------------------------------------------*\
 * void pldi_ini
 *
 * Updates driver interface, making sure everything is in order.
 * Even if filter is not being used, the defaults need to be set up.
\*--------------------------------------------------------------------------*/

static void
setdef_diplt()
{
    plsc->dipxmin = 0.0;
    plsc->dipxmax = 1.0;
    plsc->dipymin = 0.0;
    plsc->dipymax = 1.0;
}

static void
setdef_didev()
{
    plsc->mar = 0.0;
    plsc->aspect = 0.0;
    plsc->jx = 0.0;
    plsc->jy = 0.0;
}

static void
setdef_diori()
{
    plsc->diorot = 0.;
}

static void
pldi_ini(void)
{
    if (plsc->level >= 1)
    {
        if (plsc->difilt & PLDI_MAP)	/* Coordinate mapping */
            calc_dimap();

        if (plsc->difilt & PLDI_ORI)	/* Orientation */
            calc_diori();
        else
            setdef_diori();

        if (plsc->difilt & PLDI_PLT) 	/* Plot window */
            calc_diplt();
        else
            setdef_diplt();

        if (plsc->difilt & PLDI_DEV)	/* Device window */
            calc_didev();
        else
            setdef_didev();
    }
}

/*--------------------------------------------------------------------------*\
 * void pldid2pc
 *
 * Converts input values from relative device coordinates to relative plot
 * coordinates.  This function must be called when selecting a plot window
 * from a display driver, since the coordinates chosen by the user are
 * necessarily device-specific.
\*--------------------------------------------------------------------------*/

void
pldid2pc(PLFLT *xmin, PLFLT *ymin, PLFLT *xmax, PLFLT *ymax)
{
    PLFLT pxmin, pymin, pxmax, pymax;
    PLFLT sxmin, symin, sxmax, symax;
    PLFLT rxmin, rymin, rxmax, rymax;

    if (plsc->difilt & PLDI_DEV)
    {

        pldebug("pldid2pc",
                "Relative device coordinates (in): %f, %f, %f, %f\n",
                *xmin, *ymin, *xmax, *ymax);

        pxmin = plP_dcpcx(*xmin);
        pymin = plP_dcpcy(*ymin);
        pxmax = plP_dcpcx(*xmax);
        pymax = plP_dcpcy(*ymax);

        sxmin = (pxmin - plsc->didxb) / plsc->didxax;
        symin = (pymin - plsc->didyb) / plsc->didyay;
        sxmax = (pxmax - plsc->didxb) / plsc->didxax;
        symax = (pymax - plsc->didyb) / plsc->didyay;

        rxmin = plP_pcdcx((PLINT)sxmin);
        rymin = plP_pcdcy((PLINT)symin);
        rxmax = plP_pcdcx((PLINT)sxmax);
        rymax = plP_pcdcy((PLINT)symax);

        *xmin = (rxmin < 0) ? 0 : rxmin;
        *xmax = (rxmax > 1) ? 1 : rxmax;
        *ymin = (rymin < 0) ? 0 : rymin;
        *ymax = (rymax > 1) ? 1 : rymax;

        pldebug("pldid2pc",
                "Relative plot coordinates (out): %f, %f, %f, %f\n",
                rxmin, rymin, rxmax, rymax);
    }
}

/*--------------------------------------------------------------------------*\
 * void pldip2dc
 *
 * Converts input values from relative plot coordinates to relative
 * device coordinates.
\*--------------------------------------------------------------------------*/

void
pldip2dc(PLFLT *xmin, PLFLT *ymin, PLFLT *xmax, PLFLT *ymax)
{
    PLFLT pxmin, pymin, pxmax, pymax;
    PLFLT sxmin, symin, sxmax, symax;
    PLFLT rxmin, rymin, rxmax, rymax;

    if (plsc->difilt & PLDI_DEV)
    {

        pldebug("pldip2pc",
                "Relative plot coordinates (in): %f, %f, %f, %f\n",
                *xmin, *ymin, *xmax, *ymax);

        pxmin = plP_dcpcx(*xmin);
        pymin = plP_dcpcy(*ymin);
        pxmax = plP_dcpcx(*xmax);
        pymax = plP_dcpcy(*ymax);

        sxmin = pxmin * plsc->didxax + plsc->didxb;
        symin = pymin * plsc->didyay + plsc->didyb;
        sxmax = pxmax * plsc->didxax + plsc->didxb;
        symax = pymax * plsc->didyay + plsc->didyb;

        rxmin = plP_pcdcx((PLINT)sxmin);
        rymin = plP_pcdcy((PLINT)symin);
        rxmax = plP_pcdcx((PLINT)sxmax);
        rymax = plP_pcdcy((PLINT)symax);

        *xmin = (rxmin < 0) ? 0 : rxmin;
        *xmax = (rxmax > 1) ? 1 : rxmax;
        *ymin = (rymin < 0) ? 0 : rymin;
        *ymax = (rymax > 1) ? 1 : rymax;

        pldebug("pldip2pc",
                "Relative device coordinates (out): %f, %f, %f, %f\n",
                rxmin, rymin, rxmax, rymax);
    }
}

/*--------------------------------------------------------------------------*\
 * void plsdiplt
 *
 * Set window into plot space
\*--------------------------------------------------------------------------*/

void
c_plsdiplt(PLFLT xmin, PLFLT ymin, PLFLT xmax, PLFLT ymax)
{
    plsc->dipxmin = (xmin < xmax) ? xmin : xmax;
    plsc->dipxmax = (xmin < xmax) ? xmax : xmin;
    plsc->dipymin = (ymin < ymax) ? ymin : ymax;
    plsc->dipymax = (ymin < ymax) ? ymax : ymin;

    if (xmin == 0. && xmax == 1. && ymin == 0. && ymax == 1.)
    {
        plsc->difilt &= ~PLDI_PLT;
        return;
    }

    plsc->difilt |= PLDI_PLT;
    pldi_ini();
}

/*--------------------------------------------------------------------------*\
 * void plsdiplz
 *
 * Set window into plot space incrementally (zoom)
\*--------------------------------------------------------------------------*/

void
c_plsdiplz(PLFLT xmin, PLFLT ymin, PLFLT xmax, PLFLT ymax)
{
    if (plsc->difilt & PLDI_PLT)
    {
        xmin = plsc->dipxmin + (plsc->dipxmax - plsc->dipxmin) * xmin;
        ymin = plsc->dipymin + (plsc->dipymax - plsc->dipymin) * ymin;
        xmax = plsc->dipxmin + (plsc->dipxmax - plsc->dipxmin) * xmax;
        ymax = plsc->dipymin + (plsc->dipymax - plsc->dipymin) * ymax;
    }

    plsdiplt(xmin, ymin, xmax, ymax);
}

/*--------------------------------------------------------------------------*\
 * void calc_diplt
 *
 * Calculate transformation coefficients to set window into plot space.
 *
 * Note: if driver has requested to handle these commands itself, we must
 * send the appropriate escape command.  If the driver succeeds it will
 * cancel the filter operation.  The command is deferred until this point
 * to ensure that the driver has been initialized.
\*--------------------------------------------------------------------------*/

static void
calc_diplt(void)
{
    PLINT pxmin, pxmax, pymin, pymax, pxlen, pylen;

    if (plsc->dev_di)
    {
        (*plsc->dispatch_table->pl_esc) ( (struct PLStream_struct *) plsc,
                                          PLESC_DI, NULL );
    }

    if ( ! (plsc->difilt & PLDI_PLT))
        return;

    pxmin = plP_dcpcx(plsc->dipxmin);
    pxmax = plP_dcpcx(plsc->dipxmax);
    pymin = plP_dcpcy(plsc->dipymin);
    pymax = plP_dcpcy(plsc->dipymax);

    pxlen = pxmax - pxmin;
    pylen = pymax - pymin;
    pxlen = MAX(1, pxlen);
    pylen = MAX(1, pylen);

    plsc->dipxax = plsc->phyxlen / (double) pxlen;
    plsc->dipyay = plsc->phyylen / (double) pylen;
    plsc->dipxb = plsc->phyxmi - plsc->dipxax * pxmin;
    plsc->dipyb = plsc->phyymi - plsc->dipyay * pymin;
}

/*--------------------------------------------------------------------------*\
 * void plgdiplt
 *
 * Retrieve current window into plot space
\*--------------------------------------------------------------------------*/

void
c_plgdiplt(PLFLT *p_xmin, PLFLT *p_ymin, PLFLT *p_xmax, PLFLT *p_ymax)
{
    *p_xmin = plsc->dipxmin;
    *p_xmax = plsc->dipxmax;
    *p_ymin = plsc->dipymin;
    *p_ymax = plsc->dipymax;
}

/*--------------------------------------------------------------------------*\
 * void plsdidev
 *
 * Set window into device space using margin, aspect ratio, and
 * justification.  If you want to just use the previous value for any of
 * these, just pass in the magic value PL_NOTSET.
 *
 * It is unlikely that one should ever need to change the aspect ratio
 * but it's in there for completeness.
\*--------------------------------------------------------------------------*/

void
c_plsdidev(PLFLT mar, PLFLT aspect, PLFLT jx, PLFLT jy)
{
    plsetvar(plsc->mar, mar);
    plsetvar(plsc->aspect, aspect);
    plsetvar(plsc->jx, jx);
    plsetvar(plsc->jy, jy);

    if (mar == 0. && aspect == 0. && jx == 0. && jy == 0. &&
            ! (plsc->difilt & PLDI_ORI))
    {
        plsc->difilt &= ~PLDI_DEV;
        return;
    }

    plsc->difilt |= PLDI_DEV;
    pldi_ini();
}

/*--------------------------------------------------------------------------*\
 * void calc_didev
 *
 * Calculate transformation coefficients to set window into device space.
 * Calculates relative window bounds and calls plsdidxy to finish the job.
\*--------------------------------------------------------------------------*/

static void
calc_didev(void)
{
    PLFLT lx, ly, aspect, aspdev;
    PLFLT xmin, xmax, xlen, ymin, ymax, ylen;
    PLINT pxmin, pxmax, pymin, pymax, pxlen, pylen;

    if (plsc->dev_di)
    {
        (*plsc->dispatch_table->pl_esc) ( (struct PLStream_struct *) plsc,
                                          PLESC_DI, NULL );
    }

    if ( ! (plsc->difilt & PLDI_DEV))
        return;

    /* Calculate aspect ratio of physical device */

    lx = plsc->phyxlen / plsc->xpmm;
    ly = plsc->phyylen / plsc->ypmm;
    aspdev = lx / ly;

    if (plsc->difilt & PLDI_ORI)
        aspect = plsc->aspori;
    else
        aspect = plsc->aspect;

    if (aspect <= 0.)
        aspect = plsc->aspdev;

    /* Failsafe */

    plsc->mar = (plsc->mar > 0.5) ? 0.5 : plsc->mar;
    plsc->mar = (plsc->mar < 0.0) ? 0.0 : plsc->mar;
    plsc->jx = (plsc->jx >  0.5) ?  0.5 : plsc->jx;
    plsc->jx = (plsc->jx < -0.5) ? -0.5 : plsc->jx;
    plsc->jy = (plsc->jy >  0.5) ?  0.5 : plsc->jy;
    plsc->jy = (plsc->jy < -0.5) ? -0.5 : plsc->jy;

    /* Relative device coordinates that neutralize aspect ratio difference */

    xlen = (aspect < aspdev) ? (aspect / aspdev) : 1.0;
    ylen = (aspect < aspdev) ? 1.0 : (aspdev / aspect);

    xlen *= (1.0 - 2.*plsc->mar);
    ylen *= (1.0 - 2.*plsc->mar);

    xmin = (1. - xlen) * (0.5 + plsc->jx);
    xmax = xmin + xlen;

    ymin = (1. - ylen) * (0.5 + plsc->jy);
    ymax = ymin + ylen;

    /* Calculate transformation coefficients */

    pxmin = plP_dcpcx(xmin);
    pxmax = plP_dcpcx(xmax);
    pymin = plP_dcpcy(ymin);
    pymax = plP_dcpcy(ymax);

    pxlen = pxmax - pxmin;
    pylen = pymax - pymin;
    pxlen = MAX(1, pxlen);
    pylen = MAX(1, pylen);

    plsc->didxax = pxlen / (double) plsc->phyxlen;
    plsc->didyay = pylen / (double) plsc->phyylen;
    plsc->didxb = pxmin - plsc->didxax * plsc->phyxmi;
    plsc->didyb = pymin - plsc->didyay * plsc->phyymi;

    /* Set clip limits to conform to new page size */

    plsc->diclpxmi = (PLINT)(plsc->didxax * plsc->phyxmi + plsc->didxb);
    plsc->diclpxma = (PLINT)(plsc->didxax * plsc->phyxma + plsc->didxb);
    plsc->diclpymi = (PLINT)(plsc->didyay * plsc->phyymi + plsc->didyb);
    plsc->diclpyma = (PLINT)(plsc->didyay * plsc->phyyma + plsc->didyb);
}

/*--------------------------------------------------------------------------*\
 * void plgdidev
 *
 * Retrieve current window into device space
\*--------------------------------------------------------------------------*/

void
c_plgdidev(PLFLT *p_mar, PLFLT *p_aspect, PLFLT *p_jx, PLFLT *p_jy)
{
    *p_mar = plsc->mar;
    *p_aspect = plsc->aspect;
    *p_jx = plsc->jx;
    *p_jy = plsc->jy;
}

/*--------------------------------------------------------------------------*\
 * void plsdiori
 *
 * Set plot orientation, specifying rotation in units of pi/2.
\*--------------------------------------------------------------------------*/

void
c_plsdiori(PLFLT rot)
{
    plsc->diorot = rot;
    if (rot == 0.)
    {
        plsc->difilt &= ~PLDI_ORI;
        pldi_ini();
        return;
    }

    plsc->difilt |= PLDI_ORI;
    pldi_ini();
}

/*--------------------------------------------------------------------------*\
 * void calc_diori
 *
 * Calculate transformation coefficients to arbitrarily orient plot.
 * Preserve aspect ratios so the output doesn't suck.
\*--------------------------------------------------------------------------*/

static void
calc_diori(void)
{
    PLFLT r11, r21, r12, r22, cost, sint;
    PLFLT x0, y0, lx, ly, aspect;

    if (plsc->dev_di)
    {
        (*plsc->dispatch_table->pl_esc) ( (struct PLStream_struct *) plsc,
                                          PLESC_DI, NULL );
    }

    if ( ! (plsc->difilt & PLDI_ORI))
        return;

    /* Center point of rotation */

    x0 = (plsc->phyxma + plsc->phyxmi) / 2.;
    y0 = (plsc->phyyma + plsc->phyymi) / 2.;

    /* Rotation matrix */

    r11 = cos(plsc->diorot * PI / 2.);
    r21 = sin(plsc->diorot * PI / 2.);
    r12 = -r21;
    r22 = r11;

    cost = ABS(r11);
    sint = ABS(r21);

    /* Flip aspect ratio as necessary.  Grungy but I don't see a better way */

    aspect = plsc->aspect;
    if (aspect == 0.)
        aspect = plsc->aspdev;

    if (plsc->freeaspect)
        plsc->aspori = aspect;
    else
        plsc->aspori = (aspect * cost + sint) / (aspect * sint + cost);

    if ( ! (plsc->difilt & PLDI_DEV))
    {
        plsc->difilt |= PLDI_DEV;
        setdef_didev();
    }
    calc_didev();

    /* Compute scale factors */

    lx = plsc->phyxlen;
    ly = plsc->phyylen;

    /* Transformation coefficients */

    plsc->dioxax = r11;
    plsc->dioxay = r21 * (lx / ly);
    plsc->dioxb = (1. - r11) * x0 - r21 * y0 * (lx / ly);

    plsc->dioyax = r12 * (ly / lx);
    plsc->dioyay = r22;
    plsc->dioyb = (1. - r22) * y0 - r12 * x0 * (ly / lx);
}

/*--------------------------------------------------------------------------*\
 * void plgdiori
 *
 * Get plot orientation
\*--------------------------------------------------------------------------*/

void
c_plgdiori(PLFLT *p_rot)
{
    *p_rot = plsc->diorot;
}

/*--------------------------------------------------------------------------*\
 * void plsdimap
 *
 * Set up transformation from metafile coordinates.  The size of the plot is
 * scaled so as to preserve aspect ratio.  This isn't intended to be a
 * general-purpose facility just yet (not sure why the user would need it,
 * for one).
\*--------------------------------------------------------------------------*/

void
c_plsdimap(PLINT dimxmin, PLINT dimxmax, PLINT dimymin, PLINT dimymax,
           PLFLT dimxpmm, PLFLT dimypmm)
{
    plsetvar(plsc->dimxmin, dimxmin);
    plsetvar(plsc->dimxmax, dimxmax);
    plsetvar(plsc->dimymin, dimymin);
    plsetvar(plsc->dimymax, dimymax);
    plsetvar(plsc->dimxpmm, dimxpmm);
    plsetvar(plsc->dimypmm, dimypmm);

    plsc->difilt |= PLDI_MAP;
    pldi_ini();
}

/*--------------------------------------------------------------------------*\
 * void calc_dimap
 *
 * Set up transformation from metafile coordinates.  The size of the plot is
 * scaled so as to preserve aspect ratio.  This isn't intended to be a
 * general-purpose facility just yet (not sure why the user would need it,
 * for one).
\*--------------------------------------------------------------------------*/

static void
calc_dimap()
{
    PLFLT lx, ly;
    PLINT pxmin, pxmax, pymin, pymax;
    PLFLT dimxlen, dimylen, pxlen, pylen;

    if ((plsc->dimxmin == plsc->phyxmi) && (plsc->dimxmax == plsc->phyxma) &&
            (plsc->dimymin == plsc->phyymi) && (plsc->dimymax == plsc->phyyma) &&
            (plsc->dimxpmm == plsc->xpmm) && (plsc->dimypmm == plsc->ypmm))
    {
        plsc->difilt &= ~PLDI_MAP;
        return;
    }

    /* Set default aspect ratio */

    lx = (plsc->dimxmax - plsc->dimxmin + 1) / plsc->dimxpmm;
    ly = (plsc->dimymax - plsc->dimymin + 1) / plsc->dimypmm;

    plsc->aspdev = lx / ly;

    /* Build transformation to correct physical coordinates */

    dimxlen = plsc->dimxmax - plsc->dimxmin;
    dimylen = plsc->dimymax - plsc->dimymin;

    pxmin = plsc->phyxmi;
    pxmax = plsc->phyxma;
    pymin = plsc->phyymi;
    pymax = plsc->phyyma;
    pxlen = pxmax - pxmin;
    pylen = pymax - pymin;

    plsc->dimxax = pxlen / dimxlen;
    plsc->dimyay = pylen / dimylen;
    plsc->dimxb = pxmin - pxlen * plsc->dimxmin / dimxlen;
    plsc->dimyb = pymin - pylen * plsc->dimymin / dimylen;
}

/*--------------------------------------------------------------------------*\
 * void plflush()
 *
 * Flushes the output stream.  Use sparingly, if at all.
\*--------------------------------------------------------------------------*/

void
c_plflush(void)
{
    if (plsc->dev_flush)
    {
        (*plsc->dispatch_table->pl_esc) ( (struct PLStream_struct *) plsc,
                                          PLESC_FLUSH, NULL );
    }
    else
    {
        if (plsc->OutFile != NULL)
            fflush(plsc->OutFile);
    }
}

/*--------------------------------------------------------------------------*\
 * Startup routines.
\*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*\
 * void pllib_init()
 *
 * Initialize library.  Called internally by every startup routine.
 * Everything you want to always be initialized before plinit() is called
 * you should put here.  E.g. dispatch table setup, rcfile read, etc.
\*--------------------------------------------------------------------------*/

void
pllib_init()
{
    if (lib_initialized) return;
    lib_initialized = 1;

#ifdef ENABLE_DYNDRIVERS
    /* Create libltdl resources */
    lt_dlinit();
#endif

    /* Initialize the dispatch table with the info from the static drivers table
       and the available dynamic drivers. */

    plInitDispatchTable();
}

/*--------------------------------------------------------------------------*\
 * void plstar(nx, ny)
 *
 * Initialize PLplot, passing in the windows/page settings.
\*--------------------------------------------------------------------------*/

void
c_plstar(PLINT nx, PLINT ny)
{
    pllib_init();

    if (plsc->level != 0)
        plend1();

    plssub(nx, ny);

    c_plinit();
}

/*--------------------------------------------------------------------------*\
 * void plstart(devname, nx, ny)
 *
 * Initialize PLplot, passing the device name and windows/page settings.
\*--------------------------------------------------------------------------*/

void
c_plstart(const char *devname, PLINT nx, PLINT ny)
{
    pllib_init();

    if (plsc->level != 0)
        plend1();

    plssub(nx, ny);
    plsdev(devname);

    c_plinit();
}

/*--------------------------------------------------------------------------*\
 * void plinit()
 *
 * Initializes PLplot, using preset or default options.
\*--------------------------------------------------------------------------*/

void
c_plinit(void)
{
    PLFLT def_arrow_x[6] = {-0.5, 0.5, 0.3, 0.5, 0.3, 0.5};
    PLFLT def_arrow_y[6] = {0.0, 0.0,   0.2, 0.0, -0.2, 0.0};
    PLFLT lx, ly, xpmm_loc, ypmm_loc, aspect_old, aspect_new;
    PLINT mk = 0, sp = 0, inc = 0, del = 2000;

    pllib_init();

    if (plsc->level != 0)
        plend1();

    /* Set stream number */

    plsc->ipls = ipls;

    /* Set up devices */
    pllib_devinit();

    /* Auxiliary stream setup */
    plstrm_init();

    /* Initialize device & first page */
    plP_init();

    plP_bop();
    plsc->level = 1;


    /* The driver options are freed after driver initialisation,
     * since it is assumed that in this function options are
     * processed and stored somewhere else. For further driver
     * initialisations (e.g. copy stream) there are no driver
     * options defined. */
    plP_FreeDrvOpts();

    /* Calculate factor such that the character aspect ratio is preserved
     * when the overall aspect ratio is changed, i.e., if portrait mode is
     * requested (only honored for subset of drivers) or if the aspect ratio
     * is specified in any way, or if a 90 deg rotation occurs with
     * -freeaspect. */

    /* Case where plsc->aspect has a value.... (e.g., -a aspect on the
     * command line or 2nd parameter of plsdidev specified) */
    if (plsc->aspect > 0.)
    {
        lx = plsc->phyxlen / plsc->xpmm;
        ly = plsc->phyylen / plsc->ypmm;
        aspect_old = lx / ly;
        aspect_new = plsc->aspect;
        plsc->caspfactor = sqrt(aspect_old/aspect_new);
    }
    /* Case of 90 deg rotations with -freeaspect (this is also how portraite
     * mode is implemented for the drivers that honor -portrait). */
    else if (plsc->freeaspect && ABS(cos(plsc->diorot * PI / 2.)) <= 1.e-5)
    {
        lx = plsc->phyxlen / plsc->xpmm;
        ly = plsc->phyylen / plsc->ypmm;
        aspect_old = lx / ly;
        aspect_new = ly / lx;
        plsc->caspfactor = sqrt(aspect_old/aspect_new);
    }

    else
        plsc->caspfactor = 1.;

    /* Load fonts */

    plsc->cfont = 1;

    plfntld(initfont);

    /* Set up subpages */
    plP_subpInit();

    /* Set up number of allowed digits before switching to scientific notation */
    /* The user can always change this */

    if (plsc->xdigmax == 0)
        plsc->xdigmax = 4;

    if (plsc->ydigmax == 0)
        plsc->ydigmax = 4;

    if (plsc->zdigmax == 0)
        plsc->zdigmax = 3;

    if (plsc->timefmt == NULL)
        c_pltimefmt("%c");

    /* Use default transformation between continuous and broken-down time
       (and vice versa) if the transformation has not yet been defined
       for this stream. */
    if (plsc->qsasconfig == NULL)
        c_plconfigtime(0., 0., 0., 0x0, 0, 0, 0, 0, 0, 0, 0.);

    /* Switch to graphics mode and set color and arrow style*/

    plgra();
    plcol(1);

    plstyl(0, &mk, &sp);
    plpat(1, &inc, &del);

    plsvect(def_arrow_x, def_arrow_y, 6, 0);

    /* Set clip limits. */

    plsc->clpxmi = plsc->phyxmi;
    plsc->clpxma = plsc->phyxma;
    plsc->clpymi = plsc->phyymi;
    plsc->clpyma = plsc->phyyma;

    /* Page aspect ratio. */

    lx = plsc->phyxlen / plsc->xpmm;
    ly = plsc->phyylen / plsc->ypmm;
    plsc->aspdev = lx / ly;

    /* Initialize driver interface */

    pldi_ini();

    /* Apply compensating factor to original xpmm and ypmm so that
     * character aspect ratio is preserved when overall aspect ratio
     * is changed.  This must appear here in the code because previous
     * code in this routine and in routines that it calls must use the original
     * values of xpmm and ypmm before the compensating factor is applied.  */

    plP_gpixmm(&xpmm_loc, &ypmm_loc);
    plP_setpxl(xpmm_loc*plsc->caspfactor, ypmm_loc/plsc->caspfactor);
}

/*--------------------------------------------------------------------------*\
 * void plend()
 *
 * End a plotting session for all open streams.
\*--------------------------------------------------------------------------*/

void
c_plend(void)
{
    PLINT i;

    if (lib_initialized == 0) return;

    for (i = PL_NSTREAMS-1; i >= 0; i--)
    {
        if (pls[i] != NULL)
        {
            plsstrm(i);
            c_plend1();
        }
    }
    plfontrel();
#ifdef ENABLE_DYNDRIVERS
    /* Release the libltdl resources */
    lt_dlexit();
    /* Free up memory allocated to the dispatch tables */
    for (i = 0; i < npldynamicdevices; i++)
    {
        free_mem(loadable_device_list[i].devnam);
        free_mem(loadable_device_list[i].description);
        free_mem(loadable_device_list[i].drvnam);
        free_mem(loadable_device_list[i].tag);
    }
    free_mem(loadable_device_list);
    for (i = 0; i < nloadabledrivers; i++)
    {
        free_mem(loadable_driver_list[i].drvnam);
    }
    free_mem(loadable_driver_list);
    for (i = nplstaticdevices; i < npldrivers; i++)
    {
        free_mem(dispatch_table[i]->pl_MenuStr);
        free_mem(dispatch_table[i]->pl_DevName);
        free_mem(dispatch_table[i]);
    }
#endif
    for (i = 0; i < nplstaticdevices; i++)
    {
        free_mem(dispatch_table[i]);
    }
    free_mem(dispatch_table);

    lib_initialized = 0;
}

/*--------------------------------------------------------------------------*\
 * void plend1()
 *
 * End a plotting session for the current stream only.  After the stream is
 * ended the memory associated with the stream's PLStream data structure is
 * freed (for stream > 0), and the stream counter is set to 0 (the default).
\*--------------------------------------------------------------------------*/

void
c_plend1(void)
{
    if (plsc->level > 0)
    {
        plP_eop();
        plP_tidy();
        plsc->level = 0;
    }
    /* Move from plP_tidy because FileName may be set even if level == 0 */
    if (plsc->FileName)
        free_mem(plsc->FileName);

    /* Free all malloc'ed stream memory */

    free_mem(plsc->cmap0);
    free_mem(plsc->cmap1);
    free_mem(plsc->plwindow);
    free_mem(plsc->geometry);
    free_mem(plsc->dev);
    free_mem(plsc->BaseName);
#ifndef BUFFERED_FILE
    free_mem(plsc->plbuf_buffer);
#endif
    if (plsc->program) free_mem(plsc->program);
    if (plsc->server_name) free_mem(plsc->server_name);
    if (plsc->server_host) free_mem(plsc->server_host);
    if (plsc->server_port) free_mem(plsc->server_port);
    if (plsc->user) free_mem(plsc->user);
    if (plsc->plserver) free_mem(plsc->plserver);
    if (plsc->auto_path) free_mem(plsc->auto_path);

    if (plsc->arrow_x) free_mem(plsc->arrow_x);
    if (plsc->arrow_y) free_mem(plsc->arrow_y);

    if (plsc->timefmt) free_mem(plsc->timefmt);

    /* Close qsastime library for this stream that was opened by
       plconfigtime call in plinit. */

    closeqsas(&(plsc->qsasconfig));

    /* Free malloc'ed stream if not in initial stream, else clear it out */

    if (ipls > 0)
    {
        free_mem(plsc);
        pls[ipls] = NULL;
        plsstrm(0);
    }
    else
    {
        memset((char *) pls[ipls], 0, sizeof(PLStream));
    }
}

/*--------------------------------------------------------------------------*\
 * void plsstrm
 *
 * Set stream number.  If the data structure for a new stream is
 * unallocated, we allocate it here.
\*--------------------------------------------------------------------------*/

void
c_plsstrm(PLINT strm)
{
    if (strm < 0 || strm >= PL_NSTREAMS)
    {
        fprintf(stderr,
                "plsstrm: Illegal stream number %d, must be in [0, %d]\n",
                (int) strm, PL_NSTREAMS);
    }
    else
    {
        ipls = strm;
        if (pls[ipls] == NULL)
        {
            pls[ipls] = (PLStream *) malloc((size_t) sizeof(PLStream));
            if (pls[ipls] == NULL)
                plexit("plsstrm: Out of memory.");

            memset((char *) pls[ipls], 0, sizeof(PLStream));
        }
        plsc = pls[ipls];
        plsc->ipls = ipls;
    }
}

/*--------------------------------------------------------------------------*\
 * void plgstrm
 *
 * Get current stream number.
\*--------------------------------------------------------------------------*/

void
c_plgstrm(PLINT *p_strm)
{
    *p_strm = ipls;
}

/*--------------------------------------------------------------------------*\
 * void plmkstrm
 *
 * Creates a new stream and makes it the default.  Differs from using
 * plsstrm(), in that a free stream number is found, and returned.
 *
 * Unfortunately, I /have/ to start at stream 1 and work upward, since
 * stream 0 is preallocated.  One of the BIG flaws in the PLplot API is
 * that no initial, library-opening call is required.  So stream 0 must be
 * preallocated, and there is no simple way of determining whether it is
 * already in use or not.
\*--------------------------------------------------------------------------*/

void
c_plmkstrm(PLINT *p_strm)
{
    int i;

    for (i = 1; i < PL_NSTREAMS; i++)
    {
        if (pls[i] == NULL)
            break;
    }

    if (i == PL_NSTREAMS)
    {
        fprintf(stderr, "plmkstrm: Cannot create new stream\n");
        *p_strm = -1;
    }
    else
    {
        *p_strm = i;
        plsstrm(i);
    }
    plstrm_init();
}

/*--------------------------------------------------------------------------*\
 * void plstrm_init
 *
 * Does required startup initialization of a stream.  Should be called right
 * after creating one (for allocating extra memory, etc).  Users shouldn't
 * need to call this directly.
 *
 * This function can be called multiple times for a given stream, in which
 * case only the first call produces any effect.  For streams >= 1, which
 * are created dynamically, this is called by the routine that allocates
 * the stream.  Stream 0, which is preallocated, is much harder to deal with
 * because any of a number of different calls may be the first call to the
 * library.  This is handled by just calling plstrm_init() from every
 * function that might be called first.  Sucks, but it should work.
\*--------------------------------------------------------------------------*/

void
plstrm_init(void)
{
    if ( ! plsc->initialized)
    {
        plsc->initialized = 1;

        if (plsc->cmap0 == NULL)
            plscmap0n(0);

        if (plsc->cmap1 == NULL)
            plscmap1n(0);
    }

    plsc->psdoc = NULL;
}

/*--------------------------------------------------------------------------*\
 * pl_cpcolor
 *
 * Utility to copy one PLColor to another.
\*--------------------------------------------------------------------------*/

void
pl_cpcolor(PLColor *to, PLColor *from)
{
    to->r = from->r;
    to->g = from->g;
    to->b = from->b;
    to->a = from->a;
}

/*--------------------------------------------------------------------------*\
 * void plcpstrm
 *
 * Copies state parameters from the reference stream to the current stream.
 * Tell driver interface to map device coordinates unless flags == 1.
 *
 * This function is used for making save files of selected plots (e.g.
 * from the TK driver).  After initializing, you can get a copy of the
 * current plot to the specified device by switching to this stream and
 * issuing a plcpstrm() and a plreplot(), with calls to plbop() and
 * pleop() as appropriate.  The plot buffer must have previously been
 * enabled (done automatically by some display drivers, such as X).
\*--------------------------------------------------------------------------*/

void
c_plcpstrm(PLINT iplsr, PLINT flags)
{
    int i;
    PLStream *plsr;

    plsr = pls[iplsr];
    if (plsr == NULL)
    {
        fprintf(stderr, "plcpstrm: stream %d not in use\n", (int) iplsr);
        return;
    }

    /* May be debugging */

    plsc->debug = plsr->debug;

    /* Plot buffer -- need to copy file pointer so that plreplot() works */
    /* This also prevents inadvertent writes into the plot buffer */

#ifdef BUFFERED_FILE
    plsc->plbufFile = plsr->plbufFile;
#else
    plsc->plbuf_buffer_grow = plsr->plbuf_buffer_grow;
    plsc->plbuf_buffer_size = plsr->plbuf_buffer_size;
    plsc->plbuf_top = plsr->plbuf_top;
    plsc->plbuf_readpos = plsr->plbuf_readpos;
    if ((plsc->plbuf_buffer = malloc(plsc->plbuf_buffer_size)) == NULL)
        plexit("plcpstrm: Error allocating plot buffer.");
    memcpy( plsc->plbuf_buffer, plsr->plbuf_buffer, plsr->plbuf_top );
#endif

    /* Driver interface */
    /* Transformation must be recalculated in current driver coordinates */

    if (plsr->difilt & PLDI_PLT)
        plsdiplt(plsr->dipxmin, plsr->dipymin, plsr->dipxmax, plsr->dipymax);

    if (plsr->difilt & PLDI_DEV)
        plsdidev(plsr->mar, plsr->aspect, plsr->jx, plsr->jy);

    if (plsr->difilt & PLDI_ORI)
        plsdiori(plsr->diorot);

    /* Map device coordinates */

    if ( ! (flags & 0x01))
    {
        pldebug("plcpstrm", "mapping parameters: %d %d %d %d %f %f\n",
                plsr->phyxmi, plsr->phyxma, plsr->phyymi, plsr->phyyma,
                plsr->xpmm, plsr->ypmm);
        plsdimap(plsr->phyxmi, plsr->phyxma, plsr->phyymi, plsr->phyyma,
                 plsr->xpmm, plsr->ypmm);
    }

    /* current color */

    pl_cpcolor(&plsc->curcolor, &plsr->curcolor);

    /* cmap 0 */

    plsc->icol0 = plsr->icol0;
    plsc->ncol0 = plsr->ncol0;
    if (plsc->cmap0 != NULL)
        free((void *) plsc->cmap0);

    if ((plsc->cmap0 = (PLColor *) calloc(1, plsc->ncol0 * sizeof(PLColor)))==NULL)
    {
        plexit("c_plcpstrm: Insufficient memory");
    }

    for (i = 0; i < plsc->ncol0; i++)
        pl_cpcolor(&plsc->cmap0[i], &plsr->cmap0[i]);

    /* cmap 1 */

    plsc->icol1 = plsr->icol1;
    plsc->ncol1 = plsr->ncol1;
    if (plsc->cmap1 != NULL)
        free((void *) plsc->cmap1);

    if ((plsc->cmap1 = (PLColor *) calloc(1, plsc->ncol1 * sizeof(PLColor)))==NULL)
    {
        plexit("c_plcpstrm: Insufficient memory");
    }

    for (i = 0; i < plsc->ncol1; i++)
        pl_cpcolor(&plsc->cmap1[i], &plsr->cmap1[i]);

    /* Initialize if it hasn't been done yet. */

    if (plsc->level == 0)
        plinit();
}

/*--------------------------------------------------------------------------*\
 * pllib_devinit()
 *
 * Does preliminary setup of device driver.
 *
 * This function (previously plGetDev) used to be what is now shown as
 * plSelectDev below.  However, the situation is a bit more complicated now in
 * the dynloadable drivers era.  We now have to:
 *
 * 1) Make sure the dispatch table is initialized to the union of static
 *    drivers and available dynamic drivers (done from pllib_init now).
 * 2) Allow the user to select the desired device.
 * 3) Initialize the dispatch table entries for the selected device, in the
 *    case that it is a dynloadable driver that has not yet been loaded.
 *
 * Also made non-static, in order to allow some device calls to be made prior
 * to calling plinit().  E.g. plframe needs to tell the X driver to create its
 * internal data structure during widget construction time (using the escape
 * function), but doesn't call plinit() until the plframe is actually mapped.
\*--------------------------------------------------------------------------*/

void
pllib_devinit()
{
    if (plsc->dev_initialized) return;
    plsc->dev_initialized = 1;
    plSelectDev();
    plLoadDriver();
    /* offset by one since table is zero-based, but input list is not */
    plsc->dispatch_table = dispatch_table[plsc->device - 1];
}

PLDLLIMPEXP int plInBuildTree()
{
    static int inited = 0;
    static int inBuildTree = 0;

    if (inited == 0)
    {
        char currdir[PLPLOT_MAX_PATH];
        char builddir[PLPLOT_MAX_PATH];

        if (getcwd(currdir, PLPLOT_MAX_PATH) == NULL)
        {
            pldebug("plInBuildTree():", "Not enough buffer space");
        }
        else
        {
            /* The chdir / getcwd call is to ensure we get the physical
             * path without any symlinks */
            /* Ignore error in chdir - build tree may not exist */
            if (chdir(BUILD_DIR) == 0)
            {
                if (getcwd(builddir, PLPLOT_MAX_PATH) == NULL)
                {
                    pldebug("plInBuildTree():", "Not enough buffer space");
                }
                else
                {
                    if (strncmp(builddir, currdir, strlen(builddir)) == 0)
                    {
                        inBuildTree = 1;
                    }
                }
                if (chdir(currdir) != 0)
                    pldebug("plInBuildTree():", "Unable to chdir to current directory");
            }
        }
        inited = 1;
    }
    return inBuildTree;
}

#ifdef ENABLE_DYNDRIVERS

char*
plGetDrvDir ()
{
    char* drvdir;

    /* Get drivers directory in PLPLOT_DRV_DIR or DRV_DIR,
     *  on this order
     */

    if (plInBuildTree() == 1)
    {
        drvdir = BUILD_DIR "\\drivers";
        pldebug("plGetDrvDir", "Using %s as the driver directory.\n", drvdir);
    }
    else
    {
        pldebug("plGetDrvDir", "Trying to read env var PLPLOT_DRV_DIR\n");
        drvdir = getenv ("PLPLOT_DRV_DIR");

        if (drvdir == NULL)
        {
            pldebug("plGetDrvDir",
                    "Will use drivers dir: " DRV_DIR "\n");
            drvdir = DRV_DIR;
        }
    }

    return drvdir;
}

#endif


/*--------------------------------------------------------------------------*\
 * void plInitDispatchTable()
 *
 * ...
\*--------------------------------------------------------------------------*/

static int plDispatchSequencer( const void *p1, const void *p2 )
{
    const PLDispatchTable* t1 = *(PLDispatchTable **) p1;
    const PLDispatchTable* t2 = *(PLDispatchTable **) p2;

    /*     printf( "sorting: t1.name=%s t1.seq=%d t2.name=%s t2.seq=%d\n", */
    /*             t1->pl_DevName, t1->pl_seq, t2->pl_DevName, t2->pl_seq ); */

    return t1->pl_seq - t2->pl_seq;
}

static void
plInitDispatchTable()
{
    int n;

#ifdef ENABLE_DYNDRIVERS
    char buf[BUFFER2_SIZE];
    char* drvdir;
    char *devnam, *devdesc, *devtype, *driver, *tag, *seqstr;
    int seq;
    int i, j, driver_found, done=0;
    FILE *fp_drvdb = NULL;
    DIR* dp_drvdir = NULL;
    struct dirent* entry;
    /* lt_dlhandle dlhand; */

    /* Make sure driver counts are zeroed */
    npldynamicdevices = 0;
    nloadabledrivers = 0;

    /* Open a temporary file in which all the plD_DEVICE_INFO_<driver> strings
       will be stored */
    fp_drvdb = tmpfile();

    /* Open the drivers directory */
    drvdir = plGetDrvDir ();
    dp_drvdir = opendir (drvdir);
    if (dp_drvdir == NULL)
    {
        plabort ("plInitDispatchTable: Could not open drivers directory");
        return;
    }

    /* Loop over each entry in the drivers directory */

    pldebug ("plInitDispatchTable", "Scanning dyndrivers dir\n");
    while ((entry = readdir (dp_drvdir)) != NULL)
    {
        char* name = entry->d_name;
        int len = strlen (name) - 3;

        pldebug ("plInitDispatchTable",
                 "Consider file %s\n", name);

        /* Only consider entries that have the ".rc" suffix */
        if ((len > 0) && (strcmp (name + len, ".rc") == 0))
        {
            char path[PLPLOT_MAX_PATH];
            FILE* fd;

            /* Open the driver's info file */
            snprintf (path, PLPLOT_MAX_PATH, "%s/%s", drvdir, name);
            fd = fopen (path, "r");
            if (fd == NULL)
            {
                snprintf (buf, BUFFER2_SIZE,
                          "plInitDispatchTable: Could not open driver info file %s\n",
                          name);
                plabort (buf);
                return;
            }

            /* Each line in the <driver>.rc file corresponds to a specific device.
             * Write it to the drivers db file and take care of leading newline
             * character */

            pldebug ("plInitDispatchTable",
                     "Opened driver info file %s\n", name);

            while (fgets (buf, BUFFER2_SIZE, fd) != NULL)
            {
                fprintf (fp_drvdb, "%s", buf);

                if ( buf [strlen (buf) - 1] != '\n' )
                    fprintf (fp_drvdb, "\n");

                npldynamicdevices++;
            }
            fclose (fd);
        }
    }

    /* Make sure that the temporary file containing the driversr database
     * is ready to read and close the directory handle */
    fflush (fp_drvdb);
    closedir (dp_drvdir);

#endif

    /* Allocate space for the dispatch table. */
    if ((dispatch_table = (PLDispatchTable **)
                          malloc( (nplstaticdevices + npldynamicdevices) * sizeof(PLDispatchTable *) ))==NULL)
    {
        plexit("plInitDispatchTable: Insufficient memory");
    }

    /* Initialize the dispatch table entries for the static devices by calling
       the dispatch table initialization function for each static device.  This
       is the same function that would be called at load time for dynamic
       drivers. */

    for ( n=0; n < nplstaticdevices; n++ )
    {
        if ((dispatch_table[n] = (PLDispatchTable *)malloc( sizeof(PLDispatchTable) ))==NULL)
        {
            plexit("plInitDispatchTable: Insufficient memory");
        }

        (*static_device_initializers[n])( dispatch_table[n] );
    }
    npldrivers = nplstaticdevices;

#ifdef ENABLE_DYNDRIVERS

    /* Allocate space for the device and driver specs.  We may not use all of
     * these driver descriptors, but we obviously won't need more drivers than
     * devices... */
    if (((loadable_device_list = malloc( npldynamicdevices * sizeof(PLLoadableDevice) ))==NULL)||
            ((loadable_driver_list = malloc( npldynamicdevices * sizeof(PLLoadableDriver) ))==NULL))
    {
        plexit("plInitDispatchTable: Insufficient memory");
    }

    rewind( fp_drvdb );

    i = 0;
    done = !(i < npldynamicdevices);
    while ( !done )
    {
        char *p = fgets( buf, BUFFER2_SIZE, fp_drvdb );

        if (p == 0)
        {
            done = 1;
            continue;
        }

        devnam  = strtok( buf, ":" );
        devdesc = strtok( 0, ":" );
        devtype = strtok( 0, ":" );
        driver  = strtok( 0, ":" );
        seqstr  = strtok( 0, ":" );
        tag     = strtok( 0, "\n" );

        seq     = atoi(seqstr);

        n = npldrivers++;

        if ((dispatch_table[n] = malloc( sizeof(PLDispatchTable) ))==NULL)
        {
            plexit("plInitDispatchTable: Insufficient memory");
        }

        /* Fill in the dispatch table entries. */
        dispatch_table[n]->pl_MenuStr = plstrdup(devdesc);
        dispatch_table[n]->pl_DevName = plstrdup(devnam);
        dispatch_table[n]->pl_type = atoi(devtype);
        dispatch_table[n]->pl_seq = seq;
        dispatch_table[n]->pl_init = 0;
        dispatch_table[n]->pl_line = 0;
        dispatch_table[n]->pl_polyline = 0;
        dispatch_table[n]->pl_eop = 0;
        dispatch_table[n]->pl_bop = 0;
        dispatch_table[n]->pl_tidy = 0;
        dispatch_table[n]->pl_state = 0;
        dispatch_table[n]->pl_esc = 0;

        /* Add a record to the loadable device list */
        loadable_device_list[i].devnam = plstrdup(devnam);
        loadable_device_list[i].description = plstrdup(devdesc);
        loadable_device_list[i].drvnam = plstrdup(driver);
        loadable_device_list[i].tag = plstrdup(tag);

        /* Now see if this driver has been seen before.  If not, add a driver
         * entry for it. */
        driver_found = 0;
        for ( j=0; j < nloadabledrivers; j++ )
            if (strcmp( driver, loadable_driver_list[j].drvnam) == 0)
            {
                driver_found = 1;
                break;
            }

        if (!driver_found)
        {
            loadable_driver_list[nloadabledrivers].drvnam = plstrdup(driver);
            loadable_driver_list[nloadabledrivers].dlhand = 0;
            nloadabledrivers++;
        }

        loadable_device_list[i].drvidx = j;

        /* Get ready for next loadable device spec */
        i++;
    }

    /* RML: close fp_drvdb */
    fclose (fp_drvdb);

#endif

    /* Finally, we need to sort the list into presentation order, based on the
       sequence number in the dispatch ttable entries. */

    qsort( dispatch_table, npldrivers, sizeof(PLDispatchTable*),
           plDispatchSequencer );
}

/*--------------------------------------------------------------------------*\
 * void plSelectDev()
 *
 * If the user has not already specified the output device, or the
 * one specified is either: (a) not available, (b) "?", or (c) NULL, the
 * user is prompted for it.
 *
 * Prompting quits after 10 unsuccessful tries in case the user has
 * run the program in the background with insufficient input.
\*--------------------------------------------------------------------------*/

static void
plSelectDev()
{
    int dev, i, count, length;
    char response[80];

    /* Device name already specified.  See if it is valid. */

    if (*(plsc->DevName) != '\0' && *(plsc->DevName) != '?')
    {
        length = strlen(plsc->DevName);

        for (i = 0; i < npldrivers; i++)
        {
            if ((*plsc->DevName == *dispatch_table[i]->pl_DevName) &&
                    (strncmp(plsc->DevName,
                             dispatch_table[i]->pl_DevName, length) == 0))
                break;
        }

        if (i < npldrivers)
        {
            plsc->device = i + 1;
            return;
        }
        else
        {
            fprintf(stderr, "Requested device %s not available\n",
                    plsc->DevName);
        }
    }

    dev = 0;
    count = 0;

    if (npldrivers == 1)
        dev = 1;

    /* User hasn't specified it correctly yet, so we prompt */

    while (dev < 1 || dev > npldrivers)
    {
        fprintf(stdout, "\nPlotting Options:\n");
        for (i = 0; i < npldrivers; i++)
        {
            fprintf(stdout, " <%2d> %-10s %s\n", i + 1,
                    dispatch_table[i]->pl_DevName,
                    dispatch_table[i]->pl_MenuStr);
        }
        if (ipls == 0)
            fprintf(stdout, "\nEnter device number or keyword: ");
        else
            fprintf(stdout, "\nEnter device number or keyword (stream %d): ",
                    (int) ipls);

        plio_fgets(response, sizeof(response), stdin);

        /* First check to see if device keyword was entered. */
        /* Final "\n" in response messes things up, so ignore it.  */

        length = strlen(response);
        if (*(response - 1 + length) == '\n')
            length--;

        for (i = 0; i < npldrivers; i++)
        {
            if ( ! strncmp(response, dispatch_table[i]->pl_DevName,
                           (unsigned int) length))
                break;
        }
        if (i < npldrivers)
        {
            dev = i + 1;
        }
        else
        {
            if ((dev = atoi(response)) < 1)
            {
                fprintf(stdout, "\nInvalid device: %s", response);
                dev = 0;
            }
        }
        if (count++ > 10)
        {
            plexit("plSelectDev: Too many tries.");
        }
    }
    plsc->device = dev;
    strcpy(plsc->DevName, dispatch_table[dev - 1]->pl_DevName);
}

/*--------------------------------------------------------------------------*\
 * void plLoadDriver()
 *
 * Make sure the selected driver is loaded.  Static drivers are already
 * loaded, but if the user selected a dynamically loadable driver, we may
 * have to take care of that now.
\*--------------------------------------------------------------------------*/

static void
plLoadDriver(void)
{
#ifdef ENABLE_DYNDRIVERS
    int i, drvidx;
    char sym[BUFFER_SIZE];
    char *tag;

    int n=plsc->device - 1;
    PLDispatchTable *dev = dispatch_table[n];
    PLLoadableDriver *driver = 0;

    /* If the dispatch table is already filled in, then either the device was
     * linked in statically, or else perhaps it was already loaded.  In either
     * case, we have nothing left to do. */
    if (dev->pl_init)
        return;

    pldebug("plLoadDriver", "Device not loaded!\n");

    /* Now search through the list of loadable devices, looking for the record
     * that corresponds to the requested device. */
    for ( i=0; i < npldynamicdevices; i++ )
        if (strcmp( dev->pl_DevName, loadable_device_list[i].devnam ) == 0)
            break;

    /* If we couldn't find such a record, then there is some sort of internal
     * logic flaw since plSelectDev is supposed to only select a valid device.
     */
    if (i == npldynamicdevices)
    {
        fprintf( stderr, "No such device: %s.\n", dev->pl_DevName );
        plexit("plLoadDriver detected device logic screwup");
    }

    /* Note the device tag, and the driver index. Note that a given driver could
     * supply multiple devices, each with a unique tag to distinguish the driver
     * entry points for the differnet supported devices. */
    tag = loadable_device_list[i].tag;
    drvidx = loadable_device_list[i].drvidx;

    pldebug("plLoadDriver", "tag=%s, drvidx=%d\n", tag, drvidx );

    driver = &loadable_driver_list[drvidx];

    /* Load the driver if it hasn't been loaded yet. */
    if (!driver->dlhand)
    {
        char drvspec[ DRVSPEC_SIZE ];
#if defined(LTDL_WIN32) || defined(__CYGWIN__)
        snprintf( drvspec, DRVSPEC_SIZE, "%s", driver->drvnam );
#else
        snprintf( drvspec, DRVSPEC_SIZE, "%s/%s", plGetDrvDir (), driver->drvnam );
#endif /* LTDL_WIN32 */

        pldebug("plLoadDriver", "Trying to load %s on %s\n",
                driver->drvnam, drvspec );

        driver->dlhand = lt_dlopenext( drvspec);
    }

    /* If it still isn't loaded, then we're doomed. */
    if (!driver->dlhand)
    {
        pldebug("plLoadDriver", "lt_dlopenext failed because of "
                "the following reason:\n%s\n", lt_dlerror ());
        fprintf( stderr, "Unable to load driver: %s.\n", driver->drvnam );

        plexit("Unable to load driver");
    }

    /* Now we are ready to ask the driver's device dispatch init function to
       initialize the entries in the dispatch table. */

    snprintf( sym, BUFFER_SIZE, "plD_dispatch_init_%s", tag );
    {
        PLDispatchInit dispatch_init = (PLDispatchInit) lt_dlsym( driver->dlhand, sym );
        if (!dispatch_init)
        {
            fprintf( stderr,
                     "Unable to locate dispatch table initialization function for driver: %s.\n",
                     driver->drvnam );
            return;
        }

        (*dispatch_init)( dev );
    }
#endif
}

/*--------------------------------------------------------------------------*\
 * void plfontld()
 *
 * Load specified font set.
\*--------------------------------------------------------------------------*/

void
c_plfontld(PLINT ifont)
{
    if (ifont != 0)
        ifont = 1;

    if (plsc->level > 0)
        plfntld(ifont);
    else
        initfont = ifont;
}

/*--------------------------------------------------------------------------*\
 * void plreplot()
 *
 * Replays contents of plot buffer to current device/file.
\*--------------------------------------------------------------------------*/

void
c_plreplot(void)
{
#ifdef BUFFERED_FILE
    if (plsc->plbufFile != NULL)
    {
#else
    if (plsc->plbuf_buffer != NULL)
    {
#endif
        plRemakePlot(plsc);
    }
    else
    {
        plwarn("plreplot: plot buffer not available");
    }
}

/*--------------------------------------------------------------------------*\
 * void plgFileDevs()
 *
 * Returns a list of file-oriented device names and their menu strings,
 * for use in a graphical interface.  The caller must allocate enough
 * space for (*p_menustr) and (*p_devname) to hold a pointer for each
 * device -- 20 or so is plenty.  E.g. char *menustr[20].  The size of
 * these arrays should be passed in *p_ndev, which, on exit, holds the
 * number of devices actually present.
\*--------------------------------------------------------------------------*/

void
plgFileDevs(const char ***p_menustr, const char ***p_devname, int *p_ndev)
{
    plgdevlst(*p_menustr, *p_devname, p_ndev, 0);
}

/*--------------------------------------------------------------------------*\
 * void plgDevs()
 *
 * Like plgFileDevs(), but returns names and menu strings for all devices.
\*--------------------------------------------------------------------------*/

void
plgDevs(const char ***p_menustr, const char ***p_devname, int *p_ndev)
{
    plgdevlst(*p_menustr, *p_devname, p_ndev, -1);
}

static void
plgdevlst(const char **p_menustr, const char **p_devname, int *p_ndev, int type)
{
    int i, j;

    pllib_init();

    for (i = j = 0; i < npldrivers; i++)
    {
        if (type < 0 || dispatch_table[i]->pl_type == type)
        {
            p_menustr[j] = dispatch_table[i]->pl_MenuStr;
            p_devname[j] = dispatch_table[i]->pl_DevName;
            if (++j + 1 >= *p_ndev)
            {
                plwarn("plgdevlst:  too many devices");
                break;
            }
        }
    }
    p_menustr[j] = NULL;
    p_devname[j] = NULL;
    *p_ndev = j;
}

/*--------------------------------------------------------------------------*\
 *  Various external access routines.
\*--------------------------------------------------------------------------*/

/* Get output device parameters. */

void
c_plgpage(PLFLT *p_xp, PLFLT *p_yp,
          PLINT *p_xleng, PLINT *p_yleng, PLINT *p_xoff, PLINT *p_yoff)
{
    *p_xp = plsc->xdpi;
    *p_yp = plsc->ydpi;
    *p_xleng = plsc->xlength;
    *p_yleng = plsc->ylength;
    *p_xoff = plsc->xoffset;
    *p_yoff = plsc->yoffset;
}

/* Set output device parameters.  Usually ignored by the driver. */

void
c_plspage(PLFLT xp, PLFLT yp, PLINT xleng, PLINT yleng, PLINT xoff, PLINT yoff)
{
    if (plsc->level > 0)
        plwarn("calling plspage() after plinit() may give unpredictable results");

    if (xp)
        plsc->xdpi = xp;
    if (yp)
        plsc->ydpi = yp;

    if (xleng)
        plsc->xlength = xleng;
    if (yleng)
        plsc->ylength = yleng;

    if (xoff)
        plsc->xoffset = xoff;
    if (yoff)
        plsc->yoffset = yoff;

    plsc->pageset = 1;
}

/* Set the number of subwindows in x and y */

void
c_plssub(PLINT nx, PLINT ny)
{
    if (nx > 0)
        plsc->nsubx = nx;
    if (ny > 0)
        plsc->nsuby = ny;

    /* Force a page advance */

    if (plsc->level > 0)
    {
        plP_subpInit();
        /*AWI	plP_eop();
        	plP_bop();*/
    }
}

/* Set the device (keyword) name */

void
c_plsdev(const char *devname)
{
    if (plsc->level > 0)
    {
        plwarn("plsdev: Must be called before plinit.");
        return;
    }
    if (devname != NULL)
    {
        strncpy(plsc->DevName, devname, sizeof(plsc->DevName) - 1);
        plsc->DevName[sizeof(plsc->DevName) - 1] = '\0';
    }
}

/* Get the current device (keyword) name */
/* Note: you MUST have allocated space for this (80 characters is safe) */

void
c_plgdev(char *p_dev)
{
    strcpy(p_dev, plsc->DevName);
}

/* Set the memory area to be plotted (with the 'mem' driver) as the 'dev'
   member of the stream structure.  Also set the number
   of pixels in the memory passed in in 'plotmem'.
   Plotmem is a block of memory maxy by maxx by 3 bytes long, say:
   480 x 640 x 3 (Y, X, RGB)

   This memory will be freed by the user!
*/

void
c_plsmem(PLINT maxx, PLINT maxy, void *plotmem)
{
    plsc->dev = plotmem;
    plP_setphy (0, maxx, 0, maxy);
}

/* Get the current stream pointer */

void
plgpls(PLStream **p_pls)
{
    *p_pls = plsc;
}

/* Get the (current) run level.
 * Valid settings are:
 *   0	uninitialized
 *   1	initialized
 *   2	viewport defined
 *   3	world coords defined
 */

void
c_plglevel(PLINT *p_level)
{
    *p_level = plsc->level;
}

/* Set the function pointer for the keyboard event handler */

void
plsKeyEH(void (*KeyEH) (PLGraphicsIn *, void *, int *),
         void *KeyEH_data)
{
    plsc->KeyEH = KeyEH;
    plsc->KeyEH_data = KeyEH_data;
}

/* Set the function pointer for the (mouse) button event handler */

void
plsButtonEH(void (*ButtonEH) (PLGraphicsIn *, void *, int *),
            void *ButtonEH_data)
{
    plsc->ButtonEH = ButtonEH;
    plsc->ButtonEH_data = ButtonEH_data;
}

/* Sets an optional user bop handler. */

void
plsbopH(void (*handler) (void *, int *), void *handler_data)
{
    plsc->bop_handler = handler;
    plsc->bop_data = handler_data;
}

/* Sets an optional user eop handler. */

void
plseopH(void (*handler) (void *, int *), void *handler_data)
{
    plsc->eop_handler = handler;
    plsc->eop_data = handler_data;
}

/* Set the variables to be used for storing error info */

void
plsError(PLINT *errcode, char *errmsg)
{
    if (errcode != NULL)
        plsc->errcode = errcode;

    if (errmsg != NULL)
        plsc->errmsg = errmsg;
}

/* Set orientation.  Must be done before calling plinit. */

void
c_plsori(PLINT ori)
{
    plsdiori((PLFLT) ori);
}

/*
 * Set pen width.  Can be done any time, but before calling plinit is best
 * since otherwise it may be volatile (i.e. reset on next page advance).
 * If width < 0 or is unchanged by the call, nothing is done.
 */

void
c_plwid(PLINT width)
{
    if (width != plsc->width && width >= 0)
    {
        plsc->width = width;

        if (plsc->level > 0)
        {
            if ( ! plsc->widthlock)
                plP_state(PLSTATE_WIDTH);
        }
    }
}

/* Set the output file pointer */

void
plgfile(FILE **p_file)
{
    *p_file = plsc->OutFile;
}

/* Get the output file pointer */

void
plsfile(FILE *file)
{
    plsc->OutFile = file;
}

/* Get the (current) output file name.  Must be preallocated to >=80 bytes */
/* Beyond that, I truncate it.  You have been warned. */

void
c_plgfnam(char *fnam)
{
    if (fnam == NULL)
    {
        plabort("filename string must be preallocated to >=80 bytes");
        return;
    }

    *fnam = '\0';
    if (plsc->FileName != NULL)
    {
        strncpy(fnam, plsc->FileName, 79);
        fnam[79] = '\0';
    }
}

/* Set the output file name. */

void
c_plsfnam(const char *fnam)
{
    plP_sfnam(plsc, fnam);
}

/* Set the pause (on end-of-page) status */

void
c_plspause(PLINT pause)
{
    plsc->nopause = ! pause;
}

/* Set the floating point precision (in number of places) in numeric labels. */

void
c_plprec(PLINT setp, PLINT prec)
{
    plsc->setpre = setp;
    plsc->precis = prec;
}

/* Get the floating point precision (in number of places) in numeric labels. */

void
plP_gprec(PLINT *p_setp, PLINT *p_prec)
{
    *p_setp = plsc->setpre;
    *p_prec = plsc->precis;
}

const char *
plP_gtimefmt()
{
    return (const char *) plsc->timefmt;
}

/*
 * Set the escape character for text strings.
 * From C you can pass as a character, from Fortran it needs to be the decimal
 * ASCII value.  Only selected characters are allowed to prevent the user from
 * shooting himself in the foot (a '\' isn't allowed since it conflicts with
 * C's use of backslash as a character escape).
 */

void
c_plsesc(char esc)
{
    switch (esc)
    {
    case '!':		/* ASCII 33 */
    case '#':		/* ASCII 35 */
    case '$':		/* ASCII 36 */
    case '%':		/* ASCII 37 */
    case '&':		/* ASCII 38 */
    case '*':		/* ASCII 42 */
    case '@':		/* ASCII 64 */
    case '^':		/* ASCII 94 */
    case '~':		/* ASCII 126 */
        plsc->esc = esc;
        break;

    default:
        plwarn("plsesc: Invalid escape character, ignoring.");
    }
}

/* Get the escape character for text strings. */

void
plgesc(char *p_esc)
{
    if (plsc->esc == '\0')
        plsc->esc = '#';

    *p_esc = plsc->esc;
}

/* Set the FCI (font characterization integer) for unicode-enabled device
 * drivers.
 */
void
c_plsfci(PLUNICODE fci)
{
    /* Always mark FCI as such. */
    plsc->fci = fci | PL_FCI_MARK;
}

/* Get the FCI (font characterization integer) for unicode-enabled device
 * drivers.
 */
void
c_plgfci(PLUNICODE *pfci)
{
    /* Always mark FCI as such. */
    *pfci = plsc->fci | PL_FCI_MARK;
}
/* Store hex digit value shifted to the left by hexdigit hexadecimal digits
 * into pre-existing FCI.
 */
void
plP_hex2fci(unsigned char hexdigit, unsigned char hexpower, PLUNICODE *pfci)
{
    PLUNICODE mask;
    hexpower = hexpower & PL_FCI_HEXPOWER_MASK;
    mask = ~ (((PLUNICODE) PL_FCI_HEXDIGIT_MASK) << ((PLUNICODE) 4*hexpower));
    *pfci = *pfci & mask;
    mask = (((PLUNICODE) (hexdigit & PL_FCI_HEXDIGIT_MASK)) << (4*hexpower));
    *pfci = *pfci | mask;
}

/* Retrieve hex digit value from FCI that is masked out and shifted to the
 * right by hexpower hexadecimal digits. */
void
plP_fci2hex(PLUNICODE fci, unsigned char *phexdigit, unsigned char hexpower)
{
    PLUNICODE mask;
    hexpower = hexpower & PL_FCI_HEXPOWER_MASK;
    mask = (((PLUNICODE) PL_FCI_HEXPOWER_MASK) << ((PLUNICODE) (4*hexpower)));
    *phexdigit = (unsigned char) ((fci & mask) >>
                                  ((PLUNICODE) (4*hexpower)));
}

/* Get the current library version number */
/* Note: you MUST have allocated space for this (80 characters is safe) */
void
c_plgver(char *p_ver)
{
    strcpy(p_ver, VERSION);
}

/* Set inferior X window */

void
plsxwin(PLINT window_id)
{
    plsc->window_id = window_id;
}

/*--------------------------------------------------------------------------*\
 *  These set/get information for family files, and may be called prior
 *  to plinit to set up the necessary parameters.  Arguments:
 *
 *	fam	familying flag (boolean)
 *	num	member number
 *	bmax	maximum member size
\*--------------------------------------------------------------------------*/

/* Get family file parameters */

void
c_plgfam(PLINT *p_fam, PLINT *p_num, PLINT *p_bmax)
{
    *p_fam = plsc->family;
    *p_num = plsc->member;
    *p_bmax = plsc->bytemax;
}

/* Set family file parameters */

void
c_plsfam(PLINT fam, PLINT num, PLINT bmax)
{
    if (plsc->level > 0)
        plwarn("plsfam: Must be called before plinit.");

    if (fam >= 0)
        plsc->family = fam;
    if (num >= 0)
        plsc->member = num;
    if (bmax >= 0)
        plsc->bytemax = bmax;
}

/* Advance to the next family file on the next new page */

void
c_plfamadv(void)
{
    plsc->famadv = 1;
}

/*--------------------------------------------------------------------------*\
 *  Interface routines for axis labling parameters.
 *  See pldtik.c for more info.
\*--------------------------------------------------------------------------*/

/* Get x axis labeling parameters */

void
c_plgxax(PLINT *p_digmax, PLINT *p_digits)
{
    *p_digmax = plsc->xdigmax;
    *p_digits = plsc->xdigits;
}

/* Set x axis labeling parameters */

void
c_plsxax(PLINT digmax, PLINT digits)
{
    plsc->xdigmax = digmax;
    plsc->xdigits = digits;
}

/* Get y axis labeling parameters */

void
c_plgyax(PLINT *p_digmax, PLINT *p_digits)
{
    *p_digmax = plsc->ydigmax;
    *p_digits = plsc->ydigits;
}

/* Set y axis labeling parameters */

void
c_plsyax(PLINT digmax, PLINT digits)
{
    plsc->ydigmax = digmax;
    plsc->ydigits = digits;
}

/* Get z axis labeling parameters */

void
c_plgzax(PLINT *p_digmax, PLINT *p_digits)
{
    *p_digmax = plsc->zdigmax;
    *p_digits = plsc->zdigits;
}

/* Set z axis labeling parameters */

void
c_plszax(PLINT digmax, PLINT digits)
{
    plsc->zdigmax = digmax;
    plsc->zdigits = digits;
}

/* Get character default height and current (scaled) height */

void
c_plgchr(PLFLT *p_def, PLFLT *p_ht)
{
    *p_def = plsc->chrdef;
    *p_ht = plsc->chrht;
}

/* Get viewport boundaries in normalized device coordinates */

void
c_plgvpd(PLFLT *p_xmin, PLFLT *p_xmax, PLFLT *p_ymin, PLFLT *p_ymax)
{
    *p_xmin = plsc->vpdxmi;
    *p_xmax = plsc->vpdxma;
    *p_ymin = plsc->vpdymi;
    *p_ymax = plsc->vpdyma;
}

/* Get viewport boundaries in world coordinates */

void
c_plgvpw(PLFLT *p_xmin, PLFLT *p_xmax, PLFLT *p_ymin, PLFLT *p_ymax)
{
    *p_xmin = plsc->vpwxmi;
    *p_xmax = plsc->vpwxma;
    *p_ymin = plsc->vpwymi;
    *p_ymax = plsc->vpwyma;
}

/* Get the viewport boundaries in world coordinates, expanded slightly */
void
plP_xgvpw(PLFLT *p_xmin, PLFLT *p_xmax, PLFLT *p_ymin, PLFLT *p_ymax)
{
    PLFLT dx, dy;

    dx = (plsc->vpwxma - plsc->vpwxmi) * 1.0e-5;
    dy = (plsc->vpwyma - plsc->vpwymi) * 1.0e-5;

    /* The plot window is made slightly larger than requested so that */
    /* the end limits will be on the graph  */

    *p_xmin = plsc->vpwxmi - dx;
    *p_xmax = plsc->vpwxma + dx;
    *p_ymin = plsc->vpwymi - dy;
    *p_ymax = plsc->vpwyma + dy;
}

/*--------------------------------------------------------------------------*\
 *  These should not be called by the user.
\*--------------------------------------------------------------------------*/

/* Get x-y domain in world coordinates for 3d plots */

void
plP_gdom(PLFLT *p_xmin, PLFLT *p_xmax, PLFLT *p_ymin, PLFLT *p_ymax)
{
    *p_xmin = plsc->domxmi;
    *p_xmax = plsc->domxma;
    *p_ymin = plsc->domymi;
    *p_ymax = plsc->domyma;
}

/* Get vertical (z) scale parameters for 3-d plot */

void
plP_grange(PLFLT *p_zscl, PLFLT *p_zmin, PLFLT *p_zmax)
{
    *p_zscl = plsc->zzscl;
    *p_zmin = plsc->ranmi;
    *p_zmax = plsc->ranma;
}

/* Get parameters used in 3d plots */

void
plP_gw3wc(PLFLT *p_dxx, PLFLT *p_dxy, PLFLT *p_dyx, PLFLT *p_dyy, PLFLT *p_dyz)
{
    *p_dxx = plsc->cxx;
    *p_dxy = plsc->cxy;
    *p_dyx = plsc->cyx;
    *p_dyy = plsc->cyy;
    *p_dyz = plsc->cyz;
}

/* Get clip boundaries in physical coordinates */

void
plP_gclp(PLINT *p_ixmin, PLINT *p_ixmax, PLINT *p_iymin, PLINT *p_iymax)
{
    *p_ixmin = plsc->clpxmi;
    *p_ixmax = plsc->clpxma;
    *p_iymin = plsc->clpymi;
    *p_iymax = plsc->clpyma;
}

/* Set clip boundaries in physical coordinates */

void
plP_sclp(PLINT ixmin, PLINT ixmax, PLINT iymin, PLINT iymax)
{
    plsc->clpxmi = ixmin;
    plsc->clpxma = ixmax;
    plsc->clpymi = iymin;
    plsc->clpyma = iymax;
}

/* Get physical device limits in physical coordinates */

void
plP_gphy(PLINT *p_ixmin, PLINT *p_ixmax, PLINT *p_iymin, PLINT *p_iymax)
{
    *p_ixmin = plsc->phyxmi;
    *p_ixmax = plsc->phyxma;
    *p_iymin = plsc->phyymi;
    *p_iymax = plsc->phyyma;
}

/* Get number of subpages on physical device and current subpage */

void
plP_gsub(PLINT *p_nx, PLINT *p_ny, PLINT *p_cs)
{
    *p_nx = plsc->nsubx;
    *p_ny = plsc->nsuby;
    *p_cs = plsc->cursub;
}

/* Set number of subpages on physical device and current subpage */

void
plP_ssub(PLINT nx, PLINT ny, PLINT cs)
{
    plsc->nsubx = nx;
    plsc->nsuby = ny;
    plsc->cursub = cs;
}

/* Get number of pixels to a millimeter */

void
plP_gpixmm(PLFLT *p_x, PLFLT *p_y)
{
    *p_x = plsc->xpmm;
    *p_y = plsc->ypmm;
}

/* All the drivers call this to set physical pixels/mm. */

void
plP_setpxl(PLFLT xpmm, PLFLT ypmm)
{
    plsc->xpmm = xpmm;
    plsc->ypmm = ypmm;
    plsc->umx = (PLINT)(1000.0 / plsc->xpmm);
    plsc->umy = (PLINT)(1000.0 / plsc->ypmm);
}

/* Sets up physical limits of plotting device. */

void
plP_setphy(PLINT xmin, PLINT xmax, PLINT ymin, PLINT ymax)
{
    if (xmin > xmax || ymin > ymax)
        plexit("plP_setphy: device minima must not exceed maxima");

    plsc->phyxmi = xmin;
    plsc->phyxma = xmax;
    plsc->phyymi = ymin;
    plsc->phyyma = ymax;
    plsc->phyxlen = xmax - xmin;
    plsc->phyylen = ymax - ymin;
}

/*--------------------------------------------------------------------------*\
 * void c_plscompression()
 *
 * Set compression.
 * Has to be done before plinit.
\*--------------------------------------------------------------------------*/

void
c_plscompression(PLINT compression)
{
    if (plsc->level <= 0)
    {
        plsc->dev_compression=compression;
    }
}

/*--------------------------------------------------------------------------*\
 * void c_plgcompression()
 *
 * Get compression
\*--------------------------------------------------------------------------*/

void
c_plgcompression(PLINT *compression)
{
    *compression = plsc->dev_compression;
}


/*--------------------------------------------------------------------------*\
 * void plP_getinitdriverlist()
 *
 * Check to see if a driver/stream has been initialised
 * Returns a space separated list of matches streams/drivers
 * If more than one stream uses the same device, then the device name
 * will be returned for each stream.
 * Caller must allocate enough memory for "names" to hold the answer.
\*--------------------------------------------------------------------------*/

void
plP_getinitdriverlist(char *names)
{
    int i;

    for (i=0;i<PL_NSTREAMS;++i)
    {
        if (pls[i]!=NULL)
        {
            if (i==0)
                strcpy(names,pls[i]->DevName);
            else
            {
                strcat(names," ");
                strcat(names,pls[i]->DevName);
            }
        }
        else
            break;
    }
}


/*--------------------------------------------------------------------------*\
 * PLINT plP_checkdriverinit()
 *
 * Checks from a list of given drivers which ones have been initialised
 * and returns the number of devices matching the list, or -1 if in error.
 * Effectively returns the number of streams matching the given stream.
\*--------------------------------------------------------------------------*/

PLINT plP_checkdriverinit( char *names)
{
    char *buff;
    char *tok=NULL;
    PLINT ret=0;   /* set up return code to 0, the value if no devices match*/

    buff=(char *)malloc((size_t) PL_NSTREAMS*8); /* Allocate enough memory for 8
                                                characters for each possible stream */

    if (buff!=NULL)
    {
        memset(buff,0,PL_NSTREAMS*8);    /* Make sure we clear it               */
        plP_getinitdriverlist(buff);     /* Get the list of initialised devices */

        for (tok = strtok(buff, " ,");   /* Check each device against the "name" */
                tok; tok=strtok(0, " ,"))   /* supplied to the subroutine   */
        {
            if (strstr(names,tok)!=NULL)  /* Check to see if the device has been initialised */
            {
                ret++;                   /* Bump the return code if it has      */
            }
        }
        free(buff);                      /* Clear up that memory we allocated   */
    }
    else
        ret=-1;                           /* Error flag */

    return(ret);
}


/*--------------------------------------------------------------------------*\
 * plP_image
 *
 * Author: Alessandro Mirone, Nov 2001
 *
 * Updated by Hezekiah Carty, Mar 2008.
 *   - Added support for pltr callback
 *   - Commented out the "dev_fastimg" rendering path
 *
\*--------------------------------------------------------------------------*/

void
plP_image(PLFLT *z , PLINT nx, PLINT ny, PLFLT xmin, PLFLT ymin, PLFLT dx, PLFLT dy,
          void (*pltr) (PLFLT, PLFLT, PLFLT *, PLFLT *, PLPointer), PLPointer pltr_data)
{
    plsc->page_status = DRAWING;

    plimageslow(z, nx, ny, xmin, ymin, dx, dy, pltr, pltr_data);

    /*
     * COMMENTED OUT by Hezekiah Carty, March 2008
     * The current dev_fastimg rendering method does not work as-is with
     * the plimagefr coordinate transform support.
     * This is hopefully temporary, until the dev_fastimg rendering
     * path can be updated to work with the new plimage internals.
     * Until then, all plimage* rendering is done by the plimageslow
     * rendering path.
     */
#if 0   /* BEGIN dev_fastimg COMMENT */
    PLINT i, npts;
    short *xscl, *yscl;
    int   plbuf_write;

    plsc->page_status = DRAWING;

    if (plsc->dev_fastimg == 0)
    {
        plimageslow(x, y, z, nx-1, ny-1,
                    xmin, ymin, dx, dy, zmin, zmax);
        return ;
    }

    if (plsc->plbuf_write)
    {
        IMG_DT img_dt;

        img_dt.xmin=xmin;
        img_dt.ymin=ymin;
        img_dt.dx=dx;
        img_dt.dy=dy;

        plsc->dev_ix = x;
        plsc->dev_iy = y;
        plsc->dev_z = z;
        plsc->dev_nptsX = nx;
        plsc->dev_nptsY = ny;
        plsc->dev_zmin = zmin;
        plsc->dev_zmax = zmax;

        plbuf_esc(plsc, PLESC_IMAGE, &img_dt);
    }

    /* avoid re-saving plot buffer while in plP_esc() */
    plbuf_write = plsc->plbuf_write;
    plsc->plbuf_write = 0;

    npts = nx*ny;
    if (plsc->difilt)   /* isn't this odd? when replaying the plot buffer, e.g., when resizing the window, difilt() is caled again! the plot buffer should already contain the transformed data--it would save a lot of time! (and allow for differently oriented plots when in multiplot mode) */
    {
        PLINT clpxmi, clpxma, clpymi, clpyma;

        if (((xscl = (short *) malloc(nx*ny*sizeof(short)))==NULL)||
                ((yscl = (short *) malloc(nx*ny*sizeof(short)))==NULL))
        {
            plexit("plP_image: Insufficient memory");
        }

        for (i = 0; i < npts; i++)
        {
            xscl[i] = x[i];
            yscl[i] = y[i];
        }
        sdifilt(xscl, yscl, npts, &clpxmi, &clpxma, &clpymi, &clpyma);
        plsc->imclxmin = clpxmi;
        plsc->imclymin = clpymi;
        plsc->imclxmax = clpxma;
        plsc->imclymax = clpyma;
        grimage(xscl, yscl, z, nx, ny);
        free(xscl);
        free(yscl);
    }
    else
    {
        plsc->imclxmin = plsc->phyxmi;
        plsc->imclymin = plsc->phyymi;
        plsc->imclxmax = plsc->phyxma;
        plsc->imclymax = plsc->phyyma;
        grimage(x, y, z, nx, ny );
    }
    plsc->plbuf_write = plbuf_write;
#endif  /* END dev_fastimg COMMENT */
}
