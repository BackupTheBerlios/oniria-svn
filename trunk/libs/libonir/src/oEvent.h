/* $Id: oEvent.h 608 2005-10-07 09:57:23Z choman $ */
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

#include "dll.h"

#include <string>
#include "oObject.h"
#include "xml/xmlElement.h"

using std::string;
using onirXML::xmlElement;

namespace onir {

/*!\class oEvent
 * \brief Event.
 */
class LIBONIR_API oEvent : public oObject {

	public:
		/*!\name Contructors and destructor
		 */
		//@{

		/*!\fn oEvent(const string& id)
		 * \brief Constructor.
		 * \param id Event id.
		 */
		oEvent(const string& id);

		/*!\fn virtual ~oEvent()
		 * \brief Destructor.
		 */
		virtual ~oEvent();
		//@}
		


		/*!\fn inline const string& Id() const
		 * \brief Returns event id.
		 * \return Event id.
		 */
		inline const string& Id() const { return _id; };

		/*!\fn inline xmlElement * XML() const
		 * \brief Returns event XML data.
		 * \return Event XML data.
		 */
		inline xmlElement * XML() const { return _xml; };

	private:
		string _id;
		xmlElement * _xml;

		DECLARE_OOBJECT;
};

};

#endif
