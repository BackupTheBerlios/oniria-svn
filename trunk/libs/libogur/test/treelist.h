/* $Id: treelist.h 42 2006-01-23 10:30:02Z morg $ */
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
 * MERCHANTABILITY or FITNESS FOR A PAtreeICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
 
#include <QWidget>

class GTreeList;
class GTreeListItem;

 class MainWnd : public QWidget{
	Q_OBJECT
	public:	
		MainWnd(QWidget * parent = 0);
	public slots:
		void browse();	
	private:
		QString currentMovieDirectory;
		GTreeList * tree;
		GTreeListItem *item;
};
