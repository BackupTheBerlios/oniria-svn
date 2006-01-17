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
#include <cctype>
#include <algorithm>
#include <onir/im/imRosterEntry.h>
#include <onir/im/imRosterItem.h>
#include <onir/im/imRosterGroup.h>
#include <onir/im/imStatus.h>
#include <onir/rc/rcImage.h>
#include <onir/oConfig.h>
#include "guictrls/ctrlRosterTree.h"
#include "oResourceManager.h"
#include "oSessionManager.h"
#include "gApp.h"
#include "gRoster.h"

using onirIM::imRosterEntry;
using onirIM::imRosterItem;
using onirIM::imRosterGroup;
using onirIM::imStatus;
using namespace std;

BEGIN_EVENT_TABLE(gRoster, wxPanel)
	EVT_COMMAND(-1, wxEVT_MOUSE_DB_CLICK, gRoster::OnMouseDbClick)
END_EVENT_TABLE()


char _tolower_trans(char c)
{
	return tolower(c);
}

gRoster::gRoster(gApp * app, wxWindow * parent)
	: wxPanel(parent)
{
	wxBoxSizer * resizer = new wxBoxSizer(wxVERTICAL);
	
	_app = app;

	_tree = new ctrlRosterTree(this);

	resizer->Add(_tree, 1 , wxEXPAND | wxALL, 0);
	resizer->SetSizeHints(this);
	resizer->Layout();
	SetSizer(resizer);
}

bool gRoster::UpdateTree(imRoster * roster)
{
	vector<string> order;
	multimap<string, string> omap, gomap;
	_roster = roster;
	string sort_m;
	
	sort_m = _app->Config()->Value("roster", "sort", "status");

	for (map<string, imRosterGroup *>::iterator it = roster->TopGroups()->begin(); it != roster->TopGroups()->end(); it++) {
		string s, t;
		FillGroup("", it->second);
		s = it->second->Name();
		transform(s.begin(), s.end(), back_inserter<string>(t), _tolower_trans);
		gomap.insert(make_pair(t, it->second->Id()));
	}
	for (map<string, imRosterItem *>::iterator it = roster->TopItems()->begin(); it != roster->TopItems()->end(); it++) {
		string s, t;
		FillItem("", it->second);
		s = it->second->Name();
		transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
		if (sort_m == "status")
			AddStatusSortPrefix(t, it->second);
		omap.insert(make_pair(t, it->second->Id()));
	}
	
	for (multimap<string, string>::iterator it = gomap.begin(); it != gomap.end(); it++)
		order.push_back(it->second);
	for (multimap<string, string>::iterator it = omap.begin(); it != omap.end(); it++)
		order.push_back(it->second);
	_tree->Order("", order);

	_tree->Redraw("");

	return true;
}

void gRoster::FillGroup(const string& root, imRosterGroup * gr)
{
	vector<string> order;
	multimap<string, string> omap, gomap;

	string sort_m;
	
	sort_m = _app->Config()->Value("roster", "sort", "status");

	_tree->AddItem(root, gr->Id(), gr->Name(), "", true);
	_tree->FindItem(gr->Id())->SkinRoot(gr->SkinRoot());
	for (map<string, imRosterGroup *>::iterator it = gr->Groups()->begin(); it != gr->Groups()->end(); it++) {
		string s, t;
		FillGroup(gr->Id(), it->second);
		s = it->second->Name();
		transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
		gomap.insert(make_pair(t, it->second->Id()));
	}
	for (map<string, imRosterItem *>::iterator it = gr->Items()->begin(); it != gr->Items()->end(); it++) {
		string s, t;
		FillItem(gr->Id(), it->second);
		s = it->second->Name();
		transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
		if (sort_m == "status")
			AddStatusSortPrefix(t, it->second);
		omap.insert(make_pair(t, it->second->Id()));
	}

	if (!gr->FixedOrder(order)) {
		for (multimap<string, string>::iterator it = gomap.begin(); it != gomap.end(); it++)
			order.push_back(it->second);
		for (multimap<string, string>::iterator it = omap.begin(); it != omap.end(); it++)
			order.push_back(it->second);
	}
	_tree->Order(gr->Id(), order);
}

void gRoster::FillItem(const string& root, imRosterItem * item)
{
	vector<string> order;
	multimap<string, string> omap, gomap;
	string sort_m;
	
	sort_m = _app->Config()->Value("roster", "sort", "status");

	_tree->AddItem(root, item->Id(), item->Name());
	_tree->FindItem(item->Id())->SkinRoot(item->SkinRoot() + ":" + item->Status().StatusToString());
	UpdateItem(item->Id());
	for (map<string, imRosterItem *>::iterator it = item->SubItems()->begin(); it != item->SubItems()->end(); it++) {
		string s, t;
		FillItem(item->Id(), it->second);
		s = it->second->Name();
		transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
		if (sort_m == "status")
			AddStatusSortPrefix(t, it->second);
		omap.insert(make_pair(t, it->second->Id()));
	}

	if (!item->FixedOrder(order)) {
		for (multimap<string, string>::iterator it = omap.begin(); it != omap.end(); it++)
			order.push_back(it->second);
	}
	_tree->Order(item->Id(), order);
}

bool gRoster::UpdateItem(const string& id)
{
	imRosterItem * item;
	string sort_m;

	if (_roster->AllItems()->find(id) == _roster->AllItems()->end()) {
		_tree->RemoveItem(id);
		return true;
	}
	item = _roster->AllItems()->find(id)->second;

	_tree->Description(id, item->Status().Description());
	_tree->NormalIcon(id, _app->ResourceManager()->Image(item->Status().IconId(), item->IconSet()));
	_tree->ExpandedIcon(id, _app->ResourceManager()->Image(item->Status().IconId() + "-e", item->IconSet()));
	_tree->FindItem(item->Id())->SkinRoot(item->SkinRoot() + ":" + item->Status().StatusToString());
	_tree->Redraw(id);

	sort_m = _app->Config()->Value("roster", "sort", "status");

	{
		vector<string> order;
		multimap<string, string> omap, gomap;

		for (map<string, imRosterGroup *>::iterator it = _roster->TopGroups()->begin(); it != _roster->TopGroups()->end(); it++) {
			string s, t;
			s = it->second->Name();
			transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
			gomap.insert(make_pair(t, it->second->Id()));
		}
		for (map<string, imRosterItem *>::iterator it = _roster->TopItems()->begin(); it != _roster->TopItems()->end(); it++) {
			string s, t;
			s = it->second->Name();
			transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
			if (sort_m == "status")
				AddStatusSortPrefix(t, it->second);
			omap.insert(make_pair(t, it->second->Id()));
		}
	
		for (multimap<string, string>::iterator it = gomap.begin(); it != gomap.end(); it++)
			order.push_back(it->second);
		for (multimap<string, string>::iterator it = omap.begin(); it != omap.end(); it++)
			order.push_back(it->second);
		if (_tree->Order("", order))
			_tree->Redraw("");
	}
	for (map<string, imRosterGroup *>::iterator it = item->InGroups()->begin(); it != item->InGroups()->end(); it++) {
		vector<string> order;
		multimap<string, string> omap, gomap;

		for (map<string, imRosterGroup *>::iterator it2 = it->second->Groups()->begin(); it2 != it->second->Groups()->end(); it2++) {
			string s, t;
			s = it2->second->Name();
			transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
			gomap.insert(make_pair(t, it2->second->Id()));
		}
		for (map<string, imRosterItem *>::iterator it2 = it->second->Items()->begin(); it2 != it->second->Items()->end(); it2++) {
			string s, t;
			s = it2->second->Name();
			transform(s.begin(), s.end(), back_inserter(t), _tolower_trans);
			if (sort_m == "status")
				AddStatusSortPrefix(t, it2->second);
			omap.insert(make_pair(t, it2->second->Id()));
		}
	
		for (multimap<string, string>::iterator it2 = gomap.begin(); it2 != gomap.end(); it2++)
			order.push_back(it2->second);
		for (multimap<string, string>::iterator it2 = omap.begin(); it2 != omap.end(); it2++)
			order.push_back(it2->second);
		if (_tree->Order(it->second->Id(), order))
			_tree->Redraw(it->second->Id());
	}

	return true;
}

bool gRoster::NewItem(const string& id)
{
	imRosterItem * item;
	imRosterItem * ritem;
	string root;
	vector<string> order;

	if (_roster->AllItems()->find(id) == _roster->AllItems()->end())
		return false;
	
	item = _roster->AllItems()->find(id)->second;
	if (item->Parent() != NULL)
		root = item->Parent()->Id();
	
	FillItem(root, item);
	if (_roster->Items()->find(root) != _roster->Items()->end()) {
		ritem = _roster->Items()->find(root)->second;
		if (ritem->FixedOrder(order))
			_tree->Order(root, order);
	}
	return true;
}

void gRoster::AddStatusSortPrefix(string& id, imRosterItem * item)
{
	switch (item->Status().Status()) {
		case imStatus::chat:
			id = "01" + id;
			break;
		case imStatus::avail:
			id = "02" + id;
			break;
		case imStatus::away:
			id = "03" + id;
			break;
		case imStatus::xa:
			id = "04" + id;
			break;
		case imStatus::dnd:
			id = "05" + id;
			break;
		case imStatus::inv:
			id = "06" + id;
			break;
		default:
			id = "07" + id;
			break;
	}
}

void gRoster::OnMouseDbClick(wxCommandEvent &event)
{
	vector<ctrlRosterTreeItem *> v;
	v = _tree->Selected();
	
	for (vector<ctrlRosterTreeItem *>::iterator it = v.begin(); it != v.end(); it++) {
		_app->SessionManager()->StartThread(_roster->Session()->SessionId(), (*it)->Id());
	}
}
