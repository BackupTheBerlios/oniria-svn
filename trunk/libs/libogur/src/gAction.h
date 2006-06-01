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

#ifndef __ACTION_H__
#define __ACTION_H__

#include "ogur_dll.h"
#include <QWidget>

class LIBOGUR_API GAction: public QObject{
	Q_OBJECT
	public:
		GAction(QObject * parent);
		virtual void relayEvent(QEvent * e) = 0;
		virtual void reset() {};
	signals:
		void signalProcess();
};

#endif /* __ACTION_H__ */
