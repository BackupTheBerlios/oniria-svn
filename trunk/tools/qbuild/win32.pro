# $Id$

message("Win32 build")
!win32-g++: QMAKE_CXXFLAGS = -TP -G6 -GR -GX -Zi
CONFIG *= rtti