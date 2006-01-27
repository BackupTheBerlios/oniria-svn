# $Id$

oxmlincludedir = $(includedir)/oniria/oxml

SUBDIRS = . tests

EXTRA_DIST = oxml_config.h.in

lib_LTLIBRARIES = liboxml.la

liboxml_la_CPPFLAGS = -Wall @QT_CFLAGS@ -DBUILDING_LIBOXML_DLL
liboxml_la_LDFLAGS = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		       -release $(LT_RELEASE) @LIBTOOL_EXTRA_LDFLAGS@ \
		       @QT_LIBS@



liboxml_la_HEADERS_moc = xmlAttribute.h			\
			 xmlElement.h			\
			 xmlStanza.h			\
			 xmlStream.h

nobase_oxmlinclude_HEADERS = oxml.h				\
			     oxml_dll.h				\
			     $(liboxml_la_HEADERS_moc)

liboxml_la_SOURCES = xml.cc					\
		     xmlAttribute.cc				\
		     xmlElement.cc				\
		     xmlStanza.cc				\
		     xmlStream.cc				\
		     $(liboxml_la_HEADERS_moc:.h=.moc.cc)

CLEANFILES = *.moc.cc

oxmlinclude_DATA = oxml_config.h

%.moc.cc: %.h
	$(QTMOC) $< -o $@

