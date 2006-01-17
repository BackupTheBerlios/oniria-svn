/* $Id: imRosterEntry.h 492 2005-09-02 13:18:12Z choman $ */
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
#ifndef __IMROSTERENTRY_H
#define __IMROSTERENTRY_H

#include <map>
#include "../dll.h"
#include "../oObject.h"
#include "imStatus.h"

using onir::oObject;
using std::map;

namespace onirIM {

class imSession;
class imRosterGroup;

/*!\class imRosterEntry
 * \brief Roster entry.
 */
class LIBONIR_API imRosterEntry : public oObject {

	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn imRosterEntry(imSession * session)
		 * \brief Constructor
		 * \param session Pointer to session object.
		 */
		imRosterEntry(imSession * session);

		/*!\fn virtual ~imRosterEntry()
		 * \brief Destructor.
		 */
		virtual ~imRosterEntry();
		//@}
		


		/*!\fn inline imSession * Session() const
		 * \brief Returns pointer to session object.
		 * \return Pointer to session object to which this roster entry belongs.
		 */
		inline imSession * Session() const { return _session; };

		/*!\fn virtual string Name() const
		 * \brief Returns roster entry name.
		 * \return Roster entry name.
		 */
		virtual string Name() const;

		/*!\fn virtual void Name(const string& n)
		 * \brief Sets roster entry name.
		 * \param n New name.
		 */
		virtual void Name(const string& n);

		/*!\fn virtual string Id() const
		 * \brief Returns roster entry id.
		 * \return Roster item id.
		 */
		virtual string Id() const;

		/*!\fn virtual void Id(const string& n)
		 * \brief Sets roster item id.
		 * \param n New id.
		 */
		virtual void Id(const string& n);

		/*!\fn inline const string& IconSet() const
		 * \brief Returns roster iconset name.
		 * \return Roster iconset.
		 */
		inline const string& IconSet() const { return _iconset; };

		/*!\fn inline void IconSet(const string& n)
		 * \brief Sets roster icon set name.
		 * \param n New iconset.
		 */
		inline void IconSet(const string& n) { _iconset = n; };
		
		inline void SkinRoot(const string& s) { _skin = s; };
		inline const string& SkinRoot() const { return _skin; };

		virtual void AddToGroup(imRosterGroup * g);
		virtual void RemoveFromGroup(const string& id);
		inline map<string, imRosterGroup *> * InGroups() { return &_in_groups; };

	private:

		imSession * _session;
		string _name;
		string _id;
		string _iconset;
		string _skin;
		map<string, imRosterGroup *> _in_groups;

		DECLARE_OOBJECT;
};



};

#endif
