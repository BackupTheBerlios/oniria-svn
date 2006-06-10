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
 
#ifndef __OXMLCONFIG_H
#define __OXMLCONFIG_H

/*!\file oXMLConfig.h
 * 
 * \sa oXMLConfig
 */ 
 
#include <QString>
#include <QVector>
#include <QList>
#include <QStringList>
#include <onir/oConfig.h>
#include <oxml/xmlParser.h>

namespace onirXML {
    class xmlParser;
};
using onir::oConfig;
using onirXML::xmlParser;

/*!\class oXMLConfig
 * \brief Class for handling config files.
 */

class oXMLConfig : public oConfig {
	public:
		/*!\name Constructor and destructor
		 */
		//@{

		/*!\fn oXMLConfig(const QString& file = "", bool load = false);
		 * \brief Constructor
		 * \param file Configuration file name.
		 * \param load If true, configuration file will be loaded.
		 * \sa Load()
		 */	       
		oXMLConfig(const QString & file=QString(),bool load=false);
	
		virtual ~oXMLConfig();
		//@}
		

		/*!\name Saving and loading.
		 */
		//@{

		/*! \fn void file(const QString& file);
		 * \brief Sets configuration file name.
		 * \sa oXMLConfig(), load()
		 */
		void file(const QString& file);
		
		/*!\fn bool load(const QString& file);
		 * \brief Loads configuration from XML file.
		 * \param file File name.
		 * \return True if file is successfully loaded.
		 */
		bool load(const QString & file);
		
		/*!\fn bool load();
		 * \brief Loads configuration from XML file.
		 * \return True if file is successfully loaded.
		 *
		 * Before calling this method you should set config file name
		 * using file() method.
		 * \sa file
		 */
		bool load();

		/*! \fn void save();
		 * \brief Saves configuration to XML file. 
		 * \sa file()
		 */
		void save();
		//@}

		/*\name Values operations.
		 */ 
		//@{
		xmlElement * setValue(const QString& parent, const QString& node, const QString& value, bool force = false);
		xmlElement * setValue(xmlElement * parent, const QString& subn, const QString& value, bool force = false);
		xmlElement * setValue(const QString& xpath, const QString & value, bool force = false);
		
		QString value(const QString& parent, const QString& node, const QString & defval);
		QString value(xmlElement * parent, const QString& defval);
		QString value(xmlElement * parent, const QString& name, const QString& defval);
		QString value(const QString& xpath, const QString& defval);
		
		xmlElement * setValue(const QString& parent, const QString& node, int value, bool force = false);
		xmlElement * setValue(xmlElement * parent, const QString& subn, int value, bool force = false);
		xmlElement * setValue(const QString& xpath, int value, bool force = false);
		
		int value(const QString& parent, const QString& node, int defval);
		int value(xmlElement * parent, int defval);
		int value(xmlElement * parent, const QString& name, int defval);
		int value(const QString& xpath, int defval);
		//@}
		
		/*!\name Nodes operations
		 */
		//@{
		
		/*!\fn xmlElement * root()
		 * \brief Return pointer to the root node.
		 * \return Pointer to the root node
		 * \sa node(), children(), nodeName()
		 */
		xmlElement * root();
		
		/*!\fn xmlElement * node(const QString& xpath);
		 * \brief Returns pointer to the XML node.
		 * \param xpath Node path.
		 * \return Pointer to xmlElement
		 */
		xmlElement * node(const QString& xpath);
		xmlElement * node(xmlElement * parent, const QString& name);

		QVector<xmlElement *> children(const QString& parent);
		QVector<xmlElement *> children(xmlElement * parent);
		QVector<xmlElement *> children(xmlElement * parent, const QString& name);

		QString nodeName(xmlElement * p);

		xmlElement * removeNode(xmlElement * parent);
		xmlElement * removeNode(const QString& xpath);
		//@}

	private:

		void createDoc();
		bool tryLoad();		

		QStringList parseXPath(const QString& xpath);

		xmlElement * createXMLPath(const QStringList& v, bool create = true);

		bool nodeExists(xmlElement * parent, const QString& name, int index = 0);

		xmlElement * _root;
		xmlParser * _parser;
		QString _file;
};

#endif
