/* $id$ */
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

#include <set>
#include <algorithm>
#include "gApp.h"
#include <onir/utils/dconv.h>
#include "gFrame.h"
#include "oTabManager.h"
#include "gTabFrame.h"
#include "oResourceManager.h"

#define MAKE_NAME(group, name) (string(group)+":"+string(name))

using std::set;
using namespace onir;
using namespace onirUtils;

const int ID_MENU_UNDOCK = 	 wxNewId();
const int ID_NOTEBOOK =		 wxNewId();
const int MENU_BEGIN 			= 0x10;
const int MENU_END 				= 0x30;
const int SUBMENU_BEGIN			= 0x31;
const int SUBMENU_END			= 0x50;

#define MARGIN 	0

class _TabHolder : public wxPanel
{
	public:
		_TabHolder(wxWindow * parent, int id, gApp * app);
		~_TabHolder();
		inline void Parent(oTabManager * t) { _parent = t; };
		inline wxNotebook * tab() { return XRCCTRL(*this, "notebook", wxNotebook); };
		void RemovePage(const string &ident, bool hide_only = false);
		string ActiveIdent();
		void ActiveTitle(const string & name);
		void EnableBtn();
	protected:
		void OnUndockButtonClick(wxCommandEvent &event);
		void OnMenuRange(wxCommandEvent &event);
		void OnNotebookPageChange(wxNotebookEvent &event);
		void OnCloseButtonClick(wxCommandEvent &event);
		void OnSubMenuRange(wxCommandEvent &event);
		void OnClose(wxCloseEvent &event);
	private:
		class ofSubPopupCreate{
			public:
				ofSubPopupCreate(_TabHolder * t, wxMenu * m, int id);					
				void operator() (pair<string, string> p);
			private:
				_TabHolder * tab;
				int _idBegin;
				wxMenu * _popup;
		};
		
		class ofPopupCreate{
			public:
				ofPopupCreate(_TabHolder * t, wxMenu * m, int id);					
				void operator() (pair<string, oTabManager::_if_page> p);
			private:
				_TabHolder * tab;
				int _idBegin;
				wxMenu * _popup;
				set<wxWindow *> used;
		};

		void CheckForDestroy();
		gApp * _app;
		wxMenu * _popup;
		wxMenu * _subpopup;
		oTabManager * _parent;
		map<string, wxPanel *> _identToPanel;
		map<wxPanel *, string> _panelToIdent;
		map<int, string> _idToStr;
		map<string, int> _strToId;
		wxImage * _undockNormal;
		wxImage * _undockDisable;
		wxImage * _closeNormal;
		wxImage * _closeDisable;
		DECLARE_EVENT_TABLE()
		friend class oTabManager;
		friend class ofSubPopupCreate;
		friend class ofPopupCreate;
};

/*

	FUNCTIONS OBJECTS
	
*/

_TabHolder::ofSubPopupCreate::ofSubPopupCreate(_TabHolder * t, wxMenu * m, int id)
{
	tab = t;
	_popup = m;
	_idBegin = id;
}

void _TabHolder::ofSubPopupCreate::operator() (pair<string, string> p)
{
	_popup->Append(_idBegin++, p.second.c_str());
}

/* ---------------------------------*/

_TabHolder::ofPopupCreate::ofPopupCreate(_TabHolder * t, wxMenu * m, int id)
{
	tab = t;
	_popup = m;
	_idBegin = id;
}

void _TabHolder::ofPopupCreate::operator() (pair<string, oTabManager::_if_page> p)
{
	if ((used.find(p.second.owner) == used.end()) && (p.second.tab != tab)){
			if ((p.second.owner != NULL) && 
				(p.second.state == oTabManager::tws_shown)){
				tab->_idToStr[_idBegin] = p.first;
				tab->_strToId[p.first] = _idBegin;
				_popup->Append(_idBegin++,  _("Window ") + p.second.owner->GetLabel());			
				used.insert(p.second.owner);
			}
		}

}

/*
	
	---------------------------------------
	
*/

BEGIN_EVENT_TABLE(_TabHolder, wxPanel)
	EVT_BUTTON(XRCID("undockBtn"), _TabHolder::OnUndockButtonClick)
	EVT_BUTTON(XRCID("closeBtn"), _TabHolder::OnCloseButtonClick)
	EVT_NOTEBOOK_PAGE_CHANGED(XRCID("notebook"), _TabHolder::OnNotebookPageChange)	
	EVT_MENU_RANGE(MENU_BEGIN, MENU_END, _TabHolder::OnMenuRange)
	EVT_MENU_RANGE(SUBMENU_BEGIN, SUBMENU_END, _TabHolder::OnSubMenuRange)
	EVT_CLOSE(_TabHolder::OnClose)
END_EVENT_TABLE()
 

_TabHolder::_TabHolder(wxWindow * parent, int id, gApp * app)
:wxPanel()
{
	_app = app;	
	 wxXmlResource::Get()->LoadPanel(this, parent, "tabPanel");	
	 
	 _undockNormal = _app->ResourceManager()->Image("frame-tab-dock", "buttons");
	 _undockDisable = _app->ResourceManager()->Image("frame-tab-dock-disable", "buttons");
	 _closeNormal = _app->ResourceManager()->Image("frame-tab-close", "buttons");
	 _closeDisable = _app->ResourceManager()->Image("frame-tab-close-disable", "buttons");
	  
	 wxBitmap bmp(*_undockNormal);
	 wxBitmap bmpd(*_undockDisable);
	 wxBitmap closeBtn(*_closeNormal);
	 wxBitmap closeBtnd(*_closeDisable);
	 
	 XRCCTRL(*this, "undockBtn", wxBitmapButton)->SetBitmapLabel(bmp);		 
	 XRCCTRL(*this, "undockBtn", wxBitmapButton)->SetBitmapDisabled(bmpd);	
	 XRCCTRL(*this, "closeBtn", wxBitmapButton)->SetBitmapLabel(closeBtn);	
	 XRCCTRL(*this, "closeBtn", wxBitmapButton)->SetBitmapDisabled(closeBtnd);	
	 
	_popup = NULL;	
	_subpopup = NULL;
}


_TabHolder::~_TabHolder()
{	
	delete _undockNormal;
	delete _undockDisable;
	delete _closeNormal;
	delete _closeDisable;
	delete _popup;
}


void _TabHolder::OnClose(wxCloseEvent &event)
{	
	vector<string> v;
	for (size_t i = 0; i < tab()->GetPageCount(); i++){
		v.push_back(_panelToIdent[reinterpret_cast<wxPanel *>(tab()->GetPage(i))]);
	}
	
	for(vector<string>::iterator i = v.begin() ; i!= v.end(); ++i){
		RemovePage(*i, true);
	}
	CheckForDestroy();
}

void _TabHolder::OnUndockButtonClick(wxCommandEvent &event)
{
	if (_popup)
		delete _popup;
		
	_popup = new wxMenu;	
	
	bool tabnonempty = (tab()->GetPageCount() > 0);
	
	if (tabnonempty)
		_popup->Append(MENU_BEGIN, _("In new window"));				
	
	if (tabnonempty && (GetParent() != _parent->_frame->GeneralWnd())){
		_popup->Append(MENU_BEGIN + 1, _("In main window"));		
	}	
	
	if (tabnonempty)
		_popup->AppendSeparator();	
		
	vector<pair<string, string> > v;
	_parent->HiddenPages(v);
	if (!v.empty()){		
		_subpopup = new wxMenu;	
		ofSubPopupCreate ofSPC(this, _subpopup, SUBMENU_BEGIN);
		std::for_each(v.begin(), v.end(), ofSPC);			
		_popup->Append(-1, _("Hidden"), _subpopup);		
		_popup->AppendSeparator();	
	}			
	
	_idToStr.clear();
	_strToId.clear(); 
	
	if (tabnonempty){
		ofPopupCreate ofPC(this, _popup, MENU_BEGIN + 2);
		std::for_each(_parent->_pages.begin(), _parent->_pages.end(), ofPC);	
	}	
	if (_popup->GetMenuItemCount() > 0)
		XRCCTRL(*this, "undockBtn", wxBitmapButton)->PopupMenu(_popup);
}

void _TabHolder::OnMenuRange(wxCommandEvent &event)
{	
	string ident = ActiveIdent();	
	string name = _parent->_pages[ident].name;
	wxPanel * p = _identToPanel[ident];
	RemovePage(ident);		
	
	if (event.GetId() == MENU_BEGIN){	
					
		_parent->_pages.erase(ident);
		_parent->CreateMutiWindowPage("", ident, name, true, p);
		
	}else if (event.GetId() == MENU_BEGIN + 1){
		
		_parent->_pages.erase(ident);
		_parent->CreateFramePage("", ident, name, true, p);	
		
	}else{			
		
		string mident = _idToStr[event.GetId()];
		_TabHolder * t = _parent->_pages[mident].tab;
		_parent->_pages[ident].tab = t;
		_parent->_pages[ident].owner = _parent->_pages[mident].owner;
		_parent->CreatePage(t, ident, name, true ,p);
		
	}	
	CheckForDestroy();
	if (tab()->GetPageCount() == 0){
		XRCCTRL(*this, "closeBtn", wxBitmapButton)->Disable();
	}
}

void _TabHolder::OnSubMenuRange(wxCommandEvent &event)
{
	vector<pair<string, string> > v;
	_parent->HiddenPages(v);
	_parent->ShowHiddenPageInt(v[event.GetId() - SUBMENU_BEGIN].first);	
}

void _TabHolder::CheckForDestroy()
{
	if ((_identToPanel.empty()) && (GetParent() != _parent->_frame->GeneralWnd())){
		GetParent()->Hide();
	}	
}

void _TabHolder::RemovePage(const string &ident, bool hide_only)
{
	wxPanel * p = _identToPanel[ident];	
	
	p->Hide();
	p->Reparent(_parent->ParentWindow());

	for (size_t i = 0; i < tab()->GetPageCount(); i++){
		if (tab()->GetPage(i) == p){
			tab()->RemovePage(i);
			
			if (hide_only){
				_parent->_pages[ident].state = _parent->_groups[_parent->_pages[ident].group].hidestate;// oTabManager::tws_hidden;
			}
			_identToPanel.erase(ident);
			_panelToIdent.erase(p);			
			
			break;	
		}
	}		
	
}

string _TabHolder::ActiveIdent()
{
	return _panelToIdent[reinterpret_cast<wxPanel *>(tab()->GetCurrentPage())];		
}

void _TabHolder::ActiveTitle(const string & name)
{
	GetParent()->SetLabel(name.c_str());
}

void _TabHolder::OnNotebookPageChange(wxNotebookEvent &event)
{
	ActiveTitle(_parent->_pages[ActiveIdent()].name);
}

void _TabHolder::EnableBtn()
{
	XRCCTRL(*this, "undockBtn", wxButton)->Enable();
	XRCCTRL(*this, "closeBtn", wxBitmapButton)->Enable();
}

void _TabHolder::OnCloseButtonClick(wxCommandEvent &event)
{
	string ident = ActiveIdent();
	RemovePage(ident, true);
	CheckForDestroy();	
	if (tab()->GetPageCount() == 0){
		XRCCTRL(*this, "closeBtn", wxBitmapButton)->Disable();
	}

}

/******************************************************/


oTabManager::oTabManager(gApp * app, gFrame * frame)
		:oTabs()
{
	_app = app;
	_frame = frame;
	
	_mostParentWindow = new wxPanel(frame);
	_mostParentWindow->Hide();
	
	_frameTab = NULL;
	RegisterGroup("default", ts_main_window);
	RegisterGroup("system_dialogs", ts_single_window);
};

oTabManager::~oTabManager()
{

}

wxPanel * oTabManager::CreateFramePage(const string & group, const string & ident, const string & name, bool active, wxPanel * page)
{
	if (_frameTab == NULL){
		_frameTab = CreateTabs(_frame->GeneralWnd());
	}
	_if_page p;
	p.owner = _frame;
	p.tab = _frameTab;
	p.page = CreatePage(_frameTab, MAKE_NAME(group, ident), name, active, page);
	p.name = name;
	p.group = group;
	p.ident = ident;
	p.state = tws_shown;
	_pages[MAKE_NAME(group, ident)] = p;
	return p.page;
}

wxPanel * oTabManager::CreateMutiWindowPage(const string & group, const string & ident, const string & name, bool active, wxPanel * page)
{
	_if_page p;
	p.owner = new gTabFrame(_frame);
	p.owner->Show();
	p.tab = CreateTabs(p.owner);
	p.owner->SetSize(400, 400);
	p.page = CreatePage(p.tab, MAKE_NAME(group, ident), name, active, page);
	p.name = name;
	p.ident = ident;
	p.group = group;
	p.state = tws_shown;
	_pages[MAKE_NAME(group, ident)] = p;
	return p.page;
}

wxPanel * oTabManager::CreateSingleWindowPage(const string & groupname, const string & ident, const string & name, _if_group &group, bool active, wxPanel * page)
{
	if (group.singleWindow == NULL){
		group.singleWindow = new gTabFrame(_frame);
	}else{
		group.singleWindow->Show();
	}
	group.singleWindow->Show();
	if (group.singleWindowTab == NULL){
		group.singleWindowTab = CreateTabs(group.singleWindow);
	}
	_if_page p;
	p.owner = group.singleWindow;
	p.tab = group.singleWindowTab;
	group.singleWindow->SetSize(400, 400);
	p.page = CreatePage(group.singleWindowTab, MAKE_NAME(groupname, ident), name, active ,page);
	p.name = name;
	p.ident = ident;
	p.group = groupname;
	p.state = tws_shown;
	_pages[MAKE_NAME(groupname, ident)] = p;
	return p.page;

}

wxPanel * oTabManager::CreatePage( _TabHolder * p,const string & ident, const string & name, bool active, wxPanel * page)
{
	wxPanel * t = NULL;
	if (page == NULL){
		t = new wxPanel(p->tab());		
	}else{
		t = page;
		t->Reparent(p->tab());
	}		
	p->_identToPanel[ident] = t;
	p->_panelToIdent[t] = ident;
	p->tab()->AddPage(t, name.c_str(), active);
	p->ActiveTitle(name);
	p->EnableBtn();	
	return t;
}

_TabHolder * oTabManager::CreateTabs(wxWindow * parent)
{
	wxBoxSizer* sf = new wxBoxSizer(wxHORIZONTAL);
	_TabHolder * tab = new _TabHolder(parent, _frame->FreeCmd(), _app);
	tab->Parent(this);
	sf->Add(tab,2 , wxEXPAND | wxALL, MARGIN);
	sf->Fit(parent);
	parent->SetAutoLayout(TRUE);
	sf->Layout();
	sf->SetSizeHints(parent);
	parent->SetSizer(sf);
	return tab;
}

void oTabManager::RemovePage(const string & ident, const string &group)
{
	map<string, _if_page>::iterator i;
	if ((i = _pages.find(MAKE_NAME(group, ident))) == _pages.end())
		return;	
	i->second.tab->RemovePage(MAKE_NAME(group, ident));
	if ((i->second.owner != NULL) && (i->second.owner != _frame)){
		if (i->second.tab->_identToPanel.empty()){
			i->second.owner->Show(false);
			i->second.owner->Destroy();			
		}
	}	
}

wxWindow * oTabManager::PageAt(const string & ident, const string &group)
{
	map<string, _if_page>::iterator i;
	if ((i = _pages.find(MAKE_NAME(group, ident))) != _pages.end())
		return i->second.page;
	return NULL;
}

void oTabManager::RegisterGroup(const string & name, tab_style style, window_state hidestate)
{
	_if_group g;
	g.style = style;
	g.singleWindowTab = NULL;
	g.singleWindow = NULL;
	g.hidestate = hidestate;
	_groups[name] = g;
	wxLogMessage("oTabManager: register group : %s (%d)", name.c_str(), static_cast<int>(style));
}

wxWindow * oTabManager::RegisterPage(const string & ident, const string & name, const string &group)
{
	if (_pages.find(MAKE_NAME(group, ident)) != _pages.end()){
		ShowHiddenPage(ident, group);
		return NULL;
	}

	_if_group &g = _groups[group];
	wxLogMessage("oTabManager: register page at: %s (%d)", MAKE_NAME(group,ident).c_str(), static_cast<int>(g.style));
	switch (g.style){
			case ts_main_window:
			return CreateFramePage(group, ident, name, false);

			case ts_single_window:
			return CreateSingleWindowPage(group, ident, name, g, false);

			case ts_multi_window:
			return CreateMutiWindowPage(group, ident, name, false);

	}
	return NULL;
}

void oTabManager::ShowHiddenPage(const string & ident, const string &group)
{
	ShowHiddenPageInt(MAKE_NAME(group, ident));	
}

void oTabManager::ShowHiddenPageInt(const string &globalident)
{
	if (_pages.find(globalident) == _pages.end())
		return;		
		
	_if_page &page = _pages[globalident];
	if (page.state == tws_shown)
		return;
		
	_if_group &g = _groups[page.group];
	wxLogVerbose("oTabManager::ShowHiddenPageInt %s", globalident.c_str());
	switch (g.style){
		case ts_main_window:
		CreateFramePage(page.group, page.ident, page.name, true, page.page);
		break;

		case ts_single_window:
		CreateSingleWindowPage(page.group, page.ident, page.name, g, true, page.page);
		break;

		case ts_multi_window:
		CreateMutiWindowPage(page.group, page.ident, page.name, true, page.page);
		break;
	}		
}

bool oTabManager::RegisterPage(const string & ident, const string & name, wxPanel *page, const string &group)
{
	if (_pages.find(MAKE_NAME(group, ident)) != _pages.end()){
		ShowHiddenPage(ident, group);
		return false;
	}

	_if_group &g = _groups[group];
	wxLogMessage("oTabManager: register page at: %s (%d)", MAKE_NAME(group,ident).c_str(), static_cast<int>(g.style));
	switch (g.style){
			case ts_main_window:
			CreateFramePage(group, ident, name, false, page);
			break;

			case ts_single_window:
			CreateSingleWindowPage(group, ident, name, g, false, page);
			break;

			case ts_multi_window:
			CreateMutiWindowPage(group, ident, name, false, page);
			break;
	}	
	return true;
}

wxWindow * oTabManager::ParentWindow()
{
	return _mostParentWindow;
}

void oTabManager::HiddenPages(vector< pair< string, string> > & v)
{
	v.clear();
	for (map<string, _if_page>::iterator i = _pages.begin(); i!= _pages.end(); ++i){
		if (i->second.state == tws_hidden)
			v.push_back(std::make_pair(i->first, i->second.name));
	}
}
