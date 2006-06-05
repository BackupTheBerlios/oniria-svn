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
#ifndef __OHANDLER_H
#define __OHANDLER_H

#include "onir_dll.h"

#include "oEventTarget.h"

namespace onir {

class oEvent;
	
/*!\class oHandler
 * \brief Base class for handlers.
 */
class LIBONIR_API oEventHandler : public oEventTarget {

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn oEventHandler()
		 * \brief Constructor.
		 */
		oEventHandler();

		/*!\fn virtual ~oEventHandler()
		 * \brief Destructor.
		 */
		virtual ~oEventHandler();
		//@}



		/*!\fn virtual bool processEvent(oEvent * event) = 0
		 * \brief Handles event.
		 * \param event Event.
		 * \return true if event manager should call next event handler in chain. 
		 *
		 * Override this method to implement your own event handler.
		 */
		virtual bool processEvent(oEvent * event) = 0;
};

};

#endif
