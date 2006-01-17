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
#include "saslMechanism.h"
#include "saslCallback.h"
#include "saslDIGESTMD5.h"
#include "saslSASL.h"

namespace onirSASL {

DEFINE_OOBJECT(saslSASL, oObject);

saslSASL::saslSASL()
{
	INIT_OOBJECT;

	_mechanism = NULL;
	_callback = NULL;

	// register standard mechs.
	
	addMechanism(new saslDIGESTMD5());
}

saslSASL::~saslSASL()
{
	for (QMap<QString, saslMechanism *>::iterator it = _mechs.begin(); it != _mechs.end(); it++)
		delete it.value();
	if (_callback != NULL)
		delete _callback;
}

void saslSASL::callback(saslCallback * cb)
{
	if (_callback == NULL)
		delete _callback;
	_callback = cb;
	for (QMap<QString, saslMechanism *>::iterator it = _mechs.begin(); it != _mechs.end(); it++)
		it.value()->Callback(cb);
}

bool saslSASL::AddMechanism(saslMechanism * mech)
{
	if (_mechs.find(mech->name()) != _mechs.end())
		return false;

	_mechs[mech->name()] = mech;
	mech->callback(_callback);

	return true;
}

saslMechanism * saslSASL::findMechanism(const QString& name) const
{
	if (_mechs.find(name) == _mechs.end())
		return NULL;
	else
		return _mechs.find(name).value();
}

saslMechanism * saslSASL::ChooseMechanism(const QList<QString>& mechs)
{
	_allowed_mechs = mechs;
	_i_mechanism = _allowed_mechs.begin();
	return nextMechanism();
}

saslMechanism * saslSASL::nextMechanism()
{
	_mechanism = NULL;
	while (_mechanism == NULL && _i_mechanism != _allowed_mechs.end()) {
		_mechanism = findMechanism(*_i_mechanism);
		_i_mechanism++;
	}
	return _mechanism;
}

};

