/* $Id: jRosterItem.cc 629 2006-01-02 11:20:46Z choman $ */
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
#include <map>
#include "jSession.h"
#include "jRosterItem.h"
#include "jRosterSubItem.h"

using namespace std;

DEFINE_OOBJECT(jRosterItem, imRosterItem);

jRosterItem::jRosterItem(jSession * session, jRosterItem * parent)
: imRosterItem(session, parent)
{
	INIT_OOBJECT;
}

jRosterItem::~jRosterItem()
{
}

bool jRosterItem::FixedOrder(vector<string>& olist)
{
	multimap<unsigned int, string> order;
	for (map<string, imRosterItem *>::iterator it = SubItems()->begin(); it != SubItems()->end(); it++)
		order.insert(make_pair(static_cast<jRosterSubItem *>(it->second)->Priority(), it->second->Id()));
	for (multimap<unsigned int, string>::reverse_iterator it = order.rbegin(); it != order.rend(); it++)
		olist.push_back(it->second);
	return true;
}
