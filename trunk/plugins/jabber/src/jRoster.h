/* $Id: jRoster.h 559 2005-09-08 14:05:42Z choman $ */
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
#ifndef __JROSTER_H
#define __JROSTER_H

#include <onir/im/imRoster.h>
#include "jJid.h"

using namespace std;
using onirIM::imRoster;
class jSession;

class jRoster : public imRoster {

	public:
		jRoster(jSession * session);
		virtual ~jRoster();
		
		inline bool NestedGroups() const { return _nested_groups; };
		void NestedGroups(bool ng) { _nested_groups = ng; };
		inline const string& NestedGroupsDelimiter() const { return _ng_delimiter; };
		void NestedGroupsDelimiter(const string& ngd) { _ng_delimiter = ngd; };

	private:
		bool _nested_groups;
		string _ng_delimiter;

		DECLARE_OOBJECT;

};

#endif
