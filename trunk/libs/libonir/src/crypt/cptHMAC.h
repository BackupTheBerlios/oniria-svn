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
#ifndef _CPTHMAC_H
#define _CPTHMAC_H

#include <QString>
#include <stdint.h>
#include "../dll.h"

using onir::oObject;
using namespace std;

namespace onirCrypt {

class cptHash;

/*!\class cptHMAC
 * \brief HMAC: Keyed-Hashing for Message Authentication
 *
 * See <a href="http://www.faqs.org/rfcs/rfc2104.html">RFC 2104</a>
 */
class LIBONIR_API cptHMAC : public oObject {

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn cptHMAC(cptHash * hash = NULL)
		 * \brief Constructor.
		 * \param Hash algorith to use. If NULL then MD5 will be used.
		 */
		cptHMAC(cptHash * hash = NULL);

		/*!\fn virtual ~cptHMAC()
		 * \brief Destructor.
		 */
		virtual ~cptHMAC();
		//@}

		/*!\fn virtual QString compute(const uint8_t * msg, size_t msg_sz, const uint8_t * key, size_t key_sz)
		 * \brief Calculates HMAC  of given message.
		 * \param msg Message.
		 * \param msg_sz Size of message.
		 * \param key Key.
		 * \param key_sz Size of key.
		 * \return HMAC value.
		 */
		virtual QString compute(const uint8_t * msg, size_t msg_sz, const uint8_t * key, size_t key_sz);

		/*!\fn virtual QString compute(uint8_t ** hmac, const uint8_t * msg, size_t msg_sz, const uint8_t * key, size_t key_sz)
		 * \brief Calculates HMAC of given message.
		 * \param hmac Pointer to pointer to buffer with calculated HMAC.
		 * \param msg Message.
		 * \param msg_sz Size of message.
		 * \param key Key.
		 * \param key_sz Size of key.
		 * \return Size of HMAC value.
		 */
		virtual size_t compute(uint8_t ** hmac, const uint8_t * msg, size_t msg_sz, const uint8_t * key, size_t key_sz);

		/*!\overload virtual QString compute(const QString& msg, const QString& key)
		 */
		virtual QString compute(const QString& msg, const QString& key);

	protected:

		cptHash * _hash;

		DECLARE_OOBJECT;
};

};

#endif
