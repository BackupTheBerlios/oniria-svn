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
#include "oPlugin.h"

using namespace onirXML;

namespace onir {

oPlugin::oPlugin()
{
	_description = new xmlElement("plugin");
	_description->addChild("author", "");
	_description->addChild("build", "");
	_description->addChild("features", "");
}

oPlugin::~oPlugin()
{
	delete _description;
}

void oPlugin::id(const QString& s)
{
	_description->addAttribute("id", s);
}

const QString& oPlugin::id() const
{
	return _description->attributeValue("id");
}

xmlElement * oPlugin::descriptionField(const QString& n, const QString& v)
{
	return _description->addChild(n, v);
}

const QString& oPlugin::descriptionField(const QString& n) const
{
	return _description->childValue(n);
}

xmlElement * oPlugin::descriptionAuthorField(const QString& n, const QString& v)
{
	return _description->child("author")->addChild(n, v);
}

const QString& oPlugin::descriptionAuthorField(const QString& n) const
{
	return _description->child("author")->childValue(n);
}

xmlElement * oPlugin::descriptionBuildField(const QString& n, const QString& v)
{
	return _description->child("build")->addChild(n, v);
}

const QString& oPlugin::descriptionBuildField(const QString& n) const
{
	return _description->child("build")->childValue(n);
}

xmlElement * oPlugin::addFeature(const QString& n, const QString& fid)
{
	return _description->child("features")->addChild(n, "", "id", fid);
}

};

