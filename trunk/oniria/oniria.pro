# $Id$

CONFIG 		*= debug warn_on console
TEMPLATE 	= app
APP_NAME 	= oniria
TARGET		= $${APP_NAME}
VERSION		= 0.0.1 

HEADERS += src/oApp.h \
			src/gMain.h

SOURCES += src/oApp.cc \
			src/gMain.cc

FORMS += src/data/dialogs/gMain.ui 

DOC_INPUT = doxygen.cfg
		
#output
DESTDIR = ./bin
MOC_DIR = .moc
OBJECTS_DIR = .obj 
UI_DIR = .ui


BASE_PATH = .
unix:BASE_PATH = $$system(pwd)
include(../tools/qbuild/common.pro) 