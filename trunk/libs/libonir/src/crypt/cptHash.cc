/* $Id: cptHash.cc 624 2006-01-01 22:04:34Z choman $ */
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
#include <QByteArray>
#include "cptHash.h"

namespace onirCrypt {

DEFINE_OOBJECT(cptHash, oObject);

cptHash::cptHash()
{
	INIT_OOBJECT;
}

QString cptHash::compute(const QString& msg)
{
	QByteArray tmp;
	tmp = msg.toLocal8Bit();
	return compute(reinterpret_cast<const uint8_t *>(tmp.data()), tmp.size());
}


};

