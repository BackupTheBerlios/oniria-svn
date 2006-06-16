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
#include <QtDebug>
#include <oim/imProtocol.h>
#include <oim/imSession.h>
#include <oim/imMessageQueue.h>
#include <oim/imMessageThread.h>
#include <oim/imMessageThreadUI.h>
#include <oim/imMessage.h>
#include <onir/oConfig.h>
#include <onir/oEventForwarder.h>
#include <oxml/xmlElement.h>
//#include <onir/oTabs.h>
#include "oApplication.h"
#include "oEventManager.h"
//#include "gRoster.h"
//#include "oStatusManager.h"
//#include "uiChat.h"
#include "oSessionManager.h"

using namespace onirIM;
using onir::oEventForwarder;

namespace onirXML{
	class xmlElement;
};

using onirXML::xmlElement;

oSessionManager::oSessionManager(oApplication * app)
{
	_app = app;
	_status.set(imStatus::avail);
}

oSessionManager::~oSessionManager()
{
}

bool oSessionManager::registerProtocol(imProtocol * proto)
{
	if (_protocols.find(proto->protocolId()) != _protocols.end())
		return false;
	_protocols[proto->protocolId()] = proto;
	qDebug() << "oSessionManager::registerProtocol(): Registered protocol" << proto->protocolId();
	return true;
}

imProtocol * oSessionManager::findProtocol(const QString& id)
{
	if (_protocols.find(id) == _protocols.end())
		return NULL;
	return _protocols[id];
}

int oSessionManager::loadSessions()
{
	QVector<xmlElement *> snodes;
	int sessions;

	snodes = _app->config()->children("sessions");
	if (snodes.empty())
		return 0;
	sessions = 0;
	for (QVector<xmlElement *>::iterator i = snodes.begin(); i != snodes.end(); i++) {
		if (_app->config()->nodeName(*i) == "session") {
			imProtocol * proto;

			proto = findProtocol(_app->config()->value(*i, "protocol", ""));
			if (proto == NULL) {
				qDebug() << "oSessionManager::loadSessions(): session with unknown protocol:" << _app->config()->value(*i, "protocol", "");
			} else {
				imSession * s;
                
				s = proto->createSession();
				s->prepare();
				if (s != NULL) {
					s->load(*i);
					_sessions[s->sessionId()] = s;
					//createRosterWindow(s);//XXX
					qDebug() << "oSessionManager::loadSessions() Loaded session" << s->name() << ", protocol:" << proto->protocolName();
				}
			}
			
		}
	}
	return _sessions.size();
}

int oSessionManager::connectSessions(bool all)
{
	_active_sessions.clear();
	for (QMap<QString, imSession *>::iterator it = _sessions.begin(); it != _sessions.end(); it++) {
		if (all || it.value()->autoConnect()) {
			if (it.value()->connect(true)) {
				_active_sessions[it.value()->sessionId()] = it.value();
				it.value()->status(_status, false);
			}
		}
	}
	return _active_sessions.size();
}

void oSessionManager::poll()
{
	QMap<QString, imSession *>::iterator it = _active_sessions.begin();
	while (it != _active_sessions.end()) {
		if (!it.value()->poll()) {
			QString k = it.key();
			it++;
			_active_sessions.remove(k);
		} else {
			processMessageQueue(it.value());
			it++;
		}
	}
}

void oSessionManager::processMessageQueue(imSession * s)
{
	for (QMap<QString, imMessageThread *>::iterator it = s->messageQueue()->threads()->begin(); it != s->messageQueue()->threads()->end(); it++) {
		imMessage * msg;
		if (it.value()->ui() == NULL) {
			oEvent * event;
			event = new oEvent("oniria:im:session:thread:ui:create");
			event->xml()->addChild("session-id", s->sessionId());
			event->xml()->addChild("thread-id", it.value()->id());
			_app->eventManager()->process(event);
			if (it.value()->ui() != NULL)
				it.value()->ui()->create();
		}
		while ((msg = it.value()->nextInMessage()) != NULL) {
			if (it.value()->ui() != NULL) {
				it.value()->ui()->displayMessage(msg);
				delete msg;
			}
		}
		while ((msg = it.value()->nextOutMessage()) != NULL) {
			s->sendMessage(msg);
			delete msg;
		}
	}
}

bool oSessionManager::startThread(const QString& session_id, const QString& roster_id)
{
	imSession * s;
	imMessageThread * th;
	oEvent * event;

	if (_active_sessions.find(session_id) == _active_sessions.end())
		return false;
		//throw uException(_("Unknown session."));

	s = _active_sessions[session_id];

	th = s->messageQueue()->getThread("msg", roster_id, "");

	event = new oEvent("oniria:im:session:thread:ui:create");
	event->xml()->addChild("session-id", s->sessionId());
	event->xml()->addChild("thread-id", th->id());
	_app->eventManager()->process(event);
	if (th->ui() != NULL)
		th->ui()->create();
	
	return true;
}

void oSessionManager::status(const imStatus& st, bool set)
{
	_status = st;
	for (QMap<QString, imSession *>::iterator it = _active_sessions.begin(); it != _active_sessions.end(); it++) {
		it.value()->status(_status, set);
	}
}

// XXX
//wxWindow * oSessionManager::CreateRosterWindow(imSession * s)
//{	
//    _rosters[s->SessionId()] = new gRoster(_app, _app->TabManager()->ParentWindow());
//	_app->TabManager()->RegisterPage(s->SessionId(), s->Name(), _rosters[s->SessionId()], "roster");	
//	return _rosters[s->SessionId()];
//}

imSession * oSessionManager::eventSession(oEvent * event)
{
	imSession * s;

	if (_sessions.find(event->xml()->childValue("session-id")) == _sessions.end())
		return NULL;
	//	throw uException(_("Unknown session."));

	s = _sessions[event->xml()->childValue("session-id")];
	
	return s;
}

void oSessionManager::registerEventHandlers()
{
	_app->eventManager()->registerHandler("oniria:im:session:connected", new oEventForwarder(this));
	_app->eventManager()->registerHandler("oniria:im:session:roster:updated", new oEventForwarder(this));
	_app->eventManager()->registerHandler("oniria:im:session:roster:item:presence", new oEventForwarder(this));
	_app->eventManager()->registerHandler("oniria:im:session:roster:item:new", new oEventForwarder(this));
	_app->eventManager()->registerHandler("oniria:im:session:thread:ui:create", new oEventForwarder(this));
}

bool oSessionManager::processEvent(oEvent * event)
{
	ROUTE_EVENT(event, "oniria:im:session:connected", sessionConnected);
	ROUTE_EVENT(event, "oniria:im:session:roster:updated", rosterUpdated);
	ROUTE_EVENT(event, "oniria:im:session:roster:item:presence", rosterPresence);
	ROUTE_EVENT(event, "oniria:im:session:roster:item:new", rosterNewItem);
	ROUTE_EVENT(event, "oniria:im:session:thread:ui:create", threadUICreate);
	return true;
}

bool oSessionManager::sessionConnected(oEvent * event)
{
	imSession * s;
	
	s = eventSession(event);

	s->syncRoster(false);
	s->setStatus();

	return true;
}

bool oSessionManager::rosterUpdated(oEvent * event)
{
	imSession * s;
	//gRoster * rwnd;
	
	s = eventSession(event);
	
	//rwnd = _rosters[s->SessionId()];
	//rwnd->UpdateTree(s->Roster());

	return true;
}

bool oSessionManager::rosterPresence(oEvent * event)
{
	imSession * s;
	//gRoster * rwnd;
	
	s = eventSession(event);
	
	//rwnd = _rosters[s->SessionId()];
	//rwnd->UpdateItem(event->XML()->ChildValue("item-id"));

	return true;
}

bool oSessionManager::rosterNewItem(oEvent * event)
{
	imSession * s;
	//gRoster * rwnd;	// XXX
	
	s = eventSession(event);
	
	//rwnd = _rosters[s->sessionId()];	//XXX
	//rwnd->newItem(event->xml()->childValue("item-id"));	/XXX

	return true;
}

bool oSessionManager::threadUICreate(oEvent * event)
{
	imSession * s;
	imMessageThread * th;
	
	s = eventSession(event);
	th = s->messageQueue()->findThread(event->xml()->childValue("thread-id"));
	if (th == NULL)
		return true;

	//th->ui(new uiChat(wxGetApp().Oniria()));	// XXX
	
	return true;
}

void oSessionManager::registerTabGroups()
{
	// XXX
	//_app->TabManager()->RegisterGroup("roster", oTabs::ts_main_window);
	//_app->TabManager()->RegisterGroup("chat", oTabs::ts_single_window, oTabs::tws_invisible);
}
