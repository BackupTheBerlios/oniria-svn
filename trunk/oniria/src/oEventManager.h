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
#ifndef __OEVENTMANAGER_H
#define __OEVENTMANAGER_H

#include <map>
#include <string>
#include <list>
#include <set>
#include <onir/oEventQueue.h>
#include <onir/oEventHandler.h>

using std::map;
using std::string;
using std::list;
using std::set;
using onir::oEvent;
using onir::oEventHandler;
using onir::oEventQueue;

class gApp;

class oEventManager : public oEventQueue {
	public:
		oEventManager(gApp * app);
		virtual ~oEventManager();

		bool RegisterHandler(const string& id, oEventHandler * hnd);
		virtual bool Process(oEvent * event);
		virtual bool Queue(oEvent * event);

		void ProcessQueue();

		const list<oEventHandler *>& HandlerChain(const string& action);

	private:
		gApp * _app;
		map<string, list<oEventHandler *> > _handlers;
		set<oEventHandler *> _s_handlers;
		list<oEvent *> _queue;
};

#endif
