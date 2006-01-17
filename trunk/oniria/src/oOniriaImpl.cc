/* $Id: oOniriaImpl.cc 628 2006-01-02 11:16:03Z choman $ */
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
#include "gApp.h"
#include "oEventManager.h"
#include "oSessionManager.h"
#include "oResourceManager.h"
#include <onir/oConfig.h>
#include <onir/oTabs.h>
#include "oOniriaImpl.h"

using namespace std;

oOniriaImpl::oOniriaImpl(gApp * app)
{
	_app = app;
	_prog_name = PACKAGE_NAME;
	_prog_version = PACKAGE_VERSION;
	_prog_string = PACKAGE_STRING;
	_os_desc = static_cast<string>(wxGetOsDescription());
}

oOniriaImpl::~oOniriaImpl()
{
}

bool oOniriaImpl::RegisterProtocol(imProtocol * proto)
{
	return _app->SessionManager()->RegisterProtocol(proto);
}

oConfig * oOniriaImpl::Config() const
{
	return _app->Config();
}

wxLog * oOniriaImpl::Log() const
{
	return wxLog::GetActiveTarget();
}

oTabs * oOniriaImpl::Tabs() const
{
	return _app->TabManager();
}

oResources * oOniriaImpl::Resources() const
{
	return _app->ResourceManager();
}

oEventQueue * oOniriaImpl::EventQueue() const
{
	return _app->EventManager();
}

const string& oOniriaImpl::ProgramName() const
{
	return _prog_name;
}

const string& oOniriaImpl::ProgramVersion() const
{
	return _prog_version;
}

const string& oOniriaImpl::ProgramString() const
{
	return _prog_string;
}

const string& oOniriaImpl::OSDescription() const
{
	return _os_desc;
}

