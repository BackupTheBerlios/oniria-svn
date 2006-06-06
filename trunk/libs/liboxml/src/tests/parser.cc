/* $Id$ */
#include <QtDebug>
#include <QObject>
#include "../xmlAttribute.h"
#include "../xmlElement.h"
#include "../xmlParser.h"

using namespace onirXML;

int main(int argc, char * argv[])
{
	xmlParser parser;

	parser.parseFile("test.xml");
	qDebug() << parser.root()->format(false);

	return 0;
}

