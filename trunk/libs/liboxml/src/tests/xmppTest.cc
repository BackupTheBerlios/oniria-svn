/* $Id$ */
#include <QtDebug>
#include <QTcpSocket>
#include <QObject>
#include "../xmlAttribute.h"
#include "../xmlElement.h"
#include "../xmlStream.h"
#include "xmppTest.h"

using namespace onirXML;

void xmppTest::init()
{
	_socket = new QTcpSocket(this);
	QObject::connect(_socket, SIGNAL(connected()), SLOT(connected()));
	_socket->connectToHost("sauron.nmax.eu.org", 5222);
	_stream = new xmlStream();
	_stream->input(_socket);
	_stream->output(_socket);
	QObject::connect(_stream, SIGNAL(receivedStanza(xmlStanza *)), SLOT(receivedStanza(xmlStanza *)));
}

void xmppTest::run()
{
	while (1) {
		if (_socket->state() != QAbstractSocket::ConnectedState)
			_socket->waitForConnected(0);
		else {
			_socket->waitForReadyRead(0);
			_stream->poll();
		}
	}
}

void xmppTest::connected()
{
	qDebug() << "connected()";
	_stream->prepare();
	_stream->outRoot()->addAttribute("to", "sauron.nmax.eu.org");
	_stream->outRoot()->addAttribute("xmlns", "jabber:client");
	_stream->outRoot()->addAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
	_stream->outRoot()->addAttribute("version", "1.0");
	_stream->initiate();
}

void xmppTest::receivedStanza(xmlStanza * stanza)
{
	qDebug() << "got stanza: " << stanza->element()->name();
	delete stanza;
}

int main(int argc, char * argv[])
{
	xmppTest test;
	xmlStream stream;

	test.init();
	test.run();

	return 0;
}

