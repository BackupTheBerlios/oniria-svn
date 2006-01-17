/* $Id: imMessageThread.h 608 2005-10-07 09:57:23Z choman $ */
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
#ifndef __IMMESSAGETHREAD_H
#define __IMMESSAGETHREAD_H

#include <list>
#include "../dll.h"
#include "../oObject.h"

using std::list;
using onir::oObject;

namespace onirIM {

class imSession;
class imMessage;
class imMessageThreadUI;
class imPeer;

/*!\class imMessageThread
 * \brief Conversation thread.
 */
class LIBONIR_API imMessageThread : public oObject {

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imMessageThread(imSession * s)
		 * \brief Constructor
		 * \param s Session.
		 */
		imMessageThread(imSession * s);

		/*!\fn virtual ~imMessageThread()
		 * \brief Destructor.
		 */
		virtual ~imMessageThread();
		/* @} */



		/*!\fn inline const string& Id() const
		 * \brief Returns thread id.
		 * \return Thread id.
		 */
		inline const string& Id() const { return _id; };

		/*!\fn inline void Id(const string& n)
		 * \brief Sets thread id.
		 * \param n New id.
		 */
		inline void Id(const string& n) { _id = n; };
		
		/*!\fn inline imSession * Session() const
		 * \brief Returns session pointer.
		 * \return Session pointer.
		 */
		inline imSession * Session() const { return _session; };

		
		
		/*!\name Message methods
		 * @{
		 */
		
		/*!\fn virtual imMessage * NextInMessage(bool peek = false)
		 * \brief Returns next message from thread input message queue.
		 * \param peek If true message will be left in queue. If false,
		 * message will be removed from queue.
		 * \return Message pointer.
		 * \sa NextOutMessage(), imMessage
		 */
		virtual imMessage * NextInMessage(bool peek = false);

		/*!\fn virtual imMessage * NextOutMessage(bool peek = false)
		 * \brief Returns next message from thread output message queue.
		 * \param peek If true message will be left in queue. If false,
		 * message will be removed from queue.
		 * \return Message pointer.
		 * \sa NextInMessage(), imMessage
		 */
		virtual imMessage * NextOutMessage(bool peek = false);
		
		/*!\fn virtual bool AddInMessage(imMessage * msg)
		 * \brief Adds new message at the end of input message queue.
		 * \param msg Message to be added.
		 * \return true if ok.
		 * \sa AddOutMessage()
		 */
		virtual bool AddInMessage(imMessage * msg);

		/*!\fn virtual bool AddOutMessage(imMessage * msg)
		 * \brief Adds new message at the end of output message queue.
		 * \param msg Message to be added.
		 * \return true if ok.
		 * \sa AddInMessage()
		 */
		virtual bool AddOutMessage(imMessage * msg);

		/* @} */



		/*!\fn inline void LocalPeer(imPeer * p)
		 * \brief Sets local peer.
		 * \param p Local peer.
		 */
		inline void LocalPeer(imPeer * p) { _local_peer = p; };

		/*!\fn inline imPeer * LocalPeer() const
		 * \brief Returns local peer.
		 * \return Local peer.
		 */
		inline imPeer * LocalPeer() const { return _local_peer; };

		/*!\fn void AddPeer(imPeer * p)
		 * \brief Adds peer to peer list.
		 * \param p Peer.
		 */
		void AddPeer(imPeer * p);

		/*!\fn inline list<imPeer *> * Peers()
		 * \brief Returns peer list.
		 * \return Peer list.
		 */
		inline list<imPeer *> * Peers() { return &_peers; };

		/*!\fn void UI(imMessageThreadUI * th)
		 * \brief Sets message thread UI pointer.
		 * \param th Message thread UI pointer.
		 */
		void UI(imMessageThreadUI * ui);

		/*!\fn inline imMessageThread * UI() const
		 * \brief Returns pointer to message thread UI.
		 * \return Message thread UI pointer.
		 */
		inline imMessageThreadUI * UI() const { return _ui; };
	private:
	
		imSession * _session;
		string _id;
		list<imMessage *> _in_messages;
		list<imMessage *> _out_messages;
		imMessageThreadUI * _ui;
		list<imPeer *> _peers;
		imPeer * _local_peer;

		DECLARE_OOBJECT;
};



};

#endif
