/* $Id: dconv.h 418 2005-08-22 12:26:01Z choman $ */
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
 
#include "../dll.h" 
 
#include <string>

/*! \file dconv.h
 * \brief data conversion functions
 */

using std::string;
namespace onirUtils { 

/*! \fn bool LIBONIR_API ToInt(const string & val, int & ret)
 * \brief string do int conversion
 *
 * \param val string to convert
 * \param ret return value
 * \return true if conversion is success, false if fail
 */
bool LIBONIR_API ToInt(const string & val, int & ret);

/*! \fn bool LIBONIR_API ToFloat(const string & val, float & ret)
 * \brief string do float conversion
 *
 * \param val string to convert
 * \param ret return value
 * \return true if conversion is success, false if fail
 */
bool LIBONIR_API ToFloat(const string & val, float & ret);

/*! \fn bool LIBONIR_API ToInt(const string & val, int & ret)
 * \brief string do int conversion
 *
 * functions call exception uException if conversion fail;
 * \param val string to convert
 * \return converted value
 */
int LIBONIR_API ToInt(const string & val);

/*!\fn unsigned int LIBONIR_API ToUInt(const string & val)
 * \brief String to int conversion
 * \param val string to convert
 * \return converted value
 *
 * Throws uException if conversion fail.
 */
unsigned int LIBONIR_API ToUInt(const string & val);

/*! \fn bool LIBONIR_API ToFloat(const string & val, float & ret)
 * \brief string do float conversion
 *
 * functions call exception uException if conversion fail;
 * \param val string to convert
 * \return converted value
 */
float LIBONIR_API ToFloat(const string & val);

/*! \fn string LIBONIR_API ToString(int i)
 * \brief convert integer to string 
 *
 * \param i value to convert
 * \return converted value
 */
string LIBONIR_API ToString(int i);

/*! \fn string LIBONIR_API ToString(float i)
 * \brief convert float to string 
 *
 * \param i value to convert
 * \return converted value
 */ 
string LIBONIR_API ToString(float i);

/*! \fn string LIBONIR_API SplitString(const string & str, int len = 20, bool dots = true, bool show_non_print_sybmol)
 * \brief Cut string to <i>len</i>
 * \param str string to cut
 * \param len max string length
 * \param dots flag says to add three dots at end of the str, if str is greater on len
 * \param show_non_print_sybmol if in str is nonprint char then it's replace to "~"
 * \return converted value
 *
 * Function, replaces multi to single line string, and cut to specified length
 */ 
string LIBONIR_API SplitString(const string & str, int len = 20, bool dots = true, bool show_non_print_sybmol = true);

};
