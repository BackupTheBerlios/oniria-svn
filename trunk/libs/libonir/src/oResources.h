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
#ifndef __ORESOURCES_H
#define __ORESOURCES_H

#include "dll.h"

#include <string>
#include <wx/image.h>
#include "oObject.h"
#include "rc/rcResource.h"
#include "rc/rcImage.h"
#include "rc/rcSkin.h"

using std::string;
using onirRC::rcResource;
using onirRC::rcSkin;

namespace onir {

/*!\class oResources
 * \brief Interface to resource manager.
 */
class LIBONIR_API oResources : public oObject {

	public:
		/*!\name Contructors and destructor
		 */
		//@{

		/*!\fn oResources()
		 * \brief Constructor.
		 */
		oResources();
		//@}
		


		/*!\fn virtual rcResource * Resource(const string& id, const string& type)
		 * \brief Finds resource with given id and type.
		 * \param id Resource id.
		 * \param type Resource type.
		 * \return Resource pointer or null if resource is not found.
		 * \sa onirRC::rcResource
		 */
		virtual rcResource * Resource(const string& id, const string& type) = 0;
		
		/*!\fn virtual wxImage * Image(const string& id, const string& imageset = "") = 0
		 * \brief Finds image.
		 * \param id Image id.
		 * \param imageset Imageset name.
		 * \return Pointer to image or null if resource is not found.
		 * \sa onirRC::rcImage, Resource(),
		 *
		 * If imageset is an empty string, id should be full resource id, otherwise
		 * id is relative to imageset resource id.
		 */
		virtual wxImage * Image(const string& id, const string& imageset = "") = 0;

		/*!\fn virtual rcSkin * Skin(const string& id) = 0
		 * \brief Returns pointer to skin with given id.
		 * \param id Skin id.
		 * \return Skin pointer.
		 */
		virtual rcSkin * Skin(const string& id) = 0;

		/*!\fn virtual rcSkin * Skin() = 0
		 * \brief Returns pointer to active skin.
		 * \param id Skin id.
		 * \return Skin pointer.
		 */
		virtual rcSkin * Skin() = 0;

		DECLARE_OOBJECT;
};



};

#endif
