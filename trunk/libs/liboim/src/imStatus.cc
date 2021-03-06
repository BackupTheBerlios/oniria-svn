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
#include "imStatus.h"

namespace onirIM {

imStatus::imStatus(contactStatus st, const QString& description)
{
	_status = st;
	_description = description;
}

QString imStatus::iconId() const
{
	return statusToString();
}

QString imStatus::statusToString() const
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
