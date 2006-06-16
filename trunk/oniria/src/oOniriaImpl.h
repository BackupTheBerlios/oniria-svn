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
#ifndef __OONIRIAIMPL_H
#define __OONIRIAIMPL_H

#include <onir/oOniria.h>

class oApplication;
using onir::oOniria;
using onir::oConfig;
using onir::oTabs;
using onir::oResources;
using onir::oEventQueue;

class oOniriaImpl : public oOniria {
	public:
		oOniriaImpl(oApplication * app);
		virtual ~oOniriaImpl();

		virtual bool registerProtocol(imProtocol * proto);
		virtual QApplication * application() const;
		virtual QObject * applicationQObject() const;
		virtual oConfig * config() const;
		//virtual wxLog * Log() const;
		virtual oTabs * tabs() const;
		virtual oResources * resources() const;
		virtual oEventQueue * eventQueue() const;

		virtual const QString& programName() const;
		virtual const QString& programVersion() const;
		virtual const QString& programString() const;
		virtual const QString& OSDescription() const;
		
		/* @} */

	private:
		oApplication * _app;
		QString _prog_name;
		QString _prog_version;
		QString _prog_QString;
		QString _os_desc;

};

#endif
