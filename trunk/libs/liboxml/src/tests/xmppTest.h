/* $Id$ */
#ifndef __XMPPTEST_H
#define __XMPPTEST_H

#include <QObject>
#include <QTcpSocket>
#include "../xmlStream.h"
#include "../xmlStanza.h"

using namespace onirXML;

class xmppTest : public QObject
{
		Q_OBJECT;

	public:
		void init();
		void run();


	protected slots:
		void connected();
		void receivedStanza(xmlStanza * stanza);

	private:
		QTcpSocket * _socket;
		xmlStream * _stream;

};

#endif

