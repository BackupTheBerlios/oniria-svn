CONFIG      += designer plugin release
TEMPLATE    = lib
DESTDIR     = bin

unix:LIBS += -L../bin -logur
win32:LIBS += -L ../bin -logur-debug0 

INCLUDEPATH += ../src 

CONFIG(debug, debug|release) {
    unix: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,d)
}

DEFINES += BUILD_LIB_OGUR_STATIC

HEADERS       = ../src/ogur_dll.h \
		../src/gcore.h \
		../src/gtreelist.h \
		../src/gtreelistItem.h \
		../src/gaction.h \
		../src/gtreelistitemmoveaction.h \
		gtreelistplugin.h
			
SOURCES       = ../src/gcore.cc \
		../src/gtreelistItem.cc \
		../src/gtreelist.cc \
		../src/gaction.cc \
		../src/gtreelistitemmoveaction.cc \
		gtreelistplugin.cc

RESOURCES = gtreelistplugin.qrc 

MOC_DIR = .moc
OBJECTS_DIR = .obj

# install
target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/gtreelistplugin
INSTALLS += target sources
