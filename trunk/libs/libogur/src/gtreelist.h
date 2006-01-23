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
 
#ifndef __TREE_LIST__
#define __TREE_LIST__

#include "ogur_dll.h" 
#include <QScrollArea>
#include <QMap>

class GTreeListItem;
class GMouseEvent;

class LIBOGUR_API GTreeList: public QScrollArea
{	
	Q_OBJECT	
	public:
		GTreeList(QWidget * parent = 0);
		virtual ~GTreeList();
		GTreeListItem * createItem(GTreeListItem * parent, const QString & ident);
		GTreeListItem * createItem(const QString & ident, const QString & pident);		
		void redraw(GTreeListItem * from = 0);		
		GTreeListItem * elementAt(const QString & ident);
	public slots:
		void mouseEvent(GMouseEvent * ev);
	private:
		void drawItems(GTreeListItem * root, QRect & rc, bool show, GTreeListItem * from = 0);
		bool _candraw;
		GTreeListItem * _rootItem;
		QWidget * _canvas;
		QMap <QString, GTreeListItem *> _items;
};
#endif /* __TREE_LIST__ */