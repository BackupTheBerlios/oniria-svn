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
#include <iostream>
#include <onir/utils/uException.h>
#include <onir/im/imProtocol.h>
#include <onir/im/imSession.h>
#include <onir/im/imMessageQueue.h>
#include <onir/im/imMessageThread.h>
#include <onir/im/imMessage.h>
#include <onir/oConfig.h>
#include <onir/oEventForwarder.h>
#include <onir/xml/xmlElement.h>
#include <onir/oTabs.h>
#include "gApp.h"
#include "oEventManager.h"
#include "gRoster.h"
#include "oStatusManager.h"
#include "uiChat.h"
#include "oSessionManager.h"

using namespace onirIM;
using onir::oEventForwarder;
using onirUtils::uException;

namespace onirXML{
	class xmlElement;
};

using onirXML::xmlElement;

DEFINE_OOBJECT(oSessionManager, oEventTarget);

oSessionManager::oSessionManager(gApp * app)
{
	_app = app;
	_status.Set(imStatus::avail);
	INIT_OOBJECT;
}

oSessionManager::~oSessionManager()
{
}

bool oSessionManager::RegisterProtocol(imProtocol * proto)
{
	if (_protocols.find(proto->ProtocolId()) != _protocols.end())
		throw uException(_("Protocol already registered."));
	_protocols[proto->ProtocolId()] = proto;
	return true;
}

imProtocol * oSessionManager::FindProtocol(const string& id)
{
	if (_protocols.find(id) == _protocols.end())
		return NULL;
	return _protocols[id];
}

int oSessionManager::LoadSessions()
{
	vector<xmlElement *> snodes;
	int sessions;

	snodes = _app->Config()->Children("sessions");
	if (snodes.empty())
		return 0;
	sessions = 0;
	for (vector<xmlElement *>::iterator i = snodes.begin(); i != snodes.end(); i++) {
		if (_app->Config()->NodeName(*i) == "session") {
			imProtocol * proto;

			proto = FindProtocol(_app->Config()->Value(*i, "protocol", ""));
			if (proto == NULL) {
				wxLogMessage("oSessionManager: Session with unknown protocol: %s", _app->Config()->Value(*i, "protocol", "").c_str());
			} else {
				imSession * s;
                
				s = proto->CreateSession(_app->Oniria());
				s->Prepare();
				if (s != NULL) {
					s->Load(*i);
					_sessions[s->SessionId()] = s;
					CreateRosterWindow(s);
					wxLogMessage("oSessionManager: Loaded session \"%s\", protocol: %s.", s->Name().c_str(), proto->ProtocolName().c_str());
				}
			}
			
		}
	}
	return _sessions.size();
}

int oSessionManager::ConnectSessions(bool all)
{
	_active_sessions.clear();
	for (map<string, imSession *>::iterator it = _sessions.begin(); it != _sessions.end(); it++) {
		if (all || it->second->AutoConnect()) {
			if (it->second->Connect(true)) {
				_active_sessions[it->second->SessionId()] = it->second;
				it->second->Status(_status, false);
			}
		}
	}
	return _active_sessions.size();
}

void oSessionManager::Poll()
{
	map<string, imSession *>::iterator it = _active_sessions.begin();
	while (it != _active_sessions.end()) {
		if (!it->second->Poll()) {
			string k = it->first;
			it++;
			_active_sessions.erase(k);
		} else {
			ProcessMessageQueue(it->second);
			it++;
		}
	}
}

void oSessionManager::ProcessMessageQueue(imSession * s)
{
	for (map<string, imMessageThread *>::iterator it = s->MessageQueue()->Threads()->begin(); it != s->MessageQueue()->Threads()->end(); it++) {
		imMessage * msg;
		if (it->second->UI() == NULL) {
			oEvent * event;
			event = new oEvent("oniria:im:session:thread:ui:create");
			event->XML()->AddChild("session-id", s->SessionId());
			event->XML()->AddChild("thread-id", it->second->Id());
			_app->EventManager()->Process(event);
			if (it->second->UI() != NULL)
				it->second->UI()->Create();
		}
		while ((msg = it->second->NextInMessage()) != NULL) {
			if (it->second->UI() != NULL) {
				it->second->UI()->DisplayMessage(msg);
				delete msg;
			}
		}
		while ((msg = it->second->NextOutMessage()) != NULL) {
			s->SendMessage(msg);
			delete msg;
		}
	}
}

bool oSessionManager::StartThread(const string& session_id, const string& roster_id)
{
	imSession * s;
	imMessageThread * th;
	oEvent * event;

	if (_active_sessions.find(session_id) == _active_sessions.end())
		throw uException(_("Unknown session."));

	s = _active_sessions[session_id];

	th = s->MessageQueue()->GetThread("msg", roster_id, "");

	event = new oEvent("oniria:im:session:thread:ui:create");
	event->XML()->AddChild("session-id", s->SessionId());
	event->XML()->AddChild("thread-id", th->Id());
	_app->EventManager()->Process(event);
	if (th->UI() != NULL)
		th->UI()->Create();
	
	return true;
}

void oSessionManager::Status(const imStatus& status, bool set)
{
	_status = status;
	for (map<string, imSession *>::iterator it = _active_sessions.begin(); it != _active_sessions.end(); it++) {
		it->second->Status(_status, set);
	}
}

wxWindow * oSessionManager::CreateRosterWindow(imSession * s)
{	
    _rosters[s->SessionId()] = new gRoster(_app, _app->TabManager()->ParentWindow());
	_app->TabManager()->RegisterPage(s->SessionId(), s->Name(), _rosters[s->SessionId()], "roster");	
	return _rosters[s->SessionId()];
}

imSession * oSessionManager::EventSession(oEvent * event)
{
	imSession * s;

	if (_sessions.find(event->XML()->ChildValue("session-id")) == _sessions.end())
		throw uException(_("Unknown session."));

	s = _sessions[event->XML()->ChildValue("session-id")];
	
	return s;
}

void oSessionManager::RegisterEventHandlers()
{
	_app->EventManager()->RegisterHandler("oniria:im:session:connected", new oEventForwarder(this));
	_app->EventManager()->RegisterHandler("oniria:im:session:roster:updated", new oEventForwarder(this));
	_app->EventManager()->RegisterHandler("oniria:im:session:roster:item:presence", new oEventForwarder(this));
	_app->EventManager()->RegisterHandler("oniria:im:session:roster:item:new", new oEventForwarder(this));
	_app->EventManager()->RegisterHandler("oniria:im:session:thread:ui:create", new oEventForwarder(this));
}

bool oSessionManager::ProcessEvent(oEvent * event)
{
	ROUTE_EVENT(event, "oniria:im:session:connected", SessionConnected);
	ROUTE_EVENT(event, "oniria:im:session:roster:updated", RosterUpdated);
	ROUTE_EVENT(event, "oniria:im:session:roster:item:presence", RosterPresence);
	ROUTE_EVENT(event, "oniria:im:session:roster:item:new", RosterNewItem);
	ROUTE_EVENT(event, "oniria:im:session:thread:ui:create", ThreadUICreate);
	return true;
}

bool oSessionManager::SessionConnected(oEvent * event)
{
	imSession * s;
	
	s = EventSession(event);

	s->SyncRoster(false);
	s->SetStatus();

	return true;
}

bool oSessionManager::RosterUpdated(oEvent * event)
{
	imSession * s;
	gRoster * rwnd;
	
	s = EventSession(event);
	
	rwnd = _rosters[s->SessionId()];
	rwnd->UpdateTree(s->Roster());

	return true;
}

bool oSessionManager::RosterPresence(oEvent * event)
{
	imSession * s;
	gRoster * rwnd;
	
	s = EventSession(event);
	
	rwnd = _rosters[s->SessionId()];
	rwnd->UpdateItem(event->XML()->ChildValue("item-id"));

	return true;
}

bool oSessionManager::RosterNewItem(oEvent * event)
{
	imSession * s;
	gRoster * rwnd;
	
	s = EventSession(event);
	
	rwnd = _rosters[s->SessionId()];
	rwnd->NewItem(event->XML()->ChildValue("item-id"));

	return true;
}

bool oSessionManager::ThreadUICreate(oEvent * event)
{
	imSession * s;
	imMessageThread * th;
	
	s = EventSession(event);
	th = s->MessageQueue()->FindThread(event->XML()->ChildValue("thread-id"));
	if (th == NULL)
		return true;

	th->UI(new uiChat(wxGetApp().Oniria()));
	
	return true;
}

void oSessionManager::RegisterTabGroups()
{
	_app->TabManager()->RegisterGroup("roster", oTabs::ts_main_window);
	_app->TabManager()->RegisterGroup("chat", oTabs::ts_single_window, oTabs::tws_invisible);
}
