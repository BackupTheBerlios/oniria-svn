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

#include <QObject>
#include <QMap>
#include "oim_dll.h"

namespace onirIM {

class imSession;
class imRosterEntry;
class imRosterItem;
class imRosterGroup;

/*!\class imRoster
 * \brief Roster (contact list)
 */
class LIBOIM_API imRoster : public QObject {

	Q_OBJECT

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
	
		/*!\fn inline imSession * session() const
		 * \brief Returns session pointer.
		 * \return Session pointer.
		 */
		inline imSession * session() const { return _session; };

		inline QMap<QString, imRosterEntry *> * entries() { return &_entries; };
		inline QMap<QString, imRosterItem *> * items() { return &_items; };
		inline QMap<QString, imRosterItem *> * allItems() { return &_allitems; };
		inline QMap<QString, imRosterGroup *> * groups() { return &_groups; };
		inline QMap<QString, imRosterEntry *> * topEntries() { return &_top_entries; };
		inline QMap<QString, imRosterItem *> * topItems() { return &_top_items; };
		inline QMap<QString, imRosterGroup *> * topGroups() { return &_top_groups; };

		virtual bool addEntry(imRosterEntry * entry, imRosterGroup * g);
		virtual bool addEntry(imRosterEntry * entry, const QString& g = "");
		virtual bool addItem(imRosterItem * entry, imRosterGroup * g);
		virtual bool addItem(imRosterItem * entry, const QString& g = "");
		virtual bool addSubItem(imRosterItem * entry, imRosterItem * item);
		virtual bool addSubItem(imRosterItem * entry, const QString& item = "");
		virtual bool addGroup(imRosterGroup * entry, imRosterGroup * g);
		virtual bool addGroup(imRosterGroup * entry, const QString& g = "");
		
		virtual imRosterItem * removeItem(const QString& id);
		virtual imRosterGroup * removeGroup(const QString& id);
		virtual imRosterItem * removeSubItem(const QString& id);
		
		virtual imRosterEntry * entry(const QString& id);
		virtual imRosterItem * item(const QString& id, bool allitems = false);
		virtual imRosterGroup * group(const QString& id);
		virtual imRosterEntry * topEntry(const QString& id);
		virtual imRosterItem * topItem(const QString& id);
		virtual imRosterGroup * topGroup(const QString& id);

	private:

		imSession * _session;

		QMap<QString, imRosterEntry *> _entries;
		QMap<QString, imRosterItem *> _items;
		QMap<QString, imRosterItem *> _allitems;
		QMap<QString, imRosterGroup *> _groups;
		QMap<QString, imRosterEntry *> _top_entries;
		QMap<QString, imRosterItem *> _top_items;
		QMap<QString, imRosterGroup *> _top_groups;
};



};

#endif
