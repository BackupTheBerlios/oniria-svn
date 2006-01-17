/* $id$ */
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

#ifndef _O_TAB_MANAGER
#define _O_TAB_MANAGER

#include <onir/oTabs.h>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;
using onir::oTabs;

class wxWindow;
class wxNotebook;
class wxWindow;
class gApp;
class gFrame;
class _TabHolder;
class gTabFrame;

class oTabManager : public oTabs
{
	public:
	
		typedef struct {
			_TabHolder * tab;
			wxWindow * owner;
			wxPanel * page;
			string name;
			string group;
			string ident;
			window_state state;
		} _if_page;

	
		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn oTabManager(gApp * app, gFrame frame)
		 * \brief Constructor
		 * \param app gApp pointer
		 * \param frame gFrame pointer
		 */
		oTabManager(gApp * app, gFrame * frame);

		/*!\fn virtual ~oTabManager()
		 * \brief Destructor
		 */
		~oTabManager();
		//@}


		bool RegisterPage(const string & ident, const string & name, wxPanel *page, const string &group = "default");
		wxWindow * RegisterPage(const string & ident, const string & name, const string &group = "default");
		wxWindow * PageAt(const string & ident, const string &group = "default");
		void RemovePage(const string & ident, const string &group = "default");
		void RegisterGroup(const string & name, tab_style style, window_state hidestate = tws_hidden);
		void ShowHiddenPage(const string & ident, const string &group = "default");
		void HiddenPages(vector< pair< string, string> > & v);
		wxWindow * ParentWindow();
	private:
		typedef struct {
			tab_style style;
			_TabHolder * singleWindowTab;
			gTabFrame * singleWindow;
			window_state hidestate;
		}_if_group;		

		wxPanel * CreateFramePage(const string & group, const string & ident, const string & name, bool active, wxPanel * page = NULL);
		_TabHolder * CreateTabs(wxWindow * parent);
		wxPanel * CreatePage( _TabHolder * p,const string & ident, const string & name, bool active,wxPanel * page = NULL);
		wxPanel * CreateSingleWindowPage(const string & groupname, const string & ident, const string & name, _if_group &group, bool active,wxPanel * page = NULL);
		wxPanel * CreateMutiWindowPage(const string & group, const string & ident, const string & name, bool active,wxPanel * page = NULL);
		void ShowHiddenPageInt(const string &globalident);
		map<string, _if_page> _pages;
		gApp * _app;
		gFrame * _frame;
		_TabHolder * _frameTab;
		map<string, _if_group> _groups;
		wxPanel * _mostParentWindow;
		
		friend class _TabHolder;
};

 #endif /* _O_TAB_MANAGER */
