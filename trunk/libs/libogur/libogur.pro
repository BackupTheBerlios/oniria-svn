# $Id$

CONFIG += debug precompile_header
TEMPLATE = lib
LIBRARY_NAME = ogur
DEFINES += BUILDING_LIBOGUR_DLL QT_NO_CAST_TO_ASCII

#Precompiled headers
PRECOMPILED_HEADER  = src/dll.h src/ogur_config.h


# Input
HEADERS +=	src/dll.h \
			src/ogur_config.h \
			src/TreeList.h \
			src/TreeListItem.h


SOURCES +=	src/TreeListItem.cc \
			src/TreeList.cc

#output
DESTDIR = ./
CONFIG(release, debug|release){		
		message(Release build!)
		TARGET = $${LIBRARY_NAME}
	}
CONFIG(debug, debug|release){
		message(Debug build!) #no print
		TARGET = $${LIBRARY_NAME}-debug
	}
	
#messages
message (Library Target: $${TARGET} )
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Qt resources can be found in the following locations:)
message(Header files: $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary files (executables): $$[QT_INSTALL_BINS])