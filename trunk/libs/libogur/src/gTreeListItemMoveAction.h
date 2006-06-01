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

#ifndef __TIMERACTION__H__
#define __TIMERACTION__H__

#include "gAction.h"

class GTreeListItem;
class GAction;

class LIBOGUR_API GTreeListItemMoveAction : public GAction{
	Q_OBJECT
	public:
		GTreeListItemMoveAction(GTreeListItem * parent, int interval);
	protected:
		virtual void relayEvent(QEvent * e);
		virtual void reset();
	protected slots:
		virtual void slotTimer();	
	private:
		GTreeListItem * _parent;
		int _actStep;
		int _maxStep;
		int _currentStep;
		int _interval;
		bool _intimer;		
		QTimer * _timer;
};

#endif /*__TIMERACTION__H__ */
