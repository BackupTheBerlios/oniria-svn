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
 
#include "gitemline.h"
#include "gitemcol.h"

GItemLine::GItemLine(QObject * parent)
:QObject(parent)
{
}

GItemLine::~GItemLine()
{
	
}

void GItemLine::draw(QPainter * painter, const QRect & rect)
{
	foreach(GItemCol * l, _cols){
		l->draw(painter, rect);
	}		
}

void GItemLine::addCol(GItemCol * col)
{
	_cols.append(col);
}

void GItemLine::start()
{
	foreach(GItemCol * l, _cols){
		l->start();
	}	
}

void GItemLine::stop()
{
	foreach(GItemCol * l, _cols){
		l->stop();
	}	
}
