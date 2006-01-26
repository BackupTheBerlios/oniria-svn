# $Id$

TEMPLATE = lib
TARGET = ocrypt
CONFIG += dll
win32:debug:TARGET = ocrypt-debug
QT -= gui
QT += xml
DEFINES += BUILDING_LIBOCRYPT_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              sra

OCRYPT_MAJOR_VERSION=0
OCRYPT_MINOR_VERSION=1
OCRYPT_MICRO_VERSION=0
OCRYPT_INTERFACE_AGE=0
OCRYPT_BINARY_AGE=0
OCRYPT_VERSION=$${OCRYPT_MAJOR_VERSION}.$${OCRYPT_MINOR_VERSION}.$${OCRYPT_MICRO_VERSION}

# Input
HEADERS += src/ocrypt_dll.h \
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

CONFIG_FILES = src/ocrypt_config.h \
		libocrypt.pc \
		doxygen.cfg

REPLACE_KEYWORDS *= OCRYPT_MAJOR_VERSION OCRYPT_MINOR_VERSION OCRYPT_MICRO_VERSION OCRYPT_INTERFACE_AGE OCRYPT_BINARY_AGE OCRYPT_VERSION

BASE_PATH = .
unix:BASE_PATH = $$system(pwd)

include(../../tools/qbuild/common.pro)
