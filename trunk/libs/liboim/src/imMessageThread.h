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
#ifndef __IMMESSAGETHREAD_H
#define __IMMESSAGETHREAD_H

#include <QList>
#include <QObject>
#include <QString>
#include "oim_dll.h"

namespace onirIM {

class imSession;
class imMessage;
class imMessageThreadUI;
class imPeer;

/*!\class imMessageThread
 * \brief Conversation thread.
 */
class LIBOIM_API imMessageThread : public QObject {

	Q_OBJECT

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



		/*!\fn inline const QString& id() const
		 * \brief Returns thread id.
		 * \return Thread id.
		 */
		inline const QString& id() const { return _id; };

		/*!\fn inline void id(const QString& n)
		 * \brief Sets thread id.
		 * \param n New id.
		 */
		inline void id(const QString& n) { _id = n; };
		
		/*!\fn inline imSession * session() const
		 * \brief Returns session pointer.
		 * \return Session pointer.
		 */
		inline imSession * session() const { return _session; };

		
		
		/*!\name Message methods
		 * @{
		 */
		
		/*!\fn virtual imMessage * nextInMessage(bool peek = false)
		 * \brief Returns next message from thread input message queue.
		 * \param peek If true message will be left in queue. If false,
		 * message will be removed from queue.
		 * \return Message pointer.
		 * \sa nextOutMessage(), imMessage
		 */
		virtual imMessage * nextInMessage(bool peek = false);

		/*!\fn virtual imMessage * nextOutMessage(bool peek = false)
		 * \brief Returns next message from thread output message queue.
		 * \param peek If true message will be left in queue. If false,
		 * message will be removed from queue.
		 * \return Message pointer.
		 * \sa nextInMessage(), imMessage
		 */
		virtual imMessage * nextOutMessage(bool peek = false);
		
		/*!\fn virtual bool addInMessage(imMessage * msg)
		 * \brief Adds new message at the end of input message queue.
		 * \param msg Message to be added.
		 * \return true if ok.
		 * \sa addOutMessage()
		 */
		virtual bool addInMessage(imMessage * msg);

		/*!\fn virtual bool addOutMessage(imMessage * msg)
		 * \brief Adds new message at the end of output message queue.
		 * \param msg Message to be added.
		 * \return true if ok.
		 * \sa addInMessage()
		 */
		virtual bool addOutMessage(imMessage * msg);

		/* @} */



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

		/*!\fn void ui(imMessageThreadUI * th)
		 * \brief Sets message thread UI pointer.
		 * \param th Message thread UI pointer.
		 */
		void ui(imMessageThreadUI * ui);

		/*!\fn inline imMessageThread * ui() const
		 * \brief Returns pointer to message thread UI.
		 * \return Message thread UI pointer.
		 */
		inline imMessageThreadUI * ui() const { return _ui; };
	private:
	
		imSession * _session;
		QString _id;
		QList<imMessage *> _in_messages;
		QList<imMessage *> _out_messages;
		imMessageThreadUI * _ui;
		QList<imPeer *> _peers;
		imPeer * _local_peer;
};



};

#endif
