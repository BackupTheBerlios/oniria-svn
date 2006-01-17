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

#if defined(HAVE_CONFIG_H)
# include <config.h>
#endif

#include <wx/gifdecod.h>
#include "decoderGIF.h"

namespace onirDecoders{
	
DEFINE_OOBJECT(decoderGIF, oObject);

decoderGIF::decoderGIF()
{
	INIT_OOBJECT;
	type("decoderGIF");
	name("decoderGIF");	
	_decoder = NULL;	
}

decoderGIF::~decoderGIF()
{
	delete _decoder;
}

bool decoderGIF::Init(wxInputStream * is)
{
	if (_decoder)
		delete _decoder;
	_decoder = new wxGIFDecoder(is, true);
	if (_decoder->ReadGIF() != wxGIF_OK){
		delete _decoder;
		_decoder = NULL;
		return false;
	}
	if (!_decoder->IsAnimation())
		wxLogVerbose("GIF Is Not Anim");
	else
		wxLogVerbose("GIF Is Anim with %d frames", Count());
	return true;
}

bool decoderGIF::Frame(wxImage * image, int frame)
{
	if (_decoder != NULL){
		_decoder->GoFrame(frame);
		_decoder->ConvertToImage(image);
		return true;
		
	}
	return false;
}

int decoderGIF::Count()
{
	if (_decoder != NULL)	
		return _decoder->GetNumberOfFrames();
	return 0;
}

int decoderGIF::FrameDelay(int frame)
{
	if (_decoder != NULL){		
		_decoder->GoFrame(frame + 1);		
		wxLogVerbose("decoderGIF::FrameDelay(%d)", frame);		
		return _decoder->GetDelay();
		
	}
	return 1;
}

wxSize decoderGIF::LogicalSize()
{
	if (_decoder != NULL){
;		return wxSize(_decoder->GetLogicalScreenWidth(), _decoder->GetLogicalScreenHeight());		
	}
	return wxSize();
}

wxRect decoderGIF::FrameSize(int frame)
{
	if (_decoder != NULL){
		_decoder->GoFrame(frame);
		return wxRect(_decoder->GetLeft(), _decoder->GetTop(), _decoder->GetWidth(), _decoder->GetHeight());
	}
	return wxRect();
}

wxColour decoderGIF::TransparentColour()
{
	if (_decoder != NULL){
		return _decoder->GetTransparentColour();
	}
	return "WHITE";	
}

};
