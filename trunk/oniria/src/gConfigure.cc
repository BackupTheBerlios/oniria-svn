/* $Id: gConfigure.cc 628 2006-01-02 11:16:03Z choman $ */
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

 
#include "gConfigure.h"
 
gConfigure::gConfigure(wxWindow * parent)
{
	
	wxXmlResource::Get()->LoadDialog(this, parent, "configDialog");	
	wxNotebook * nb = XRCCTRL(*this, "config_tabs", wxNotebook);
	
	wxPanel * p = new wxPanel;
	wxXmlResource::Get()->LoadPanel(p, nb, "configDialog_basic");	
				
	wxPanel * wnd = XRCCTRL(*p, "configDialog_parent", wxPanel);
	
	wxPanel * p2 = new wxPanel;
	wxXmlResource::Get()->LoadPanel(p2, wnd, "configDialog_Information");	
	p2->SetSize(wnd->GetParent()->GetSize());
	//p2->Show();		
	
	XRCCTRL(*this, "config_tabs", wxNotebook)->AddPage(p, "a", false);
	
}
