/*
  This header file contains the lookup table used for converting between
  FCIs (font characterization integers) and font names for TrueType fonts.

  Copyright (C) 2005  Alan W. Irwin

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

/* N.B. When updating this table by hand be sure to keep it in 
 * ascending order in fci! 
 */
#define N_TrueTypeLookup 30
static const FCI_to_FontName_Table TrueTypeLookup[N_TrueTypeLookup] = {
     {PL_FCI_MARK | 0x000, (unsigned char *)PL_FREETYPE_SANS},
     {PL_FCI_MARK | 0x001, (unsigned char *)PL_FREETYPE_SERIF},
     {PL_FCI_MARK | 0x002, (unsigned char *)PL_FREETYPE_MONO},
     {PL_FCI_MARK | 0x003, (unsigned char *)PL_FREETYPE_SCRIPT},
     {PL_FCI_MARK | 0x004, (unsigned char *)PL_FREETYPE_SYMBOL},
     {PL_FCI_MARK | 0x010, (unsigned char *)PL_FREETYPE_SANS_ITALIC},
     {PL_FCI_MARK | 0x011, (unsigned char *)PL_FREETYPE_SERIF_ITALIC},
     {PL_FCI_MARK | 0x012, (unsigned char *)PL_FREETYPE_MONO_ITALIC},
     {PL_FCI_MARK | 0x013, (unsigned char *)PL_FREETYPE_SCRIPT_ITALIC},
     {PL_FCI_MARK | 0x014, (unsigned char *)PL_FREETYPE_SYMBOL_ITALIC},
     {PL_FCI_MARK | 0x020, (unsigned char *)PL_FREETYPE_SANS_OBLIQUE},
     {PL_FCI_MARK | 0x021, (unsigned char *)PL_FREETYPE_SERIF_OBLIQUE},
     {PL_FCI_MARK | 0x022, (unsigned char *)PL_FREETYPE_MONO_OBLIQUE},
     {PL_FCI_MARK | 0x023, (unsigned char *)PL_FREETYPE_SCRIPT_OBLIQUE},
     {PL_FCI_MARK | 0x024, (unsigned char *)PL_FREETYPE_SYMBOL_OBLIQUE},
     {PL_FCI_MARK | 0x100, (unsigned char *)PL_FREETYPE_SANS_BOLD},
     {PL_FCI_MARK | 0x101, (unsigned char *)PL_FREETYPE_SERIF_BOLD},
     {PL_FCI_MARK | 0x102, (unsigned char *)PL_FREETYPE_MONO_BOLD},
     {PL_FCI_MARK | 0x103, (unsigned char *)PL_FREETYPE_SCRIPT_BOLD},
     {PL_FCI_MARK | 0x104, (unsigned char *)PL_FREETYPE_SYMBOL_BOLD},
     {PL_FCI_MARK | 0x110, (unsigned char *)PL_FREETYPE_SANS_BOLD_ITALIC},
     {PL_FCI_MARK | 0x111, (unsigned char *)PL_FREETYPE_SERIF_BOLD_ITALIC},
     {PL_FCI_MARK | 0x112, (unsigned char *)PL_FREETYPE_MONO_BOLD_ITALIC},
     {PL_FCI_MARK | 0x113, (unsigned char *)PL_FREETYPE_SCRIPT_BOLD_ITALIC},
     {PL_FCI_MARK | 0x114, (unsigned char *)PL_FREETYPE_SYMBOL_BOLD_ITALIC},
     {PL_FCI_MARK | 0x120, (unsigned char *)PL_FREETYPE_SANS_BOLD_OBLIQUE},
     {PL_FCI_MARK | 0x121, (unsigned char *)PL_FREETYPE_SERIF_BOLD_OBLIQUE},
     {PL_FCI_MARK | 0x122, (unsigned char *)PL_FREETYPE_MONO_BOLD_OBLIQUE},
     {PL_FCI_MARK | 0x123, (unsigned char *)PL_FREETYPE_SCRIPT_BOLD_OBLIQUE},
     {PL_FCI_MARK | 0x124, (unsigned char *)PL_FREETYPE_SYMBOL_BOLD_OBLIQUE}
};
