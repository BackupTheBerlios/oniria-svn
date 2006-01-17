/* $Id: xConfig.h 391 2005-08-21 09:00:01Z morg $ */
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
 
#ifndef __X_CONFIG_H
#define __X_CONFIG_H

/*!\file xConfig.h
 * 
 * \sa xConfig
 */ 
 
#include <onir/oConfig.h>
#include <list>
#include <vector>
#include <onir/xml/xmlParser.h>

namespace onirXML{
    class xmlParser;
};
using std::list;
using std::vector;
using onir::oConfig;
using onirXML::xmlParser;

/*!\class xConfig
 * \brief This class is libxml2 library wrapper.  
 *
 * Class facilitates use with xml files.
 * It can Store and load data, from any node in xml file
 */
class xConfig :public oConfig
{
	public:
		/** @name Common
		 * Initializing, and load or store functions
		 */
		//@{

		/*! \fn xConfig(const string & file=string(),bool load=false);
		 * \brief Constructor
		 * \param file takes <i>std::string</i> as file path, it need not be placed.
		 * \param load flag informing about: whether passed file has to be loaded
		 * \sa Load, FileName
		 */	       
		 xConfig(const string & file=string(),bool load=false);
	
		 virtual ~xConfig(); 
		
		/*! \fn bool Load(const string & file);
		 * \brief Load file
		 */
		bool Load(const string & file);
		
		/*! \fn bool Load();
		 * \brief Load file
		 * 
		 * File must be set in File function, or in the constructor
		 * \sa File
		 */
		bool Load();

		/*! \fn void File(const string & file);
		 * \brief Only sets file name, you must call Load method
		 * \sa xConfig
		 */
		void File(const string & file);

		/*! \fn void Flush();
		 * \brief Save internal xml tree into the file 
		 * \sa File
		 */
		void Flush();
		
		//@}

		/** @name Data manipulation
		 * Store and Loads data values, properties etc.
		 */
		//@{
		
		/** @name string manipulation 
		 * Store and Loads string values
		 */
		//@{
		xmlElement * StoreValue(const string & parent, const string & node, const string & value, bool force = false);
		xmlElement * StoreValue(xmlElement *parent, const string & subn, const string & value, bool force = false);
		xmlElement * StoreValueNs(const string & coors, const string & value, bool force = false);
		
		string Value(const string & parent, const string & node, const string & defval);
		string Value(xmlElement *parent, const string & defval);
		string Value(xmlElement *parent, const string & name, const string & defval);
		string ValueNs(const string & coors, const string & defval);
		//@}
		
		/** @name number manipulation 
		 * Store and Loads integer values
		 */
		//@{
		xmlElement * StoreValue(const string & parent, const string & node, int value, bool force = false);
		xmlElement * StoreValue(xmlElement *parent, const string & subn,int value, bool force = false);
		xmlElement * StoreValueNs(const string & coors, int value, bool force = false);
		
		int Value(const string & parent, const string & node, int defval);
		int Value(xmlElement *parent, int defval);
		int Value(xmlElement *parent, const string & name, int defval);
		int ValueNs(const string & coors, int defval);
		//@}
		
		//@}
		
		/** @name Nodes operations
		 * Delete, enumerate etc. 
		 */
		//@{
		
		/*! \fn xmlElement *Root()
		 * \brief Return point at the root node
		 *
		 * \return pointer at the root node
		 * \sa NodeAt, Children, NodeName
		 */
		xmlElement *Root();
		
		/*! \fn xmlElement *NodeAt(const string & coors);
		 * \brief return pointer at node on <i>coors</i>
		 *
		 * \param coors Coordinates to specified node
		 * \return pointer
		 */
		xmlElement *NodeAt(const string & coors);
		xmlElement *NodeAt(xmlElement *parent, const string & name);
		vector<xmlElement *> Children(const string & parent);
		vector<xmlElement *> Children(xmlElement *parent);
		vector<xmlElement *> Children(xmlElement *parent, const string name);
		string NodeName(xmlElement *p);
		void DeleteNode(xmlElement *parent);
		void DeleteNode(const string & coors);
		//@}
	private:
		void CreateDoc();
		bool TryLoad();		
		list<string> ParseCoors(const string & coors);
		xmlElement *ProcessNodesCreate(const list<string> & v, bool create = true);
		bool NodeExists(xmlElement *parent, const string & name, int index = 0);
		xmlElement * _rootNode;
        xmlParser * _parser;
		string _file;
};

#endif /* __X_CONFIG_H */

