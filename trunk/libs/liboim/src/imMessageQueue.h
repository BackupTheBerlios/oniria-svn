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
#ifndef __IMMESSAGEQUEUE_H
#define __IMMESSAGEQUEUE_H

#include <QMap>
#include <QObject>
#include <QString>
#include "oim_dll.h"

namespace onirIM {

class imSession;
class imMessageThread;

/*!\class imMessageQueue
 * \brief Message queue.
 */
class LIBOIM_API imMessageQueue : public QObject {

	Q_OBJECT

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imMessageQueue(imSession * session)
		 * \brief Constructor
		 * \param session Session pointer.
		 */
		imMessageQueue(imSession * session);

		/*!\fn virtual ~imMessageQueue()
		 * \brief Destructor.
		 */
		virtual ~imMessageQueue();
		/* @} */
		
		

		/*!\fn inline imSession * session() const
		 * \brief Returns session pointer.
		 * \return Session pointer.
		 */
		inline imSession * session() const { return _session; };



		/*!\name Thread methods
		 * @{
		 */
		
		virtual imMessageThread * getThread(const QString& type, const QString& roster_id, const QString& id = "") = 0;
		
		/*!\fn virtual bool addThread(imMessageThread * th)
		 * \brief Adds thread to message queue.
		 * \param th Thread.
		 * \return true if ok.
		 */
		virtual bool addThread(imMessageThread * th);
		
		/*!\fn virtual imMessageThread * findThread(const QString& id)
		 * \brief Finds thread.
		 * \param id Thread id.
		 * \return Thread pointer or \c NULL if not found.
		 */
		virtual imMessageThread * findThread(const QString& id);
		
		inline QMap<QString, imMessageThread *> * threads() { return &_threads; };
		/* @} */
	
	private:
		imSession * _session;
		QMap<QString, imMessageThread *> _threads;
};



};

#endif
