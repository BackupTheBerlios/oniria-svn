/* $Id: gChat.cc 628 2006-01-02 11:16:03Z choman $ */
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
#include "gApp.h"
#include "uiChat.h"
#include "gChat.h"

BEGIN_EVENT_TABLE(gChat, wxPanel)
	EVT_BUTTON(XRCID("send"), gChat::OnSentButtonClick)	
END_EVENT_TABLE()

gChat::gChat(gApp * app, uiChat * ui, wxWindow * parent)
{
	_app = app;	
	_ui = ui;
	wxXmlResource::Get()->LoadPanel(this, parent, "chatPanel");	
	_displayText = XRCCTRL(*this, "displayText", wxTextCtrl);
	_sendText = XRCCTRL(*this, "message", wxTextCtrl);
}

void gChat::OnSentButtonClick(wxCommandEvent &event)
{
	string text = static_cast<string>(_sendText->GetValue());
	_sendText->SetValue(wxEmptyString);
//	_displayText->AppendText(text);	
	_ui->SendMessage(text);
}

void gChat::AddText(const string &text)
{	
	_displayText->AppendText(text.c_str());	
}
