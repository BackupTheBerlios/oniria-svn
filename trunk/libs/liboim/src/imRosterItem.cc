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
#include "imRosterItem.h"

namespace onirIM {

imRosterItem::imRosterItem(imSession * session, imRosterItem * parent)
	: imRosterEntry(session)
{
	_parent = parent;
	iconSet("roster");
	skinRoot("roster:item");
}

imRosterItem::~imRosterItem()
{
}

bool imRosterItem::addSubItem(imRosterItem * e)
{
	_subitems[e->id()] = e;
	e->parent(this);
	return true;
}

imRosterItem * imRosterItem::subItem(const QString& id)
{
	if (_subitems.find(id) == _subitems.end())
		return NULL;
	else
		return _subitems[id];
}

bool imRosterItem::fixedOrder(QVector<QString>& olist)
{
	// by default we don't want fixed order, so let's the oniria sort entries.
	return false;
}

imRosterItem * imRosterItem::removeSubItem(const QString& id)
{
	imRosterItem * item;
	
	item = subItem(id);
	if (item == NULL)
		return NULL;
		
	_subitems.remove(id);
	
	item->parent(NULL);
	
	return item;
}

};
