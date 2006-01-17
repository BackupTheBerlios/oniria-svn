# $Id$

TEMPLATE = lib
TARGET = onir
win32:debug:TARGET = onir-debug
QT -= gui
DEFINES += BUILDING_LIBONIR_DLL QT_NO_CAST_TO_ASCII
DEPENDPATH += . \
              src \
              src/crypt \
              src/win32 \
              src/utils 

win32 {
	INCLUDEPATH += ../libs/win32/libidn/include ../libs/win32/iconv/include
}

win32:LIBS = -L../libs/win32/libidn/lib -lidn -L../libs/win32/iconv/lib -liconv

# Input
HEADERS += src/dll.h \
           src/onir.h \
           src/plugin.h \
           src/win32/config.h \
           src/win32/onir_config.h \
           src/oObject.h \
           src/oOniria.h \
           src/utils/uBase16.h \
           src/utils/uBase64.h \
           src/crypt/cptHash.h \
           src/crypt/cptHMAC.h \
           src/crypt/cptMD5.h \
	   src/sasl/saslCallback.h \
	   src/sasl/saslMechanism.h 

SOURCES += src/onir.cc \
           src/oObject.cc \
           src/oOniria.cc \
           src/utils/utils.cc \
           src/utils/uBase16.cc \
           src/utils/uBase64.cc \
           src/crypt/cptHash.cc \
           src/crypt/cptHMAC.cc \
           src/crypt/cptMD5.cc \
           src/crypt/crypt.cc \
	   src/sasl/sasl.cc \
	   src/sasl/saslCallback.cc \
	   src/sasl/saslMechanism.cc 

