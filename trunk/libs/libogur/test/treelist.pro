
CONFIG += warn_on debug
TEMPLATE = app
SOURCES = treelist.cc
unix:LIBS += -L../bin -logur
win32:LIBS += -L ../bin -logur-debug0

win32:{
	target.path = ../bin
	INSTALLS += target
}

