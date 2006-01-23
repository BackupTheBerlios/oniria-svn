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
#include "imRosterEntry.h"
#include "imRosterGroup.h"
#include "imRoster.h"

namespace onirIM {

imRoster::imRoster(imSession * session)
{
	_session = session;
}

imRoster::~imRoster()
{
	for (QMap<QString, imRosterEntry *>::iterator it = _entries.begin(); it != _entries.end(); it++)
		delete it.value();
}

bool imRoster::addEntry(imRosterEntry * entry, imRosterGroup * g)
{
	_entries[entry->id()] = entry;
	if (g != NULL) {
		g->addEntry(entry);
		entry->addToGroup(g);
	} else {
		_top_entries[entry->id()] = entry;
	}
	return true;
}

bool imRoster::addEntry(imRosterEntry * entry, const QString& g)
{
	imRosterGroup * pg = NULL;
	
	if (_groups.find(g) != _groups.end())
		pg = _groups[g];
		
	return addEntry(entry, pg);
}

bool imRoster::addItem(imRosterItem * entry, imRosterGroup * g)
{
	_entries[entry->id()] = entry;
	_items[entry->id()] = entry;
	_allitems[entry->id()] = entry;
	if (g != NULL) {
		g->addItem(entry);
		entry->addToGroup(g);
	} else {
		_top_items[entry->id()] = entry;
		_top_entries[entry->id()] = entry;
	}
	return true;
}

bool imRoster::addItem(imRosterItem * entry, const QString& g)
{
	imRosterGroup * pg = NULL;
	
	if (_groups.find(g) != _groups.end())
		pg = _groups[g];
		
	return addItem(entry, pg);
}

bool imRoster::addSubItem(imRosterItem * entry, imRosterItem * item)
{
	_entries[entry->id()] = entry;
	_allitems[entry->id()] = entry;
	if (item != NULL) {
		item->addSubItem(entry);
		return true;
	} else {
		return false;
	}
}

bool imRoster::addSubItem(imRosterItem * entry, const QString& item)
{
	imRosterItem * pi = NULL;
	
	if (_items.find(item) != _items.end())
		pi = _items[item];
		
	return addSubItem(entry, pi);
}

bool imRoster::addGroup(imRosterGroup * entry, imRosterGroup * g)
{
	_entries[entry->id()] = entry;
	_groups[entry->id()] = entry;
	if (g != NULL) {
		g->addGroup(entry);
	} else {
		_top_groups[entry->id()] = entry;
		_top_entries[entry->id()] = entry;
	}
	return true;
}

bool imRoster::addGroup(imRosterGroup * entry, const QString& g)
{
	imRosterGroup * pg = NULL;
	
	if (_groups.find(g) != _groups.end())
		pg = _groups[g];
		
	return addGroup(entry, pg);
}

imRosterEntry * imRoster::entry(const QString& id)
{
	if (_entries.find(id) == _entries.end())
		return NULL;
	else
		return _entries[id];
}

imRosterItem * imRoster::item(const QString& id, bool allitems)
{
	if (allitems) {
		if (_allitems.find(id) == _allitems.end())
			return NULL;
		else
			return _allitems[id];
	} else {
		if (_items.find(id) == _items.end())
			return NULL;
		else
			return _items[id];
	}
}

imRosterGroup * imRoster::group(const QString& id)
{
	if (_groups.find(id) == _groups.end())
		return NULL;
	else
		return _groups[id];
}

imRosterEntry * imRoster::topEntry(const QString& id)
{
	if (_top_entries.find(id) == _top_entries.end())
		return NULL;
	else
		return _top_entries[id];
}

imRosterItem * imRoster::topItem(const QString& id)
{
	if (_top_items.find(id) == _top_items.end())
		return NULL;
	else
		return _top_items[id];
}

imRosterGroup * imRoster::topGroup(const QString& id)
{
	if (_top_groups.find(id) == _top_groups.end())
		return NULL;
	else
		return _top_groups[id];
}

imRosterItem * imRoster::removeItem(const QString& aid)
{
	imRosterItem * ritem;
	QMap<QString, imRosterGroup *>::iterator it1;

	ritem = item(aid);
	if (ritem == NULL)
		return NULL;
	
	it1 = ritem->inGroups()->begin();
	while (it1 != ritem->inGroups()->end()) {
		imRosterGroup * gr = it1.value();
		it1++;
		gr->removeItem(aid);
	}
		
	if (topItem(aid) == ritem) {
		_top_items.remove(aid);
		_top_entries.remove(aid);
	}
	
	_items.remove(aid);
	_entries.remove(aid);
	_allitems.remove(aid);
	
	return ritem;
}

imRosterGroup * imRoster::removeGroup(const QString& id)
{
	imRosterGroup * item;
	QMap<QString, imRosterGroup *>::iterator it1;

	item = group(id);
	if (item == NULL)
		return NULL;
	
	it1 = item->inGroups()->begin();
	while (it1 != item->inGroups()->end()) {
		imRosterGroup * gr = it1.value();
		it1++;
		gr->removeGroup(id);
	}
		
	for (QMap<QString, imRosterEntry *>::iterator it = item->entries()->begin(); it != item->entries()->end(); it++)
		it.value()->removeFromGroup(id);
		
	if (topGroup(id) == item) {
		_top_groups.remove(id);
		_top_entries.remove(id);
	}
	
	_groups.remove(id);
	_entries.remove(id);
	
	return item;
}

imRosterItem * imRoster::removeSubItem(const QString& id)
{
	imRosterItem * item;
	
	if (_allitems.find(id) == _allitems.end())
		return NULL;
	else
		item = _allitems[id];
		
	_allitems.remove(id);
	_entries.remove(id);
		
	if (item->parent() != NULL)
		return item->parent()->removeSubItem(id);
	else
		return NULL;
}

};
