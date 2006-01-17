/* $Id: guiButton.cc 614 2005-12-29 16:44:50Z choman $ */
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

#include "guiButton.h"

namespace onirGUI{

IMPLEMENT_DYNAMIC_CLASS(guiButton, wxControl)

BEGIN_EVENT_TABLE(guiButton, wxControl)
	EVT_PAINT(guiButton::OnPaint)
END_EVENT_TABLE()

guiButton::guiButton()
{}


bool guiButton::Create(wxWindow *parent,
	wxWindowID id,
	const wxString & text,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& validator,
	const wxString & name){

	if ( !CreateControl(parent, id, pos, size, style, validator, name) )
      return false;

	return true;
}


void guiButton::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	dc.DrawLine(0, 0, 20, 20);
}

};
