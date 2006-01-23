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
#ifndef __IMROSTERITEM_H
#define __IMROSTERITEM_H

#include <QVector>
#include <QMap>
#include "oim_dll.h"
#include "imStatus.h"
#include "imRosterEntry.h"

namespace onirIM {

class imSession;

/*!\class imRosterItem
 * \brief Roster entry.
 */
class LIBOIM_API imRosterItem : public imRosterEntry {

	Q_OBJECT

	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn imRosterItem(imSession * session, imRosterItem * parent = NULL)
		 * \brief Constructor
		 * \param session Pointer to session object.
		 * \param parent Pointer to parent item (for subitems only).
		 */
		imRosterItem(imSession * session, imRosterItem * parent = NULL);

		/*!\fn virtual ~imRosterItem()
		 * \brief Destructor.
		 */
		virtual ~imRosterItem();
		//@}
		
		inline const imStatus& status() const { return _status; };
		inline void status(const imStatus& astatus) { _status = astatus; };
		
		inline QMap<QString, imRosterItem *> * subItems() { return &_subitems; };
		virtual bool addSubItem(imRosterItem * e);
		virtual imRosterItem * removeSubItem(const QString& id);

		inline imRosterItem * parent() const { return _parent; };
		inline void parent(imRosterItem * parent) { _parent = parent; };
		
		virtual imRosterItem * subItem(const QString& id);

		virtual bool fixedOrder(QVector<QString>& olist);

	private:

		imStatus _status;
		QMap<QString, imRosterItem *> _subitems;
		imRosterItem * _parent;
};



};

#endif
