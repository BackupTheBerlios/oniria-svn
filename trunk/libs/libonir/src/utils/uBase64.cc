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
#include "uBase64.h"

namespace onirUtils {

static const char * b64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

uBase64::uBase64()
{
}

size_t uBase64::decode(QByteArray * dst, const char * src, size_t len)
{
	size_t d_sz;
	if (len == 0)
		len = strlen(src);

	d_sz = len >> 2;
	d_sz *= 3;
	if (src[len - 1] == '=')
		d_sz--;
	if (src[len - 2] == '=') 
		d_sz--;


	dst->resize(d_sz);

	for (size_t i = 0, k = 0; i < len; i += 4, k += 3) {
		uint32_t triplet = 0;
		for (uint32_t j = 0; j < 64; j++) {
			if (src[i + 0] == b64_table[j])
				triplet |= ((j & 0x3f) << 18);
			if (src[i + 1] == b64_table[j])
				triplet |= ((j & 0x3f) << 12);
			if (src[i + 2] == b64_table[j])
				triplet |= ((j & 0x3f) <<  6);
			if (src[i + 3] == b64_table[j])
				triplet |= ((j & 0x3f) <<  0);
		}
		if (src[i + 2] != '=') {
			reinterpret_cast<uint8_t *>(dst->data())[k + 1] = static_cast<uint8_t>(triplet >> 8);
			if (src[i + 3] != '=')
				reinterpret_cast<uint8_t *>(dst->data())[k + 2] = static_cast<uint8_t>(triplet);
		}
		reinterpret_cast<uint8_t *>(dst->data())[k + 0] = static_cast<uint8_t>(triplet >> 16);
	}

	return len;
}

size_t uBase64::decode(QByteArray * dst, const QByteArray * src)
{
	return uBase64::decode(dst, src->data(), src->size());
}

size_t uBase64::decode(QByteArray * dst, const QString& src)
{
	QByteArray tmp = src.toLocal8Bit();
	return uBase64::decode(dst, &tmp);
}

QString uBase64::encode(const uint8_t * src, size_t len)
{
	QString enc;
	size_t enc_len, i, j;

	if (len == 0)
		len = strlen(reinterpret_cast<const char *>(src));

	enc_len = len / 3;
	if (len % 3 != 0)
		enc_len++;
	enc_len *= 4;
	enc.resize(enc_len);
	enc.fill('=');

	for (i = 0, j = 0; i < len - (len % 3); i += 3, j += 4) {
		uint32_t triplet = 0;

		triplet |= src[i + 0] << 16;
		triplet |= src[i + 1] << 8;
		triplet |= src[i + 2] << 0;

		enc[j + 0] = b64_table[(triplet >> 18) & 0x3f];
		enc[j + 1] = b64_table[(triplet >> 12) & 0x3f];
		enc[j + 2] = b64_table[(triplet >>  6) & 0x3f];
		enc[j + 3] = b64_table[(triplet >>  0) & 0x3f];
	}

	if (len > i) {
		uint32_t triplet = 0;
		triplet |= src[i + 0] << 16;
		if (len - i == 2)
			triplet |= src[i + 1] << 8;
		enc[j + 0] = b64_table[(triplet >> 18) & 0x3f];
		enc[j + 1] = b64_table[(triplet >> 12) & 0x3f];
		if (len - i == 2)
			enc[j + 2] = b64_table[(triplet >>  6) & 0x3f];
	}

	return enc;
}

QString uBase64::encode(const char * src, size_t len)
{
	return encode(reinterpret_cast<const uint8_t *>(src), len);
}

QString uBase64::encode(const QString& src)
{
	QByteArray tmp = src.toLocal8Bit();
	return encode(&tmp);
}

QString uBase64::encode(QByteArray * src)
{
	return encode(src->data(), src->size());
}

};
