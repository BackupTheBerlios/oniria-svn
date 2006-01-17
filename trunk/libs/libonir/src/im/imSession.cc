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
#include "../oOniria.h"
#include "imProtocol.h"
#include "imMessageQueue.h"
#include "imSession.h"

namespace onirIM {

DEFINE_OOBJECT(imSession, oObject);

imSession::imSession(oOniria * o, imProtocol * proto)
{
	INIT_OOBJECT;
	_oniria = o;
	_proto = proto;
	_prepared = false;
	_msg_queue = NULL;
}

bool imSession::Prepare()
{
	if (_prepared)
		return true;
	
	_msg_queue = CreateMessageQueue();
	
	_prepared = true;
	return true;
}

bool imSession::Load(xmlElement *cfg)
{
	_cnode = cfg;
	
	Prepare();	// to be sure

	Name(_oniria->Config()->Value(cfg, "name", ""));
	if (Name() == "")
		return false;


	if (_oniria->Config()->NodeAt(cfg, "autoconnect") != NULL)
		_autoconnect = true;
	else
		_autoconnect = false;

	return true;
}

string imSession::SessionId() const
{
	return Protocol()->ProtocolId() + "::" + Name();
}

bool imSession::Status(const imStatus& st, bool set)
{
	_status = st;
	if (set)
		return SetStatus();
	else
		return true;
}

imMessageQueue * imSession::CreateMessageQueue()
{
	return NULL;
}

};

