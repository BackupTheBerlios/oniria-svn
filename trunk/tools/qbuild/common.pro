
isEmpty(BUILD_DIR_PREFIX){
	BUILD_DIR_PREFIX = .
}

isEmpty(MOC_DIR){
        MOC_DIR = $${BUILD_DIR_PREFIX}/.moc
}

isEmpty(OBJ_DIR){
        OBJ_DIR = $${BUILD_DIR_PREFIX}/.obj
}
		

#system specific conditions

unix{
	
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
  	staticlib.extra = make staticlib
  	staticlib.path = $${LIB_DIR}
  	staticlib.files = lib$${TARGET}.a

  	# install library
  	target.path = $${LIB_DIR}

  	# "make install" configuration options
  	INSTALLS += target staticlib include #documentation 

}

win32{
	!win32-g++: QMAKE_CXXFLAGS = -TP -G6 -GR -GX -Zi
	CONFIG *= rtti
	#DEFINES *= QT_THREAD_SUPPORT
}

