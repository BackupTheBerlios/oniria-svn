/* $Id: uException.h 182 2005-07-26 19:08:19Z choman $ */
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
#ifndef __UEXCEPTION_H
#define __UEXCEPTION_H

#include "../dll.h"

#include <string>
#include <exception>

using namespace std;

namespace onirUtils {

/*!\class uException
 * \brief Base exception class.
 *
 * Plugins should use this class when throwing exceptions.
 */
class LIBONIR_API uException : public exception {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn uException() throw()
		 * \brief Trivial constructor.
		 */
		uException() throw();

		/*!\fn uException(const string& err, const string& where = "") throw()
		 * \brief Constructor.
		 * \param err String describing error condition.
		 * \param where String describing where an error occured.
		 */
		uException(const string& err, const string& where = "") throw();

		/*!\fn virtual ~uException() throw()
		 * \brief Destructor
		 */
		virtual ~uException() throw();
		//@}

		/*!\fn virtual const char * what() const throw()
		 * \brief Returns error description.
		 * \return Error description
		 * \sa Where(), RawWhat()
		 *
		 * String returned by this method is combined from strings
		 * returned by Where() and RawWhat().
		 */
		virtual const char * what() const throw();

		/*!\fn inline const string& Where() const throw()
		 * \brief Returns string describing where exception occured.
		 * \return String descriping where exception occured.
		 * \sa what(), RawWhat()
		 */
		inline const string& Where() const throw() { return _where; };

		/*!\fn inline const string& RawWhat() const throw()
		 * \brief Returns string describing error.
		 * \return String describing error.
		 * \sa what(), Where()
		 */
		inline const string& RawWhat() const throw() { return _what; };

	private:
		string _what;
		string _where;
};

};

#endif
