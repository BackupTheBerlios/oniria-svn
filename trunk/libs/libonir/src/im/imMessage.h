/* $Id: imMessage.h 614 2005-12-29 16:44:50Z choman $ */
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
#ifndef __IMMESSAGE_H
#define __IMMESSAGE_H

#include <list>
#include "../dll.h"
#include "../oObject.h"

using std::list;
using onir::oObject;

namespace onirIM {

class imMessageThread;
class imPeer;

/*!\class imMessage
 * \brief Message.
 */
class LIBONIR_API imMessage : public oObject {

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imMessage()
		 * \brief Constructor
		 */
		imMessage();

		/*!\fn virtual ~imMessage()
		 * \brief Destructor.
		 */
		virtual ~imMessage();
		/* @} */

		/*!\fn inline void Thread(imMessageThread * th)
		 * \brief Sets message thread pointer.
		 * \param th Message thread pointer.
		 */
		inline void Thread(imMessageThread * th) { _thread = th; };

		/*!\fn inline imMessageThread * Thread() const
		 * \brief Returns pointer to message thread.
		 * \return Message thread pointer.
		 */
		inline imMessageThread * Thread() const { return _thread; };

		/*!\fn inline void Body(const string& t)
		 * \brief Sets message body.
		 * \param th Message body.
		 */
		inline void Body(const string& t) { _body = t; };

		/*!\fn inline const string& Body() const
		 * \brief Returns message body.
		 * \return Message body.
		 */
		inline const string& Body() const { return _body; };

		/*!\fn inline void Subject(const string& t)
		 * \brief Sets message subject.
		 * \param th Message subject.
		 */
		inline void Subject(const string& t) { _subject = t; };

		/*!\fn inline const string& Body() const
		 * \brief Returns message body.
		 * \return Message body.
		 */
		inline const string& Subject() const { return _subject; };

		/*!\fn inline void Sent(time_t ts)
		 * \brief Sets time when message was sent.
		 * \param ts Timestamp.
		 */
		inline void Sent(time_t ts) { _ts_sent = ts; };

		/*!\fn inline time_t Sent() const
		 * \brief Returns time when message was sent.
		 * \param ts Timestamp.
		 */
		inline time_t Sent() const { return _ts_sent; };

		/*!\fn inline void Received(time_t ts)
		 * \brief Sets time when message was received.
		 * \return Timestamp.
		 */
		inline void Received(time_t ts) { _ts_recv = ts; };

		/*!\fn inline time_t Received() const
		 * \brief Returns time when message was received.
		 * \return Timestamp.
		 */
		inline time_t Received() const { return _ts_recv; };

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

	private:

		imMessageThread * _thread;
		string _body;
		string _subject;
		time_t _ts_sent;
		time_t _ts_recv;
		list<imPeer *> _peers;
		imPeer * _local_peer;

		DECLARE_OOBJECT;
};



};

#endif
