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
#ifndef __CPTBASE64_H
#define __CPTBASE64_H

#include "dll.h"

#include <QString>
#include <QByteArray>

namespace onirCrypt {

/*!\class cptBase64
 * \brief Base64 encoder and decoder.
 */
class LIBOCRYPT_API cptBase64 {
	
	public:
		
		/*!\name Decoding
		 */
		//@{

		/*!\fn static size_t decode(QByteArray * dst, const char * src, size_t len = 0)
		 * \brief Decodes Base64 encoded buffer.
		 * \param dst Destination buffer.
		 * \param src Buffer with encoded data.
		 * \param len Length of source encoded data. If 0, size of encoded data is computed
		 * by calling strlen(src).
		 * \return Length of decoded data.
		 */
		static size_t decode(QByteArray * dst, const char * src, size_t len = 0);

		/*!\overload static size_t decode(QByteArray * dst, const QString& src)
		 */
		static size_t decode(QByteArray * dst, const QString& src);

		/*!\overload static size_t decode(QByteArray * dst, const QByteArray * src)
		 */
		static size_t decode(QByteArray * dst, const QByteArray * src);
		//@}



		/*!\name Encoding
		 */
		//@{

		/*!\fn static QString encode(const uint8_t * src, size_t len = 0)
		 * \brief Encodes data using Base64.
		 * \param src Source buffer.
		 * \param len Length of source buffer. If 0, size of buffer is computed
		 * using strlen().
		 * \return Encoded data.
		 */
		static QString encode(const uint8_t * src, size_t len = 0);
		
		/*!\overload static QString encode(const char * src, size_t len = 0)
		 */
		static QString encode(const char * src, size_t len = 0);

		/*!\overload static QString encode(const QString& src)
		 */
		static QString encode(const QString& src);

		/*!\overload static QString encode(QByteArray * src)
		 */
		static QString encode(QByteArray * src);
		//@}

	protected:
		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn cptBase64()
		 * \brief Protected constructor.
		 *
		 * Don't instantiate this class.
		 */
		cptBase64();
		//@}

		/*!\name Buffer operations
		 */
		//@{

};

};

#endif
