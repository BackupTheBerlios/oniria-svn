/* $Id: rcImage.h 376 2005-08-19 13:34:46Z choman $ */
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
#ifndef __RCIMAGE_H
#define __RCIMAGE_H

#include "../dll.h"
#include <map>
#include <wx/image.h>
#include "rcFileResource.h"

using namespace std;

namespace onirRC {

/*!\class rcImage
 * \brief Image resource.
 */
class LIBONIR_API rcImage : public rcFileResource {
	public:

		/*!\name Constructors and destructor
		 */
		//@{

		/*!\fn rcImage(oOniria * o)
		 * \brief Constructor.
		 * \param o oOniria pointer.
		 */
		rcImage(oOniria * o);

		/*!\fn virtual ~rcImage()
		 * \brief Destructor.
		 */
		virtual ~rcImage();
		//@}



		/*!\fn virtual wxImage * Load()
		 * \brief Loads image.
		 * \return Pointer to wxImage.
		 */
		virtual wxImage * Load();

	private:

		DECLARE_OOBJECT;
};

};

#endif

