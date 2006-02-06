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

#ifndef __G_TREE_LIST_ITEM_TABLE_H__
#define __G_TREE_LIST_ITEM_TABLE_H__

#include <QtGui/QPainter>
#include <QtCore/QObject>

#include "gcore.h"
#include "ogur_dll.h" 

class LIBOGUR_API GTreeListItemLine : public QObject
{
	Q_OBJECT
	public:
		GTreeListItemLine(QObject * parent = 0);
		virtual ~GTreeListItemLine();
		void draw(QPainter * painter, const QRect & rect);
	signals:
		void signalUpdateRequired();
	
};

#endif /* __G_TREE_LIST_ITEM_TABLE_H__ */
