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
#include <QTextStream>
#include "cptHash.h"
#include "cptMD5.h"
#include "cptHMAC.h"

namespace onirCrypt {

cptHMAC::cptHMAC(cptHash * hash)
{
	if (hash == NULL)
		hash = new cptMD5();
	_hash = hash;
}

cptHMAC::~cptHMAC()
{
	delete _hash;
}

size_t cptHMAC::compute(uint8_t ** hmac, const uint8_t * msg, size_t msg_sz, const uint8_t * key, size_t key_sz)
{
	uint8_t * padded_key;
	uint8_t * ipad;
	uint8_t * opad;
	uint8_t * h_ipad;
	size_t hmac_sz;

	padded_key = new uint8_t[_hash->blockSize()];
	ipad = new uint8_t[_hash->blockSize()];
	opad = new uint8_t[_hash->blockSize()];
	memset(padded_key, 0, _hash->blockSize());

	if (key_sz > _hash->blockSize()) {	// hash the key first
		uint8_t * hashed_key;
		size_t hsz;

		_hash->init();
		_hash->update(key, key_sz);
		hsz = _hash->finalize(&hashed_key);
		memcpy(padded_key, hashed_key, hsz);
		delete hashed_key;
	} else {				// copy key directly
		memcpy(padded_key, key, key_sz);
	}

	for (size_t i = 0; i < _hash->blockSize(); i++) {
		ipad[i] = padded_key[i] ^ 0x36;	// K XOR ipad
		opad[i] = padded_key[i] ^ 0x5c;	// K XOR opad
	}

	_hash->init();
	_hash->update(ipad, _hash->blockSize());
	_hash->update(msg, msg_sz);
	_hash->finalize(&h_ipad);		// H(K XOR ipad, msg)

	_hash->init();
	_hash->update(opad, _hash->blockSize());
	_hash->update(h_ipad, _hash->hashSize());
	hmac_sz = _hash->finalize(hmac);	// H(K XOR opad, H(K XOR ipad, msg))

	delete padded_key;
	delete ipad;
	delete opad;
	delete h_ipad;
	return hmac_sz;
}

QString cptHMAC::compute(const uint8_t * msg, size_t msg_sz, const uint8_t * key, size_t key_sz)
{
	QTextStream ss;
	uint8_t * hmac;
	size_t hmac_sz;

	hmac_sz = compute(&hmac, msg, msg_sz, key, key_sz);
	for (size_t i = 0; i < hmac_sz; i++)
		ss << hex << qSetPadChar('0') << qSetFieldWidth(2) << static_cast<uint32_t>(hmac[i]);
	delete hmac;

	return ss.readAll();
}

QString cptHMAC::compute(const QString& msg, const QString& key)
{
	QByteArray tmpm, tmpk;
	tmpm = msg.toLocal8Bit();
	tmpk = key.toLocal8Bit();
	return compute(reinterpret_cast<const uint8_t *>(tmpm.data()), tmpm.size(),
			reinterpret_cast<const uint8_t *>(tmpk.data()), tmpk.size());
}

};

