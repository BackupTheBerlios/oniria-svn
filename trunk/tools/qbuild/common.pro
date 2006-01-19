
isEmpty(BUILD_DIR_PREFIX){
	BUILD_DIR_PREFIX = .
}

isEmpty(MOC_DIR){
        MOC_DIR = $${BUILD_DIR_PREFIX}/.moc
}

isEmpty(OBJ_DIR){
        OBJ_DIR = $${BUILD_DIR_PREFIX}/.obj
}

include(unix.pro)
include(win32.pro)