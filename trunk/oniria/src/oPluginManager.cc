/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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
#include <QDir>
#include <QStringList>
#include <QtDebug>
#if defined(HAVE_DLFCN_H)
# include <dlfcn.h>
#endif
#include <onir/oPlugin.h>
#include "oApplication.h"
#include "oPluginManager.h"

#if defined(WIN32)
# define DYNLIB_MASK	"*.dll"
# define PLUGIN_CREATE	"plugin_create"
#elif defined(__LINUX__)
# define DYNLIB_MASK	"*.so"
# define PLUGIN_CREATE	"plugin_create"
#else
# define DYNLIB_MASK	"*.so"
# define PLUGIN_CREATE	"plugin_create"
#endif

typedef bool (*plugin_create)(oPlugin **);

oPluginManager::oPluginManager(oApplication * app)
{
	_app = app;
}

oPluginManager::~oPluginManager()
{
}

int oPluginManager::loadPlugins()
{
	QDir dir(PLUGINDIR);
	QStringList flt, files;

	flt.push_back(DYNLIB_MASK);
	files = dir.entryList(flt, QDir::Files | QDir::Readable);

	qDebug() << "oPluginManager::loadPlugins(): Plugins dir:" << PLUGINDIR;
	qDebug() << "oPluginManager::loadPlugins(): Plugins mask:" << DYNLIB_MASK;
	for (QStringList::iterator it = files.begin(); it != files.end(); it++) {

		QLibrary * dl;
		oPlugin * plug;
		plugin_create fn;

		qDebug() << "oPluginManager::loadPlugins(): Found plugin:" << *it;

		dl = new QLibrary(QString(PLUGINDIR) + "/" + *it);
		if (!dl->load()) {
			qDebug() << "oPluginManager::loadPlugins(): Can't load library " << *it;
#if defined(HAVE_DLFCN_H)
			qDebug() << "oPluginManager::loadPlugins():" << dlerror();
#endif
			delete dl;
		} else {
			fn = (plugin_create)dl->resolve(PLUGIN_CREATE);
			if (!fn) {
				qDebug() << "oPluginManager::loadPlugins(): Can't find plugin entry point in " << *it;
				delete dl;
				continue;
			}
			plug = NULL;
			if (fn(&plug)) {
				if (!plug->id().isEmpty()) {
					if (plug != NULL)
						_plugins[plug->id()] = plug;
					qDebug() << "oPluginManager::loadPlugins(): Loaded plugin:" << plug->id();
					_dlls.push_back(dl);
				} else {
					qDebug() << "oPluginManager::loadPlugins(): Empty plugin id? Bad...";
					delete dl;
					continue;
				}
			} else {
				delete dl;
			}
		}

	}
	qDebug() << "oPluginManager::loadPlugins(): Loaded " << _dlls.size() << " plugins.";
	return _dlls.size();
}

int oPluginManager::createPlugins()
{
	int init_ok = 0;
	for (QMap<QString, oPlugin *>::iterator it = _plugins.begin(); it != _plugins.end(); it++) {
		if (it.value()->create(_app->oniria()))
			init_ok++;
	}
	return init_ok;
	return 0;
}

