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
		GTreeListItem * nextVisible(GTreeListItem * current = 0);
		GTreeListItem * previousVisible(GTreeListItem * current = 0);		
		int clearSelected();
		inline QMap<QString, GTreeListItem *> & selected() { return _selected; }
	public slots:
		void slotMouseEvent(GMouseEvent * ev);
	protected:
		void keyPressEvent(QKeyEvent *e);
	private:
		void drawItems(GTreeListItem * root, QSize & sz, bool show, GTreeListItem * from = 0);
		void setupItem(GTreeListItem * item);
		bool _candraw;
		GTreeListItem * _rootItem;
		GTreeListItem * _currentItem;
		QWidget * _canvas;
		int _drawIdent;
		QMap <QString, GTreeListItem *> _items;
		QMap <QString, GTreeListItem *> _selected;
};
#endif /* __TREE_LIST__ */
