/* $Id: wxPLplotstream.h.in 9619 2009-02-25 22:05:56Z smekal $

   Copyright (C) 2005  Werner Smekal

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

#if !defined( WXPLPLOTSTREAM_H__INCLUDED_ )
#define WXPLPLOTSTREAM_H__INCLUDED_

#include "plstream.h"

// forward declarations
class wxImage;
class wxDC;
  
// we define some macros, where the *name* of these depend on
// if freetype is available - in the code we have checks
// for the WX_TEMP_...._IS_ON macros (otherwise WX_TEMP_...._IS_OFF
// is defined)
#define WX_TEMP_HAVE_FREETYPE_IS_
  
/*! Style options for wxPLplotstream:
 *  wxPLPLOT_NONE: no option
 *  wxPLPLOT_FREETYPE: use freetype library instead of Hershey fonts
 *  wxPLPLOT_SMOOTHTEXT: antialiase font (if freetype library is used)
 *  wxPLPLOT_BACKEND_DC: use the standard wxDC backend (always available)
 *  wxPLPLOT_BACKEND_AGG: use the AGG backend (if available)
 *  wxPLPLOT_BACKEND_GC: use the wxGraphicsContext backend (if available)
 *  wxPLPLOT_DRAWTEXT: use wxWidgets routines to draw text
 *  wxPLPLOT_USE_HERSHEY_SYMBOLS: use hershey symbols to draw symbols instead of font symbols
 */
enum {
  wxPLPLOT_NONE                = 0,
#ifdef WX_TEMP_HAVE_FREETYPE_IS_ON
  wxPLPLOT_FREETYPE            = 1 << 0,
  wxPLPLOT_SMOOTH_TEXT         = 1 << 1,
#endif
  wxPLPLOT_BACKEND_DC          = 1 << 2,
  wxPLPLOT_BACKEND_AGG         = 1 << 3,
  wxPLPLOT_BACKEND_GC          = 1 << 4,
  wxPLPLOT_DRAW_TEXT           = 1 << 5,
  wxPLPLOT_USE_HERSHEY_SYMBOLS = 1 << 6
};

/*! wxPLplotstream is inherited from plstream, which is the C++ interface
 *  to the plplot API. The documentation of this interface is described in
 *  the PLplot manual, not here. 
 */
class PLDLLIMPEXP_WX wxPLplotstream : public plstream
{
public:
  wxPLplotstream();  //!< Constructor.
  wxPLplotstream( wxDC *dc, int width, int height, int style = wxPLPLOT_NONE );  //!< Constructor.
  void Create( wxDC *dc, int width, int height, int style );
	~wxPLplotstream();
  //wxPLplotstream( wxImage *buffer, int width, int height, int style );
  void set_stream();  //!< Calls some code before every PLplot command.
	void SetSize( int width, int height );   //!< Set new size of plot area.
	void RenewPlot();   //!< Redo plot and update memory dc
  void Update();      //!< Update memory dc, but don't redo plot

private:
  void InitStream();
  
private:
	wxDC* m_dc;     //!< Pointer to wxDC to plot into.
  wxImage* m_image;   //!< pointer to wxImage
	int m_width;    //!< Width of dc/plot area.
	int m_height;   //!< Height of dc/plot area.
  int m_style;    //!< style of this plot
  int m_backend;  //!< driver backend used
};


#endif // !defined( WXPLPLOTSTREAM_H__INCLUDED_ )
