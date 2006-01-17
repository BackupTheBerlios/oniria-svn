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
#include "uException.h"

namespace onirUtils {

uException::uException() throw()
{
	_what = _("Unknown exception");
}

uException::uException(const string& err, const string& where) throw()
{
	_what = err;
	_where = where;
}

uException::~uException() throw()
{
}

const char * uException::what() const throw()
{
	string err;
	if (!_where.empty())
		err = _where + ": " + _what;
	else
		err = _what;
	return err.c_str();
}

};
