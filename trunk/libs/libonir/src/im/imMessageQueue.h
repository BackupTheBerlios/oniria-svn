/* $Id: imMessageQueue.h 608 2005-10-07 09:57:23Z choman $ */
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

#include <map>
#include "../dll.h"
#include "../oObject.h"

using std::map;
using onir::oObject;

namespace onirIM {

class imSession;
class imMessageThread;

/*!\class imMessageQueue
 * \brief Message queue.
 */
class LIBONIR_API imMessageQueue : public oObject {

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
		
		

		/*!\fn inline imSession * Session() const
		 * \brief Returns session pointer.
		 * \return Session pointer.
		 */
		inline imSession * Session() const { return _session; };



		/*!\name Thread methods
		 * @{
		 */
		
		virtual imMessageThread * GetThread(const string& type, const string& roster_id, const string& id = "") = 0;
		
		/*!\fn virtual bool AddThread(imMessageThread * th)
		 * \brief Adds thread to message queue.
		 * \param th Thread.
		 * \return true if ok.
		 */
		virtual bool AddThread(imMessageThread * th);
		
		/*!\fn virtual imMessageThread * FindThread(const string& id)
		 * \brief Finds thread.
		 * \param id Thread id.
		 * \return Thread pointer or \c NULL if not found.
		 */
		virtual imMessageThread * FindThread(const string& id);
		
		inline map<string, imMessageThread *> * Threads() { return &_threads; };
		/* @} */
	
	private:
		imSession * _session;
		map<string, imMessageThread *> _threads;

		DECLARE_OOBJECT;
};



};

#endif
