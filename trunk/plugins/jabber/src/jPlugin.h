/* $Id: jPlugin.h 149 2005-07-24 17:50:26Z choman $ */
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
#ifndef __JPLUGIN_H
#define __JPLUGIN_H

#include <onir/oPlugin.h>
#include <onir/oOniria.h>

using namespace std;
using onir::oPlugin;
using onir::oOniria;
class jProtocol;

class jPlugin : public oPlugin {

	public:
		jPlugin();
		virtual ~jPlugin();

		virtual bool Create(oOniria * o);

		DECLARE_OOBJECT;

	private:
		jProtocol * _protocol;
};

#endif
