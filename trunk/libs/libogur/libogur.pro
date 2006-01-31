# $Id$

CONFIG 		*= debug warn_on dll
TEMPLATE 	= lib
LIBRARY_NAME 	= ogur
TARGET		= $${LIBRARY_NAME}
VERSION		= 0.0.1


DEFINES 	+= BUILDING_LIBOGUR_DLL QT_NO_CAST_TO_ASCII

#Precompiled headers
#PRECOMPILED_HEADER  = src/ogur_dll.h src/ogur_config.h


# Input
HEADERS       = src/ogur_dll.h \
		src/gcore.h \
		src/gtreelist.h \
		src/gtreelistItem.h \
		src/gaction.h \
		src/gtreelistitemmoveaction.h
			
SOURCES       = src/gcore.cc \
		src/gtreelistItem.cc \
		src/gtreelist.cc \
		src/gaction.cc \
		src/gtreelistitemmoveaction.cc


CONFIG_FILES = libogur.pc 
DOC_INPUT = doxygen.cfg
		
#output
DESTDIR = ./bin
MOC_DIR = .moc
OBJECTS_DIR = .obj

target.path = $$[QT_INSTALL_PLUGINS]/designer

#########################################################
#########################################################

win32:CONFIG(release, debug|release){		
		message(Release build!)
		TARGET = $${LIBRARY_NAME}
	}
win32:CONFIG(debug, debug|release){
		message(Debug build!) #no print
		TARGET = $${LIBRARY_NAME}-debug
	}
	

!isEmpty(BUILDING_LIBOGUR_STATIC){
	CONFIG *= staticlib
}

BASE_PATH = .
unix:BASE_PATH = $$system(pwd)
include(../../tools/qbuild/common.pro)
