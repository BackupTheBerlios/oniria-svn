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
#include <onir/oEvent.h>
#include "oEventManager.h"

using namespace std;

oEventManager::oEventManager(gApp * app)
{
	_app = app;
}

oEventManager::~oEventManager()
{
	for (list<oEvent *>::iterator it = _queue.begin(); it != _queue.end(); it++)
		delete *it;
	for (set<oEventHandler *>::iterator i = _s_handlers.begin(); i != _s_handlers.end(); i++)
		delete *i;
}

bool oEventManager::RegisterHandler(const string& id, oEventHandler * hnd)
{
	_handlers[id].push_back(hnd);
	_s_handlers.insert(hnd);
	wxLogVerbose("oEventManager: Registered handler for event %s.", id.c_str());
	return true;
}

bool oEventManager::Process(oEvent * event)
{
	if (_handlers.find(event->Id()) != _handlers.end()) {
		wxLogVerbose("oEventManager: Processing event %s, handlers: %d", event->Id().c_str(), _handlers[event->Id()].size());
		for (list<oEventHandler *>::iterator it = _handlers[event->Id()].begin(); it != _handlers[event->Id()].end(); it++)
			if (!(*it)->ProcessEvent(event))
				break;
	}
	delete event;
	return true;
}

bool oEventManager::Queue(oEvent * event)
{
	wxLogVerbose("oEventManager: Queued event %s.", event->Id().c_str());
	_queue.push_back(event);
	return true;
}

void oEventManager::ProcessQueue()
{
	while (!_queue.empty()) {
		Process(_queue.front());
		_queue.pop_front();
	}
}

