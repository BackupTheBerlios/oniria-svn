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
#include <QByteArray>
#include <QXmlDefaultHandler>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include "xmlAttribute.h"
#include "xmlElement.h"
#include "xmlParser.h"

namespace onirXML {


/*void XMLCALL _xml_p_decl(void * data, const XML_Char * version, const XML_Char * encoding, int standalone)
{
	xmlParser * p = static_cast<xmlParser *>(data);
	if (encoding != NULL)
		p->Encoding(encoding);
}*/

class _xmlParserHandler : public QXmlDefaultHandler {
	public:
		inline _xmlParserHandler(xmlParser * parser) { _parser = parser; };

		virtual bool characters(const QString& ch);
		virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
		virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

	private:
		xmlParser * _parser;
};

bool _xmlParserHandler::characters(const QString& ch)
{
	_parser->parseCharacterData(ch);
	return true;
}

bool _xmlParserHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attrs)
{
	_parser->parseStartTag(qName, attrs);
	return true;
}

bool _xmlParserHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	_parser->parseEndTag(qName);
	return true;
}

struct xmlParser::__private {
	QXmlSimpleReader * reader;
	QXmlInputSource * source;
	_xmlParserHandler * handler;
};

xmlParser::xmlParser()
{
	_state = unknown;
	_root = _active = NULL;
	_private = NULL;

	prepare();
}

xmlParser::~xmlParser()
{
	cleanup();
}

void xmlParser::cleanup()
{
	if (_root != NULL) {
		delete _root;
		_root = NULL;
	}
	_active = NULL;

	if (_private != NULL) {
		if (_private->reader != NULL) {
			delete _private->reader;
			_private->reader = NULL;
		}
		if (_private->handler != NULL) {
			delete _private->handler;
			_private->handler = NULL;
		}
		if (_private->source != NULL) {
			delete _private->source;
			_private->source = NULL;
		}
		delete _private;
		_private = NULL;
	}

	_state = unknown;
}

bool xmlParser::prepare()
{
	cleanup();

	encoding("UTF-8");	// set default encoding

	_private = new __private;
	_private->handler = NULL;
	_private->source = NULL;
	_private->reader = NULL;
	_private->source = new QXmlInputSource();
	_private->handler = new _xmlParserHandler(this);
	_private->reader = new QXmlSimpleReader();

	_private->reader->setContentHandler(_private->handler);

	_state = ready;

	return true;
}

bool xmlParser::parse(const QByteArray& xml)
{
	QByteArray buf;

	if (state() != ready)
		return false;

	buf.append(_private->source->data());
	buf.append(xml);
	_private->source->setData(buf);
	if (state() == ready)
		return _private->reader->parse(_private->source, true);
	else if (state() == parsing)
		return _private->reader->parseContinue();
	else
		return false;
}

bool xmlParser::parse(const QString& xml)
{
	QByteArray buf;
	buf.append(xml);
	return parse(buf);
}

bool xmlParser::parseFile(const QString& fn)
{
	QFile f(fn);
	if (!f.open(QIODevice::ReadOnly))
		return false;
	return parseFile(&f);
}

bool xmlParser::parseFile(QIODevice * f)
{
	if (f == NULL)
		return false;

	while (!f->atEnd()) {
		if (!parse(f->readAll()))
			return false;
	}
	return true;
}

bool xmlParser::parseStartTag(const QString& el, const QXmlAttributes& attrs)
{
	xmlElement * elem;

	if (state() != ready && state() != parsing)
		return false;

	if (state() == ready && _active == NULL) {
		_root = new xmlElement;
		elem = _root;
		_state = parsing;
	} else {
		elem = new xmlElement;
	}

	elem->name(el);
	elem->encoding(encoding());
	for (int i = 0; i < attrs.count(); i++)
		elem->addAttribute(attrs.qName(i), attrs.value(i));

	if (_active != NULL)
		_active->addChild(elem);

	_active = elem;

	return true;
}

bool xmlParser::parseEndTag(const QString& el)
{
	if (state() != parsing || _active == NULL)
		return false;

	if (_active->name() != el)	// something wrong with XML
		return false;
	_active = _active->parent();

	if (_active == NULL)
		_state = finished;

	return true;
}

bool xmlParser::parseCharacterData(const QString& s)
{
	if (state() != parsing || _active == NULL)
		return false;

	_active->value(_active->value() + s);

	return true;
}

};

