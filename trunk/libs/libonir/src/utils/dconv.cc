/* $Id: dconv.cc 614 2005-12-29 16:44:50Z choman $ */
/*
 * Copyright (C) 2005
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

#if defined(HAVE_CONFIG_H)
# include <config.h>
#endif

#include "dconv.h"
#include "uException.h"
#include <sstream>
#include <cctype>

using std::stringstream;

namespace onirUtils {

string ToString(int i)
{
	stringstream s;
	s<<i;	
	return s.str();
}

string ToString(float i)
{
	stringstream s;
	s<<i;	
	return s.str();
}

bool ToInt(const string & val, int & ret)
{
	return (sscanf(val.c_str(),"%d", &ret) == 1);
}

bool ToFloat(const string & val, float & ret)
{
	return (sscanf(val.c_str(),"%f", &ret) == 1);	
}

int ToInt(const string & val)
{
	int ret;
	if (sscanf(val.c_str(),"%d", &ret))
		return ret;
	else{ 
		throw uException(_("Error conversion string do integer value"), "int ToInt(const string & val)");
	}	 			
}

unsigned int ToUInt(const string & val)
{
	unsigned int ret;
	if (sscanf(val.c_str(),"%u", &ret))
		return ret;
	else{ 
		throw uException(_("Error conversion string do integer value"), "int ToInt(const string & val)");
	}	 			
}

float ToFloat(const string & val)
{
	float ret;
	if (sscanf(val.c_str(),"%f", &ret))
		return ret;
	else{ 
		throw uException(_("Error conversion string do floating point value"), "float ToFloat(const string & val)");
	}
}

string SplitString(const string & str, int len, bool dots, bool show_non_print_sybmol)
{
	int index = 0;
	string ret, bs = str;
	for (string::iterator i = bs.begin(); i != bs.end(); ++i){
		if (isprint(*i))
			ret+=*i;
		else if (show_non_print_sybmol)
			ret+="~";
		if (index++>=len){
			if (dots)
				ret+=" ...";
			break;
		}
	}
	return ret;
}
 
}
