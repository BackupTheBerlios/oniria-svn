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
 * MERCHANTABILITY or FITNESS FOR A PAtreeICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

 
#include <QApplication>
#include <QtGui>
#include <gtreelist.h>
#include <gtreelistitem.h> 
#include <gitemcol.h>
#include <gitemline.h>
#include "treelist.h"
 
 
 MainWnd::MainWnd(QWidget * parent)
 :QWidget(parent){
		tree = new GTreeList(this);
	
		tree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		tree->setBackgroundRole(QPalette::Base);	
		
		item = tree->createItem("one", "");
		item->col()->data(GItemCol::image, ":/icon.png");
		
		item = tree->createItem("two", "");
		item->col()->data(GItemCol::image, ":/icon.png");

		item = tree->createItem("three", "two");
		item->col()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<b><u>Test</u></b>");
		item->line()->addCol()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<i>Test 2</i>");

		item = tree->createItem("three2", "two");
		item->col()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<b><u>Test</u></b>");
		item->line()->addCol()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<i>Test 2</i>");


		item = tree->createItem("three3", "one");
		item->col()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<b><u>Test</u></b>");
		item->line()->addCol()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<i>Test 2</i>");


		item = tree->createItem("three4", "three2");
		item->col()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<b><u>Test</u></b>");
		item->line()->addCol()->data(GItemCol::image, ":/icon.png");
		item->line()->addCol()->data(GItemCol::text, "<i>Test 2</i>");

		tree->redraw();		
		
		QPushButton * browseButton = new QPushButton("Browse");
		connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
		QHBoxLayout * buttonsLayout = new QHBoxLayout;
		buttonsLayout->addStretch();
		buttonsLayout->addWidget(browseButton);		
		buttonsLayout->addStretch();
		
		QVBoxLayout * mainLayout = new QVBoxLayout;
		mainLayout->addWidget(tree);		
		mainLayout->addLayout(buttonsLayout);
		setLayout(mainLayout);

	}

void MainWnd::browse()
{
	QString fileName;
	fileName = QFileDialog::getOpenFileName(this, tr("Select a File"), currentMovieDirectory, tr("Animation & graphic (*.gif *.mng *.png)"));
	if (!fileName.isEmpty()){
		int index = fileName.length() - fileName.lastIndexOf("/");
        if (!(index < 0)) {
            currentMovieDirectory = fileName;
            currentMovieDirectory.chop(index);
        }
		QMap<QString, GTreeListItem *> s = tree->selected();
		if (!s.empty()){
			GTreeListItem * item = s.begin().value();
			item->col()->data(GItemCol::animation, fileName);			
			tree->redraw(item);
		}
	}
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	MainWnd m;
	m.resize(300, 700);
	m.show();
 	return app.exec();
} 
