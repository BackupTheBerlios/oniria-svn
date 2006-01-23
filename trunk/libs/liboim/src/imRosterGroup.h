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

#include <QVector>
#include <QMap>
#include "oim_dll.h"
#include "imStatus.h"
#include "imRosterEntry.h"
#include "imRosterItem.h"

namespace onirIM {

class imSession;

/*!\class imRosterGroup
 * \brief Roster group.
 */
class LIBOIM_API imRosterGroup : public imRosterEntry {

	Q_OBJECT

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
		
		inline QMap<QString, imRosterEntry *> * entries() { return &_entries; };
		inline QMap<QString, imRosterItem *> * items() { return &_items; };
		inline QMap<QString, imRosterGroup *> * groups() { return &_groups; };

		virtual bool addEntry(imRosterEntry * e);
		virtual bool addItem(imRosterItem * e);
		virtual bool addGroup(imRosterGroup * e);

		virtual imRosterItem * removeItem(const QString& id);
		virtual imRosterGroup * removeGroup(const QString& id);

		virtual imRosterEntry * entry(const QString& id);
		virtual imRosterItem * item(const QString& id);
		virtual imRosterGroup * group(const QString& id);

		virtual bool fixedOrder(QVector<QString>& olist);

	private:
	
		QMap<QString, imRosterEntry *> _entries;
		QMap<QString, imRosterItem *> _items;
		QMap<QString, imRosterGroup *> _groups;
};



};

#endif
