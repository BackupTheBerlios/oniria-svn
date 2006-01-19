# $Id$

message("Unix build")

isEmpty(PREFIX):PREFIX =/usr
isEmpty(LIB_DIR):LIB_DIR = $${PREFIX}/lib
isEmpty(INCLUDE_DIR):INCLUDE_DIR = $${PREFIX}/include
isEmpty(DOC_DIR):DOC_DIR = $${PREFIX}/share/doc

!hpux:QMAKE_COPY_FILE = $${QMAKE_COPY_FILE} -P

# install header
include.path = $${INCLUDE_DIR}/$${TARGET}
include.files = $${HEADERS}

# install library
target.path = $${LIB_DIR}

# "make install" configuration options
INSTALLS += target include

message(PREFIX = $${PREFIX})
message(LIB_DIR = $${LIB_DIR})
message(INCLUDE_DIR = $${INCLUDE_DIR})
message(DOC_DIR = $${DOC_DIR})
message(TARGET = $${TARGET})