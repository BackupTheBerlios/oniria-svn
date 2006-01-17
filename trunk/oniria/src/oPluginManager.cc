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
#include <iostream>
#include <wx/dir.h>
#include <wx/dynlib.h>
#include <onir/utils/uListDirTraverser.h>
#include <onir/oPlugin.h>
#include "gApp.h"
#include "oPluginManager.h"

#if defined(WIN32)
# define DYNLIB_MASK	"*.dll"
# define PLUGIN_CREATE	"plugin_create"
#elif defined(__LINUX__)
# define DYNLIB_MASK	"*.so"
# define PLUGIN_CREATE	"plugin_create"
#else
# define DYNLIB_MASK	"*"
# define PLUGIN_CREATE	"plugin_create"
#endif

using namespace std;
using onirUtils::uListDirTraverser;

typedef bool (*plugin_create)(oPlugin **);

oPluginManager::oPluginManager(gApp * app)
{
	_app = app;
}

oPluginManager::~oPluginManager()
{
}

int oPluginManager::LoadPlugins()
{
	uListDirTraverser trav;
	wxDir dir(PLUGINDIR);
	
	dir.Traverse(trav, DYNLIB_MASK);

	for (list<string>::iterator it = trav.files().begin(); it != trav.files().end(); it++) {

		wxDynamicLibrary * dl;
		oPlugin * plug;
		plugin_create fn;

		dl = new wxDynamicLibrary();
		if (!dl->Load(*it)) {
			delete dl;
		} else {
			fn = (plugin_create)dl->GetSymbol(PLUGIN_CREATE);
			if (!fn) {
				delete dl;
				continue;
			}
			plug = NULL;
			if (fn(&plug)) {
				if (plug != NULL)
					_plugins[plug->name()] = plug;
				_dlls.push_back(dl);
			} else {
				delete dl;
			}
		}

	}
	return _dlls.size();
}

int oPluginManager::CreatePlugins()
{
	int init_ok = 0;
	for (map<string, oPlugin *>::iterator it = _plugins.begin(); it != _plugins.end(); it++) {
		if (it->second->Create(_app->Oniria()))
			init_ok++;
	}
	return init_ok;
}

