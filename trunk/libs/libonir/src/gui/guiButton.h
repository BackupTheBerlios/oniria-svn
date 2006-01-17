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

#ifndef _GUIBUTTON_H
#define _GUIBUTTON_H

#include "../dll.h"

#if 0

namespace onirGUI {

/*!\class guiButton
 * \brief Button class
 */

class LIBONIR_API guiButton : public wxControl {
	public:
		/*!\name Contructors and destructor
		 */
		//@{
		/*!\fn guiButton()
		 * \brief Constructor
		 */
		 guiButton();
		 //@}


		bool Create(wxWindow *parent,
			wxWindowID id,
			const wxString & text,
			const wxPoint& pos,
			const wxSize& size,
			long style,
			const wxValidator& validator,
			const wxString & name);

		protected:
			void OnPaint(wxPaintEvent &event);
		DECLARE_EVENT_TABLE();
 		DECLARE_DYNAMIC_CLASS_NO_COPY(guiButton)

 };

 };


#endif

#endif
