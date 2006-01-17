/* $Id: rcResource.h 369 2005-08-19 09:52:51Z choman $ */
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
#ifndef __RCRESOURCE_H
#define __RCRESOURCE_H

#include <string>
#include <set>
#include "../oObject.h"
#include "../oOniria.h"
#include "../xml/xmlElement.h"

using onir::oObject;
using onir::oOniria;
using onirXML::xmlElement;
using namespace std;

namespace onirRC {

class rcPack;

/*!\class rcResource
 * \brief Resource entity.
 */
class LIBONIR_API rcResource : public oObject {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn rcResource(oOniria * o)
		 * \brief Constructor.
		 * \param o oOniria pointer.
		 */
		rcResource(oOniria * o);

		/*!\fn virtual ~rcResource()
		 * \brief Destructor.
		 */
		virtual ~rcResource();
		//@}



		/*!\fn virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml)
		 * \brief Preloads resource.
		 * \param file Name of resource file.
		 * \param owner Owner of resource.
		 * \param xml Resource XML description.
		 * \return true if ok
		 */
		virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml);

		/*!\fn inline xmlElement * XML() const
		 * \brief Returns XML element describing resource.
		 * \return Pointer to XML element.
		 */
		inline xmlElement * XML() const { return _xml; };

		/*!\fn string Id() const
		 * \brief Returns full id of resource.
		 * \return Resource id.
		 */
		string Id() const;

		/*!\fn inline const string& File() const
		 * \brief Returns resource file name in which resource is contained.
		 * \return Resource file name.
		 */
		inline const string& File() const { return _file; };

		/*!\fn inline const string& Type() const
		 * \brief Returns resource type.
		 * \return Resource type.
		 */
		inline const string& Type() const { return _type; };

		/*!\fn inline rcPack * Owner() const
		 * \brief Returns resource owner.
		 * \return Resource owner.
		 */
		inline rcPack * Owner() const { return _owner; };
		
		/*!\fn inline oOniria * Oniria() const
		 * \brief Returns oOniria pointer.
		 * \return oOniria pointer.
		 */
		inline oOniria * Oniria() const { return _oniria; };

	private:
		string _type;
		string _id;
		xmlElement * _xml;
		set<xmlElement *> _xmls;
		rcPack * _owner;
		string _file;
		oOniria * _oniria;

		DECLARE_OOBJECT;
};

};

#endif

