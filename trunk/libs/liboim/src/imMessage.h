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
#ifndef __IMMESSAGE_H
#define __IMMESSAGE_H

#include <QList>
#include <QObject>
#include "oim_dll.h"

namespace onirIM {

class imMessageThread;
class imPeer;

/*!\class imMessage
 * \brief Message.
 */
class LIBOIM_API imMessage : public QObject {

	Q_OBJECT

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

		/*!\fn inline void thread(imMessageThread * th)
		 * \brief Sets message thread pointer.
		 * \param th Message thread pointer.
		 */
		inline void thread(imMessageThread * th) { _thread = th; };

		/*!\fn inline imMessageThread * thread() const
		 * \brief Returns pointer to message thread.
		 * \return Message thread pointer.
		 */
		inline imMessageThread * thread() const { return _thread; };

		/*!\fn inline void body(const QString& t)
		 * \brief Sets message body.
		 * \param th Message body.
		 */
		inline void body(const QString& t) { _body = t; };

		/*!\fn inline const QString& body() const
		 * \brief Returns message body.
		 * \return Message body.
		 */
		inline const QString& body() const { return _body; };

		/*!\fn inline void subject(const QString& t)
		 * \brief Sets message subject.
		 * \param th Message subject.
		 */
		inline void subject(const QString& t) { _subject = t; };

		/*!\fn inline const QString& subject() const
		 * \brief Returns message subject.
		 * \return Message subject.
		 */
		inline const QString& subject() const { return _subject; };

		/*!\fn inline void sent(time_t ts)
		 * \brief Sets time when message was sent.
		 * \param ts Timestamp.
		 */
		inline void sent(time_t ts) { _ts_sent = ts; };

		/*!\fn inline time_t sent() const
		 * \brief Returns time when message was sent.
		 * \param ts Timestamp.
		 */
		inline time_t sent() const { return _ts_sent; };

		/*!\fn inline void received(time_t ts)
		 * \brief Sets time when message was received.
		 * \return Timestamp.
		 */
		inline void received(time_t ts) { _ts_recv = ts; };

		/*!\fn inline time_t received() const
		 * \brief Returns time when message was received.
		 * \return Timestamp.
		 */
		inline time_t received() const { return _ts_recv; };

		/*!\fn inline void localPeer(imPeer * p)
		 * \brief Sets local peer.
		 * \param p Local peer.
		 */
		inline void localPeer(imPeer * p) { _local_peer = p; };

		/*!\fn inline imPeer * localPeer() const
		 * \brief Returns local peer.
		 * \return Local peer.
		 */
		inline imPeer * localPeer() const { return _local_peer; };

		/*!\fn void addPeer(imPeer * p)
		 * \brief Adds peer to peer list.
		 * \param p Peer.
		 */
		void addPeer(imPeer * p);

		/*!\fn inline QList<imPeer *> * peers()
		 * \brief Returns peer list.
		 * \return Peer list.
		 */
		inline QList<imPeer *> * peers() { return &_peers; };

	private:

		imMessageThread * _thread;
		QString _body;
		QString _subject;
		time_t _ts_sent;
		time_t _ts_recv;
		QList<imPeer *> _peers;
		imPeer * _local_peer;
};



};

#endif
