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
#ifndef __RCPACK_H
#define __RCPACK_H

#include "../dll.h"
#include <map>
#include "rcResource.h"

using namespace std;

namespace onirRC {

class LIBONIR_API rcPack : public rcResource {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn rcPack(oOniria * o)
		 * \brief Constructor.
		 * \param o oOniria pointer.
		 */
		rcPack(oOniria * o);

		/*!\fn virtual ~rcPack()
		 * \brief Destructor.
		 */
		virtual ~rcPack();
		//@}


		
		/*!\fn virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml)
		 * \brief Preloads resource.
		 * \param file Name of resource file.
		 * \param owner Owner of resource.
		 * \param xml Resource XML description.
		 * \return true if ok
		 */
		virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml);

		/*!\fn virtual rcResource * Resource(const string& id, const string& type)
		 * \brief Finds resource with given id and type.
		 * \param id Resource id.
		 * \param type Resource type.
		 * \return Resource pointer or null if resource is not found.
		 */
		virtual rcResource * Resource(const string& id, const string& type);

	private:
		map<string, map<string, rcResource *> > _resources;	// <type, <id, resource> >
		list<xmlElement *> _elements;

		DECLARE_OOBJECT;
};

};

#endif

