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


#ifndef __GADVSTATUS_HPP_
#define __GADVSTATUS_HPP_



class gApp;

class gAdvStatus : public wxPanel
{

public:
        gAdvStatus(gApp * app, wxWindow * parent);
        virtual ~gAdvStatus();
protected:
        void _setStatusClick(wxCommandEvent& event);
        void _cancelClick(wxCommandEvent& event);
        void _defaultClick(wxCommandEvent& event);
        void _defaultDeleteClick(wxCommandEvent& event);
        void OnHistory(wxCommandEvent& event);
        void OnStatusChange(wxCommandEvent& event);
private:
		void ActStatus();
        gApp * _app;
        wxComboBox * _status;
        wxComboBox * _history;
        wxTextCtrl * _statusText;
        wxTextCtrl * _defaultStatus;        
        DECLARE_EVENT_TABLE();
        
        friend class gBottomBar;
};

#endif




