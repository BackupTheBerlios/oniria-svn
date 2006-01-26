# $Id$

SUBDIRS = . tests

ocryptincludedir = $(includedir)/oniria/ocrypt

EXTRA_DIST = ocrypt_config.h.in

lib_LTLIBRARIES = libocrypt.la

libocrypt_la_CPPFLAGS = -Wall @QT_CFLAGS@ -DBUILDING_LIBOCRYPT_DLL
libocrypt_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) @LIBTOOL_EXTRA_LDFLAGS@ \
		       @QT_LIBS@



libocrypt_la_HEADERS_moc = cptHash.h			\
			   cptMD5.h			\
			   cptHMAC.h

nobase_ocryptinclude_HEADERS = ocrypt.h				\
			       ocrypt_dll.h			\
			       cptBase16.h			\
			       cptBase64.h			\
			       $(libocrypt_la_HEADERS_moc)

libocrypt_la_SOURCES = crypt.cc					\
		       cptHash.cc				\
		       cptMD5.cc				\
		       cptHMAC.cc				\
		       cptBase16.cc				\
		       cptBase64.cc				\
		       $(libocrypt_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

ocryptinclude_DATA = ocrypt_config.h

%.moc.cc: %.h
	$(QTMOC) $< -o $@

