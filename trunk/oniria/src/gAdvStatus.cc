/* $Id: gAdvStatus.cc 628 2006-01-02 11:16:03Z choman $ */
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
#include <deque>
#include "gApp.h"
#include "oSessionManager.h"
#include "gAdvStatus.h"
#include "gBottomBar.h"
#include "oStatusManager.h"

using onirIM::imStatus;

BEGIN_EVENT_TABLE(gAdvStatus,wxPanel)
	EVT_BUTTON(XRCID("cancelBtn"),gAdvStatus::_cancelClick)
	EVT_BUTTON(XRCID("okBtn"),gAdvStatus::_setStatusClick)
	EVT_BUTTON(XRCID("deleteBtn"),gAdvStatus::_defaultDeleteClick)
	EVT_BUTTON(XRCID("defaultBtn"),gAdvStatus::_defaultClick)
	EVT_COMBOBOX(XRCID("history"),gAdvStatus::OnHistory)
	EVT_COMMAND(-1, wxEVT_STATUS_CHANGE, gAdvStatus::OnStatusChange)
END_EVENT_TABLE()

gAdvStatus::gAdvStatus(gApp * app, wxWindow * parent)
    :wxPanel()
{

  _app = app;
  
  wxXmlResource::Get()->LoadPanel(this, parent, "advStatus");
  _status = XRCCTRL(*this, "status", wxComboBox);
  _statusText = XRCCTRL(*this, "statusText", wxTextCtrl);
  _defaultStatus = XRCCTRL(*this, "defaultStatus", wxTextCtrl); 
  _history = XRCCTRL(*this, "history", wxComboBox); 
  
  
  _status->Append(_("Online"), reinterpret_cast<void *>(imStatus::avail));
  _status->Append(_("Free for Chat"), reinterpret_cast<void *>(imStatus::chat));
  _status->Append(_("Away"), reinterpret_cast<void *>(imStatus::away));
  _status->Append(_("Not Available"), reinterpret_cast<void *>(imStatus::xa));
  _status->Append(_("Do not Disturb"), reinterpret_cast<void *>(imStatus::dnd));
  _status->Append(_("Invisible"), reinterpret_cast<void *>(imStatus::inv));
  _status->Append(_("Offline"), reinterpret_cast<void *>(imStatus::na));    
  _app->StatusManager()->RegisterEventTarget(this);
}

gAdvStatus::~gAdvStatus()
{}

void gAdvStatus::ActStatus()
{
	  switch (_app->SessionManager()->Status().Status())
    {
      case imStatus::avail:
      _status->Select(0);
      break;
      case imStatus::chat:
      _status->Select(1);
      break;
      case imStatus::away:
      _status->Select(2);
      break;
      case imStatus::xa:
      _status->Select(3);
      break;
      case imStatus::dnd:
      _status->Select(4);
      break;
      case imStatus::inv:
      _status->Select(5);
      break;
      case imStatus::na:
      _status->Select(6);
      break;
      default:
      break;
    }
    string statusText = _app->SessionManager()->Status().Description();
	_statusText->SetLabel(statusText.c_str());
	_statusText->SetSelection(0, statusText.size());
	string s = _app->StatusManager()->Default().Description();
	if (s.empty()){
		_defaultStatus->SetLabel(_("< Empty >"));
	}else{
		_defaultStatus->SetLabel(s.c_str());
	}
	
	_history->Clear();
	_history->Append(_("< Empty >"));
	deque<pair<string, string> > stat = _app->StatusManager()->Statuses();	
	for (deque<pair<string, string> >::iterator i = stat.begin() ; i!=stat.end(); ++i){
		_history->Append(i->first, &i->second);
	}	

}

void gAdvStatus::_setStatusClick(wxCommandEvent& event)
{	
	string status = _statusText->GetValue().c_str();
	int sel = _status->GetSelection();
	_app->StatusManager()->Status(reinterpret_cast<int>((_status->GetClientData(sel))), status);    
	Close();
}


void gAdvStatus::_cancelClick(wxCommandEvent& event)
{
  Close();
}

void gAdvStatus::_defaultClick(wxCommandEvent& event)
{
	wxString s=_statusText->GetValue();
	if (s.IsEmpty())
    	s = _("< Empty >");
	else{
		_app->StatusManager()->Default(s.c_str());		
	}
	_app->StatusManager()->Default(reinterpret_cast<int>((_status->GetClientData(_status->GetSelection()))));	
  	_defaultStatus->SetValue(s);
  
}


void gAdvStatus::_defaultDeleteClick(wxCommandEvent& event)
{
	_defaultStatus->SetLabel(_("< Empty >"));
	_app->StatusManager()->Default("");
}

void gAdvStatus::OnHistory(wxCommandEvent& event)
{
	wxString s;
	int item = _history->GetSelection();
	if (item > 0)
		s = *reinterpret_cast<string *>(_history->GetClientData(item));	
  	_statusText->SetValue(s);
}

void gAdvStatus::OnStatusChange(wxCommandEvent &event)
{
	ActStatus();	
}

