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

OIM_MAJOR_VERSION=0
OIM_MINOR_VERSION=1
OIM_MICRO_VERSION=0
OIM_INTERFACE_AGE=0
OIM_BINARY_AGE=0
OIM_VERSION=$${OIM_MAJOR_VERSION}.$${OIM_MINOR_VERSION}.$${OIM_MICRO_VERSION}

	      
# Input
HEADERS += src/oim_dll.h \
           src/oim.h \
	   src/oim_config.h 

SOURCES += src/sasl.cc 

DOC_INPUT = doxygen.cfg

CONFIG_FILES = liboim-config \
		src/oim_config.h \
		liboim.pc \
		doxygen.cfg

REPLACE_KEYWORDS *= OIM_MAJOR_VERSION OIM_MINOR_VERSION OIM_MICRO_VERSION OIM_INTERFACE_AGE OIM_BINARY_AGE OIM_VERSION 

BASE_PATH =.
unix:BASE_PATH=$$system(pwd)

include(../../tools/qbuild/common.pro)
