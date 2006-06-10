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

#include <oxml/xmlParser.h>
#include <oxml/xmlElement.h>
#include "oXMLConfig.h"

using onirXML::xmlParser;

//@cond 
#define XML_VERSION "1.0"
#define XML_ENCODING "UTF-8"
#define CONFIG_ROOT "config"
#define XPATH_SEPARATOR '/'
//@endcond

oXMLConfig::oXMLConfig(const QString& file, bool ld)
: oConfig()
{
	_root = NULL;
	_file = file;
	_parser = new xmlParser;
	if (ld)
		load();
}

oXMLConfig::~oXMLConfig()
{
	save();
	delete _parser;
}

bool oXMLConfig::load(const QString & f)
{
	_file = f;
	return load();
}

void oXMLConfig::createDoc()
{
	_root = new xmlElement;
	_root->name(CONFIG_ROOT);
}

bool oXMLConfig::load()
{
	if (!tryLoad()) {
		createDoc();
		return false;
	}
	return true;
}

bool oXMLConfig::tryLoad()
{
	_parser->parseFile(_file);
	if (!_parser->state() == xmlParser::finished)
		return false;
	
	_root = _parser->root();
	if (_root == NULL) {
		return false;
	}
	
	if (_root->name() != CONFIG_ROOT) {
		return false;
	}
	
	return true;
}

void oXMLConfig::file(const QString& f)
{
	_file = f;
}


QStringList oXMLConfig::parseXPath(const QString& xpath)
{
	return xpath.split(XPATH_SEPARATOR);
}

void oXMLConfig::save()
{
/*	ofstream f;
	f.open(_file.c_str(), ios::out | ios::trunc);
	f<<_rootNode->Format(false);*/
	// TODO
}


xmlElement * oXMLConfig::createXMLPath(const QStringList& v, bool create)
{
	xmlElement * pa = _root;	
	xmlElement * ch = NULL;

	for (QStringList::const_iterator i = v.begin(); i != v.end(); i++) {
		ch = pa->child(*i);
		if (ch != NULL)
			pa = ch;
		else if (create)
			pa = pa->addChild(*i, "");
		else
			return NULL;
	}
	return pa;
}

bool oXMLConfig::nodeExists(xmlElement * parent, const QString& name, int index)
{
	return static_cast<int>(parent->children().count(name)) > index;
}

xmlElement * oXMLConfig::removeNode(xmlElement * parent)
{
	if (parent == NULL)
		return NULL;
	parent->detach();
	return parent;
}

xmlElement * oXMLConfig::removeNode(const QString& xpath)
{
	return removeNode(node(xpath));
}	

xmlElement * oXMLConfig::setValue(const QString& parent, const QString& node, const QString& value, bool force)
{
	xmlElement * p = createXMLPath(parseXPath(parent));
	return setValue(p, node, value, force);
}

xmlElement * oXMLConfig::setValue(const QString& xpath, const QString& value, bool force)
{
	int pos = xpath.lastIndexOf(XPATH_SEPARATOR);
	if (pos == -1) {
		return setValue("", xpath, value, force);
	} else {
		return setValue(xpath.mid(0, pos), xpath.mid(pos + 1, xpath.size() - (pos + 1)), value, force);
	}
}

xmlElement * oXMLConfig::setValue(xmlElement * parent, const QString& subn, const QString& value, bool force)
{
	xmlElement * el = parent->child(subn);
	if ((!force) && (el != NULL)) {
		el->value(value);
		return el;
	} else {
		return parent->addChild(subn, value);
	}
}

QString  oXMLConfig::value(const QString& parent, const QString& node , const QString& defval)
{
	QStringList v = parseXPath(parent + XPATH_SEPARATOR + node);
	if (v.empty())
		return defval;	
	xmlElement * p = createXMLPath(v, false);
	if (p == NULL)
		return defval;

	return value(p, defval);
}

QString oXMLConfig::value(xmlElement * parent, const QString & name, const QString & defval)
{	
	QList<xmlElement *> pn;
	parent->children(name, pn);
	if (pn.empty())
		return defval;
	return value(pn.front(), defval);
}

QString oXMLConfig::value(xmlElement * parent, const QString& defval)
{
    return parent->value();
}

QString oXMLConfig::value(const QString& xpath, const QString& defval)
{
	int pos = xpath.lastIndexOf(XPATH_SEPARATOR);
	if (pos == -1){
		return value("", xpath, defval);
	}else{
		return value(xpath.mid(0, pos), xpath.mid(pos + 1, xpath.size() - (pos + 1)), defval);
	}
} 

xmlElement * oXMLConfig::node(xmlElement * parent, const QString& name)
{	
	return parent->child(name);	
}

xmlElement * oXMLConfig::node(const QString& xpath)
{
	return createXMLPath(parseXPath(xpath), false);
}

QVector<xmlElement *> oXMLConfig::children(const QString& parent)
{	
	return children(node(parent));		
}

QVector<xmlElement *> oXMLConfig::children(xmlElement * parent)	
{
	QMultiMap<QString, xmlElement *> childs;
	QVector<xmlElement *> ret;
	if (parent == NULL)
		return ret;
	parent->children(childs);
	for (QMultiMap<QString, xmlElement *>::iterator i = childs.begin(); i != childs.end(); i++) {
		ret.push_back(i.value());
	}
	return ret;
}

QVector<xmlElement *> oXMLConfig::children(xmlElement * parent, const QString& name)
{
	QList<xmlElement* > l;
	parent->children(name, l);
	QVector<xmlElement *> ret;
	for (QList<xmlElement *>::iterator it = l.begin(); it != l.end(); it++)
		ret.push_back(*it);
	return ret;
}

QString oXMLConfig::nodeName(xmlElement * p)
{
	return p != NULL ? p->name() : "";
}

xmlElement * oXMLConfig::root()
{
	return _root;
}

xmlElement * oXMLConfig::setValue(const QString& parent, const QString& node, int value, bool force)
{
	return setValue(parent, node, QString::number(value), force);
}

xmlElement * oXMLConfig::setValue(xmlElement * parent, const QString& subn, int value, bool force)
{
	return setValue(parent, subn, QString::number(value), force);
}

xmlElement * oXMLConfig::setValue(const QString& xpath, int value, bool force)
{
	return setValue(xpath, QString::number(value), force);
}
		
int oXMLConfig::value(const QString& parent, const QString& node, int defval)
{
	bool ok;
	int val;
	val = value(parent, node, QString::number(defval)).toInt(&ok);
	if (ok)
		return val;
	else
		return defval;
}

int oXMLConfig::value(xmlElement * parent, int defval)
{
	bool ok;
	int val;
	val = value(parent, QString::number(defval)).toInt(&ok);
	if (ok)
		return val;
	else
		return defval;
}

int oXMLConfig::value(xmlElement * parent, const QString& name, int defval)
{
	bool ok;
	int val;
	val = value(parent, name, QString::number(defval)).toInt(&ok);
	if (ok)
		return val;
	else
		return defval;
}

int oXMLConfig::value(const QString& xpath, int defval)
{
	bool ok;
	int val;
	val = value(xpath, QString::number(defval)).toInt(&ok);
	if (ok)
		return val;
	else
		return defval;
}

