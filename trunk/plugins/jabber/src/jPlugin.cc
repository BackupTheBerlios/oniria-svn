/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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
//#include "jProtocol.h"
#include "jPlugin.h"

jPlugin::jPlugin()
: oPlugin()
{
	descriptionField("name", "jabber");
	descriptionField("description", "Jabber (XMPP) protocol.");
	descriptionField("version", VERSION);
	descriptionAuthorField("name", "Michal Wysoczanski");
	descriptionAuthorField("email", "choman@foto-koszalin.pl");
	descriptionAuthorField("www", "http://foto-koszalin.pl");
}

jPlugin::~jPlugin()
{
}

bool jPlugin::create(oOniria * o)
{
	//_protocol = new jProtocol;
	//o->RegisterProtocol(_protocol);
	return true;
}

