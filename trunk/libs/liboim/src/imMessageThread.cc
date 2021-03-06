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
#include "imPeer.h"
#include "imMessage.h"
#include "imMessageThreadUI.h"
#include "imMessageThread.h"

namespace onirIM {

imMessageThread::imMessageThread(imSession * s)
{
	_ui = NULL;
	_session = s;
	_local_peer = NULL;
}

imMessageThread::~imMessageThread()
{
	imMessage * msg;
	
	while ((msg = nextInMessage()) != NULL)
		delete msg;
	while ((msg = nextOutMessage()) != NULL)
		delete msg;
	if (_ui != NULL)
		delete _ui;
	for (QList<imPeer *>::iterator it = _peers.begin(); it != _peers.end(); it++)
		delete *it;
	if (_local_peer != NULL)
		delete _local_peer;
}

void imMessageThread::ui(imMessageThreadUI * ui)
{
	_ui = ui;
	if (_ui != NULL)
		_ui->thread(this);
}

imMessage * imMessageThread::nextInMessage(bool peek)
{
	imMessage * msg;
	
	if (_in_messages.empty())
		return NULL;
	
	msg = _in_messages.front();
	if (!peek)
		_in_messages.pop_front();
	
	return msg;
}

imMessage * imMessageThread::nextOutMessage(bool peek)
{
	imMessage * msg;
	
	if (_out_messages.empty())
		return NULL;
	
	msg = _out_messages.front();
	if (!peek)
		_out_messages.pop_front();
	
	return msg;
}

bool imMessageThread::addInMessage(imMessage * msg)
{
	if (msg == NULL)
		return false;
	
	_in_messages.push_back(msg);
	msg->thread(this);
	return true;
}

bool imMessageThread::addOutMessage(imMessage * msg)
{
	if (msg == NULL)
		return false;
	
	_out_messages.push_back(msg);
	msg->thread(this);
	return true;
}

void imMessageThread::addPeer(imPeer * p)
{
	_peers.push_back(p);
}

};
