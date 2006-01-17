/* $Id: jProtocol.h 209 2005-07-28 17:05:39Z choman $ */
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
#ifndef __JPROTOCOL_H
#define __JPROTOCOL_H

#include <onir/im/imProtocol.h>
#include <onir/im/imSession.h>
#include <onir/oOniria.h>

using namespace std;
using onirIM::imProtocol;
using onirIM::imSession;
using onir::oOniria;

class jProtocol : public imProtocol {

	public:
		jProtocol();
		virtual ~jProtocol();

		virtual string ProtocolId() const;
		virtual string ProtocolName() const;
		virtual string ProtocolDescription() const;
		virtual string ProtocolVersion() const;

		virtual imSession * CreateSession(oOniria * o);

		DECLARE_OOBJECT;
};

#endif
