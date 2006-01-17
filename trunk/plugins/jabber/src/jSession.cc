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
#include <set>
#include <wx/socket.h>
#include <onir/onir.h>
#include <onir/oOniria.h>
#include <onir/oConfig.h>
#include <onir/oEvent.h>
#include <onir/oEventQueue.h>
#include <onir/io/ioSocketStream.h>
#include <onir/xml/xmlAttribute.h>
#include <onir/xml/xmlElement.h>
#include <onir/xml/xmlStanza.h>
#include <onir/xml/xmlStream.h>
#include <onir/utils/uBuffer.h>
#include <onir/utils/uBase64.h>
#include <onir/utils/dconv.h>
#include <onir/sasl/saslSASL.h>
#include <onir/sasl/saslMechanism.h>
#include <onir/im/imRoster.h>
#include <onir/im/imRosterGroup.h>
#include <onir/im/imMessageQueue.h>
#include <onir/im/imMessageThread.h>
#include <onir/im/imMessage.h>
#include "jPeer.h"
#include "jRoster.h"
#include "jRosterItem.h"
#include "jRosterSubItem.h"
#include "jMessageQueue.h"
#include "jSession.h"

using onirXML::xmlStanza;
using onirXML::xmlElement;
using onirUtils::uBase64;
using onirUtils::uBuffer;
using onirUtils::ToUInt;
using onir::oEvent;
using namespace onirIM;

DEFINE_OOBJECT(jSession, imSession);

jSession::jSession(oOniria * o, imProtocol * proto)
	: imSession(o, proto)
{
	INIT_OOBJECT;

	_xml = NULL;
	_socket = NULL;
	_iostream = NULL;
	_state = unknown;
	_sasl = NULL;
	_force_no_sasl = false;
	_feat_sess = false;
	_feat_bind = false;
	_roster = NULL;
}

jSession::~jSession()
{
}

bool jSession::Load(xmlElement *cnode)
{
	string jid, resource;

	if (!imSession::Load(cnode))
		return false;

	jid = Oniria()->Config()->Value(cnode, "jid", "");
	resource = Oniria()->Config()->Value(cnode, "resource", "Oniria");
	_priority = Oniria()->Config()->Value(cnode, "priority", 15);
	_jid.Set(jid, resource);
	if (!_jid.Valid())
		return false;

	_password = Oniria()->Config()->Value(cnode, "password", "");
	_force_no_sasl = (Oniria()->Config()->NodeAt(cnode, "force-no-sasl") != NULL);


	return true;
}

bool jSession::Connect(bool ac)
{
	wxIPV4address addr;

	_roster = new jRoster(this);

	_socket = new wxSocketClient;
	addr.Hostname(_jid.Domain());
	addr.Service(5222);
	_socket->SetNotify(0);
	_socket->Notify(false);
	_socket->Connect(addr, false);
	_state = connecting;

	return true;
}

bool jSession::Poll()
{
	if (_socket != NULL && _xml == NULL) {	// we are establishing connection
	
	        _socket->WaitOnConnect(0, 0);
		if (_socket->IsConnected()) {

			// create and setup I/O stream
			_iostream = new ioSocketStream;
			_iostream->Socket(_socket);
			_iostream->NonBlocking();
			
			// create and setup XML stream
			_xml = new xmlStream(_iostream, _iostream);
			_xml->Prepare();
			_xml->OutRoot()->Name("stream:stream");
			_xml->OutRoot()->AddAttribute("to", _jid.Domain());
			_xml->OutRoot()->AddAttribute("xmlns", "jabber:client");
			_xml->OutRoot()->AddAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
			_xml->OutRoot()->AddAttribute("version", "1.0");
			_xml->Initiate();

		}
	} else if (_xml != NULL) {
		xmlStanza * stanza;
	
		_xml->Poll();

		while ((stanza = _xml->NextStanza())) {
			bool ret = true;
			wxLogVerbose("jSession: Received stanza: %s", stanza->Format().c_str());

			if (_state == authenticating) {
				ret = DoSASLAuth(stanza);
			} else if (stanza->Element()->Name() == "stream:features") {
				ret = ParseFeatures(stanza);
			} else if (stanza->Element()->Name() == "iq") {
				ret = ParseIQ(stanza);
			} else if (stanza->Element()->Name() == "presence") {
				ret = ParsePresence(stanza);
			} else if (stanza->Element()->Name() == "message") {
				ret = ParseMessage(stanza);
			}
			delete stanza;
			return ret;
		}
	}
	return true;
}

imMessageQueue * jSession::CreateMessageQueue()
{
	return new jMessageQueue(this);
}

bool jSession::SetStatus()
{
	string status, type;

	type = "";
	switch (Status().Status()) {
		case imStatus::chat:
			status = "chat";
			break;
		case imStatus::avail:
			status = "avail";
			break;
		case imStatus::away:
			status = "away";
			break;
		case imStatus::xa:
			status = "xa";
			break;
		case imStatus::dnd:
			status = "dnd";
			break;
		case imStatus::inv:
			status = "";
			type = "unavailable";
			break;
		default:
			return false;
	}

	return Presence(status, Status().Description(), type);
}

imRoster * jSession::Roster()
{
	return _roster;
}

bool jSession::SyncRoster(bool send)
{
	if (!send) {
		xmlStanza * p;
		
		p = IQQuery("jabber:iq:private", "get", "roster_delim_1");
		p->Element()->Child("query")->AddChild("roster", "");
		p->Element()->Child("query")->Child("roster")->AddAttribute("xmlns", "roster:delimiter");
		_xml->AddStanza(p);

		p = IQQuery("jabber:iq:roster", "get", "roster_1", "", _jid.Jid());
		_xml->AddStanza(p);
	}

	return true;
}

imMessageThread * jSession::GetMessageThread(const string& type, const jJid& jid, const string& id)
{
	jPeer * peer;
	jPeer * lpeer;
	jRosterItem * ri;
	imMessageThread * thr;
	string thid;

	if (id.empty())
		thid = jid.Jid();
	else
		thid = id;

	thr = MessageQueue()->FindThread(thid);
	if (thr == NULL) {

		thr = new imMessageThread(this);
		
		peer = new jPeer;
		peer->Jid(jid);
		peer->Name(jid.Jid());
		ri = static_cast<jRosterItem *>(Roster()->Item(string("jid:") + jid.Bare(), true));
		if (ri == NULL)
			ri = static_cast<jRosterItem *>(Roster()->Item(string("jid:") + jid.Jid(), true));
		if (ri != NULL)
			peer->Name(ri->Name());
	
		thr->AddPeer(peer);
		thr->Id(thid);
				
		lpeer = new jPeer;
		lpeer->Jid(_jid);
		lpeer->Name(_jid.Node());
		thr->LocalPeer(lpeer);
		MessageQueue()->AddThread(thr);

	}
	
	return thr;
}

bool jSession::SendMessage(imMessage * msg)
{
	for (list<imPeer *>::iterator it = msg->Thread()->Peers()->begin(); it != msg->Thread()->Peers()->end(); it++) {
		xmlStanza * stanza;

		stanza = new xmlStanza;
		stanza->Element()->Name("message");
		stanza->Element()->AddAttribute("type", "chat"); // TODO: support for other message types
		stanza->Element()->AddAttribute("from", _jid.Jid());
		stanza->Element()->AddAttribute("to", static_cast<jPeer *>(*it)->Jid().Jid());
		if (!msg->Subject().empty())
			stanza->Element()->AddChild("subject", msg->Subject());
		stanza->Element()->AddChild("body", msg->Body());
		stanza->Element()->AddChild("thread", msg->Thread()->Id());
		_xml->AddStanza(stanza);
	}
	
	return true;
}

imStatus jSession::PresenceToStatus(xmlStanza * stanza)
{
	imStatus st;
	imStatus::status status;

	if (stanza->Element()->AttributeValue("type") == "unavailable") {
		status = imStatus::na;
	} else {
		xmlElement * show;
		
		status = imStatus::avail;
		show = stanza->Element()->Child("show");
		if (show != NULL) {
			if (show->Value() == "away")
				status = imStatus::away;
			else if (show->Value() == "xa")
				status = imStatus::xa;
			else if (show->Value() == "dnd")
				status = imStatus::dnd;
			else if (show->Value() == "chat")
				status = imStatus::chat;
		}
	}
	
	st.Set(status, stanza->Element()->ChildValue("status"));
	
	return st;
}

bool jSession::Presence(const string& status, const string& desc, const string& type, const string& to)
{
	xmlStanza * stanza;

	stanza = new xmlStanza;
	stanza->Element()->Name("presence");
	if (!type.empty())
		stanza->Element()->AddAttribute("type", type);
	if (!to.empty())
		stanza->Element()->AddAttribute("to", to);
	if (!status.empty())
		stanza->Element()->AddChild("show", status);
	if (!desc.empty())
		stanza->Element()->AddChild("status", desc);
	stanza->Element()->AddChild("priority", _priority);

	_xml->AddStanza(stanza);

	return true;
}

xmlStanza * jSession::IQ(const string& type, const string& id, const string& to, const string& from)
{
	xmlStanza * p;

	p = new xmlStanza;
	p->Element()->Name("iq");
	p->Element()->AddAttribute("type", type);
	p->Element()->AddAttribute("id", id);
	if (!from.empty())
		p->Element()->AddAttribute("from", from);
	if (!to.empty())
		p->Element()->AddAttribute("to", to);

	return p;
}

xmlElement * jSession::Query(const string& xmlns)
{
	xmlElement * p;
	p = new xmlElement;
	p->Name("query");
	p->AddAttribute("xmlns", xmlns);
	return p;
}

xmlStanza * jSession::IQQuery(const string& xmlns, const string& type, const string& id, const string& to, const string& from)
{
	xmlStanza * p;

	p = IQ(type, id, to, from);
	p->Element()->AddChild(Query(xmlns));
	return p;
}

oEvent * jSession::Event(const string& id)
{
	oEvent * event;
	event = new oEvent(id);
	event->XML()->AddChild("session-id", SessionId());
	return event;
}

bool jSession::SASLAuth(const list<string>& mechs)
{
	xmlStanza * stanza;

	if (_sasl != NULL)
		delete _sasl;

	_sasl = new saslSASL;
	if (_sasl->ChooseMechanism(mechs) == NULL) {
		wxLogError("jSession: No supported SASL mechanisms found.");
		return false;
	}
	wxLogVerbose("jSession: Using %s SASL mechanism.", _sasl->Mechanism()->Name().c_str());

	_sasl->Mechanism()->AddProperty("username", _jid.Node());
	_sasl->Mechanism()->AddProperty("passwd", _password);
	_sasl->Mechanism()->AddProperty("host", _jid.Domain());
	_sasl->Mechanism()->AddProperty("serv-type", "xmpp");
	
	stanza = new xmlStanza;
	stanza->Element()->Name("auth");
	stanza->Element()->AddAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-sasl");
	stanza->Element()->AddAttribute("mechanism", _sasl->Mechanism()->Name());
	_xml->AddStanza(stanza);

	_state = authenticating;

	return true;
}

bool jSession::DoSASLAuth(xmlStanza * stanza)
{
	if (stanza->Element()->AttributeValue("xmlns") == "urn:ietf:params:xml:ns:xmpp-sasl") {
		if (stanza->Element()->Name() == "challenge") {
			uBuffer challenge, response;

			uBase64::Decode(&challenge, stanza->Element()->Value());
			wxLogVerbose("jSession: SASL challenge: %s", challenge.str().c_str());
			if (!_sasl->Mechanism()->Response(&challenge, &response))
				return false;
			wxLogVerbose("jSession: SASL response: %s", response.str().c_str());

			stanza = new xmlStanza;
			stanza->Element()->Name("response");
			stanza->Element()->AddAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-sasl");
			stanza->Element()->Value(uBase64::Encode(&response));
			_xml->AddStanza(stanza);

			return true;
		} else if (stanza->Element()->Name() == "success") {

			wxLogMessage("jSession: Authenticated.");

			// destroy current and create new stream
			delete _xml;
			_xml = new xmlStream(_iostream, _iostream);
			_xml->Prepare();
			_xml->OutRoot()->Name("stream:stream");
			_xml->OutRoot()->AddAttribute("to", _jid.Domain());
			_xml->OutRoot()->AddAttribute("xmlns", "jabber:client");
			_xml->OutRoot()->AddAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
			_xml->OutRoot()->AddAttribute("version", "1.0");
			_xml->Initiate();

			_state = authenticated;

			return true;

		} else if (stanza->Element()->Name() == "failure") {
			multimap<string, xmlElement *> children;
			string auth_err = "unknown";
			
			stanza->Element()->Children(children);
			if (!children.empty())
				auth_err = children.begin()->second->Name();
			wxLogError("jSession: Authentication failed: %s", auth_err.c_str());

			// TODO: allow authentication retries
			_state = closed;

			return false;
		}
	}
	return true;
}

bool jSession::BindResource()
{
	xmlStanza * iq;
	xmlElement * bind;

	if (!_feat_bind)
		return false;

	iq = IQ("set", "bind_1");
	bind = new xmlElement("bind");
	bind->AddAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-bind");
	bind->AddChild("resource", _jid.Resource());
	iq->Element()->AddChild(bind);
	_xml->AddStanza(iq);

	_state = binding;

	return true;
}

bool jSession::EstablishSession()
{
	xmlStanza * iq;
	xmlElement * session;

	if (!_feat_sess)
		return false;

	iq = IQ("set", "sess_1", _jid.Domain());
	session = new xmlElement("session");
	session->AddAttribute("xmlns", "urn:ietf:params:xml:ns:xmpp-session");
	iq->Element()->AddChild(session);
	_xml->AddStanza(iq);

	_state = establishing;

	return true;
}

bool jSession::ParseFeatures(xmlStanza * stanza)
{

	if (_state == connecting) {
		xmlElement * e_mechs;
		list<xmlElement *> l_mechs;
		list<string> mechs;

		while (!_force_no_sasl) {
			e_mechs = stanza->Element()->Child("mechanisms");
			if (e_mechs == NULL) {
				// no <mechanisms> tag, give up
				break;
			}
			if (e_mechs->AttributeValue("xmlns") != "urn:ietf:params:xml:ns:xmpp-sasl") {
				// <mechanisms> ok, but from different namespace
				break;
			}
			e_mechs->Children("mechanism", l_mechs);

			for (list<xmlElement *>::iterator it = l_mechs.begin(); it != l_mechs.end(); it++)
				mechs.push_back((*it)->Value());

			for (list<string>::iterator it = mechs.begin(); it != mechs.end(); it++)
				wxLogVerbose("jSession: SASL mechanism: %s", it->c_str());

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

		e = stanza->Element()->Child("bind");
		if (e != NULL && e->AttributeValue("xmlns") == "urn:ietf:params:xml:ns:xmpp-bind") {
			_feat_bind = true;
			wxLogVerbose("jSession: Resource binding supported.");
		}
		e = stanza->Element()->Child("session");
		if (e != NULL && e->AttributeValue("xmlns") == "urn:ietf:params:xml:ns:xmpp-session") {
			_feat_sess = true;
			wxLogVerbose("jSession: Sessions supported.");
		}

		
		// start resource binding
		if (_feat_bind)
			return BindResource();
		else
			return false;
	}

	return true;
}

bool jSession::ParseIQ(xmlStanza * stanza)
{
	if (_state == binding) {
		return ParseIQBind(stanza);
	} else if (_state == establishing) {
		return ParseIQSession(stanza);
	} else if (_state == established) {
		xmlElement * el;

		el = stanza->Element()->Child("query");
		if (el != NULL) {
			string xmlns = el->AttributeValue("xmlns");

			if (xmlns == "jabber:iq:roster")
				return ParseIQRoster(stanza);
			else if (xmlns == "jabber:iq:private")
				return ParseIQPrivate(stanza);
			else if (xmlns == "jabber:iq:version")
				return ParseIQVersion(stanza);
		}
	}
	return true;	
}

bool jSession::ParseIQBind(xmlStanza * stanza)
{
	string type, id;

	type = stanza->Element()->AttributeValue("type");
	id = stanza->Element()->AttributeValue("id");

	if (id == "bind_1") {
		if (type == "result") {
			if (stanza->Element()->Child("bind") != NULL) {
				string jid;
				jid = stanza->Element()->Child("bind")->ChildValue("jid");
				_jid.Set(jid);
				wxLogMessage("jSession: Resource bound as %s.", jid.c_str());
				
				return EstablishSession();
			}
		} else if (type == "error") {
			// TODO: error handling. Possibly stream pausing.
		}
	}
	return false;
}

bool jSession::ParseIQSession(xmlStanza * stanza)
{
	string type, id;

	type = stanza->Element()->AttributeValue("type");
	id = stanza->Element()->AttributeValue("id");

	if (id == "sess_1") {
		if (type == "result") {

			wxLogMessage("jSession: Session established. Sending initial presence.");
			_state = established;

			Oniria()->EventQueue()->Queue(Event("oniria:im:session:connected"));

			return true;
		} else if (type == "error") {
			// TODO: error handling.
		}
	}
	return false;
}

bool jSession::ParseIQPrivate(xmlStanza * stanza)
{
	if (stanza->Element()->AttributeValue("type") == "result") {
		if (stanza->Element()->AttributeValue("id") == "roster_delim_1") {	// reply to SyncRoster()
			if (stanza->Element()->Child("query")->Child("roster") == NULL)
				return true;
			if (stanza->Element()->Child("query")->Child("roster")->AttributeValue("xmlns") != "roster:delimiter")
				return true;
			
			_roster->NestedGroups(true);
			_roster->NestedGroupsDelimiter(stanza->Element()->Child("query")->ChildValue("roster"));
			
			wxLogVerbose("jSession: Nested groups supported, using \"%s\" as delimiter.", _roster->NestedGroupsDelimiter().c_str());
		}
	}
	return true;
}

bool jSession::ParseIQVersion(xmlStanza * stanza)
{
	if (stanza->Element()->AttributeValue("type") == "get") {
		xmlStanza * reply;
		string id, to;
		
		id = stanza->Element()->AttributeValue("id");
		to = stanza->Element()->AttributeValue("from");
		reply = IQQuery("jabber:iq:version", "result", id, to, _jid.Jid());
		reply->Element()->Child("query")->AddChild("name", Oniria()->ProgramName());
		reply->Element()->Child("query")->AddChild("version", Oniria()->ProgramVersion());
		reply->Element()->Child("query")->AddChild("os", Oniria()->OSDescription());
		_xml->AddStanza(reply);
	} else if (stanza->Element()->AttributeValue("type") == "result") {
		jRosterItem * ri;
		string from;
		xmlElement * q;
		
		from = stanza->Element()->AttributeValue("from");
		q = stanza->Element()->Child("query");
		ri = static_cast<jRosterItem *>(_roster->Item(from, true));
		if (ri != NULL) {
			ri->SoftwareName(q->ChildValue("name"));
			ri->SoftwareVersion(q->ChildValue("version"));
			ri->OS(q->ChildValue("os"));
		}
	}
	return true;
}

bool jSession::ParseIQRoster(xmlStanza * stanza)
{
	if (stanza->Element()->AttributeValue("type") == "result") {
		if (stanza->Element()->AttributeValue("id") == "roster_1") {	// reply to SyncRoster()
			xmlElement * q;
			list<xmlElement *> items;
			map<string, imRosterGroup *> grps;

			q = stanza->Element()->Child("query");
			if (q == NULL)
				return false;

			q->Children("item", items);

			for (list<xmlElement *>::iterator it = items.begin(); it != items.end(); it++) {
				jRosterItem * ri;
				list<xmlElement *> e_grps;
				
				wxLogVerbose("Roster item: jid: %s, name: %s, subscription: %s",
						(*it)->AttributeValue("jid").c_str(),
						(*it)->AttributeValue("name").c_str(),
						(*it)->AttributeValue("subscription").c_str());
						
				ri = new jRosterItem(this);
				ri->Name((*it)->AttributeValue("name"));
				ri->Id("jid:" + (*it)->AttributeValue("jid"));
				ri->Jid(jJid((*it)->AttributeValue("jid")));
				if (ri->Name().empty())
					ri->Name(ri->Jid().Jid());
				(*it)->Children("group", e_grps);
				if (e_grps.empty()) {
					_roster->AddItem(ri, NULL);
				} else {
					for (list<xmlElement *>::iterator it = e_grps.begin(); it != e_grps.end(); it++) {
						imRosterGroup * g = NULL;
						if (grps.find("group:" + (*it)->Value()) == grps.end()) {
					
							if (_roster->NestedGroups() && !_roster->NestedGroupsDelimiter().empty()) {
								string r_id = (*it)->Value(); // rest id
								string delim = _roster->NestedGroupsDelimiter();
								string parent_id = ""; // parent group id
								imRosterGroup * parent = NULL; // parent group id
								string::size_type d_pos;
								while ((d_pos = r_id.find(delim)) != string::npos) {
									string g_id;
									g_id = string(r_id, 0, d_pos);
									r_id = string(r_id, d_pos + delim.size());
									
									if (!parent_id.empty())
										parent_id = parent_id + delim;
									parent_id += g_id;
									if (grps.find("group:" + parent_id) == grps.end()) {
										g = new imRosterGroup(this);
										g->Id("group:" + parent_id);
										g->Name(g_id);
										_roster->AddGroup(g, parent);
										grps[g->Id()] = g;
									} else {
										g = grps["group:" + parent_id];
									}
									parent = g;
								}
								if (!r_id.empty()) {
									if (grps.find("group:" + (*it)->Value()) == grps.end()) {
										g = new imRosterGroup(this);
										g->Id("group:" + (*it)->Value());
										g->Name(r_id);
										_roster->AddGroup(g, parent);
										grps[g->Id()] = g;
									} else {
										g = grps["group:" + (*it)->Value()];
									}
								}
							} else {
								g = new imRosterGroup(this);
								g->Id("group:" + (*it)->Value());
								g->Name((*it)->Value());
								
								_roster->AddGroup(g);
								
								grps[g->Id()] = g;
							}
						}
						
						g = grps["group:" + (*it)->Value()];
						if (g != NULL)
							wxLogVerbose("jSession: Adding %s to group %s", ri->Id().c_str(), g->Id().c_str());
						_roster->AddItem(ri, g);
					}
				}
			}
			Oniria()->EventQueue()->Queue(Event("oniria:im:session:roster:updated"));
		}
	}
	return true;
}

bool jSession::ParsePresence(xmlStanza * stanza)
{
	
	if (stanza->Element()->AttributeValue("type") == "" ||
	    stanza->Element()->AttributeValue("type") == "unavailable") {
		oEvent * event;
		imRosterItem * item = NULL;
		jRosterItem * bare = NULL;
		jJid jid;
		imStatus status;
		vector<string> order;

		status = PresenceToStatus(stanza);
		jid.Set(stanza->Element()->AttributeValue("from"));
		
		item = _roster->Item("jid:" + jid.Jid());	// check if it's main item.
		if (item == NULL)				// find bare jid only if it's not main item.
			bare = static_cast<jRosterItem *>(_roster->Item("jid:" + jid.Bare()));

		if (_roster->AllItems()->find("jid:" + jid.Jid()) == _roster->AllItems()->end()) {
			
			jRosterSubItem * sitem;
			
			if (stanza->Element()->AttributeValue("type") == "unavailable")
				return true;
		
			if (jid.Resource().empty())
				return true;

			if (bare == NULL)
				return true;
			
			sitem = new jRosterSubItem(this, bare);
			sitem->Id("jid:" + jid.Jid());
			sitem->Name(jid.Resource());
			sitem->Jid(jid);
			try {
				sitem->Priority(ToUInt(stanza->Element()->ChildValue("priority")));
			} catch (...) {
			}
			item = sitem;
			_roster->AddSubItem(item, bare);
		
			event = Event("oniria:im:session:roster:item:new");
			event->XML()->AddChild("item-id", "jid:" + jid.Jid());
			Oniria()->EventQueue()->Queue(event);
		} else {
			item = _roster->AllItems()->find("jid:" + jid.Jid())->second;
		}
		
		if (item->Status() != status) {
			xmlStanza * verst;

			item->Status(status);
			if (!jid.Resource().empty() && bare != NULL && status.Status() == imStatus::na) {
				_roster->RemoveSubItem(item->Id());
				delete item;
				item = NULL;
			}
			if (bare != NULL) {
				bare->FixedOrder(order);
				if (!order.empty()) {
					if (item != NULL) {
						if (order.front() == item->Id())
							bare->Status(status);
					} else {
						bare->Status(bare->SubItem(order.front())->Status());
					}
				} else {
					bare->Status(status);	// should be only, when receiving type='unavailable' from last resource
				}
			}
	
			event = Event("oniria:im:session:roster:item:presence");
			event->XML()->AddChild("item-id", "jid:" + jid.Jid());
			Oniria()->EventQueue()->Queue(event);
			if (!jid.Resource().empty() && bare != NULL) {
				event = Event("oniria:im:session:roster:item:presence");
				event->XML()->AddChild("item-id", "jid:" + jid.Bare());
				Oniria()->EventQueue()->Queue(event);
			}
			
			verst = IQQuery("jabber:iq:version", "get", "version_1", jid.Jid(), _jid.Jid());
			_xml->AddStanza(verst);
		}

	}
	return true;
}

bool jSession::ParseMessage(xmlStanza * stanza)
{
	
	if (stanza->Element()->Child("body") != NULL) {
		jJid jid;
		jPeer * peer;
		imMessage * msg;
		string thid;
		imMessageThread * thr;
		jRosterItem * ri;
	
		thid = stanza->Element()->AttributeValue("from");
		jid.Set(thid);
		if (!stanza->Element()->ChildValue("thread").empty())
			thid = thid + ":" + stanza->Element()->ChildValue("thread");
	
		peer = new jPeer;
		peer->Jid(jid);
		peer->Name(jid.Jid());
		ri = static_cast<jRosterItem *>(Roster()->Item(string("jid:") + jid.Bare(), true));
		if (ri == NULL)
			ri = static_cast<jRosterItem *>(Roster()->Item(string("jid:") + jid.Jid(), true));
		if (ri != NULL) {
			peer->Name(ri->Name());
		}

		thr = GetMessageThread("msg", jid, thid);
	
		msg = new imMessage;
		msg->Subject(stanza->Element()->ChildValue("subject"));
		msg->Body(stanza->Element()->ChildValue("body"));
		msg->LocalPeer(thr->LocalPeer());
		msg->AddPeer(peer);

		thr->AddInMessage(msg);
	}

	return true;
}
