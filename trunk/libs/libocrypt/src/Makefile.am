# $Id$

# TODO: Add autoconf test for moc, anc use something like QTMOC macro.
# (???) Move moc rule to separate file, which could be included in other
# Makefiles.

ocryptincludedir = $(includedir)/ocrypt

EXTRA_DIST = ocrypt_config.h.in

lib_LTLIBRARIES = libocrypt.la

libocrypt_la_CPPFLAGS = -Wall @QT_CFLAGS@ -DBUILDING_LIBOCRYPT_DLL
libocrypt_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) \
		       @QT_LIBS@



libocrypt_la_HEADERS_moc = cptHash.h			\
			   cptMD5.h			\
			   cptHMAC.h			\
			   cptBase16.h			\
			   cptBase64.h

nobase_ocryptinclude_HEADERS = ocrypt.h				\
			       $(libocrypt_la_HEADERS_moc)

libocrypt_la_SOURCES = crypt.cc					\
		       cptHash.cc				\
		       cptMD5.cc				\
		       cptHMAC.cc				\
		       cptBase16.cc				\
		       cptBase64.cc				\
		       $(libocrypt_la_HEADERS_moc:.h=.moc.cc)


ocryptinclude_DATA = ocrypt_config.h

%.moc.cc: %.h
	moc $< -o $@

