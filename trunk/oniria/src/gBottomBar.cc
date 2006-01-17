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

#include <onir/im/imStatus.h>
#include <wx/utils.h>
#include <algorithm>
#include "gBottomBar.h"
#include "gAdvStatus.h"
#include "gConfigure.h"
#include "gApp.h"
#include "oStatusManager.h"
#include "oSessionManager.h"
#include "oTabManager.h"

using namespace std;
using onirIM::imStatus;

#define PANEL_HEIGHT 20
#define BUTTON_BOX 20

const int LEFT_BUTTON 			= wxNewId();
const int RIGHT_BUTTON			= wxNewId();
const int TEXT_BOX				= wxNewId();
const int TEXT_RIGHT_BUTTON 	= wxNewId();
const int MENU_SETTINGS			= wxNewId();
const int MENU_CLOSE			= wxNewId();

const int MENU_BEGIN 			= 0x10;
const int MENU_END 				= 0x30;

BEGIN_EVENT_TABLE(gBottomBar, wxPanel)
	EVT_BUTTON(TEXT_RIGHT_BUTTON, gBottomBar::EventFunc)
	EVT_BUTTON(RIGHT_BUTTON, gBottomBar::EventFunc)
	EVT_BUTTON(LEFT_BUTTON, gBottomBar::EventFunc)
	EVT_MENU_RANGE(MENU_BEGIN, MENU_END, gBottomBar::EventFunc)
	EVT_MENU(MENU_SETTINGS, gBottomBar::OnMenu)
	EVT_COMMAND(-1, wxEVT_STATUS_CHANGE, gBottomBar::OnStatusChange)
	EVT_TEXT_ENTER(TEXT_BOX, gBottomBar::OnEnter) 
END_EVENT_TABLE()

gBottomBar::gBottomBar(gApp * app, wxWindow * parent)
    : gDockBarBase(parent)
{
  _app = app;  
  
  SetAutoLayout(true);
  _status=new ctrlStatusText(this, TEXT_BOX);
  int h = _status->GetSize().GetHeight();
  _leftBtn = new wxButton(this, LEFT_BUTTON, _(":P"), wxDefaultPosition, wxSize(h, h));
  _rightBtn = new wxButton(this, RIGHT_BUTTON, _("<:"), wxDefaultPosition, wxSize(h, h));
  _textRightBtn = new wxButton(this, TEXT_RIGHT_BUTTON, _("<:"), wxDefaultPosition, wxSize(h, h));
  
  _resizer = new wxBoxSizer(wxHORIZONTAL);
  _resizer->Add(_leftBtn, 0, wxALL, 1);
  _resizer->Add(_status, 1, wxEXPAND | wxALL, 1);
  _resizer->Add(_textRightBtn, 0, wxALL, 1);
  _resizer->Add(_rightBtn, 0, wxALL, 1);
  _resizer->SetSizeHints(this);
  _resizer->Layout();
  SetSizer(_resizer);
  
  
  _basicMenu = new wxMenu;
  _basicMenu->Append(MENU_SETTINGS, _("&Settings"));
  _basicMenu->AppendSeparator();
  _basicMenu->Append(MENU_CLOSE, _("Cl&ose"));
  
  _advstatus = NULL;
  _statusMenu = NULL;
  _configure = NULL;
  
  _app->StatusManager()->RegisterEventTarget(this);
  _status->StatusData(_app->StatusManager()->Statuses());
  _status->SetValue(_app->StatusManager()->Default().Description());
	
}

gBottomBar::~gBottomBar()
{
	if (_statusMenu)
		delete _statusMenu;	
	delete _basicMenu;
}

wxMenu * gBottomBar::BuildStatusMenu()
{
	int begin = MENU_BEGIN;
	if (_statusMenu	!= NULL)
		delete _statusMenu;
	_statusMenu = new wxMenu;
	deque<pair<string, string> > stat = _app->StatusManager()->Statuses();
	wxMenuItem * item;
	for (deque<pair<string, string> >::iterator i = stat.begin() ; i!=stat.end(); ++i){			
			_idToStr[begin] = i->second;
			item = _statusMenu->Append(begin, i->first.c_str());
			begin++;
	}	
	return _statusMenu;
}

void gBottomBar::Reorganize()
{
  //_resizer->SetOrientation(DockType());  
  //_resizer->Layout();  
}

void gBottomBar::EventFunc(wxCommandEvent& event)
{	
	wxLogVerbose("gBottomBar::EventFunc(%d)", event.GetId());
	if (event.GetId() == RIGHT_BUTTON){  
		CreateAdvStatusDlg();			
    }else if (event.GetId() == TEXT_RIGHT_BUTTON){
    	BuildStatusMenu();
		_status->PopupMenu(_statusMenu, _status->GetPosition());		    	
    }else if((event.GetId() >= MENU_BEGIN) && (event.GetId() <= MENU_END)){    	    	
    	string str = _idToStr[event.GetId()];
    	_app->StatusManager()->Status(str.c_str());
    }else if (event.GetId() == LEFT_BUTTON ){
    	_status->PopupMenu(_basicMenu, _status->GetPosition());
    }
    
}

void gBottomBar::OnEnter(wxCommandEvent &event)
{	
	_app->StatusManager()->Status(_status->GetValue().c_str());	
}

void gBottomBar::OnMenu(wxCommandEvent &event)
{
	if (event.GetId() == MENU_SETTINGS){		
		if (_configure == NULL)
			_configure = new gConfigure(this);
		_configure->Show();		
	}else if (event.GetId() == MENU_CLOSE){
		_app->CloseApp();
	}
}

void gBottomBar::OnStatusChange(wxCommandEvent &event)
{
	_status->SetValue(event.GetString());
	_status->StatusData(_app->StatusManager()->Statuses());      
}

void gBottomBar::CreateAdvStatusDlg()
{		
	if (_advstatus == NULL){
		_advstatus = new gAdvStatus(_app, _app->TabManager()->ParentWindow());		
	}
	_app->TabManager()->RegisterPage("advanced status dialog", _("Advanced status"), _advstatus, "system_dialogs");	
}
