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
#include <QTcpSocket>
#include <QtDebug>
#include <onir/onir.h>
#include <onir/oOniria.h>
#include <onir/oConfig.h>
#include <onir/oEvent.h>
#include <onir/oEventQueue.h>
#include <oxml/xmlAttribute.h>
#include <oxml/xmlElement.h>
#include <oxml/xmlStanza.h>
#include <oxml/xmlStream.h>
#include <ocrypt/cptBase64.h>
#include <osasl/saslSASL.h>
#include <osasl/saslMechanism.h>
#include <oim/imRoster.h>
#include <oim/imRosterGroup.h>
#include <oim/imMessageQueue.h>
#include <oim/imMessageThread.h>
#include <oim/imMessage.h>
#include "jPeer.h"
#include "jRoster.h"
#include "jRosterItem.h"
#include "jRosterSubItem.h"
#include "jMessageQueue.h"
#include "jSession.h"

using onirXML::xmlStanza;
using onirXML::xmlElement;
using onirCrypt::cptBase64;
using onir::oEvent;
using namespace onirIM;

jSession::jSession(oOniria * o, imProtocol * proto)
	: imSession(proto)
{
	_xml = NULL;
	_state = unknown;
	_sasl = NULL;
	_force_no_sasl = false;
	_feat_sess = false;
	_feat_bind = false;
	_roster = NULL;
	_oniria = o;
	_socket = NULL;
}

jSession::~jSession()
{
}

bool jSession::load(xmlElement *cnode)
{
	QString jid, resource;

	if (!imSession::load(cnode))
		return false;

	jid = oniria()->config()->value(cnode, "jid", "");
	resource = oniria()->config()->value(cnode, "resource", "Oniria");
	_priority = oniria()->config()->value(cnode, "priority", 15);
	_jid.set(jid, resource);
	if (!_jid.valid())
		return false;

	_password = oniria()->config()->value(cnode, "password", "");
	_force_no_sasl = (oniria()->config()->node(cnode, "force-no-sasl") != NULL);


	return true;
}

bool jSession::connect(bool ac)
{
	//wxIPV4address addr;

	_roster = new jRoster(this);

	_socket = new QTcpSocket();
	QObject::connect(_socket, SIGNAL(connected()), SLOT(connected()));
	_socket->connectToHost(_jid.domain(), 5222);	// TODO: resolve host using dns SRV records
	_state = connecting;

	return true;
}

void jSession::connected()
{
	qDebug() << "jSession::connected():" << sessionId();
	_xml = new xmlStream(_socket, _socket);
	QObject::connect(_xml, SIGNAL(receivedStanza(xmlStanza *)), SLOT(receivedStanza(xmlStanza *)));
	_xml->prepare();
	_xml->outRoot()->name("stream:stream");
	_xml->outRoot()->addAttribute("to", _jid.domain());
	_xml->outRoot()->addAttribute("xmlns", "jabber:client");
	_xml->outRoot()->addAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
	_xml->outRoot()->addAttribute("version", "1.0");
	_xml->initiate();
}

void jSession::receivedStanza(xmlStanza * stanza)
{
	if (_state == authenticating) {
		doSASLAuth(stanza);
	} else if (stanza->element()->name() == "stream:features") {
		parseFeatures(stanza);
	} else if (stanza->element()->name() == "iq") {
		parseIQ(stanza);
	} else if (stanza->element()->name() == "presence") {
		parsePresence(stanza);
	} else if (stanza->element()->name() == "message") {
		parseMessage(stanza);
	}
	delete stanza;
}

bool jSession::poll()
{
	if (_socket != NULL && _xml == NULL) {	// we are establishing connection

		_socket->waitForConnected(0);

	} else if (_xml != NULL) {

		_xml->poll();

/*		while ((stanza = _xml->nextStanza())) {
			bool ret = true;
			//wxLogVerbose("jSession: Received stanza: %s", stanza->Format().c_str());

			return ret;
		}*/
	}
	return true;
}

imMessageQueue * jSession::createMessageQueue()
{
	return new jMessageQueue(this);
}

bool jSession::setStatus()
{
	QString st, type;

	type = "";
	switch (status().status()) {
		case imStatus::chat:
			st = "chat";
			break;
		case imStatus::avail:
			st = "avail";
			break;
		case imStatus::away:
			st = "away";
			break;
		case imStatus::xa:
			st = "xa";
			break;
		case imStatus::dnd:
			st = "dnd";
			break;
		case imStatus::inv:
			st = "";
			type = "unavailable";
			break;
		default:
			return false;
	}

	return presence(st, status().description(), type);
}

imRoster * jSession::roster()
{
	return _roster;
}

bool jSession::syncRoster(bool send)
{
	if (!send) {
		xmlStanza * p;
		
		p = iqQuery("jabber:iq:private", "get", "roster_delim_1");
		p->element()->child("query")->addChild("roster", "");
		p->element()->child("query")->child("roster")->addAttribute("xmlns", "roster:delimiter");
		_xml->addStanza(p);

		p = iqQuery("jabber:iq:roster", "get", "roster_1", "", _jid.jid());
		_xml->addStanza(p);
	}

	return true;
}

imMessageThread * jSession::getMessageThread(const QString& type, const jJid& jid, const QString& id)
{
	jPeer * peer;
	jPeer * lpeer;
	jRosterItem * ri;
	imMessageThread * thr;
	QString thid;

	if (id.isEmpty())
		thid = jid.jid();
	else
		thid = id;

	thr = messageQueue()->findThread(thid);
	if (thr == NULL) {

		thr = new imMessageThread(this);
		
		peer = new jPeer;
		peer->jid(jid);
		peer->name(jid.jid());
		ri = static_cast<jRosterItem *>(roster()->item(QString("jid:") + jid.bare(), true));
		if (ri == NULL)
			ri = static_cast<jRosterItem *>(roster()->item(QString("jid:") + jid.jid(), true));
		if (ri != NULL)
			peer->name(ri->name());
	
		thr->addPeer(peer);
		thr->id(thid);
				
		lpeer = new jPeer;
		lpeer->jid(_jid);
		lpeer->name(_jid.node());
		thr->localPeer(lpeer);
		messageQueue()->addThread(thr);

	}
	
	return thr;
}

bool jSession::sendMessage(imMessage * msg)
{
	for (QList<imPeer *>::iterator it = msg->thread()->peers()->begin(); it != msg->thread()->peers()->end(); it++) {
		xmlStanza * stanza;

		stanza = new xmlStanza;
		stanza->element()->name("message");
		stanza->element()->addAttribute("type", "chat"); // TODO: support for other message types
		stanza->element()->addAttribute("from", _jid.jid());
		stanza->element()->addAttribute("to", static_cast<jPeer *>(*it)->jid().jid());
		if (!msg->subject().isEmpty())
			stanza->element()->addChild("subject", msg->subject());
		stanza->element()->addChild("body", msg->body());
		stanza->element()->addChild("thread", msg->thread()->id());
		_xml->addStanza(stanza);
	}
	
	return true;
}

imStatus jSession::presenceToStatus(xmlStanza * stanza)
{
	imStatus st;
	imStatus::contactStatus e_st;

	if (stanza->element()->attributeValue("type") == "unavailable") {
		e_st = imStatus::na;
	} else {
		xmlElement * show;
		
		e_st = imStatus::avail;
		show = stanza->element()->child("show");
		if (show != NULL) {
			if (show->value() == "away")
				e_st = imStatus::away;
			else if (show->value() == "xa")
				e_st = imStatus::xa;
			else if (show->value() == "dnd")
				e_st = imStatus::dnd;
			else if (show->value() == "chat")
				e_st = imStatus::chat;
		}
	}
	
	st.set(e_st, stanza->element()->childValue("status"));
	
	return st;
}

bool jSession::presence(const QString& status, const QString& desc, const QString& type, const QString& to)
{
	xmlStanza * stanza;

	stanza = new xmlStanza;
	stanza->element()->name("presence");
	if (!type.isEmpty())
		stanza->element()->addAttribute("type", type);
	if (!to.isEmpty())
		stanza->element()->addAttribute("to", to);
	if (!status.isEmpty())
		stanza->element()->addChild("show", status);
	if (!desc.isEmpty())
		stanza->element()->addChild("status", desc);
	stanza->element()->addChild("priority", _priority);

	_xml->addStanza(stanza);

	return true;
}

xmlStanza * jSession::iq(const QString& type, const QString& id, const QString& to, const QString& from)
{
	xmlStanza * p;

	p = new xmlStanza;
	p->element()->name("iq");
	p->element()->addAttribute("type", type);
	p->element()->addAttribute("id", id);
	if (!from.isEmpty())
		p->element()->addAttribute("from", from);
	if (!to.isEmpty())
		p->element()->addAttribute("to", to);

	return p;
}

xmlElement * jSession::query(const QString& xmlns)
{
	xmlElement * p;
	p = new xmlElement;
	p->name("query");
	p->addAttribute("xmlns", xmlns);
	return p;
}

xmlStanza * jSession::iqQuery(const QString& xmlns, const QString& type, const QString& id, const QString& to, const QString& from)
{
	xmlStanza * p;

	p = iq(type, id, to, from);
	p->element()->addChild(query(xmlns));
	return p;
}

oEvent * jSession::event(const QString& id)
{
	oEvent * event;
	event = new oEvent(id);
	event->xml()->addChild("session-id", sessionId());
	return event;
}

bool jSession::SASLAuth(const QList<QString>& mechs)
{
	xmlStanza * stanza;

	if (_sasl != NULL)
		delete _sasl;

	_sasl = new saslSASL;
	if (_sasl->chooseMechanism(mechs) == NULL) {
		qWarning() << "jSession::SASLAuth() No supported SASL mechanisms found.";
		return false;
	}
	qDebug() << "jSession::SASLAuth():" << sessionId() << ": Using" << _sasl->mechanism()->name() << "SASL mechanism.";

	_sasl->mechanism()->addProperty("username", _jid.node());
	_sasl->mechanism()->addProperty("passwd", _password);
	_sasl->mechanism()->addProperty("host", _jid.domain());
	_sasl->mechanism()->addProperty("serv-type", "xmpp");
	
	stanza = new xmlStanza;
	stanza->element()->name("auth");
	stanza->element()->addAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-sasl");
	stanza->element()->addAttribute("mechanism", _sasl->mechanism()->name());
	_xml->addStanza(stanza);

	_state = authenticating;

	return true;
}

bool jSession::doSASLAuth(xmlStanza * stanza)
{
	if (stanza->element()->attributeValue("xmlns") == "urn:ietf:params:xml:ns:xmpp-sasl") {
		if (stanza->element()->name() == "challenge") {
			QByteArray challenge, response;

			cptBase64::decode(&challenge, stanza->element()->value());
			qDebug() << "jSession::doSASLAuth():" << sessionId() << ": SASL challenge:" << challenge;
			if (!_sasl->mechanism()->response(&challenge, &response))
				return false;
			qDebug() << "jSession::doSASLAuth():" << sessionId() << ": SASL response" << response;

			stanza = new xmlStanza;
			stanza->element()->name("response");
			stanza->element()->addAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-sasl");
			stanza->element()->value(cptBase64::encode(&response));
			_xml->addStanza(stanza);

			return true;
		} else if (stanza->element()->name() == "success") {

			qDebug() << "jSession::doSASLAuth():" << sessionId() << ": Authenticated.";

			// destroy current and create new stream
			_xml->disconnect(this);
			delete _xml;
			_xml = new xmlStream(_socket, _socket);
			QObject::connect(_xml, SIGNAL(receivedStanza(xmlStanza *)), SLOT(receivedStanza(xmlStanza *)));
			_xml->prepare();
			_xml->outRoot()->name("stream:stream");
			_xml->outRoot()->addAttribute("to", _jid.domain());
			_xml->outRoot()->addAttribute("xmlns", "jabber:client");
			_xml->outRoot()->addAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
			_xml->outRoot()->addAttribute("version", "1.0");
			_xml->initiate();
			_xml->poll();

			_state = authenticated;

			return true;

		} else if (stanza->element()->name() == "failure") {
			QMultiMap<QString, xmlElement *> children;
			QString auth_err = "unknown";
			
			stanza->element()->children(children);
			if (!children.empty())
				auth_err = children.begin().value()->name();
			//wxLogError("jSession: Authentication failed: %s", auth_err.c_str());

			// TODO: allow authentication retries
			_state = closed;

			return false;
		}
	}
	return true;
}

bool jSession::bindResource()
{
	xmlStanza * iqs;
	xmlElement * bind;

	if (!_feat_bind)
		return false;

	iqs = iq("set", "bind_1");
	bind = new xmlElement("bind");
	bind->addAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-bind");
	bind->addChild("resource", _jid.resource());
	iqs->element()->addChild(bind);
	_xml->addStanza(iqs);

	_state = binding;

	return true;
}

bool jSession::establishSession()
{
	xmlStanza * iqs;
	xmlElement * session;

	if (!_feat_sess)
		return false;

	iqs = iq("set", "sess_1", _jid.domain());
	session = new xmlElement("session");
	session->addAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-session");
	iqs->element()->addChild(session);
	_xml->addStanza(iqs);

	_state = establishing;

	return true;
}

bool jSession::parseFeatures(xmlStanza * stanza)
{
	if (_state == connecting) {
		xmlElement * e_mechs;
		QList<xmlElement *> l_mechs;
		QList<QString> mechs;

		while (!_force_no_sasl) {
			e_mechs = stanza->element()->child("mechanisms");
			if (e_mechs == NULL) {
				// no <mechanisms> tag, give up
				break;
			}
			if (e_mechs->attributeValue("xmlns") != "urn:ietf:params:xml:ns:xmpp-sasl") {
				// <mechanisms> ok, but from different namespace
				break;
			}
			e_mechs->children("mechanism", l_mechs);

			for (QList<xmlElement *>::iterator it = l_mechs.begin(); it != l_mechs.end(); it++) {
				mechs.push_back((*it)->value());
				qDebug() << "jSession::parseFeatures():" << sessionId() << ": SASL mechanism:" << (*it)->value();
			}


			// start authentication process
			if (!mechs.empty()) {
				return SASLAuth(mechs);
			}
			break;
		}

		// fallback to old-style auth
		// TODO: old-style auth

	} else if (_state == authenticated) {
		xmlElement * e;

		e = stanza->element()->child("bind");
		if (e != NULL && e->attributeValue("xmlns") == "urn:ietf:params:xml:ns:xmpp-bind") {
			_feat_bind = true;
			//wxLogVerbose("jSession: Resource binding supported.");
		}
		e = stanza->element()->child("session");
		if (e != NULL && e->attributeValue("xmlns") == "urn:ietf:params:xml:ns:xmpp-session") {
			_feat_sess = true;
			//wxLogVerbose("jSession: Sessions supported.");
		}

		
		// start resource binding
		if (_feat_bind)
			return bindResource();
		else
			return false;
	}

	return true;
}

bool jSession::parseIQ(xmlStanza * stanza)
{
	if (_state == binding) {
		return parseIQBind(stanza);
	} else if (_state == establishing) {
		return parseIQSession(stanza);
	} else if (_state == established) {
		xmlElement * el;

		el = stanza->element()->child("query");
		if (el != NULL) {
			QString xmlns = el->attributeValue("xmlns");

			if (xmlns == "jabber:iq:roster")
				return parseIQRoster(stanza);
			else if (xmlns == "jabber:iq:private")
				return parseIQPrivate(stanza);
			else if (xmlns == "jabber:iq:version")
				return parseIQVersion(stanza);
		}
	}
	return true;	
}

bool jSession::parseIQBind(xmlStanza * stanza)
{
	QString type, id;

	type = stanza->element()->attributeValue("type");
	id = stanza->element()->attributeValue("id");

	if (id == "bind_1") {
		if (type == "result") {
			if (stanza->element()->child("bind") != NULL) {
				QString jid;
				jid = stanza->element()->child("bind")->childValue("jid");
				_jid.set(jid);
				//wxLogMessage("jSession: Resource bound as %s.", jid.c_str());
				
				return establishSession();
			}
		} else if (type == "error") {
			// TODO: error handling. Possibly stream pausing.
		}
	}
	return false;
}

bool jSession::parseIQSession(xmlStanza * stanza)
{
	QString type, id;

	type = stanza->element()->attributeValue("type");
	id = stanza->element()->attributeValue("id");

	if (id == "sess_1") {
		if (type == "result") {

			//wxLogMessage("jSession: Session established. Sending initial presence.");
			_state = established;

			oniria()->eventQueue()->queue(event("oniria:im:session:connected"));

			return true;
		} else if (type == "error") {
			// TODO: error handling.
		}
	}
	return false;
}

bool jSession::parseIQPrivate(xmlStanza * stanza)
{
	if (stanza->element()->attributeValue("type") == "result") {
		if (stanza->element()->attributeValue("id") == "roster_delim_1") {	// reply to SyncRoster()
			if (stanza->element()->child("query")->child("roster") == NULL)
				return true;
			if (stanza->element()->child("query")->child("roster")->attributeValue("xmlns") != "roster:delimiter")
				return true;
			
			_roster->nestedGroups(true);
			_roster->nestedGroupsDelimiter(stanza->element()->child("query")->childValue("roster"));
			
			//wxLogVerbose("jSession: Nested groups supported, using \"%s\" as delimiter.", _roster->NestedGroupsDelimiter().c_str());
		}
	}
	return true;
}

bool jSession::parseIQVersion(xmlStanza * stanza)
{
	if (stanza->element()->attributeValue("type") == "get") {
		xmlStanza * reply;
		QString id, to;
		
		id = stanza->element()->attributeValue("id");
		to = stanza->element()->attributeValue("from");
		reply = iqQuery("jabber:iq:version", "result", id, to, _jid.jid());
		reply->element()->child("query")->addChild("name", oniria()->programName());
		reply->element()->child("query")->addChild("version", oniria()->programVersion());
		reply->element()->child("query")->addChild("os", oniria()->OSDescription());
		_xml->addStanza(reply);
	} else if (stanza->element()->attributeValue("type") == "result") {
		jRosterItem * ri;
		QString from;
		xmlElement * q;
		
		from = stanza->element()->attributeValue("from");
		q = stanza->element()->child("query");
		ri = static_cast<jRosterItem *>(_roster->item(from, true));
		if (ri != NULL) {
			ri->softwareName(q->childValue("name"));
			ri->softwareVersion(q->childValue("version"));
			ri->OS(q->childValue("os"));
		}
	}
	return true;
}

bool jSession::parseIQRoster(xmlStanza * stanza)
{
	if (stanza->element()->attributeValue("type") == "result") {
		if (stanza->element()->attributeValue("id") == "roster_1") {	// reply to SyncRoster()
			xmlElement * q;
			QList<xmlElement *> items;
			QMap<QString, imRosterGroup *> grps;

			q = stanza->element()->child("query");
			if (q == NULL)
				return false;

			q->children("item", items);

			for (QList<xmlElement *>::iterator it = items.begin(); it != items.end(); it++) {
				jRosterItem * ri;
				QList<xmlElement *> e_grps;
				
				qDebug() << "jSession::parseIQRoster():" << sessionId() << ": Roster item: jid:" << (*it)->attributeValue("jid")
					<< ", name:" << (*it)->attributeValue("name") << ", subscription:" << (*it)->attributeValue("subscription");
						
				ri = new jRosterItem(this);
				ri->name((*it)->attributeValue("name"));
				ri->id("jid:" + (*it)->attributeValue("jid"));
				ri->jid(jJid((*it)->attributeValue("jid")));
				if (ri->name().isEmpty())
					ri->name(ri->jid().jid());
				(*it)->children("group", e_grps);
				if (e_grps.isEmpty()) {
					_roster->addItem(ri, NULL);
				} else {
					for (QList<xmlElement *>::iterator it = e_grps.begin(); it != e_grps.end(); it++) {
						imRosterGroup * g = NULL;
						if (grps.find("group:" + (*it)->value()) == grps.end()) {
					
							if (_roster->nestedGroups() && !_roster->nestedGroupsDelimiter().isEmpty()) {
								QString r_id = (*it)->value(); // rest id
								QString delim = _roster->nestedGroupsDelimiter();
								QString parent_id = ""; // parent group id
								imRosterGroup * parent = NULL; // parent group id
								int d_pos;
								while ((d_pos = r_id.indexOf(delim)) != -1) {
									QString g_id;
									g_id = r_id.mid(0, d_pos);
									r_id = r_id.mid(d_pos + delim.size());
									
									if (!parent_id.isEmpty())
										parent_id = parent_id + delim;
									parent_id += g_id;
									if (grps.find("group:" + parent_id) == grps.end()) {
										g = new imRosterGroup(this);
										g->id("group:" + parent_id);
										g->name(g_id);
										_roster->addGroup(g, parent);
										grps[g->id()] = g;
									} else {
										g = grps["group:" + parent_id];
									}
									parent = g;
								}
								if (!r_id.isEmpty()) {
									if (grps.find("group:" + (*it)->value()) == grps.end()) {
										g = new imRosterGroup(this);
										g->id("group:" + (*it)->value());
										g->name(r_id);
										_roster->addGroup(g, parent);
										grps[g->id()] = g;
									} else {
										g = grps["group:" + (*it)->value()];
									}
								}
							} else {
								g = new imRosterGroup(this);
								g->id("group:" + (*it)->value());
								g->name((*it)->value());
								
								_roster->addGroup(g);
								
								grps[g->id()] = g;
							}
						}
						
						g = grps["group:" + (*it)->value()];
						//if (g != NULL)
						//	wxLogVerbose("jSession: Adding %s to group %s", ri->Id().c_str(), g->Id().c_str());
						_roster->addItem(ri, g);
					}
				}
			}
			oniria()->eventQueue()->queue(event("oniria:im:session:roster:updated"));
		}
	}
	return true;
}

bool jSession::parsePresence(xmlStanza * stanza)
{
	
	if (stanza->element()->attributeValue("type") == "" ||
	    stanza->element()->attributeValue("type") == "unavailable") {
		oEvent * ev;
		imRosterItem * item = NULL;
		jRosterItem * bare = NULL;
		jJid jid;
		imStatus status;
		QVector<QString> order;

		status = presenceToStatus(stanza);
		jid.set(stanza->element()->attributeValue("from"));
		
		item = _roster->item("jid:" + jid.jid());	// check if it's main item.
		if (item == NULL)				// find bare jid only if it's not main item.
			bare = static_cast<jRosterItem *>(_roster->item("jid:" + jid.bare()));

		if (_roster->allItems()->find("jid:" + jid.jid()) == _roster->allItems()->end()) {
			
			jRosterSubItem * sitem;
			
			if (stanza->element()->attributeValue("type") == "unavailable")
				return true;
		
			if (jid.resource().isEmpty())
				return true;

			if (bare == NULL)
				return true;
			
			sitem = new jRosterSubItem(this, bare);
			sitem->id("jid:" + jid.jid());
			sitem->name(jid.resource());
			sitem->jid(jid);
			try {
				sitem->priority(stanza->element()->childValue("priority").toUInt());
			} catch (...) {
			}
			item = sitem;
			_roster->addSubItem(item, bare);
		
			ev = event("oniria:im:session:roster:item:new");
			ev->xml()->addChild("item-id", "jid:" + jid.jid());
			oniria()->eventQueue()->queue(ev);
		} else {
			item = _roster->allItems()->find("jid:" + jid.jid()).value();
		}
		
		if (item->status() != status) {
			xmlStanza * verst;

			item->status(status);
			if (!jid.resource().isEmpty() && bare != NULL && status.status() == imStatus::na) {
				_roster->removeSubItem(item->id());
				delete item;
				item = NULL;
			}
			if (bare != NULL) {
				bare->fixedOrder(order);
				if (!order.empty()) {
					if (item != NULL) {
						if (order.front() == item->id())
							bare->status(status);
					} else {
						bare->status(bare->subItem(order.front())->status());
					}
				} else {
					bare->status(status);	// should be only, when receiving type='unavailable' from last resource
				}
			}
	
			ev = event("oniria:im:session:roster:item:presence");
			ev->xml()->addChild("item-id", "jid:" + jid.jid());
			oniria()->eventQueue()->queue(ev);
			if (!jid.resource().isEmpty() && bare != NULL) {
				ev = event("oniria:im:session:roster:item:presence");
				ev->xml()->addChild("item-id", "jid:" + jid.bare());
				oniria()->eventQueue()->queue(ev);
			}
			
			verst = iqQuery("jabber:iq:version", "get", "version_1", jid.jid(), _jid.jid());
			_xml->addStanza(verst);
		}

	}
	return true;
}

bool jSession::parseMessage(xmlStanza * stanza)
{
	
	if (stanza->element()->child("body") != NULL) {
		jJid jid;
		jPeer * peer;
		imMessage * msg;
		QString thid;
		imMessageThread * thr;
		jRosterItem * ri;
	
		thid = stanza->element()->attributeValue("from");
		jid.set(thid);
		if (!stanza->element()->childValue("thread").isEmpty())
			thid = thid + ":" + stanza->element()->childValue("thread");
	
		peer = new jPeer;
		peer->jid(jid);
		peer->name(jid.jid());
		ri = static_cast<jRosterItem *>(roster()->item(QString("jid:") + jid.bare(), true));
		if (ri == NULL)
			ri = static_cast<jRosterItem *>(roster()->item(QString("jid:") + jid.jid(), true));
		if (ri != NULL) {
			peer->name(ri->name());
		}

		thr = getMessageThread("msg", jid, thid);
	
		msg = new imMessage;
		msg->subject(stanza->element()->childValue("subject"));
		msg->body(stanza->element()->childValue("body"));
		msg->localPeer(thr->localPeer());
		msg->addPeer(peer);

		thr->addInMessage(msg);
	}

	return true;
}

