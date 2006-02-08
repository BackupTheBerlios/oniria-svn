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
 
#ifndef __G_ITEM_COL_H__
#define __G_ITEM_COL_H__

#include <QtCore/QObject>
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>
#include <QtGui/QMovie>
#include <QtGui/QPicture>

#include "gcore.h"
#include "ogur_dll.h" 

class GItemLine;

class LIBOGUR_API GItemCol : public QObject
{
	Q_OBJECT
	public:
		enum GColDataType{ animation, image, text, html, unknown };
		GItemCol(QObject * parent = 0);
		virtual ~GItemCol();
		virtual void draw(QPainter * painter, const QRect & rect, bool torect = false);
		virtual void data(GColDataType type, const QString & filename);
		inline GColDataType type() { return _type; }
		virtual void start();
		virtual void stop();
		virtual GItemLine * addLine();
		QSize size();
	public slots:
		virtual void slotUpdateRequired();
	signals:
		void signalUpdateRequired();
	private:
		void deleteData();
		GColDataType _type;
		QTextDocument * _text;
		QImage * _image;
		QMovie * _movie;
		QSize _animsize;
		QList<GItemLine *> _lines;
	private slots:
		void resized(const QSize & rect);
		void updated(const QRect & rect);
	
};
#endif /* __G_ITEM_COL_H__ */
