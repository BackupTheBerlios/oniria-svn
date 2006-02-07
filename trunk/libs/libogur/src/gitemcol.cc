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

#include "gitemcol.h"
#include "gitemcanvas.h"
#include "gitemline.h"

GItemCol::GItemCol(QObject * parent)
:QObject(parent),_type(unknown)
{
}

GItemCol::~GItemCol()
{
	GItemLine * o = 0;
	QListIterator<GItemLine *> it(_lines);
	while (it.hasNext()){
		o = it.next();
		disconnect(o,  SIGNAL(signalUpdateRequired()), this, SLOT(slotUpdateRequired()));
		delete o;
	}
	_lines.clear();
}

void GItemCol::updated(const QRect & rect)
{
	Q_UNUSED(rect)
	slotUpdateRequired();
}

void GItemCol::slotUpdateRequired()
{
	emit signalUpdateRequired();
}

QSize GItemCol::size()
{
	if (_lines.empty()){
		switch (_type){
			case animation:
				return QSize();
			case image:
				return _image->size();
			case text:
				break;
				
			default:
				qWarning("GItemCol::size (Unknown data format)");
		}
	}
	QSize sz(0, 0);
	QSize s;
	foreach(GItemLine * l, _lines){
		s = l->size();
		if (sz.width() < s.width())
			sz.setWidth(s.width());
		sz.setHeight(sz.height() + s.height());
	}
	return sz;
}


GItemLine * GItemCol::addLine()
{
	GItemLine * line = new GItemLine(this);
	connect (line, SIGNAL(signalUpdateRequired()), this, SLOT(slotUpdateRequired()));
	_lines.append(line);
	return line;
}

void GItemCol::deleteData()
{
	switch (_type){
		case animation:
			disconnect(_movie, SIGNAL(updated()), this, SLOT(updated(const QRect &)));
			delete _movie;
			break;
		case image:
			delete _image;
			break;			
		case text:
			delete _text;
			break;
			
		default:
			qWarning("GItemCol::deleteData (Unknown data format)");
	}
}


void GItemCol::draw(QPainter * painter, const QRect & rect)
{
	if (_lines.empty()){
		switch (_type){
			case animation:
				if (_movie->state() == QMovie::Running)
					painter->drawPixmap(rect.x(), rect.y(), _movie->currentPixmap());
				break;
			case image:
				painter->drawPixmap(rect, QPixmap::fromImage(*_image));
				break;
			case text:
				break;
				
			default:
				qWarning("GItemCol::data (Unknown data format)");
		}
	}else{
		foreach(GItemLine * l, _lines){
			l->draw(painter, rect);
		}
	}
}

void GItemCol::data(GColDataType type, const QString & filename)
{
	_type = type;
	switch (_type){
		case animation:
			_movie = new QMovie(filename, QByteArray(), this);
			connect(_movie, SIGNAL(updated()), this, SLOT(updated(const QRect &)));
			break;
		case image:
			_image = new QImage(filename);
			break;
			
		case text:
			_text = new QTextDocument(this);
			//_text->setSource(filename);
			break;
			
		default:
			qWarning("GItemCol::data (Unknown data format)");
	}
}

void GItemCol::start()
{
	if (_lines.empty()){
		if (_type == animation)
			_movie->start();
	}else{
		foreach(GItemLine * l, _lines){
			l->start();
		}
	}
}

void GItemCol::stop()
{
	if (_lines.empty()){
		if (_type == animation)
			_movie->stop();
	}else{
		foreach(GItemLine * l, _lines){
			l->stop();
		}
	}
}
