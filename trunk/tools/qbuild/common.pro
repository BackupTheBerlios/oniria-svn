# $Id$

# variables:
# DOC_INPUT - specs input file for doxygen doc generator

QMAKE_EXT_MOC = .cc

include(funcs.pri)

isEmpty(BUILD_DIR_PREFIX){
	BUILD_DIR_PREFIX = .
}

isEmpty(MOC_DIR){
        MOC_DIR = $${BUILD_DIR_PREFIX}/.moc
}

!isEmpty(OBJ_DIR):OBJ_DIR = $${BUILD_DIR_PREFIX}/.obj

unix:include(unix.pro)
win32:include(win32.pro)

!isEmpty(DOC_INPUT){
	dox.target = doc
	dox.commands = doxygen $${DOC_INPUT}
	dox.depends =
	QMAKE_EXTRA_TARGETS += doc
	message(DOC: $${DOC_INPUT})
}