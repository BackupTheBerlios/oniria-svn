# $Id$

TEMPLATE = lib
TARGET = oxml
win32:debug:TARGET = oxml-debug
QT -= gui
QT += xml
DEFINES += BUILDING_LIBOXML_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              src

# Input
HEADERS += src/dll.h \
           src/oxml.h \
	   src/oxml_config.h \
	   src/xmlAttribute.h \
	   src/xmlElement.h \
	   src/xmlStanza.h \
	   src/xmlStream.h

SOURCES += src/xml.cc \
	   src/xmlAttribute.cc \
	   src/xmlElement.cc \
	   src/xmlStanza.cc \
	   src/xmlStream.cc

include(../../tools/qbuild/common.pro)