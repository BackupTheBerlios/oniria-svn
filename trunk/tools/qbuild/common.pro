# $Id$

# variables:
# DOC_INPUT - specs input file for doxygen doc generator

QMAKE_EXT_MOC = .cc

unix:include(unix.pro)
win32:include(win32.pro)

!isEmpty(DOC_INPUT){
	dox.target = doc
	dox.commands = doxygen $${DOC_INPUT}
	dox.depends =
	QMAKE_EXTRA_TARGETS += doc
}
