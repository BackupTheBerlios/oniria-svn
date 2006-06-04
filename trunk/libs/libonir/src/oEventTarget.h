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
#ifndef __OEVENTTARGET_H
#define __OEVENTTARGET_H

#include "onir_dll.h"

#include <string>
#include "oEvent.h"

using std::string;
using onir::oEvent;

namespace onir {

/*!\class oEventTarget
 * \brief Event target.
 * \sa oEvent, oEventHandler
 *
 * To implement your own event handler, use rather oEventHandler than this class.
 */
class LIBONIR_API oEventTarget : public oObject {

	public:
		/*!\name Contructors and destructor
		 */
		//@{

		/*!\fn oEventTarget()
		 * \brief Constructor.
		 */
		oEventTarget();

		/*!\fn virtual ~oEventTarget()
		 * \brief Destructor.
		 */
		virtual ~oEventTarget();
		//@}
		


		/*!\fn virtual bool ProcessEvent(oEvent * event)
		 * \brief Process event.
		 * \param event Event.
		 * \return true if event manager should call next event handler in chain. 
		 *
		 * Override this method to implement your own event processing method.
		 */
		virtual bool ProcessEvent(oEvent * event) = 0;


	private:

		DECLARE_OOBJECT;
};

#define ROUTE_EVENT(__event, __id, __func)	\
	if ((__event)->Id() == (__id))		\
		return __func(event);

};

#endif
