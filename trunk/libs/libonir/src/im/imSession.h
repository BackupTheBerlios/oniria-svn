/* $Id: imSession.h 608 2005-10-07 09:57:23Z choman $ */
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

#include "../dll.h"
#include "../oObject.h"
#include "../oConfig.h"
#include "imStatus.h"

using onir::oObject;
namespace onir {
	class oOniria;
};

namespace onirXML{
	class xmlElement;
};

using onir::oOniria;
using onirXML::xmlElement;

namespace onirIM {

class imProtocol;
class imRoster;
class imMessageQueue;
class imMessage;

/*!\class imSession
 * \brief Base class for IM sessions.
 */
class LIBONIR_API imSession : public oObject {

	public:

		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn imSession(oOniria * o, imProtocol * proto)
		 * \brief Constructor
		 * \param o Pointer to Oniria interface
		 * \param proto Pointer to imProtocol object
		 */
		imSession(oOniria * o, imProtocol * proto);
		/* @} */
		


		/*!\name Various methods.
		 * @{
		 */

		/*!\fn inline imProtocol * Protocol() const
		 * \brief Returns pointer to protocol object.
		 * \return Pointer to protocol object associated with session.
		 */
		inline imProtocol * Protocol() const { return _proto; };

		/*!\fn virtual string SessionId() const
		 * \brief Returns session id.
		 * \return Session id.
		 *
		 * Default implementation returns id combined from protocol id
		 * and session name.
		 */
		virtual string SessionId() const;

		/*!\fn inline oOniria * Oniria() const
		 * \brief Returns pointer to Oniria interface.
		 * \return Pointer to Oniria interface.
		 */
		inline oOniria * Oniria() const { return _oniria; };

		/*!\fn inline const string& Name() const
		 * \brief Returns name of the session.
		 * \return Session name
		 */
		inline const string& Name() const { return _sesname; };

		/*!\fn inline void Name(const string& n)
		 * \brief Sets session name/
		 * \param n New name
		 */
		inline void Name(const string& n) { _sesname = n; };

		/*!\fn inline bool AutoConnect() const
		 * \brief Returns true if autoconnect for this session is enabled.
		 * \return true if auto connect at program startup.
		 */
		inline bool AutoConnect() const { return _autoconnect; };

		/*!\fn inline void AutoConnect(bool a)
		 * \brief Sets autoconnect flag.
		 * \param a true if session should be autoconnected at 
		 * program startup.
		 */
		inline void AutoConnect(bool a) { _autoconnect = a; };
		/* @} */



		/*!\name Status operations.
		 * @{
		 */

		virtual bool SyncRoster(bool send) = 0;
		
		virtual imRoster * Roster() = 0;

		/* @} */


		/*!\name Status operations.
		 * @{
		 */

		/*!\fn inline const imStatus& Status() const
		 * \brief Returns current status.
		 * \return Status.
		 * \sa imStatus
		 */
		inline const imStatus& Status() const { return _status; };

		/*!\fn bool Status(const imStatus& st, bool set = true)
		 * \brief Sets status.
		 * \param st Status to set.
		 * \param set If true, SetStatus() will be called, which means
		 * that status will be sent to server.
		 * \return true if ok.
		 * \sa SetStatus(), imStatus
		 */
		bool Status(const imStatus& st, bool set = true);

		/*!\fn virtual bool SetStatus() = 0
		 * \brief Override this method to implement setting status on the IM server.
		 * \return true if ok.
		 * \sa Status(), imStatus
		 */
		virtual bool SetStatus() = 0;
		/* @} */


		
		/*!\name Storing and loading.
		 * @{
		 */

		/*!\fn virtual bool Load(xmlElement * cnode)
		 * \brief Loads session from config node.
		 * \param cnode XML config node
		 * \return true if ok, false otherwise.
		 */
		virtual bool Load(xmlElement *cnode);
		/* @} */


		
		/*!\fn virtual bool Prepare()
		 * \brief Initializes internal state of session. Creates message queue, etc.
		 * \return true if ok
		 */
		virtual bool Prepare();

		/*!\fn virtual bool Connect(bool ac = false) = 0
		 * \brief Connects session.
		 * \param ac true if this is autoconnection on program startup.
		 * \return true if ok
		 */
		virtual bool Connect(bool ac = false) = 0;

		/*!\fn virtual bool Poll() = 0
		 * \brief Main session routine.
		 * \return false if session should be removed from polling queue.
		 */
		virtual bool Poll() = 0;
		
		
		
		/*!\name Message queue
		 * @{
		 */

		/*!\fn virtual imMessageQueue * CreateMessageQueue()
		 * \brief Creates message queue.
		 * \return Pointer to newly created message queue.
		 *
		 * Override this method to implement your own message queue
		 * creation.
		 */
		virtual imMessageQueue * CreateMessageQueue();
		
		/*!\fn inline imMessageQueue * MessageQueue() const
		 * \brief Returns message queue pointer.
		 * \return Message queue pointer.
		 */
		inline imMessageQueue * MessageQueue() const { return _msg_queue; };

		/*!\fn virtual bool SendMessage(imMessage * msg) = 0
		 * \brief Sends message to server.
		 * \param msg Message to be sent.
		 * \return true if ok.
		 */
		virtual bool SendMessage(imMessage * msg) = 0;
		
		/* @} */

	protected:

		/*!\fn inline xNode ConfigNode() const
		 * \brief Returns session XML configuration node.
		 * \return XML config node
		 */
		inline xmlElement *ConfigNode() const { return _cnode; };

	private:

		oOniria * _oniria;
		imProtocol * _proto;
		string _sesname;
		xmlElement *_cnode;
		bool _autoconnect;
		imMessageQueue * _msg_queue;
		bool _prepared;		// true if Prepare() was called.

		imStatus _status;

		DECLARE_OOBJECT;
};



};

#endif
