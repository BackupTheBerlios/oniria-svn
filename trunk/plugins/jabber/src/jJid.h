/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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

#include <QString>

/*!\class jJid
 * \brief Represents a JID
 */
class jJid {

	public:

		/*!\fn jJid()
		 * \brief Trivial constructor.
		 */
		jJid();

		/*!\fn jJid(const QString& full)
		 * \brief Constructor
		 * \param full JID in form node@domain/resource
		 */
		jJid(const QString& full);

		/*!\fn jJid(const QString& node, const QString& domain, const QString& resource = "")
		 * \brief Constructor
		 * \param node Node name
		 * \param domain Domain
		 * \param resource Resource
		 */
		jJid(const QString& node, const QString& domain, const QString& resource = "");

		/*!\fn bool set(const QString& full)
		 * \brief Initialize jJid object
		 * \param full JID in form node@domain/resource
		 * \return JID in form node@domain/resource
		 */
		const QString& set(const QString& full);

		/*!\fn bool set(const QString& bare, const QString& resource)
		 * \brief Initialize jJid object
		 * \param bare JID in bare form (node@domain).
		 * \param resource Resource name.
		 * \return JID in form node@domain/resource
		 */
		const QString& set(const QString& bare, const QString& resource);

		/*!\fn bool set(const QString& node, const QString& domain, const QString& resource)
		 * \brief Initialize jJid object.
		 * \param node Node name
		 * \param domain Domain
		 * \param resource Resource
		 * \return JID in form node@domain/resource or empty QString if given arguments
		 * are invalid.
		 */
		const QString& set(const QString& node, const QString& domain, const QString& resource);

		/*!\fn const QString& jid() const
		 * \brief Returns JID in full form.
		 * \return JID
		 */
		const QString& jid() const { return _full; };

		/*!\fn const QString& node() const
		 * \brief Returns node name.
		 * \return Node name
		 */
		const QString& node() const { return _node; };

		/*!\fn const QString& domain() const
		 * \brief Returns domain.
		 * \return Domain
		 */
		const QString& domain() const { return _domain; };

		/*!\fn const QString& resource() const
		 * \brief Returns resource name.
		 * \return Resource name
		 */
		const QString& resource() const { return _resource; };

		/*!\fn const QString& bare() const
		 * \brief Returns JID in bare form (node@domain).
		 * \return JID in bare form.
		 */
		const QString& bare() const { return _bare; };

		/*!\fn bool valid() const
		 * \brief Checks if JID is valid.
		 * \return true if JID is valid
		 */
		bool valid() const;
		
	private:
		QString _full;
		QString _node;
		QString _domain;
		QString _resource;
		QString _bare;
};

#endif

