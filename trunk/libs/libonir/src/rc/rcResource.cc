/* $Id: rcResource.cc 614 2005-12-29 16:44:50Z choman $ */
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
#include "rcResource.h"
#include "rcPack.h"
#include "../oEventQueue.h"
#include "../oEvent.h"

using onir::oEvent;
using onir::oEventQueue;

namespace onirRC {

DEFINE_OOBJECT(rcResource, oObject);

rcResource::rcResource(oOniria * o)
{
	INIT_OOBJECT;

	_xml = NULL;
	_owner = NULL;
	_oniria = o;
}

rcResource::~rcResource()
{
	for (set<xmlElement *>::iterator it = _xmls.begin(); it != _xmls.end(); it++)
		delete *it;
}

bool rcResource::Prepare(const string& file, rcPack * owner, xmlElement * xml)
{
	oEvent * event;

	_xml = xml;
	_xmls.insert(xml);
	_type = xml->AttributeValue("type");
	_id = xml->AttributeValue("id");
	_owner = owner;
	_file = file;

	wxLogVerbose("rcResource: Added resource: %s", Id().c_str());
	
	event = new oEvent("oniria:resource:added");
	event->XML()->AddChild("resource-id", Id());
	event->XML()->AddChild("resource-type", _type);
	Oniria()->EventQueue()->Queue(event);

	return true;
}

string rcResource::Id() const
{
	string id;

	if (_owner != NULL)
		id = _owner->Id();
	if (!id.empty() && !_id.empty())
		id += ":";
	id += _id;
	return id;
}

};

