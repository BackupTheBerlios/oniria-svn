# $Id$

onirincludedir = $(includedir)/oniria/onir

#SUBDIRS = . tests

EXTRA_DIST = onir_config.h.in

lib_LTLIBRARIES = libonir.la

libonir_la_CPPFLAGS = -Wall @QT_CFLAGS@ -DBUILDING_LIBONIR_DLL
libonir_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) @LIBTOOL_EXTRA_LDFLAGS@ \
		       @QT_LIBS@



libonir_la_HEADERS_moc =

nobase_onirinclude_HEADERS = onir.h				\
			     onir_dll.h				\
			     $(libonir_la_HEADERS_moc)

libonir_la_SOURCES = onir.cc					\
		     $(libonir_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

onirinclude_DATA = onir_config.h

%.moc.cc: %.h
	$(QTMOC) $< -o $@

