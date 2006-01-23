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
#include "imRosterGroup.h"
#include "imRosterEntry.h"

namespace onirIM {

imRosterEntry::imRosterEntry(imSession * session)
{
	_session = session;
	skinRoot("roster:entry");
}

imRosterEntry::~imRosterEntry()
{
}

QString imRosterEntry::name() const
{
	return _name;
}

void imRosterEntry::name(const QString& n)
{
	_name = n;
}

QString imRosterEntry::id() const
{
	return _id;
}

void imRosterEntry::id(const QString& n)
{
	_id = n;
}

void imRosterEntry::addToGroup(imRosterGroup * g)
{
	_in_groups[g->id()] = g;
}

void imRosterEntry::removeFromGroup(const QString& id)
{
	_in_groups.remove(id);
}

};
