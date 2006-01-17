/* $Id: oSessionManager.h 584 2005-09-21 13:19:26Z choman $ */
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

#include <map>
#include <string>
#include <onir/im/imProtocol.h>
#include <onir/im/imSession.h>
#include <onir/im/imStatus.h>
#include <onir/oEventTarget.h>

using std::map;
using std::string;
using onirIM::imProtocol;
using onirIM::imSession;
using onirIM::imStatus;
using onir::oEventTarget;
using onir::oEvent;

class gApp;
class gRoster;

/*!\class oSessionManager
 */
class oSessionManager : public oEventTarget {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn oSessionManager(gApp * app)
		 * \brief Constructor
		 * \param app gApp pointer
		 */
		oSessionManager(gApp * app);

		/*!\fn virtual ~oSessionManager()
		 * \brief Destructor
		 */
		virtual ~oSessionManager();
		//@}



		/*!\fn bool RegisterProtocol(imProtocol * proto)
		 * \brief Registers new protocol.
		 * \param proto Pointer to oniirIM::imProtocol object
		 * \return true if ok
		 * \sa onir::oOniria::RegisterProtocol(), onirIM::imProtocol
		 */
		bool RegisterProtocol(imProtocol * proto);

		/*!\fn imProtocol * FindProtocol(const string& id)
		 * \brief Finds protocol object for given id.
		 * \param id Protocol id
		 * \return Pointer to onirIM::imProtocol, or NULL if not found.
		 */
		imProtocol * FindProtocol(const string& id);

		/*\fn int LoadSessions()
		 * \brief Loads saved sessions from config file.
		 * \return Number of loaded sessions.
		 */
		int LoadSessions();

		/*!\fn int ConnectSessions(bool all = false)
		 * \brief Connects sessions.
		 * \param all If true, all sessions are connected, not only these with autoconnect flag.
		 * \return Number of connected sessions.
		 */
		int ConnectSessions(bool all = false);

		/*!\fn void Poll()
		 * \brief Makes sessions alive. ;)
		 */
		void Poll();
		
		/*!\fn void ProcessMessageQueue(imSession * s)
		 * \brief Process session message queue.
		 * \param s Session.
		 *
		 * Flushes input message queue and displays pending messages to user.
		 */
		void ProcessMessageQueue(imSession * s);
		
		bool StartThread(const string& session_id, const string& roster_id);

		/*!\fn void Status(const imStatus& status, bool set = true)
		 * \brief Sets status.
		 * \param status Status.
		 * \param set True, if status change should be sent to IM servers.
		 */
		void Status(const imStatus& status, bool set = true);

		/*!\fn inline const imStatus& Status() const
		 * \brief Returns current status.
		 * \return Current status.
		 */
		inline const imStatus& Status() const { return _status; };

		/*!\fn void RegisterTabGroups()
		 * \brief Registers tab groups for rosters, chats, etc.
		 */
		void RegisterTabGroups();

		/*!\fn void RegisterEventHandlers()
		 * \brief Registers session event handlers. Mainly from oniria:im:session namespace.
		 */
		void RegisterEventHandlers();

		/*!\fn virtual bool ProcessEvent(oEvent * event)
		 * \brief Handles event.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		virtual bool ProcessEvent(oEvent * event);

	protected:

		wxWindow * CreateRosterWindow(imSession * s);

		/*!\name Event handlers.
		 * @{
		 */

		/*!\fn imSession * EventSession(oEvent * event)
		 * \brief Returns session which generated given event.
		 * \param event Event.
		 * \return Session pointer.
		 */
		imSession * EventSession(oEvent * event);

		/*!\fn bool SessionConnected(oEvent * event)
		 * \brief Called when session is successfully connected to server.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool SessionConnected(oEvent * event);

		/*!\fn bool RosterUpdated(oEvent * event)
		 * \brief Called when roster is changed.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool RosterUpdated(oEvent * event);

		/*!\fn bool RosterPresence(oEvent * event)
		 * \brief Called when roster item presence changed.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool RosterPresence(oEvent * event);

		/*!\fn bool RosterNewItem(oEvent * event)
		 * \brief Called when new roster item is added.
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool RosterNewItem(oEvent * event);

		/*!\fn bool ThreadUICreate(oEvent * event)
		 * \brief Called when UI for thread need to be created..
		 * \param event Event.
		 * \return true if event manager should call next handler in chain.
		 */
		bool ThreadUICreate(oEvent * event);

		/* @} */

	private:
		gApp * _app;
		map<string, imProtocol *> _protocols;
		map<string, imSession *> _sessions;
		map<string, imSession *> _active_sessions;
		map<string, gRoster *> _rosters;

		imStatus _status;

		DECLARE_OOBJECT;
};

#endif
