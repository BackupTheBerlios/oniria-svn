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
 
#ifndef __TREE_LIST_ITEM_H
#define __TREE_LIST_ITEM_H

#include "ogur_dll.h"
#include <QWidget>

class LIBOGUR_API TreeListItem :public QWidget{
	Q_OBJECT;
	public:
		TreeListItem(QWidget * parent = 0);		
		inline QString FirstTitle() { return _firstTitle; };
		void FirstTitle(const QString & value);
		
		inline QString SecondTitle() { return _secondTitle; }
		void SecondTitle(const QString & value);
		
		inline QString Ident() { return _ident; }
		inline void Ident(const QString & value) { _ident = value; }
		
		inline bool Selected() { return _selected; }
		void Selected(bool value);		
		
		inline bool Expanded() { return _expanded; }
		void Expanded(bool value);
		
		inline bool Visible() { return _visible; }
		void Visible(bool value);
		
		QList<TreeListItem *> & Childs() { return _childs; }
		QSize Draw();
	protected:
		virtual void paintEvent(QPaintEvent *);
		virtual void mousePressEvent(QMouseEvent * e);
	private:		
		QSize Draw(QPainter & paint);
		QString _ident;
		QString _firstTitle;
		QString _secondTitle;
		bool _selected;
		bool _expanded;	
		bool _visible;
		QList<TreeListItem *> _childs;				
};

#endif /* __TREE_LIST_ITEM__ */

