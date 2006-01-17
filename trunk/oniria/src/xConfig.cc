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


#include <algorithm>
#include <map>
#include <onir/utils/dconv.h>
#include <onir/utils/uException.h>
#include <onir/xml/xmlParser.h>
#include <onir/xml/xmlElement.h>
#include <fstream>
#include "xConfig.h"

using onirXML::xmlParser;
using namespace std;


/// @cond 
/** doxygen skip this section
 * 
 */

#define XML_VERSION "1.0"
#define XML_ENCODING "UTF-8"
#define CONFIG_ROOT "config"
#define SEPARATE_CHAR '/'

///@endcond

using namespace onirUtils;


xConfig::xConfig(const string & file,bool load)
:oConfig()
{
	_rootNode = NULL;
	_file = file;
	_parser = new xmlParser;
	if (load)
		Load();
}

xConfig::~xConfig()
{
	Flush();
    delete _parser;
}

bool xConfig::Load(const string & file)
{
	_file = file;
	return Load();
}
void xConfig::CreateDoc()
{
		_rootNode = new xmlElement;
		_rootNode->Name(CONFIG_ROOT); 
}

bool xConfig::Load()
{
	if (!TryLoad()){		
		CreateDoc();			
		return false;
	}		
	return true;
}

bool xConfig::TryLoad()
{
	_parser->ParseFile(_file.c_str());
	if (!_parser->State() == xmlParser::finished)
        return false;
	
	_rootNode = _parser->Root();
	if (_rootNode == NULL) {
		return false;
	}
	
	if (_rootNode->Name() != CONFIG_ROOT) {
		return false;
	}	
	
	return true;
}

void xConfig::File(const string & file)
{
	_file=file;
}


list<string>  xConfig::ParseCoors(const string & coors)
{
	list<string> vp;
	string c = coors;	
	if (c.empty())
		return vp;
	
	if (c[c.size()] != SEPARATE_CHAR)
		c += SEPARATE_CHAR;
		
	string::size_type pos;
	string tmp;	
	int val=0;
	while ((pos = c.find(SEPARATE_CHAR)) != string::npos){
		val = 0;
		tmp = c.substr(0, pos);
		c.erase(0, pos + 1);
		vp.push_back(tmp);
	}
	return vp;
}

void xConfig::Flush()
{
	ofstream f;
	f.open(_file.c_str(), ios::out | ios::trunc);
	f<<_rootNode->Format(false);
}


xmlElement * xConfig::ProcessNodesCreate(const list<string> & v, bool create)
{
	list<xmlElement *> p;
	xmlElement *pa = _rootNode;	
	xmlElement *child = NULL;
	list<string> va;
	list<xmlElement *> tmp;
	copy(v.begin(), v.end(), back_inserter(va));
	for (list<string>::iterator i = va.begin(); i != va.end(); ++i){
		child = pa->Child(*i);
		if (child != NULL){		
			pa = child;
		}else if (create){
			pa = pa->AddChild(*i, "");			
		}else
             return NULL;
	}
	return pa;	
}

bool xConfig::NodeExists(xmlElement * parent,const string &name,int index)
{
	return static_cast<int>(parent->Children().count(name)) > index;
}

void xConfig::DeleteNode(xmlElement * parent)
{
	if (parent == NULL)
        return;
    parent->Detach();
}

void xConfig::DeleteNode(const string & coors)
{
	DeleteNode(NodeAt(coors));
}	

xmlElement * xConfig::StoreValue(const string & parent,const string & node,const string & value, bool force)
{
	list<string> v = ParseCoors(parent);
	xmlElement * p = ProcessNodesCreate(v);
	return StoreValue(p, node, value, force);
}

xmlElement * xConfig::StoreValueNs(const string & coors, const string & value, bool force)
{
	string::size_type pos = coors.rfind(SEPARATE_CHAR);
	if (pos==string::npos){
		return StoreValue("",coors,value, force);
	}else{
		return StoreValue(coors.substr(0, pos ), coors.substr(pos + 1, coors.size() - (pos + 1)), value, force);
	}
}

xmlElement *xConfig::StoreValue(xmlElement * parent, const string & subn, const string & value, bool force)
{
	xmlElement * el = parent -> Child(subn);	
	if ((!force) && (el != NULL)){		
		el->Value(value);                            
		return el;
	}else{
        return parent->AddChild(subn, value);
    }
}

string  xConfig::Value(const string & parent, const string & node , const string & defval)
{
	list<string> v = ParseCoors(parent + SEPARATE_CHAR + node);
	if (v.empty())
		return defval;	
	xmlElement * p = ProcessNodesCreate(v, false);
	if (p == NULL)
		return defval;

	return Value(p, defval);
}

string xConfig::Value(xmlElement * parent, const string & name, const string & defval)
{	
	list<xmlElement *> pn;
	parent->Children(name, pn);
	if (pn.empty())
		return defval;
    return Value(pn.front(), defval);
}

string xConfig::Value(xmlElement * parent, const string & defval)
{
    return parent->Value();
}

string xConfig::ValueNs(const string & coors, const string & defval)
{
	string::size_type pos = coors.rfind(SEPARATE_CHAR);
	if (pos==string::npos){
		return Value("",coors,defval);
	}else{
		return Value(coors.substr(0, pos ), coors.substr(pos + 1, coors.size() - (pos + 1)), defval);
	}
} 

xmlElement * xConfig::NodeAt(xmlElement * parent, const string & name)
{	
	return parent->Child(name);	
}

xmlElement * xConfig::NodeAt(const string & coors)
{
	return ProcessNodesCreate(ParseCoors(coors), false);
}

vector<xmlElement *> xConfig::Children(const string & parent)
{	
	return Children(NodeAt(parent));		
}

vector<xmlElement *> xConfig::Children(xmlElement * parent)	
{
	multimap<string, xmlElement *> childs;
	vector<xmlElement *> ret;
	if (parent == NULL)
        return ret;
	parent->Children(childs);	
	for (multimap<string, xmlElement *>::iterator i = childs.begin(); i!= childs.end(); ++i){
		ret.push_back(i->second);
	}	
	return ret;
}

vector<xmlElement *> xConfig::Children(xmlElement * parent, const string name)
{
	list<xmlElement* > l;
	parent->Children(name, l);
	vector<xmlElement *> ret;
	std::copy(l.begin(), l.end(), std::back_inserter(ret));
	return ret;
}

string xConfig::NodeName(xmlElement * p)
{
	return p != NULL ? p->Name() : "";
}

xmlElement * xConfig::Root()
{
	return _rootNode;
}

xmlElement * xConfig::StoreValue(const string & parent, const string & node, int value, bool force)
{
	return StoreValue(parent, node, ToString(value), force);
}

xmlElement * xConfig::StoreValue(xmlElement * parent, const string & subn,int value, bool force)
{
	return StoreValue(parent, subn, ToString(value), force);
}

xmlElement * xConfig::StoreValueNs(const string & coors, int value, bool force)
{
	return StoreValueNs(coors, ToString(value), force);
}
		
int xConfig::Value(const string & parent, const string & node, int defval)
{
	try{
		return ToInt(Value(parent, node, ToString(defval)));
	}catch(uException c){
		return defval;
	}
}

int xConfig::Value(xmlElement * parent, int defval)
{
	try{
		return ToInt(Value(parent, ToString(defval)));
	}catch(uException c){
		return defval;
	}
}

int xConfig::Value(xmlElement * parent, const string & name, int defval)
{
	try{
		return ToInt(Value(parent, name, ToString(defval)));
	}catch(uException c){
		return defval;
	}	
}

int xConfig::ValueNs(const string & coors, int defval)
{
	try{
		return ToInt(ValueNs(coors, ToString(defval)));
	}catch(uException c){
		return defval;
	}
}
