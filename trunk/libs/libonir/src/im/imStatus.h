/* $Id: imStatus.h 608 2005-10-07 09:57:23Z choman $ */
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

#include "../dll.h"
#include "../oObject.h"

using onir::oObject;

namespace onirIM {

/*!\class imStatus
 * \brief Contact status.
 */
class LIBONIR_API imStatus : public oObject {

	public:

		/*!\enum status
		 * \brief Statuses
		 */
		enum status {
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

		/*!\fn imStatus(status st = unspecified, const string& description = "")
		 * \brief Constructor
		 * \param st Status.
		 * \param description Status description.
		 */
		imStatus(status st = unspecified, const string& description = "");
		//@}
		


		/*!\fn inline void Set(status st, const string& desc = "")
		 * \brief Sets status.
		 * \param st Status.
		 * \param desc Status description.
		 */
		inline void Set(status st, const string& desc = "") { _status = st; _description = desc; };

		/*!\fn inline status * Status() const
		 * \brief Returns status.
		 * \return Status.
		 */
		inline status Status() const { return _status; };

		/*!\fn inline const string& Description() const
		 * \brief Returns status description.
		 * \return Status description.
		 */
		inline const string& Description() const { return _description; };

		/*!\fn string IconId() const
		 * \brief Returns icon id associated with status.
		 * \return Icon id.
		 */
		string IconId() const;
		
		/*!\fn string StatusToString() const
		 * \brief Returns string representation of status.
		 * \return String representation of status.
		 */
		string StatusToString() const;
		
		inline bool operator==(const imStatus& s) const { return Status() == s.Status() && Description() == s.Description(); };
		inline bool operator!=(const imStatus& s) const { return Status() != s.Status() || Description() != s.Description(); };

	private:

		status _status;
		string _description;

		DECLARE_OOBJECT;
};



};

#endif
