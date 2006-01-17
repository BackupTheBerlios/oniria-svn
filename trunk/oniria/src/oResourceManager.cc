/* $Id: oResourceManager.cc 628 2006-01-02 11:16:03Z choman $ */
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
#include <wx/dir.h>
#include <wx/filesys.h>
#include <wx/fs_zip.h>
#include <wx/stream.h>
#include <onir/utils/uListDirTraverser.h>
#include <onir/xml/xmlParser.h>
#include <onir/xml/xmlElement.h>
#include <onir/rc/rcImage.h>
#include <onir/rc/rcSkin.h>
#include <onir/oConfig.h>
#include <onir/oEventHandler.h>
#include "gApp.h"
#include "oEventManager.h"
#include "oResourceManager.h"

using namespace std;
using onirUtils::uListDirTraverser;
using onirXML::xmlParser;
using onirXML::xmlElement;
using onirXML::xmlAttribute;
using onir::oEventHandler;
using onirRC::rcImage;
using onirRC::rcSkin;

class oResourceEventHandler : public oEventHandler {
	public:
		oResourceEventHandler(oResourceManager * rm);
		virtual bool ProcessEvent(oEvent * event);

	private:
		oResourceManager * _rm;
		
		DECLARE_OOBJECT;
};

DEFINE_OOBJECT(oResourceEventHandler, oEventHandler);

oResourceEventHandler::oResourceEventHandler(oResourceManager * rm)
{
	INIT_OOBJECT;
	_rm = rm;
}

bool oResourceEventHandler::ProcessEvent(oEvent * event)
{
	return _rm->ProcessEvent(event);
}

DEFINE_OOBJECT(oResourceManager, rcPack);

oResourceManager::oResourceManager(gApp * app)
{
	INIT_OOBJECT;
	_app = app;
	_root = NULL;

	wxFileSystem::AddHandler(new wxZipFSHandler());
}

oResourceManager::~oResourceManager()
{
}

int oResourceManager::LoadResources()
{
	wxFileSystem fs;
	wxFSFile * f;
	string xml;
	xmlParser parser;
	string datadir;
	uListDirTraverser trav;
	wxDir dir;
	xmlElement * rel;

	datadir = _app->Config()->Value(_app->Config()->Root(), "datadir", DATADIR);
	dir.Open(datadir);
	dir.Traverse(trav, "*.pak");

	rel = new xmlElement;
	rel->Name("resource");
	rel->AddAttribute("type", "pack");
	rel->AddAttribute("id", "root");
	_root = new rcPack(_app->Oniria());
	_root->Prepare("", NULL, rel);

	for (list<string>::iterator it = trav.files().begin(); it != trav.files().end(); it++) {
		f = fs.OpenFile((*it) + "#zip:resources.xml");
		
		if (f != NULL) {

			parser.Prepare();

			while (!f->GetStream()->Eof()) {
				char * buf;

				buf = new char[8192];
				f->GetStream()->Read(buf, 8192);
				if (f->GetStream()->LastRead() > 0)
					parser.Parse(buf, f->GetStream()->LastRead());
				delete[] buf;
			}

			delete f;

			if (parser.State() == xmlParser::finished) {
				wxLogVerbose("oResourceManager: Found resource file: %s", (*it).c_str());
				if (parser.Root()->Name() == "resource-file") {
					xmlElement * xml;
					list<xmlElement *> res;

					xml = parser.Detach();
					_root->Prepare(*it, NULL, xml);
				}
			}
		}
	}

	return 0;
}

rcResource * oResourceManager::Resource(const string& id, const string& type)
{
	return _root->Resource(id, type);
}

wxImage * oResourceManager::Image(const string& id, const string& imageset)
{
	string root;
	rcImage * rc;
	
	rc = NULL;
	if (!imageset.empty()) {
		rcSkin * skin;
		if (_imagesets.find(imageset) != _imagesets.end()) {
			root = _imagesets[imageset];
			rc = static_cast<rcImage *>(Resource(root + ":" + id, "image"));
		}
		if (rc == NULL && _imagesets.find(imageset + ":user") != _imagesets.end()) {
			root = _imagesets[imageset + ":user"];
			rc = static_cast<rcImage *>(Resource(root + ":" + id, "image"));
		}
		skin = Skin();
		if (rc == NULL && skin != NULL) {
			string root = skin->StringValue(string("imagesets:") + imageset);
			rc = static_cast<rcImage *>(Resource(root + ":" + id, "image"));
		}
		if (rc == NULL && _imagesets.find(imageset + ":default") != _imagesets.end()) {
			root = _imagesets[imageset + ":default"];
			rc = static_cast<rcImage *>(Resource(root + ":" + id, "image"));
		}
	}
	
	if (rc == NULL)
		return NULL;
	else
		return rc->Load();
}

rcSkin * oResourceManager::Skin(const string& id)
{
	if (_skins.find(id) == _skins.end())
		return NULL;
	else
		return static_cast<rcSkin *>(Resource(_skins[id], "skin"));
}

rcSkin * oResourceManager::Skin()
{
	return Skin(_app->Config()->Value(_app->Config()->Root(), "skin", "default"));
}

void oResourceManager::RegisterEventHandlers()
{
	oResourceEventHandler * hnd;
	
	hnd = new oResourceEventHandler(this);
	_app->EventManager()->RegisterHandler("oniria:resource:added", hnd);
}

bool oResourceManager::ProcessEvent(oEvent * event)
{
	ROUTE_EVENT(event, "oniria:resource:added", ResourceAdded);
	return true;
}

bool oResourceManager::ResourceAdded(oEvent * event)
{
	string resid, type;
	rcResource * rc;
	
	resid = event->XML()->ChildValue("resource-id");
	type = event->XML()->ChildValue("resource-type");

	rc = Resource(resid, type);
	if (rc == NULL)
		return true;

	if (type == "pack" && rc->XML()->AttributeValue("class") == "imageset") {
		string origin, isid;
		origin = rc->XML()->AttributeValue("origin");
		isid = rc->XML()->AttributeValue("imageset-id");
		if (origin == "default") {
			isid += ":" + origin;
			_imagesets[isid] = rc->Id();
			wxLogVerbose("oResourceManager: Registered imageset: %s -> %s", isid.c_str(), rc->Id().c_str());
		}
	} else if (type == "skin") {
		string skinid;
		rcSkin * skin;
		
		skinid = rc->XML()->AttributeValue("skin-id");
		_skins[skinid] = rc->Id();
		
		skin = static_cast<rcSkin *>(rc);
		wxLogVerbose("oResourceManager: Registered skin \"%s\": %s -> %s", skin->StringValue("name").c_str(), skinid.c_str(), rc->Id().c_str());
	}
	
	return true;
}
