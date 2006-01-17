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
#include <map>
#include <onir/im/imRoster.h>
#include "jSession.h"
#include "jRosterItem.h"
#include "jMessageQueue.h"

using namespace std;

DEFINE_OOBJECT(jMessageQueue, imMessageQueue);

jMessageQueue::jMessageQueue(jSession * session)
: imMessageQueue(session)
{
	INIT_OOBJECT;
}

jMessageQueue::~jMessageQueue()
{
}

imMessageThread * jMessageQueue::GetThread(const string& type, const string& roster_id, const string& id)
{
	jRosterItem * ri;
	imMessageThread * th = NULL;

	ri = static_cast<jRosterItem *>(Session()->Roster()->Item(roster_id, true));
	if (ri != NULL) {
		th = static_cast<jSession *>(Session())->GetMessageThread(type, ri->Jid(), id);
	}
	return th;
}
