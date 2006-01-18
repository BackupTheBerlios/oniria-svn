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
#ifndef _CPTMD5_H
#define _CPTMD5_H

#include <QString>
#include <QObject>
#include <stdint.h>
#include "dll.h"
#include "cptHash.h"

namespace onirCrypt {

/*!\class cptMD5
 * \brief The MD5 Message-Digest Algorithm
 *
 * See <a href="http://www.faqs.org/rfcs/rfc1321.html">RFC 1321</a>
 */
class LIBOCRYPT_API cptMD5 : public cptHash {

	Q_OBJECT

	public:
		/*!\name Constructors and destructor.
		 */
		//@{

		/*!\fn cptMD5()
		 * \brief Constructor.
		 */
		cptMD5();
		//@}

		/*!\fn virtual QString compute(const uint8_t * msg, size_t sz)
		 * \brief Calculates MD5 sum of given message.
		 * \param msg Message MD5 sum to be calculated from.
		 * \param sz Message length in bytes.
		 * \return MD5 sum.
		 */
		virtual QString compute(const uint8_t * msg, size_t sz);

		/*!\fn virtual bool init()
		 * \brief Initializes hashing process
		 * \return true if ok.
		 */
		virtual bool init();

		/*!\fn virtual bool update(const uint8_t * msg, size_t sz)
		 * \brief Updates hashing process
		 * \param msg New data to hash.
		 * \param sz Size of data.
		 * \return true if ok.
		 */
		virtual bool update(const uint8_t * msg, size_t sz);

		/*!\overload virtual bool update(const QString& msg)
		 */
		virtual bool update(const QString& msg);

		/*!\fn virtual size_t finalize(uint8_t ** hash)
		 * \brief Ends hashing process.
		 * \param hash Pointer to pointer of hash.
		 * \return Size of hash in bytes.
		 */
		virtual size_t finalize(uint8_t ** hash);

		/*!\fn virtual size_t blockSize() const
		 * \brief Returns hash method block size in bytes. For MD5 it's always 64.
		 * \return Hash method block size (always 64).
		 */
		virtual size_t blockSize() const;

		/*!\fn virtual size_t hashSize() const
		 * \brief Returns hash size in bytes. For MD5 it's always 16.
		 * \return Hash size (always 16).
		 */
		virtual size_t hashSize() const;

	protected:
		void transform(const uint8_t * buf);

		uint32_t getUINT32(const uint8_t * src) const;
		void putUINT32(uint8_t * dst, uint32_t x) const;
		uint32_t rol(uint32_t x, uint32_t n) const;

		uint32_t F(uint32_t x, uint32_t y, uint32_t z) const;
		uint32_t G(uint32_t x, uint32_t y, uint32_t z) const;
		uint32_t H(uint32_t x, uint32_t y, uint32_t z) const;
		uint32_t I(uint32_t x, uint32_t y, uint32_t z) const;

		void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) const;
		void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) const;
		void HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) const;
		void II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) const;

	private:

		uint32_t _state[4];
		size_t _count[2];
		uint8_t _buf[64];
};

};

#endif
