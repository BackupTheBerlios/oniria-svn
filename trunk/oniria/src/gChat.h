/* $Id: gChat.h 556 2005-09-08 11:41:27Z choman $ */
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
 
 #include <string>
 
 using std::string;
 
 class gApp;
 class uiChat;
 
 class gChat : public wxPanel {
 	public:
 		gChat(gApp * app, uiChat * ui, wxWindow * parent);
 		void AddText(const string &text);
	protected:
		void OnSentButtonClick(wxCommandEvent &event);
	private:
		gApp * _app;
		wxTextCtrl * _displayText;
		wxTextCtrl * _sendText;
		uiChat * _ui;
		
		DECLARE_EVENT_TABLE()
};
