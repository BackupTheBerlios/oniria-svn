# $Id$

message("Unix build")

isEmpty(BASE_PATH):error(You must set basedir in 'BASE_PATH' variable. eg. "BASE_PATH = \$$system(pwd)")
include(funcs.pri)

isEmpty(PREFIX){
	PREFIX = $$getFromCache(PREFIX)
	isEmpty(PREFIX):PREFIX =/usr
}

isEmpty(LIB_DIR){
	LIB_DIR = $$getFromCache(LIB_DIR)
	isEmpty(LIB_DIR):LIB_DIR = $${PREFIX}/lib
}

isEmpty(INCLUDE_DIR){
	INCLUDE_DIR = $$getFromCache(INCLUDE_DIR)
	isEmpty(INCLUDE_DIR):INCLUDE_DIR = $${PREFIX}/include
}

isEmpty(DOC_DIR){
	DOC_DIR = $$getFromCache(DOC_DIR)
	isEmpty(DOC_DIR):DOC_DIR = $${PREFIX}/share/doc
}

INCLUDEPATH *= $${INCLUDE_DIR}
INCLUDEPATH *= /usr/include

LIBS *= -L$${LIB_DIR}
LIBS *= -L/usr/lib

!hpux:QMAKE_COPY_FILE = $${QMAKE_COPY_FILE} -P

# install header
include.path += $${INCLUDE_DIR}/$${TARGET}
include.files += $${HEADERS} 

# install library
target.path += $${LIB_DIR}

# "make install" configuration options
INSTALLS += target include

cacheKeywords()
configFilesReplace()

message(BASE_PATH = $${BASE_PATH})
message(PREFIX = $${PREFIX})
message(LIB_DIR = $${LIB_DIR})
message(INCLUDE_DIR = $${INCLUDE_DIR})
message(DOC_DIR = $${DOC_DIR})
message(TARGET = $${TARGET})
