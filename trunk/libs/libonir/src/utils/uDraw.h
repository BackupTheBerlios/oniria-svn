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



#ifndef __U_DRAW__
#define __U_DRAW__

#include "../dll.h"
namespace onirUtils {


class LIBONIR_API uDraw{
	public:
		uDraw();
		virtual ~uDraw();

		static uDraw * Get();

		void DrawVerticalGradient(wxDC &dc, const wxRect &rect, const wxColour &from, const wxColour &to);
		void DrawHorizontalGradient(wxDC &dc, const wxRect &rect, const wxColour &from, const wxColour &to);
		void DrawSingleColour(wxDC &dc, const wxRect &rect, const wxColor &col);
		void DrawSingleRectangle(wxDC &dc, const wxRect &rect, wxColour &bg, wxColour &frame);
	private:
		static uDraw * _current;
};


};

#endif /* __U_DRAW__ */
