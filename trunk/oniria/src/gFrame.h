/* $Id: gFrame.h 490 2005-09-02 08:43:33Z choman $ */
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

#ifndef __GFRAME_H
#define __GFRAME_H

#include <set>

namespace onir {
	class oOniria;
};

using std::set;

class wxFrameLayout;
class gBottomBar;
class wxPanel;
class wxWindow;
class gApp;

class gFrame : public wxFrame
{

	public:

 		gFrame(wxWindow * parent, 
		       const wxString & name="",
		       long style = wxDEFAULT_FRAME_STYLE,
		       const wxPoint& pos = wxDefaultPosition,
		       const wxSize& size = wxDefaultSize,
		       wxWindowID id = wxID_ANY,
		       gApp * a = NULL);

		~gFrame();

		long FreeCmd();
		inline wxWindow * GeneralWnd() { return reinterpret_cast<wxWindow *>( _general); };

private:

	virtual void OnSize(wxSizeEvent & event);
	virtual void OnCommandRange(wxCommandEvent & event);
	virtual void OnIdle(wxIdleEvent & event);

	wxFrameLayout	*	_layout;        
	wxPanel  *	_general;
		
	set<long> _used_commands;
	gApp * _app;

	DECLARE_EVENT_TABLE()
};

#endif /* __FRAME_H */
