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
 
#ifndef __TREE_LIST_ITEM__
#define __TREE_LIST_ITEM__

#include "gcore.h"
#include "ogur_dll.h" 
#include <QWidget>


class GTreeListItem;

class LIBOGUR_API GTreeListItem :public QWidget{
	Q_OBJECT
	public:		
		GTreeListItem(QWidget * parent, const QString & ident, GTreeListItem * top);		
		~GTreeListItem();
		
		inline QString ident() { return _ident; }		
		
		inline bool selected() { return _selected; }
		void selected(bool value);		
		
		inline bool expanded() { return _expanded; }
		void expanded(bool value);
		
		inline bool visible() { return _visible; }
		void visible(bool value);
		
		QList<GTreeListItem *> & childs() { return _childs; }
		QSize drawItem(bool draw = true);
		GTreeListItem * top() { return _top; }
	signals:		
		void itemMouseClick(GMouseEvent * sender);		
	protected:
		virtual void paintEvent(QPaintEvent *);
		virtual void mousePressEvent(QMouseEvent * e);
		virtual void mouseDoubleClickEvent(QMouseEvent * e);
	private:		
		QSize drawItem(QPainter & paint);
		QString _ident;
		bool _selected;
		bool _expanded;	
		bool _visible;
		GTreeListItem * _top;
		QList<GTreeListItem *> _childs;				
};

#endif /* __TREE_LIST_ITEM__ */

