/* $Id: saslCallback.h 635 2006-01-03 13:14:09Z choman $ */
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
#ifndef __SASLCALLBACK_H
#define __SASLCALLBACK_H

#include <QString>
#include <QByteArray>
#include "../dll.h"
#include "../oObject.h"

using onir::oObject;

namespace onirSASL {

/*!\class saslCallback
 * \brief SASL callback, used by saslMechanism to obtain specific
 * informations.
 */
class LIBONIR_API saslCallback : public oObject {

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn saslCallback()
		 * \brief Constructor.
		 */
		saslCallback();
		//@}

		/*!\fn virtual QByteArray * property(const QString& name)
		 * \brief Called by saslMechanism to obtain missing properties.
		 * \param name Property name.
		 * \return Callback should return property value or NULL.
		 */
		virtual QByteArray * property(const QString& name);

		DECLARE_OOBJECT;
};



};

#endif
