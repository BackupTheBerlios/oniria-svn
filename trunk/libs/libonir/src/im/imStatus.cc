/* $Id: imStatus.cc 614 2005-12-29 16:44:50Z choman $ */
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
#include "../oOniria.h"
#include "imStatus.h"

namespace onirIM {

DEFINE_OOBJECT(imStatus, oObject);

imStatus::imStatus(status st, const string& description)
{
	INIT_OOBJECT;
	_status = st;
	_description = description;
}

string imStatus::IconId() const
{
	return StatusToString();
}

string imStatus::StatusToString() const
{
	switch (_status) {
		case chat:
			return "chat";
		case avail:
			return "avail";
		case away:
			return "away";
		case xa:
			return "xa";
		case dnd:
			return "dnd";
		case inv:
			return "inv";
		case na:
			return "na";
		default:
			return "unsp";
	}
}

};
