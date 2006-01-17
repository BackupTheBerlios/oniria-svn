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
#include "rcFileResource.h"

namespace onirRC {

DEFINE_OOBJECT(rcFileResource, rcResource);

rcFileResource::rcFileResource(oOniria * o)
: rcResource(o)
{
	INIT_OOBJECT;
}

rcFileResource::~rcFileResource()
{
}

bool rcFileResource::Prepare(const string& file, rcPack * owner, xmlElement * xml)
{
	if (!rcResource::Prepare(file, owner, xml))
		return false;

	_location = xml->AttributeValue("file");
	return !_location.empty();
}

wxFSFile * rcFileResource::Open()
{
	wxFileSystem fs;

	return fs.OpenFile(File() + "#zip:" + _location);
}

};

