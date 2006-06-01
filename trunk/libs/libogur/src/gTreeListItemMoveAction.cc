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
#include "gTreeListItem.h"
#include "gTreeListItemMoveAction.h"


GTreeListItemMoveAction::GTreeListItemMoveAction(GTreeListItem * parent, int interval)
:GAction(parent)
{
	_parent = parent;
	_interval = interval;
	_timer = new QTimer(this);
	connect(_timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
	_actStep = 1;
	_maxStep = 10;
	_currentStep = 1;
	_intimer = false;	
}

void GTreeListItemMoveAction::relayEvent(QEvent * e)
{	
	if (e->type() == QEvent::Enter){
		_actStep = 1;
		_intimer = true;
		if (_currentStep == 0)
			_currentStep = 1;
		if (!_timer->isActive())
			_timer->start(_interval);			
	}
}

void GTreeListItemMoveAction::reset()
{
	_timer->stop();		
	_currentStep = 0;
}

void GTreeListItemMoveAction::slotTimer()
{
	if (_intimer){
		_parent->move(_parent->x() + _actStep, _parent->y());
		_currentStep += _actStep;
		if (_currentStep > _maxStep)
			_actStep  = -1;
		if (_currentStep <= 1){
			_intimer = false;
		}
	}else{
		_timer->stop();		
		_currentStep = 0;
	}	
	emit signalProcess();
}
