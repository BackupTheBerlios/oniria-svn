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
#include <QtDebug>
#include <onir/oEvent.h>
#include "oEventManager.h"

oEventManager::oEventManager(oApplication * app)
{
	_app = app;
}

oEventManager::~oEventManager()
{
	for (QList<oEvent *>::iterator it = _queue.begin(); it != _queue.end(); it++)
		delete *it;
	for (QMap<oEventHandler *, oEventHandler *>::iterator i = _m_handlers.begin(); i != _m_handlers.end(); i++)
		delete i.key();
}

bool oEventManager::registerHandler(const QString& id, oEventHandler * hnd)
{
	_handlers[id].push_back(hnd);
	_m_handlers.insert(hnd, hnd);
	qDebug() << "oEventManager::registerHandler(): Registered handler for event" << id;
	return true;
}

bool oEventManager::process(oEvent * event)
{
	if (_handlers.find(event->id()) != _handlers.end()) {
		qDebug() << "oEventManager::process(): Processing event" << event->id() << " handlers:" << _handlers[event->id()].size();
		for (QList<oEventHandler *>::iterator it = _handlers[event->id()].begin(); it != _handlers[event->id()].end(); it++)
			if (!(*it)->processEvent(event))
				break;
	}
	delete event;
	return true;
}

bool oEventManager::queue(oEvent * event)
{
	qDebug() << "oEventManager::queue(): Queued event" << event->id();
	_queue.push_back(event);
	return true;
}

void oEventManager::processQueue()
{
	while (!_queue.empty()) {
		process(_queue.front());
		_queue.pop_front();
	}
}

