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
#include "gtreelistitemmoveaction.h"

GTreeList::GTreeList(QWidget * parent):
QScrollArea(parent)
{	
	_canvas = new QWidget(this);
	_rootItem = new GTreeListItem(_canvas, "", 0);	
	Q_ASSERT(_rootItem);
	_rootItem->expanded(true);
	_rootItem->visible(false);
	_rootItem->resize(0, 0);
	_items.insert(_rootItem->ident(), _rootItem);
	setWidget(_canvas);
	_drawIdent = 0;
	_currentItem = _rootItem;
}

GTreeList::~GTreeList()
{
	delete _rootItem;
	delete _canvas;
}

void GTreeList::setupItem(GTreeListItem * item)
{
	item->addAction(new GTreeListItemMoveAction(item, 10));
}

GTreeListItem * GTreeList::createItem(GTreeListItem * parent, const QString & ident)
{
	Q_ASSERT(parent);
	GTreeListItem * childitem = new GTreeListItem(_canvas, ident, parent);
	Q_CHECK_PTR(childitem);
	setupItem(childitem);
	
	_items.insert(childitem->ident(), childitem);
	if (!parent->childs().empty()){
		GTreeListItem * item = parent->childs().last();
		item->next(childitem);
		childitem->previous(item);
	}
	parent->childs().append(childitem);
	connect(childitem, SIGNAL(signalItemMouseClick(GMouseEvent *)), this, SLOT(slotMouseEvent(GMouseEvent *)));
	if (!_currentItem)
		_currentItem = childitem;
	return childitem;
}

GTreeListItem * GTreeList::createItem(const QString & ident, const QString & pident)
{	
	GTreeListItem * pitem = 0;
	if (_items.find(pident) != _items.end())
		pitem = _items[pident];			
	else
		pitem = _rootItem;
		
	Q_ASSERT(pitem);	
	return createItem(pitem, ident);	
}

GTreeListItem * GTreeList::elementAt(const QString & ident)
{
	if (_items.find(ident) != _items.end())
		return _items[ident];			
	else
		return 0;

}

GTreeListItem * GTreeList::nextVisible(GTreeListItem * current)
{
	if (current == 0)
		current = _currentItem;
	Q_ASSERT(current);	
	if (current->expanded()){		
		if (!current->childs().empty()){			
			return current->childs().first();
		}
	}else{
		if (current->next())
			return current->next();
		else
			if (current->top() && current->top()->next())
				return current->top()->next();
	}
	return current;
}

GTreeListItem * GTreeList::previousVisible(GTreeListItem * current)
{
	if(current == 0)
		current = _currentItem;
	Q_ASSERT(current);
	
	if (current->previous()){
		if (current->previous()->expanded()){
			if (!current->previous()->childs().empty())
				return current->previous()->childs().last();
		}			
		return current->previous();
	}
	if (current->top() && current->top() != _rootItem)
		return current->top();
	return current;
}

void GTreeList::keyPressEvent(QKeyEvent *e)
{	
	Q_ASSERT(_currentItem);
	if (e->key() == Qt::Key_Left && _currentItem->expanded()){
		_currentItem->expanded(false);
		redraw();
		return ;
	}else if (e->key() == Qt::Key_Right && !_currentItem->expanded()){
		_currentItem->expanded(true);
		redraw();
		return ;
	}

	if (e->modifiers() ^ Qt::ControlModifier){
		clearSelected();
	}
	if (e->key() == Qt::Key_Down){
		_currentItem = nextVisible();
	}else if (e->key() == Qt::Key_Up){
		_currentItem = previousVisible();
	}
	_currentItem->selected(true);
	_selected.insert(_currentItem->ident(), _currentItem);
		
}

void GTreeList::slotMouseEvent(GMouseEvent * ev)
{
	GTreeListItem * it = elementAt(reinterpret_cast<GTreeListItem*>(ev->sender())->ident());	
	Q_ASSERT(it);
	
	if (ev->modifiers() ^ Qt::ControlModifier){
		clearSelected();	
		it->selected(true);			
		if (!it->childs().empty())
			it->expanded(!it->expanded());	
		_selected.insert(it->ident(), it);
	}else{
		it->selected(!it->selected());
		if (it->selected()){
			_selected.insert(it->ident(), it);
		}else{
			_selected.remove(it->ident());
		}
	}
	_currentItem = it;
	redraw(qobject_cast<GTreeListItem*>(ev->sender()));	
}

void GTreeList::redraw(GTreeListItem * from)
{
	QSize r;//(_rootItem->pos(), QSize(0, 0));
	_candraw = false;
	drawItems(_rootItem, r, true, from);
	if (r.width() < width())
		r.setWidth(width());
	_canvas->resize(r);
	
}

void GTreeList::drawItems(GTreeListItem * root, QSize & sz, bool show, GTreeListItem * from)
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
				i->prepare(false);					
				i->resetActions();
				i->move(_drawIdent, sz.height());				
				sz.setHeight(sz.height() + i->height());
				
				if (sz.width() < i->width())
					sz.setWidth(i->width());
				
				sz.setHeight(sz.height());
				if (_candraw){
					i->show();					
					i->repaint();
				}				
			}else
				i->hide();
		}
		
		if (show && (i->expanded())){
			int ident = 20;
			_drawIdent = ident;			
			drawItems(i, sz, true);
			_drawIdent = 0;			
		}else
			drawItems(i, sz, false);
			
	}
}

int GTreeList::clearSelected()
{
	QMapIterator<QString, GTreeListItem *> it(_selected);
	int selected(0);
	GTreeListItem *i;
	while(it.hasNext()){
		i = it.next().value();
		selected++;
		i->selected(false);
	}
	_selected.clear();
	return selected;
}

