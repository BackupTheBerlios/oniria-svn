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

namespace onirIM {

imRosterGroup::imRosterGroup(imSession * session)
	: imRosterEntry(session)
{
	skinRoot("roster:group");
}

imRosterGroup::~imRosterGroup()
{
}

bool imRosterGroup::addEntry(imRosterEntry * e)
{
	_entries[e->id()] = e;
	return true;
}

bool imRosterGroup::addItem(imRosterItem * e)
{
	_items[e->id()] = e;
	return addEntry(e);
}

bool imRosterGroup::addGroup(imRosterGroup * e)
{
	_groups[e->id()] = e;
	return addEntry(e);
}

imRosterEntry * imRosterGroup::entry(const QString& id)
{
	if (_entries.find(id) == _entries.end())
		return NULL;
	else
		return _entries[id];
}

imRosterItem * imRosterGroup::item(const QString& id)
{
	if (_items.find(id) == _items.end())
		return NULL;
	else
		return _items[id];
}

imRosterGroup * imRosterGroup::group(const QString& id)
{
	if (_groups.find(id) == _groups.end())
		return NULL;
	else
		return _groups[id];
}

bool imRosterGroup::fixedOrder(QVector<QString>& olist)
{
	// by default we don't want fixed order, so let's the oniria sort entries.
	return false;
}

imRosterItem * imRosterGroup::removeItem(const QString& rid)
{
	imRosterItem * ritem;
	
	ritem = item(rid);
	if (ritem == NULL)
		return NULL;
		
	_items.remove(rid);
	_entries.remove(rid);
	
	ritem->removeFromGroup(id());
	
	return ritem;
}

imRosterGroup * imRosterGroup::removeGroup(const QString& rid)
{
	imRosterGroup * item;
	
	item = group(rid);
	if (item == NULL)
		return NULL;
	
	_groups.remove(rid);
	_entries.remove(rid);

	item->removeFromGroup(id());
	
	return item;
}

};
