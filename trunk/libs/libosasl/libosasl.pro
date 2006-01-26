# $Id$

# FIX: This probably will not work.
	
TEMPLATE = lib
TARGET = osasl
CONFIG += dll
win32:debug:TARGET = osasl-debug
QT -= gui
QT += xml
DEFINES += BUILDING_LIBOSASL_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              src

OSASL_MAJOR_VERSION=0
OSASL_MINOR_VERSION=1
OSASL_MICRO_VERSION=0
OSASL_INTERFACE_AGE=0
OSASL_BINARY_AGE=0
OSASL_VERSION=$${OSASL_MAJOR_VERSION}.$${OSASL_MINOR_VERSION}.$${OSASL_MICRO_VERSION}

	      
# Input
HEADERS += src/osasl_dll.h \
           src/osasl.h \
	   src/osasl_config.h \
	   src/saslCallback.h \
	   src/saslMechanism.h \
	   src/saslSASL.h \
	   src/saslDIGESTMD5.h

SOURCES += src/sasl.cc \
	   src/saslCallback.cc \
	   src/saslMechanism.cc \
	   src/saslSASL.cc \
	   src/saslDIGESTMD5.cc

DOC_INPUT = doxygen.cfg

CONFIG_FILES = libosasl-config \
		src/osasl_config.h \
		libosasl.pc \
		doxygen.cfg 

REPLACE_KEYWORDS *= OSASL_MAJOR_VERSION OSASL_MINOR_VERSION OSASL_MICRO_VERSION OSASL_INTERFACE_AGE OSASL_BINARY_AGE OSASL_VERSION 

BASE_PATH =.
unix:BASE_PATH = $$system(pwd)
include(../../tools/qbuild/common.pro)
