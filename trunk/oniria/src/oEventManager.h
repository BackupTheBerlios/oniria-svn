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
#ifndef __OEVENTMANAGER_H
#define __OEVENTMANAGER_H

#include <QString>
#include <QMap>
#include <QList>
#include <onir/oEventQueue.h>
#include <onir/oEventHandler.h>

using onir::oEvent;
using onir::oEventHandler;
using onir::oEventQueue;

class oApplication;

class oEventManager : public oEventQueue {

	Q_OBJECT;

	public:
		oEventManager(oApplication * app);
		virtual ~oEventManager();

		bool registerHandler(const QString& id, oEventHandler * hnd);
		virtual bool process(oEvent * event);
		virtual bool queue(oEvent * event);

		const QList<oEventHandler *>& handlerChain(const QString& action);

	public slots:
		void processQueue();


	private:
		oApplication * _app;
		QMap<QString, QList<oEventHandler *> > _handlers;
		QMap<oEventHandler *, oEventHandler *> _m_handlers;	// should be QSet, but Qt set sucks a bit.
		QList<oEvent *> _queue;
};

#endif
