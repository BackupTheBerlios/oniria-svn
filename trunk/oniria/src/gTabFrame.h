
#ifndef __GTABFRAME_HPP_
#define __GTABFRAME_HPP_


#include <wx/frame.h>


class gTabFrame : public wxFrame
{

 public:
    gTabFrame(wxWindow *parent);
    virtual ~gTabFrame();
    protected:
    	void OnClose(wxCloseEvent &event);
	private:
    DECLARE_EVENT_TABLE()
};


#endif
 
 
 
 
