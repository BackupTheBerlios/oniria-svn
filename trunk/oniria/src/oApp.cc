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
#if defined(WIN32)
# include "win32/oniria_config.h"
#else
# include "oniria_config.h"
#endif
#include "oApp.h"

#include <QApplication>
#include "gMain.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	gMain mainWindow;
	mainWindow.show();	
	return app.exec();
}

/*
#include <onir/onir.h>
#include <wx/utils.h>
#include <wx/filefn.h>
#include "gFrame.h"

#include "oPluginManager.h"
#include "oEventManager.h"
#include "oSessionManager.h"
#include "oResourceManager.h"
#include "oOniriaImpl.h"
#include "xConfig.h"
#include "oTabManager.h"
#include "oStatusManager.h"

class gApp;

class logWindow :public wxLogWindow{
	public:
		logWindow(gApp * a, wxWindow * p, const wxChar * title):wxLogWindow(p, title)
		{
			_app = a;
		}
		virtual void OnFrameDelete(wxFrame *frame)
		{
			_app->Config()->StoreValueNs("log/x_pos", frame->GetPosition().x);
			_app->Config()->StoreValueNs("log/y_pos", frame->GetPosition().y);

			_app->Config()->StoreValueNs("log/width", frame->GetSize().GetWidth());
			_app->Config()->StoreValueNs("log/height",frame->GetSize().GetHeight());
			wxLogWindow::OnFrameDelete(frame);
		}
	private:
		gApp * _app;


};


IMPLEMENT_APP(gApp)


bool gApp::OnInit()
{
	wxString prn;
	wxString cf;

	::wxInitAllImageHandlers();
	_logwnd = NULL;

	cf = ::wxGetHomeDir() + "/.oniria";
	if (!::wxDirExists(cf))
		::wxMkdir(cf, 0700);
	_config = new xConfig((cf + "/config.xml").c_str(), true);

	_eventman = new oEventManager(this);

	_resourceman = new oResourceManager(this);

	_plugman = new oPluginManager(this);
	_plugman->LoadPlugins();

	_sessionman = new oSessionManager(this);

	_statusman = new oStatusManager(this);


	_oniria = new oOniriaImpl(this);

	wxXmlResource::Get()->InitAllHandlers();

	wxFileName file;
	file.AssignDir(DATADIR);
	file.SetFullName("oniria.xrc");
	wxString sRes = file.GetFullPath();
	if (!file.IsOk() || !file.FileExists() || !wxXmlResource::Get()->Load(sRes)){
		wxLogFatalError(_("Bad resource file (%s)"), sRes.c_str());
	}

	libonir_init_resources(wxXmlResource::Get());

	wxXmlResource::Get()->SetFlags(wxXmlResource::Get()->GetFlags() | wxXRC_NO_SUBCLASSING);
	prn.Printf(_("%s ( ver.: %d.%d.%d )"),
			   ONIRIA_PROGRAM_NAME,
			   ONIRIA_MAJOR_VERSION,
			   ONIRIA_MINOR_VERSION,
			   ONIRIA_MICRO_VERSION);
	SetAppName(prn);

	_main = new gFrame(
				NULL,
				prn,
				wxCLIP_CHILDREN | wxMINIMIZE_BOX | wxMAXIMIZE_BOX |wxTHICK_FRAME | wxSYSTEM_MENU | wxCAPTION,
				wxDefaultPosition,
				wxSize(200, 600),
				wxID_ANY,
				this);

	SetTopWindow(_main);

	if (Config()->ValueNs("log/target", "none") == "window"){
		_logwnd = new logWindow ( this, _main," log");
		_logwnd->GetFrame()->Move(
			Config()->ValueNs("log/x_pos", wxDefaultPosition.x),
			Config()->ValueNs("log/y_pos", wxDefaultPosition.y)
		);

		_logwnd->GetFrame()->SetSize(
			Config()->ValueNs("log/width", 400),
			Config()->ValueNs("log/height", 300)
		);
	}
	if (Config()->NodeAt("log/verbose") != NULL) {
		wxLog::SetVerbose(true);
		libonir_init_log(_logwnd, true);
	} else {
		libonir_init_log(_logwnd, false);
	}
	libonir_init("WINDOWS-1250");

	_sessionman->RegisterEventHandlers();
	_resourceman->RegisterEventHandlers();

	_resourceman->LoadResources();
	EventManager()->ProcessQueue();

	_tabs = new oTabManager(this, _main);
	_sessionman->RegisterTabGroups();

	_plugman->CreatePlugins();
	_sessionman->LoadSessions();
	_sessionman->ConnectSessions();
	_main->Show(true);

	return true;
}

int gApp::OnExit()
{
	delete _oniria;
	delete _eventman;
	delete _resourceman;
	delete _sessionman;
	delete _plugman;
	delete _tabs;
	delete _statusman;
	delete _config;

	return 0;
}

void gApp::CloseApp()
{
	if (wxMessageBox(_("Close program ?"), _("Question"), wxYES_NO | wxICON_QUESTION) == wxYES)
		_main->Close();
}
*/
