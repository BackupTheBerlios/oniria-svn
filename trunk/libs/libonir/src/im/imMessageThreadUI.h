/* $Id: imMessageThreadUI.h 608 2005-10-07 09:57:23Z choman $ */
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

#include "../dll.h"
#include "../oObject.h"
#include "../oOniria.h"

using onir::oObject;
using onir::oOniria;

namespace onirIM {

class imMessageThread;
class imMessage;

/*!\class imMessageThreadUI
 * \brief Base class for various message interfaces.
 */
class LIBONIR_API imMessageThreadUI : public oObject {

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imMessageThreadUI(oOniria * o)
		 * \brief Constructor
		 * \param o oOniria pointer.
		 */
		imMessageThreadUI(oOniria * o);

		/*!\fn virtual ~imMessageThreadUI()
		 * \brief Destructor.
		 */
		virtual ~imMessageThreadUI();
		/* @} */
		
		

		/*!\fn inline oOniria * Oniria() const
		 * \brief Returns pointer to Oniria interface.
		 * \return Pointer to Oniria interface.
		 */
		inline oOniria * Oniria() const { return _oniria; };

		/*!\fn inline void Thread(imMessageThread * th)
		 * \brief Sets message thread pointer.
		 * \param th Message thread pointer.
		 */
		inline void Thread(imMessageThread * th) { _thread = th; };

		/*!\fn inline imMessageThread * Thread() const
		 * \brief Returns pointer to message thread.
		 * \return Message thread pointer.
		 */
		inline imMessageThread * Thread() const { return _thread; };
	
		/*!\fn virtual bool Create() = 0
		 * \brief Creates UI (ie. creates window)
		 * \return true if ok.
		 */
		virtual bool Create() = 0;

		/*!\fn virtual bool DisplayMessage(imMessage * msg, bool output = false) = 0
		 * \brief Displays message.
		 * \param msg Message to be displayed.
		 * \param output Flag indicating whether message should be displayed as output message.
		 * \return true if ok.
		 */
		virtual bool DisplayMessage(imMessage * msg, bool output = false) = 0;
	private:
	
		oOniria * _oniria;
		imMessageThread * _thread;
	
		DECLARE_OOBJECT;
};



};

#endif
