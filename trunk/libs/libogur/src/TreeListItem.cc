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
 
#include <QtGui>
//#include <QListIterator>
//#include "TreeList.h"
#include "TreeListItem.h"


TreeListItem::TreeListItem(QWidget * parent)
:QWidget(parent)
{
	_ident = "";	
	_firstTitle = "";
	_secondTitle = "";
	_selected = false;
	_expanded = false;
	_visible = true;
}

void TreeListItem::FirstTitle(const QString & value)
{
	_firstTitle = value;
	repaint();
}

void TreeListItem::SecondTitle(const QString & value)
{
	_secondTitle = value;
	repaint();
}

void TreeListItem::Selected(bool value)
{
	_selected = value;
	repaint();
}

void TreeListItem::Expanded(bool value)
{
	_expanded = value;
	Draw();
}

void TreeListItem::Visible(bool value)
{
	_visible = value;
	repaint();
}

void TreeListItem::mousePressEvent(QMouseEvent * e)
{
	Selected(!Selected());	
	Expanded(!Expanded());
}

QSize TreeListItem::Draw()
{	
	QRect sr;
	if (Visible()){		
		QPainter p(this);
		QSize s = Draw(p);	
		sr.setSize(s);	
		if (Expanded()){
			sr.setLeft(sr.left() + 10);
			QListIterator<TreeListItem *> it(_childs);
			while (it.hasNext()){
				TreeListItem * o = it.next();
				o->move(sr.left(), sr.bottom());
				QSize s = o->Draw();
				sr.setBottom(sr.bottom() + s.height());		
				o->move(sr.left(), sr.bottom());
			}
		}
	}	
	return sr.size();
}

QSize TreeListItem::Draw(QPainter & paint)
{	
	if (Selected())
		paint.drawLine(0, 0,  width(),  height());	
	else 
		paint.drawLine(0, height(), width(), 0);
	paint.drawText(10, 10, _ident);	
	return size();
}

void TreeListItem::paintEvent(QPaintEvent *)
{	
	QPainter p(this);
	Draw(p);
}
