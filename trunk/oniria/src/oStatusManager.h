/* $Id: oStatusManager.h 571 2005-09-14 09:28:57Z morg $ */
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
 
#ifndef __O_STATUS_MANAGER_H__
#define __O_STATUS_MANAGER_H__

#include <deque>
#include <list>
#include <string>
#include <onir/im/imStatus.h>
class gApp;
 
 namespace onirXML{
	class xmlElement;
	class xmlAttribute;
};

using std::deque;
using std::pair;
using std::list;
using std::string;

using onirXML::xmlElement;
using onirXML::xmlAttribute;
using onirIM::imStatus;
 
class oStatusManager{
public:
	oStatusManager(gApp *app);
	~oStatusManager();
	void Status(imStatus::status status, const string &desc, bool def = false);
	void Status(int status, const string &desc, bool def = false);
	void Status(imStatus::status status, bool def = false);
	void Status(int status, bool def = false);	
	void Status(const string &desc, bool def = false);
	
	void RegisterEventTarget(wxWindow * p, bool sent_initial = true);
	void AddStatus(const string & status, bool def = false);
	inline deque<pair<string, string> > &Statuses(){ return _lastStatus; };
	imStatus Default();
	void Default(const string & str) { _defaultStatusDescription = str; } ;
	void Default(int status) { _defaultStatus = status; };
	void Count(int c);
	int Count() {return _count; }
private:
	void LoadStatus();
	void SaveStatus();
	void SendStatusChange(imStatus::status status, const string &desc);
	int _count;
	list<wxWindow *> _eventTarget;
	string _defaultStatusDescription;
	int _defaultStatus;
	deque<pair<string, string> > _lastStatus;
	gApp * _app;
};

DECLARE_LOCAL_EVENT_TYPE(wxEVT_STATUS_CHANGE, -1)

#endif /* __O_STATUS_MANAGER_H__ */

