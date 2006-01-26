/* $Id$ */
#include <QtDebug>
#include "../xmlAttribute.h"
#include "../xmlElement.h"
#include "../xmlStream.h"

using namespace onirXML;

int main(int argc, char * argv[])
{
	xmlStream stream;
/*
	addr.Hostname("nmax.eu.org");
	addr.Service(5222);
	sock->Connect(addr, true);
	tcp.Socket(sock);
	tcp.NonBlocking();

	stream.Input(&tcp);
	stream.Output(&tcp);
*/
	stream.prepare();
	stream.outRoot()->addAttribute("to", "nmax.eu.org");
	stream.outRoot()->addAttribute("xmlns", "jabber:client");
	stream.outRoot()->addAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
	stream.outRoot()->addAttribute("version", "1.0");
	stream.initiate();

	while (1) {
		stream.poll();
	}

	qDebug() << "test1" << "test1.5";
	qDebug() << "test2";
	qDebug() << "test3";
	return 0;
}

