/* $Id: oTabs.h 585 2005-09-21 13:20:18Z morg $ */
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

#ifndef _O_TABS
#define _O_TABS

#include "dll.h"

#include <map>
#include <string>
#include "oObject.h"

using namespace std;

namespace onir {

class oOniria;

/*!\class oTabs
 * \brief Interface to manage tab pages.
 *
 * Tabs can be displayed in three ways, as defined in tab_style.
 * \sa tab_style
 */
class LIBONIR_API oTabs :public oObject
{
	public:

		/*!\enum tab_style
		 * \brief Modes in which new tabs should be displayed.
		 * \sa RegisterGroup()
		 */
		enum tab_style {
			ts_multi_window,	//!< each tab in its own window
			ts_single_window,	//!< all tabs in one window
			ts_main_window		//!< all tabs in main frame window
		};
		
		/*!\enum window_state
		 * \brief default window state when window is close
		 * \sa RegisterGroup()
		 */
		enum window_state{
			tws_shown,
			tws_hidden,
			tws_invisible
		};


		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn oTabs()
		 * \brief Constructor
		 */
		oTabs();

		//@}

		/*!\fn virtual wxWindow * RegisterPage(const string & ident, const string & name, const string &group = "default") = 0
		 * \brief Registesr new tab in group
		 * \param ident Tab id.
		 * \param name Tab name (displayed as title).
		 * \param group Group to which registered tab belongs.
		 * \sa RegisterGroup(), PageAt()
		 *
		 * Tab id must be unique in group. 
		 * Group must be registered by RegisterGroup() method.
		 */
		virtual wxWindow * RegisterPage(const string & ident, const string & name, const string &group = "default") = 0;

		/*!\overload virtual bool RegisterPage(const string & ident, const string & name, wxPanel *page, const string &group = "default") = 0
		 */
		virtual bool RegisterPage(const string & ident, const string & name, wxPanel *page, const string &group = "default") = 0;

		/*!\fn virtual wxWindow * PageAt(const string & ident, const string &group = "default") = 0
		 * \brief Returns tab with given tab id.
		 * \param ident Tab id.
		 * \param group Group id.
		 * \return Pointer to tab window.
		 */
		virtual wxWindow * PageAt(const string & ident, const string &group = "default") = 0;
		virtual void RemovePage(const string & ident, const string &group = "default") = 0;
		virtual void RegisterGroup(const string & name, tab_style style, window_state hidestate = tws_hidden) = 0;
		
		/*!\fn virtual wxWindow * ParentWindow() = 0
		 * \brief return parent to new created window
		 * \sa RegisterPage
		 *
		 * window returntd by this function must be used as parent window 
		 * new created tab only if tab will be registered by second version RegisterPage function		 
		 */
		virtual wxWindow * ParentWindow() = 0;
		DECLARE_OOBJECT;

};
}
#endif /* _O_TABS */

