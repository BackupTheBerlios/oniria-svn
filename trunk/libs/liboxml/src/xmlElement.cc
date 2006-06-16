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
#include <QTextStream>
#include <QRegExp>
#include "oxml.h"
#include "xmlElement.h"

namespace onirXML {

extern QString _liboxml_charset;

xmlElement::xmlElement(const QString& aname, const QString& avalue)
{
	name(aname);
	value(avalue);
	parent(NULL);
	order(0);
	encoding("UTF-8");
	_last_child = 0;
	_last_attr = 0;
}

xmlElement::xmlElement(const QString& aname, int avalue)
{
	name(aname);
	value(avalue);
	parent(NULL);
	order(0);
	encoding("UTF-8");
	_last_child = 0;
	_last_attr = 0;
}

xmlElement::~xmlElement()
{
	for (QMultiMap<QString, xmlElement *>::iterator it = _children.begin(); it != _children.end(); it++)
		delete it.value();

	for (QMap<QString, xmlAttribute *>::iterator it = _attributes.begin(); it != _attributes.end(); it++)
		delete it.value();
}

void xmlElement::value(int avalue)
{
	QString s;
	QTextStream ss(&s);
	ss << avalue;
	value(s);
}

void xmlElement::value(const QString& avalue)
{
	_value = avalue;
}

bool xmlElement::valid() const
{
	return !_name.isEmpty();
}

bool xmlElement::empty() const
{
	return value().isEmpty() && _children.empty();
}

xmlAttribute * xmlElement::addAttribute(const QString& aname, const QString& avalue)
{
	xmlAttribute * attrib = new xmlAttribute(aname, avalue);
	attrib->encoding(encoding());
	return addAttribute(attrib);
}

xmlAttribute * xmlElement::addAttribute(const QString& aname, int avalue)
{
	xmlAttribute * attrib = new xmlAttribute(aname, avalue);
	attrib->encoding(encoding());
	return addAttribute(attrib);
}

xmlAttribute * xmlElement::addAttribute(xmlAttribute * attrib)
{
	if (_attributes.find(attrib->name()) != _attributes.end())
		return false;

	_attributes[attrib->name()] = attrib;
	_attr_order[++_last_attr] = attrib;
	attrib->order(_last_attr);
	return attrib;
}

xmlAttribute * xmlElement::attribute(const QString& aname) const
{
	if (_attributes.find(aname) == _attributes.end())
		return NULL;

	return _attributes.find(aname).value();
}

const QString& xmlElement::attributeValue(const QString& aname, const QString& def) const
{
	xmlAttribute * attr = attribute(aname);
	if (attr == NULL)
		return def;
	else
		return attr->value();
}

xmlElement * xmlElement::addChild(const QString& aname, const QString& avalue)
{
	xmlElement * elem = new xmlElement(aname, avalue);
	elem->encoding(encoding());
	return addChild(elem);
}

xmlElement * xmlElement::addChild(const QString& aname, int avalue)
{
	xmlElement * elem = new xmlElement(aname, avalue);
	elem->encoding(encoding());
	return addChild(elem);
}

xmlElement * xmlElement::addChild(const QString& aname, const QString& avalue, const QString& attrname, const QString& attrvalue)
{
	xmlElement * elem = addChild(aname, avalue);
	elem->addAttribute(attrname, attrvalue);
	return elem;
}

xmlElement * xmlElement::addChild(const QString& aname, int avalue, const QString& attrname, const QString& attrvalue)
{
	xmlElement * elem = addChild(aname, avalue);
	elem->addAttribute(attrname, attrvalue);
	return elem;
}

xmlElement * xmlElement::addChild(xmlElement * elem)
{
	elem->parent(this);
	_children.insert(elem->name(), elem);
	_child_order[++_last_child] = elem;
	elem->order(_last_child);
	return elem;
}

int xmlElement::children(const QString& aname, QList<xmlElement *>& dst) const
{
	if (_children.count(aname) == 0)
		return 0;

	for (QMultiMap<QString, xmlElement *>::const_iterator it = _children.find(aname); it != _children.end() && it.key() == aname; it++) {
		dst.push_back(it.value());
	}

	return _children.count(aname);
}

xmlElement * xmlElement::child(const QString& name) const
{
	if (_children.count(name) == 0)
		return NULL;

	return _children.find(name).value();
}

const QString& xmlElement::childValue(const QString& name, const QString& def) const
{
	xmlElement * elem = child(name);
	if (elem == NULL)
		return def;
	else
		return elem->value();
}

QMultiMap<QString, xmlElement *> xmlElement::detach()
{
	QMultiMap<QString, xmlElement *> m = _children;
	_children.clear();
	_child_order.clear();
	_last_child = 0;
	return m;
}

void xmlElement::detach(QMultiMap<QString, xmlElement *>& dst)
{
	dst = _children;
	_children.clear();
	_child_order.clear();
	_last_child = 0;
}

int xmlElement::detach(const QString& name, QList<xmlElement *>& dst)
{
	if (_children.count(name) == 0)
		return 0;

	for (QMultiMap<QString, xmlElement *>::const_iterator it = _children.find(name); it != _children.end() && it.key() == name; it++) {
		dst.push_back(it.value());
		_child_order.remove(it.value()->order());
	}
	_children.remove(name);

	return dst.size();
}

xmlElement * xmlElement::detach(const QString& name)
{
	xmlElement * el;

	if (_children.find(name) == _children.end())
		return NULL;

	el =  _children.find(name).value();
	_children.erase(_children.find(name));
	if (el != NULL)
		_child_order.remove(el->order());
	return el;
}

QString xmlElement::formatOpening(bool one_line, bool force_non_empty, const QString& indent_string, unsigned int indent_level) const
{
	QString s;
	QTextStream ss(&s);

	if (!valid())
		return "";

	if (!one_line)
		for (unsigned int i = 0; i < indent_level; i++)
			ss << indent_string;
	ss << "<" << name();

	for (QMap<int, xmlAttribute *>::const_iterator it = _attr_order.begin(); it != _attr_order.end(); it++) {
		if (it.value()->valid())
			ss << " " << it.value()->format();
	}

	if (empty() && !force_non_empty)
		ss << " />";
	else
		ss << ">";

	return s;
}

QString xmlElement::formatContent(bool one_line, const QString& indent_string, unsigned int indent_level) const
{
	QString s;
	QTextStream ss(&s);

	if (!valid() || empty())
		return "";

	if (!_value.isEmpty() && _value.indexOf(QRegExp("\\S")) != -1) {
		QByteArray conv;

		conv = _value.toUtf8();	
			
		conv.replace("&", "&amp;");
		conv.replace("<", "&lt;");
		conv.replace(">", "&gt;");
		conv.replace("'", "&apos;");
		conv.replace("\"", "&quot;");
		ss << conv.data();
	}
	if (!one_line && !_children.empty())
		ss << endl;

	for (QMap<int, xmlElement *>::const_iterator it = _child_order.begin(); it != _child_order.end(); it++) {
		ss << it.value()->format(one_line, false, indent_string, indent_level + 1);
		if (!one_line)
			ss << endl;
	}

	return s;
}

QString xmlElement::formatClosing(bool one_line, bool force, const QString& indent_string, unsigned int indent_level) const
{
	QString s;
	QTextStream ss(&s);
	if ((empty() && !force) || !valid())
		return "";

	if (!one_line && !_children.empty())
		for (unsigned int i = 0; i < indent_level; i++)
			ss << indent_string;
	ss << "</" << name() << ">";
	return s;
}

QString xmlElement::format(bool one_line, bool force_non_empty, const QString& indent_string, unsigned int indent_level) const
{
	QString s;
	QTextStream ss(&s);

	if (!valid())
		return "";

	ss << formatOpening(one_line, force_non_empty, indent_string, indent_level);
	if (!empty()) {
		ss << formatContent(one_line, indent_string, indent_level);
	}
	if (!empty() || force_non_empty)
		ss << formatClosing(one_line, force_non_empty, indent_string, indent_level);
	return s;
}

};

