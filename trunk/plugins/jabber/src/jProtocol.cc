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
#include "jSession.h"
#include "jProtocol.h"

jProtocol::jProtocol()
{
}

jProtocol::~jProtocol()
{
}

QString jProtocol::protocolId() const
{
	return "jabber";
}

QString jProtocol::protocolName() const
{
	return "Jabber";
}

QString jProtocol::protocolDescription() const
{
	return "Jabber protocol";
}

QString jProtocol::protocolVersion() const
{
	return "1.0";
}

imSession * jProtocol::createSession(oOniria * o)
{
	jSession * p;
	p = new jSession(o, this);
	return p;
}

