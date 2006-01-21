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
 
#ifndef __TREE_LIST_H
#define __TREE_LIST_H

#include "ogur_dll.h"
#include <QScrollArea>
#include <QMap>

class TreeListItem;

class LIBOGUR_API TreeList: public QScrollArea
{	
	Q_OBJECT	
	public:
		TreeList(QWidget * parent = 0);
		virtual ~TreeList();
		TreeListItem * CreateItem(const QString & ident, const QString & pident);
		void Redraw();
	private:
		TreeListItem * _rootItem;
		QMap <QString, TreeListItem *> _items;
};
#endif /* __TREE_LIST__ */
