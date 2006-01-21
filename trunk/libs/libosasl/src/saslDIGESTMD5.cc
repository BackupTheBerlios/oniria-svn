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
#include <QRegExp>
#include <ocrypt/cptMD5.h>
#include <ocrypt/cptBase16.h>
#include "saslCallback.h"
#include "saslDIGESTMD5.h"

using onirCrypt::cptMD5;
using onirCrypt::cptBase16;

namespace onirSASL {

saslDIGESTMD5::saslDIGESTMD5()
{
	name("DIGEST-MD5");
	_step = 1;
	state(ready);
}

saslDIGESTMD5::~saslDIGESTMD5()
{
}

bool saslDIGESTMD5::response(QByteArray * challenge, QByteArray * response)
{
	if (_step == 1)
		return step1(challenge, response);
	else if (_step == 2)
		return step2(challenge, response);
	else
		return false;
}

bool saslDIGESTMD5::step1(QByteArray * challenge, QByteArray * response)
{
	QString s_ch;
	QString realm, nonce, username, serv_type, host, serv_name, passwd, digest_uri, nc, cnonce;
	QTextStream resp;
	QByteArray * prop;
	QString a1, a2, rval;
	cptMD5 md5;
	uint8_t * hash;
	QByteArray buf;
	QRegExp re;
	int off;

	s_ch = challenge->data();

	// nonce = "nonce" "=" <"> nonce-value <">
	re.setPattern("nonce=\"((\\\\\"|[^\\x0-\\x9\\xa-\\x1f\\x7f\"])*)\"");
	if (re.indexIn(s_ch) < 0) {
		state(error);
		return false;
	}
	nonce = re.cap(1);
	cnonce = md5.compute(reinterpret_cast<const uint8_t *>(nonce.toLocal8Bit().data()), nonce.size());
	nc = "00000001";

	// algorithm = "algorithm" "=" "md5-sess"
	re.setPattern("algorithm=md5-sess");
	if (re.indexIn(s_ch) < 0) {
		state(error);
		return false;
	}

	// realm = "realm" "=" <"> realm-value <">
	re.setPattern("realm=(?!\\\\)\"((\\\\\"|[^\\x0-\\x9\\xa-\\x1f\\x7f\"])*)\"");
	off = 0;
	if ((off = re.indexIn(s_ch, off)) >= 0) {
		realm = re.cap(1);
	}
	if (realm == "") {
		prop = property("realm");
		if (prop != NULL)
			realm = prop->data();
	}

	prop = property("username");
	if (prop != NULL)
		username = prop->data();
	if (username.isEmpty()) {
		state(error);
		return false;
	}

	prop = property("serv-type");
	if (prop != NULL)
		serv_type = prop->data();
	if (serv_type.isEmpty()) {
		state(error);
		return false;
	}

	prop = property("host");
	if (prop != NULL)
		host = prop->data();
	if (host.isEmpty()) {
		state(error);
		return false;
	}

	prop = property("serv-name");
	if (prop != NULL)
		serv_name = prop->data();

	digest_uri = serv_type + "/" + host;
	if (!serv_name.isEmpty())
		digest_uri += "/" + serv_name;

	prop = property("passwd");
	if (prop != NULL)
		passwd = prop->data();

	// calculate response-value
	md5.init();
	md5.update(username);
	md5.update(":");
	md5.update(realm);
	md5.update(":");
	md5.update(passwd);
	md5.finalize(&hash);

	md5.init();
	md5.update(hash, 16);
	delete hash;
	md5.update(":");
	md5.update(nonce);
	md5.update(":");
	md5.update(cnonce);
	md5.finalize(&hash);
	a1 = cptBase16::encode(hash, 16, true);
	delete hash;

	md5.init();
	md5.update("AUTHENTICATE:");
	md5.update(digest_uri);
	md5.finalize(&hash);
	a2 = cptBase16::encode(hash, 16, true);
	delete hash;

	md5.init();
	md5.update(a1);
	md5.update(":");
	md5.update(nonce);
	md5.update(":");
	md5.update(nc);
	md5.update(":");
	md5.update(cnonce);
	md5.update(":");
	md5.update("auth");
	md5.update(":");
	md5.update(a2);
	md5.finalize(&hash);
	rval = cptBase16::encode(hash, 16, true);
	delete hash;

	resp << "username=\"" << username << "\",";
	resp << "realm=\"" << realm << "\",";
	resp << "nonce=\"" << nonce << "\",";
	resp << "cnonce=\"" << cnonce << "\",";
	resp << "nc=" << nc << ",";
	resp << "qop=auth,";
	resp << "digest-uri=\"" << digest_uri << "\",";
	resp << "response=" << rval << ",";
	resp << "charset=utf-8";

	*response = resp.readAll().toLocal8Bit();

	_step = 2;
	state(auth);
	
	return true;
}

bool saslDIGESTMD5::step2(QByteArray * challenge, QByteArray * response)
{
	if (state() != auth) {
		state(error);
		return false;
	}

	// We assume that if we get second challenge from the server, 
	// the authentication is successfull.
	// TODO: check rspauth?

	state(auth_ok);
	*response = "";
	return true;
}

};

