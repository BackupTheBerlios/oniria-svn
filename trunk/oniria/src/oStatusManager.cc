/* $Id: oStatusManager.cc 628 2006-01-02 11:16:03Z choman $ */
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

#include <onir/xml/xmlElement.h>
#include <onir/xml/xmlAttribute.h>
#include <onir/utils/dconv.h>
#include "xConfig.h"
#include "gApp.h"
#include "oSessionManager.h"
#include "oStatusManager.h"

DEFINE_LOCAL_EVENT_TYPE(wxEVT_STATUS_CHANGE)

using namespace onirUtils;

oStatusManager::oStatusManager(gApp * app)
{
	_count = 15;
	_app = app;	
	_defaultStatus = static_cast<int>(imStatus::avail);
	LoadStatus();
}

oStatusManager::~oStatusManager()
{
	SaveStatus();
}

void oStatusManager::RegisterEventTarget(wxWindow * p, bool sent_initial)
{ 	
	if (sent_initial){
		wxCommandEvent event(wxEVT_STATUS_CHANGE);			
		event.SetString(_app->SessionManager()->Status().Description().c_str());
		event.SetInt(static_cast<int>(_app->SessionManager()->Status().Status()));
		p->ProcessEvent(event);
	}
	_eventTarget.push_back(p); 	
}

void oStatusManager::LoadStatus()
{	
	xmlElement * el = _app->Config()->NodeAt("status/history");	
	
	if (el == NULL)
		return;
	
	int count;
	if (!ToInt(el->AttributeValue("count", "15"), count))		
		count = 15;					
	
	vector<xmlElement *> e = _app->Config()->Children(el, "item");
	for (vector<xmlElement *>::iterator i = e.begin() ; i!=e.end(); ++i){
		if ((*i)->Attribute("default") != NULL)
			_defaultStatusDescription = (*i)->Value();
		_lastStatus.push_back(make_pair(SplitString((*i)->Value(), 20), (*i)->Value()));
	}
	
	Count(count);	
	
	el = _app->Config()->NodeAt("status");
	
	if (el != NULL){
		string def = el->AttributeValue("default", ToString(static_cast<int>(imStatus::avail)));		
		
		if (!ToInt(def, _defaultStatus)){		
			_defaultStatus = static_cast<int>(imStatus::avail);
		}
	}
	_app->SessionManager()->Status(Default(), false);
	SendStatusChange(Default().Status(), Default().Description());
}

void oStatusManager::SaveStatus()
{
	xmlElement * el;		
	_app->Config()->DeleteNode("status/history");

	for (deque<pair<string, string> >::iterator i = _lastStatus.begin(); i != _lastStatus.end(); ++i) {
		el = _app->Config()->StoreValue("status/history", "item", i->second, true);		
		if (_defaultStatusDescription == i->second){
			el->AddAttribute("default", "");
		}		
	}	
	el = _app->Config()->NodeAt("status");	
	xmlAttribute * attrib;
	if (el != NULL){
		attrib = el->Attribute("default");
		if (attrib == NULL){
			attrib = new xmlAttribute("default");
		}
		attrib->Value(ToString(_defaultStatus));
		el->AddAttribute(attrib);	
	}
		
	el = _app->Config()->NodeAt("status/history");
	if (el != NULL){
		attrib = el->Attribute("count");
		if (attrib == NULL){
			attrib = new xmlAttribute("count");
		}
		attrib->Value(ToString(_count));
		el->AddAttribute(attrib);
	}
	
}

imStatus oStatusManager::Default()
{
	return imStatus(static_cast<imStatus::status>(_defaultStatus), _defaultStatusDescription);	
}

void oStatusManager::Count(int c)
{
	_count = c;
	while((static_cast<int>(_lastStatus.size()) > _count) && !_lastStatus.empty()){
		_lastStatus.erase(_lastStatus.end() - 1);		
	}	
}

void oStatusManager::AddStatus(const string & status, bool def)
{	
	for (deque<pair<string, string> >::iterator i = _lastStatus.begin() ; i!=_lastStatus.end(); ++i){
		if (i->second == status){
			_lastStatus.erase(i);	
			break;	
		}
	}	
	_lastStatus.push_front(make_pair(SplitString(status, 20), status));
	if (static_cast<int>(_lastStatus.size()) > _count){
		_lastStatus.erase(_lastStatus.end() - 1);
	}
	if (def)
		_defaultStatusDescription = status;
}

void oStatusManager::SendStatusChange(imStatus::status status, const string &desc)
{
	wxCommandEvent event(wxEVT_STATUS_CHANGE);			
	event.SetString(desc.c_str());
	event.SetInt(status);
	for (list<wxWindow *>::iterator i = _eventTarget.begin(); i != _eventTarget.end(); ++i){
		if (*i)
			(*i)->ProcessEvent(event);
	}
}

void oStatusManager::Status(imStatus::status status, const string &desc, bool def)
{
	_app->SessionManager()->Status(imStatus(status, desc), true);
	AddStatus(desc, def);
	SendStatusChange(status, desc);
}
 
void oStatusManager::Status(imStatus::status status, bool def)
{
	Status(status, _app->SessionManager()->Status().Description(), def);			
}

void oStatusManager::Status(const string &desc, bool def)
{
	Status(_app->SessionManager()->Status().Status(), desc, def);			
}

void oStatusManager::Status(int status, const string &desc, bool def)
{
	Status(static_cast<imStatus::status>(status), desc, def);
}

void oStatusManager::Status(int status, bool def)
{
	Status(static_cast<imStatus::status>(status), def);
}
