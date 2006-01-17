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
#include <wx/fl/controlbar.h>
#include <wx/fl/barhintspl.h>
#include <wx/fl/hintanimpl.h>
#include <wx/fl/controlbar.h>
#include <wx/fl/gcupdatesmgr.h>
#include <wx/fl/antiflickpl.h>
#include <wx/fl/barhintspl.h>
#include <wx/fl/rowdragpl.h>
#include <onir/oOniria.h>
#include <onir/oConfig.h>
#include "gFrame.h"
#include "gBottomBar.h"
#include "gTopBar.h"
#include "oSessionManager.h"
#include "oEventManager.h"
#include "oTabManager.h"
#include "gApp.h"


#define CMD_START 0x1000l
#define CMD_END   0xf000l
#define CMD_ERROR 0xffffl

#define BOTTOM_PANEL_HEIGHT 25
#define BOTTOM_PANEL_GAP_X 1
#define BOTTOM_PANEL_GAP_Y 1
#define BOTTOM_PANEL_NAME "Bottom Panel"

#define TOP_PANEL_HEIGHT 26
#define TOP_PANEL_GAP_X 1
#define TOP_PANEL_GAP_Y 1
#define TOP_PANEL_NAME "Top Panel"

BEGIN_EVENT_TABLE(gFrame, wxFrame) 
	EVT_SIZE(gFrame::OnSize)
	EVT_COMMAND_RANGE(CMD_START,CMD_END,wxEVT_COMMAND_BUTTON_CLICKED,gFrame::OnCommandRange)
	EVT_IDLE(gFrame::OnIdle)
END_EVENT_TABLE()

class glUpdateManager: public cbGCUpdatesMgr {
	public:
		void OnStartChanges();
		void OnFinishChanges();
};

void glUpdateManager::OnStartChanges(){
	cbGCUpdatesMgr::OnStartChanges();
}

void glUpdateManager::OnFinishChanges(){
	cbGCUpdatesMgr::OnFinishChanges();
	BarArrayT ba=mpLayout->GetBars();
	gDockBarBase * p;
	for (size_t i=0;i<ba.Count();i++){
		cbBarInfo & bar = *ba[i]; 
		p=reinterpret_cast<gDockBarBase*>(bar.mpBarWnd);
		if ((bar.mState==wxCBAR_DOCKED_HORIZONTALLY)||(bar.mState==wxCBAR_FLOATING))
			p->DockType(wxHORIZONTAL);
		else if (bar.mState==wxCBAR_DOCKED_VERTICALLY){
			p->DockType(wxVERTICAL);
		}	
		p->Reorganize();
	}
}

gFrame::gFrame(wxWindow * parent,const wxString & name,long style,const wxPoint &pos,const wxSize & size, wxWindowID id, gApp * a )
:wxFrame(parent, id, name, pos, size)
{
	_app = a;
	
	Move(
		_app->Config()->ValueNs("main_window/x_pos", wxDefaultPosition.x), 
		_app->Config()->ValueNs("main_window/y_pos", wxDefaultPosition.y)
	);
	
	SetSize( 
		_app->Config()->ValueNs("main_window/width", 200), 
		_app->Config()->ValueNs("main_window/height", 600)
	);
	
	glUpdateManager * g_up=new glUpdateManager();
	_general=new wxPanel(this);	
	_layout = new wxFrameLayout(this,_general);
	_layout->SetUpdatesManager(g_up);
	_layout->PushDefaultPlugins(); 
	_layout->AddPlugin(CLASSINFO(cbAntiflickerPlugin));
	_layout->AddPlugin(CLASSINFO(cbBarHintsPlugin)); 
	_layout->AddPlugin(CLASSINFO(cbRowDragPlugin));
	
	cbDimInfo sizes_b( size.GetWidth(),BOTTOM_PANEL_HEIGHT,  // when docked horizontally      
                     size.GetWidth(),BOTTOM_PANEL_HEIGHT,	    // when docked vertically        
                     size.GetWidth(),BOTTOM_PANEL_HEIGHT-2,    // when floated                  
                     true,									 // the bar is fixed-size
                     BOTTOM_PANEL_GAP_X,         			 // vertical gap (bar border)
                     BOTTOM_PANEL_GAP_Y          			 // horizontal gap (bar border)
                   );
 	_layout->AddBar(new gBottomBar(_app, this), sizes_b, FL_ALIGN_BOTTOM, 0, 0, BOTTOM_PANEL_NAME, true);
 	
    cbDimInfo sizes_t( size.GetWidth(),TOP_PANEL_HEIGHT+2,  // when docked horizontally      
                     size.GetWidth(),TOP_PANEL_HEIGHT,    // when docked vertically        
                     size.GetWidth()-10,TOP_PANEL_HEIGHT-6,    // when floated                  
                     true, 								 // the bar is fixed-size
                     TOP_PANEL_GAP_X,         			 // vertical gap (bar border)
                     TOP_PANEL_GAP_Y          			 // horizontal gap (bar border)
                   );
 	_layout->AddBar(new gTopBar(_app, this),sizes_t, FL_ALIGN_TOP,0,0,TOP_PANEL_NAME,true); 	
}
gFrame::~gFrame()
{
	_app->Config()->StoreValueNs("main_window/x_pos", this->GetPosition().x);
	_app->Config()->StoreValueNs("main_window/y_pos", this->GetPosition().y);
	
	_app->Config()->StoreValueNs("main_window/width", this->GetSize().GetWidth());
	_app->Config()->StoreValueNs("main_window/height", this->GetSize().GetHeight());
	
	if ( _layout ) 
        delete _layout;
}

void gFrame::OnSize(wxSizeEvent & event)
{
     wxFrame::OnSize(event);
}

void gFrame::OnCommandRange(wxCommandEvent & event)
{
	wxMessageBox("Command Range");	
}

void gFrame::OnIdle(wxIdleEvent & event)
{
	_app->SessionManager()->Poll();
	_app->EventManager()->ProcessQueue();
#if defined(WIN32)
	event.RequestMore();
	wxMilliSleep(1);
#endif
}

long gFrame::FreeCmd()
{
	for (long i = CMD_START; i<= CMD_END; i++){
		if (_used_commands.find(i) == _used_commands.end()){
			_used_commands.insert(i);
			return i;
		}
	}
	return CMD_ERROR;
}

