# $Id$

noinst_PROGRAMS = xmppTest

INCLUDES = -I.. @QT_CFLAGS@
LDADD = -L../ -loxml @QT_LIBS@
DEPENDENCIES = ../liboxml.la

#xmppTest_HEADERS_moc = xmppTest.h
xmppTest_SOURCES = xmppTest.cc	\
		   xmppTest.h	\
		   xmppTest.moc.cc

CLEANFILES = *.moc.cc

%.moc.cc: %.h
	$(QTMOC) $< -o $@

