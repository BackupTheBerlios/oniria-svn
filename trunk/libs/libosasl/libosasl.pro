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

# Input
HEADERS += src/dll.h \
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
	 
include(../../tools/qbuild/common.pro)
