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
#include "rcPack.h"
#include "rcFileResource.h"
#include "rcImage.h"
#include "rcSkin.h"

namespace onirRC {

DEFINE_OOBJECT(rcPack, rcResource);

rcPack::rcPack(oOniria * o)
: rcResource(o)
{
	INIT_OOBJECT;
}

rcPack::~rcPack()
{
	for (map<string, map<string, rcResource *> >::iterator it = _resources.begin(); it != _resources.end(); it++)
		for (map<string, rcResource *>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
			delete it2->second;
}

bool rcPack::Prepare(const string& file, rcPack * owner, xmlElement * xml)
{
	list<xmlElement *> res;
	if (!rcResource::Prepare(file, owner, xml))
		return false;

	xml->Detach("resource", res);

	for (list<xmlElement *>::iterator it = res.begin(); it != res.end(); it++) {
		string id, type;
		rcResource * r;

		id = (*it)->AttributeValue("id");
		type = (*it)->AttributeValue("type");
		r = NULL;

		if (_resources[type].find(id) != _resources[type].end()) {
			if (type != "pack") {
				delete *it;	// TODO: how to handle collisions?
				continue;
			} else {
				r = _resources[type][id];
			}
		}

		if (r == NULL) {
			if (type == "pack")
				r = new rcPack(Oniria());
			else if (type == "image")
				r = new rcImage(Oniria());
			else if (type == "skin")
				r = new rcSkin(Oniria());
			else if (!(*it)->AttributeValue("file").empty())	// TODO: handle different types of resources.
				r = new rcFileResource(Oniria());
			else
				r = new rcResource(Oniria());
		}

		r->Prepare(file, this, *it);
		_resources[type][id] = r;
	}

	return true;
}

rcResource * rcPack::Resource(const string& id, const string& type)
{
	string::size_type pos;

	pos = id.find(":");

	if (pos == string::npos) {	// leaf
		if (_resources[type].find(id) == _resources[type].end())
			return NULL;
		else
			return _resources[type][id];
	} else {			// node down
		rcPack * pack;
		string node;

		node.assign(id, 0, pos);
		pack = static_cast<rcPack *>(Resource(node, "pack"));
		if (pack != NULL)
			return pack->Resource(string(id, pos+1), type);
		else
			return NULL;
	}
}

};

