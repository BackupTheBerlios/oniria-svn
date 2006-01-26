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

isEmpty(PACKAGE):PACKAGE = $${TARGET}
REPLACE_KEYWORDS *= PREFIX LIB_DIR INCLUDE_DIR VERSION TARGET DOC_DIR PACKAGE

defineTest(keywordReplace){
	infile = $$1
	outfile = $$2
	vars = $$eval($$3)	
	isEmpty(vars):vars = $$REPLACE_KEYWORDS
	sed_args = 
	for(var, vars){
		sed_args += -e's!@$$var@!$$eval($$var)!g' 
	}
	system(sed $$sed_args $$infile > $$outfile)
	return (true)	
}

defineTest(keywordFilesReplace){
	files = $$eval($$1)
	vars = $$2
	isEmpty(vars):vars = $$REPLACE_KEYWORDS
	for(file, files){
		file_test = $$find(file, .in$)
		count(file_test, 1){
			fil = $$BASE_PATH/$$file		
			exists($$fil){
				keywordReplace($$fil, $$system(echo $$fil | sed -e's/.in$//'), $$vars)
			}else:warning(file not found: $$fil)
		}
		
	}
	return (true)
}

#Cache file functions
isEmpty(CACHE_FILE):CACHE_FILE = $${BASE_PATH}/$${TARGET}_cache.cse

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
	var = $$system(sed -e'/^:_$${varname}_=/!d; /^:_$${varname}_=/{s/^:_$${varname}_=//}' $$file)
	return ($$var)
}

