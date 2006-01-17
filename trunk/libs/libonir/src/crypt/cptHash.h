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
#ifndef _CPTHASH_H
#define _CPTHASH_H

#include <QString>
#include <stdint.h>
#include "../dll.h"
#include "../oObject.h"

using onir::oObject;

namespace onirCrypt {

/*!\class cptHash
 * \brief Base class for hashing algorithms (ie MD5, SHA-1)
 */
class LIBONIR_API cptHash : public oObject {

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn cptHash()
		 * \brief constructor.
		 */
		cptHash();
		//@}

		/*!\fn virtual QString compute(const uint8_t * msg, size_t sz) = 0
		 * \brief Calculates hash of given message.
		 * \param msg Message to be hashed.
		 * \param sz Message length in bytes.
		 * \return Hash value.
		 */
		virtual QString compute(const uint8_t * msg, size_t sz) = 0;

		/*!\overload virtual QString compute(const QString& msg)
		 */
		virtual QString compute(const QString& msg);

		/*!\fn virtual bool init() = 0
		 * \brief Initializes hashing process
		 * \return true if ok.
		 */
		virtual bool init() = 0;

		/*!\fn virtual bool update(const uint8_t * msg, size_t sz) = 0
		 * \brief Updates hashing process
		 * \param msg New data to hash.
		 * \param sz Size of data.
		 * \return true if ok.
		 */
		virtual bool update(const uint8_t * msg, size_t sz) = 0;

		/*!\fn virtual size_t finalize(uint8_t ** hash)
		 * \brief Ends hashing process.
		 * \param hash Pointer to pointer of hash.
		 * \return Size of hash in bytes.
		 */
		virtual size_t finalize(uint8_t ** hash) = 0;

		/*!\fn virtual size_t blockSize() const = 0
		 * \brief Returns hash method block size in bytes (ie. for MD5 it returns 64)
		 * \return Hash method block size.
		 */
		virtual size_t blockSize() const = 0;

		/*!\fn virtual size_t hashSize() const = 0
		 * \brief Returns hash size in bytes (ie. for MD5 it returns 16)
		 * \return Hash size.
		 */
		virtual size_t hashSize() const = 0;

	private:

		DECLARE_OOBJECT;
};

};

#endif
