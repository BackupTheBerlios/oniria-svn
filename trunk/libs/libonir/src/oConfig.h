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
 
#ifndef __O_CONFIG_H
#define __O_CONFIG_H

/*!\file oConfig.h
 * 
 * \sa oConfig
 */

#include <vector>
#include <list>
#include "oObject.h"

using std::vector;
using std::list;
using std::pair;


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
class LIBONIR_API oConfig  : public oObject 
{
	public:
		oConfig();
		/** @name Data manipulation
		 * Store and Loads data values, properties etc.
		 */
		//@{
		
		/** @name string manipulation 
		 * Store and Loads string values
		 */
		//@{
		virtual xmlElement * StoreValue(const string & parent, const string & node, const string & value, bool force = false) = 0;
		virtual xmlElement * StoreValue(xmlElement * parent, const string & subn,const string & value, bool force = false) = 0;
		virtual xmlElement * StoreValueNs(const string & coors, const string & value, bool force = false) = 0;
		
		virtual string Value(const string & parent, const string & node, const string & defval) = 0;
		virtual string Value(xmlElement * parent, const string & defval) = 0;
		virtual string Value(xmlElement * parent, const string & name, const string & defval) = 0;
		virtual string ValueNs(const string & coors, const string & defval) = 0;
		//@}
		
		/** @name numbers manipulation 
		 * Store and Loads integer values
		 */
		//@{
		virtual xmlElement * StoreValue(const string & parent, const string & node, int value, bool force = false) = 0;
		virtual xmlElement * StoreValue(xmlElement * parent, const string & subn,int value, bool force = false) = 0;
		virtual xmlElement * StoreValueNs(const string & coors, int value, bool force = false) = 0;
		
		virtual int Value(const string & parent, const string & node, int defval) = 0;
		virtual int Value(xmlElement * parent, int defval) = 0;
		virtual int Value(xmlElement * parent, const string & name, int defval) = 0;
		virtual int ValueNs(const string & coors, int defval) = 0;
		//@}
		
		//@}
		
		/** @name Nodes operations
		 * Delete, enumerate etc. 
		 */
		//@{
		
		/*! \fn virtual xmlElement * Root() = 0;
		 * \brief Return point at the root node
		 *
		 * \return pointer at the root node
		 * \sa NodeAt, Children, NodeName
		 */
		virtual xmlElement * Root() = 0;
		
		/*! \fn virtual xmlElement * NodeAt(const string& coors) = 0;
		 * \brief return pointer at node on <i>coors</i>
		 *
		 * \param coors Coordinates to specified node
		 * \return pointer or NULL if not fount
		 */
		virtual xmlElement * NodeAt(const string & coors) = 0;
		
		/*! \fn virtual xmlElement * NodeAt(xmlElement * parent, const string & name) = 0;
		 * \brief return pointer at node on <i>coors</i>
		 *
		 * \param parent Parent node
		 * \param name Coordinates to specified node
		 * \return pointer or NULL if not found
		 */
		virtual xmlElement * NodeAt(xmlElement * parent, const string & name) = 0;
		
		
		/*! \fn virtual list<xmlElement *> Children(const string & parent) = 0;
		 * \brief enums children nodes
		 *
		 * \param parent Coordinates to parent node
		 * \return vector of child nodes
		 * \sa Children
		 */
		virtual vector<xmlElement *> Children(const string & parent) = 0;
		
		/*! \fn virtual list<xmlElement *> Children(xmlElement * parent) = 0;
		 * \brief enums children nodes
		 *
		 * \param parent Coordinates to parent node
		 * \return vector of child nodes
		 * \sa Children
		 */
		virtual vector<xmlElement *> Children(xmlElement * parent) = 0;
		 
		/*! \fn virtual list<xmlElement *> Children(xmlElement * parent, const string name) = 0;
		 * \brief enums children nodes
		 *
		 * \param parent Coordinates to parent node
		 * \param name Name nodes, only nodes with this name will be returned
		 * \return vector of child nodes
		 * \sa Children
		 */
		virtual vector<xmlElement *> Children(xmlElement * parent, const string name) = 0;
		
		/*! \fn virtual string NodeName(xmlElement * p) = 0;
		 * \brief returns node name
		 */
		virtual string NodeName(xmlElement * p) = 0;
		virtual void DeleteNode(xmlElement * parent) = 0;
		virtual void DeleteNode(const string & coors) = 0;
		//@}
		DECLARE_OOBJECT
};

}
#endif /* __O_CONFIG_H */

