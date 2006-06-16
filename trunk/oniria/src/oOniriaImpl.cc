/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-kszalin.pl>
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
#include "oApplication.h"
#include "oEventManager.h"
#include "oSessionManager.h"
//#include "oResourceManager.h"
#include <onir/oConfig.h>
//#include <onir/oTabs.h>
#include "oOniriaImpl.h"

oOniriaImpl::oOniriaImpl(oApplication * app)
{
	_app = app;
	_prog_name = PACKAGE_NAME;
	_prog_version = PACKAGE_VERSION;
	_prog_QString = PACKAGE_STRING;
	//_os_desc = static_cast<QString>(wxGetOsDescription());
}

oOniriaImpl::~oOniriaImpl()
{
}

bool oOniriaImpl::registerProtocol(imProtocol * proto)
{
	return _app->sessionManager()->registerProtocol(proto);
	return true;
}

QApplication * oOniriaImpl::application() const
{
	return _app;
}

QObject * oOniriaImpl::applicationQObject() const
{
	return _app;
}

oConfig * oOniriaImpl::config() const
{
	return _app->config();
}

//wxLog * oOniriaImpl::Log() const
//{
//	return wxLog::GetActiveTarget();
//}

oTabs * oOniriaImpl::tabs() const
{
	// TODO
	return NULL; //_app->TabManager();
}

oResources * oOniriaImpl::resources() const
{
	// TODO
	return NULL; //_app->ResourceManager();
}

oEventQueue * oOniriaImpl::eventQueue() const
{
	return _app->eventManager();
}

const QString& oOniriaImpl::programName() const
{
	return _prog_name;
}

const QString& oOniriaImpl::programVersion() const
{
	return _prog_version;
}

const QString& oOniriaImpl::programString() const
{
	return _prog_QString;
}

const QString& oOniriaImpl::OSDescription() const
{
	return _os_desc;
}

