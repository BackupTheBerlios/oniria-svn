/* $Id: xmlStream.cc 636 2006-01-03 14:04:42Z choman $ */
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
void XMLCALL _xml_start_tag(void * data, const char * el, const char ** attr)
{
	xmlStream * ps = static_cast<xmlStream *>(data);
	ps->ParseStartTag(el, attr);
}

void XMLCALL _xml_end_tag(void * data, const char * el)
{
	xmlStream * ps = static_cast<xmlStream *>(data);
	ps->ParseEndTag(el);
}

void XMLCALL _xml_character_data(void * data, const XML_Char * s, int len)
{
	xmlStream * ps = static_cast<xmlStream *>(data);
	ps->ParseCharacterData(QString(s, len));
}

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

	private:
		xmlStream * _stream;
};

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
		//XML_ParserFree(_private->parser);
		delete _private;
		_private = NULL;
	}

	_input = "";
	_output = "";
	
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
}

bool xmlStream::initiate()
{
	QTextStream os;

	if (output() == NULL || input() == NULL)
		return false;

	if (state() != ready)
		return false;

	_input = "";
	_output = "<?xml version='1.0'?>";

	// Prepare root element, and add to queue
	_output += _out_root->formatOpening(true, true);	// open stream
	
	_state = initiating;

	return true;
}

bool xmlStream::poll()
{
	QByteArray buf;

	if (state() != initiating && state() != established && state() != stanza && state() != closing)
		return false;

/*	if (input()->Read(&buf, 0, false) > 0)
		_input += buf.str();

	// format and send stanzas
	if (State() == established) {
		for (list<xmlStanza *>::iterator it = _out_stanzas.begin(); it != _out_stanzas.end(); it++) {
			_output += (*it)->Format();
			delete (*it);
		}
		_out_stanzas.clear();
	}
	if (!_output.empty()) {
		size_t wr;
		buf.Copy(_output.c_str(), _output.size());
		wr = Output()->Write(&buf, 0, false);
		if (wr > 0)
			_output.erase(0, wr);
	}
*/
	return parse();
}

bool xmlStream::close()
{
	_state = closing;
	_output += _out_root->formatClosing(true, true);
	return false;
}

bool xmlStream::parse()
{
	if (_input.isEmpty())
		return false;

	//XML_Parse(_private->parser, _input.c_str(), _input.size(), 0);
	_input = "";

	return true;
}

void xmlStream::parseStartTag(const char * elem, const char ** attrs)
{
	if (state() == initiating) {
		if (QString(elem) == QString("stream:stream")) {		// input root
			_in_root->name(elem);
			for (int i = 0; attrs[i]; i += 2)
				_in_root->addAttribute(attrs[i], attrs[i+1]);

			_state = established;
		} else {
			// stream is errorneus
			_state = error;

			/*!\todo Prepare error response. */

			_output += "</stream:stream>";
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

void xmlStream::parseEndTag(const char * elem)
{
	if (state() == stanza) {		// forward parsing to active stanza
		if (_active_stanza != NULL) {
			if (!_active_stanza->parseEndTag(elem)) {
				if (_active_stanza->valid()) {
					emit receivedStanza(_active_stanza);
					_active_stanza = NULL;
					_state = established;
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

void xmlStream::addStanza(xmlStanza * stanza)
{
	if (stanza != NULL)
		_out_stanzas.push_back(stanza);
}

};
