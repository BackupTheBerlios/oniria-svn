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
#include <QTextStream>
#include <QByteArray>
#include <QXmlDefaultHandler>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include "xmlElement.h"
#include "xmlStanza.h"
#include "xmlStream.h"

namespace onirXML {

/*
void XMLCALL _xml_decl(void * data, const XML_Char * version, const XML_Char * encoding, int standalone)
{
	xmlStream * ps = static_cast<xmlStream *>(data);
	if (encoding != NULL)
		ps->Encoding(encoding);
}
*/

class _xmlStreamHandler : public QXmlDefaultHandler {
	public:
		inline _xmlStreamHandler(xmlStream * stream) { _stream = stream; };

		virtual bool characters(const QString& ch);
		virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
		virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);

	private:
		xmlStream * _stream;
};

bool _xmlStreamHandler::characters(const QString& ch)
{
	_stream->parseCharacterData(ch);
	return true;
}

bool _xmlStreamHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attrs)
{
	_stream->parseStartTag(qName, attrs);
	return true;
}

bool _xmlStreamHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
	_stream->parseEndTag(qName);
	return true;
}

struct xmlStream::__private {
	QXmlSimpleReader * reader;
	QXmlInputSource * source;
	_xmlStreamHandler * handler;
};

xmlStream::xmlStream()
{
	input(NULL);
	output(NULL);
	_state = unknown;
	_in_root = _out_root = NULL;
	_private = NULL;
}

xmlStream::xmlStream(QIODevice * istream, QIODevice * ostream)
{
	input(istream);
	if (ostream == NULL)
		output(istream);
	else
		output(ostream);
	_state = unknown;
	_in_root = _out_root = NULL;
	_private = NULL;
}

xmlStream::~xmlStream()
{
	cleanup();
}

QIODevice * xmlStream::input(QIODevice * istream)
{
	QIODevice * old = input();
	_istream = istream;
	return old;
}

QIODevice * xmlStream::output(QIODevice * ostream)
{
	QIODevice * old = output();
	_ostream = ostream;
	return old;
}

void xmlStream::cleanup()
{
	if (_in_root != NULL) {
		delete _in_root;
		_in_root = NULL;
	}

	if (_out_root != NULL) {
		delete _out_root;
		_out_root = NULL;
	}

	_active_stanza = NULL;

	for (QList<xmlStanza *>::iterator it = _out_stanzas.begin(); it != _out_stanzas.end(); it++)
		delete *it;
	_out_stanzas.clear();

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

	_input_b = "";
	_output_b = "";
	
	_state = unknown;
}

bool xmlStream::prepare()
{
	cleanup();
	encoding("UTF-8");	// set default encoding

	_private = new __private;
	_private->handler = NULL;
	_private->source = NULL;
	_private->reader = NULL;
	_private->source = new QXmlInputSource();
	_private->handler = new _xmlStreamHandler(this);
	_private->reader = new QXmlSimpleReader();

	_private->reader->setContentHandler(_private->handler);
	_private->reader->setFeature("http://xml.org/sax/features/namespace-prefixes", true);
	_private->reader->setFeature("http://xml.org/sax/features/namespaces", false);

	_in_root = new xmlElement;

	_out_root = new xmlElement;
	_out_root->name("stream:stream");

	QObject::connect(input(), SIGNAL(readyRead()),
			this, SLOT(readyRead()));

	_state = ready;

	return true;
}

void xmlStream::readyRead()
{
	_input_b.append(input()->readAll());
	parse();
}

bool xmlStream::initiate()
{
	QTextStream os;

	if (output() == NULL || input() == NULL)
		return false;

	if (state() != ready)
		return false;

	_input_b = "";
	_output_b = "<?xml version='1.0'?>";

	// Prepare root element, and add to queue
	_output_b.append(_out_root->formatOpening(true, true));	// open stream
	
	_state = initiating;

	flush();

	return true;
}

bool xmlStream::poll()
{
	QByteArray buf;

	if (state() != initiating && state() != established && state() != stanza && state() != closing)
		return false;

	readyRead();
	flush();

	return true;
}

bool xmlStream::close()
{
	_state = closing;
	_output_b.append(_out_root->formatClosing(true, true));
	return false;
}

bool xmlStream::parse()
{
	QByteArray b;
	bool ok;
	int numb;

	b.append(_private->source->data());
	b.append(_input_b);
	_input_b = "";

	// Qt XML parser is so stupid to parse only valid chunk of xml, and preserve
	// rest for next pass, so we must do that manually
	
	ok = false;
	numb = b.size();
	while (!ok) {
		_private->source->setData(b.left(numb));
		if (state() == initiating) {
			ok =  _private->reader->parse(_private->source, true);
		} else {
			ok = _private->reader->parseContinue();
		}
		// try to parse smaller buffer as long as numb > 0
		if (numb > 0)
			numb--;
		else
			break;
	}
	_private->source->setData(QByteArray());		// reset source
	_input_b = b.right(b.size() - numb);	// preserve rest for next try

	return true;
}

void xmlStream::parseStartTag(const QString& elem, const QXmlAttributes& attrs)
{
	if (state() == initiating) {
		if (QString(elem) == QString("stream:stream")) {		// input root
			_in_root->name(elem);
			for (int i = 0; i < attrs.count(); i++)
				_in_root->addAttribute(attrs.qName(i), attrs.value(i));

			_state = established;
		} else {
			// stream is errorneus
			_state = error;

			/*!\todo Prepare error response. */

			_output_b.append("</stream:stream>");
		}
		
	} else if (state() == established) {	// new stanza arrived
		_active_stanza = new xmlStanza;
		if (_active_stanza->parseStartTag(elem, attrs))
			_state = stanza;
	} else if (state() == stanza) {		// forward parsing to active stanza
		if (_active_stanza != NULL) {
			if (!_active_stanza->parseStartTag(elem, attrs)) {
				if (!_active_stanza->valid()) {
					_state = error;
				} else {
					emit receivedStanza(_active_stanza);
					_active_stanza = NULL;
					_state = established;
				}
			}
		}
	}
}

void xmlStream::parseEndTag(const QString& elem)
{
	if (state() == stanza) {		// forward parsing to active stanza
		if (_active_stanza != NULL) {
			if (!_active_stanza->parseEndTag(elem)) {
				if (_active_stanza->valid()) {
					xmlStanza * as = _active_stanza;
					_active_stanza = NULL;
					_state = established;
					emit receivedStanza(as);
				} else {
					_state = error;
				}
			}
		}
	}
}

void xmlStream::parseCharacterData(const QString& s)
{
	if (state() == stanza) {
		if (_active_stanza != NULL) {
			_active_stanza->parseCharacterData(s);
		}
	}
}

void xmlStream::addStanza(xmlStanza * st)
{
	if (st != NULL)
		_out_stanzas.push_back(st);
	flush();
}

void xmlStream::flush()
{
	// format and send stanzas
	if (state() == established) {
		for (QList<xmlStanza *>::iterator it = _out_stanzas.begin(); it != _out_stanzas.end(); it++) {
			_output_b.append((*it)->format());
			delete (*it);
		}
		_out_stanzas.clear();
	}
	if (!_output_b.isEmpty()) {
		qint64 wr;
		wr = output()->write(_output_b);
		if (wr > 0)
			_output_b.remove(0, wr);
	}
}

};
