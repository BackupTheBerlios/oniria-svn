/* $Id: gDockBarBase.h 209 2005-07-28 17:05:39Z choman $ */
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

#ifndef __G_DOCK_BAR_BASE_H
#define __G_DOCK_BAR_BASE_H

class gDockBarBase :public wxPanel{
	public:
		gDockBarBase(wxWindow * parent);
		virtual void DockType(int t){_dockTtype=t;}
		virtual int DockType(){return _dockTtype;}
		virtual void Reorganize(){}
	private:
		int _dockTtype;
};

#endif /* __G_DOCK_BAR_BASE_H */
