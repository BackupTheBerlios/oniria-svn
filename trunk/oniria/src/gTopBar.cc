/* $Id: gTopBar.cc 628 2006-01-02 11:16:03Z choman $ */
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
 
#include "gTopBar.h"
#include "gApp.h"
#include "oStatusManager.h"

#define TOP_BUTTON_SIZE 20
#define TOP_COMBO 0x100l
 
BEGIN_EVENT_TABLE(gTopBar, gDockBarBase)
	EVT_COMBOBOX(TOP_COMBO, gTopBar::OnComboBox) 
	EVT_COMMAND(-1, wxEVT_STATUS_CHANGE, gTopBar::OnStatusChange)
END_EVENT_TABLE()

 
gTopBar::gTopBar(gApp * app, wxWindow * parent)
:gDockBarBase(parent)
{	
	_app = app;
	wxArrayString a;
	_combo=new wxComboBox( this, TOP_COMBO, 
		"Status", 
		wxDefaultPosition, 
		wxSize(TOP_BUTTON_SIZE,TOP_BUTTON_SIZE),
		a,
		wxCB_DROPDOWN | wxCB_READONLY);
	
	_resizer=new wxBoxSizer(wxHORIZONTAL);	
	_resizer->Add(_combo,1,wxALL,0);
	_resizer->SetSizeHints(this); 
	_resizer->Layout();	
	SetSizer(_resizer);	
	
  _combo->Append(_("Online"), reinterpret_cast<void *>(imStatus::avail));
  _combo->Append(_("Free for Chat"), reinterpret_cast<void *>(imStatus::chat));
  _combo->Append(_("Away"), reinterpret_cast<void *>(imStatus::away));
  _combo->Append(_("Not Available"), reinterpret_cast<void *>(imStatus::xa));
  _combo->Append(_("Do not Disturb"), reinterpret_cast<void *>(imStatus::dnd));
  _combo->Append(_("Invisible"), reinterpret_cast<void *>(imStatus::inv));
  _combo->Append(_("Offline"), reinterpret_cast<void *>(imStatus::na)); 	
  
  _app->StatusManager()->RegisterEventTarget(this);
}

void gTopBar::Reorganize()
{
	_resizer->SetOrientation(DockType());
	_resizer->Layout();
}

void gTopBar::OnComboBox(wxCommandEvent &event)
{
	int sel = _combo->GetSelection();
	_app->StatusManager()->Status(reinterpret_cast<int>((_combo->GetClientData(sel))));    
}

void gTopBar::OnStatusChange(wxCommandEvent &event)
{	
	for (int i = 0; i < _combo->GetCount(); i++){
		if (reinterpret_cast<int>((_combo->GetClientData(i))) == event.GetInt()){
			_combo->Select(i);
			break;
		}
	}
	
}
