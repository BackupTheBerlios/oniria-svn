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
#ifndef __IMROSTERENTRY_H
#define __IMROSTERENTRY_H

#include <QMap>
#include <QObject>
#include "oim_dll.h"
#include "imStatus.h"

namespace onirIM {

class imSession;
class imRosterGroup;

/*!\class imRosterEntry
 * \brief Roster entry.
 */
class LIBOIM_API imRosterEntry : public QObject {

	Q_OBJECT

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
		


		/*!\fn inline imSession * session() const
		 * \brief Returns pointer to session object.
		 * \return Pointer to session object to which this roster entry belongs.
		 */
		inline imSession * session() const { return _session; };

		/*!\fn virtual QString name() const
		 * \brief Returns roster entry name.
		 * \return Roster entry name.
		 */
		virtual QString name() const;

		/*!\fn virtual void name(const QString& n)
		 * \brief Sets roster entry name.
		 * \param n New name.
		 */
		virtual void name(const QString& n);

		/*!\fn virtual QString id() const
		 * \brief Returns roster entry id.
		 * \return Roster item id.
		 */
		virtual QString id() const;

		/*!\fn virtual void id(const QString& n)
		 * \brief Sets roster item id.
		 * \param n New id.
		 */
		virtual void id(const QString& n);

		/*!\fn inline const QString& iconSet() const
		 * \brief Returns roster iconset name.
		 * \return Roster iconset.
		 */
		inline const QString& iconSet() const { return _iconset; };

		/*!\fn inline void iconSet(const QString& n)
		 * \brief Sets roster icon set name.
		 * \param n New iconset.
		 */
		inline void iconSet(const QString& n) { _iconset = n; };
		
		inline void skinRoot(const QString& s) { _skin = s; };
		inline const QString& skinRoot() const { return _skin; };

		virtual void addToGroup(imRosterGroup * g);
		virtual void removeFromGroup(const QString& id);
		inline QMap<QString, imRosterGroup *> * inGroups() { return &_in_groups; };

	private:

		imSession * _session;
		QString _name;
		QString _id;
		QString _iconset;
		QString _skin;
		QMap<QString, imRosterGroup *> _in_groups;
};



};

#endif
