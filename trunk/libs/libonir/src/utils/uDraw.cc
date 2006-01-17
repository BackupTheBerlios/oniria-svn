/* $Id$ */
/*
 * Copyright (C) 2005
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#if defined(HAVE_CONFIG_H)
# include <config.h>
#endif

#include "uDraw.h"

namespace onirUtils {

uDraw * uDraw::_current = NULL;

/*static*/ uDraw * uDraw::Get()
{
	if (_current == NULL)
		_current = new uDraw();
	return _current;
}

uDraw::uDraw()
{

}
uDraw::~uDraw()
{
}

void uDraw::DrawVerticalGradient(wxDC &dc, const wxRect &rect, const wxColour &from, const wxColour &to)
{
	// gradient fill from colour 1 to colour 2 with top to bottom

	if(rect.height < 1 || rect.width < 1)
		return;

	int size = rect.height;

	dc.SetPen(*wxTRANSPARENT_PEN);


	// calculate gradient coefficients
	wxColour col2 = from,
					col1 = to;

	double rstep = double((col2.Red() -   col1.Red())) / double(size), rf = 0,
				   gstep = double((col2.Green() - col1.Green())) / double(size), gf = 0,
						   bstep = double((col2.Blue() -  col1.Blue())) / double(size), bf = 0;

	wxColour currCol;
	for(int y = rect.y; y < rect.y + size; y++)
	{
		currCol.Set(
			(unsigned char)(col1.Red() + rf),
			(unsigned char)(col1.Green() + gf),
			(unsigned char)(col1.Blue() + bf)
		);
		dc.SetBrush( wxBrush( currCol, wxSOLID ) );
		dc.DrawRectangle( rect.x, rect.y + (y - rect.y), rect.width, size );
		rf += rstep; gf += gstep; bf += bstep;
	}
}

void uDraw::DrawHorizontalGradient(wxDC &dc, const wxRect &rect, const wxColour &from, const wxColour &to)
{
	if(rect.height < 1 || rect.width < 1)
		return;

	int size = rect.width;

	dc.SetPen(*wxTRANSPARENT_PEN);

	// calculate gradient coefficients
	wxColour col2 = from,
					col1 = to;

	double rstep = double((col2.Red() -   col1.Red())) / double(size), rf = 0,
				   gstep = double((col2.Green() - col1.Green())) / double(size), gf = 0,
						   bstep = double((col2.Blue() -  col1.Blue())) / double(size), bf = 0;

	wxColour currCol;
	for(int x = rect.x; x < rect.x + size; x++)
	{
		currCol.Set(
			(unsigned char)(col1.Red() + rf),
			(unsigned char)(col1.Green() + gf),
			(unsigned char)(col1.Blue() + bf)
		);
		dc.SetBrush( wxBrush( currCol, wxSOLID ) );
		dc.DrawRectangle( rect.x + (x - rect.x), rect.y, 1, rect.height );
		rf += rstep; gf += gstep; bf += bstep;
	}
}

void uDraw::DrawSingleColour(wxDC &dc, const wxRect &rect, const wxColor &col)
{
	if(rect.height < 1 || rect.width < 1)
		return;

	dc.SetPen(*wxTRANSPARENT_PEN);

	// draw simple rectangle
	dc.SetBrush( wxBrush( col, wxSOLID ) );
	dc.DrawRectangle( rect.x, rect.y, rect.width, rect.height );
}

void uDraw::DrawSingleRectangle(wxDC &dc, const wxRect &rect, wxColour &bg, wxColour &frame)
{
	wxASSERT(GetParent());

	if(rect.height < 2 || rect.width < 1)
		return;

	// single frame, set up internal fill colour

	wxBrush br;
	br.SetStyle(wxSOLID);
	br.SetColour(bg);

	wxPen pen(frame);
	dc.SetPen(pen);

	dc.SetBrush( br );
	dc.DrawRectangle( rect.x, rect.y, rect.width, rect.height - 1);

	wxPen bgpen(bg);
	dc.SetPen(bgpen);
	dc.DrawLine(rect.x, rect.y + rect.height - 1, rect.x + rect.width, rect.y + rect.height - 1);
}

}
