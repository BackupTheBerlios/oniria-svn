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
#include <map>
#include "jSession.h"
#include "jRosterItem.h"
#include "jRosterSubItem.h"

jRosterItem::jRosterItem(jSession * session, jRosterItem * parent)
: imRosterItem(session, parent)
{
}

jRosterItem::~jRosterItem()
{
}

bool jRosterItem::fixedOrder(QVector<QString>& olist)
{
	QMultiMap<unsigned int, QString> order;
	for (QMap<QString, imRosterItem *>::iterator it = subItems()->begin(); it != subItems()->end(); it++)
		order.insert(static_cast<jRosterSubItem *>(it.value())->priority(), it.value()->id());
	for (QMultiMap<unsigned int, QString>::iterator it = order.begin(); it != order.end(); it++)
		olist.push_front(it.value());
	return true;
}
