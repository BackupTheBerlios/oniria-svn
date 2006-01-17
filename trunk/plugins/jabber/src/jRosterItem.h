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
#ifndef __JROSTERITEM_H
#define __JROSTERITEM_H

#include <onir/im/imRosterItem.h>
#include "jJid.h"

using namespace std;
using onirIM::imRosterItem;
class jSession;

class jRosterItem : public imRosterItem {

	public:
		jRosterItem(jSession * session, jRosterItem * parent = NULL);
		virtual ~jRosterItem();

		const jJid& Jid() const { return _jid; };
		void Jid(const jJid& jid) { _jid = jid; };
		
		virtual bool FixedOrder(vector<string>& olist);
		
		inline void SoftwareName(const string& s) { _soft_name = s; };
		inline void SoftwareVersion(const string& s) { _soft_version = s; };
		inline void OS(const string& s) { _os = s; };

	private:
		jJid _jid;
		
		// JEP-0092 stuff (version info)
		string _soft_name;
		string _soft_version;
		string _os;

		DECLARE_OOBJECT;

};

#endif
