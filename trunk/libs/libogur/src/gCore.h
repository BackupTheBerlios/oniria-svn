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
 
#ifndef __CORE__H__
#define __CORE__H__

#include "ogur_dll.h" 
#include <QWidget>

class LIBOGUR_API GMouseEvent{
	public:
		enum ClickType{ one_click, db_click };
		GMouseEvent(QMouseEvent * me, QWidget * s, ClickType ct = one_click);
		inline QPoint pos() { return _pos; }
		inline QPoint globalPos() { return _globalPos; }
		inline QWidget * sender() { return _sender; }
		inline Qt::MouseButton button() { return _button; }
		inline Qt::MouseButtons buttons() { return _buttons; }
		inline Qt::KeyboardModifiers modifiers() { return _modifiers; }
		inline ClickType click() { return _clickType; } 
	private:
		Qt::MouseButton _button;
		Qt::MouseButtons _buttons;
		Qt::KeyboardModifiers _modifiers;
		QPoint _pos, _globalPos;
		QWidget * _sender;
		ClickType _clickType;

};
#endif /* __CORE__H__ */ 
