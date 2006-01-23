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
#ifndef __IMPROTOCOL_H
#define __IMPROTOCOL_H

#include "oim_dll.h"
#include <QObject>

namespace onirIM {

class imSession;

/*!\class imProtocol
 * \brief Base class for implementing IM protocols
 */
class LIBOIM_API imProtocol : public QObject {

	Q_OBJECT

	public:
		/*!\name Constructors and destructors
		 */
		//@{
		/*!\fn imProtocol()
		 * \brief Constructor
		 */
		imProtocol();
		//@}

		/*!\fn virtual QString protocolId() const = 0
		 * \brief Returns protocol id.
		 * \return Protocol id
		 * \sa onir::oOniria::RegisterProtocol()
		 *
		 * Returned id should be unique. Only one protocol with
		 * given id could exists.
		 */
		virtual QString protocolId() const = 0;

		/*!\fn virtual QString protocolName() const = 0
		 * \brief Returns protocol name.
		 * \return Protocol name
		 */
		virtual QString protocolName() const = 0;

		/*!\fn virtual QString protocolVersion() const = 0
		 * \brief Returns protocol version.
		 * \return Protocol version
		 */
		virtual QString protocolVersion() const = 0;

		/*!\fn virtual QString protocolDescription() const = 0
		 * \brief Returns protocol description.
		 * \return Protocol description
		 */
		virtual QString protocolDescription() const = 0;

		/*!\fn virtual imSession * createSession() = 0
		 * \brief Creates new session object.
		 * \param o Pointer to Oniria interface.
		 * \return Pointer to newly created session object.
		 */
		virtual imSession * createSession() = 0;
};



};

#endif
