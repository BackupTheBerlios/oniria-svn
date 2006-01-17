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

#include <wx/image.h>
#include "../decoders/decoderGIF.h"
#include "guiAnimate.h"

namespace onirGUI{

#define TIMER 0x10

BEGIN_EVENT_TABLE(guiAnimate, wxControl)
	EVT_TIMER(TIMER, guiAnimate::OnTimer)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(guiAnimate, wxControl) 



class AnimTimer : public wxTimer
{
public:   
    AnimTimer(guiAnimate* a) {_base = a;}    
    //void Notify(){
    	//_base->PlayFrames();
    //}
    guiAnimate* _base;
};




guiAnimate::guiAnimate()
{
	_currentFrame = 0;
	_firstFrame = 0;
	_lastFrame = 0;
	_loop = true;
	_state = stop;
	_decoder  = NULL;
	_timer = new AnimTimer(this);//
	_timer->SetOwner(this, TIMER);
}

guiAnimate::~guiAnimate()
{
	delete _decoder;
	delete _timer;
}


bool guiAnimate::Create(wxWindow *parent, 
	wxWindowID id, 	
	const wxPoint& pos, 
	const wxSize& size, 
	long style,                      
	const wxValidator& validator,  
	const wxString & name){
	
	if ( !CreateControl(parent, id, pos, size, style, validator, name) )
      return false;
              
	return true;	
}

bool guiAnimate::Data(wxInputStream * is, const string & type)
{
	if (type == "GIF")
		_decoder = new onirDecoders::decoderGIF();	
	return _decoder->Init(is);
}

void guiAnimate::PlayFrames()
{	
	wxBitmap _buffer(GetSize().GetWidth(), GetSize().GetHeight());
	
	wxMemoryDC dc;	
	dc.SelectObject(_buffer);
	DrawFrame(dc, GetPosition(), _currentFrame);		
	_timer->Start(_decoder->FrameDelay(_currentFrame), true);
	_currentFrame++;
	wxLogVerbose("Play Frame for frame %d", _currentFrame);
	if (_currentFrame == _lastFrame){
		if (_loop){
			_currentFrame = _firstFrame;
		}else{
			Stop();
		}
		
	}	
	dc.SelectObject(wxNullBitmap);	
	
	wxClientDC winDC(this);
	//winDC.DrawBitmap(_buffer, GetPosition().x, GetPosition().y);
	winDC.DrawBitmap(_buffer, 1,1);
	
}

void guiAnimate::Play()
{
	wxLogVerbose("1");
	_lastFrame = _decoder->Count();
	_firstFrame = 0;
	_currentFrame = 0;
	wxLogVerbose("2");
	int id = _decoder->FrameDelay(_currentFrame);
	wxLogVerbose("%d", id);
	_timer->Start(100, true);//id);	
	wxLogVerbose("3");
	_state = play;	
}

void guiAnimate::Stop()
{
	_timer->Stop();
	_state = stop;
}

void guiAnimate::Pause()
{
	if (_state == pause){
		_timer->Start(_decoder->FrameDelay(_currentFrame));
		_state = play;	
	}else{
		_timer->Stop();
		_state = pause;
	}
	
}

void guiAnimate::DrawFrame(wxDC & dc, const wxPoint &point, size_t frame)
{	
	wxImage image;
	_decoder->Frame(&image, frame);
	wxBitmap bmp(image);	
	dc.DrawBitmap(bmp, point.x, point.y, (bmp.GetMask() != NULL)); 
}

void guiAnimate::OnTimer(wxTimerEvent &event)
{
	wxLogVerbose("guiAnimate::OnTimer");
	PlayFrames();
}

};
