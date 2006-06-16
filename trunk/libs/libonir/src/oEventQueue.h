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
#ifndef __OEVENTQUEUE_H
#define __OEVENTQUEUE_H

#include "onir_dll.h"

#include <QObject>
#include <QString>

namespace onir {

class oEvent;
class oEventHandler;

/*!\class oEventQueue
 * \brief Event queue.
 */
class LIBONIR_API oEventQueue : public QObject {

		Q_OBJECT;

	public:
		/*!\name Contructors and destructor
		 */
		//@{

		/*!\fn oEventQueue()
		 * \brief Constructor.
		 */
		oEventQueue();

		/*!\fn virtual ~oEventQueue()
		 * \brief Destructor.
		 */
		virtual ~oEventQueue();
		//@}


		/*!\fn virtual bool registerHandler(const QString& id, oEventHandler * hnd) = 0
		 * \brief Registers new event handler.
		 * \param id Event id.
		 * \param hnd Handler for given event.
		 * \return true if registration successful, false otherwise.
		 * \sa oEventHandler
		 *
		 * Plugins should call this method to register new event handler.
		 */
		virtual bool registerHandler(const QString& id, oEventHandler * hnd) = 0;

		/*!\fn virtual bool process(oEvent * event) = 0
		 * \brief Process event.
		 * \param event Event.
		 * \return true if ok
		 * \sa Queue()
		 *
		 * This method process event immediately, and returns when event handling
		 * finished. If possible, you should rather use Queue() than this method.
		 */
		virtual bool process(oEvent * event) = 0;

		/*!\fn virtual bool queue(oEvent * event) = 0
		 * \brief Queues event for processing.
		 * \param event Event.
		 * \return true if ok.
		 * \sa Process()
		 *
		 * Queued event will be processed in next event handling cycle.
		 */
		virtual bool queue(oEvent * event) = 0;
};

};

#endif

