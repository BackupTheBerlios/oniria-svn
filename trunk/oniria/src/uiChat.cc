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
#include <onir/im/imSession.h>
#include <onir/im/imMessageThread.h>
#include <onir/im/imMessage.h>
#include <onir/im/imPeer.h>
#include "gApp.h"
#include "gChat.h"
#include "oTabManager.h"
#include "uiChat.h"

using onirIM::imMessageThread;
using onirIM::imMessage;
using onirIM::imSession;
using onirIM::imPeer;

DEFINE_OOBJECT(uiChat, imMessageThreadUI);

uiChat::uiChat(oOniria * o)
	: imMessageThreadUI(o)
{
	INIT_OOBJECT;
}

uiChat::~uiChat()
{
	if (_wnd != NULL)
		delete _wnd;
}

bool uiChat::Create()
{
	_wnd = new gChat(&wxGetApp(), this, wxGetApp().TabManager()->ParentWindow());
	wxGetApp().TabManager()->RegisterPage(Thread()->Session()->SessionId() + ":" + Thread()->Id(), Thread()->Id(), _wnd, "chat");
	return true;
}

bool uiChat::DisplayMessage(imMessage * msg, bool output)
{
	string text;

	text = msg->Received().Format();
	if (output) {
		text += "\n";
		text += Thread()->LocalPeer()->Name();
		text += ":";
	} else {
		for (list<imPeer *>::iterator it = msg->Peers()->begin(); it != msg->Peers()->end(); it++) {
			text += "\n";
			text += (*it)->Name();
			text += ":";
		}
	}
	text += "\n";
	text += msg->Body();
	text += "\n------------------------------------------\n";
	_wnd->AddText(text);
	
	return true;
}

void uiChat::SendMessage(const string& txt)
{
	imMessage * msg;
	
	msg = new imMessage;
	msg->Body(txt);
	msg->LocalPeer(Thread()->LocalPeer());
	DisplayMessage(msg, true);
	Thread()->AddOutMessage(msg);
}
