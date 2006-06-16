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
#ifndef __OSESSIONMANAGER_H
#define __OSESSIONMANAGER_H

#include <oim/imProtocol.h>
#include <oim/imSession.h>
#include <oim/imStatus.h>
#include <onir/oEventTarget.h>

using onirIM::imProtocol;
using onirIM::imSession;
using onirIM::imStatus;
using onir::oEventTarget;
using onir::oEvent;

class oApplication;
//class gRoster;

/*!\class oSessionManager
 */
class oSessionManager : public oEventTarget {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn oSessionManager(oApplication * app)
		 * \brief Constructor
		 * \param app oApplication pointer
		 */
		oSessionManager(oApplication * app);

		/*!\fn virtual ~oSessionManager()
		 * \brief Destructor
		 */
		virtual ~oSessionManager();
		//@}



		/*!\fn bool registerProtocol(imProtocol * proto)
		 * \brief Registers new protocol.
		 * \param proto Pointer to oniirIM::imProtocol object
		 * \return true if ok
		 * \sa onir::oOniria::RegisterProtocol(), onirIM::imProtocol
		 */
		bool registerProtocol(imProtocol * proto);

		/*!\fn imProtocol * findProtocol(const QString& id)
		 * \brief Finds protocol object for given id.
		 * \param id Protocol id
		 * \return Pointer to onirIM::imProtocol, or NULL if not found.
		 */
		imProtocol * findProtocol(const QString& id);

		/*\fn int loadSessions()
		 * \brief Loads saved sessions from config file.
		 * \return Number of loaded sessions.
		 */
		int loadSessions();

		/*!\fn int connectSessions(bool all = false)
		 * \brief Connects sessions.
		 * \param all If true, all sessions are connected, not only these with autoconnect flag.
		 * \return Number of connected sessions.
		 */
		int connectSessions(bool all = false);

		/*!\fn void Poll()
		 * \brief Makes sessions alive. ;)
		 */
		void poll();
		
		/*!\fn void processMessageQueue(imSession * s)
		 * \brief Process session message queue.
		 * \param s Session.
		 *
		 * Flushes input message queue and displays pending messages to user.
		 */
		void processMessageQueue(imSession * s);
		
		bool startThread(const QString& session_id, const QString& roster_id);

		/*!\fn void status(const imStatus& st, bool set = true)
		 * \brief Sets status.
		 * \param status Status.
		 * \param set True, if status change should be sent to IM servers.
		 */
		void status(const imStatus& st, bool set = true);

		/*!\fn inline const imStatus& Status() const
		 * \brief Returns current status.
		 * \return Current status.
		 */
		inline const imStatus& status() const { return _status; };

		/*!\fn void RegisterTabGroups()
		 * \brief Registers tab groups for rosters, chats, etc.
		 */
		void registerTabGroups();

		/*!\fn void RegisterEventHandlers()
		 * \brief Registers session event handlers. Mainly from oniria:im:session namespace.
		 */
		void registerEventHandlers();

		/*!\fn virtual bool processEvent(oEvent * event)
		 * \brief Handles event.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		virtual bool processEvent(oEvent * event);

	protected:

		//wxWindow * CreateRosterWindow(imSession * s);

		/*!\name Event handlers.
		 * @{
		 */

		/*!\fn imSession * eventSession(oEvent * event)
		 * \brief Returns session which generated given event.
		 * \param event Event.
		 * \return Session pointer.
		 */
		imSession * eventSession(oEvent * event);

		/*!\fn bool sessionConnected(oEvent * event)
		 * \brief Called when session is successfully connected to server.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool sessionConnected(oEvent * event);

		/*!\fn bool RosterUpdated(oEvent * event)
		 * \brief Called when roster is changed.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool rosterUpdated(oEvent * event);

		/*!\fn bool RosterPresence(oEvent * event)
		 * \brief Called when roster item presence changed.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool rosterPresence(oEvent * event);

		/*!\fn bool RosterNewItem(oEvent * event)
		 * \brief Called when new roster item is added.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool rosterNewItem(oEvent * event);

		/*!\fn bool ThreadUICreate(oEvent * event)
		 * \brief Called when UI for thread need to be created..
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool threadUICreate(oEvent * event);

		/* @} */

	private:
		oApplication * _app;
		QMap<QString, imProtocol *> _protocols;
		QMap<QString, imSession *> _sessions;
		QMap<QString, imSession *> _active_sessions;
		//QMap<QString, gRoster *> _rosters;

		imStatus _status;
};

#endif
