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
#ifndef __JSESSION_H
#define __JSESSION_H

#include <QString>
#include <QList>
#include <onir/oOniria.h>
#include <oim/imProtocol.h>
#include <oim/imSession.h>
#include <oim/imStatus.h>
#include <oim/imMessage.h>
#include <oim/imMessageThread.h>
#include <oxml/xmlElement.h>
#include <oxml/xmlStanza.h>
#include <oxml/xmlStream.h>
#include <osasl/saslSASL.h>
#include <onir/oEvent.h>
#include "jJid.h"

using namespace onirIM;
using onirXML::xmlStream;
using onirXML::xmlStanza;
using onirXML::xmlElement;
using onirSASL::saslSASL;
using onir::oOniria;
using onir::oEvent;

class QTcpSocket;
class jRoster;

class jSession : public imSession {
		
		Q_OBJECT;

	public:
		jSession(oOniria * o, imProtocol * proto);
		virtual ~jSession();

		virtual bool setStatus();

		virtual bool syncRoster(bool send);
		virtual imRoster * roster();

		virtual bool load(xmlElement *cnode);
		virtual bool connect(bool ac = false);
		
		virtual imMessageQueue * createMessageQueue();
		virtual bool sendMessage(imMessage * msg);
		imMessageThread * getMessageThread(const QString& type, const jJid& peer, const QString& id = "");

		virtual bool poll();

		inline oOniria * oniria() const { return _oniria; };

	protected slots:
		void connected();
		void receivedStanza(xmlStanza * stanza);

	protected:

		bool presence(const QString& status, const QString& desc = "", const QString& type = "", const QString& to = "");
		imStatus presenceToStatus(xmlStanza * stanza);
		xmlStanza * iq(const QString& type, const QString& id, const QString& to = "", const QString& from = "");
		xmlElement * query(const QString& xmlns);
		xmlStanza * iqQuery(const QString& xmlns, const QString& type, const QString& id, const QString& to = "", const QString& from = "");
		oEvent * event(const QString& id);

		bool SASLAuth(const QList<QString>& mechs);
		bool doSASLAuth(xmlStanza * stanza);
		bool bindResource();
		bool establishSession();

		bool parseFeatures(xmlStanza * stanza);

		bool parseIQ(xmlStanza * stanza);
		bool parseIQBind(xmlStanza * stanza);
		bool parseIQSession(xmlStanza * stanza);
		bool parseIQRoster(xmlStanza * stanza);
		bool parseIQPrivate(xmlStanza * stanza);
		bool parseIQVersion(xmlStanza * stanza);

		bool parsePresence(xmlStanza * stanza);
		
		bool parseMessage(xmlStanza * stanza);

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

		oOniria * _oniria;

		sessionState _state;

		jJid _jid;
		unsigned int _priority;
		QString _password;

		QTcpSocket * _socket;
		xmlStream * _xml;

		bool _feat_bind;	// server supports resource binding
		bool _feat_sess;	// server supports sessions

		bool _force_no_sasl;
		saslSASL * _sasl;
		
		jRoster * _roster;
};

#endif
