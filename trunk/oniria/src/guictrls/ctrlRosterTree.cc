/* $Id: ctrlRosterTree.cc 628 2006-01-02 11:16:03Z choman $ */
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

#include <onir/utils/uDraw.h>
#include "../gApp.h"
#include "../oResourceManager.h"
#include "ctrlRosterTree.h"

using onirUtils::uDraw;
 

#define SPACE_TEXT_IMAGE 2

#define TIMER_ID 0x01

class scrollCanvas : public wxPanel{
	public:
		 scrollCanvas(wxScrolledWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
		 scrollCanvas(){}
	private:
		 wxScrolledWindow   *_owner;
		DECLARE_DYNAMIC_CLASS(scrollCanvas)
};

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_MOUSE_CLICK, 0x01)
	DECLARE_EVENT_TYPE(wxEVT_MOUSE_MOVE, 0x02)	
END_DECLARE_EVENT_TYPES()

DEFINE_EVENT_TYPE(wxEVT_MOUSE_CLICK)
DEFINE_EVENT_TYPE(wxEVT_MOUSE_MOVE)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_MOUSE_DB_CLICK)

BEGIN_EVENT_TABLE(ctrlRosterTreeItem, wxPanel)
	EVT_PAINT(ctrlRosterTreeItem::OnPaint)
	EVT_MOUSE_EVENTS(ctrlRosterTreeItem::OnMouseDown)
	EVT_TIMER(TIMER_ID, ctrlRosterTreeItem::OnTimer)
END_EVENT_TABLE()



ctrlRosterTreeItem::ctrlRosterTreeItem(wxWindow * parent)
		:wxPanel(parent, -1, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN)
{
	_timer.SetOwner(this, TIMER_ID);
	
	_normal_i = NULL;
	_expanded_i = NULL;
	
	_title = "";
	
	_expanded = false;
	_selected = false;
	
	_hidden = false;
	
	Show(false);
	
	_title_fnt.SetWeight(wxFONTWEIGHT_BOLD); 
	_title_fnt.SetPointSize(8);
	_desc_fnt.SetPointSize(7);
	
	_skin = "roster:item";
	
	_lastClick = wxPoint(0, 0);
	
}

ctrlRosterTreeItem::~ctrlRosterTreeItem()
{
	if (_normal_i)
		delete _normal_i;
	if (_expanded_i)
		delete _expanded_i;
	
}

void ctrlRosterTreeItem::NormalIcon(wxImage * i)
{ 
	_normal_i = i; 	
	if (_normal_i){
		_normal_i->SetMask(true);
		_normal_i->SetMaskColour(_normal_i->GetRed(0, 0), _normal_i->GetGreen(0, 0), _normal_i->GetBlue(0, 0));
	}
}

void ctrlRosterTreeItem::ExpandedIcon(wxImage * i)
{
	_expanded_i = i; 
	if (_expanded_i){
		_expanded_i->SetMask(true);
		_expanded_i->SetMaskColour(_expanded_i->GetRed(0, 0), _expanded_i->GetGreen(0, 0), _expanded_i->GetBlue(0, 0));
	}
	
}

void ctrlRosterTreeItem::Title(const string & s)
{	
	_title = s;
};

void ctrlRosterTreeItem::Description(const string & s)
{
	_description = s;
};

void ctrlRosterTreeItem::OnTimer(wxTimerEvent& event)
{

}

ctrlRosterTreeItem::clickPlace ctrlRosterTreeItem::ClickPlace()
{
	if (_imageRect.Inside(_lastClick))
		return image;
	if (_titleRect.Inside(_lastClick))
		return title;
	if (_descriptionRect.Inside(_lastClick))
		return description;
	return unknown;
}

string ctrlRosterTreeItem::Skin() const
{
	if (_selected && _expanded) {
		return _skin + ":selected-e";
	} else if (_selected && !_expanded) {
		return _skin + ":selected";
	} else if (!_selected && _expanded) {
		return _skin + ":normal-e";
	} else if (!_selected && !_expanded) {
		return _skin + ":normal";
	}
	return _skin;
}

string ctrlRosterTreeItem::Skin(const string& id) const
{
	return Skin() + ":" + id;
}

void ctrlRosterTreeItem::DrawBkGround(wxDC & dc)
{
	wxSize s = GetSize();
	wxColour from, to;
	from = wxGetApp().ResourceManager()->Skin()->ColourValue(Skin("background:gradient:from"));
	to = wxGetApp().ResourceManager()->Skin()->ColourValue(Skin("background:gradient:to"));

	if (from == to) 
		uDraw::Get()->DrawSingleColour(dc, wxRect(wxPoint(0, 0), s), from);
	else
		uDraw::Get()->DrawVerticalGradient(dc, wxRect(wxPoint(0, 0), s), from, to);
	
}

wxSize ctrlRosterTreeItem::DrawImage(wxDC & dc, const wxPoint & p, bool draw)
{
	wxImage * i;
	if (_expanded)
		i = _expanded_i;
	else
		i = _normal_i;

	if ((i != NULL) && (i->Ok())){
		wxBitmap b(*i);
		if (draw){			
			dc.DrawBitmap(b, p.x, p.y, true);
		}
		wxSize sz = wxSize(b.GetWidth() + SPACE_TEXT_IMAGE, b.GetHeight());
		_imageRect = wxRect(p, sz);
		return sz;
	}
	_imageRect = wxRect();
	return wxSize(0, 0);
}

void ctrlRosterTreeItem::SkinRoot(const string& s)
{
	_skin = s;
	SetupFonts();
}
	
void ctrlRosterTreeItem::SetupFonts()
{
	wxGetApp().ResourceManager()->Skin()->SetupFont(&_title_fnt, Skin("title:font"));
	wxGetApp().ResourceManager()->Skin()->SetupFont(&_desc_fnt, Skin("description:font"));
}

wxSize ctrlRosterTreeItem::Draw(bool draw)
{	
	wxClientDC dc(this);	
    
	int scroll_x = 0;
	int scroll_y = 0;
	_owner->CalcUnscrolledPosition(scroll_x, scroll_y, &scroll_x, &scroll_y);    
	int size_x = 0;
	int size_y = 0;
	GetParent()->GetClientSize(&size_x, &size_y);				

	wxSize s = GetSize();
	wxPoint p = GetPosition();
	
	if (draw &&
		(p.x + s.GetWidth() - scroll_x > 0) &&
		(p.y + s.GetHeight() - scroll_y > 0) &&
		(p.x - scroll_x < size_x) &&
		(p.y - scroll_y <size_y)
	){
		draw = true;	
	}else
		draw = false;	
	
	int tx = 0, ty = 0, dx = 0, dy = 0;
	int gx = 1;
	int gy = 1;

	gx = wxGetApp().ResourceManager()->Skin()->IntValue(Skin("pad:x"), gx);
	gy = wxGetApp().ResourceManager()->Skin()->IntValue(Skin("pad:y"), gy);

	int x = gx;
	int y = gy;
	
	if (draw)
		DrawBkGround(dc);
	wxSize image = DrawImage(dc, wxPoint(x, y), draw);
	x += image.GetWidth();

	dc.SetTextForeground(wxGetApp().ResourceManager()->Skin()->ColourValue(Skin("title:colour"), wxColour("BLACK")));
	dc.SetFont(_title_fnt);
	if (draw)
		dc.DrawText(_title.c_str(), x, y);
	dc.GetTextExtent(_title.c_str(), &tx, &ty);
	_titleRect = wxRect(x, y, tx, ty);
	
	dc.SetTextForeground(wxGetApp().ResourceManager()->Skin()->ColourValue(Skin("description:colour"), wxColour("BLACK")));
	dc.SetFont(_desc_fnt);
	if (!_description.empty())
		dc.GetMultiLineTextExtent(_description.c_str(), &dx, &dy);		
	if (draw){
		dc.DrawLabel(_description.c_str(), wxRect(x, ty + y, dx, dy));			
	}
	_descriptionRect = wxRect(x, ty + y, dx, dy);
		
	int w = x + tx > x + dx ? x + tx : x + dx;
	int h = y + (dy + ty) > image.GetHeight() ? (dy + ty) : image.GetHeight();
	wxSize xs = wxSize(w + gx, h + 2 * gy);
	
	if (!draw){
		SetSize(xs);		
	}
	return xs;
}

void ctrlRosterTreeItem::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	Draw();
}

void ctrlRosterTreeItem::OnMouseDown(wxMouseEvent & event)
{
	wxCommandEvent c_event;
	c_event.SetId(GetId());
	c_event.SetEventObject(this);
	event.SetEventObject(this);
	
	_lastClick = event.GetPosition();
	
	if (event.LeftDown()){
		c_event.SetEventType(wxEVT_MOUSE_CLICK);
	}

	if (event.LeftDClick()){
		c_event.SetEventType(wxEVT_MOUSE_DB_CLICK);
	}
	event.Skip();
	GetParent()->GetEventHandler()->ProcessEvent(c_event);
	//GetParent()->GetEventHandler()->ProcessEvent(event);
}

/* ------ scrollCanvas -------- */

IMPLEMENT_DYNAMIC_CLASS(scrollCanvas, wxPanel) 

scrollCanvas::scrollCanvas(wxScrolledWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
: wxPanel( parent, id, pos, size)
{
	_owner = parent;
	SetBackgroundColour(wxGetApp().ResourceManager()->Skin()->ColourValue("roster:background"));
}

/* ----- ctrlRosterTree --------- */

BEGIN_EVENT_TABLE(ctrlRosterTree, wxScrolledWindow)
	EVT_COMMAND(-1, wxEVT_MOUSE_CLICK, ctrlRosterTree::EventFunc)
	EVT_COMMAND(-1, wxEVT_MOUSE_DB_CLICK, ctrlRosterTree::EventFunc)
	EVT_COMMAND(-1, wxEVT_MOUSE_MOVE, ctrlRosterTree::EventFunc)
	EVT_MOUSE_EVENTS(ctrlRosterTree::OnMouseDown)
END_EVENT_TABLE()

ctrlRosterTree::ctrlRosterTree(wxWindow * parent, wxWindowID id)
		:wxScrolledWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxNO_BORDER)
{
	_canvas = new scrollCanvas(this, wxID_ANY, wxDefaultPosition, GetSize());
	_canvas->SetSizeHints(wxDefaultSize);
	
	/*
	_toggleNormalIcon = NULL;
	_toggleExpandIcon = NULL;
	*/
	
	
	_root = new ctrlRosterTreeItem(_canvas);
	_root->Expanded(true);
	_root->Hidden(true);
	_root->Move(wxGetApp().ResourceManager()->Skin()->IntValue("roster:margin:left", 10), wxGetApp().ResourceManager()->Skin()->IntValue("roster:margin:top", 10));	
	_root->SetBackgroundColour(wxGetApp().ResourceManager()->Skin()->ColourValue("roster:background"));
	
	SetScrollRate(5, 5);	
	SetBackgroundColour(wxGetApp().ResourceManager()->Skin()->ColourValue("roster:background"));
	
	wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *middlesizer = new wxBoxSizer(wxHORIZONTAL);    
	middlesizer->Add(_canvas, 1, wxEXPAND); 
	mainsizer->Add(middlesizer, 1, wxEXPAND);  
       
    SetSizer(mainsizer);	
}

ctrlRosterTree::~ctrlRosterTree()
{

}

void ctrlRosterTree::Title(const string & id, const string & name, bool redraw)
{
	//wxLogVerbose("ctrlRosterTree: Title (%s)", id.c_str());
	ctrlRosterTreeItem * el = FindItem(id);
	el->Title(name);
	if (redraw)
		el->Draw();
}

void ctrlRosterTree::Description(const string & id, const string & desc, bool redraw)
{
	//wxLogVerbose("ctrlRosterTree: Description (%s)", id.c_str());
	ctrlRosterTreeItem * el = FindItem(id);
	el->Description(desc);
	if (redraw)
		DrawItems(el);
	
}

wxImage *ctrlRosterTree::NormalIcon(const string & id, wxImage * image, bool delete_old, bool redraw)
{	
	//wxLogVerbose("ctrlRosterTree: Normal Icon (%s)", id.c_str());
	ctrlRosterTreeItem * el = FindItem(id);
	wxImage * old = el->NormalIcon();
	el->NormalIcon(image);
	if (redraw)
		el->Draw();
	if (delete_old){
		delete old;
		return NULL;
	}else{
		return old;
	}
	
}

wxImage *ctrlRosterTree::ExpandedIcon(const string & id, wxImage * image, bool delete_old, bool redraw)
{
	//wxLogVerbose("ctrlRosterTree: Expand Icon (%s)", id.c_str());
	ctrlRosterTreeItem * el = FindItem(id);
	wxImage * old = el->ExpandedIcon();
	el->ExpandedIcon(image);
	if (redraw)
		el->Draw();
	if (delete_old){
		delete old;
		return NULL;
	}else{
		return old;
	}

}

/*
wxImage *ctrlRosterTree::ToggleNormalIcon(wxImage * image, bool delete_old = true)
{
	wxImage * old = _toggleNormalIcon;
	_toggleNormalIcon = image;
	if (delete_old){
		delete old;
		return NULL;
	}else{
		return old;
	}
}
wxImage *ctrlRosterTree::ToggleExpandIcon(wxImage * image, bool delete_old = true)
{
	wxImage * old = _toggleExpandIcon;
	_toggleExpandIcon = image;
	if (delete_old){
		delete old;
		return NULL;
	}else{
		return old;
	}
}
*/

void ctrlRosterTree::AddItem(const string & root, const string & id, const string & name, const string & desc, bool groupitem, wxImage * normal, wxImage * expand, bool redraw)
{
	
	ctrlRosterTreeItem * root_el = NULL;
	if (!root.empty())
		root_el = FindItem(root);

	if (!root_el)
		root_el = _root;

	ctrlRosterTreeItem * element = new ctrlRosterTreeItem(_canvas);
	element->Title(name);
	element->Description(desc);
	element->Id(id);
	element->NormalIcon(normal);
	element->ExpandedIcon(expand);
	element->Group(groupitem);
	element->SetOwner(this);

	element->Parent(root_el);
	root_el->Items()->push_back(element);
	//wxLogVerbose("ctrlRosterTree: AddItem (%s)", id.c_str());
	if (redraw)
		DrawItems(element);
	
}

void ctrlRosterTree::RemoveItem(const string & id, bool children_only, bool redraw)
{
	//wxLogVerbose("ctrlRosterTree: Remove item (%s)", id.c_str());
	ctrlRosterTreeItem * e = FindItem(id);
	if (e){
		e = e->Parent();
		for (size_t i = 0; i < e->Items()->size(); i++){
			if ((*e->Items())[i]->Id() == id){
				RemoveItems((*e->Items())[i]);
				if (!children_only){
					(*e->Items())[i]->Destroy();
					e->Items()->erase(e->Items()->begin()+i);
				}
				if (redraw)
					DrawItems();
				break;
			}
		}
	}

}

void ctrlRosterTree::Redraw(const string &from_item)
{
	ctrlRosterTreeItem * item = FindItem(from_item);
	DrawItems(item);
}

void ctrlRosterTree::DisableSelections(ctrlRosterTreeItem * root)
{
	for (vector<ctrlRosterTreeItem*>::iterator i = _selected.begin(); i!= _selected.end(); ++i){
		(*i)->Selected(false);
		(*i)->Draw();		
	}
	_selected.clear();
}

ctrlRosterTreeItem * ctrlRosterTree::FindItemHelper(ctrlRosterTreeItem * root, const string & id)
{
	ctrlRosterTreeItem * ret;
	for (vector<ctrlRosterTreeItem*>::iterator i = root->Items()->begin(); i!= root->Items()->end(); ++i){
		if ((*i)->Id() == id){
			return (*i);
		}
		if (!(*i)->Items()->empty()){
			ret = FindItemHelper(*i, id);
			if (ret)
				return ret;
		}
	}
	return NULL;
}

ctrlRosterTreeItem * ctrlRosterTree::FindItem(const string & id)
{
	if (id.empty())
		return _root;
	ctrlRosterTreeItem * r = FindItemHelper(_root, id); 
	if (r)
		return r;
	return NULL;
}

void ctrlRosterTree::DrawItems(ctrlRosterTreeItem * from)
{
	wxRect r(_root->GetPosition(), wxSize(0,0));
	_candraw = false;
	DrawItems(_root, r, true, from);		
	_canvas->SetSizeHints(r.GetSize());
	FitInside();	
}

void ctrlRosterTree::RemoveItems(ctrlRosterTreeItem * root)
{
	for (vector<ctrlRosterTreeItem*>::iterator i = root->Items()->begin(); i!= root->Items()->end(); ++i){
		if (!(*i)->Items()->empty()){
			RemoveItems(*i);
			(*i)->Items()->clear();
		}
		(*i)->Destroy();
		delete (*i);
	}
} 

void ctrlRosterTree::DrawItems(ctrlRosterTreeItem * root, wxRect & rc, bool show, ctrlRosterTreeItem * from)
{					
	if (!from || from == _root)
		_candraw = true;
	for (vector<ctrlRosterTreeItem*>::iterator i = root->Items()->begin(); i!= root->Items()->end(); ++i){
		if ((*i) == from)
			_candraw = true;
		if (!(*i)->Hidden()){
			if (show){				
				wxSize s = (*i)->Draw(false);
				(*i)->Move(rc.x, rc.y);				
				rc.y += s.GetHeight();
								
				if (rc.GetWidth() < s.GetWidth())
					rc.SetWidth(s.GetWidth());				
				rc.SetHeight(rc.y);
				
				if (_candraw){
					if (!(*i)->Show(true))
						(*i)->Draw();											
				}
			}else{
				(*i)->Show(false);
			}
		}
		if (show && (*i)->Expanded()){
			int indent;
			indent = wxGetApp().ResourceManager()->Skin()->IntValue((*i)->Skin("indent"));
			rc.x += indent;
			DrawItems(*i, rc, true);
			rc.x -= indent;
		}else{
			DrawItems(*i, rc, false);
		}
	}
}

vector<ctrlRosterTreeItem*> & ctrlRosterTree::Selected()
{
	return _selected;
}

void ctrlRosterTree::OnMouseDown(wxMouseEvent &event)
{
//	wxLogVerbose("ctrlRosterTree: Mouse Event (%d, %d, %d)", event.GetWheelDelta(), event.GetWheelRotation(), event.GetLinesPerAction());
	int step = (abs(event.GetWheelRotation()) / event.GetWheelDelta()) * event.GetLinesPerAction();
	if (event.GetWheelRotation() > 0){
		ScrollLines(-step);
	}else{
		ScrollLines(step);
	}
	event.Skip();	
}

void ctrlRosterTree::EventFunc(wxCommandEvent & event)
{
	ctrlRosterTreeItem * el = reinterpret_cast<ctrlRosterTreeItem*>(event.GetEventObject());
	if (event.GetEventType() == wxEVT_MOUSE_DB_CLICK){
		if (el->Group() || el->ClickPlace() == ctrlRosterTreeItem::image){
			el->Expanded(!el->Expanded());
			el->SetupFonts();
			DrawItems(el);		
		}else{
			event.Skip();
		}
	}
	if (event.GetEventType() == wxEVT_MOUSE_CLICK){
		if (el->ClickPlace() == ctrlRosterTreeItem::image){
			el->Expanded(!el->Expanded());
			el->SetupFonts();
			DrawItems(el);					
		}
		if (!::wxGetKeyState(WXK_CONTROL))
			DisableSelections(_root);
		el->Selected(true);		
		el->SetupFonts();
		_selected.push_back(el);
		el->Draw();		
	}	
}

bool ctrlRosterTree::Order(const string& id, const vector<string>& order, bool redraw)
{	
	ctrlRosterTreeItem * item = FindItem(id);
	vector<ctrlRosterTreeItem *> newitems;		
	vector<ctrlRosterTreeItem *> olditems = *item->Items();

	for (vector<string>::const_iterator it = order.begin(); it!= order.end(); ++it){
		for (vector<ctrlRosterTreeItem*>::iterator i = item->Items()->begin(); i!= item->Items()->end(); ++i){
			if (*it == (*i)->Id()){						
				newitems.push_back(*i);
				//item->Items()->erase(i);				
				break;
			}
		}
	}
	if (olditems != newitems) {
		item->Items()->swap(newitems);	
		if (redraw)
			Redraw(id);
		return true;
	}
	return false;
}

void ctrlRosterTree::BackgroundColour(const wxColour& colour)
{
	_canvas->SetBackgroundColour(colour);
}
