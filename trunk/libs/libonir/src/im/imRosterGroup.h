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
#ifndef __IMROSTERGROUP_H
#define __IMROSTERGROUP_H

#include <vector>
#include <map>
#include "../dll.h"
#include "imStatus.h"
#include "imRosterEntry.h"
#include "imRosterItem.h"

using std::vector;
using std::map;

namespace onirIM {

class imSession;

/*!\class imRosterGroup
 * \brief Roster group.
 */
class LIBONIR_API imRosterGroup : public imRosterEntry {

	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn imRosterGroup(imSession * session)
		 * \brief Constructor
		 * \param session Pointer to session object.
		 */
		imRosterGroup(imSession * session);

		/*!\fn virtual ~imRosterGroup()
		 * \brief Destructor.
		 */
		virtual ~imRosterGroup();
		//@}
		
		inline map<string, imRosterEntry *> * Entries() { return &_entries; };
		inline map<string, imRosterItem *> * Items() { return &_items; };
		inline map<string, imRosterGroup *> * Groups() { return &_groups; };

		virtual bool AddEntry(imRosterEntry * e);
		virtual bool AddItem(imRosterItem * e);
		virtual bool AddGroup(imRosterGroup * e);

		virtual imRosterItem * RemoveItem(const string& id);
		virtual imRosterGroup * RemoveGroup(const string& id);

		virtual imRosterEntry * Entry(const string& id);
		virtual imRosterItem * Item(const string& id);
		virtual imRosterGroup * Group(const string& id);

		virtual bool FixedOrder(vector<string>& olist);

	private:
	
		map<string, imRosterEntry *> _entries;
		map<string, imRosterItem *> _items;
		map<string, imRosterGroup *> _groups;

		DECLARE_OOBJECT;
};



};

#endif
