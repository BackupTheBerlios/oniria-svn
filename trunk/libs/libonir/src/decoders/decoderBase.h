/* $Id: decoderBase.h 614 2005-12-29 16:44:50Z choman $ */
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

#ifndef _DECODERBASE_H
#define _DECODERBASE_H
#include "../dll.h"
#include "../oObject.h"

using onir::oObject;
namespace onirDecoders {

// Need porting to QT
#if 0

class LIBONIR_API decoderBase : public oObject
{
	public:
		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn decoderBase()
		 * \brief Constructor
		 */
		decoderBase();

		/*!\fn ~decoderBase()
		 * \brief Constructor
		 */
		virtual ~decoderBase();
		/* @} */

		/*!\fn virtual void Init (wxImputStream * is)
		 * \brief Initialize decoder for given stream.
		 */
		virtual bool Init (wxInputStream * is) = 0;

		/*!\fn virtual wxImage * Frame(int frame) = 0
		 * \brief Return single frame
		 * \param stream of data to decode
		 * \return true if success
		 */
		virtual bool Frame(wxImage * image, int frame) = 0;

		/*!\fn virtual int Count() = 0
		 * \brief Returns Count frames
		 * \
		 */
		virtual int Count() = 0;

		/*!\fn virtual int FrameDelay(int frame)
		 * \brief Return Delay for frame
		 */
		virtual int FrameDelay(int frame) { return 0; }

		/*!\fn virtual wxSize LogicalSize()
		 * \brief Return size whole animate
		 */
		virtual wxSize LogicalSize() = 0;

		/*!\fn virtual wxRect FrameSize(int frame)
		 * \brief return single frame rect;
		 */
		virtual wxRect FrameSize(int frame) { return wxRect(); };

		/*!\fn virtual wxColour TransparentColour()
		 * \brief return global transparent colour
		 */
		virtual wxColour TransparentColour() { return "BLACK"; };



	DECLARE_OOBJECT;
};

#endif

};

#endif
