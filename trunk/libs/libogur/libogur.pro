# $Id$

CONFIG 		*= debug precompile_header warn_on dll
TEMPLATE 	= lib
LIBRARY_NAME 	= ogur
TARGET		= $${LIBRARY_NAME}
VERSION		= 0.0.1


DEFINES 	+= BUILDING_LIBOGUR_DLL QT_NO_CAST_TO_ASCII

#Precompiled headers
PRECOMPILED_HEADER  = src/ogur_dll.h src/ogur_config.h


# Input
HEADERS +=	src/ogur_dll.h \
			src/ogur_config.h \
			src/TreeList.h \
			src/TreeListItem.h


SOURCES +=	src/TreeListItem.cc \
			src/TreeList.cc

#output
DESTDIR = ./bin
MOC_DIR = .moc
OBJECTS_DIR = .obj

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

DOC_INPUT = doxygen.cfg
	 
include(../../tools/qbuild/common.pro)
