/* $Id: guiPopupWindow.cc 614 2005-12-29 16:44:50Z choman $ */
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

#include "guiPopupWindow.h"

namespace onirGUI{

guiPopupWindowBase::guiPopupWindowBase()
:wxDialog()
{
	_style = cpsVEXPAND;	
}

void guiPopupWindowBase::AutoPosition(const wxRect & rect)
{
    wxSize pop = GetSize();    
    wxRect area = ::wxGetClientDisplayRect();
    wxRect rc = rect;    
    
    int x, y;
    if (pop.GetHeight() + rc.GetBottom() + 5 < area.GetBottom()){
    	y = rc.GetBottom() + 5;
    }else{
    	y = rc.GetTop() - pop.GetHeight() - 5;
    }
    
    if (rc.GetLeft() + pop.GetWidth() < area.GetRight()){
        x = rc.GetLeft();
    }else{
    	x = rc.GetRight() - pop.GetWidth();    	
    }
    
    Move(x, y);
}

bool guiPopupWindowBase::Show(bool show)
{
	if ((IsShown() && show) || (!IsShown() && !show))
		return false; 
		
	switch (_style){			
		case cpsVEXPAND:
			return Expand(show);	
		break;
		default:
			return wxDialog::Show(show);
	}
}

bool guiPopupWindowBase::Expand(bool in)
{
	#define EXPAND_STEP 8
	wxSize sz = GetSize();
	wxPoint p = GetPosition();
	bool ret;
	if (in){
		SetSize(sz.GetWidth(), 0);		
		ret = wxDialog::Show(true);
		for(int i = 0; i <= sz.GetHeight() - EXPAND_STEP; i += EXPAND_STEP){
			SetSize(sz.GetWidth(), i);
			Move(p);
		}
		SetSize(sz);
	}else{
		for(int i = sz.GetHeight() + EXPAND_STEP; i >= 0; i-=EXPAND_STEP){
			SetSize(sz.GetWidth(), i);
			Move(p);
		}
		ret = wxDialog::Show(false);
		SetSize(sz);
	}
	return ret;
}
/* ------------------------------------ */

DEFINE_EVENT_TYPE(wxEVT_POPUP_LIST_CLICK)


BEGIN_EVENT_TABLE(guiPopupListBoxWindow, wxDialog)	
    EVT_LISTBOX(XRCID("list"), guiPopupListBoxWindow::OnSelect) 
END_EVENT_TABLE()

guiPopupListBoxWindow::guiPopupListBoxWindow(wxWindow * parent)
:guiPopupWindowBase()
{
	wxXmlResource::Get()->LoadDialog(this, parent, "PopupListBox");
}

void guiPopupListBoxWindow::AddItem(const string & str, string * data)
{
	XRCCTRL(*this, "list", wxListBox)->Append(str.c_str(), data);
}

void guiPopupListBoxWindow::Clear()
{
	XRCCTRL(*this, "list", wxListBox)->Clear();
}

void guiPopupListBoxWindow::MoveSelDown()
{
	wxListBox * list = XRCCTRL(*this, "list", wxListBox);
    int index = list->GetSelection() + 1;    
    if (index >= list->GetCount())
        index = 0; 
    list->Select(index);    
}

void guiPopupListBoxWindow::MoveSelUp()
{	
	wxListBox * list = XRCCTRL(*this, "list", wxListBox);
    int index = list->GetSelection() - 1;    
    if (index < 0)
        index = list->GetCount() - 1; 
    list->Select(index);
}

string guiPopupListBoxWindow::Selection()
{
    wxListBox * list = XRCCTRL(*this, "list", wxListBox);
    string * s = reinterpret_cast<string *>(list->GetClientData(list->GetSelection()));
    return s?*s:"";
}

void guiPopupListBoxWindow::OnSelect(wxCommandEvent &event)
{
	wxCommandEvent c_event;
	c_event.SetId(GetId());
	c_event.SetEventObject(this);
	c_event.SetEventType(wxEVT_POPUP_LIST_CLICK);
	event.Skip();
	GetParent()->GetEventHandler()->ProcessEvent(c_event);
}

};
