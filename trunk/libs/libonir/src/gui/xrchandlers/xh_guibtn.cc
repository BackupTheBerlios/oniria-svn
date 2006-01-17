/* $Id: xh_guibtn.cc 614 2005-12-29 16:44:50Z choman $ */
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
 
#if defined(HAVE_CONFIG_H)
# include <config.h>
#endif

#include "xh_guibtn.h"
#include "../guiButton.h"

using onirGUI::guiButton; 
namespace onirXRC_handlers{


IMPLEMENT_DYNAMIC_CLASS(guiXmlButtonHandler, wxXmlResourceHandler)

guiXmlButtonHandler::guiXmlButtonHandler()
: wxXmlResourceHandler()
{
	
    /*
    XRC_ADD_STYLE(wxBU_LEFT);
    XRC_ADD_STYLE(wxBU_RIGHT);
    XRC_ADD_STYLE(wxBU_TOP);
    XRC_ADD_STYLE(wxBU_BOTTOM);
    XRC_ADD_STYLE(wxBU_EXACTFIT);
    */
    AddWindowStyles();
}

wxObject *guiXmlButtonHandler::DoCreateResource()
{
   XRC_MAKE_INSTANCE(button, guiButton)

   button->Create(m_parentAsWindow,
                    GetID(),
                    GetText(wxT("label")),
                    GetPosition(), 
                    GetSize(),
                    GetStyle(),
                    wxDefaultValidator,
                    GetName());
	
    /*if (GetBool(wxT("default"), 0))
        button->SetDefault();
*/
    SetupWindow(button);

    return button;
}

bool guiXmlButtonHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("guiButton"));
}

 	
};
