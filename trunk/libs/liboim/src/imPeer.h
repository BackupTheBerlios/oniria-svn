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
#ifndef __IMPEER_H
#define __IMPEER_H

#include <QObject>
#include <QString>
#include "oim_dll.h"

namespace onirIM {

class imRosterItem;

/*!\class imPeer
 * \brief Peer in chat, dcc, etc.
 */
class LIBOIM_API imPeer : public QObject {

	Q_OBJECT

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imPeer()
		 * \brief Constructor
		 */
		imPeer();

		/*!\fn virtual ~imPeer()
		 * \brief Destructor.
		 */
		virtual ~imPeer();
		/* @} */
		
		/*!\fn inline void rosterItem(imRosterItem * ri)
		 * \brief Sets roster item associated with that peer.
		 * \param ri Roster item pointer.
		 */
		inline void rosterItem(imRosterItem * ri) { _ri = ri; };

		/*!\fn inline imRosterItem * rosterItem() const
		 * \brief Returns roster item associated with that peer.
		 * \return Roster item pointer.
		 */
		inline imRosterItem * rosterItem() const { return _ri; };
	
		/*!\fn virtual QString name() const
		 * \brief Returns peer name.
		 * \return Peer name.
		 */
		virtual QString name() const;

		/*!\fn virtual void name(const QString& n)
		 * \brief Sets peer name.
		 * \param n New name.
		 */
		virtual void name(const QString& n);

	private:
	
		imRosterItem * _ri;
		QString _name;
};



};

#endif
