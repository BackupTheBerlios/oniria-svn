# $Id$

message("Win32 build")
BASE_DIR = .
!win32-g++: QMAKE_CXXFLAGS = -TP -G6 -GR -GX -Zi
CONFIG *= rtti
