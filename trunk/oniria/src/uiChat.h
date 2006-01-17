/* $Id: uiChat.h 628 2006-01-02 11:16:03Z choman $ */
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
#ifndef __UICHAT_H
#define __UICHAT_H

#include <onir/im/imMessageThreadUI.h>
#include <onir/im/imMessage.h>

using onirIM::imMessageThreadUI;
using onirIM::imMessage;
class gChat;

class uiChat : public imMessageThreadUI {

	public:

		uiChat(oOniria * o);
		virtual ~uiChat();
		
		virtual bool Create();
		virtual bool DisplayMessage(imMessage * msg, bool output = false);
		
		void SendMessage(const string& txt);

	private:

		gChat * _wnd;

		DECLARE_OOBJECT;
};

#endif
