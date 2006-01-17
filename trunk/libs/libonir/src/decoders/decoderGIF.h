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


#ifndef __DECODER_GIF__
#define __DECODER_GIF__

#include "../dll.h"
#include "decoderBase.h"

class wxGIFDecoder;

namespace onirDecoders{

class LIBONIR_API decoderGIF : public decoderBase{
	public:
		/*!\name Constructors and destructor
		 * @{
		 */

		/*!\fn decoderGIF()
		 * \brief Constructor
		 */
		decoderGIF();
		
		/*!\fn ~decoderGIF()
		 * \brief Constructor
		 */
		~decoderGIF();
		/* @} */
		
		virtual bool Init (wxInputStream * is);
		virtual bool Frame(wxImage * image, int frame);
		virtual int Count();
		virtual int FrameDelay(int frame);
		virtual wxSize LogicalSize();
		virtual wxRect FrameSize(int frame);
		virtual wxColour TransparentColour();
	private:
		wxGIFDecoder *_decoder;
		
	DECLARE_OOBJECT;

};

};

#endif /* __DECODER_GIF__ */
