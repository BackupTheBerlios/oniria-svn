win32{
	message("Win32 build")
	!win32-g++: QMAKE_CXXFLAGS = -TP -G6 -GR -GX -Zi
	CONFIG *= rtti
	#DEFINES *= QT_THREAD_SUPPORT
}