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
#include "gCore.h"

GMouseEvent::GMouseEvent(QMouseEvent * me, QWidget * s, ClickType ct)
{	
	_sender = s;
	_clickType = ct;
	
	if (me){
		_pos = me->pos();
		_globalPos = me->globalPos();
		_button = me->button();
		_buttons = me->buttons();
		_modifiers = me->modifiers();
	}
}
