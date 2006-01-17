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
#if defined(HAVE_CONFIG_H)
# include <config.h>
#endif
#include <cstring>
#include <stdint.h>
#include "uBase16.h"

namespace onirUtils {

static const char * b16_table_uc = "0123456789ABCDEF";
static const char * b16_table_lc = "0123456789abcdef";

uBase16::uBase16()
{
}

size_t uBase16::decode(QByteArray * dst, const char * src, size_t len, bool lc)
{
	size_t d_sz;
	const char * b16_table;

	if (lc)
		b16_table = b16_table_lc;
	else
		b16_table = b16_table_uc;

	if (len == 0)
		len = strlen(src);

	d_sz = len >> 1;

	dst->resize(d_sz);

	for (size_t i = 0, k = 0; i < len; i += 2, k += 1) {
		uint8_t byte = 0;
		for (uint32_t j = 0; j < 16; j++) {
			if (src[i + 0] == b16_table[j])
				byte |= ((j & 0xf) << 4);
			if (src[i + 1] == b16_table[j])
				byte |= ((j & 0xf) << 0);
		}
		reinterpret_cast<uint8_t *>(dst->data())[k] = byte;
	}

	return len;
}

size_t uBase16::decode(QByteArray * dst, const QByteArray * src, bool lc)
{
	return uBase16::decode(dst, src->data(), src->size(), lc);
}

size_t uBase16::decode(QByteArray * dst, const QString& src, bool lc)
{
	QByteArray tmp = src.toLocal8Bit();
	return uBase16::decode(dst, &tmp, lc);
}

QString uBase16::encode(const uint8_t * src, size_t len, bool lc)
{
	QString enc;
	size_t enc_len, i, j;
	const char * b16_table;

	if (lc)
		b16_table = b16_table_lc;
	else
		b16_table = b16_table_uc;

	if (len == 0)
		len = strlen(reinterpret_cast<const char *>(src));

	enc_len = len << 1;
	enc.resize(enc_len);

	for (i = 0, j = 0; i < len; i += 1, j += 2) {
		enc[j + 0] = b16_table[(src[i] >> 4) & 0xf];
		enc[j + 1] = b16_table[(src[i] >> 0) & 0xf];
	}

	return enc;
}

QString uBase16::encode(const char * src, size_t len, bool lc)
{
	return encode(reinterpret_cast<const char *>(src), len, lc);
}

QString uBase16::encode(const QString& src, bool lc)
{
	QByteArray tmp = src.toLocal8Bit();
	return encode(&tmp, lc);
}

QString uBase16::encode(QByteArray * src, bool lc)
{
	return encode(src->data(), src->size(), lc);
}

};
