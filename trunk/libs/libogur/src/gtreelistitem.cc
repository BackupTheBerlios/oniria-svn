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
#include "gtreelistitem.h"


GTreeListItem::GTreeListItem(QWidget * parent, const QString & ident)
:QWidget(parent)
{
	hide();
	_ident = ident;	
	_selected = false;
	_expanded = false;
	_visible = true;	
}

GTreeListItem::~GTreeListItem()
{
	GTreeListItem * o = 0;
	QListIterator<GTreeListItem *> it(_childs);
	while (it.hasNext()){
		o = it.next();
		o->hide();
		delete o;
	}
}

void GTreeListItem::selected(bool value)
{
	_selected = value;
}

void GTreeListItem::expanded(bool value)
{
	_expanded = value;
}

void GTreeListItem::visible(bool value)
{
	_visible = value;
}

void GTreeListItem::mousePressEvent(QMouseEvent * e)
{
	//selected(!selected());	
	expanded(!expanded());	
	GMouseEvent tlme(e, this, GMouseEvent::one_click);	
	emit itemMouseClick(&tlme);
}

void GTreeListItem::mouseDoubleClickEvent(QMouseEvent * e)
{
	GMouseEvent tlme(e, this, GMouseEvent::db_click);	
	emit itemMouseClick(&tlme);
}

QSize GTreeListItem::drawItem(bool draw)
{
	QPainter p(this);
	return drawItem(p);	
}

QSize GTreeListItem::drawItem(QPainter & paint)
{	
	QColor c1, c2;
	if (selected()){
		c1 = QColor(0, 0, 0, 255);
		c2 = QColor(0, 0, 0, 0);
	}else{ 
		c1 = QColor(0, 0, 0, 0);
		c2 = QColor(0, 0, 0, 255);		
	}
	
	QLinearGradient fade(0, 0, 0, height());
    fade.setColorAt(0, c1);
    fade.setColorAt(1, c2);
    paint.fillRect(rect(), fade);
		
	paint.drawText(10, 10, _ident);	
	return size();
}

void GTreeListItem::paintEvent(QPaintEvent *)
{	
	QPainter p(this);
	drawItem(p);
}
