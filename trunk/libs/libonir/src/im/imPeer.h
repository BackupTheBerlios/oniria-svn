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

#include "../dll.h"
#include "../oObject.h"

using onir::oObject;

namespace onirIM {

class imRosterItem;

/*!\class imPeer
 * \brief Peer in chat, dcc, etc.
 */
class LIBONIR_API imPeer : public oObject {

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
		
		/*!\fn inline void RosterItem(imRosterItem * ri)
		 * \brief Sets roster item associated with that peer.
		 * \param ri Roster item pointer.
		 */
		inline void RosterItem(imRosterItem * ri) { _ri = ri; };

		/*!\fn inline imRosterItem * RosterItem() const
		 * \brief Returns roster item associated with that peer.
		 * \return Roster item pointer.
		 */
		inline imRosterItem * RosterItem() const { return _ri; };
	
		/*!\fn virtual string Name() const
		 * \brief Returns peer name.
		 * \return Peer name.
		 */
		virtual string Name() const;

		/*!\fn virtual void Name(const string& n)
		 * \brief Sets peer name.
		 * \param n New name.
		 */
		virtual void Name(const string& n);

	private:
	
		imRosterItem * _ri;
		string _name;

		DECLARE_OOBJECT;
};



};

#endif
