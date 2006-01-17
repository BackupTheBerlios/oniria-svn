/* $Id: xmlAttribute.cc 639 2006-01-03 14:22:18Z choman $ */
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
#include "oxml.h"
#include "xmlAttribute.h"

namespace onirXML {

xmlAttribute::xmlAttribute(const QString& aname, const QString& avalue)
{
	name(aname);
	value(avalue);
	order(0);
	encoding("UTF-8");
}

xmlAttribute::xmlAttribute(const QString& aname, int avalue)
{
	name(aname);
	value(avalue);
	order(0);
	encoding("UTF-8");
}

void xmlAttribute::value(int avalue)
{
	QTextStream ss;
	ss << avalue;
	value(ss.readAll());
}

void xmlAttribute::value(const QString& avalue)
{
	_value = avalue;
}

bool xmlAttribute::valid() const
{
	return !_name.isEmpty();
}

QString xmlAttribute::format() const
{
	QTextStream ss;
	char quot;
	QByteArray conv;

	conv = value().toUtf8();

	if (value().indexOf('\'') != -1)
		quot = '"';
	else
		quot = '\'';

	conv.replace("&", "&amp;");
	conv.replace("<", "&lt;");
	conv.replace(">", "&gt;");
	conv.replace("'", "&apos;");
	conv.replace("\"", "&quot;");

	ss << name() << "=" << quot << conv.data() << quot;
	return ss.readAll();
}

};

