/* $Id: imRosterGroup.cc 614 2005-12-29 16:44:50Z choman $ */
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

namespace onirIM {

DEFINE_OOBJECT(imRosterGroup, imRosterEntry);

imRosterGroup::imRosterGroup(imSession * session)
	: imRosterEntry(session)
{
	SkinRoot("roster:group");
	INIT_OOBJECT;
}

imRosterGroup::~imRosterGroup()
{
}

bool imRosterGroup::AddEntry(imRosterEntry * e)
{
	_entries[e->Id()] = e;
	return true;
}

bool imRosterGroup::AddItem(imRosterItem * e)
{
	_items[e->Id()] = e;
	return AddEntry(e);
}

bool imRosterGroup::AddGroup(imRosterGroup * e)
{
	_groups[e->Id()] = e;
	return AddEntry(e);
}

imRosterEntry * imRosterGroup::Entry(const string& id)
{
	if (_entries.find(id) == _entries.end())
		return NULL;
	else
		return _entries[id];
}

imRosterItem * imRosterGroup::Item(const string& id)
{
	if (_items.find(id) == _items.end())
		return NULL;
	else
		return _items[id];
}

imRosterGroup * imRosterGroup::Group(const string& id)
{
	if (_groups.find(id) == _groups.end())
		return NULL;
	else
		return _groups[id];
}

bool imRosterGroup::FixedOrder(vector<string>& olist)
{
	// by default we don't want fixed order, so let's the oniria sort entries.
	return false;
}

imRosterItem * imRosterGroup::RemoveItem(const string& id)
{
	imRosterItem * item;
	
	item = Item(id);
	if (item == NULL)
		return NULL;
		
	_items.erase(id);
	_entries.erase(id);
	
	item->RemoveFromGroup(Id());
	
	return item;
}

imRosterGroup * imRosterGroup::RemoveGroup(const string& id)
{
	imRosterGroup * item;
	
	item = Group(id);
	if (item == NULL)
		return NULL;
	
	_groups.erase(id);
	_entries.erase(id);

	item->RemoveFromGroup(Id());
	
	return item;
}

};
