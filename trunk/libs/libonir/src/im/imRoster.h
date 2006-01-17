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
#ifndef __IMROSTER_H
#define __IMROSTER_H

#include "../dll.h"
#include "../oObject.h"
#include <map>

using std::map;
using onir::oObject;

namespace onirIM {

class imSession;
class imRosterEntry;
class imRosterItem;
class imRosterGroup;

/*!\class imRoster
 * \brief Roster (contact list)
 */
class LIBONIR_API imRoster : public oObject {

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imRoster(imSession * session)
		 * \brief Constructor
		 * \param session Pointer to session object.
		 */
		imRoster(imSession * sessions);

		/*!\fn virtual ~imRoster()
		 * \brief Destructor.
		 */
		virtual ~imRoster();
		/* @} */
	
		/*!\fn inline imSession * Session() const
		 * \brief Returns session pointer.
		 * \return Session pointer.
		 */
		inline imSession * Session() const { return _session; };

		inline map<string, imRosterEntry *> * Entries() { return &_entries; };
		inline map<string, imRosterItem *> * Items() { return &_items; };
		inline map<string, imRosterItem *> * AllItems() { return &_allitems; };
		inline map<string, imRosterGroup *> * Groups() { return &_groups; };
		inline map<string, imRosterEntry *> * TopEntries() { return &_top_entries; };
		inline map<string, imRosterItem *> * TopItems() { return &_top_items; };
		inline map<string, imRosterGroup *> * TopGroups() { return &_top_groups; };

		virtual bool AddEntry(imRosterEntry * entry, imRosterGroup * g);
		virtual bool AddEntry(imRosterEntry * entry, const string& g = "");
		virtual bool AddItem(imRosterItem * entry, imRosterGroup * g);
		virtual bool AddItem(imRosterItem * entry, const string& g = "");
		virtual bool AddSubItem(imRosterItem * entry, imRosterItem * item);
		virtual bool AddSubItem(imRosterItem * entry, const string& item = "");
		virtual bool AddGroup(imRosterGroup * entry, imRosterGroup * g);
		virtual bool AddGroup(imRosterGroup * entry, const string& g = "");
		
		virtual imRosterItem * RemoveItem(const string& id);
		virtual imRosterGroup * RemoveGroup(const string& id);
		virtual imRosterItem * RemoveSubItem(const string& id);
		
		virtual imRosterEntry * Entry(const string& id);
		virtual imRosterItem * Item(const string& id, bool allitems = false);
		virtual imRosterGroup * Group(const string& id);
		virtual imRosterEntry * TopEntry(const string& id);
		virtual imRosterItem * TopItem(const string& id);
		virtual imRosterGroup * TopGroup(const string& id);

	private:

		imSession * _session;

		map<string, imRosterEntry *> _entries;
		map<string, imRosterItem *> _items;
		map<string, imRosterItem *> _allitems;
		map<string, imRosterGroup *> _groups;
		map<string, imRosterEntry *> _top_entries;
		map<string, imRosterItem *> _top_items;
		map<string, imRosterGroup *> _top_groups;

		DECLARE_OOBJECT;
};



};

#endif
