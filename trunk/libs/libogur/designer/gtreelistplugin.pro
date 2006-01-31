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

HEADERS     = gtreelistplugin.h
              
SOURCES     = gtreelistplugin.cc
              

# install
target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/gtreelistplugin
INSTALLS += target sources
