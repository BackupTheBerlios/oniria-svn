/* $Id: ctrlStatusText.cc 628 2006-01-02 11:16:03Z choman $ */
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

#include <wx/gdicmn.h>
#include <cctype>
#include "ctrlStatusText.h"
#include <onir/gui/guiPopupWindow.h>

using namespace onirGUI;

BEGIN_EVENT_TABLE(ctrlStatusText, wxTextCtrl)	
	EVT_CHAR(ctrlStatusText::OnChar)
	EVT_MOVE(ctrlStatusText::OnMove) 
	EVT_KILL_FOCUS(ctrlStatusText::OnFocus)
	EVT_COMMAND(XRCID("PopupListBox"), wxEVT_POPUP_LIST_CLICK, ctrlStatusText::StatusClick)
END_EVENT_TABLE()



ctrlStatusText::ctrlStatusText(wxWindow * parent, wxWindowID id)
:wxTextCtrl(parent, id)
{	
	_enablePopup = true;
	_autoPopup = true;
	_autoPopupForce = false;
	_popup = new guiPopupListBoxWindow(this);
    _popup->Show(false);
    _firstActive = false;
}

ctrlStatusText::~ctrlStatusText()
{
    
}


void ctrlStatusText::Match(deque<pair<string, string> > & ret, const wxString & mask)
{
	wxLogMessage("ctrlStatusText:Mach process with %s ", mask.c_str());
	ret.clear();
	wxString s;
	for (deque<pair<string, string> >::iterator i = _statusData.begin() ; i != _statusData.end(); ++i){
		s = i->second.c_str();
	//	s = s.Lower();
		if (s.StartsWith(mask)){
			ret.push_back(*i);
		}
	}		
}

void ctrlStatusText::DisplayPopup(deque<pair<string, string> > & items)
{
	if (!_enablePopup)
		return;					
		
	_popup->Clear();
	for (deque<pair<string, string> >::iterator i = items.begin() ; i != items.end(); ++i){
		_popup->AddItem(i->first, &i->second);
	}
	
	if (items.empty() && !_autoPopupForce){
		_popup->Show(false);
		_autoPopupForce = false;
		wxLogMessage("ctrlStatusText:hide popup");		
	}else{ 
		_popup->AutoPosition(wxRect(ClientToScreen(GetRect().GetTopLeft()), ClientToScreen(GetRect().GetBottomRight())));
		_popup->Show(true);		
		wxLogMessage("ctrlStatusText:display popup with %d match", items.size());
	}
	SetFocus();
}

void ctrlStatusText::DisplayText(deque<pair<string, string> > & items)
{	
	wxString s = Value();
	wxString base = Value();
	if (!items.empty()){
		s = items.front().second.c_str();	
		SetValue(s);		
		SetSelection(base.Length(), s.Length());
		wxLogMessage("ctrlStatusText: display text with all: %s, base:	%s", s.c_str(), base.c_str());
	}
}

wxString ctrlStatusText::Value()
{
	long fr, to;
	GetSelection(&fr, &to);	
	if ((to - fr == 0))
		return GetValue();
	else{
		return GetValue().Mid(0, fr);
	}
	
}

void ctrlStatusText::OnMove(wxMoveEvent &event)
{
    _popup->AutoPosition(GetRect());
}

void ctrlStatusText::StatusClick(wxCommandEvent &event)
{
	if (_popup->IsShown()){
		_popup->Show(false);	
		SetValue(_popup->Selection().c_str());
		SetInsertionPoint(GetValue().Length());
	}
}

void ctrlStatusText::OnFocus(wxFocusEvent &event)
{
	event.Skip();
}


void ctrlStatusText::OnChar(wxKeyEvent &event)
{	
	bool can_process = true;		
	event.Skip(false);
			
	wxLogMessage("ctrlStatusText: (%s , %s , %d)", GetValue().c_str() , Value().c_str(), event.GetKeyCode());
	wxString base = Value();
	switch (event.GetKeyCode()){
		case WXK_BACK:			
			if (!base.IsEmpty()){
				base = base.Mid(0, base.Length() - 1);
				SetValue(base);
				SetInsertionPoint(base.Length());
				wxLogMessage("ctrlStatusText:bkspace (result: %s)", base.c_str());				
			}
		break;
		case WXK_UP:		
               if (_popup->IsShown()){
                   _popup->MoveSelUp();
                   SetValue(_popup->Selection().c_str());
                   SetInsertionPoint(GetValue().Length());
                   can_process = false;                 
               }               
		break;
		case WXK_DOWN:
               if (_popup->IsShown()){
                   _popup->MoveSelDown();
                   SetValue(_popup->Selection().c_str());
                   SetInsertionPoint(GetValue().Length());
                   can_process = false;                   
               }              
		break;		
	
		case WXK_RETURN:
                if (_popup->IsShown()){                    
                    _popup->Show(false);
                }             	                
                can_process = false;  
                event.Skip();
		break;		
		case WXK_ESCAPE:
               _popup->Show(false);
               can_process = false;               
		break;	
		case WXK_DELETE:
			if (_popup->IsShown()){                    
    		    _popup->Show(false);
			}
			can_process = false;
			event.Skip();                  
		break;	
		case WXK_SPACE:
			if (event.ControlDown()){
				_autoPopupForce = true;	
				wxLogMessage("ctrlStatusText: force popup reguest");
			}
		break;		
		case WXK_HOME:
		case WXK_END:
			can_process = false;
			event.Skip();
			break;		
	}
	
	bool spec = event.AltDown() || event.ShiftDown() || event.ControlDown();
	if (spec && iscntrl(event.GetKeyCode())){
		can_process = false;
		event.Skip();
	}
	
	if (can_process){		
		deque<pair<string, string> > items;						
		if (!_autoPopupForce && isprint(event.GetKeyCode())){			
			char c;			
			if (event.ShiftDown())
				c = (char)toupper(event.GetKeyCode());				
			else
				c = (char)tolower(event.GetKeyCode());
			SetValue(Value() + c);		
		}
		Match(items, Value());				
				
		DisplayText(items);
		
		if (_autoPopup || _autoPopupForce)
        	DisplayPopup(items);
		if (items.empty()){
			SetInsertionPoint(GetValue().Length());
		}
	}
		
}
