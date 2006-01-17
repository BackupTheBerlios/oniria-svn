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
#include "imRosterEntry.h"
#include "imRosterGroup.h"
#include "imRoster.h"

namespace onirIM {

DEFINE_OOBJECT(imRoster, oObject);

imRoster::imRoster(imSession * session)
{
	INIT_OOBJECT;
	_session = session;
}

imRoster::~imRoster()
{
	for (map<string, imRosterEntry *>::iterator it = _entries.begin(); it != _entries.end(); it++)
		delete it->second;
}

bool imRoster::AddEntry(imRosterEntry * entry, imRosterGroup * g)
{
	_entries[entry->Id()] = entry;
	if (g != NULL) {
		g->AddEntry(entry);
		entry->AddToGroup(g);
	} else {
		_top_entries[entry->Id()] = entry;
	}
	return true;
}

bool imRoster::AddEntry(imRosterEntry * entry, const string& g)
{
	imRosterGroup * pg = NULL;
	
	if (_groups.find(g) != _groups.end())
		pg = _groups[g];
		
	return AddEntry(entry, pg);
}

bool imRoster::AddItem(imRosterItem * entry, imRosterGroup * g)
{
	_entries[entry->Id()] = entry;
	_items[entry->Id()] = entry;
	_allitems[entry->Id()] = entry;
	if (g != NULL) {
		g->AddItem(entry);
		entry->AddToGroup(g);
	} else {
		_top_items[entry->Id()] = entry;
		_top_entries[entry->Id()] = entry;
	}
	return true;
}

bool imRoster::AddItem(imRosterItem * entry, const string& g)
{
	imRosterGroup * pg = NULL;
	
	if (_groups.find(g) != _groups.end())
		pg = _groups[g];
		
	return AddItem(entry, pg);
}

bool imRoster::AddSubItem(imRosterItem * entry, imRosterItem * item)
{
	_entries[entry->Id()] = entry;
	_allitems[entry->Id()] = entry;
	if (item != NULL) {
		item->AddSubItem(entry);
		return true;
	} else {
		return false;
	}
}

bool imRoster::AddSubItem(imRosterItem * entry, const string& item)
{
	imRosterItem * pi = NULL;
	
	if (_items.find(item) != _items.end())
		pi = _items[item];
		
	return AddSubItem(entry, pi);
}

bool imRoster::AddGroup(imRosterGroup * entry, imRosterGroup * g)
{
	_entries[entry->Id()] = entry;
	_groups[entry->Id()] = entry;
	if (g != NULL) {
		g->AddGroup(entry);
	} else {
		_top_groups[entry->Id()] = entry;
		_top_entries[entry->Id()] = entry;
	}
	return true;
}

bool imRoster::AddGroup(imRosterGroup * entry, const string& g)
{
	imRosterGroup * pg = NULL;
	
	if (_groups.find(g) != _groups.end())
		pg = _groups[g];
		
	return AddGroup(entry, pg);
}

imRosterEntry * imRoster::Entry(const string& id)
{
	if (_entries.find(id) == _entries.end())
		return NULL;
	else
		return _entries[id];
}

imRosterItem * imRoster::Item(const string& id, bool allitems)
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

imRosterGroup * imRoster::Group(const string& id)
{
	if (_groups.find(id) == _groups.end())
		return NULL;
	else
		return _groups[id];
}

imRosterEntry * imRoster::TopEntry(const string& id)
{
	if (_top_entries.find(id) == _top_entries.end())
		return NULL;
	else
		return _top_entries[id];
}

imRosterItem * imRoster::TopItem(const string& id)
{
	if (_top_items.find(id) == _top_items.end())
		return NULL;
	else
		return _top_items[id];
}

imRosterGroup * imRoster::TopGroup(const string& id)
{
	if (_top_groups.find(id) == _top_groups.end())
		return NULL;
	else
		return _top_groups[id];
}

imRosterItem * imRoster::RemoveItem(const string& id)
{
	imRosterItem * item;
	map<string, imRosterGroup *>::iterator it1;

	item = Item(id);
	if (item == NULL)
		return NULL;
	
	it1 = item->InGroups()->begin();
	while (it1 != item->InGroups()->end()) {
		imRosterGroup * gr = it1->second;
		it1++;
		gr->RemoveItem(id);
	}
		
	if (TopItem(id) == item) {
		_top_items.erase(id);
		_top_entries.erase(id);
	}
	
	_items.erase(id);
	_entries.erase(id);
	_allitems.erase(id);
	
	return item;
}

imRosterGroup * imRoster::RemoveGroup(const string& id)
{
	imRosterGroup * item;
	map<string, imRosterGroup *>::iterator it1;

	item = Group(id);
	if (item == NULL)
		return NULL;
	
	it1 = item->InGroups()->begin();
	while (it1 != item->InGroups()->end()) {
		imRosterGroup * gr = it1->second;
		it1++;
		gr->RemoveGroup(id);
	}
		
	for (map<string, imRosterEntry *>::iterator it = item->Entries()->begin(); it != item->Entries()->end(); it++)
		it->second->RemoveFromGroup(id);
		
	if (TopGroup(id) == item) {
		_top_groups.erase(id);
		_top_entries.erase(id);
	}
	
	_groups.erase(id);
	_entries.erase(id);
	
	return item;
}

imRosterItem * imRoster::RemoveSubItem(const string& id)
{
	imRosterItem * item;
	
	if (_allitems.find(id) == _allitems.end())
		return NULL;
	else
		item = _allitems[id];
		
	_allitems.erase(id);
	_entries.erase(id);
		
	if (item->Parent() != NULL)
		return item->Parent()->RemoveSubItem(id);
	else
		return NULL;
}

};
