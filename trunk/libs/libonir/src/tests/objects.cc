/* $Id: objects.cc 614 2005-12-29 16:44:50Z choman $ */
#include <string>
#include <iostream>
#include <clocale>
#include <onir.h>
#include <oObject.h>

using namespace onir;

class ChildClass : public oObject {
	public:
		ChildClass();
		~ChildClass();

	DECLARE_OOBJECT;
};

DEFINE_OOBJECT(ChildClass, oObject);

ChildClass::ChildClass()
{
	INIT_OOBJECT;
}

ChildClass::~ChildClass()
{
}

class ChildClass2 : public ChildClass {
	public:
		ChildClass2();
		~ChildClass2();

	DECLARE_OOBJECT;
};

DEFINE_OOBJECT(ChildClass2, ChildClass);

ChildClass2::ChildClass2()
{
	INIT_OOBJECT;
}

ChildClass2::~ChildClass2()
{
}

int main(int argc, char * argv[])
{
	ChildClass c;
	ChildClass2 c2;

	cout << "c.type()                : " << c.type() << endl;
	cout << "c2.type()               : " << c2.type() << endl;
	cout << "c.name()                : " << c.name() << endl;
	cout << "c2.name()               : " << c2.name() << endl;
	cout << "c.FullType()         : " << c.FullType() << endl;
	cout << "c2.FullType()        : " << c2.FullType() << endl;
	cout << "c.IsKindOf(oObject)     : " << (c.IsKindOf("oObject") ? "true" : "false") << endl;
	cout << "c2.IsKindOf(oObject)    : " << (c2.IsKindOf("oObject") ? "true" : "false") << endl;
	cout << "c.IsKindOf(xObject)     : " << (c.IsKindOf("xObject") ? "true" : "false") << endl;
	cout << "c2.IsKindOf(xObject)    : " << (c2.IsKindOf("xObject") ? "true" : "false") << endl;
	cout << "c2.IsKindOf(ChildClass) : " << (c2.IsKindOf("ChildClass") ? "true" : "false") << endl;
	cout << "c2.IsKindOf(c)          : " << (c2.IsKindOf(c) ? "true" : "false") << endl;
	cout << "c.IsKindOf(c2)          : " << (c.IsKindOf(c2) ? "true" : "false") << endl;

	return 0;
}
