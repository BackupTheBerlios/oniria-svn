# $Id$

noinst_PROGRAMS = xmpp parser

INCLUDES = -I.. @QT_CFLAGS@
LDADD = -L../ -loxml @QT_LIBS@
DEPENDENCIES = ../liboxml.la

#xmppTest_HEADERS_moc = xmppTest.h
xmpp_SOURCES = xmppTest.cc	\
	       xmppTest.h	\
	       xmppTest.moc.cc

parser_SOURCES = parser.cc

EXTRADIST = test.xml

CLEANFILES = *.moc.cc

%.moc.cc: %.h
	$(QTMOC) $< -o $@

