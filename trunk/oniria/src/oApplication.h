/* $Id$ */
/*
 * Copyright (C) 2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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
 
#ifndef __OAPPLICATION_H
#define __OAPPLICATION_H
 
#include <QApplication>
#include <onir/oOniria.h>
#include <onir/oConfig.h>

using onir::oOniria;
using onir::oConfig;

class oPluginManager;
class oEventManager;

class oApplication : public QApplication {

	Q_OBJECT

	public:
		oApplication(int& argc, char ** argv);

		inline oOniria * oniria() const { return _oniria; };
		inline oConfig * config() const { return _config; };
		inline oEventManager * eventManager() const { return _eventman; };
		inline oPluginManager * pluginManager() const { return _plugman; };
		
	private:
		oOniria * _oniria;
		oConfig * _config;
		oPluginManager * _plugman;
		oEventManager * _eventman;
};
 
#endif
