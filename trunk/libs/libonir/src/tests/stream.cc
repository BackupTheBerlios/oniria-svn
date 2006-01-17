/* $Id$ */
#include <string>
#include <iostream>
#include <clocale>
#include <onir.h>
#include <wx/socket.h>
#include <utils/uException.h>
#include <utils/uBuffer.h>
#include <io/ioSocketStream.h>

using namespace onirUtils;
using namespace onirIO;

int main(int argc, char * argv[])
{
	ioSocketStream tcp;
	uBuffer buf;

	setlocale(LC_ALL, "pl_PL");
	libonir_init();

	try {
		string host = argv[1];
		wxSocketClient * sock = new wxSocketClient;
		wxIPV4address addr;
		addr.Hostname(host);
		addr.Service(25);
		sock->Connect(addr, true);
		tcp.Socket(sock);
		tcp.NonBlocking();
		
		while (!tcp.Read(&buf, 0));
		cout << buf.str() << endl;
	} catch (uException e) {
		cerr << e.what() << endl;
	}

	return 0;
}
