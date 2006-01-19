# $Id$

# variables:
# DOC_INPUT - specs input file for doxygen doc generator
# BUILD_DIR_PREFIX 

QMAKE_EXT_MOC = .cc

include(funcs.pri)

isEmpty(BUILD_DIR_PREFIX){
	BUILD_DIR_PREFIX = .
}

MOC_DIR = $${BUILD_DIR_PREFIX}/.moc
OBJ_DIR = $${BUILD_DIR_PREFIX}/.obj

unix:include(unix.pro)
win32:include(win32.pro)

!isEmpty(DOC_INPUT){
	dox.target = doc
	dox.commands = doxygen $${DOC_INPUT}
	dox.depends =
	QMAKE_EXTRA_TARGETS += doc
	message(DOC: $${DOC_INPUT})
}