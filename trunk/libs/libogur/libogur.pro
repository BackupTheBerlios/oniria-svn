# $Id$

CONFIG 		*= debug warn_on dll
TEMPLATE 	= lib
LIBRARY_NAME 	= ogur
TARGET		= $${LIBRARY_NAME}
VERSION		= 0.0.1

DEFINES 	+= BUILDING_LIBOGUR_DLL QT_NO_CAST_TO_ASCII

# Input
HEADERS       = src/ogur_dll.h \
		src/gcore.h \
		src/gtreelist.h \
		src/gtreelistItem.h \
		src/gaction.h \
		src/gtreelistitemmoveaction.h \
		src/gtreelistitemtable.h
			
SOURCES       = src/gcore.cc \
		src/gtreelistItem.cc \
		src/gtreelist.cc \
		src/gaction.cc \
		src/gtreelistitemmoveaction.cc \
		src/gtreelistitemtable.cc


CONFIG_FILES = libogur.pc 
DOC_INPUT = doxygen.cfg
		
#output
DESTDIR = ./bin
MOC_DIR = .moc
OBJECTS_DIR = .obj

#########################################################
#########################################################

!isEmpty(BUILDING_LIBOGUR_STATIC){
	CONFIG *= staticlib
	DEFINES -= BUILDING_LIBOGUR_DLL
	DEFINES += BUILDING_LIBOGUR_STATIC
}

win32{
	isEmpty(DESIGNER_PLUGIN){	
		target.commands = win32-install
		target.path += ../../win32-build		
	}else{
		target.path = $$[QT_INSTALL_PLUGINS]/designer 
	}	
	INSTALLS += target
}

BASE_PATH = .
unix:BASE_PATH = $$system(pwd)
include(../../tools/qbuild/common.pro)
