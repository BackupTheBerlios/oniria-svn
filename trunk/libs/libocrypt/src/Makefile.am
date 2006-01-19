# $Id$

ocryptincludedir = $(includedir)/ocrypt

EXTRA_DIST = ocrypt_config.h.in

lib_LTLIBRARIES = libocrypt.la

libocrypt_la_CPPFLAGS = -Wall @QT_CFLAGS@ -DBUILDING_LIBOCRYPT_DLL
libocrypt_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) \
		       @qt_libs@

libocrypt_la_SOURCES = crypt.cc				\
		       cptHash.cc			\
		       cptMD5.cc			\
		       cptHMAC.cc			\
		       cptBase16.cc			\
		       cptBase64.cc


nobase_ocryptinclude_HEADERS = ocrypt.h			\
			       cptHash.h		\
			       cptMD5.h			\
			       cptHMAC.h		\
			       cptBase16.h		\
			       cptBase64.h

ocryptinclude_DATA = ocrypt_config.h

