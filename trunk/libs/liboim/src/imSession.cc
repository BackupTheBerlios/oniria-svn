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
#include "imProtocol.h"
#include "imMessageQueue.h"
#include "imSession.h"

namespace onirIM {

imSession::imSession(imProtocol * proto)
{
	_proto = proto;
	_prepared = false;
	_msg_queue = NULL;
}

bool imSession::prepare()
{
	if (_prepared)
		return true;
	
	_msg_queue = createMessageQueue();
	
	_prepared = true;
	return true;
}

bool imSession::load(xmlElement *cfg)
{
	_cnode = cfg;
	
	prepare();	// to be sure

	name(cfg->childValue("name", ""));
	if (name() == "")
		return false;


	if (cfg->child("autoconnect") != NULL)
		_autoconnect = true;
	else
		_autoconnect = false;

	return true;
}

QString imSession::sessionId() const
{
	return protocol()->protocolId() + "::" + name();
}

bool imSession::status(const imStatus& st, bool set)
{
	_status = st;
	if (set)
		return setStatus();
	else
		return true;
}

imMessageQueue * imSession::createMessageQueue()
{
	return NULL;
}

};

