/* $Id: guiPopupWindow.h 594 2005-09-22 21:31:42Z morg $ */
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

#ifndef __GUI_POPUP_WINDOW__
#define __GUI_POPUP_WINDOW__

#include "../dll.h"

#include <string>

namespace onirGUI{

using std::string;

/*!\class guiPopupWindowBase
 *\brief base class to all popup windows
 *\sa guiPopupListBoxWindow
 */
class LIBONIR_API guiPopupWindowBase : public wxDialog{
	public:
	
		/*!\name Contructors and destructor
		 */
		//@{
		/*!\fn guiPopupWindowBase()
		 * \brief Constructor
		 */
		guiPopupWindowBase();
		//@}

	
		/*!\enum guiPopupStyle
		 * \brief show style
		 */
		enum guiPopupStyle
		{  
			cpsNORMAL,//!< show popup in normal style
			cpsVEXPAND //!< popup will be expand in vertical size
		};
		
		/*!\fn virtual void AutoPosition(const wxRect & rect)
		 * \brief Moving popup 
		 * \param rect rectangle which is possibly curtained
		 *
		 * Places window inside given rectangle
		 * so that window doesn't go out beyond the screen
		 */
		virtual void AutoPosition(const wxRect & rect);
		
		/*!\fn virtual bool Show(bool show = true)
		 * \brief show or hide window
		 * \param show if true popup will be shown, else popup will be hide
		 */
		virtual bool Show(bool show = true);	
	private:
		bool Expand(bool in);
		guiPopupStyle _style;
};

/*! \class guiPopupListBoxWindow
 * \brief popup with list
 */
 class LIBONIR_API guiPopupListBoxWindow : public guiPopupWindowBase
{
	public:
		/*!\name Contructors and destructor
		 */
		//@{
		/*!\fn guiPopupListBoxWindow()
		 * \brief Constructor
		 * \param parent pointer to parent window
		 */
		guiPopupListBoxWindow(wxWindow * parent);
		//@}
		
		/*!\fn void AddItem(const string & str, string * data = NULL)
		 * \brief add item to list
		 * \param str display string
		 * \param data user string will be inserted to item
		 * \sa Selection
		 */
		void AddItem(const string & str, string * data = NULL);
		
		/*!\fn void Clear()
		 * \brief Clear list
		 */
		void Clear();
		
		/*!\fn void MoveSelDown()
		 * \param move selection down 
		 * \sa MoveSelUp
		 */
		void MoveSelDown();
		
		/*!\fn void MoveSelUp()
		 * \param move selection up 
		 * \sa MoveSelDown
		 */
		void MoveSelUp();
		
		/*!\fn string Selection()
		 * \brief return data string from selected item
		 * \return data string or "" if data is NULL
		 * \sa AddItem
		 */
		string Selection();
    protected:
        void OnSelect(wxCommandEvent &event);
    DECLARE_EVENT_TABLE()	
};

DECLARE_EXPORTED_EVENT_TYPE(LIBONIR_API, wxEVT_POPUP_LIST_CLICK, 0x01)	


}

#endif /* __GUI_POPUP_WINDOW__ */
