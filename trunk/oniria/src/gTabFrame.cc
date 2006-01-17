/* $Id: gTabFrame.cc 628 2006-01-02 11:16:03Z choman $ */
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


#include "gTabFrame.h"

BEGIN_EVENT_TABLE(gTabFrame,wxFrame)
	EVT_CLOSE(gTabFrame::OnClose)
END_EVENT_TABLE()




gTabFrame::gTabFrame( wxWindow *parent)
    : wxFrame()
{
	wxXmlResource::Get()->LoadFrame(this, parent, "tabFrame");
}

gTabFrame::~gTabFrame()
{
    
} 

void gTabFrame::OnClose(wxCloseEvent &event)
{			
  	for (wxWindowListNode *node = GetChildren().GetFirst(); node; node = node->GetNext()){
    	node->GetData()->ProcessEvent(event);     	
  	}
}

 
