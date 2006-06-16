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
#include "oXMLConfig.h"
#include "oOniriaImpl.h"
#include "oPluginManager.h"
#include "oSessionManager.h"
#include "oEventManager.h"
#include "oApplication.h"


oApplication::oApplication(int& argc, char ** argv)
: QApplication(argc, argv)
{
	QString cf;
	QDir dir;

	cf = QDir::homePath() + "/.oniria";
	dir.setPath(cf);
	if (!dir.exists())
		dir.mkpath(cf);
	_config = new oXMLConfig(cf + "/config.xml", true);

	_eventman = new oEventManager(this);

	_oniria = new oOniriaImpl(this);

	_plugman = new oPluginManager(this);
	_plugman->loadPlugins();

	_sessionman = new oSessionManager(this);

	_sessionman->registerEventHandlers();

	_eventman->processQueue();

	_plugman->createPlugins();

	_sessionman->loadSessions();
	_sessionman->connectSessions();
}

