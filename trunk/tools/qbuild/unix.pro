# $Id$

#NO_CACHE_FILE

message("Unix build")

isEmpty(NO_CACHE_FILE){
	CACHE_FILE = .$${TARGET}_cache.cse

	#Cache file
	exists($${CACHE_FILE}){
		message(wczytywanie cache)
		include($${CACHE_FILE})	
	}
}

isEmpty(PREFIX){
	!isEmpty(_C_PREFIX):PREFIX = $${_C_PREFIX}
	else:PREFIX =/usr
}else{
	
}

isEmpty(LIB_DIR){
	!isEmpty(_C_LIB_DIR):LIB_DIR = $${_C_LIB_DIR}
	else:LIB_DIR = $${PREFIX}/lib
}

isEmpty(INCLUDE_DIR){
	!isEmpty(_C_INCLUDE_DIR):INCLUDE_DIR = $${_C_INCLUDE_DIR}
	else:INCLUDE_DIR = $${PREFIX}/include
}

isEmpty(DOC_DIR){
	!isEmpty(_C_DOC_DIR):DOC_DIR = $${_C_DOC_DIR}
	else:DOC_DIR = $${PREFIX}/share/doc
}


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

isEmpty(NO_CACHE_FILE){
	message(Write cache file into $${CACHE_FILE})
	system(rm -f $${CACHE_FILE} || touch $${CACHE_FILE})
	system(echo _C_PREFIX=$${PREFIX} >> $${CACHE_FILE})
}