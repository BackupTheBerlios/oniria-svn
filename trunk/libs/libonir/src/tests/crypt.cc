/* $Id: crypt.cc 614 2005-12-29 16:44:50Z choman $ */
#include <string>
#include <iostream>
#include <iomanip>
#include <onir.h>
#include <crypt/cptMD5.h>
#include <crypt/cptHMAC.h>

using namespace onirCrypt;
using namespace std;

int main(int argc, char * argv[])
{
	string msg = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	string md5_sum;
	string hmac_val;
	cptMD5 md5;
	cptHMAC hmac;

	md5_sum = md5.cptHash::Compute(msg);

	cout << md5.FullType() << endl;
	cout << "Message: " << msg << endl;
	cout << "MD5: " << md5_sum << endl;

	msg = "what do ya want for nothing?";
	hmac_val = hmac.Compute(msg, "Jefe");
	cout << "HMAC-MD5: " << hmac_val << endl;

	return 0;
}
