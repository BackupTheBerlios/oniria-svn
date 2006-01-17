/* $Id: gTopBar.h 483 2005-08-29 12:14:26Z morg $ */
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
 
#ifndef __G_TOP_BAR_H
#define __G_TOP_BAR_H
 
#include "gDockBarBase.h"

class gApp; 
 
class gTopBar :public gDockBarBase{
		public:
			gTopBar(gApp * app, wxWindow * parent);
		protected:
			void Reorganize();
			void OnComboBox(wxCommandEvent &event);
			void OnStatusChange(wxCommandEvent &event);
		private:			
			gApp * _app;
			wxComboBox * _combo;
			wxBoxSizer * _resizer;
			DECLARE_EVENT_TABLE()
};
 
#endif /* __TOP_BAR_H */
