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
#ifndef __IMSESSION_H
#define __IMSESSION_H

#include <QObject>
#include <QString>
#include <oxml/xmlElement.h>
#include "oim_dll.h"
#include "imStatus.h"

using onirXML::xmlElement;

namespace onirIM {

class imProtocol;
class imRoster;
class imMessageQueue;
class imMessage;

/*!\class imSession
 * \brief Base class for IM sessions.
 */
class LIBOIM_API imSession : public QObject {

	Q_OBJECT

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imSession(imProtocol * proto)
		 * \brief Constructor
		 * \param proto Pointer to imProtocol object
		 */
		imSession(imProtocol * proto);
		/* @} */
		


		/*!\name Various methods.
		 * @{
		 */

		/*!\fn inline imProtocol * protocol() const
		 * \brief Returns pointer to protocol object.
		 * \return Pointer to protocol object associated with session.
		 */
		inline imProtocol * protocol() const { return _proto; };

		/*!\fn virtual QString sessionId() const
		 * \brief Returns session id.
		 * \return Session id.
		 *
		 * Default implementation returns id combined from protocol id
		 * and session name.
		 */
		virtual QString sessionId() const;

		/*!\fn inline oOniria * oniria() const
		 * \brief Returns pointer to Oniria interface.
		 * \return Pointer to Oniria interface.
		 */
		//inline oOniria * oniria() const { return _oniria; };

		/*!\fn inline const QString& name() const
		 * \brief Returns name of the session.
		 * \return Session name
		 */
		inline const QString& name() const { return _sesname; };

		/*!\fn inline void name(const QString& n)
		 * \brief Sets session name/
		 * \param n New name
		 */
		inline void name(const QString& n) { _sesname = n; };

		/*!\fn inline bool autoConnect() const
		 * \brief Returns true if autoconnect for this session is enabled.
		 * \return true if auto connect at program startup.
		 */
		inline bool autoConnect() const { return _autoconnect; };

		/*!\fn inline void autoConnect(bool a)
		 * \brief Sets autoconnect flag.
		 * \param a true if session should be autoconnected at 
		 * program startup.
		 */
		inline void autoConnect(bool a) { _autoconnect = a; };
		/* @} */



		/*!\name Status operations.
		 * @{
		 */

		virtual bool syncRoster(bool send) = 0;
		
		virtual imRoster * roster() = 0;

		/* @} */


		/*!\name Status operations.
		 * @{
		 */

		/*!\fn inline const imStatus& status() const
		 * \brief Returns current status.
		 * \return Status.
		 * \sa imStatus
		 */
		inline const imStatus& status() const { return _status; };

		/*!\fn bool status(const imStatus& st, bool set = true)
		 * \brief Sets status.
		 * \param st Status to set.
		 * \param set If true, SetStatus() will be called, which means
		 * that status will be sent to server.
		 * \return true if ok.
		 * \sa setStatus(), imStatus
		 */
		bool status(const imStatus& st, bool set = true);

		/*!\fn virtual bool setStatus() = 0
		 * \brief Override this method to implement setting status on the IM server.
		 * \return true if ok.
		 * \sa status(), imStatus
		 */
		virtual bool setStatus() = 0;
		/* @} */


		
		/*!\name Storing and loading.
		 * @{
		 */

		/*!\fn virtual bool load(xmlElement * cnode)
		 * \brief Loads session from config node.
		 * \param cnode XML config node
		 * \return true if ok, false otherwise.
		 */
		virtual bool load(xmlElement *cnode);
		/* @} */


		
		/*!\fn virtual bool prepare()
		 * \brief Initializes internal state of session. Creates message queue, etc.
		 * \return true if ok
		 */
		virtual bool prepare();

		/*!\fn virtual bool connect(bool ac = false) = 0
		 * \brief Connects session.
		 * \param ac true if this is autoconnection on program startup.
		 * \return true if ok
		 */
		virtual bool connect(bool ac = false) = 0;

		/*!\fn virtual bool poll() = 0
		 * \brief Main session routine.
		 * \return false if session should be removed from polling queue.
		 */
		virtual bool poll() = 0;
		
		
		
		/*!\name Message queue
		 * @{
		 */

		/*!\fn virtual imMessageQueue * createMessageQueue()
		 * \brief Creates message queue.
		 * \return Pointer to newly created message queue.
		 *
		 * Override this method to implement your own message queue
		 * creation.
		 */
		virtual imMessageQueue * createMessageQueue();
		
		/*!\fn inline imMessageQueue * messageQueue() const
		 * \brief Returns message queue pointer.
		 * \return Message queue pointer.
		 */
		inline imMessageQueue * messageQueue() const { return _msg_queue; };

		/*!\fn virtual bool sendMessage(imMessage * msg) = 0
		 * \brief Sends message to server.
		 * \param msg Message to be sent.
		 * \return true if ok.
		 */
		virtual bool sendMessage(imMessage * msg) = 0;
		
		/* @} */

	protected:

		/*!\fn inline xmlElemrnt configNode() const
		 * \brief Returns session XML configuration node.
		 * \return XML config node
		 */
		inline xmlElement * configNode() const { return _cnode; };

	private:

		imProtocol * _proto;
		QString _sesname;
		xmlElement *_cnode;
		bool _autoconnect;
		imMessageQueue * _msg_queue;
		bool _prepared;		// true if Prepare() was called.

		imStatus _status;
};



};

#endif
