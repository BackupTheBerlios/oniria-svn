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
	
}

void GItemCol::updated(const QRect & rect)
{
		emit signalUpdateRequired();
}

void GItemCol::addLine(GItemLine * line)
{
	_lines.append(line);
}

void GItemCol::deleteData()
{
	switch (_type){
		case animation:
			delete _movie;
			disconnect(_movie, SIGNAL(updated()), this, SLOT(updated(const QRect &)));
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
				painter->drawPicture(rect.x(), rect.y(), *_image); 
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
			_image = new QPicture();
			_image->load(filename);
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
