/* $Id: oOniriaImpl.h 563 2005-09-11 10:06:55Z choman $ */
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
#ifndef __OONIRIAIMPL_H
#define __OONIRIAIMPL_H

#include <onir/oOniria.h>

class gApp;
using onir::oOniria;
using onir::oConfig;
using onir::oTabs;
using onir::oResources;
using onir::oEventQueue;

class oOniriaImpl : public oOniria {
	public:
		oOniriaImpl(gApp * app);
		virtual ~oOniriaImpl();

		virtual bool RegisterProtocol(imProtocol * proto);
		virtual oConfig * Config() const;
		virtual wxLog * Log() const;
		virtual oTabs * Tabs() const;
		virtual oResources * Resources() const;
		virtual oEventQueue * EventQueue() const;

		virtual const string& ProgramName() const;
		virtual const string& ProgramVersion() const;
		virtual const string& ProgramString() const;
		virtual const string& OSDescription() const;
		
		/* @} */

	private:
		gApp * _app;
		string _prog_name;
		string _prog_version;
		string _prog_string;
		string _os_desc;

};

#endif
