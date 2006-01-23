# $Id$

# FIX: This probably will not work.
	
TEMPLATE = lib
TARGET = oim
CONFIG += dll
win32:debug:TARGET = oim-debug
QT -= gui
QT += xml
DEFINES += BUILDING_LIBOIM_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              src

# Input
HEADERS += src/dll.h \
           src/oim.h \
	   src/oim_config.h 

SOURCES += src/sasl.cc 

DOC_INPUT = doxygen.cfg
	 
include(../../tools/qbuild/common.pro)
