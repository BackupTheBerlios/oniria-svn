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
#ifndef __OPLUGINMANAGER_H
#define __OPLUGINMANAGER_H

#include <map>
#include <string>
#include <vector>
#include <onir/oPlugin.h>

using std::map;
using std::string;
using std::vector;
using onir::oPlugin;
class wxDynamicLibrary;
class gApp;

class oPluginManager {
	public:
		oPluginManager(gApp * app);
		virtual ~oPluginManager();

		int LoadPlugins();
		int CreatePlugins();

	private:
		gApp * _app;
		map<string, oPlugin *> _plugins;
		vector<wxDynamicLibrary *> _dlls;

};

#endif
