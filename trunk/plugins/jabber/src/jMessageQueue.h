/* $Id: jMessageQueue.h 581 2005-09-21 13:15:47Z choman $ */
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
#ifndef __JMESSAGEQUEUE_H
#define __JMESSAGEQUEUE_H

#include <onir/im/imMessageQueue.h>
#include <onir/im/imMessageThread.h>

using namespace std;
using onirIM::imMessageQueue;
using onirIM::imMessageThread;
class jSession;

class jMessageQueue : public imMessageQueue {

	public:
		jMessageQueue(jSession * session);
		virtual ~jMessageQueue();

		virtual imMessageThread * GetThread(const string& type, const string& roster_id, const string& id = "");
	private:

		DECLARE_OOBJECT;

};

#endif
