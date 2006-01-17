/* $Id: saslMechanism.cc 635 2006-01-03 13:14:09Z choman $ */
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
#include "saslCallback.h"
#include "saslMechanism.h"

namespace onirSASL {

DEFINE_OOBJECT(saslMechanism, oObject);

saslMechanism::saslMechanism()
{
	INIT_OOBJECT;

	state(not_implemented);
}

saslMechanism::~saslMechanism()
{
}

void saslMechanism::addProperty(const QString& name, QByteArray * val)
{
	_properties.insert(name, val);
}

void saslMechanism::addProperty(const QString& name, const QString& val)
{
	return addProperty(name, new QByteArray(val.toLocal8Bit()));
}

void saslMechanism::properties(const QString& name, QList<QByteArray *>& props) const
{
	for (QMultiMap<QString, QByteArray *>::const_iterator it = _properties.find(name); it != _properties.end() && it.key() == name; it++)
		props.push_back(it.value());
}

QByteArray * saslMechanism::property(const QString& name, bool use_cb) const
{
	QList<QByteArray *> props;
	properties(name, props);
	if (props.empty()) {
		if(use_cb && callback() != NULL)
			return callback()->property(name);
		return NULL;
	}
	return props.back();
}

bool saslMechanism::response(QByteArray * challenge, QByteArray * response)
{
	state(not_implemented);
	return false;
}

bool saslMechanism::challenge(QByteArray * response, QByteArray * challenge)
{
	state(not_implemented);
	return false;
}

};

