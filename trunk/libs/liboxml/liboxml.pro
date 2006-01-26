# $Id$

TEMPLATE = lib
TARGET = oxml
CONFIG += dll
win32:debug:TARGET = oxml-debug
QT -= gui
QT += xml
DEFINES += BUILDING_LIBOXML_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              src

OXML_MAJOR_VERSION=0
OXML_MINOR_VERSION=1
OXML_MICRO_VERSION=0
OXML_INTERFACE_AGE=0
OXML_BINARY_AGE=0
OXML_VERSION=$${OXML_MAJOR_VERSION}.$${OXML_MINOR_VERSION}.$${OXML_MICRO_VERSION}

	      
# Input
HEADERS += src/oxml_dll.h \
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

DOC_INPUT = doxygen.cfg

CONFIG_FILES = 	doxygen.cfg \
		liboxml-config \
		liboxml.pc \
		src/oxml_config.h

		
REPLACE_KEYWORDS *= OXML_MAJOR_VERSION OXML_MINOR_VERSION OXML_MICRO_VERSION OXML_INTERFACE_AGE OXML_BINARY_AGE OXML_VERSION
		
BASE_PATH =.
unix:BASE_PATH = $$system(pwd)
	 
include(../../tools/qbuild/common.pro)
