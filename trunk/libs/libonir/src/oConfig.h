/* $Id$ */
/*
 * Copyright (C) 2005-2006 Michal Wysoczanski <choman@foto-koszalin.pl>
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
 
#ifndef __OCONFIG_H
#define __OCONFIG_H

#include <QVector>
#include <QString>

#include "onir_dll.h"

/*!\file oConfig.h
 * 
 * \sa oConfig
 */

namespace onirXML{
    class xmlElement;
};

using onirXML::xmlElement;

namespace onir {
	
/*!\class oConfig
 * \brief This class is libxml2 library wrapper.  
 *
 * Class facilitates use with xml files.
 * it can Store and load data, from any node in xml file
 */
class LIBONIR_API oConfig 
{
	public:

		oConfig();
		virtual ~oConfig();

		virtual xmlElement * setValue(const QString& parent, const QString& node, const QString& value, bool force = false) = 0;
		virtual xmlElement * setValue(xmlElement * parent, const QString& subn,const QString& value, bool force = false) = 0;
		virtual xmlElement * setValue(const QString& xpath, const QString& value, bool force = false) = 0;
		
		virtual QString value(const QString& parent, const QString& node, const QString& defval) = 0;
		virtual QString value(xmlElement * parent, const QString& defval) = 0;
		virtual QString value(xmlElement * parent, const QString& name, const QString& defval) = 0;
		virtual QString value(const QString& xpath, const QString& defval) = 0;
		
		virtual xmlElement * setValue(const QString& parent, const QString& node, int value, bool force = false) = 0;
		virtual xmlElement * setValue(xmlElement * parent, const QString& subn,int value, bool force = false) = 0;
		virtual xmlElement * setValue(const QString& xpath, int value, bool force = false) = 0;
		
		virtual int value(const QString& parent, const QString& node, int defval) = 0;
		virtual int value(xmlElement * parent, int defval) = 0;
		virtual int value(xmlElement * parent, const QString& name, int defval) = 0;
		virtual int value(const QString& xpath, int defval) = 0;
		
		virtual xmlElement * root() = 0;
		virtual xmlElement * node(const QString& xpath) = 0;
		virtual xmlElement * node(xmlElement * parent, const QString& name) = 0;
		virtual QVector<xmlElement *> children(const QString& parent) = 0;
		virtual QVector<xmlElement *> children(xmlElement * parent) = 0;
		virtual QVector<xmlElement *> children(xmlElement * parent, const QString& name) = 0;
		virtual QString nodeName(xmlElement * p) = 0;
		virtual void removeNode(xmlElement * parent) = 0;
		virtual void removeNode(const QString& xpath) = 0;
};

}
#endif /* __OCONFIG_H */

