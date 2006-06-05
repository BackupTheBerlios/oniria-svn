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
#ifndef __OEVENTFORWARDER_H
#define __OEVENTFORWARDER_H

#include "onir_dll.h"

#include "oEventHandler.h"

namespace onir {

class oEvent;
class oEventTarget;
	
/*!\class oEventForwarder
 * \brief Event handler which forwards event to another event target.
 */
class LIBONIR_API oEventForwarder : public oEventHandler {

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn oEventForwarder(oEventTarget * target)
		 * \brief Constructor.
		 * \param target Event target to forward event to.
		 */
		oEventForwarder(oEventTarget * target);

		/*!\fn virtual ~oEventForwarder()
		 * \brief Destructor.
		 */
		virtual ~oEventForwarder();
		//@}



		/*!\fn virtual bool ProcessEvent(oEvent * event)
		 * \brief Prcess event.
		 * \param event Event.
		 * \return true if event manager should call next event handler in chain.
		 *
		 * Forwards event to another event target.
		 */
		virtual bool processEvent(oEvent * event);

	private:
		oEventTarget * _target;
};

};

#endif
