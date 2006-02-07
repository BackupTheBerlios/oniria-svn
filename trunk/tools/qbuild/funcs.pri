# $Id$
#Test functions

include(unix/tests.pri)

defineTest(createFile){
	file = $$1
	message(CreateFile $$file)
	exists($$file):system(rm -f $$file)
	system(echo '/*  Do not change this file, all changes will be lost*/ ' > $$file)	
	return(true)
}

isEmpty(package):package = $${TARGET}
isEmpty(libdir):libdir = $${LIB_DIR}
isEmpty(includedir):includedir = $${INCLUDE_DIR}
isEmpty(prefix):prefix = $${PREFIX}
REPLACE_KEYWORDS *= PREFIX LIB_DIR INCLUDE_DIR VERSION TARGET DOC_DIR PACKAGE package includedir libdir prefix

defineTest(keywordReplace){
	infile = $$1
	outfile = $$2
	vars = $$eval($$3)	
	isEmpty(vars):vars = $$REPLACE_KEYWORDS
	sed_args = 
	for(var, vars){
		sed_args += -e's!@$$var@!$$eval($$var)!g' 
	}
	message(Generate file: $$outfile)
	system(sed $$sed_args $$infile > $$outfile)
	return (true)	
}

defineTest(keywordFilesReplace){	
	files = $$eval($$1)
	vars = $$2
	isEmpty(vars):vars = $$REPLACE_KEYWORDS
	for(file, files){
		fil = $$BASE_PATH/$${file}	
		exists($${fil}.in){
			keywordReplace($${fil}.in, $$fil, $$vars)
		}else:warning(file not found: $${fil}.in)
		
	}
	return (true)
}

defineTest(configFilesReplace){
	!isEmpty(CONFIG_FILES){
		keywordFilesReplace(CONFIG_FILES)
		return (true)		
	}
	return(false)
}

#Cache file functions
isEmpty(CACHE_FILE):CACHE_FILE = $${BASE_PATH}/.$${TARGET}_cache

defineTest(addToCacheFile){
	vars = $$eval($$1)
	file = $$2
	isEmpty(file):file = $$CACHE_FILE
	!exists($$file):createFile($$file)
	for(var, vars){
		system(sed -n -e'/:_$${var}_=/!p; $a\:_$${var}_=$$eval($${var})' $${file} > $${file}_temp)
		system(mv -f $${file}_temp $$file)
	}
	return (true)
}


isEmpty(CACHE_VARS):CACHE_VARS *= $$REPLACE_KEYWORDS

defineTest(cacheKeywords){	
	addToCacheFile(CACHE_VARS)
	return (true)
}

defineReplace(getFromCache){
	varname = $$1
	file = $$2
	isEmpty(file):file = $$CACHE_FILE
	exists($$file){
		var = $$system(sed -e'/^:_$${varname}_=/!d; /^:_$${varname}_=/{s/^:_$${varname}_=//}' $$file)
		return ($$var)
	}
}

