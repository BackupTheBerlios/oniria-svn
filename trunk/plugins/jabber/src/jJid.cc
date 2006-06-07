/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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
#include "jJid.h"

jJid::jJid()
{
	_full = "";
	_node = "";
	_domain = "";
	_resource = "";
}

jJid::jJid(const QString& full)
{
	set(full);
}

jJid::jJid(const QString& node, const QString& domain, const QString& resource)
{
	set(node, domain, resource);
}

/*!\todo Use libidn to be i18n aware
 */
const QString& jJid::set(const QString& full)
{
	int pos;

	_full = full;

	_resource = "";
	_bare = _full;
	pos = _full.indexOf('/');
	if (pos != -1) {
		_bare = _full.left(pos);
		_resource = _full.mid(pos + 1, _full.size() - pos - 1);
	}

	pos = _bare.indexOf('@');
	_domain = _bare;
	_node = "";
	if (pos != -1) {
		_node = _bare.mid(0, pos);
		_domain = _bare.mid(pos + 1, _bare.size() - pos - 1);
	}

	return _full;
}

const QString& jJid::set(const QString& bare, const QString& resource)
{
	int pos;
	
	_bare = bare;
	_resource = resource;

	pos = _bare.indexOf('@');
	_domain = _bare;
	_node = "";
	if (pos != -1) {
		_node = _bare.mid(0, pos);
		_domain = _bare.mid(pos + 1, _bare.size() - pos - 1);
	}

	_full = _bare;
	if (!_resource.isEmpty())
		_full += "/" + _resource;

	return _full;
}

const QString& jJid::set(const QString& node, const QString& domain, const QString& resource)
{
	_node = node;
	_domain = domain;
	_resource = resource;

	_full = "";

	if (_domain.isEmpty())
		return _full;

	if (!_node.isEmpty())
		_full = _node + "@";

	_full += _domain;
	_bare = _full;

	if (!_resource.isEmpty())
		_full += "/" + _resource;

	return _full;
}

bool jJid::valid() const
{
	if (_domain.isEmpty())
		return false;
	else
		return true;
}

