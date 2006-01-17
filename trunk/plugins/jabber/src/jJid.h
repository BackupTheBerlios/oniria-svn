/* $Id$ */
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
#ifndef __JJID_H
#define __JJID_H

#include <string>

using namespace std;

/*!\class jJid
 * \brief Represents a JID
 */
class jJid {

	public:

		/*!\fn jJid()
		 * \brief Trivial constructor.
		 */
		jJid();

		/*!\fn jJid(const string& full)
		 * \brief Constructor
		 * \param full JID in form node@domain/resource
		 */
		jJid(const string& full);

		/*!\fn jJid(const string& node, const string& domain, const string& resource = "")
		 * \brief Constructor
		 * \param node Node name
		 * \param domain Domain
		 * \param resource Resource
		 */
		jJid(const string& node, const string& domain, const string& resource = "");

		/*!\fn bool Set(const string& full)
		 * \brief Initialize jJid object
		 * \param full JID in form node@domain/resource
		 * \return JID in form node@domain/resource
		 */
		const string& Set(const string& full);

		/*!\fn bool Set(const string& bare, const string& resource)
		 * \brief Initialize jJid object
		 * \param bare JID in bare form (node@domain).
		 * \param resource Resource name.
		 * \return JID in form node@domain/resource
		 */
		const string& Set(const string& bare, const string& resource);

		/*!\fn bool Set(const string& node, const string& domain, const string& resource)
		 * \brief Initialize jJid object.
		 * \param node Node name
		 * \param domain Domain
		 * \param resource Resource
		 * \return JID in form node@domain/resource or empty string if given arguments
		 * are invalid.
		 */
		const string& Set(const string& node, const string& domain, const string& resource);

		/*!\fn const string& Jid() const
		 * \brief Returns JID in full form.
		 * \return JID
		 */
		const string& Jid() const { return _full; };

		/*!\fn const string& Node() const
		 * \brief Returns node name.
		 * \return Node name
		 */
		const string& Node() const { return _node; };

		/*!\fn const string& Domain() const
		 * \brief Returns domain.
		 * \return Domain
		 */
		const string& Domain() const { return _domain; };

		/*!\fn const string& Resource() const
		 * \brief Returns resource name.
		 * \return Resource name
		 */
		const string& Resource() const { return _resource; };

		/*!\fn const string& Bare() const
		 * \brief Returns JID in bare form (node@domain).
		 * \return JID in bare form.
		 */
		const string& Bare() const { return _bare; };

		/*!\fn bool Valid() const
		 * \brief Checks if JID is valid.
		 * \return true if JID is valid
		 */
		bool Valid() const;
		
	private:
		string _full;
		string _node;
		string _domain;
		string _resource;
		string _bare;
};

#endif
