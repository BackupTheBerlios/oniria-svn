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
#include "gtreelistitemmoveaction.h"

GTreeListItem::GTreeListItem(QWidget * parent, const QString & ident, GTreeListItem * top)
:QWidget(parent)
{
	_action = new GTreeListItemMoveAction(this, 10);
	hide();
	_ident = ident;	
	_selected = false;
	_expanded = false;
	_visible = true;	
	_top = top;
	_next = 0;
	_previous = 0;
	installEventFilter(this);
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
	//delete _action;
	//_action = 0;
}

void GTreeListItem::selected(bool value)
{
	_selected = value;
	repaint();
}

void GTreeListItem::expanded(bool value)
{
	_expanded = value;
	if (childs().empty())
		_expanded = false;
}

void GTreeListItem::visible(bool value)
{
	_visible = value;
}

void GTreeListItem::mousePressEvent(QMouseEvent * e)
{		
	GMouseEvent tlme(e, this, GMouseEvent::one_click);	
	emit signalItemMouseClick(&tlme);
}

void GTreeListItem::mouseDoubleClickEvent(QMouseEvent * e)
{
	GMouseEvent tlme(e, this, GMouseEvent::db_click);	
	emit signalItemMouseClick(&tlme);
}

bool GTreeListItem::eventFilter(QObject *obj, QEvent *e)
{
	if (_action != 0){
		_action->relayEvent(e);
	}
	return QWidget::eventFilter(obj, e);
}

QSize GTreeListItem::drawItem(bool draw)
{	
	return size();
}
	
void GTreeListItem::paintEvent(QPaintEvent *)
{	
	QPainter p(this);
	QColor c1, c2;
	if (selected()){
		c1 = QColor(0, 0, 0, 255);
		c2 = QColor(0, 0, 255, 0);
	}else{ 
		c1 = QColor(0, 0, 0, 0);
		c2 = QColor(0, 255, 0, 255);		
	}
	
	QLinearGradient fade(0, 0, 0, height());
	fade.setColorAt(0, c1);
	fade.setColorAt(1, c2);
	p.fillRect(rect(), fade);

	p.drawText(10, 10, _ident);	
}
