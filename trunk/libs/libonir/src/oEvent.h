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
#ifndef __OEVENT_H
#define __OEVENT_H

#include "onir_dll.h"

#include <oxml/xmlElement.h>

using onirXML::xmlElement;

namespace onir {

/*!\class oEvent
 * \brief Event.
 */
class LIBONIR_API oEvent {

	public:
		/*!\name Contructors and destructor
		 */
		//@{

		/*!\fn oEvent(const QString& id)
		 * \brief Constructor.
		 * \param id Event id.
		 */
		oEvent(const QString& id);

		/*!\fn virtual ~oEvent()
		 * \brief Destructor.
		 */
		virtual ~oEvent();
		//@}
		


		/*!\fn inline const QString& id() const
		 * \brief Returns event id.
		 * \return Event id.
		 */
		inline const QString& id() const { return _id; };

		/*!\fn inline xmlElement * xml() const
		 * \brief Returns event XML data.
		 * \return Event XML data.
		 */
		inline xmlElement * xml() const { return _xml; };

	private:
		QString _id;
		xmlElement * _xml;
};

};

#endif
