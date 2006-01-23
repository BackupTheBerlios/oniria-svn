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
#ifndef __IMSTATUS_H
#define __IMSTATUS_H

#include <QString>
#include "oim_dll.h"

namespace onirIM {

/*!\class imStatus
 * \brief Contact status.
 */
class LIBOIM_API imStatus {

	public:

		/*!\enum contatctStatus
		 * \brief Statuses
		 */
		enum contactStatus {
			unspecified,	/*!< Status is unset. */
			chat,		/*!< The entity or resource is actively interested in chatting. */
			avail,		/*!< The entity or resource is available */
			away,		/*!< The entity or resource is temporarily away. */
			xa,		/*!< The entity or resource is away for an extended period (xa = "eXtended Away"). */
			dnd,		/*!< The entity or resource is busy (dnd = "Do Not Disturb"). */
			inv,		/*!< The entity or resource is invisible. */
			na		/*!< The entity or resource is not available (disconnected). */
		};

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn imStatus(contactStatus st = unspecified, const QString& description = "")
		 * \brief Constructor
		 * \param st Status.
		 * \param description Status description.
		 */
		imStatus(contactStatus st = unspecified, const QString& description = "");
		//@}
		


		/*!\fn inline void set(status st, const QString& desc = "")
		 * \brief Sets status.
		 * \param st Status.
		 * \param desc Status description.
		 */
		inline void set(contactStatus st, const QString& desc = "") { _status = st; _description = desc; };

		/*!\fn inline contactStatus * status() const
		 * \brief Returns status.
		 * \return Status.
		 */
		inline contactStatus status() const { return _status; };

		/*!\fn inline const QString& description() const
		 * \brief Returns status description.
		 * \return Status description.
		 */
		inline const QString& description() const { return _description; };

		/*!\fn QString iconId() const
		 * \brief Returns icon id associated with status.
		 * \return Icon id.
		 */
		QString iconId() const;
		
		/*!\fn QString statusToString() const
		 * \brief Returns QString representation of status.
		 * \return String representation of status.
		 */
		QString statusToString() const;
		
		inline bool operator== (const imStatus& s) const { return status() == s.status() && description() == s.description(); };
		inline bool operator!= (const imStatus& s) const { return status() != s.status() || description() != s.description(); };

	private:

		contactStatus _status;
		QString _description;
};



};

#endif
