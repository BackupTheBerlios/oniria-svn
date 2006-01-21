# $Id$

osaslincludedir = $(includedir)/oniria/osasl

EXTRA_DIST = osasl_config.h.in

lib_LTLIBRARIES = libosasl.la

libosasl_la_CPPFLAGS = -Wall @QT_CFLAGS@ @OCRYPT_CFLAGS@ -DBUILDING_LIBOSASL_DLL
libosasl_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) \
		       @QT_LIBS@ @OCRYPT_LIBS@



libosasl_la_HEADERS_moc = saslCallback.h			\
			  saslMechanism.h			\
			  saslSASL.h				\
			  saslDIGESTMD5.h

nobase_osaslinclude_HEADERS = osasl.h				\
			      osasl_dll.h			\
			      $(libosasl_la_HEADERS_moc)

libosasl_la_SOURCES = sasl.cc					\
		      saslCallback.cc				\
		      saslMechanism.cc				\
		      saslSASL.cc				\
		      saslDIGESTMD5.cc				\
		      $(libosasl_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

osaslinclude_DATA = osasl_config.h

%.moc.cc: %.h
	$(QTMOC) $< -o $@

