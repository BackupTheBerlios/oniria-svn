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
#include <boost/regex.hpp>
#include <sstream>
#include "../crypt/cptMD5.h"
#include "../utils/uBase16.h"
#include "saslCallback.h"
#include "saslDIGESTMD5.h"

using onirCrypt::cptMD5;
using onirUtils::uBase16;

namespace onirSASL {

DEFINE_OOBJECT(saslDIGESTMD5, saslMechanism);

saslDIGESTMD5::saslDIGESTMD5()
{
	INIT_OOBJECT;

	name("DIGEST-MD5");
	_step = 1;
	state(ready);
}

saslDIGESTMD5::~saslDIGESTMD5()
{
}

bool saslDIGESTMD5::Response(QByteArray * challenge, QByteArray * response)
{
	if (_step == 1)
		return Step1(challenge, response);
	else if (_step == 2)
		return Step2(challenge, response);
	else
		return false;
}

bool saslDIGESTMD5::Step1(QByteArray * challenge, QByteArray * response)
{
	QString s_ch;
	QString::const_iterator start, end;
	boost::regex exp;
	boost::match_flag_type flags;
	boost::match_results<std::QString::const_iterator> what;
	QString realm, nonce, username, serv_type, host, serv_name, passwd, digest_uri, nc, cnonce;
	QStringstream resp;
	QByteArray * prop;
	QString a1, a2, rval;
	cptMD5 md5;
	uint8_t * hash;
	QByteArray buf;

	s_ch = challenge->str();
	flags = boost::match_default;
	start = s_ch.begin();
	end = s_ch.end();

	// nonce = "nonce" "=" <"> nonce-value <">
	exp = "nonce=\"((\\\\\"|[^\\x0-\\x9\\xa-\\x1f\\x7f\"])*)\"";
	start = s_ch.begin();
	end = s_ch.end();
	if (!regex_search(start, end, what, exp, flags)) {
		State(error);
		return false;
	}
	nonce = QString(what[1].first, what[1].second);
	cnonce = md5.Compute(reinterpret_cast<const uint8_t *>(nonce.c_str()), nonce.size());
	nc = "00000001";

	// algorithm = "algorithm" "=" "md5-sess"
	exp = "algorithm=md5-sess";
	start = s_ch.begin();
	end = s_ch.end();
	if (!regex_search(start, end, what, exp, flags)) {
		State(error);
		return false;
	}

	// realm = "realm" "=" <"> realm-value <">
	exp = "realm=(?!\\\\)\"((\\\\\"|[^\\x0-\\x9\\xa-\\x1f\\x7f\"])*)\"";
	start = s_ch.begin();
	end = s_ch.end();
	while (regex_search(start, end, what, exp, flags)) {
		realm = QString(what[1].first, what[1].second);
		start = what[0].second;
	}
	if (realm == "") {
		prop = Property("realm");
		if (prop != NULL)
			realm = prop->str();
	}

	prop = Property("username");
	if (prop != NULL)
		username = prop->str();
	if (username.empty()) {
		State(error);
		return false;
	}

	prop = Property("serv-type");
	if (prop != NULL)
		serv_type = prop->str();
	if (serv_type.empty()) {
		State(error);
		return false;
	}

	prop = Property("host");
	if (prop != NULL)
		host = prop->str();
	if (host.empty()) {
		State(error);
		return false;
	}

	prop = Property("serv-name");
	if (prop != NULL)
		serv_name = prop->str();

	digest_uri = serv_type + "/" + host;
	if (!serv_name.empty())
		digest_uri += "/" + serv_name;

	prop = Property("passwd");
	if (prop != NULL)
		passwd = prop->str();

	// calculate response-value
	md5.Init();
	md5.Update(username);
	md5.Update(":");
	md5.Update(realm);
	md5.Update(":");
	md5.Update(passwd);
	md5.Finalize(&hash);

	md5.Init();
	md5.Update(hash, 16);
	delete hash;
	md5.Update(":");
	md5.Update(nonce);
	md5.Update(":");
	md5.Update(cnonce);
	md5.Finalize(&hash);
	a1 = uBase16::Encode(hash, 16, true);
	delete hash;

	md5.Init();
	md5.Update("AUTHENTICATE:");
	md5.Update(digest_uri);
	md5.Finalize(&hash);
	a2 = uBase16::Encode(hash, 16, true);
	delete hash;

	md5.Init();
	md5.Update(a1);
	md5.Update(":");
	md5.Update(nonce);
	md5.Update(":");
	md5.Update(nc);
	md5.Update(":");
	md5.Update(cnonce);
	md5.Update(":");
	md5.Update("auth");
	md5.Update(":");
	md5.Update(a2);
	md5.Finalize(&hash);
	rval = uBase16::Encode(hash, 16, true);
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

	response->Copy(resp.str());

	_step = 2;
	State(auth);
	
	return true;
}

bool saslDIGESTMD5::Step2(QByteArray * challenge, QByteArray * response)
{
	if (State() != auth) {
		State(error);
		return false;
	}

	// We assume that if we get second challenge from the server, 
	// the authentication is successfull.
	// TODO: check rspauth?

	State(auth_ok);
	response->Copy("");
	return true;
}

};

