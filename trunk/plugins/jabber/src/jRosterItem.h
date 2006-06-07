/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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

#include <oim/imRosterItem.h>
#include "jJid.h"

using onirIM::imRosterItem;
class jSession;

class jRosterItem : public imRosterItem {

	public:
		jRosterItem(jSession * session, jRosterItem * parent = NULL);
		virtual ~jRosterItem();

		const jJid& jid() const { return _jid; };
		void jid(const jJid& jid) { _jid = jid; };
		
		virtual bool fixedOrder(QVector<QString>& olist);
		
		// JEP-0092 stuff (version info)
		inline void softwareName(const QString& s) { _soft_name = s; };
		inline void softwareVersion(const QString& s) { _soft_version = s; };
		inline void OS(const QString& s) { _os = s; };

	private:
		jJid _jid;
		
		// JEP-0092 stuff (version info)
		QString _soft_name;
		QString _soft_version;
		QString _os;
};

#endif
