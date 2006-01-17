/* $Id: xmlParser.cc 614 2005-12-29 16:44:50Z choman $ */
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
#include <sstream>
#include <fstream>
#include <wx/filesys.h>
#include <expat.h>
#include "../utils/uBuffer.h"
#include "xmlAttribute.h"
#include "xmlElement.h"
#include "xmlParser.h"


using namespace std;
using onirUtils::uBuffer;

namespace onirXML {

DEFINE_OOBJECT(xmlParser, oObject);

struct xmlParser::__private {
	XML_Parser parser;
};

void XMLCALL _xml_p_start_tag(void * data, const char * el, const char ** attr)
{
	xmlParser * p = static_cast<xmlParser *>(data);
	if (!p->ParseStartTag(el, attr))
		XML_StopParser(p->_private->parser, FALSE);
}

void XMLCALL _xml_p_end_tag(void * data, const char * el)
{
	xmlParser * p = static_cast<xmlParser *>(data);
	if (!p->ParseEndTag(el))
		XML_StopParser(p->_private->parser, FALSE);
}

void XMLCALL _xml_p_character_data(void * data, const XML_Char * s, int len)
{
	xmlParser * p = static_cast<xmlParser *>(data);
	if (!p->ParseCharacterData(string(s, len)))
		XML_StopParser(p->_private->parser, FALSE);
}

void XMLCALL _xml_p_decl(void * data, const XML_Char * version, const XML_Char * encoding, int standalone)
{
	xmlParser * p = static_cast<xmlParser *>(data);
	if (encoding != NULL)
		p->Encoding(encoding);
}

xmlParser::xmlParser()
{
	INIT_OOBJECT;

	_state = unknown;
	_root = _active = NULL;
	_private = NULL;

	Prepare();
}

xmlParser::~xmlParser()
{
	Cleanup();
}

void xmlParser::Cleanup()
{
	if (_root != NULL) {
		delete _root;
		_root = NULL;
	}
	_active = NULL;

	if (_private != NULL) {
		XML_ParserFree(_private->parser);
		delete _private;
		_private = NULL;
	}
	
	_state = unknown;
}

bool xmlParser::Prepare()
{
	Cleanup();

	Encoding("UTF-8");	// set default encoding

	_private = new __private;
	_private->parser = XML_ParserCreate(NULL);
	XML_SetUserData(_private->parser, this);
	XML_SetElementHandler(_private->parser, _xml_p_start_tag, _xml_p_end_tag);
	XML_SetCharacterDataHandler(_private->parser, _xml_p_character_data);

	_state = ready;

	return true;
}

bool xmlParser::Parse(const char * xml, size_t sz)
{
	if (sz == 0)
		sz = strlen(xml);

	return XML_Parse(_private->parser, xml, sz, 0) == XML_STATUS_OK;
}

bool xmlParser::Parse(const string& xml)
{
	return Parse(xml.c_str(), xml.size());
}


bool xmlParser::ParseFile(const string& fn)
{
	wxFileSystem fs;
	wxFSFile * f;
	bool b;

	f = fs.OpenFile(fn);
	if (f == NULL)
		return false;
	b = ParseFile(f);
	delete f;
	return b;
}

bool xmlParser::ParseFile(wxFSFile * f)
{
	static char buf[8192];
	
	if (f == NULL)
		return false;

	while (!f->GetStream()->Eof()) {
		f->GetStream()->Read(buf, 8192);
		if (!Parse(buf, f->GetStream()->LastRead()))
			return false;
	}
	return true;
}

bool xmlParser::ParseStartTag(const char * el, const char ** attrs)
{
	xmlElement * elem;

	if (State() != ready && State() != parsing)
		return false;

	if (State() == ready && _active == NULL) {
		_root = new xmlElement;
		elem = _root;
		_state = parsing;
	} else {
		elem = new xmlElement;
	}

	elem->Name(el);
	elem->Encoding(Encoding());
	for (int i = 0; attrs[i]; i += 2)
		elem->AddAttribute(attrs[i], attrs[i+1]);

	if (_active != NULL)
		_active->AddChild(elem);

	_active = elem;

	return true;
}

bool xmlParser::ParseEndTag(const char * el)
{
	if (State() != parsing || _active == NULL)
		return false;

	if (_active->Name() != el)	// something wrong with XML
		return false;
	_active = _active->Parent();

	if (_active == NULL)
		_state = finished;

	return true;
}

bool xmlParser::ParseCharacterData(const string& s)
{
	if (State() != parsing || _active == NULL)
		return false;

	_active->Value(_active->Value() + s);

	return true;
}

};
