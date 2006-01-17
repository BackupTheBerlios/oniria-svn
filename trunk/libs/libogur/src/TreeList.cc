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

#include "TreeListItem.h"
#include "TreeList.h"

TreeList::TreeList(QWidget * parent):
QScrollArea(parent)
{	
	_rootItem = new TreeListItem(0);	
	_rootItem->Expanded(true);
	_rootItem->Visible(false);
	_rootItem->resize(0, 0);
	_items.insert("", _rootItem);
}

TreeList::~TreeList()
{
}

TreeListItem * TreeList::CreateItem(const QString & ident, const QString & pident)
{	
	TreeListItem * pitem = 0;
	if (_items.find(pident) != _items.end())
		pitem = _items[pident];		
	else
		pitem = _rootItem;
		
	TreeListItem * item = new TreeListItem(this);
	_items.insert(ident, item);
	item->Ident(ident);	
	pitem->Childs().append(item);
	
	return item;
}

void TreeList::Redraw()
{
	_rootItem->Draw();
}
