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
#include "jJid.h"

jJid::jJid()
{
	_full = "";
	_node = "";
	_domain = "";
	_resource = "";
}

jJid::jJid(const string& full)
{
	Set(full);
}

jJid::jJid(const string& node, const string& domain, const string& resource)
{
	Set(node, domain, resource);
}

/*!\todo Use libidn to be i18n aware
 */
const string& jJid::Set(const string& full)
{
	string::size_type pos;

	_full = full;

	_resource = "";
	_bare = _full;
	pos = _full.find('/');
	if (pos != string::npos) {
		_bare.assign(_full, 0, pos);
		_resource.assign(_full, pos + 1, _full.size() - pos - 1);
	}

	pos = _bare.find('@');
	_domain = _bare;
	_node = "";
	if (pos != string::npos) {
		_node.assign(_bare, 0, pos);
		_domain.assign(_bare, pos + 1, _bare.size() - pos - 1);
	}

	return _full;
}

const string& jJid::Set(const string& bare, const string& resource)
{
	string::size_type pos;
	
	_bare = bare;
	_resource = resource;

	pos = _bare.find('@');
	_domain = _bare;
	_node = "";
	if (pos != string::npos) {
		_node.assign(_bare, 0, pos);
		_domain.assign(_bare, pos + 1, _bare.size() - pos - 1);
	}

	_full = _bare;
	if (!_resource.empty())
		_full += "/" + _resource;

	return _full;
}

const string& jJid::Set(const string& node, const string& domain, const string& resource)
{
	_node = node;
	_domain = domain;
	_resource = resource;

	_full = "";

	if (_domain.empty())
		return _full;

	if (!_node.empty())
		_full = _node + "@";

	_full += _domain;
	_bare = _full;

	if (!_resource.empty())
		_full += "/" + _resource;

	return _full;
}

bool jJid::Valid() const
{
	if (_domain.empty())
		return false;
	else
		return true;
}
