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
#ifndef __IMMESSAGETHREADUI_H
#define __IMMESSAGETHREADUI_H

#include <QObject>
#include "oim_dll.h"

namespace onirIM {

class imMessageThread;
class imMessage;

/*!\class imMessageThreadUI
 * \brief Base class for various message interfaces.
 */
class LIBOIM_API imMessageThreadUI : public QObject {

	Q_OBJECT

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imMessageThreadUI()
		 * \brief Constructor
		 */
		imMessageThreadUI();

		/*!\fn virtual ~imMessageThreadUI()
		 * \brief Destructor.
		 */
		virtual ~imMessageThreadUI();
		/* @} */
		
		

		/*!\fn inline void thread(imMessageThread * th)
		 * \brief Sets message thread pointer.
		 * \param th Message thread pointer.
		 */
		inline void thread(imMessageThread * th) { _thread = th; };

		/*!\fn inline imMessageThread * thread() const
		 * \brief Returns pointer to message thread.
		 * \return Message thread pointer.
		 */
		inline imMessageThread * thread() const { return _thread; };
	
		/*!\fn virtual bool create() = 0
		 * \brief Creates UI (ie. creates window)
		 * \return true if ok.
		 */
		virtual bool create() = 0;

		/*!\fn virtual bool displayMessage(imMessage * msg, bool output = false) = 0
		 * \brief Displays message.
		 * \param msg Message to be displayed.
		 * \param output Flag indicating whether message should be displayed as output message.
		 * \return true if ok.
		 */
		virtual bool displayMessage(imMessage * msg, bool output = false) = 0;
	private:
		imMessageThread * _thread;
};



};

#endif
