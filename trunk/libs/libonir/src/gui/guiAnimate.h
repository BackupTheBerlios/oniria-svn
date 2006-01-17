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
 
#ifndef __GUI_ANIMATE_H__
#define __GUI_ANIMATE_H__

#include "../dll.h"
#include <vector>
#include <string>


using std::vector;
using std::string;


namespace onirDecoders{
	class decoderBase;		
};

using onirDecoders::decoderBase;

namespace onirGUI{

class AnimTimer;
	
	
/*!\class guiAnimate
 *\brief Dispaly animate sequences
 */
class LIBONIR_API guiAnimate: public wxControl {
	public: 
		enum state{
			play,
			stop,
			pause
		};
			
		/*!\name Contructors and destructor
		 */
		//@{
		/*!\fn guiAnimate()
		 * \brief Constructor
		 */
		 guiAnimate();
		 
 		/*!\fn ~guiAnimate()
		 * \brief Constructor
		 */
		 ~guiAnimate();

		 //@}
		 
		 
		 /*!\fn void Play()
		  *\brief Play sequence
		  */
		 void Play();
		 
		 /*!\fn void Stop()
		  *\brief Stop sequence
		  */
		void Stop();
		
		 /*!\fn void Pause()
		  *\brief Pause sequence
		  */
		void Pause();		
		 
		 void Loop(bool b) { _loop = b; };
		 bool Loop() const { return _loop; };			 
		 
		 bool Data(wxInputStream * is, const string & type);
			 
		bool Create(wxWindow *parent, 
			wxWindowID id, 	
			const wxPoint& pos, 
			const wxSize& size, 
			long style,                      
			const wxValidator& validator,  
			const wxString & name);
	protected:
		void OnTimer(wxTimerEvent &event);
	private:
		void DrawFrame(wxDC & dc, const wxPoint &point, size_t frame);
		void PlayFrames();
		AnimTimer * _timer;
		size_t _currentFrame;
		size_t _firstFrame;
		size_t _lastFrame;
		bool _loop;		
		state _state;
		decoderBase * _decoder;
		friend class AnimTimer;
		DECLARE_EVENT_TABLE();
		DECLARE_DYNAMIC_CLASS_NO_COPY(guiAnimate)

	
};

};

#endif /* __GUI_ANIMATE_H__ */
