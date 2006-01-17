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

DEFINE_OOBJECT(imRosterEntry, oObject);

imRosterEntry::imRosterEntry(imSession * session)
{
	INIT_OOBJECT;
	_session = session;
	SkinRoot("roster:entry");
}

imRosterEntry::~imRosterEntry()
{
}

string imRosterEntry::Name() const
{
	return _name;
}

void imRosterEntry::Name(const string& n)
{
	_name = n;
}

string imRosterEntry::Id() const
{
	return _id;
}

void imRosterEntry::Id(const string& n)
{
	_id = n;
}

void imRosterEntry::AddToGroup(imRosterGroup * g)
{
	_in_groups[g->Id()] = g;
}

void imRosterEntry::RemoveFromGroup(const string& id)
{
	_in_groups.erase(id);
}

};
