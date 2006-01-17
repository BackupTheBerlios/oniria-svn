/* $Id: rcSkin.cc 614 2005-12-29 16:44:50Z choman $ */
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
#include <wx/filesys.h>
#include "../xml/xmlParser.h"
#include "rcSkin.h"

using onirXML::xmlParser;

namespace onirRC {

DEFINE_OOBJECT(rcSkin, rcFileResource);

rcSkin::rcSkin(oOniria * o)
: rcFileResource(o)
{
	_skin_xml = NULL;
	INIT_OOBJECT;
}

rcSkin::~rcSkin()
{
	if (_skin_xml != NULL)
		delete _skin_xml;
}

bool rcSkin::Prepare(const string& file, rcPack * owner, xmlElement * xml)
{
	rcFileResource::Prepare(file, owner, xml);
	if (!xml->AttributeValue("file").empty()) {
		xmlParser parser;
		wxFSFile * f;

		f = Open();
		parser.Prepare();
		if (parser.ParseFile(f))
			_skin_xml = parser.Detach();
		delete f;
	} else {
		_skin_xml = xml->Detach("skin");
	}

	if (_skin_xml != NULL)
		PrepareElement(file, _skin_xml);
	return _skin_xml != NULL;
}

void rcSkin::PrepareElement(const string& file, xmlElement * el)
{
	list<xmlElement *> incs;
	multimap<string, xmlElement *> childs;

	el->Detach("include", incs);
	for (list<xmlElement *>::iterator it = incs.begin(); it != incs.end(); it++) {
		xmlParser parser;
		wxFSFile * f;
		wxFileSystem fs;

		f = fs.OpenFile(file + "#zip:" + (*it)->AttributeValue("file"));
	
		parser.Prepare();
		if (parser.ParseFile(f))
			el->AddChild(parser.Detach());
		delete f;
		delete *it;
	}
	
	el->Children(childs);
	for (multimap<string, xmlElement *>::iterator it = childs.begin(); it != childs.end(); it++)
		PrepareElement(file, it->second);
}

xmlElement * rcSkin::XMLValue(xmlElement * parent, const string& pid, const string& id)
{
	string tid, parsed;
	xmlElement * el;
	string::size_type pos;
	string eln;
	string ref;

	
	pos = id.find(":");
	eln.assign(id, 0, pos);
	el = parent->Child(eln);
	
	if (el == NULL)
		return NULL;
		
	if (!pid.empty())
		parsed = pid + ":";
	parsed += eln;

	if (pos == string::npos)	// leaf
		return el;

	parent = el;
	tid = string(id, pos + 1);
	el = XMLValue(parent, parsed, tid);

	if (el == NULL) {
		ref = parent->AttributeValue("ref");
		if (ref != "") {
			if (ref[0] == ':') {	// non-relative reference
				return XMLValue(_skin_xml, "", string(ref, 1) + ":" + tid);
			} else {		// relative reference
				return XMLValue(_skin_xml, "", pid + ":" + ref + ":" + tid);
			}
		}
	}

	return el;
}

xmlElement * rcSkin::XMLValue(const string& id)
{
	return XMLValue(_skin_xml, "", id);
}

string rcSkin::StringValue(const string& id, const string& def)
{
	xmlElement * el;
	
	el = XMLValue(id);
	if (el != NULL)
		return el->Value();
	else
		return def;
}

wxColour rcSkin::ColourValue(const string& id, const wxColour& def)
{
	string val;
	val = StringValue(id, "");
	if (val.empty())
		return def;
	
	if (val[0] == '#') {
		unsigned char r, g, b;
		
		r = strtol(string(val, 1, 2).c_str(), NULL, 16);
		g = strtol(string(val, 3, 2).c_str(), NULL, 16);
		b = strtol(string(val, 5, 2).c_str(), NULL, 16);
		
		return wxColour(r, g, b);
	} else {
		return wxColour(val);
	}
}

int rcSkin::IntValue(const string& id, int def)
{
	string val;
	val = StringValue(id, "");
	if (val.empty())
		return def;

	return strtol(val.c_str(), NULL, 0);
}

unsigned int rcSkin::UIntValue(const string& id, unsigned int def)
{
	string val;
	val = StringValue(id, "");
	if (val.empty())
		return def;

	return strtoul(val.c_str(), NULL, 0);
}

bool rcSkin::BoolValue(const string& id, bool def)
{
	xmlElement * el;
	
	el = XMLValue(id);
	if (el != NULL) {
		string value = el->AttributeValue("value");
		if (value == "1" || value == "true" || value == "yes")
			return true;
		else if (value == "0" || value == "false" || value == "no")
			return false;
		else
			return true;
	} else {
		return def;
	}
}

void rcSkin::SetupFont(wxFont * font, const string& id)
{
	if (BoolValue(id + ":bold", font->GetWeight() == wxFONTWEIGHT_BOLD))
		font->SetWeight(wxFONTWEIGHT_BOLD);
	else
		font->SetWeight(wxFONTWEIGHT_NORMAL);
	font->SetPointSize(UIntValue(id + ":size", font->GetPointSize()));
	font->SetFaceName(StringValue(id + ":face", static_cast<string>(font->GetFaceName())));
	if (BoolValue(id + ":italic", font->GetStyle() == wxFONTSTYLE_ITALIC))
		font->SetStyle(wxFONTSTYLE_ITALIC);
	else
		font->SetStyle(wxFONTSTYLE_NORMAL);
	font->SetUnderlined(BoolValue(id + ":underlined", font->GetUnderlined()));
}

};

