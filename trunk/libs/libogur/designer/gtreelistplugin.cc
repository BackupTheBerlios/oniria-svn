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

#include <QtCore/qplugin.h>
#include "gtreelistplugin.h"
#include <ogur/gtreelist.h>

class GTreeList_des : public GTreeList{
	public:
		GTreeList_des(QWidget * parent = 0):GTreeList(parent)
		{
			GTreeListItem * it = 0;
			it = createItem("12", "");
			it = createItem("121", "12");
			it = createItem("122", "12");
			it = createItem("13", "");
			redraw();
		}
};

GTreeListPlugin::GTreeListPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void GTreeListPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool GTreeListPlugin::isInitialized() const
{
    return initialized;
}

QWidget *GTreeListPlugin::createWidget(QWidget *parent)
{
	return new GTreeList_des(parent);
}

QString GTreeListPlugin::name() const
{
	return "GTreeList";
}

QString GTreeListPlugin::group() const
{
	return "Ogur Controls";
}

QIcon GTreeListPlugin::icon() const
{
	return QIcon(":/icon.png");
}

QString GTreeListPlugin::toolTip() const
{
	return "";
}

QString GTreeListPlugin::whatsThis() const
{
	return "";
}

bool GTreeListPlugin::isContainer() const
{
	return false;
}

QString GTreeListPlugin::domXml() const
{
    return "<widget class=\"GTreeList\" name=\"TreeList\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>100</width>\n"
           "   <height>150</height>\n"
           "  </rect>\n"
           " </property>\n"
           "</widget>\n";
}

QString GTreeListPlugin::includeFile() const
{
	return "ogur/gtreelist.h";
}

QString GTreeListPlugin::codeTemplate() const
{
    return "";
}

Q_EXPORT_PLUGIN(GTreeListPlugin)
