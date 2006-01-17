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
#ifndef __JSESSION_H
#define __JSESSION_H

#include <list>
#include <string>
#include <wx/socket.h>
#include <onir/oOniria.h>
#include <onir/im/imProtocol.h>
#include <onir/im/imSession.h>
#include <onir/im/imStatus.h>
#include <onir/im/imMessage.h>
#include <onir/im/imMessageThread.h>
#include <onir/io/ioSocketStream.h>
#include <onir/xml/xmlElement.h>
#include <onir/xml/xmlStanza.h>
#include <onir/xml/xmlStream.h>
#include <onir/sasl/saslSASL.h>
#include <onir/oEvent.h>
#include "jJid.h"

using namespace std;
using namespace onirIM;
using onirIO::ioSocketStream;
using onirXML::xmlStream;
using onirXML::xmlStanza;
using onirXML::xmlElement;
using onirSASL::saslSASL;
using onir::oOniria;
using onir::oEvent;

class jRoster;

class jSession : public imSession {

	public:
		jSession(oOniria * o, imProtocol * proto);
		virtual ~jSession();

		virtual bool SetStatus();

		virtual bool SyncRoster(bool send);
		virtual imRoster * Roster();

		virtual bool Load(xmlElement *cnode);
		virtual bool Connect(bool ac = false);
		
		virtual imMessageQueue * CreateMessageQueue();
		virtual bool SendMessage(imMessage * msg);
		imMessageThread * GetMessageThread(const string& type, const jJid& peer, const string& id = "");

		virtual bool Poll();

	protected:

		bool Presence(const string& status, const string& desc = "", const string& type = "", const string& to = "");
		imStatus PresenceToStatus(xmlStanza * stanza);
		xmlStanza * IQ(const string& type, const string& id, const string& to = "", const string& from = "");
		xmlElement * Query(const string& xmlns);
		xmlStanza * IQQuery(const string& xmlns, const string& type, const string& id, const string& to = "", const string& from = "");
		oEvent * Event(const string& id);

		bool SASLAuth(const list<string>& mechs);
		bool DoSASLAuth(xmlStanza * stanza);
		bool BindResource();
		bool EstablishSession();

		bool ParseFeatures(xmlStanza * stanza);

		bool ParseIQ(xmlStanza * stanza);
		bool ParseIQBind(xmlStanza * stanza);
		bool ParseIQSession(xmlStanza * stanza);
		bool ParseIQRoster(xmlStanza * stanza);
		bool ParseIQPrivate(xmlStanza * stanza);
		bool ParseIQVersion(xmlStanza * stanza);

		bool ParsePresence(xmlStanza * stanza);
		
		bool ParseMessage(xmlStanza * stanza);

	private:
		enum sessionState {
			unknown,
			connecting,
			authenticating,
			authenticated,
			binding,
			establishing,
			established,
			closed
		};

		sessionState _state;

		jJid _jid;
		unsigned int _priority;
		string _password;

		wxSocketClient * _socket;
		ioSocketStream * _iostream;
		xmlStream * _xml;

		bool _feat_bind;	// server supports resource binding
		bool _feat_sess;	// server supports sessions

		bool _force_no_sasl;
		saslSASL * _sasl;
		
		jRoster * _roster;


		DECLARE_OOBJECT;
};

#endif
