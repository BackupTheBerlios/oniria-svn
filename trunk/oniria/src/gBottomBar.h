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

#ifndef __G_BOTTOM_BAR_H
#define __G_BOTTOM_BAR_H

#include <map>
#include "gDockBarBase.h"
#include "guictrls/ctrlStatusText.h"

using std::map;

class gConfigure;
class gAdvStatus;
class gApp;

class gBottomBar : public gDockBarBase
{
public:
        gBottomBar(gApp * app, wxWindow * parent);
        ~gBottomBar();
        
protected:
        void Reorganize();
        void EventFunc(wxCommandEvent &event);
        void OnEnter(wxCommandEvent &event);
        void OnMenu(wxCommandEvent &event);
        void OnStatusChange(wxCommandEvent &event);
private:  
		void CreateAdvStatusDlg();
        wxMenu * BuildStatusMenu();        
        wxMenu * _statusMenu;
        wxMenu * _basicMenu;
        wxBoxSizer * _resizer;
        ctrlStatusText *_status;
        wxButton * _rightBtn;
        wxButton * _leftBtn;
        wxButton * _textRightBtn;
        gConfigure * _configure;
        gAdvStatus * _advstatus;
        gApp * _app;        
        map<int, string> _idToStr;
        int _ids[30];
        DECLARE_EVENT_TABLE()
};


#endif /* __G_BOTTOM_BAR_H */

