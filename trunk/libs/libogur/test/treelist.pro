
CONFIG += warn_on debug console
TEMPLATE = app
#DEFINES += BUILDING_LIBOGUR_DLL
INCLUDEPATH += ../src

HEADERS = treelist.h
SOURCES = treelist.cc

unix:LIBS += -L../bin -logur
win32:LIBS += -L ../bin -logur-debug0

RESOURCES = treelist.qrc

RCC_DIR = res

MOC_DIR = moc

win32:{
	DESTDIR = ../bin
	target.path = ../bin
	INSTALLS += target
}

