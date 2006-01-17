/* $Id: xh_guibtn.h 611 2005-12-01 21:39:21Z morg $ */
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
 
 #ifndef __XH__GUIBTN_H__
 #define __XH__GUIBTN_H__
 
 #include "../../dll.h"
 
 namespace onirXRC_handlers{
 	
 //class wxXmlNode;

/*!\class guiXmlButtonHandler
 *\brief Class to handle guiButton from xrc resources
 */
class guiXmlButtonHandler : public wxXmlResourceHandler{
public:
    guiXmlButtonHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
    DECLARE_DYNAMIC_CLASS(guiXmlButtonHandler);
};

};
 
 
#endif /* __XH__GUIBTN_H__ */

