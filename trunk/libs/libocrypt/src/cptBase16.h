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
#ifndef __CPTBASE16_H
#define __CPTBASE16_H

#include "dll.h"

#include <QString>
#include <QByteArray>
#include <QObject>
#include <stdint.h>

namespace onirCrypt {

/*!\class cptBase16
 * \brief Base16 encoder and decoder.
 */
class LIBOCRYPT_API cptBase16 {
	public:
		
		/*!\name Decoding
		 */
		//@{

		/*!\fn static size_t decode(QByteArray * dst, const char * src, size_t len = 0, bool lc = false)
		 * \brief Decodes Base16 encoded buffer.
		 * \param dst Destination buffer.
		 * \param src Buffer with encoded data.
		 * \param len Length of source encoded data. If 0, size of encoded data is computed
		 * by calling strlen(src).
		 * \param lc If true, lower case characters will be used. Note, that this isn't 
		 * fully Base16 compliant, but may be usefull.
		 * \return Length of decoded data.
		 */
		static size_t decode(QByteArray * dst, const char * src, size_t len = 0, bool lc = false);

		/*!\overload static size_t decode(QByteArray * dst, const QString& src, bool lc = false)
		 */
		static size_t decode(QByteArray * dst, const QString& src, bool lc = false);

		/*!\overload static size_t decode(QByteArray * dst, const QByteArray * src, bool lc = false)
		 */
		static size_t decode(QByteArray * dst, const QByteArray * src, bool lc = false);
		//@}



		/*!\name Encoding
		 */
		//@{

		/*!\fn static QString encode(const uint8_t * src, size_t len = 0, bool lc = false)
		 * \brief Encodes data using Base16.
		 * \param src Source buffer.
		 * \param len Length of source buffer. If 0, size of buffer is computed
		 * using strlen().
		 * \param lc If true, lower case characters will be used. Note, that this isn't 
		 * \return Encoded data.
		 */
		static QString encode(const uint8_t * src, size_t len = 0, bool lc = false);

		/*!\overload static QString encode(const char * src, size_t len = 0, bool lc = false)
		 */
		static QString encode(const char * src, size_t len = 0, bool lc = false);

		/*!\overload static QString encode(const QString& src, bool lc = false)
		 */
		static QString encode(const QString& src, bool lc = false);

		/*!\overload static QString encode(QByteArray * src, bool lc = false)
		 */
		static QString encode(QByteArray * src, bool lc = false);
		//@}

	protected:
		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn cptBase16()
		 * \brief Protected constructor.
		 *
		 * Don't instantiate this class.
		 */
		cptBase16();
		//@}

		/*!\name Buffer operations
		 */
		//@{

};

};

#endif
