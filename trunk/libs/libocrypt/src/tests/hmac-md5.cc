/* $Id$ */
#include <QString>
#include <iostream>
#include "../cptMD5.h"
#include "../cptHMAC.h"

using namespace std;
using namespace onirCrypt;

int main(int argc, char * argv[])
{
	QString msg = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	QString md5_sum;
	QString hmac_val;
	cptMD5 md5;
	cptHMAC hmac;

	md5_sum = md5.cptHash::compute(msg);

	cout << "Message: " << msg.toLocal8Bit().data() << endl; 
	cout << "MD5: " << md5_sum.toLocal8Bit().data() << endl;

	msg = "what do ya want for nothing?";
	hmac_val = hmac.compute(msg, "Jefe");
	cout << "HMAC-MD5: " << hmac_val.toLocal8Bit().data() << endl;

	return 0;
}
