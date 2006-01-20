# $Id$

TEMPLATE = lib
TARGET = ocrypt
CONFIG += dll
win32:debug:TARGET = ocrypt-debug
QT -= gui
QT += xml
DEFINES += BUILDING_LIBOCRYPT_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              src

# Input
HEADERS += src/dll.h \
           src/ocrypt.h \
	   src/ocrypt_config.h \
	   src/cptHash.h \
	   src/cptMD5.h \
	   src/cptHMAC.h \
	   src/cptBase16.h \
	   src/cptBase64.h

SOURCES += src/crypt.cc \
	   src/cptHash.cc \
	   src/cptMD5.cc \
	   src/cptHMAC.cc \
	   src/cptBase16.cc \
	   src/cptBase64.cc

DOC_INPUT = doxygen.cfg
	 
include(../../tools/qbuild/common.pro)