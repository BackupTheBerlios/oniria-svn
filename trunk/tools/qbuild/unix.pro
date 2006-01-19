unix{
	message("Unix build")
	isEmpty(PREFIX){
		PREFIX = /usr
	}

	isEmpty(LIB_DIR){
		LIB_DIR = $${PREFIX}/lib
	}

	isEmpty(INCLUDE_DIR){
		INCLUDE_DIR = $${PREFIX}/include
	}

	isEmpty(DOC_DIR){
		DOC_DIR = $${PREFIX}/share/doc
	}

	!hpux {
	    QMAKE_COPY_FILE = $${QMAKE_COPY_FILE} -P
	}
  	# install header
  	include.path = $${INCLUDE_DIR}/$${TARGET}
  	include.files = $${HEADERS}

  	# install documentation html
  	#documentation.path = $${DOC_DIR}/$${TARGET}
  	#documentation.files = ../doc/*.html ../doc/*.css

  	# install documentation refManual
  	#docRefManual.path = $${DOC_DIR}/$${TARGET}
  	#docRefManual.files = ../doc/refManual/*

  	# install static library  	
  	#staticlib.path = $${LIB_DIR}
  	#staticlib.files = lib$${TARGET}.a
	
	#install dynamic library
	dll.files = $${TARGET}.so
	dll.path = $${LIB_DIR}

  	# install library
  	target.path = $${LIB_DIR}

  	# "make install" configuration options
  	INSTALLS += target include dll#documentation 
}