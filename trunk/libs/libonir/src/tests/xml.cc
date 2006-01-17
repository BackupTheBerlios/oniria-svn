/* $Id: xml.cc 614 2005-12-29 16:44:50Z choman $ */
#include <string>
#include <iostream>
#include <clocale>
#include <wx/socket.h>
#include <onir.h>
#include <oObject.h>
#include <io/ioSocketStream.h>
#include <xml/xmlAttribute.h>
#include <xml/xmlElement.h>
#include <xml/xmlStream.h>

using namespace onirXML;
using namespace onirIO;

int main(int argc, char * argv[])
{
	xmlStream stream;
	ioSocketStream tcp;
	wxSocketClient * sock = new wxSocketClient;
	wxIPV4address addr;

	addr.Hostname("nmax.eu.org");
	addr.Service(5222);
	sock->Connect(addr, true);
	tcp.Socket(sock);
	tcp.NonBlocking();

	stream.Input(&tcp);
	stream.Output(&tcp);

	stream.Prepare();
	stream.OutRoot()->AddAttribute("to", "nmax.eu.org");
	stream.OutRoot()->AddAttribute("xmlns", "jabber:client");
	stream.OutRoot()->AddAttribute("xmlns:stream", "http://etherx.jabber.org/streams");
	stream.OutRoot()->AddAttribute("version", "1.0");
	stream.Initiate();

	while (1)
		stream.Poll();

	return 0;
}
