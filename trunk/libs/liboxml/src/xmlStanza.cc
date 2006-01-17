/* $Id: xmlStanza.cc 636 2006-01-03 14:04:42Z choman $ */
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
#include "xmlElement.h"
#include "xmlStanza.h"

namespace onirXML {

xmlStanza::xmlStanza()
{
	encoding("UTF-8");	// set default encoding

	_element = new xmlElement;
	_active = NULL;
	_level = 0;
	_valid = false;
}

xmlStanza::~xmlStanza()
{
	delete _element;
}

bool xmlStanza::parseStartTag(const char * el, const char ** attrs)
{
	xmlElement * elem;
	if (_level == 0) {	// start new stanza
		elem = _element;
	} else {
		elem = new xmlElement;
	}

	elem->name(el);
	elem->encoding(encoding());
	for (int i = 0; attrs[i]; i += 2)
		elem->addAttribute(attrs[i], attrs[i+1]);

	if (_active != NULL)
		_active->addChild(elem);

	_active = elem;
	_level++;
	return true;
}

bool xmlStanza::parseEndTag(const char * el)
{
	if (_active != NULL) {
		if (_active->name() != el)	// something wrong with XML
			return false;
		_active = _active->parent();
	}

	_level--;
	
	if (_level == 0)
		_valid = true;

	return _level > 0;
}

void xmlStanza::parseCharacterData(const QString& s)
{
	if (_active == NULL)
		return;

	_active->value(_active->value() + s);
}

QString xmlStanza::format(bool one_line, bool force_non_empty) const
{
	return _element->format(one_line, force_non_empty);
}

};

