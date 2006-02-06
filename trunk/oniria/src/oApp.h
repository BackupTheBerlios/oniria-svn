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

#ifndef __GAPP_H
#define __GAPP_H

/*
class gFrame;
class oPluginManager;
class oEventManager;
class oSessionManager;
class oResourceManager;
class oStatusManager;
class logWindow;

namespace onir {
	class oOniria;
	class oConfig;
	class oTabs;
};
using onir::oOniria;
using onir::oConfig;
using onir::oTabs;

class gApp : public wxApp {

	public :
	
		virtual bool OnInit();
		virtual int OnExit();

		inline oOniria * Oniria() const { return _oniria; };
		inline oEventManager * EventManager() const { return _eventman; };
		inline oPluginManager * PluginManager() const { return _plugman; };
		inline oSessionManager * SessionManager() const { return _sessionman; };
		inline oResourceManager * ResourceManager() const { return _resourceman; };
		inline oConfig * Config() const { return _config; };
		inline oTabs * TabManager() const { return _tabs; };
		inline oStatusManager * StatusManager() const { return _statusman; }
		
		void CloseApp();
	private:

		gFrame * _main;
		
		oOniria * _oniria;
		oEventManager * _eventman;
		oPluginManager * _plugman;
		oSessionManager * _sessionman;
		oResourceManager * _resourceman;
		oConfig * _config;
		wxLogWindow * _logwnd;
		oTabs * _tabs;
		oStatusManager * _statusman;

		friend class oOniriaImpl;
};

DECLARE_APP(gApp);
*/

#endif /* __MAIN_H */
