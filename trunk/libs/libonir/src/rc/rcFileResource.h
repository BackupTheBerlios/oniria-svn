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
#ifndef __RCFILERESOURCE_H
#define __RCFILERESOURCE_H

#include "../dll.h"
#include <map>
#include <wx/filesys.h>
#include "rcResource.h"

using namespace std;

namespace onirRC {

/*!\class rcFileResource
 * \brief Resource loaded from file.
 */
class LIBONIR_API rcFileResource : public rcResource {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn rcFileResource(oOniria * o)
		 * \brief Constructor.
		 * \param o oOniria pointer.
		 */
		rcFileResource(oOniria * o);

		/*!\fn virtual ~rcFileResource()
		 * \brief Destructor.
		 */
		virtual ~rcFileResource();
		//@}


		
		/*!\fn virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml)
		 * \brief Preloads resource.
		 * \param file Name of resource file.
		 * \param owner Owner of resource.
		 * \param xml Resource XML description.
		 * \return true if ok
		 */
		virtual bool Prepare(const string& file, rcPack * owner, xmlElement * xml);

		/*!\fn virtual wxFSFile * Open()
		 * \brief Opens file.
		 * \return Pointer to wxFSFile.
		 */
		virtual wxFSFile * Open();

	private:
		string _location;

		DECLARE_OOBJECT;
};

};

#endif

