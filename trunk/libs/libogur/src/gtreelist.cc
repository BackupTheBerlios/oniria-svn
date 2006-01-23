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
#include "gtreelist.h"

GTreeList::GTreeList(QWidget * parent):
QScrollArea(parent)
{	
	_canvas = new QWidget(this);
	_rootItem = new GTreeListItem(_canvas, "");	
	Q_ASSERT(_rootItem);
	_rootItem->expanded(true);
	_rootItem->visible(false);
	_rootItem->resize(0, 0);
	_items.insert(_rootItem->ident(), _rootItem);
	setWidget(_canvas);
}

GTreeList::~GTreeList()
{
	delete _rootItem;
	delete _canvas;
}

GTreeListItem * GTreeList::createItem(GTreeListItem * parent, const QString & ident)
{
	Q_ASSERT(parent);
	GTreeListItem * childitem = new GTreeListItem(_canvas, ident);
	Q_CHECK_PTR(childitem);
	_items.insert(childitem->ident(), childitem);
	parent->childs().append(childitem);
	return childitem;
}

GTreeListItem * GTreeList::createItem(const QString & ident, const QString & pident)
{	
	qDebug() << "createItem ident:" << ident << " Parent:"<< pident;
	GTreeListItem * pitem = 0;
	if (_items.find(pident) != _items.end())
		pitem = _items[pident];			
	else
		pitem = _rootItem;
		
	Q_ASSERT(pitem);
	qDebug() << "Parentid:" << pitem->ident();
	GTreeListItem * childitem = new GTreeListItem(_canvas, ident);
	Q_CHECK_PTR(childitem);
	
	_items.insert(childitem->ident(), childitem);	
	pitem->childs().append(childitem);
	
	connect(childitem, SIGNAL(itemMouseClick(GMouseEvent *)), this, SLOT(mouseEvent(GMouseEvent *)));
	return childitem;
}

GTreeListItem * GTreeList::elementAt(const QString & ident)
{
	if (_items.find(ident) != _items.end())
		return _items[ident];			
	else
		return 0;

}

void GTreeList::mouseEvent(GMouseEvent * ev)
{
	//GTreeListItem * it = elementAt(reinterpret_cast<GTreeListItem*>(ev)->ident());	
	//Q_ASSERT(it);
	//if (ev->click() == ev->GMouseEvent::one_click){
		//it->selected(!it->selected());		
	//}
	//qDebug() << "wrr";
	//redraw(qobject_cast<GTreeListItem*>(ev->sender()));
	redraw();
}

void GTreeList::redraw(GTreeListItem * from)
{
	QRect r(_rootItem->pos(), QSize(0, 0));
	_candraw = false;
	drawItems(_rootItem, r, true, from);
	_canvas->resize(r.size());
	
}

void GTreeList::drawItems(GTreeListItem * root, QRect & rc, bool show, GTreeListItem * from)
{
	if ((!from) || (from == _rootItem))
		_candraw = true;
	
	QListIterator<GTreeListItem *> it(root->childs());
	while (it.hasNext()){
		GTreeListItem * i = it.next();
		if (i == from)
			_candraw = true;
		if (i->visible()){
			if (show){
				QSize s = i->drawItem(false);
				i->move(rc.x(), rc.y());
				rc.setY(rc.y() + s.height());
				
				if (rc.width() < s.width())
					rc.setWidth(s.width());
				
				rc.setHeight(rc.y());
				if (_candraw){
					i->show();					
					i->drawItem();
				}
				
			}else
				i->hide();
		}
		
		if (show && (i->expanded())){
			int ident = 20;
			rc.setX(rc.x() + ident);
			drawItems(i, rc, true);
			rc.setX(rc.x() - ident);
		}else
			drawItems(i, rc, false);
			
	}
}

